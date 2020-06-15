#include "EpiUI/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiUI/Layout/uiLayout.h"
#include "EpiUI/Layout/uiLayout.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

uiLayoutItem& uiLayout::AddWidget(uiWidget* widget)
{
    uiLayoutItem& item = m_Items.PushBack();
    item.SetWidget(widget);

    return item;
}

EPI_NAMESPACE_END()
