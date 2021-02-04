EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertySliderFloating.h"
#include "EpiUI/ViewModel/uiVMPropertySliderFloating.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void uiVMPropertySliderFloating::SetValue_Callback(epiFloat value)
{
    epiAssert(MetaType::IsFloating(m_PrtyPtr.GetTypeID())); // TODO: IsFloatingFundamental
    switch (m_PrtyPtr.GetTypeID())
    {
    case epiMetaTypeID_epiFloat: SetValue<epiFloat>(static_cast<epiFloat>(value)); break;
    case epiMetaTypeID_epiDouble: SetValue<epiDouble>(static_cast<epiDouble>(value)); break;
    default: epiAssert(!"Unexpected type id!");
    }
}

epiFloat uiVMPropertySliderFloating::GetValue_Callback() const
{
    epiAssert(MetaType::IsFloating(m_PrtyPtr.GetTypeID())); // TODO: IsFloatingFundamental
    switch (m_PrtyPtr.GetTypeID())
    {
    case epiMetaTypeID_epiFloat: return static_cast<epiFloat>(GetValue<epiFloat>());
    case epiMetaTypeID_epiDouble: return static_cast<epiFloat>(GetValue<epiDouble>());
    default: epiAssert(!"Unexpected type id!");
    }

    return 0.0f;
}

EPI_NAMESPACE_END()
