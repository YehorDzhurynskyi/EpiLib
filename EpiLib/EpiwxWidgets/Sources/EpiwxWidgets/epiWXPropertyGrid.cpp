#include "EpiwxWidgets/epiWXPropertyGrid.h"

#include <wx/wx.h>

#include <fmt/core.h>

EPI_NAMESPACE_USING()

wxBEGIN_EVENT_TABLE(epiWXPropertyGrid, wxPropertyGrid)
    EVT_PG_CHANGED(wxID_ANY, epiWXPropertyGrid::OnPropertyGridChanged)
    EVT_PG_RIGHT_CLICK(wxID_ANY, epiWXPropertyGrid::OnPropertyGridRightClick)
wxEND_EVENT_TABLE()

epiWXPropertyGrid::epiWXPropertyGrid(wxWindow* parent,
                                     wxWindowID id,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxString& name)
    : wxPropertyGrid(parent, id, pos, size, style, name)
{
    SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);
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
            p->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_READONLY, true);

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
    // TODO: add the ability to upload another `n` items with Property Grid UI
    const epiSize_t arraySz = std::min(100ull, array.GetSize());
    for (epiU32 i = 0; i < arraySz; ++i)
    {
        const epiString label = fmt::format("[{:d}]", i);

        PropertyPointer* ptr = new PropertyPointer();
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
    // TODO: add the ability to upload another `n` items with Property Grid UI
    const epiSize_t arraySz = std::min(100ull, array.GetSize());
    for (epiU32 i = 0; i < arraySz; ++i)
    {
        const epiString label = fmt::format("[{:d}]", i);

        PropertyPointer* ptr = new PropertyPointer();
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

        PropertyPointer* ptr = new PropertyPointer();
        *ptr = PropertyPointer::CreateFromProperty(object, property);

        if (MetaType::IsFundamental(property->GetTypeID()))
        {
            AddFundamental(*ptr, label, parentPrty, editable);
        }
        else if (MetaType::IsString(property->GetTypeID()))
        {
            AddString(*ptr, label, parentPrty, editable);
        }
        else if (MetaType::IsMultiDimensionalInplace(property->GetTypeID()))
        {
            wxPGProperty* prty = new wxStringProperty(property->GetName(), wxPG_LABEL);
            AddProperty(*ptr, prty, parentPrty, editable);

            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_NOEDITOR, true);
            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_READONLY, true);
            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_DISABLED, true);
            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_COLLAPSED, true);

            switch (property->GetTypeID())
            {
            case epiMetaTypeID_epiSize2: FillMultiDimensionalInplace<epiSize2, epiSize2::value_type>(ptr->Get<epiSize2>(), prty); break;
            case epiMetaTypeID_epiSize2f: FillMultiDimensionalInplace<epiSize2f, epiSize2f::value_type>(ptr->Get<epiSize2f>(), prty); break;
            case epiMetaTypeID_epiSize2d: FillMultiDimensionalInplace<epiSize2d, epiSize2d::value_type>(ptr->Get<epiSize2d>(), prty); break;
            case epiMetaTypeID_epiSize2s: FillMultiDimensionalInplace<epiSize2s, epiSize2s::value_type>(ptr->Get<epiSize2s>(), prty); break;
            case epiMetaTypeID_epiSize2u: FillMultiDimensionalInplace<epiSize2u, epiSize2u::value_type>(ptr->Get<epiSize2u>(), prty); break;
            case epiMetaTypeID_epiVec2f: FillMultiDimensionalInplace<epiVec2f, epiVec2f::value_type>(ptr->Get<epiVec2f>(), prty); break;
            case epiMetaTypeID_epiVec2d: FillMultiDimensionalInplace<epiVec2d, epiVec2d::value_type>(ptr->Get<epiVec2d>(), prty); break;
            case epiMetaTypeID_epiVec2s: FillMultiDimensionalInplace<epiVec2s, epiVec2s::value_type>(ptr->Get<epiVec2s>(), prty); break;
            case epiMetaTypeID_epiVec2s8: FillMultiDimensionalInplace<epiVec2s8, epiVec2s8::value_type>(ptr->Get<epiVec2s8>(), prty); break;
            case epiMetaTypeID_epiVec2s16: FillMultiDimensionalInplace<epiVec2s16, epiVec2s16::value_type>(ptr->Get<epiVec2s16>(), prty); break;
            case epiMetaTypeID_epiVec2s32: FillMultiDimensionalInplace<epiVec2s32, epiVec2s32::value_type>(ptr->Get<epiVec2s32>(), prty); break;
            case epiMetaTypeID_epiVec2s64: FillMultiDimensionalInplace<epiVec2s64, epiVec2s64::value_type>(ptr->Get<epiVec2s64>(), prty); break;
            case epiMetaTypeID_epiVec2u: FillMultiDimensionalInplace<epiVec2u, epiVec2u::value_type>(ptr->Get<epiVec2u>(), prty); break;
            case epiMetaTypeID_epiVec2u8: FillMultiDimensionalInplace<epiVec2u8, epiVec2u8::value_type>(ptr->Get<epiVec2u8>(), prty); break;
            case epiMetaTypeID_epiVec2u16: FillMultiDimensionalInplace<epiVec2u16, epiVec2u16::value_type>(ptr->Get<epiVec2u16>(), prty); break;
            case epiMetaTypeID_epiVec2u32: FillMultiDimensionalInplace<epiVec2u32, epiVec2u32::value_type>(ptr->Get<epiVec2u32>(), prty); break;
            case epiMetaTypeID_epiVec2u64: FillMultiDimensionalInplace<epiVec2u64, epiVec2u64::value_type>(ptr->Get<epiVec2u64>(), prty); break;
            case epiMetaTypeID_epiVec3f: FillMultiDimensionalInplace<epiVec3f, epiVec3f::value_type>(ptr->Get<epiVec3f>(), prty); break;
            case epiMetaTypeID_epiVec3d: FillMultiDimensionalInplace<epiVec3d, epiVec3d::value_type>(ptr->Get<epiVec3d>(), prty); break;
            case epiMetaTypeID_epiVec3s: FillMultiDimensionalInplace<epiVec3s, epiVec3s::value_type>(ptr->Get<epiVec3s>(), prty); break;
            case epiMetaTypeID_epiVec3s8: FillMultiDimensionalInplace<epiVec3s8, epiVec3s8::value_type>(ptr->Get<epiVec3s8>(), prty); break;
            case epiMetaTypeID_epiVec3s16: FillMultiDimensionalInplace<epiVec3s16, epiVec3s16::value_type>(ptr->Get<epiVec3s16>(), prty); break;
            case epiMetaTypeID_epiVec3s32: FillMultiDimensionalInplace<epiVec3s32, epiVec3s32::value_type>(ptr->Get<epiVec3s32>(), prty); break;
            case epiMetaTypeID_epiVec3s64: FillMultiDimensionalInplace<epiVec3s64, epiVec3s64::value_type>(ptr->Get<epiVec3s64>(), prty); break;
            case epiMetaTypeID_epiVec3u: FillMultiDimensionalInplace<epiVec3u, epiVec3u::value_type>(ptr->Get<epiVec3u>(), prty); break;
            case epiMetaTypeID_epiVec3u8: FillMultiDimensionalInplace<epiVec3u8, epiVec3u8::value_type>(ptr->Get<epiVec3u8>(), prty); break;
            case epiMetaTypeID_epiVec3u16: FillMultiDimensionalInplace<epiVec3u16, epiVec3u16::value_type>(ptr->Get<epiVec3u16>(), prty); break;
            case epiMetaTypeID_epiVec3u32: FillMultiDimensionalInplace<epiVec3u32, epiVec3u32::value_type>(ptr->Get<epiVec3u32>(), prty); break;
            case epiMetaTypeID_epiVec3u64: FillMultiDimensionalInplace<epiVec3u64, epiVec3u64::value_type>(ptr->Get<epiVec3u64>(), prty); break;
            case epiMetaTypeID_epiVec4f: FillMultiDimensionalInplace<epiVec4f, epiVec4f::value_type>(ptr->Get<epiVec4f>(), prty); break;
            case epiMetaTypeID_epiVec4d: FillMultiDimensionalInplace<epiVec4d, epiVec4d::value_type>(ptr->Get<epiVec4d>(), prty); break;
            case epiMetaTypeID_epiVec4s: FillMultiDimensionalInplace<epiVec4s, epiVec4s::value_type>(ptr->Get<epiVec4s>(), prty); break;
            case epiMetaTypeID_epiVec4s8: FillMultiDimensionalInplace<epiVec4s8, epiVec4s8::value_type>(ptr->Get<epiVec4s8>(), prty); break;
            case epiMetaTypeID_epiVec4s16: FillMultiDimensionalInplace<epiVec4s16, epiVec4s16::value_type>(ptr->Get<epiVec4s16>(), prty); break;
            case epiMetaTypeID_epiVec4s32: FillMultiDimensionalInplace<epiVec4s32, epiVec4s32::value_type>(ptr->Get<epiVec4s32>(), prty); break;
            case epiMetaTypeID_epiVec4s64: FillMultiDimensionalInplace<epiVec4s64, epiVec4s64::value_type>(ptr->Get<epiVec4s64>(), prty); break;
            case epiMetaTypeID_epiVec4u: FillMultiDimensionalInplace<epiVec4u, epiVec4u::value_type>(ptr->Get<epiVec4u>(), prty); break;
            case epiMetaTypeID_epiVec4u8: FillMultiDimensionalInplace<epiVec4u8, epiVec4u8::value_type>(ptr->Get<epiVec4u8>(), prty); break;
            case epiMetaTypeID_epiVec4u16: FillMultiDimensionalInplace<epiVec4u16, epiVec4u16::value_type>(ptr->Get<epiVec4u16>(), prty); break;
            case epiMetaTypeID_epiVec4u32: FillMultiDimensionalInplace<epiVec4u32, epiVec4u32::value_type>(ptr->Get<epiVec4u32>(), prty); break;
            case epiMetaTypeID_epiVec4u64: FillMultiDimensionalInplace<epiVec4u64, epiVec4u64::value_type>(ptr->Get<epiVec4u64>(), prty); break;
            case epiMetaTypeID_epiMat2x2f: FillMultiDimensionalInplace<epiMat2x2f, epiMat2x2f::value_type>(ptr->Get<epiMat2x2f>(), prty); break;
            case epiMetaTypeID_epiMat3x3f: FillMultiDimensionalInplace<epiMat3x3f, epiMat3x3f::value_type>(ptr->Get<epiMat3x3f>(), prty); break;
            case epiMetaTypeID_epiMat4x4f: FillMultiDimensionalInplace<epiMat4x4f, epiMat4x4f::value_type>(ptr->Get<epiMat4x4f>(), prty); break;
            case epiMetaTypeID_epiComplexf: FillMultiDimensionalInplace<epiComplexf, epiComplexf::value_type>(ptr->Get<epiComplexf>(), prty); break;
            case epiMetaTypeID_epiComplexd: FillMultiDimensionalInplace<epiComplexd, epiComplexd::value_type>(ptr->Get<epiComplexd>(), prty); break;
            case epiMetaTypeID_epiRect2f: FillMultiDimensionalInplace<epiRect2f, epiRect2f::value_type>(ptr->Get<epiRect2f>(), prty); break;
            case epiMetaTypeID_epiRect2d: FillMultiDimensionalInplace<epiRect2d, epiRect2d::value_type>(ptr->Get<epiRect2d>(), prty); break;
            case epiMetaTypeID_epiRect2s: FillMultiDimensionalInplace<epiRect2s, epiRect2s::value_type>(ptr->Get<epiRect2s>(), prty); break;
            case epiMetaTypeID_epiRect2u: FillMultiDimensionalInplace<epiRect2u, epiRect2u::value_type>(ptr->Get<epiRect2u>(), prty); break;
            default: epiAssert(false, "Unhandled case!");
            }
        }
        else if (MetaType::IsMultiDimensional(property->GetTypeID()))
        {
            epiBaseArray& array = ptr->Get<epiBaseArray>();

            wxPGProperty* prty = new wxStringProperty(property->GetName(), wxPG_LABEL, fmt::format("<Array> size={:d}", array.GetSize()));
            AddProperty(*ptr, prty, parentPrty, editable);

            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_NOEDITOR, true);
            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_READONLY, true);
            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_DISABLED, true);
            prty->ChangeFlag(wxPGPropertyFlags::wxPG_PROP_COLLAPSED, true);

            if (property->GetTypeID() == epiMetaTypeID_epiArray)
            {
                FillMultiDimensional(array, property->GetNestedTypeID(), prty);
            }
            else if (property->GetTypeID() == epiMetaTypeID_epiPtrArray)
            {
                FillMultiDimensionalPtr(array, property->GetNestedTypeID(), prty);
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

    if (PropertyPointer* ptr = reinterpret_cast<PropertyPointer*>(property->GetClientData()))
    {
        OnPropertyRightClick(*ptr);
    }
}
