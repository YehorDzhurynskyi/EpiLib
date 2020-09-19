EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.h"
#include "EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

void dvDrawerSeries1Df::Draw(gfxContext& ctx, const dvVMSeries1Df& seriesVM, const epiRect2f& worldFrame, const epiRect2f& uiFrame, epiFloat z)
{
    switch (seriesVM.GetRepr())
    {
    case dvSeries1DfRepr::Peak:
    {
        epiFloat x = 0.0f;
        const dSeries1Df* series = seriesVM.GetSeries();
        for (epiFloat y : series->GetData())
        {
            const epiVec2f world(x, y);
            const epiVec2f p = ((world - worldFrame.LeftBottom()) / worldFrame.GetSize()) * uiFrame.GetSize() + uiFrame.LeftBottom();

            ctx.GetDrawerPrimitive().DrawLine(epiVec2f{ x, 0.0f }, p, seriesVM.GetColor(), z);

            x += 1.0f;
        }
    } break;
    }
}

EPI_NAMESPACE_END()
