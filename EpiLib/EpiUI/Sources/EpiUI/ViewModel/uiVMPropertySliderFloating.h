#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMPropertySliderFloating.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMPropertySlider.h"

EPI_NAMESPACE_BEGIN()

class uiVMPropertySliderFloating : public uiVMPropertySlider
{
EPI_GENREGION_BEGIN(uiVMPropertySliderFloating)

EPI_GENHIDDEN_uiVMPropertySliderFloating()

public:
    constexpr static epiMetaTypeID TypeID{0x3ce18576};

    enum uiVMPropertySliderFloating_PIDs
    {
        PID_Value = 0xdcb67730,
        PID_MinValue = 0xe1feef64,
        PID_MaxValue = 0x79e4085,
        PID_COUNT = 3
    };

protected:
    epiFloat GetValue_Callback() const;
    void SetValue_Callback(epiFloat value);

protected:
    epiFloat m_MinValue{0.0f};
    epiFloat m_MaxValue{0.0f};

EPI_GENREGION_END(uiVMPropertySliderFloating)

public:
    template<typename T>
    uiVMPropertySliderFloating(const epiPropertyPointer& prtyPtr, T minValue = std::numeric_limits<T>::min(), T maxValue = std::numeric_limits<T>::max());

    template<typename T>
    void SetValue(T value);

    template<typename T>
    T GetValue() const;
};

template<typename T>
uiVMPropertySliderFloating::uiVMPropertySliderFloating(const epiPropertyPointer& prtyPtr, T minValue, T maxValue)
    : super(prtyPtr)
    , m_MinValue{static_cast<epiFloat>(minValue)}
    , m_MaxValue{static_cast<epiFloat>(maxValue)}
{
    static_assert(std::is_floating_point_v<T>);
}

template<typename T>
void uiVMPropertySliderFloating::SetValue(T value)
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<T>());

    value = std::clamp<T>(value, static_cast<T>(m_MinValue), static_cast<T>(m_MaxValue));

    m_PrtyPtr.Set<T>(value);
}

template<typename T>
T uiVMPropertySliderFloating::GetValue() const
{
    epiAssert(m_PrtyPtr.GetTypeID() == MetaType::TypeOf<T>());

    T value = m_PrtyPtr.Get<T>();

    epiAssert(epiEqual(static_cast<epiFloat>(value), std::clamp<epiFloat>(static_cast<epiFloat>(value), m_MinValue, m_MaxValue)));

    return value;
}

EPI_NAMESPACE_END()
