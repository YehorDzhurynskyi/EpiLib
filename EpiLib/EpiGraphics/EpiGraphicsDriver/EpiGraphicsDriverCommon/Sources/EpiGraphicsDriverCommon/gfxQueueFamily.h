#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueFamily.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueFamilyImpl;

} // internalgfx

class gfxQueueFamily : public Object
{
EPI_GENREGION_BEGIN(gfxQueueFamily)

EPI_GENHIDDEN_gfxQueueFamily()

public:
    constexpr static epiMetaTypeID TypeID{0x25e95f0c};

    enum gfxQueueFamily_PIDs
    {
        PID_QueueTypeSupported = 0xd8209495,
        PID_QueueCount = 0xf330505b,
        PID_COUNT = 2
    };

protected:
    gfxQueueType GetQueueTypeSupported_Callback() const;
    epiSize_t GetQueueCount_Callback() const;

EPI_GENREGION_END(gfxQueueFamily)

public:
    friend class gfxDevice;

public:
    gfxQueueFamily() = default;
    gfxQueueFamily(internalgfx::gfxQueueFamilyImpl* impl);
    gfxQueueFamily(const gfxQueueFamily & rhs) = delete;
    gfxQueueFamily& operator=(const gfxQueueFamily & rhs) = delete;
    gfxQueueFamily(gfxQueueFamily&& rhs);
    gfxQueueFamily& operator=(gfxQueueFamily&& rhs);
    ~gfxQueueFamily();

    epiBool HasImpl() const;

protected:
    internalgfx::gfxQueueFamilyImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
