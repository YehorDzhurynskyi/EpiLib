EPI_GENREGION_BEGIN(include)
#include "EpiUI/Layout/uiLayoutBox.h"
#include "EpiUI/Layout/uiLayoutBox.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

#if 0
void uiLayoutBox::OnResize()
{
    epiAssert(GetDirection() == uiDirection::TopToBottom, "The only direction is now supported");

    const epiVec2f& sizeLayout = GetSize();
    epiArray<uiLayoutItem>& items = GetItems();

    for (auto& item : GetItems())
    {
        epiFloat proposedHeight{};
        epiVec2f sizeWidget{sizeLayout.x, 0.0f};

        uiWidget* widget = item.GetWidget();
        const uiSizePolicyInfo& sizePolicyInfo = widget->GetSizePolicyInfo();
        const uiSizePolicy& sizePolicyVertical = sizePolicyInfo.GetSizePolicyVertical();

        switch (sizePolicyVertical)
        {
        case uiSizePolicy_Fixed:
        {
            sizeWidget.y = widget->GetSizeHint().y;
        } break;
        case uiSizePolicy_Minimum:
        {
            sizeWidget.y = std::max(widget->GetSizeHint().y, proposedHeight);
        } break;
        case uiSizePolicy_Maximum:
        {
            sizeWidget.y = std::min(widget->GetSizeHint().y, proposedHeight);
        } break;
        case uiSizePolicy_Preferred:
        {
            sizeWidget.y = widget->GetSizeHint().y;
        } break;
        case uiSizePolicy_Expanding: epiAssert(false, "Unhandled case"); break;
        case uiSizePolicy_MinimumExpanding: epiAssert(false, "Unhandled case"); break;
        case uiSizePolicy_Ignored: epiAssert(false, "Unhandled case"); break;
        default: epiAssert(false, "Unhandled case");
        }

        widget->SetSize(sizeWidget);
    }
}
#endif

void uiLayoutBox::OnResize()
{
    // TODO: finish

    epiAssert(GetDirection() == uiDirection::TopToBottom, "The only direction is now supported");

    const epiVec2f sizeTotal = GetSize();

    epiArray<uiLayoutItem>& items = GetItems();
    for (auto& item : items)
    {
        item.GetWidget()->SetWidth(sizeTotal.x);
        item.GetWidget()->SetHeight(0.0f);
    }

    epiFloat heightFree = sizeTotal.y;
    for (auto& item : items)
    {
        uiWidget* widget = item.GetWidget();
        const uiSizePolicyInfo& sizePolicyInfo = widget->GetSizePolicyInfo();
        const uiSizePolicy& sizePolicy = sizePolicyInfo.GetSizePolicyVertical();

        if (sizePolicy & uiSizePolicy_Shrink_Mask)
        {
            continue;
        }

        heightFree = std::max(0.0f, heightFree - widget->GetSizeHint().y);
        widget->SetHeight(widget->GetSizeHint().y);
    }

    for (auto& item : items)
    {
        uiWidget* widget = item.GetWidget();
        const uiSizePolicyInfo& sizePolicyInfo = widget->GetSizePolicyInfo();
        const uiSizePolicy& sizePolicy = sizePolicyInfo.GetSizePolicyVertical();

        if (sizePolicy & uiSizePolicy_Expand_Mask)
        {
            item.GetWidget()->SetHeight(heightFree);
        }
    }

    {
        epiFloat offsetY = 0.0f;
        for (auto it = items.rbegin(); it != items.rend(); ++it)
        {
            uiLayoutItem& item = *it;

            uiWidget* widget = item.GetWidget();
            widget->SetPosition((sizeTotal / -2.0f) + epiVec2f{ 0.0f, offsetY });

            offsetY += widget->GetHeight();
        }
    }
}

EPI_NAMESPACE_END()
