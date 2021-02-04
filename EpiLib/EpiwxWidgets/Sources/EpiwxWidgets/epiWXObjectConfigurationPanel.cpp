#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"

#include "EpiwxWidgets/epiWXSlider.h"
#include "EpiwxWidgets/epiWXSliderRange.h"

#include "EpiCore/ObjectModel/Property/epiPropertyPointer.h"

#include "EpiUI/ViewModel/uiVMPropertyCheckboxBoolean.h"
#include "EpiUI/ViewModel/uiVMPropertySliderFloating.h"
#include "EpiUI/ViewModel/uiVMPropertySliderIntegralSigned.h"
#include "EpiUI/ViewModel/uiVMPropertySliderIntegralUnsigned.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/checkbox.h>

epiWXObjectConfigurationPanel::epiWXObjectConfigurationPanel(epi::epiIPropertyChangedHandler& dataContext,
                                                             epi::epiArray<std::unique_ptr<epi::uiVMPropertyBase>>&& vmList, // TODO: ensure lifetime // TODO: use epiPtrArray
                                                             wxWindow* parent,
                                                             wxWindowID id,
                                                             const wxPoint& pos,
                                                             const wxSize& size,
                                                             long style,
                                                             const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
    , m_DataContext{dataContext}
    , m_VMList{std::move(vmList)}
{
    wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 30, 20);

    for (const auto& vm : m_VMList)
    {
        if (!vm)
        {
            continue;
        }

        if (wxWindow* control = MakeControlFromPropertyVM(*vm); control != nullptr)
        {
            const epi::epiPropertyPointer& ptr = vm->GetPrtyPtr();
            m_DataContext.PropertyChangedTriggerCallbacks(ptr.GetPID());

            sizer->Add(new wxStaticText(this, wxID_ANY, ptr.GetPropertyName()), wxSizerFlags().Right().Expand().CentreVertical().Proportion(1));
            sizer->Add(control, wxSizerFlags().Expand().CenterVertical().Proportion(2));
        }
    }

    wxBoxSizer* vboxSizer = new wxBoxSizer(wxVERTICAL);
    vboxSizer->Add(sizer, 1, wxALL | wxEXPAND, 20);

    SetSizerAndFit(vboxSizer);
}

wxWindow* epiWXObjectConfigurationPanel::MakeControlFromPropertyVM(epi::uiVMPropertyBase& vm)
{
    wxWindow* control = nullptr;

    const epi::epiPropertyPointer& ptr = vm.GetPrtyPtr();
    if (epi::uiVMPropertyCheckboxBoolean* checkboxVM = epi::epiAs<epi::uiVMPropertyCheckboxBoolean>(&vm))
    {
        wxCheckBox* checkbox = new wxCheckBox(this, wxID_ANY, wxEmptyString);

        // TODO: adjust for a specific type
        checkbox->Bind(wxEVT_CHECKBOX, &epiWXObjectConfigurationPanel::OnCheckboxValueChanged, this); // TODO: figure out whether it should be unbonded
        checkbox->SetClientData(checkboxVM);

        m_DataContext.PropertyChangedRegister(ptr.GetPID(), [checkbox]()
        {
            if (epi::uiVMPropertyCheckboxBoolean* checkboxVM = static_cast<epi::uiVMPropertyCheckboxBoolean*>(checkbox->GetClientData()))
            {
                checkbox->SetValue(checkboxVM->GetValue());
                checkbox->Refresh();
            }
        });

        control = checkbox;
    }
    else if (epi::uiVMPropertySlider* sliderVM = epi::epiAs<epi::uiVMPropertySlider>(&vm))
    {
        // TODO: add hint to the user for a most popular values (for example, a median filter is good in range 3..7)

        epiWXSliderBase* slider = nullptr;
        if (epi::uiVMPropertySliderFloating* sliderFloatingVM = epi::epiAs<epi::uiVMPropertySliderFloating>(&vm))
        {
            switch (ptr.GetTypeID())
            {
            case epi::epiMetaTypeID_epiFloat:
            {
                slider = new epiWXSlider<epiFloat>(this,
                                                   wxID_ANY,
                                                   ptr,
                                                   static_cast<epiFloat>(sliderFloatingVM->GetMinValue()),
                                                   static_cast<epiFloat>(sliderFloatingVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiDouble:
            {
                slider = new epiWXSlider<epiDouble>(this,
                                                    wxID_ANY,
                                                    ptr,
                                                    static_cast<epiDouble>(sliderFloatingVM->GetMinValue()),
                                                    static_cast<epiDouble>(sliderFloatingVM->GetMaxValue()));
            } break;
            default: epiAssert(!"Unexpected type id!");
            }
        }
        else if (epi::uiVMPropertySliderIntegralSigned* sliderIntegralSignedVM = epi::epiAs<epi::uiVMPropertySliderIntegralSigned>(&vm))
        {
            switch (ptr.GetTypeID())
            {
            case epi::epiMetaTypeID_epiS8:
            {
                slider = new epiWXSlider<epiS8>(this,
                                                wxID_ANY,
                                                ptr,
                                                static_cast<epiS8>(sliderIntegralSignedVM->GetMinValue()),
                                                static_cast<epiS8>(sliderIntegralSignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiS16:
            {
                slider = new epiWXSlider<epiS16>(this,
                                                 wxID_ANY,
                                                 ptr,
                                                 static_cast<epiS16>(sliderIntegralSignedVM->GetMinValue()),
                                                 static_cast<epiS16>(sliderIntegralSignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiS32:
            {
                slider = new epiWXSlider<epiS32>(this,
                                                 wxID_ANY,
                                                 ptr,
                                                 static_cast<epiS32>(sliderIntegralSignedVM->GetMinValue()),
                                                 static_cast<epiS32>(sliderIntegralSignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiS64:
            {
                slider = new epiWXSlider<epiS64>(this,
                                                 wxID_ANY,
                                                 ptr,
                                                 static_cast<epiS64>(sliderIntegralSignedVM->GetMinValue()),
                                                 static_cast<epiS64>(sliderIntegralSignedVM->GetMaxValue()));
            } break;
            default: epiAssert(!"Unexpected type id!");
            }
        }
        else if (epi::uiVMPropertySliderIntegralUnsigned* sliderIntegralUnsignedVM = epi::epiAs<epi::uiVMPropertySliderIntegralUnsigned>(&vm))
        {
            switch (ptr.GetTypeID())
            {
            case epi::epiMetaTypeID_epiByte:
            {
                slider = new epiWXSlider<epiByte>(this,
                                                  wxID_ANY,
                                                  ptr,
                                                  static_cast<epiByte>(sliderIntegralUnsignedVM->GetMinValue()),
                                                  static_cast<epiByte>(sliderIntegralUnsignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiU8:
            {
                slider = new epiWXSlider<epiU8>(this,
                                                wxID_ANY,
                                                ptr,
                                                static_cast<epiU8>(sliderIntegralUnsignedVM->GetMinValue()),
                                                static_cast<epiU8>(sliderIntegralUnsignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiU16:
            {
                slider = new epiWXSlider<epiU16>(this,
                                                 wxID_ANY,
                                                 ptr,
                                                 static_cast<epiU16>(sliderIntegralUnsignedVM->GetMinValue()),
                                                 static_cast<epiU16>(sliderIntegralUnsignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiU32:
            {
                slider = new epiWXSlider<epiU32>(this,
                                                 wxID_ANY,
                                                 ptr,
                                                 static_cast<epiU32>(sliderIntegralUnsignedVM->GetMinValue()),
                                                 static_cast<epiU32>(sliderIntegralUnsignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiU64:
            {
                slider = new epiWXSlider<epiU64>(this,
                                                 wxID_ANY,
                                                 ptr,
                                                 static_cast<epiU64>(sliderIntegralUnsignedVM->GetMinValue()),
                                                 static_cast<epiU64>(sliderIntegralUnsignedVM->GetMaxValue()));
            } break;
            case epi::epiMetaTypeID_epiSize_t:
            {
                slider = new epiWXSlider<epiSize_t>(this,
                                                    wxID_ANY,
                                                    ptr,
                                                    static_cast<epiSize_t>(sliderIntegralUnsignedVM->GetMinValue()),
                                                    static_cast<epiSize_t>(sliderIntegralUnsignedVM->GetMaxValue()));
            } break;
            default: epiAssert(!"Unexpected type id!");
            }
        }

        m_DataContext.PropertyChangedRegister(ptr.GetPID(), [slider]()
        {
            slider->RefreshValue();
        });

        control = slider;
    }
    else
    {
        epiLogError("Unhandled VM type=`{}`", vm.GetMetaClass().GetName());
    }
#if 0
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
#endif

    return control;
}

void epiWXObjectConfigurationPanel::OnCheckboxValueChanged(wxCommandEvent& event)
{
    const wxCheckBox* checkbox = static_cast<const wxCheckBox*>(event.GetEventObject());
    if (epi::uiVMPropertyCheckboxBoolean* checkboxVM = static_cast<epi::uiVMPropertyCheckboxBoolean*>(checkbox->GetClientData()))
    {
        checkboxVM->SetValue(checkbox->GetValue());
    }
}
