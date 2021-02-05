#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertySliderIntegralUnsigned.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMPropertySlider.h"

EPI_NAMESPACE_BEGIN()

class uiVMPropertySliderIntegralUnsigned : public uiVMPropertySlider
{
EPI_GENREGION_BEGIN(uiVMPropertySliderIntegralUnsigned)

EPI_GENHIDDEN_uiVMPropertySliderIntegralUnsigned()

public:
    constexpr static epiMetaTypeID TypeID{0x4f9cae9e};

    enum uiVMPropertySliderIntegralUnsigned_PIDs
    {
        PID_Value = 0xdcb67730,
        PID_MinValue = 0xe1feef64,
        PID_MaxValue = 0x79e4085,
        PID_DefaultValue = 0xdc53e7d5,
        PID_COUNT = 4
    };

protected:
    epiU64 GetValue_Callback() const;
    void SetValue_Callback(epiU64 value);

protected:
    epiU64 m_MinValue{0};
    epiU64 m_MaxValue{0};
    epiU64 m_DefaultValue{0};

EPI_GENREGION_END(uiVMPropertySliderIntegralUnsigned)

public:
    template<typename T>
    uiVMPropertySliderIntegralUnsigned(const epiPropertyPointer& prtyPtr, T defaultValue, T minValue = std::numeric_limits<T>::min(), T maxValue = std::numeric_limits<T>::max());

    template<typename T>
    void SetValue(T value);

    template<typename T>
    T GetValue() const;
};

template<typename T>
uiVMPropertySliderIntegralUnsigned::uiVMPropertySliderIntegralUnsigned(const epiPropertyPointer& prtyPtr, T defaultValue, T minValue, T maxValue)
    : super(prtyPtr)
    , m_MinValue{static_cast<epiU64>(minValue)}
    , m_MaxValue{static_cast<epiU64>(maxValue)}
    , m_DefaultValue{static_cast<epiU64>(defaultValue)}
{
    static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>);
}

template<typename T>
void uiVMPropertySliderIntegralUnsigned::SetValue(T value)
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<T>());

    value = std::clamp<T>(value, static_cast<T>(m_MinValue), static_cast<T>(m_MaxValue));

    m_PrtyPtr.Set<T>(value);
}

template<typename T>
T uiVMPropertySliderIntegralUnsigned::GetValue() const
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<T>());

    T value = m_PrtyPtr.Get<T>();

    epiAssert(epiEqual(static_cast<epiU64>(value), std::clamp<epiU64>(static_cast<epiU64>(value), m_MinValue, m_MaxValue)));

    return value;
}

EPI_NAMESPACE_END()
