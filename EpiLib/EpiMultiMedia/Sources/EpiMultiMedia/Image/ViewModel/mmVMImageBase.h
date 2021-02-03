#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/Property/epiIPropertyChangedHandler.h"
#include "EpiCore/MT/EventLoop/epiEventLoopPeriodicalTask.h"
#include "EpiCore/MT/EventLoop/epiEventLoop.h"
#include "EpiCore/MT/JobSystem/epiJobScheduler.h"
#include "EpiCore/MT/JobSystem/epiJobCallback.h"

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

// TODO: add const to `mmImage* m_ImageSrc{nullptr};`

protected:
    template<typename Callback, typename ...Args>
    void UpdateImage(epiEventLoopPeriodicalTask*& task,
                     void(mmVMImageBase::*SetImage)(const mmImage&),
                     Callback Callback,
                     Args... args);

    virtual void SetImageSrc_Internal(mmImage* imageSrc) {}
    virtual mmImage GetImageTgt_Internal() const = 0;
};

template<typename Callback, typename ...Args>
void mmVMImageBase::UpdateImage(epiEventLoopPeriodicalTask*& task,
                                void(mmVMImageBase::*SetImage)(const mmImage&),
                                Callback callback,
                                Args... args)
{
    epiProfileFunction;

    if (mmImage* image = GetImageSrc())
    {
        auto job = std::make_unique<epiJobCallback<Callback, Args...>>(callback, std::forward<Args>(args)...);
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
                    if (auto job = jobHandle->GetJob<epiJobCallback<Callback, Args...>>())
                    {
                        // TODO: handle bug: `this` isn't guaranteed to exist
                        (this->*SetImage)(job->GetResult());
                    }

                    keepAlive = false;
                }

                return keepAlive;
            }, 10ms);
        }
    }
}

EPI_NAMESPACE_END()
