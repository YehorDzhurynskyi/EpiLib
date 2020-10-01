#include "EpiCore/ObjectModel/PropertyPointer.h"

#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

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

    const epi::MetaClass& meta = m_Object.GetMetaClass();
    const epi::MetaClassData& metaData = meta.GetClassData();
    for (const auto& prty : metaData)
    {
        if (epi::epiMetaTypeID typeID = prty.GetTypeID(); epi::MetaType::IsNumeric(typeID))
        {
            sizer->Add(new wxStaticText(this, wxID_ANY, prty.GetName()), wxSizerFlags().Right().Expand());

            wxControl* control = nullptr;
            if (epi::MetaType::IsFloating(typeID))
            {
                wxSpinCtrlDouble* spin = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP);

                // TODO: adjust for a specific type
                spin->SetRange(std::numeric_limits<epiDouble>::min(), std::numeric_limits<epiDouble>::max());
                spin->Bind(wxEVT_SPINCTRLDOUBLE, &epiWXObjectConfigurationPanel::OnSpinDoubleValueChanged, this); // TODO: figure out whether it should be unbonded

                control = spin;
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

            if (control != nullptr)
            {
                epi::PropertyPointer* ptr = m_PrtyPointers.emplace_back(new epi::PropertyPointer());
                *ptr = epi::PropertyPointer::CreateFromProperty(m_Object, &prty);
                control->SetClientData(ptr);

                sizer->Add(control, wxSizerFlags().Expand());
            }
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

    if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(static_cast<wxSpinCtrl*>(event.GetEventObject())->GetClientData()))
    {
        switch (ptr->GetTypeID())
        {
        case epiMetaTypeID_epiFloat: ptr->Set<epiFloat>(event.GetValue()); break;
        case epiMetaTypeID_epiDouble: ptr->Set<epiDouble>(event.GetValue()); break;
        default: epiLogError("Unhandled case for typeid=`{}`", ptr->GetTypeID());
        }
    }

    QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
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

    QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
}
