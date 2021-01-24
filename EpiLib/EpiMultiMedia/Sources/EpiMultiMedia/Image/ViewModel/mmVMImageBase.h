#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"
#include "EpiCore/MT/EventLoop/epiEventLoopPeriodicalTask.h"
#include "EpiCore/MT/EventLoop/epiEventLoop.h"
#include "EpiCore/MT/JobSystem/epiJobScheduler.h"

#include "EpiMultimedia/Image/mmJobImage.h"
#include "EpiMultimedia/Image/mmImage.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageBase : public Object, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(mmVMImageBase)

EPI_GENHIDDEN_mmVMImageBase()

public:
    constexpr static epiMetaTypeID TypeID{0x1ae604c8};

    enum mmVMImageBase_PIDs
    {
        PID_ImageSrc = 0xfa9be066,
        PID_ImageTgt = 0x4bb29530,
        PID_COUNT = 2
    };

protected:
    void SetImageSrc_Callback(mmImage* value);
    mmImage GetImageTgt_Callback() const;

protected:
    mmImage* m_ImageSrc{nullptr};

EPI_GENREGION_END(mmVMImageBase)

protected:
    template<typename ...Args>
    void UpdateImage(epiEventLoopPeriodicalTask*& task,
                     void(mmVMImageBase::*SetImage)(const mmImage&),
                     mmImage(mmImage::*Convert)() const,
                     void(mmImage::*Callback)(Args...),
                     Args... args);

    virtual void SetImageSrc_Internal(mmImage* imageSrc) {}
    virtual mmImage GetImageTgt_Internal() const = 0;
};

template<typename ...Args>
void mmVMImageBase::UpdateImage(epiEventLoopPeriodicalTask*& task,
                                void(mmVMImageBase::*SetImage)(const mmImage&),
                                mmImage(mmImage::*Convert)() const,
                                void(mmImage::*Callback)(Args...),
                                Args... args)
{
    if (mmImage* image = GetImageSrc())
    {
        std::unique_ptr<mmJobImage<Args...>> job = std::make_unique<mmJobImage<Args...>>((image->*Convert)(), Callback, std::forward<Args>(args)...);
        std::shared_ptr<epiJobHandle> jobHandle = epiJobScheduler::GetInstance().Schedule(std::move(job));
        if (epiEventLoop* eventLoop = epiEventLoop::GetMainEventLoop())
        {
            if (task != nullptr)
            {
                task->Cancel();
            }

            task = &eventLoop->AddPeriodicalTask([this, jobHandle, SetImage]()
            {
                epiBool keepAlive = true;

                if (jobHandle->IsCompleted())
                {
                    if (mmJobImage<Args...>* job = jobHandle->GetJob<mmJobImage<Args...>>())
                    {
                        (this->*SetImage)(job->GetImage());
                    }

                    keepAlive = false;
                }

                return keepAlive;
            }, 60ms);
        }
    }
}

EPI_NAMESPACE_END()
