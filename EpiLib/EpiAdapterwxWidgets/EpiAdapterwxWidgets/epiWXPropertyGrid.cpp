#include "EpiAdapterwxWidgets/pch.h"
#include "epiWXPropertyGrid.h"

#include "EpiCore/ObjectModel/PropertyPointer.h"

using namespace epi;

wxBEGIN_EVENT_TABLE(epiWXPropertyGrid, wxPropertyGrid)
    EVT_PG_CHANGED(-1, epiWXPropertyGrid::OnPropertyGridChanged)
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

            FillProperties(object, metaClassData, p);
        }

        epiAssert(MetaType::IsCompound(m->GetSuperTypeID()) || m->GetSuperTypeID() == MetaTypeID_epiNone);
        if (m->GetSuperTypeID() == MetaTypeID_epiNone)
        {
            break;
        }
        m = ClassRegistry_Type_Lookup(m->GetSuperTypeID());
        epiAssert(m);
    } while (true);
}

void epiWXPropertyGrid::FillMultiDimensional(epiBaseArray& array, MetaTypeID nestedTypeID, wxPGProperty* parentPrty)
{
    const epiSize_t arraySz = array.GetSize();
    for (epiU32 i = 0; i < arraySz; ++i)
    {
        const std::string label = fmt::format("[{:d}]", i);
        PropertyPointer ptr = PropertyPointer::CreateFromArray(array, nestedTypeID, i);

        if (MetaType::IsCompound(nestedTypeID))
        {
            Object& obj = ptr.Get<Object&>();
            wxPGProperty* prty = new wxStringProperty(label.c_str(), wxPG_LABEL, obj.ToString().c_str());
            AddProperty(prty, parentPrty, true);

            FillCompound(obj, prty);
        }
        else if (MetaType::IsString(nestedTypeID))
        {
            AddString(ptr, label.c_str(), parentPrty, true);
        }
        else if (MetaType::IsFundamental(nestedTypeID))
        {
            AddFundamental(ptr, label.c_str(), parentPrty, true);
        }
        else
        {
            epiAssert(false, "Unhandled case");
        }
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
        PropertyPointer ptr = PropertyPointer::CreateFromProperty(object, property);

        if (MetaType::IsCompound(property->GetTypeID()))
        {
            wxPGProperty* prty = new wxStringProperty(label, wxPG_LABEL, "");
            AddProperty(prty, parentPrty, editable);

            FillCompound(ptr.Get<Object&>(), prty);
        }
        else if (MetaType::IsMultiDimensional(property->GetTypeID()))
        {
            wxPGProperty* prty = new wxStringProperty(property->GetName(), wxPG_LABEL, "<Array>");
            AddProperty(prty, parentPrty, editable);

            FillMultiDimensional(ptr.Get<epiBaseArray&>(), property->GetNestedTypeID(), prty);
        }
        else if (MetaType::IsFundamental(property->GetTypeID()))
        {
            AddFundamental(ptr, label, parentPrty, editable);
        }
        else if (MetaType::IsString(property->GetTypeID()))
        {
            AddString(ptr, label, parentPrty, editable);
        }
        else
        {
            epiAssert(false, "Unhandled case");
        }
    }
}

void epiWXPropertyGrid::AddFundamental(PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable)
{
    epiAssert(MetaType::IsFundamental(ptr.GetTypeID()));

    wxPGProperty* prty = nullptr;
    switch (ptr.GetTypeID())
    {
    case MetaTypeID_epiChar: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiChar>()); break;
    case MetaTypeID_epiWChar: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiWChar>()); break;
    case MetaTypeID_epiBool: prty = new wxBoolProperty(label, wxPG_LABEL, ptr.Get<epiBool>()); break;
    case MetaTypeID_epiFloat: prty = new wxFloatProperty(label, wxPG_LABEL, ptr.Get<epiFloat>()); break;
    case MetaTypeID_epiDouble: prty = new wxFloatProperty(label, wxPG_LABEL, ptr.Get<epiDouble>()); break;
    case MetaTypeID_epiByte: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiByte>()); break;
    case MetaTypeID_epiS8: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS8>()); break;
    case MetaTypeID_epiS16: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS16>()); break;
    case MetaTypeID_epiS32: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS32>()); break;
    case MetaTypeID_epiS64: prty = new wxIntProperty(label, wxPG_LABEL, ptr.Get<epiS64>()); break;
    case MetaTypeID_epiSize_t: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiSize_t>()); break;
    case MetaTypeID_epiU8: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU8>()); break;
    case MetaTypeID_epiU16: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU16>()); break;
    case MetaTypeID_epiU32: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU32>()); break;
    case MetaTypeID_epiU64: prty = new wxUIntProperty(label, wxPG_LABEL, ptr.Get<epiU64>()); break;
    default: epiAssert(false, "Unhanled case");
    }

    AddProperty(prty, parentPrty, editable);
}

void epiWXPropertyGrid::AddString(PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable)
{
    epiAssert(MetaType::IsString(ptr.GetTypeID()));

    wxPGProperty* prty = nullptr;
    switch (ptr.GetTypeID())
    {
    case MetaTypeID_epiString: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiString&>()); break;
    case MetaTypeID_epiWString: prty = new wxStringProperty(label, wxPG_LABEL, ptr.Get<epiWString&>()); break;
    default: epiAssert(false, "Unhanled case");
    }

    AddProperty(prty, parentPrty, editable);
}

void epiWXPropertyGrid::OnPropertyGridChanged(wxPropertyGridEvent& event)
{
    wxPGProperty* property = event.GetProperty();
    if (property == nullptr)
    {
        return;
    }

    wxVariant value = property->GetValue();
    if (value.IsNull())
    {
        return;
    }
}

void epiWXPropertyGrid::AddProperty(wxPGProperty* prty, wxPGProperty* parentPrty, epiBool editable)
{
    prty = parentPrty != nullptr ? parentPrty->AppendChild(prty) : Append(prty);
    prty->Enable(editable ? parentPrty->IsEnabled() : false);
}
