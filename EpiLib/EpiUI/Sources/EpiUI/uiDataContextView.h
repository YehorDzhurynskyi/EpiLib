#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiDataContextView.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiUI/ViewModel/uiVMPropertyBase.h"

EPI_NAMESPACE_BEGIN()

enum class uiDataContextViewEntryView : epiS32
{
EPI_GENREGION_BEGIN(uiDataContextViewEntryView)
    None = 0,
    CheckboxBoolean = 1,
    SliderFloating = 2,
    SliderIntegralSigned = 3,
    SliderIntegralUnsigned = 4
EPI_GENREGION_END(uiDataContextViewEntryView)
};

class uiDataContextViewEntry : public Object
{
EPI_GENREGION_BEGIN(uiDataContextViewEntry)

EPI_GENHIDDEN_uiDataContextViewEntry()

public:
    constexpr static epiMetaTypeID TypeID{0x2a41cc33};

    enum uiDataContextViewEntry_PIDs
    {
        PID_PID = 0xc3f78667,
        PID_View = 0x5ecf04b0,
        PID_COUNT = 2
    };

protected:
    epiHash_t m_PID{0};
    uiDataContextViewEntryView m_View{uiDataContextViewEntryView::None};

EPI_GENREGION_END(uiDataContextViewEntry)

public:
    union ViewData
    {
        struct
        {
            epiFloat MinValue;
            epiFloat MaxValue;
            epiFloat DefaultValue;
        } SliderFloating;
        struct
        {
            epiS64 MinValue;
            epiS64 MaxValue;
            epiS64 DefaultValue;
        } SliderIntegralSigned;
        struct
        {
            epiU64 MinValue;
            epiU64 MaxValue;
            epiU64 DefaultValue;
        } SliderIntegralUnsigned;
    };

public:
    const ViewData& GetViewData() const;
    void SetViewData(const ViewData& viewData);

protected:
    ViewData m_ViewData{0};
};

class uiDataContextView : public Object
{
EPI_GENREGION_BEGIN(uiDataContextView)

EPI_GENHIDDEN_uiDataContextView()

public:
    constexpr static epiMetaTypeID TypeID{0xbbfb822d};

    enum uiDataContextView_PIDs
    {
        PID_Entries = 0xe2458a59,
        PID_COUNT = 1
    };

protected:
    epiArray<uiDataContextViewEntry> m_Entries{};

EPI_GENREGION_END(uiDataContextView)

public:
    void Add(epiMetaPropertyID pid, uiDataContextViewEntryView view, uiDataContextViewEntry::ViewData viewData = {0});
    void AddCheckboxBoolean(epiMetaPropertyID pid);

    template<typename T>
    void AddSlider(epiMetaPropertyID pid, T defaultValue, T minValue = std::numeric_limits<T>::min(), T maxValue = std::numeric_limits<T>::max());

    // TODO: use epiPtrArray
    epiArray<std::unique_ptr<uiVMPropertyBase>> BuildVMList(Object& dataContext) const;
};

template<typename T>
void uiDataContextView::AddSlider(epiMetaPropertyID pid, T defaultValue, T minValue, T maxValue)
{
    if constexpr (std::is_floating_point_v<T>)
    {
        uiDataContextViewEntry::ViewData data;
        data.SliderFloating.MinValue = static_cast<decltype(data.SliderFloating.MinValue)>(minValue);
        data.SliderFloating.MaxValue = static_cast<decltype(data.SliderFloating.MaxValue)>(maxValue);
        data.SliderFloating.DefaultValue = static_cast<decltype(data.SliderFloating.DefaultValue)>(defaultValue);

        Add(pid, uiDataContextViewEntryView::SliderFloating, data);
    }
    else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>)
    {
        uiDataContextViewEntry::ViewData data;
        data.SliderIntegralSigned.MinValue = static_cast<decltype(data.SliderIntegralSigned.MinValue)>(minValue);
        data.SliderIntegralSigned.MaxValue = static_cast<decltype(data.SliderIntegralSigned.MaxValue)>(maxValue);
        data.SliderIntegralSigned.DefaultValue = static_cast<decltype(data.SliderIntegralSigned.DefaultValue)>(defaultValue);

        Add(pid, uiDataContextViewEntryView::SliderIntegralSigned, data);
    }
    else if constexpr (std::is_integral_v<T>&& std::is_unsigned_v<T>)
    {
        uiDataContextViewEntry::ViewData data;
        data.SliderIntegralUnsigned.MinValue = static_cast<decltype(data.SliderIntegralUnsigned.MinValue)>(minValue);
        data.SliderIntegralUnsigned.MaxValue = static_cast<decltype(data.SliderIntegralUnsigned.MaxValue)>(maxValue);
        data.SliderIntegralUnsigned.DefaultValue = static_cast<decltype(data.SliderIntegralUnsigned.DefaultValue)>(defaultValue);

        Add(pid, uiDataContextViewEntryView::SliderIntegralUnsigned, data);
    }
    else
    {
        static_assert(!"Unhandled case!");
    }
}

EPI_NAMESPACE_END()
