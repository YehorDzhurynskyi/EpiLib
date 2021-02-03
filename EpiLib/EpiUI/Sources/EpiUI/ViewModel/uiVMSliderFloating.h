#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/ViewModel/uiVMSliderFloating.hxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMBase.h"

EPI_NAMESPACE_BEGIN()

class uiVMSliderFloating : public uiVMBase
{
EPI_GENREGION_BEGIN(uiVMSliderFloating)

EPI_GENHIDDEN_uiVMSliderFloating()

public:
    constexpr static epiMetaTypeID TypeID{0xf34e2058};

    enum uiVMSliderFloating_PIDs
    {
        PID_MinValue = 0xe1feef64,
        PID_MaxValue = 0x79e4085,
        PID_COUNT = 2
    };

protected:
    epiFloat m_MinValue{0.0f};
    epiFloat m_MaxValue{0.0f};

EPI_GENREGION_END(uiVMSliderFloating)

public:
    template<typename T>
    uiVMSliderFloating(const epiPropertyPointer& prtyPtr, T minValue = std::numeric_limits<T>::min(), T maxValue = std::numeric_limits<T>::max());

    template<typename T>
    void SetValue(T value);

    template<typename T>
    T GetValue() const;

    void SetValue(epiFloat value);
    epiFloat GetValue() const;
};

template<typename T>
uiVMSliderFloating::uiVMSliderFloating(const epiPropertyPointer& prtyPtr, T minValue, T maxValue)
    : super(prtyPtr)
    , m_MinValue{static_cast<epiFloat>(minValue)}
    , m_MaxValue{static_cast<epiFloat>(maxValue)}
{
    static_assert(std::is_floating_point_v<T>);
}

template<typename T>
void uiVMSliderFloating::SetValue(T value)
{
    value = std::clamp<T>(value, static_cast<T>(m_MinValue), static_cast<T>(m_MaxValue));

    m_PrtyPtr.Set<T>(value);
}

template<typename T>
T uiVMSliderFloating::GetValue() const
{
    T value = m_PrtyPtr.Get<T>();

    epiAssert(epiEqual(static_cast<epiFloat>(value), std::clamp<epiFloat>(static_cast<epiFloat>(value), m_MinValue, m_MaxValue)));

    return value;
}

EPI_NAMESPACE_END()
