EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.h"
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

void dvDrawerSeries1Df::Draw(gfxContext& ctx, const dvVMSeries1Df& seriesVM, const epiRect2f& worldFrame, const epiRect2f& uiFrame)
{
    switch (seriesVM.GetRepr())
    {
    case dvSeries1DfRepr::Peak:
    {
        const dSeries1Df* series = seriesVM.GetSeries();
        const epiArray<epiFloat>& data = series->GetData();

        const epiS32 left = std::max(static_cast<epiS32>(worldFrame.Left), 0);
        const epiS32 right = std::min(static_cast<epiS32>(std::ceil(worldFrame.Right)), static_cast<epiS32>(data.Size()));
        for (epiS32 x = left; x < right; ++x)
        {
            const epiFloat y = data[x];
            const epiVec2f world1(x, 0.0f);
            const epiVec2f world2(x, y);
            const epiVec2f p1 = ((world1 - worldFrame.LeftBottom()) / worldFrame.GetSize()) * uiFrame.GetSize() + uiFrame.LeftBottom();
            const epiVec2f p2 = ((world2 - worldFrame.LeftBottom()) / worldFrame.GetSize()) * uiFrame.GetSize() + uiFrame.LeftBottom();

            ctx.GetDrawerPrimitive().DrawLine(p1, p2, seriesVM.GetColor1(), seriesVM.GetColor2(), seriesVM.GetZ());
        }
    } break;
    case dvSeries1DfRepr::Bar:
    {
        const dSeries1Df* series = seriesVM.GetSeries();
        const epiArray<epiFloat>& data = series->GetData();

        const epiS32 left = std::max(static_cast<epiS32>(worldFrame.Left), 0);
        const epiS32 right = std::min(static_cast<epiS32>(std::ceil(worldFrame.Right)), static_cast<epiS32>(data.Size()));
        for (epiS32 x = left; x < right; ++x)
        {
            const epiFloat y = data[x];
            const epiVec2f world1(x, 0.0f);
            const epiVec2f world2(x + 1.0f, y);
            const epiVec2f p1 = ((world1 - worldFrame.LeftBottom()) / worldFrame.GetSize()) * uiFrame.GetSize() + uiFrame.LeftBottom();
            const epiVec2f p2 = ((world2 - worldFrame.LeftBottom()) / worldFrame.GetSize()) * uiFrame.GetSize() + uiFrame.LeftBottom();
            const epiRect2f rect(p1, p2);

            ctx.GetDrawerPrimitive().DrawQuad(rect, seriesVM.GetColor1(), seriesVM.GetColor2(), seriesVM.GetZ());
        }
    } break;
    }
}

EPI_NAMESPACE_END()
