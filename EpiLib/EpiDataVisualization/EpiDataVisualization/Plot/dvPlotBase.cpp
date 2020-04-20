#include "EpiDataVisualization/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/dvPlotBase.h"
#include "EpiDataVisualization/Plot/dvPlotBase.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

epiVec2f dvPlotBase::GetRangeX_Callback() const
{
    return epiVec2f(m_ClipBox.Left, m_ClipBox.Right);
}

void dvPlotBase::SetRangeX_Callback(const epiVec2f& value)
{
    m_ClipBox.Left = value.x;
    m_ClipBox.Right = value.y;
}

epiVec2f dvPlotBase::GetRangeY_Callback() const
{
    return epiVec2f(m_ClipBox.Bottom, m_ClipBox.Top);
}

void dvPlotBase::SetRangeY_Callback(const epiVec2f& value)
{
    m_ClipBox.Bottom = value.x;
    m_ClipBox.Top = value.y;
}

EPI_NAMESPACE_END()
