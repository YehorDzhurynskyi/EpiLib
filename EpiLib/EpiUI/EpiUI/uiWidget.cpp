#include "EpiUI/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.h"
#include "EpiUI/uiWidget.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void uiWidget::Update()
{
    for (auto& w : m_Children)
    {
        w->Update();
    }
}

const epiVec2f& uiWidget::GetPosition_Callback() const
{
    return m_BBox.BottomLeft();
}

void uiWidget::SetPosition_Callback(const epiVec2f& value)
{
    m_BBox.Left = value.x;
    m_BBox.Bottom = value.y;
}

epiFloat uiWidget::GetWidth_Callback() const
{
    return m_BBox.GetWidth();
}

void uiWidget::SetWidth_Callback(epiFloat value)
{
    m_BBox.Right = value + m_BBox.Left;
}

epiFloat uiWidget::GetHeight_Callback() const
{
    return m_BBox.GetHeight();
}

void uiWidget::SetHeight_Callback(epiFloat value)
{
    m_BBox.Top = value + m_BBox.Bottom;
}

void uiWidget::OnMousePrimary(MouseAction action)
{
    if (uiWidget* widget = WidgetOverMouse(GetMouseLocalUICoord()))
    {
        widget->OnMousePrimary(action);
    }
}

void uiWidget::OnMouseWheel(epiFloat dZoom)
{
    if (uiWidget* widget = WidgetOverMouse(GetMouseLocalUICoord()))
    {
        widget->OnMouseWheel(dZoom);
    }
}

void uiWidget::OnMouseFocus(epiBool focused)
{
    for (auto& w : m_Children)
    {
        w->OnMouseFocus(focused);
    }
}

void uiWidget::OnResize(const epiRect2f& parentBBox)
{
    epiRect2f bbox = parentBBox;

    if (m_SizePolicyX == uiSizePolicy::Expand)
    {
        if (uiWidget* neighbor = FindNeighborClosestLeft())
        {
            bbox.Left = neighbor->GetBBox().Right;
        }
        if (uiWidget* neighbor = FindNeighborClosestRight())
        {
            bbox.Right = neighbor->GetBBox().Left;
        }
    }
    else if (m_SizePolicyX == uiSizePolicy::Fixed)
    {
        const epiRect2f& bboxCurr = GetBBox();
        bbox.Left = bboxCurr.Left;
        bbox.Right = bboxCurr.Right;
    }

    if (m_SizePolicyY == uiSizePolicy::Expand)
    {
        if (uiWidget* neighbor = FindNeighborClosestBottom())
        {
            bbox.Bottom = neighbor->GetBBox().Top;
        }
        if (uiWidget* neighbor = FindNeighborClosestTop())
        {
            bbox.Top = neighbor->GetBBox().Bottom;
        }
    }
    else if (m_SizePolicyY == uiSizePolicy::Fixed)
    {
        const epiRect2f& bboxCurr = GetBBox();
        bbox.Bottom = bboxCurr.Bottom;
        bbox.Top = bboxCurr.Top;
    }

    SetBBox(bbox);

    for (auto& w : m_Children)
    {
        w->OnResize(GetBBox());
    }
}

epiVec2f uiWidget::GetMouseLocalUICoord_Callback() const
{
    return GetMouseLocalUICoord_Internal();
}

epiVec2f uiWidget::GetMouseLocalUICoord_Internal() const
{
    const epiVec2f mouseLocalUICoord = m_Parent->GetMouseLocalUICoord();
    return mouseLocalUICoord; // TODO: implement
}

uiWidget* uiWidget::WidgetOverMouse(const epiVec2f& mouseUICoord) const
{
    auto it = std::find_if(m_Children.begin(), m_Children.end(), [&](const uiWidget* widget)
    {
        return widget->GetBBox().IsIn(mouseUICoord);
    });
    return it != m_Children.end() ? *it : nullptr;
}

uiWidget* uiWidget::FindNeighborClosest(FindNeighborClosestComparator&& comparator) const
{
    epiAssert(m_Parent, "this widget should have a parent");

    auto it = std::min_element(m_Parent->m_Children.begin(), m_Parent->m_Children.end(), comparator);
    if (it == m_Parent->m_Children.end() || *it == this)
    {
        return nullptr;
    }

    return comparator(*it, this) ? *it : nullptr;
}

uiWidget* uiWidget::FindNeighborClosestLeft() const
{
    const epiRect2f& bboxThis = GetBBox();

    auto comparator = [&](const uiWidget* lhs, const uiWidget* rhs) -> epiBool
    {
        const epiRect2f& bboxLhs = lhs->GetBBox();
        const epiRect2f& bboxRhs = rhs->GetBBox();

        epiAssert((bboxLhs & bboxRhs).IsEmpty(), "lhs and rhs bboxes shouldn't have an intersection");

        if (lhs == this)
        {
            return !(bboxRhs.Right < bboxThis.Left);
        }
        else if (rhs == this)
        {
            return bboxLhs.Right < bboxThis.Left;
        }

        if (bboxRhs.Right < bboxThis.Left)
        {
            return bboxLhs.Right < bboxThis.Left ? bboxLhs.Right > bboxRhs.Right : false;
        }

        return true;
    };

    return FindNeighborClosest(comparator);
}

uiWidget* uiWidget::FindNeighborClosestRight() const
{
    const epiRect2f& bboxThis = GetBBox();

    auto comparator = [&](const uiWidget* lhs, const uiWidget* rhs) -> epiBool
    {
        const epiRect2f& bboxLhs = lhs->GetBBox();
        const epiRect2f& bboxRhs = rhs->GetBBox();

        epiAssert((bboxLhs & bboxRhs).IsEmpty(), "lhs and rhs bboxes shouldn't have an intersection");

        if (lhs == this)
        {
            return !(bboxRhs.Left > bboxThis.Right);
        }
        else if (rhs == this)
        {
            return bboxLhs.Left > bboxThis.Right;
        }

        if (bboxRhs.Left > bboxThis.Right)
        {
            return bboxLhs.Left > bboxThis.Right ? bboxLhs.Left < bboxRhs.Left : false;
        }

        return true;
    };

    return FindNeighborClosest(comparator);
}

uiWidget* uiWidget::FindNeighborClosestBottom() const
{
    const epiRect2f& bboxThis = GetBBox();

    auto comparator = [&](const uiWidget* lhs, const uiWidget* rhs) -> epiBool
    {
        const epiRect2f& bboxLhs = lhs->GetBBox();
        const epiRect2f& bboxRhs = rhs->GetBBox();

        epiAssert((bboxLhs & bboxRhs).IsEmpty(), "lhs and rhs bboxes shouldn't have an intersection");

        if (lhs == this)
        {
            return !(bboxRhs.Top < bboxThis.Bottom);
        }
        else if (rhs == this)
        {
            return bboxLhs.Top < bboxThis.Bottom;
        }

        if (bboxRhs.Top < bboxThis.Bottom)
        {
            return bboxLhs.Top < bboxThis.Bottom ? bboxLhs.Top > bboxRhs.Top : false;
        }

        return true;
    };

    return FindNeighborClosest(comparator);
}

uiWidget* uiWidget::FindNeighborClosestTop() const
{
    const epiRect2f& bboxThis = GetBBox();

    auto comparator = [&](const uiWidget* lhs, const uiWidget* rhs) -> epiBool
    {
        const epiRect2f& bboxLhs = lhs->GetBBox();
        const epiRect2f& bboxRhs = rhs->GetBBox();

        epiAssert((bboxLhs & bboxRhs).IsEmpty(), "lhs and rhs bboxes shouldn't have an intersection");

        if (lhs == this)
        {
            return !(bboxRhs.Bottom > bboxThis.Top);
        }
        else if (rhs == this)
        {
            return bboxLhs.Bottom > bboxThis.Top;
        }

        if (bboxRhs.Bottom > bboxThis.Top)
        {
            return bboxLhs.Bottom > bboxThis.Top ? bboxLhs.Bottom < bboxRhs.Bottom : false;
        }

        return true;
    };

    return FindNeighborClosest(comparator);
}

EPI_NAMESPACE_END()
