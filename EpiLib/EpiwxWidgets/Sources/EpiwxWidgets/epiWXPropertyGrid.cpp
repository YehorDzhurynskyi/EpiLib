#include "EpiwxWidgets/epiWXPropertyGrid.h"

#include "EpiwxWidgets/epiWXPlot.h"

#include <wx/wx.h>

#include <fmt/core.h>

EPI_NAMESPACE_USING()

wxBEGIN_EVENT_TABLE(epiWXPropertyGrid, wxPropertyGrid)
    EVT_PG_CHANGED(-1, epiWXPropertyGrid::OnPropertyGridChanged)
    EVT_PG_RIGHT_CLICK(-1, epiWXPropertyGrid::OnPropertyGridRightClick)
wxEND_EVENT_TABLE()

epiWXPropertyGrid::epiWXPropertyGrid(wxWindow* parent,
                                     wxWindowID id,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxString& name)
    : wxPropertyGrid(parent, id, pos, size, style, name)
{
}

void epiWXPropertyGrid::Clear()
{
    wxPropertyGrid::Clear();

    m_PropertyPointers.clear();
}

void epiWXPropertyGrid::SetObject(Object& object)
{
    Clear();

    FillCompound(object, nullptr);
}

void epiWXPropertyGrid::FillCompound(Object& object, wxPGProperty* prty)
{
    const MetaClass& meta = object.GetMetaClass();
    epiAssert(MetaType::IsCompound(meta.GetTypeID()));

    const MetaClass* m = &meta;
    do
    {
        const MetaClassData& metaClassData = m->GetClassData();

        if (metaClassData.GetPropertiesCount() > 0)
        {
            wxPGProperty* p = new wxStringProperty(m->GetName(), wxPG_LABEL, "");
            p = prty != nullptr ? prty->InsertChild(0, p) : Append(p);
            p->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_NOEDITOR, true);

            FillProperties(object, metaClassData, p);
        }

        epiAssert(MetaType::IsCompound(m->GetSuperTypeID()) || m->GetSuperTypeID() == epiMetaTypeID_None);
        if (m->GetSuperTypeID() == epiMetaTypeID_None)
        {
            break;
        }
        m = ClassRegistry_Type_Lookup(m->GetSuperTypeID());
        epiAssert(m);
    } while (true);
}

void epiWXPropertyGrid::FillMultiDimensional(epiBaseArray& array, epiMetaTypeID nestedTypeID, wxPGProperty* parentPrty)
{
    const epiSize_t arraySz = array.GetSize();
    for (epiU32 i = 0; i < arraySz; ++i)
    {
        const epiString label = fmt::format("[{:d}]", i);

        auto ptr = new PropertyPointer();
        *ptr = PropertyPointer::CreateFromArray(array, nestedTypeID, i);

        if (MetaType::IsFundamental(nestedTypeID))
        {
            AddFundamental(*ptr, label.c_str(), parentPrty, true);
        }
        else if (MetaType::IsString(nestedTypeID))
        {
            AddString(*ptr, label.c_str(), parentPrty, true);
        }
        else if (MetaType::IsCompound(nestedTypeID))
        {
            Object& obj = ptr->Get<Object>();
            wxPGProperty* prty = new wxStringProperty(label.c_str(), wxPG_LABEL, obj.ToString().c_str());
            AddProperty(*ptr, prty, parentPrty, true);

            FillCompound(obj, prty);
        }
        else
        {
            epiAssert(false, "Unhandled case");
        }

        // TODO: replace unique_ptr with plain type
        // PROBLEM: property's client data dangling pointer
        m_PropertyPointers.push_back(ptr);
    }
}

void epiWXPropertyGrid::FillMultiDimensionalPtr(epi::epiBaseArray& array, epi::epiMetaTypeID nestedTypeID, wxPGProperty* parentPrty)
{
    const epiSize_t arraySz = array.GetSize();
    for (epiU32 i = 0; i < arraySz; ++i)
    {
        const epiString label = fmt::format("[{:d}]", i);

        auto ptr = new PropertyPointer();
        *ptr = PropertyPointer::CreateFromArray(array, epiMetaTypeID_Ptr, i);

        if (MetaType::IsCompound(nestedTypeID))
        {
            Object* obj = ptr->Get<Object*>();
            wxPGProperty* prty = new wxStringProperty(label.c_str(), wxPG_LABEL, obj->ToString().c_str());
            AddProperty(*ptr, prty, parentPrty, true);

            FillCompound(*obj, prty);
        }
        else
        {
            // TODO: finish other branches
            epiAssert(false, "Unhandled case");
        }

        // TODO: replace unique_ptr with plain type
        // PROBLEM: property's client data dangling pointer
        m_PropertyPointers.push_back(ptr);
    }
}

void epiWXPropertyGrid::FillProperties(Object& object, const MetaClassData& meta, wxPGProperty* parentPrty)
{
    for (epiU32 i = 0; i < meta.GetPropertiesCount(); ++i)
    {
        const MetaProperty* property = meta.GetPropertyAt(i);
        epiAssert(property != nullptr);

        const epiBool editable = !property->GetFlags().ReadOnly;
        const epiChar* label = property->GetName();

        auto ptr = new PropertyPointer();
        *ptr = PropertyPointer::CreateFromProperty(object, property);

        if (MetaType::IsFundamental(property->GetTypeID()))
        {
            AddFundamental(*ptr, label, parentPrty, editable);
        }
        else if (MetaType::IsString(property->GetTypeID()))
        {
            AddString(*ptr, label, parentPrty, editable);
        }
        else if (MetaType::IsMultiDimensional(property->GetTypeID()))
        {
            wxPGProperty* prty = new wxStringProperty(property->GetName(), wxPG_LABEL, "<Array>");
            AddProperty(*ptr, prty, parentPrty, editable);

            if (property->GetTypeID() == epiMetaTypeID_epiArray)
            {
                FillMultiDimensional(ptr->Get<epiBaseArray>(), property->GetNestedTypeID(), prty);
            }
            else if (property->GetTypeID() == epiMetaTypeID_epiPtrArray)
            {
                FillMultiDimensionalPtr(ptr->Get<epiBaseArray>(), property->GetNestedTypeID(), prty);
            }
            else
            {
                epiAssert(false, "Unhandled case");
            }
        }
        else if (MetaType::IsPointer(property->GetTypeID()))
        {
            wxPGProperty* prty = new wxStringProperty(label, wxPG_LABEL, "");
            AddProperty(*ptr, prty, parentPrty, editable);

            FillCompound(*ptr->Get<Object*>(), prty);
        }
        else if (MetaType::IsCompound(property->GetTypeID()))
        {
            wxPGProperty* prty = new wxStringProperty(label, wxPG_LABEL, "");
            AddProperty(*ptr, prty, parentPrty, editable);

            FillCompound(ptr->Get<Object>(), prty);
        }
        else
        {
            epiAssert(false, "Unhandled case");
        }

        // TODO: replace unique_ptr with plain type
        // PROBLEM: property's client data dangling pointer
        m_PropertyPointers.push_back(ptr);
    }
}

void epiWXPropertyGrid::AddFundamental(PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable)
{
    epiAssert(MetaType::IsFundamental(ptr.GetTypeID()));

    wxPGProperty* prty = nullptr;
    switch (ptr.GetTypeID())
    {
    case epiMetaTypeID_epiChar: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiChar>()); break;
    case epiMetaTypeID_epiWChar: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiWChar>()); break;
    case epiMetaTypeID_epiBool: prty = new wxBoolProperty(label, wxPG_LABEL, ptr.Get<epiBool>()); break;
    case epiMetaTypeID_epiFloat: prty = new wxFloatProperty(label, wxPG_LABEL, ptr.Get<epiFloat>()); break;
    case epiMetaTypeID_epiDouble: prty = new wxFloatProperty(label, wxPG_LABEL, ptr.Get<epiDouble>()); break;
    case epiMetaTypeID_epiByte: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiByte>()); break;
    case epiMetaTypeID_epiS8: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS8>()); break;
    case epiMetaTypeID_epiS16: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS16>()); break;
    case epiMetaTypeID_epiS32: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS32>()); break;
    case epiMetaTypeID_epiS64: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS64>()); break;
    case epiMetaTypeID_epiSize_t: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiSize_t>()); break;
    case epiMetaTypeID_epiU8: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU8>()); break;
    case epiMetaTypeID_epiU16: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU16>()); break;
    case epiMetaTypeID_epiU32: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU32>()); break;
    case epiMetaTypeID_epiU64: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU64>()); break;
    default: epiAssert(false, "Unhandled case");
    }

    AddProperty(ptr, prty, parentPrty, editable);
}

void epiWXPropertyGrid::AddString(PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable)
{
    epiAssert(MetaType::IsString(ptr.GetTypeID()));

    wxPGProperty* prty = nullptr;
    switch (ptr.GetTypeID())
    {
    case epiMetaTypeID_epiString: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiString>()); break;
    case epiMetaTypeID_epiWString: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiWString>()); break;
    default: epiAssert(false, "Unhandled case");
    }

    AddProperty(ptr, prty, parentPrty, editable);
}

void epiWXPropertyGrid::AddProperty(PropertyPointer& ptr, wxPGProperty* prty, wxPGProperty* parentPrty, epiBool editable)
{
    prty = parentPrty != nullptr ? parentPrty->AppendChild(prty) : Append(prty);
    prty->Enable(editable ? parentPrty->IsEnabled() : false);
    prty->SetClientData(&ptr);
}

void epiWXPropertyGrid::OnPropertyGridChanged(wxPropertyGridEvent& event)
{
    wxPGProperty* property = event.GetProperty();
    if (property == nullptr)
    {
        return;
    }

    void* clientData = property->GetClientData();
    PropertyPointer* ptr = reinterpret_cast<PropertyPointer*>(clientData);

    if (MetaType::IsFundamental(ptr->GetTypeID()))
    {
        const wxVariant value = property->GetValue();
        switch (ptr->GetTypeID())
        {
        case epiMetaTypeID_epiChar: ptr->Set<epiChar>(static_cast<epiChar>(value.GetChar())); break;
        case epiMetaTypeID_epiWChar: ptr->Set<epiWChar>(static_cast<epiWChar>(value.GetChar())); break;
        case epiMetaTypeID_epiBool: ptr->Set<epiBool>(value.GetBool()); break;
        case epiMetaTypeID_epiFloat: ptr->Set<epiFloat>(value.GetDouble()); break;
        case epiMetaTypeID_epiDouble: ptr->Set<epiDouble>(value.GetDouble()); break;
        case epiMetaTypeID_epiByte: ptr->Set<epiByte>(value.GetLongLong().GetValue()); break;
        case epiMetaTypeID_epiS8: ptr->Set<epiS8>(value.GetLongLong().GetValue()); break;
        case epiMetaTypeID_epiS16: ptr->Set<epiS16>(value.GetLongLong().GetValue()); break;
        case epiMetaTypeID_epiS32: ptr->Set<epiS32>(value.GetLongLong().GetValue()); break;
        case epiMetaTypeID_epiS64: ptr->Set<epiS64>(value.GetLongLong().GetValue()); break;
        case epiMetaTypeID_epiSize_t: ptr->Set<epiSize_t>(value.GetULongLong().GetValue()); break;
        case epiMetaTypeID_epiU8: ptr->Set<epiU8>(value.GetULongLong().GetValue()); break;
        case epiMetaTypeID_epiU16: ptr->Set<epiU16>(value.GetULongLong().GetValue()); break;
        case epiMetaTypeID_epiU32: ptr->Set<epiU32>(value.GetULongLong().GetValue()); break;
        case epiMetaTypeID_epiU64: ptr->Set<epiU64>(value.GetULongLong().GetValue()); break;
        default: epiAssert(false, "Unhandled case");
        }
    }
    else
    {
        epiAssert(false, "Unhandled case");
    }
}

void epiWXPropertyGrid::OnPropertyGridRightClick(wxPropertyGridEvent& event)
{
    wxPGProperty* property = event.GetProperty();
    if (property == nullptr)
    {
        return;
    }

    void* clientData = property->GetClientData();
    PropertyPointer* ptr = reinterpret_cast<PropertyPointer*>(clientData);
    if (ptr->GetTypeID() != epiMetaTypeID_epiFloat)
    {
        wxMessageBox(wxT("Only real number property could be chosen!"), wxT("Error"));
        return;
    }
}
