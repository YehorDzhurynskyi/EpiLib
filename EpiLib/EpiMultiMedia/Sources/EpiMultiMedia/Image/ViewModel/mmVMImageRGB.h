#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageRGB.hxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageRGB : public mmVMImageBase
{
EPI_GENREGION_BEGIN(mmVMImageRGB)

EPI_GENHIDDEN_mmVMImageRGB()

public:
    constexpr static epiMetaTypeID TypeID{0xbd9ce539};

    enum mmVMImageRGB_PIDs
    {
        PID_ImageR = 0xabdaab02,
        PID_ImageG = 0xc6074fe9,
        PID_ImageB = 0xb66dbb66,
        PID_COUNT = 3
    };

protected:
    mmImage m_ImageR{};
    mmImage m_ImageG{};
    mmImage m_ImageB{};

EPI_GENREGION_END(mmVMImageRGB)

protected:
    void SetImageSrc_Internal(mmImage* imageSrc) override;
    mmImage GetImageTgt_Internal() const override;

protected:
    epiEventLoopPeriodicalTask* m_PeriodicalTaskR{nullptr};
    epiEventLoopPeriodicalTask* m_PeriodicalTaskG{nullptr};
    epiEventLoopPeriodicalTask* m_PeriodicalTaskB{nullptr};
};

EPI_NAMESPACE_END()
