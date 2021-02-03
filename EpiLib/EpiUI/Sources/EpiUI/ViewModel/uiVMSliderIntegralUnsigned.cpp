EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMSliderIntegralUnsigned.h"
#include "EpiUI/ViewModel/uiVMSliderIntegralUnsigned.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void uiVMSliderIntegralUnsigned::SetValue(epiU64 value)
{
    epiAssert(MetaType::IsNumeric(m_PrtyPtr.GetTypeID()));
    switch (m_PrtyPtr.GetTypeID())
    {
    case epiMetaTypeID_epiByte: SetValue<epiByte>(static_cast<epiByte>(value)); break;
    case epiMetaTypeID_epiU8: SetValue<epiU8>(static_cast<epiU8>(value)); break;
    case epiMetaTypeID_epiU16: SetValue<epiU16>(static_cast<epiU16>(value)); break;
    case epiMetaTypeID_epiU32: SetValue<epiU32>(static_cast<epiU32>(value)); break;
    case epiMetaTypeID_epiS64: SetValue<epiU64>(static_cast<epiU64>(value)); break;
    case epiMetaTypeID_epiSize_t: SetValue<epiSize_t>(static_cast<epiSize_t>(value)); break;
    default: epiAssert(!"Unexpected type id!");
    }
}

epiU64 uiVMSliderIntegralUnsigned::GetValue() const
{
    epiAssert(MetaType::IsNumeric(m_PrtyPtr.GetTypeID()));
    switch (m_PrtyPtr.GetTypeID())
    {
    case epiMetaTypeID_epiByte: return static_cast<epiU64>(GetValue<epiByte>());
    case epiMetaTypeID_epiU8: return static_cast<epiU64>(GetValue<epiU8>());
    case epiMetaTypeID_epiU16: return static_cast<epiU64>(GetValue<epiU16>());
    case epiMetaTypeID_epiU32: return static_cast<epiU64>(GetValue<epiU32>());
    case epiMetaTypeID_epiU64: return static_cast<epiU64>(GetValue<epiU64>());
    case epiMetaTypeID_epiSize_t: return static_cast<epiU64>(GetValue<epiSize_t>());
    default: epiAssert(!"Unexpected type id!");
    }

    return 0;
}

EPI_NAMESPACE_END()
