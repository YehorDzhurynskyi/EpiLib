#include "EpiUI/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiWidget.h"
#include "EpiUI/uiWidget.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

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

EPI_NAMESPACE_END()
