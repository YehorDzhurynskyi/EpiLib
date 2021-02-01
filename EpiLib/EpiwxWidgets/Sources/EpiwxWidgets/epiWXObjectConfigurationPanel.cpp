#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"

#include "EpiwxWidgets/epiWXSlider.h"
#include "EpiwxWidgets/epiWXSliderRange.h"

#include "EpiCore/ObjectModel/PropertyPointer.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/checkbox.h>

epiWXObjectConfigurationPanel::epiWXObjectConfigurationPanel(epi::Object& object, // TODO: ensure lifetime
                                                             wxWindow* parent,
                                                             wxWindowID id,
                                                             const wxPoint& pos,
                                                             const wxSize& size,
                                                             long style,
                                                             const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
    , m_Object{object}
{
    wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 30, 20);

    // TODO: check whether interface is supported
    epi::epiIPropertyChangedHandler& propertyChangedHandler = dynamic_cast<epi::epiIPropertyChangedHandler&>(m_Object);

    const epi::MetaClass& meta = m_Object.GetMetaClass();
    const epi::MetaClassData& metaData = meta.GetClassData();
    for (const auto& prty : metaData)
    {
        if (wxWindow* control = MakeControlFromProperty(prty); control != nullptr)
        {
            propertyChangedHandler.PropertyChangedTriggerCallbacks(prty.GetPID());

            sizer->Add(new wxStaticText(this, wxID_ANY, prty.GetName()), wxSizerFlags().Right().Expand().CentreVertical().Proportion(1));
            sizer->Add(control, wxSizerFlags().Expand().CenterVertical().Proportion(2));
        }
    }

    wxBoxSizer* vboxSizer = new wxBoxSizer(wxVERTICAL);
    vboxSizer->Add(sizer, 1, wxALL | wxEXPAND, 20);

    SetSizerAndFit(vboxSizer);
}

wxWindow* epiWXObjectConfigurationPanel::MakeControlFromProperty(const epi::MetaProperty& prty)
{
    wxWindow* control = nullptr;

    // TODO: check whether interface is supported
    epi::epiIPropertyChangedHandler& propertyChangedHandler = dynamic_cast<epi::epiIPropertyChangedHandler&>(m_Object);

    const epi::epiMetaPropertyID prtyID = prty.GetPID();
    const epi::epiMetaTypeID typeID = prty.GetTypeID();
    if (typeID == epi::epiMetaTypeID_epiBool)
    {
        wxCheckBox* checkbox = new wxCheckBox(this, wxID_ANY, wxEmptyString);

        // TODO: adjust for a specific type
        checkbox->Bind(wxEVT_CHECKBOX, &epiWXObjectConfigurationPanel::OnCheckboxValueChanged, this); // TODO: figure out whether it should be unbonded

        // TODO: release memory
        epi::PropertyPointer* ptr = new epi::PropertyPointer(epi::PropertyPointer::CreateFromProperty(m_Object, &prty));
        checkbox->SetClientData(ptr);
        propertyChangedHandler.PropertyChangedRegister(prtyID, [this, checkbox]()
        {
            if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(checkbox->GetClientData()))
            {
                checkbox->SetValue(ptr->Get<epiBool>());
                checkbox->Refresh();
            }
        });

        control = checkbox;
    }
    else if (epi::MetaType::IsNumeric(typeID))
    {
        // TODO: add hint to the user for a most popular values (for example, a median filter is good in range 3..7)
        switch (typeID)
        {
        case epi::epiMetaTypeID_epiByte: control = MakeControlSlider<epiByte>(prty); break;
        case epi::epiMetaTypeID_epiFloat: control = MakeControlSlider<epiFloat>(prty); break;
        case epi::epiMetaTypeID_epiDouble: control = MakeControlSlider<epiDouble>(prty); break;
        case epi::epiMetaTypeID_epiSize_t: control = MakeControlSlider<epiSize_t>(prty); break;
        case epi::epiMetaTypeID_epiU8: control = MakeControlSlider<epiU8>(prty); break;
        case epi::epiMetaTypeID_epiU16: control = MakeControlSlider<epiU16>(prty); break;
        case epi::epiMetaTypeID_epiU32: control = MakeControlSlider<epiU32>(prty); break;
        case epi::epiMetaTypeID_epiU64: control = MakeControlSlider<epiU64>(prty); break;
        case epi::epiMetaTypeID_epiS8: control = MakeControlSlider<epiS8>(prty); break;
        case epi::epiMetaTypeID_epiS16: control = MakeControlSlider<epiS16>(prty); break;
        case epi::epiMetaTypeID_epiS32: control = MakeControlSlider<epiS32>(prty); break;
        case epi::epiMetaTypeID_epiS64: control = MakeControlSlider<epiS64>(prty); break;
        default: epiLogError("Unrecognized typeID=`{}`", typeID); break;
        }
    }
    else if (epi::MetaType::IsMultiDimensionalInplace(typeID))
    {
        switch (typeID)
        {
        case epi::epiMetaTypeID_epiSize2: control = MakeControlSliderRange<epiSize_t>(prty); break;
        case epi::epiMetaTypeID_epiSize2f: control = MakeControlSliderRange<epiFloat>(prty); break;
        case epi::epiMetaTypeID_epiSize2d: control = MakeControlSliderRange<epiDouble>(prty); break;
        case epi::epiMetaTypeID_epiSize2s: control = MakeControlSliderRange<epiS32>(prty); break;
        case epi::epiMetaTypeID_epiSize2u: control = MakeControlSliderRange<epiU32>(prty); break;
        case epi::epiMetaTypeID_epiVec2f: control = MakeControlSliderRange<epiFloat>(prty); break;
        case epi::epiMetaTypeID_epiVec2d: control = MakeControlSliderRange<epiDouble>(prty); break;
        case epi::epiMetaTypeID_epiVec2s: control = MakeControlSliderRange<epiS32>(prty); break;
        case epi::epiMetaTypeID_epiVec2s8: control = MakeControlSliderRange<epiS8>(prty); break;
        case epi::epiMetaTypeID_epiVec2s16: control = MakeControlSliderRange<epiS16>(prty); break;
        case epi::epiMetaTypeID_epiVec2s32: control = MakeControlSliderRange<epiS32>(prty); break;
        case epi::epiMetaTypeID_epiVec2s64: control = MakeControlSliderRange<epiS64>(prty); break;
        case epi::epiMetaTypeID_epiVec2u: control = MakeControlSliderRange<epiU32>(prty); break;
        case epi::epiMetaTypeID_epiVec2u8: control = MakeControlSliderRange<epiU8>(prty); break;
        case epi::epiMetaTypeID_epiVec2u16: control = MakeControlSliderRange<epiU16>(prty); break;
        case epi::epiMetaTypeID_epiVec2u32: control = MakeControlSliderRange<epiU32>(prty); break;
        case epi::epiMetaTypeID_epiVec2u64: control = MakeControlSliderRange<epiU64>(prty); break;
        default: epiLogError("Unrecognized typeID=`{}`", typeID); break;
        }
    }

    return control;
}

void epiWXObjectConfigurationPanel::OnCheckboxValueChanged(wxCommandEvent& event)
{
    const wxCheckBox* checkbox = static_cast<const wxCheckBox*>(event.GetEventObject());
    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(checkbox->GetClientData()))
    {
        ptr->Set<epiBool>(checkbox->GetValue());
    }
}
