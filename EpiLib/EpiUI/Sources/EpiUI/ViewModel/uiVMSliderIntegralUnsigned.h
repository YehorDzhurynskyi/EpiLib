#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMSliderIntegralUnsigned.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMBase.h"

EPI_NAMESPACE_BEGIN()

class uiVMSliderIntegralUnsigned : public uiVMBase
{
EPI_GENREGION_BEGIN(uiVMSliderIntegralUnsigned)

EPI_GENHIDDEN_uiVMSliderIntegralUnsigned()

public:
    constexpr static epiMetaTypeID TypeID{0x35fcfe02};

    enum uiVMSliderIntegralUnsigned_PIDs
    {
        PID_MinValue = 0xe1feef64,
        PID_MaxValue = 0x79e4085,
        PID_COUNT = 2
    };

protected:
    epiU64 m_MinValue{0};
    epiU64 m_MaxValue{0};

EPI_GENREGION_END(uiVMSliderIntegralUnsigned)

public:
    template<typename T>
    uiVMSliderIntegralUnsigned(const epiPropertyPointer& prtyPtr, T minValue = std::numeric_limits<T>::min(), T maxValue = std::numeric_limits<T>::max());

    template<typename T>
    void SetValue(T value);

    template<typename T>
    T GetValue() const;

    void SetValue(epiU64 value);
    epiU64 GetValue() const;
};

template<typename T>
uiVMSliderIntegralUnsigned::uiVMSliderIntegralUnsigned(const epiPropertyPointer& prtyPtr, T minValue, T maxValue)
    : super(prtyPtr)
    , m_MinValue{static_cast<epiU64>(minValue)}
    , m_MaxValue{static_cast<epiU64>(maxValue)}
{
    static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>);
}

template<typename T>
void uiVMSliderIntegralUnsigned::SetValue(T value)
{
    value = std::clamp<T>(value, static_cast<T>(m_MinValue), static_cast<T>(m_MaxValue));

    m_PrtyPtr.Set<T>(value);
}

template<typename T>
T uiVMSliderIntegralUnsigned::GetValue() const
{
    T value = m_PrtyPtr.Get<T>();

    epiAssert(epiEqual(static_cast<epiU64>(value), std::clamp<epiU64>(static_cast<epiU64>(value), m_MinValue, m_MaxValue)));

    return value;
}

EPI_NAMESPACE_END()
