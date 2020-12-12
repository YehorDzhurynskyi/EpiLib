EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.cxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Image/mmJobImage.h"

#include "EpiCore/MT/JobSystem/epiJobScheduler.h"
#include "EpiCore/MT/EventLoop/epiEventLoop.h"

EPI_NAMESPACE_BEGIN()

using JobThreshold = mmJobImage<epiU8, epiU8, epiU8, epiU8>;

mmVMImageThreshold::mmVMImageThreshold()
{
    SetIsThresholdSynchronized(true);
}

void mmVMImageThreshold::SetThresholdR_Callback(epiU8 value)
{
    if (!epiEqual(GetThresholdR(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            std::unique_ptr<JobThreshold> job = std::make_unique<JobThreshold>(image->ToGrayScaleR(), &mmImage::Threshold, value, value, value, 0);
            std::shared_ptr<epiJobHandle> jobHandle = epiJobScheduler::GetInstance().Schedule(std::move(job));
            if (epiEventLoop* eventLoop = epiEventLoop::GetMainEventLoop())
            {
                if (m_PeriodicalTaskR != nullptr)
                {
                    m_PeriodicalTaskR->Cancel();
                }

                m_PeriodicalTaskR = &eventLoop->AddPeriodicalTask([this, jobHandle, value]()
                {
                    epiBool keepAlive = true;

                    if (jobHandle->IsCompleted())
                    {
                        if (JobThreshold* job = jobHandle->GetJob<JobThreshold>())
                        {
                            SetImageR(job->GetImage());

                            epiPropertyChangedCheckAndTrigger(ThresholdR, value);
                        }
                        keepAlive = false;
                    }

                    return keepAlive;
                }, 60ms);
            }

            if (GetIsThresholdSynchronized())
            {
                mmImage imageG = image->ToGrayScaleG();
                imageG.Threshold(value, value, value);

                SetImageG(imageG);

                epiPropertyChangedCheckAndTrigger(ThresholdG, value);

                mmImage imageB = image->ToGrayScaleB();
                imageB.Threshold(value, value, value);

                SetImageB(imageB);

                epiPropertyChangedCheckAndTrigger(ThresholdB, value);
            }
        }
    }
}

void mmVMImageThreshold::SetThresholdG_Callback(epiU8 value)
{
    if (!epiEqual(GetThresholdG(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageG = image->ToGrayScaleG();
            imageG.Threshold(value, value, value);

            SetImageG(imageG);

            if (GetIsThresholdSynchronized())
            {
                mmImage imageR = image->ToGrayScaleR();
                imageR.Threshold(value, value, value);

                SetImageR(imageR);

                epiPropertyChangedCheckAndTrigger(ThresholdR, value);

                mmImage imageB = image->ToGrayScaleB();
                imageB.Threshold(value, value, value);

                SetImageB(imageB);

                epiPropertyChangedCheckAndTrigger(ThresholdB, value);
            }
        }
    }

    epiPropertyChangedCheckAndTrigger(ThresholdG, value);
}

void mmVMImageThreshold::SetThresholdB_Callback(epiU8 value)
{
    if (!epiEqual(GetThresholdB(), value))
    {
        if (mmImage* image = GetImageSrc())
        {
            mmImage imageB = image->ToGrayScaleB();
            imageB.Threshold(value, value, value);

            SetImageB(imageB);

            if (GetIsThresholdSynchronized())
            {
                mmImage imageR = image->ToGrayScaleR();
                imageR.Threshold(value, value, value);

                SetImageR(imageR);

                epiPropertyChangedCheckAndTrigger(ThresholdR, value);

                mmImage imageG = image->ToGrayScaleG();
                imageG.Threshold(value, value, value);

                SetImageG(imageG);

                epiPropertyChangedCheckAndTrigger(ThresholdG, value);
            }
        }
    }

    epiPropertyChangedCheckAndTrigger(ThresholdB, value);
}

void mmVMImageThreshold::SetIsThresholdSynchronized_Callback(epiBool value)
{
    epiPropertyChangedCheckAndTrigger(IsThresholdSynchronized, value);
}

void mmVMImageThreshold::SetImageSrc_Internal(mmImage* imageSrc)
{
    if (mmImage* image = GetImageSrc())
    {
        SetImageR(image->ToGrayScaleR());
        SetImageG(image->ToGrayScaleG());
        SetImageB(image->ToGrayScaleB());
    }
}

mmImage mmVMImageThreshold::GetImageTgt_Internal() const
{
    mmImage to;

    const mmImage& r = GetImageR();
    const mmImage& g = GetImageG();
    const mmImage& b = GetImageB();

    epiAssert(r.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);
    epiAssert(g.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);
    epiAssert(b.GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);

    epiAssert(r.GetWidth() == g.GetWidth() && g.GetWidth() == b.GetWidth());
    epiAssert(r.GetHeight() == g.GetHeight() && g.GetHeight() == b.GetHeight());
    epiAssert(r.GetBPP() == g.GetBPP() && g.GetBPP() == b.GetBPP());
    epiAssert(r.GetBPC() == g.GetBPC() && g.GetBPC() == b.GetBPC());

    to.SetWidth(r.GetWidth());
    to.SetHeight(r.GetHeight());
    to.SetPixelFormat(mmImagePixelFormat::R8G8B8);
    epiArray<epiU8>& toData = to.GetData();
    toData.Resize(r.GetData().Size() * 3);

    for (epiU32 i = 0; i < toData.Size() / 3; ++i)
    {
        toData[i * 3 + 0] = r.GetData()[i];
        toData[i * 3 + 1] = g.GetData()[i];
        toData[i * 3 + 2] = b.GetData()[i];
    }

    return to;
}

EPI_NAMESPACE_END()
