EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMSliderIntegralSigned.h"
#include "EpiUI/ViewModel/uiVMSliderIntegralSigned.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void uiVMSliderIntegralSigned::SetValue(epiS64 value)
{
    epiAssert(MetaType::IsNumeric(m_PrtyPtr.GetTypeID()));
    switch (m_PrtyPtr.GetTypeID())
    {
    case epiMetaTypeID_epiS8: SetValue<epiS8>(static_cast<epiS8>(value)); break;
    case epiMetaTypeID_epiS16: SetValue<epiS16>(static_cast<epiS16>(value)); break;
    case epiMetaTypeID_epiS32: SetValue<epiS32>(static_cast<epiS32>(value)); break;
    case epiMetaTypeID_epiS64: SetValue<epiS64>(static_cast<epiS64>(value)); break;
    default: epiAssert(!"Unexpected type id!");
    }
}

epiS64 uiVMSliderIntegralSigned::GetValue() const
{
    epiAssert(MetaType::IsNumeric(m_PrtyPtr.GetTypeID()));
    switch (m_PrtyPtr.GetTypeID())
    {
    case epiMetaTypeID_epiS8: return static_cast<epiS64>(GetValue<epiS8>());
    case epiMetaTypeID_epiS16: return static_cast<epiS64>(GetValue<epiS16>());
    case epiMetaTypeID_epiS32: return static_cast<epiS64>(GetValue<epiS32>());
    case epiMetaTypeID_epiS64: return static_cast<epiS64>(GetValue<epiS64>());
    default: epiAssert(!"Unexpected type id!");
    }

    return 0;
}

EPI_NAMESPACE_END()
