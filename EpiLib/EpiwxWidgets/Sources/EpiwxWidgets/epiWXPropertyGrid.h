#pragma once

#include <wx/propgrid/propgrid.h>

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/PropertyPointer.h"

class epiWXPlot;
class epiWXPropertyGrid : public wxPropertyGrid
{
public:
    wxDECLARE_EVENT_TABLE();

public:
    epiWXPropertyGrid(wxWindow* parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize,
                      long style = 0,
                      const wxString& name = wxPropertyGridNameStr);

    void SetObject(epi::Object& object);
    void Clear() override;

    virtual void OnPropertyRightClick(epi::PropertyPointer& ptr) {}

protected:
    void FillCompound(epi::Object& object, wxPGProperty* parentPrty);
    void FillMultiDimensional(epi::epiBaseArray& array, epi::epiMetaTypeID nestedTypeID, wxPGProperty* parentPrty);
    void FillMultiDimensionalPtr(epi::epiBaseArray& array, epi::epiMetaTypeID nestedTypeID, wxPGProperty* parentPrty);

    template<typename T, typename Nested>
    void FillMultiDimensionalInplace(T& inplace, wxPGProperty* parentPrty);

    void FillProperties(epi::Object& object, const epi::MetaClassData& meta, wxPGProperty* parentPrty);

    void AddFundamental(epi::PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable);
    void AddString(epi::PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable);
    void AddProperty(epi::PropertyPointer& ptr, wxPGProperty* prty, wxPGProperty* parentPrty, epiBool editable);

    void OnPropertyGridChanged(wxPropertyGridEvent& event);
    void OnPropertyGridRightClick(wxPropertyGridEvent& event);

protected:
    std::vector<epi::PropertyPointer*> m_PropertyPointers;
};

template<typename T, typename Nested>
void epiWXPropertyGrid::FillMultiDimensionalInplace(T& inplace, wxPGProperty* parentPrty)
{
    constexpr size_t size = sizeof(T) / sizeof(Nested);
    epiAssertStatic(size > 1);

    for (epiU32 i = 0; i < size; ++i)
    {
        const epiString label = fmt::format("[{:d}]", i);

        PropertyPointer* ptr = new PropertyPointer();
        *ptr = PropertyPointer::CreateFromArrayInplace<T, Nested>(inplace, i);

        if constexpr (MetaType::IsFundamental<Nested>())
        {
            AddFundamental(*ptr, label.c_str(), parentPrty, true);
        }
        else if constexpr (MetaType::IsString<Nested>())
        {
            AddString(*ptr, label.c_str(), parentPrty, true);
        }
        else if constexpr (MetaType::IsCompound<Nested>())
        {
            Object& obj = ptr->Get<Object>();
            wxPGProperty* prty = new wxStringProperty(label.c_str(), wxPG_LABEL, obj.ToString().c_str());
            AddProperty(*ptr, prty, parentPrty, true);

            FillCompound(obj, prty);
        }
        else
        {
            epiAssertStatic(false, "Unhandled case");
        }

        // TODO: replace unique_ptr with plain type
        // PROBLEM: property's client data dangling pointer
        m_PropertyPointers.push_back(ptr);
    }
}
