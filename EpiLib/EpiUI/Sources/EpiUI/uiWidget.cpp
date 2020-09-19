EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.h"
#include "EpiUI/uiWidget.cxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiContext.h"
#include "EpiUI/Layout/uiLayout.h"

EPI_NAMESPACE_BEGIN()

epiBool uiSizePolicyInfo::GetCanExpandVertically_Callback() const
{
    return GetSizePolicyVertical() & uiSizePolicy_Expand_Mask;
}

epiBool uiSizePolicyInfo::GetCanExpandHorizontally_Callback() const
{
    return GetSizePolicyHorizontal() & uiSizePolicy_Expand_Mask;
}

void uiWidget::Update()
{
    for (auto& w : GetChildren())
    {
        w->Update();
    }
}

void uiWidget::Draw(uiContext& uiContext)
{
    for (auto& w : GetChildren())
    {
        w->Draw(uiContext);
    }
}

epiRect2f uiWidget::GetBBox_Callback() const
{
    epiRect2f bbox;
    bbox.Left = m_Position.x;
    bbox.Bottom = m_Position.y;
    bbox.Right = m_Position.x + m_Size.x;
    bbox.Top = m_Position.y + m_Size.y;

    return bbox;
}

void uiWidget::SetBBox_Callback(const epiRect2f& value)
{
    m_Position.x = value.Left;
    m_Position.y = value.Bottom;
    m_Size.x = value.Right - m_Position.x;
    m_Size.y = value.Top - m_Position.y;
}

epiFloat uiWidget::GetWidth_Callback() const
{
    return m_Size.x;
}

void uiWidget::SetWidth_Callback(epiFloat value)
{
    m_Size.x = value;
}

epiFloat uiWidget::GetHeight_Callback() const
{
    return m_Size.y;
}

void uiWidget::SetHeight_Callback(epiFloat value)
{
    m_Size.y = value;
}

void uiWidget::OnMousePrimary(uiMouseAction action)
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
    for (auto& w : GetChildren())
    {
        w->OnMouseFocus(focused);
    }
}

#if 1
void uiWidget::OnResize()
{
    if (uiWidget* parent = GetParent())
    {
        SetBBox(parent->GetBBox());
    }

    for (auto& w : GetChildren())
    {
        w->OnResize();
    }
}
#else
void uiWidget::OnResize()
{
    if (uiLayout* layout = GetLayout())
    {
        if (uiWidget* parent = GetParent())
        {
            layout->SetSize(parent->GetSize());
        }

        layout->OnResize();
    }

    for (auto& w : GetChildren())
    {
        w->OnResize();
    }
}

void uiWidget::OnResize()
{
    epiAssert(m_Parent, "Top-level widget should override this method");

    const uiSizePolicy parentSizePolicy = m_Parent->GetSizePolicy();
    const epiVec2f& parentSize = m_Parent->GetSize();
    const uiSizePolicy sizePolicy = GetSizePolicy();

    switch (parentSizePolicy)
    {
    case uiSizePolicy::Fixed:
    {
        epiVec2f size{};
        switch (sizePolicy)
        {
        case uiSizePolicy::Fixed:
        {
            size = GetSizeHint();
        } break;
        case uiSizePolicy::Minimum:
        {
            size = GetSizeHint();
        } break;
        case uiSizePolicy::Maximum: epiAssert(false, "Unhandled case"); break;
        case uiSizePolicy::Preferred: epiAssert(false, "Unhandled case"); break;
        case uiSizePolicy::Expanding: epiAssert(false, "Unhandled case"); break;
        case uiSizePolicy::MinimumExpanding: epiAssert(false, "Unhandled case"); break;
        case uiSizePolicy::Ignored: epiAssert(false, "Unhandled case"); break;
        default: epiAssert(false, "Unhandled case");
        }

        SetSize(size);
        for (auto& w : m_Children)
        {
            w->OnResize();
        }
    } break;
    case uiSizePolicy::Minimum:
    {
        size = GetSizeHint();
    } break;
    case uiSizePolicy::Maximum:
    {
        size = GetSizeHint();
    } break;
    case uiSizePolicy::Preferred:
    {
        size = GetSizeHint();
    } break;
    case uiSizePolicy::Expanding:
    {
        size = GetSizeHint();
    } break;
    case uiSizePolicy::MinimumExpanding:
    {
        size = GetSizeHint();
    } break;
    case uiSizePolicy::Ignored:
    {
        size = GetSizeHint();
    } break;
    default: epiAssert(false, "Unhandled case");
    }

    epiVec2f size{};
    switch (GetSizePolicy())
    {
    case uiSizePolicy::Fixed:
    {
        size = GetSizeHint();
    } break;
    case uiSizePolicy::Minimum: size = GetSizeHint(); break;
    case uiSizePolicy::Maximum: epiAssert(false, "Unhandled case"); break;
    case uiSizePolicy::Preferred: epiAssert(false, "Unhandled case"); break;
    case uiSizePolicy::Expanding: epiAssert(false, "Unhandled case"); break;
    case uiSizePolicy::MinimumExpanding: epiAssert(false, "Unhandled case"); break;
    case uiSizePolicy::Ignored: epiAssert(false, "Unhandled case"); break;
    default: epiAssert(false, "Unhandled case");
    }

    SetSize(size);
    for (auto& w : m_Children)
    {
        w->OnResize();
    }
}
#endif

epiVec2f uiWidget::GetMouseLocalUICoord_Callback() const
{
    return GetMouseLocalUICoord_Internal();
}

epiVec2f uiWidget::GetMouseLocalUICoord_Internal() const
{
    const epiVec2f mouseLocalUICoordParent = m_Parent->GetMouseLocalUICoord();
    const epiRect2f& bbox = GetBBox();

    return mouseLocalUICoordParent; // TODO: implement
}

uiWidget* uiWidget::WidgetOverMouse(const epiVec2f& mouseUICoord) const
{
    auto it = std::find_if(GetChildren().begin(),
                           GetChildren().end(),
                           [&](const uiWidget* widget)
    {
        return widget->GetBBox().IsIn(mouseUICoord);
    });

    return it != GetChildren().end() ? *it : nullptr;
}

EPI_NAMESPACE_END()
