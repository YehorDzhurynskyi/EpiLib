#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertySliderIntegralSigned.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMPropertySlider.h"

EPI_NAMESPACE_BEGIN()

class uiVMPropertySliderIntegralSigned : public uiVMPropertySlider
{
EPI_GENREGION_BEGIN(uiVMPropertySliderIntegralSigned)

EPI_GENHIDDEN_uiVMPropertySliderIntegralSigned()

public:
    constexpr static epiMetaTypeID TypeID{0x3c68adbe};

    enum uiVMPropertySliderIntegralSigned_PIDs
    {
        PID_Value = 0xdcb67730,
        PID_MinValue = 0xe1feef64,
        PID_MaxValue = 0x79e4085,
        PID_DefaultValue = 0xdc53e7d5,
        PID_COUNT = 4
    };

protected:
    epiS64 GetValue_Callback() const;
    void SetValue_Callback(epiS64 value);

protected:
    epiS64 m_MinValue{0};
    epiS64 m_MaxValue{0};
    epiS64 m_DefaultValue{0};

EPI_GENREGION_END(uiVMPropertySliderIntegralSigned)

public:
    template<typename T>
    uiVMPropertySliderIntegralSigned(const epiPropertyPointer& prtyPtr, T defaultValue, T minValue = std::numeric_limits<T>::min(), T maxValue = std::numeric_limits<T>::max());

    template<typename T>
    void SetValue(T value);

    template<typename T>
    T GetValue() const;
};

template<typename T>
uiVMPropertySliderIntegralSigned::uiVMPropertySliderIntegralSigned(const epiPropertyPointer& prtyPtr, T defaultValue, T minValue, T maxValue)
    : super(prtyPtr)
    , m_MinValue{static_cast<epiS64>(minValue)}
    , m_MaxValue{static_cast<epiS64>(maxValue)}
    , m_DefaultValue{static_cast<epiS64>(defaultValue)}
{
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);
}

template<typename T>
void uiVMPropertySliderIntegralSigned::SetValue(T value)
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<T>());

    value = std::clamp<T>(value, static_cast<T>(m_MinValue), static_cast<T>(m_MaxValue));

    m_PrtyPtr.Set<T>(value);
}

template<typename T>
T uiVMPropertySliderIntegralSigned::GetValue() const
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<T>());

    T value = m_PrtyPtr.Get<T>();

    epiAssert(epiEqual(static_cast<epiS64>(value), std::clamp<epiS64>(static_cast<epiS64>(value), m_MinValue, m_MaxValue)));

    return value;
}

EPI_NAMESPACE_END()
