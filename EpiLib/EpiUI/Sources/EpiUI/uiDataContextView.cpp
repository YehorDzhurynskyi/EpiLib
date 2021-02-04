EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiDataContextView.h"
#include "EpiUI/uiDataContextView.cxx"
EPI_GENREGION_END(include)

#include "EpiUI/ViewModel/uiVMPropertyCheckboxBoolean.h"
#include "EpiUI/ViewModel/uiVMPropertySliderFloating.h"
#include "EpiUI/ViewModel/uiVMPropertySliderIntegralSigned.h"
#include "EpiUI/ViewModel/uiVMPropertySliderIntegralUnsigned.h"

EPI_NAMESPACE_BEGIN()

const uiDataContextViewEntry::ViewData& uiDataContextViewEntry::GetViewData() const
{
    return m_ViewData;
}

void uiDataContextViewEntry::SetViewData(const uiDataContextViewEntry::ViewData& viewData)
{
    m_ViewData = viewData;
}

void uiDataContextView::Add(epiMetaPropertyID pid, uiDataContextViewEntryView view, uiDataContextViewEntry::ViewData viewData)
{
    uiDataContextViewEntry entry;
    entry.SetPID(pid);
    entry.SetView(view);
    entry.SetViewData(viewData);

    GetEntries().push_back(entry);
}

void uiDataContextView::AddCheckboxBoolean(epiMetaPropertyID pid)
{
    Add(pid, uiDataContextViewEntryView::CheckboxBoolean);
}

epiArray<std::unique_ptr<uiVMPropertyBase>> uiDataContextView::BuildVMList(Object& dataContext) const
{
    epiArray<std::unique_ptr<uiVMPropertyBase>> vmList;
    vmList.Reserve(GetEntries().Size());

    const MetaClass& meta = dataContext.GetMetaClass();
    for (const auto& entry : GetEntries())
    {
        const MetaProperty* prty = meta.GetPropertyBy(entry.GetPID());
        epiAssert(prty != nullptr);
        epiPropertyPointer ptr = epiPropertyPointer::CreateFromProperty(dataContext, prty);

        std::unique_ptr<uiVMPropertyBase> vm = nullptr;
        switch (entry.GetView())
        {
        case uiDataContextViewEntryView::CheckboxBoolean:
        {
            vm = std::make_unique<uiVMPropertyCheckboxBoolean>(ptr);
        } break;
        case uiDataContextViewEntryView::SliderFloating:
        {
            vm = std::make_unique<uiVMPropertySliderFloating>(ptr,
                                                              entry.GetViewData().SliderFloating.MinValue,
                                                              entry.GetViewData().SliderFloating.MaxValue);
        } break;
        case uiDataContextViewEntryView::SliderIntegralSigned:
        {
            vm = std::make_unique<uiVMPropertySliderIntegralSigned>(ptr,
                                                                    entry.GetViewData().SliderIntegralSigned.MinValue,
                                                                    entry.GetViewData().SliderIntegralSigned.MaxValue);
        } break;
        case uiDataContextViewEntryView::SliderIntegralUnsigned:
        {
            vm = std::make_unique<uiVMPropertySliderIntegralUnsigned>(ptr,
                                                                      entry.GetViewData().SliderIntegralUnsigned.MinValue,
                                                                      entry.GetViewData().SliderIntegralUnsigned.MaxValue);
        } break;
        default: epiLogError("Unhandled uiDataContextViewEntryView=`{}`", entry.GetView()); // TODO: use string representation
        }

        epiAssert(vm);
        vmList.push_back(std::move(vm));
    }

    return vmList;
}

EPI_NAMESPACE_END()
