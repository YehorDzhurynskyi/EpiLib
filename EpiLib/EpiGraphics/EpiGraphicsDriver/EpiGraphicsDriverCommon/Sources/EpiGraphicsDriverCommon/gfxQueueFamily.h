#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueFamily.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueFamilyDescriptorImpl;
class gfxQueueFamilyImpl;

} // internalgfx

class gfxQueueFamilyDescriptor : public Object, epiPimpl<internalgfx::gfxQueueFamilyDescriptorImpl>
{
EPI_GENREGION_BEGIN(gfxQueueFamilyDescriptor)

EPI_GENHIDDEN_gfxQueueFamilyDescriptor()

public:
    constexpr static epiMetaTypeID TypeID{0xfa02338a};

    enum gfxQueueFamilyDescriptor_PIDs
    {
        PID_QueueTypeSupportedMask = 0xb25513f0,
        PID_QueueCount = 0xf330505b,
        PID_COUNT = 2
    };

protected:
    gfxQueueType GetQueueTypeSupportedMask_Callback() const;
    epiSize_t GetQueueCount_Callback() const;

EPI_GENREGION_END(gfxQueueFamilyDescriptor)

public:
    friend class gfxDevice;

public:
    gfxQueueFamilyDescriptor() = default;
    gfxQueueFamilyDescriptor(internalgfx::gfxQueueFamilyDescriptorImpl* impl);

public:
    epiBool IsQueueTypeSupported(gfxQueueType mask) const;
};

class gfxQueueFamily : public Object, public epiPimpl<internalgfx::gfxQueueFamilyImpl>
{
EPI_GENREGION_BEGIN(gfxQueueFamily)

EPI_GENHIDDEN_gfxQueueFamily()

public:
    constexpr static epiMetaTypeID TypeID{0x25e95f0c};

    enum gfxQueueFamily_PIDs
    {
        PID_Queues = 0xc86607a0,
        PID_COUNT = 1
    };

protected:
    epiArray<gfxQueue> m_Queues{};

EPI_GENREGION_END(gfxQueueFamily)

public:
    gfxQueueFamily() = default;
    gfxQueueFamily(internalgfx::gfxQueueFamilyImpl* impl, epiBool isOwner);
};

EPI_NAMESPACE_END()
