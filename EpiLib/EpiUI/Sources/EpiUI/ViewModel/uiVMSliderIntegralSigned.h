#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMSliderIntegralSigned.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMBase.h"

EPI_NAMESPACE_BEGIN()

class uiVMSliderIntegralSigned : public uiVMBase
{
EPI_GENREGION_BEGIN(uiVMSliderIntegralSigned)

EPI_GENHIDDEN_uiVMSliderIntegralSigned()

public:
    constexpr static epiMetaTypeID TypeID{0x36f20130};

    enum uiVMSliderIntegralSigned_PIDs
    {
        PID_MinValue = 0xe1feef64,
        PID_MaxValue = 0x79e4085,
        PID_COUNT = 2
    };

protected:
    epiS64 m_MinValue{0};
    epiS64 m_MaxValue{0};

EPI_GENREGION_END(uiVMSliderIntegralSigned)

public:
    template<typename T>
    uiVMSliderIntegralSigned(const epiPropertyPointer& prtyPtr, T minValue = std::numeric_limits<T>::min(), T maxValue = std::numeric_limits<T>::max());

    template<typename T>
    void SetValue(T value);

    template<typename T>
    T GetValue() const;

    void SetValue(epiS64 value);
    epiS64 GetValue() const;
};

template<typename T>
uiVMSliderIntegralSigned::uiVMSliderIntegralSigned(const epiPropertyPointer& prtyPtr, T minValue, T maxValue)
    : super(prtyPtr)
    , m_MinValue{static_cast<epiS64>(minValue)}
    , m_MaxValue{static_cast<epiS64>(maxValue)}
{
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);
}

template<typename T>
void uiVMSliderIntegralSigned::SetValue(T value)
{
    value = std::clamp<T>(value, static_cast<T>(m_MinValue), static_cast<T>(m_MaxValue));

    m_PrtyPtr.Set<T>(value);
}

template<typename T>
T uiVMSliderIntegralSigned::GetValue() const
{
    T value = m_PrtyPtr.Get<T>();

    epiAssert(epiEqual(static_cast<epiS64>(value), std::clamp<epiS64>(static_cast<epiS64>(value), m_MinValue, m_MaxValue)));

    return value;
}

EPI_NAMESPACE_END()
