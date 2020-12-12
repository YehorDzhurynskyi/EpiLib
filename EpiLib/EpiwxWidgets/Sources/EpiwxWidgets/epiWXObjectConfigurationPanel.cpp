#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"

#include "EpiwxWidgets/epiWXSliderRange.h"

#include "EpiCore/ObjectModel/PropertyPointer.h"
#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/checkbox.h>

wxDEFINE_EVENT(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED, wxCommandEvent);

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
        const epiHash_t prtyID = prty.GetPID();

        wxWindow* control = nullptr;
        if (epi::epiMetaTypeID typeID = prty.GetTypeID(); epi::MetaType::IsNumeric(typeID))
        {
            if (epi::MetaType::IsFloating(typeID))
            {
                wxSpinCtrlDouble* spin = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP);

                // TODO: adjust for a specific type
                spin->SetRange(std::numeric_limits<epiDouble>::min(), std::numeric_limits<epiDouble>::max());
                spin->SetIncrement(0.1);
                spin->Bind(wxEVT_SPINCTRLDOUBLE, &epiWXObjectConfigurationPanel::OnSpinDoubleValueChanged, this); // TODO: figure out whether it should be unbonded
                propertyChangedHandler.PropertyChangedRegister(prtyID, [this, spin]()
                {
                    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(spin->GetClientData()))
                    {
                        switch (ptr->GetTypeID())
                        {
                        case epi::epiMetaTypeID_epiFloat: spin->SetValue(ptr->Get<epiFloat>()); break;
                        case epi::epiMetaTypeID_epiDouble: spin->SetValue(ptr->Get<epiDouble>()); break;
                        default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
                        }

                        spin->Refresh();

                        QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
                    }
                });

                control = spin;
            }
            else if (epi::MetaType::IsNumeric(typeID))
            {
                // TODO: add hint to the user for a most popular values (for example, a median filter is good in range 3..7)
                epiS32 minValue = 0;
                epiS32 maxValue = 0;
                switch (typeID)
                {
                case epi::epiMetaTypeID_epiByte: minValue = std::numeric_limits<epiByte>::min(); maxValue = std::numeric_limits<epiByte>::max(); break;
                case epi::epiMetaTypeID_epiU8: minValue = std::numeric_limits<epiU8>::min(); maxValue = std::numeric_limits<epiU8>::max(); break;
                case epi::epiMetaTypeID_epiS8: minValue = std::numeric_limits<epiS8>::min(); maxValue = std::numeric_limits<epiS8>::max(); break;
                case epi::epiMetaTypeID_epiSize_t: minValue = std::numeric_limits<epiU8>::min(); maxValue = std::numeric_limits<epiU8>::max(); break;
                default: epiLogError("Unexpected typeID=`{}`", typeID); break;
                }

                wxSlider* slider = new wxSlider(this, wxID_ANY, 0, minValue, maxValue, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_AUTOTICKS | wxSL_LABELS);
                slider->Bind(wxEVT_SLIDER, &epiWXObjectConfigurationPanel::OnSliderValueChanged, this); // TODO: figure out whether it should be unbonded
                propertyChangedHandler.PropertyChangedRegister(prtyID, [this, slider]()
                {
                    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(slider->GetClientData()))
                    {
                        switch (ptr->GetTypeID())
                        {
                        case epi::epiMetaTypeID_epiByte: slider->SetValue(ptr->Get<epiByte>()); break;
                        case epi::epiMetaTypeID_epiU8: slider->SetValue(ptr->Get<epiU8>()); break;
                        case epi::epiMetaTypeID_epiS8: slider->SetValue(ptr->Get<epiS8>()); break;
                        case epi::epiMetaTypeID_epiSize_t: slider->SetValue(ptr->Get<epiSize_t>()); break;
                        default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
                        }

                        slider->Refresh();

                        QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
                    }
                });

                control = slider;
            }
            else
            {
                wxSpinCtrl* spin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP);

                // TODO: adjust for a specific type
                spin->SetRange(std::numeric_limits<epiS32>::min(), std::numeric_limits<epiS32>::max());
                spin->Bind(wxEVT_SPINCTRL, &epiWXObjectConfigurationPanel::OnSpinValueChanged, this); // TODO: figure out whether it should be unbonded
                spin->Bind(wxEVT_TEXT, &epiWXObjectConfigurationPanel::OnSpinTextValueChanged, this); // TODO: figure out whether it should be unbonded

                control = spin;
            }
        }
        else if (typeID == epi::epiMetaTypeID_epiVec2s8 || typeID == epi::epiMetaTypeID_epiVec2u8) // TODO: implement other types
        {
            epiS32 minValue = 0;
            epiS32 maxValue = 0;
            switch (typeID)
            {
            case epi::epiMetaTypeID_epiVec2s8: minValue = std::numeric_limits<epiS8>::min(); maxValue = std::numeric_limits<epiS8>::max(); break;
            case epi::epiMetaTypeID_epiVec2u8: minValue = std::numeric_limits<epiU8>::min(); maxValue = std::numeric_limits<epiU8>::max(); break;
            default: epiLogError("Unexpected typeID=`{}`", typeID); break;
            }

            epiWXSliderRange* slider = new epiWXSliderRange(this, wxID_ANY, 0, 0, minValue, maxValue);
            slider->Bind(wxEVT_SLIDER, &epiWXObjectConfigurationPanel::OnSliderRangeValueChanged, this); // TODO: figure out whether it should be unbonded
            propertyChangedHandler.PropertyChangedRegister(prtyID, [this, slider]()
            {
                if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(slider->GetClientData()))
                {
                    switch (ptr->GetTypeID())
                    {
                    case epi::epiMetaTypeID_epiVec2s8:
                    {
                        epiVec2s8 value = ptr->Get<epiVec2s8>();
                        slider->SetValueLower(value.x);
                        slider->SetValueUpper(value.y);
                    } break;
                    case epi::epiMetaTypeID_epiVec2u8:
                    {
                        epiVec2u8 value = ptr->Get<epiVec2u8>();
                        slider->SetValueLower(value.x);
                        slider->SetValueUpper(value.y);
                    } break;
                    default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
                    }

                    slider->Refresh();

                    QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
                }
            });

            control = slider;
        }
        else if (typeID == epi::epiMetaTypeID_epiBool)
        {
            wxCheckBox* checkbox = new wxCheckBox(this, wxID_ANY, wxEmptyString);

            // TODO: adjust for a specific type
            checkbox->Bind(wxEVT_CHECKBOX, &epiWXObjectConfigurationPanel::OnCheckboxValueChanged, this); // TODO: figure out whether it should be unbonded
            propertyChangedHandler.PropertyChangedRegister(prtyID, [this, checkbox]()
            {
                if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(checkbox->GetClientData()))
                {
                    checkbox->SetValue(ptr->Get<epiBool>());

                    checkbox->Refresh();

                    QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
                }
            });

            control = checkbox;
        }

        if (control != nullptr)
        {
            epi::PropertyPointer* ptr = m_PrtyPointers.emplace_back(new epi::PropertyPointer());
            *ptr = epi::PropertyPointer::CreateFromProperty(m_Object, &prty);
            control->SetClientData(ptr);
            propertyChangedHandler.PropertyChangedTriggerCallbacks(prtyID);

            sizer->Add(new wxStaticText(this, wxID_ANY, prty.GetName()), wxSizerFlags().Right().Expand().CentreVertical().Proportion(1));
            sizer->Add(control, wxSizerFlags().Expand().CenterVertical().Proportion(2));
        }
    }

    wxBoxSizer* vboxSizer = new wxBoxSizer(wxVERTICAL);
    vboxSizer->Add(sizer, 1, wxALL | wxEXPAND, 20);

    SetSizerAndFit(vboxSizer);
}

void epiWXObjectConfigurationPanel::OnSpinValueChanged(wxSpinEvent& event)
{
    const wxSpinCtrl* spin = static_cast<const wxSpinCtrl*>(event.GetEventObject());
    OnSpinValueChanged_Internal(*spin);
}

void epiWXObjectConfigurationPanel::OnSpinTextValueChanged(wxCommandEvent& event)
{
    const wxSpinCtrl* spin = static_cast<const wxSpinCtrl*>(event.GetEventObject());
    OnSpinValueChanged_Internal(*spin);
}

void epiWXObjectConfigurationPanel::OnSpinDoubleValueChanged(wxSpinDoubleEvent& event)
{
    EPI_NAMESPACE_USING()

    const wxSpinCtrlDouble* spin = static_cast<const wxSpinCtrlDouble*>(event.GetEventObject());
    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(spin->GetClientData()))
    {
        switch (ptr->GetTypeID())
        {
        case epiMetaTypeID_epiFloat: ptr->Set<epiFloat>(event.GetValue()); break;
        case epiMetaTypeID_epiDouble: ptr->Set<epiDouble>(event.GetValue()); break;
        default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
        }
    }
}

void epiWXObjectConfigurationPanel::OnSliderValueChanged(wxCommandEvent& event)
{
    EPI_NAMESPACE_USING()

    const wxSlider* slider = static_cast<const wxSlider*>(event.GetEventObject());
    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(slider->GetClientData()))
    {
        switch (ptr->GetTypeID())
        {
        case epiMetaTypeID_epiByte: ptr->Set<epiByte>(slider->GetValue()); break;
        case epiMetaTypeID_epiU8: ptr->Set<epiU8>(slider->GetValue()); break;
        case epiMetaTypeID_epiS8: ptr->Set<epiS8>(slider->GetValue()); break;
        case epiMetaTypeID_epiSize_t: ptr->Set<epiSize_t>(slider->GetValue()); break;
        default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
        }
    }
}

void epiWXObjectConfigurationPanel::OnSliderRangeValueChanged(wxCommandEvent& event)
{
    EPI_NAMESPACE_USING()

    const epiWXSliderRange* slider = static_cast<const epiWXSliderRange*>(event.GetEventObject());
    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(slider->GetClientData()))
    {
        switch (ptr->GetTypeID())
        {
        case epiMetaTypeID_epiVec2s8: ptr->Set<epiVec2s8>(epiVec2s8{slider->GetValueLower(), slider->GetValueUpper()}); break;
        case epiMetaTypeID_epiVec2u8: ptr->Set<epiVec2u8>(epiVec2u8{slider->GetValueLower(), slider->GetValueUpper()}); break;
        default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
        }
    }
}

void epiWXObjectConfigurationPanel::OnCheckboxValueChanged(wxCommandEvent& event)
{
    const wxCheckBox* checkbox = static_cast<const wxCheckBox*>(event.GetEventObject());
    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(checkbox->GetClientData()))
    {
        ptr->Set<epiBool>(checkbox->GetValue());
    }
}

void epiWXObjectConfigurationPanel::OnSpinValueChanged_Internal(const wxSpinCtrl& spin)
{
    EPI_NAMESPACE_USING()

    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(spin.GetClientData()))
    {
        switch (ptr->GetTypeID())
        {
        case epiMetaTypeID_epiByte: ptr->Set<epiByte>(spin.GetValue()); break;
        case epiMetaTypeID_epiSize_t: ptr->Set<epiSize_t>(spin.GetValue()); break;
        case epiMetaTypeID_epiU8: ptr->Set<epiU8>(spin.GetValue()); break;
        case epiMetaTypeID_epiU16: ptr->Set<epiU16>(spin.GetValue()); break;
        case epiMetaTypeID_epiU32: ptr->Set<epiU32>(spin.GetValue()); break;
        case epiMetaTypeID_epiU64: ptr->Set<epiU64>(spin.GetValue()); break;
        case epiMetaTypeID_epiS8: ptr->Set<epiS8>(spin.GetValue()); break;
        case epiMetaTypeID_epiS16: ptr->Set<epiS16>(spin.GetValue()); break;
        case epiMetaTypeID_epiS32: ptr->Set<epiS32>(spin.GetValue()); break;
        case epiMetaTypeID_epiS64: ptr->Set<epiS64>(spin.GetValue()); break;
        default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
        }
    }
}
