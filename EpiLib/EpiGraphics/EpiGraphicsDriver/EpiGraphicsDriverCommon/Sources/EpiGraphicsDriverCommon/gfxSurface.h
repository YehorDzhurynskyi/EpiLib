#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSurface.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImpl;
class gfxPhysicalDeviceImpl;

} // internalgfx

class gfxPhysicalDevice;
class gfxSurface : public Object
{
EPI_GENREGION_BEGIN(gfxSurface)

EPI_GENHIDDEN_gfxSurface()

public:
    constexpr static epiMetaTypeID TypeID{0x6eed7df8};

    enum gfxSurface_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxSurface)

public:
    gfxSurface() = default;
    gfxSurface(internalgfx::gfxSurfaceImpl* impl);
    gfxSurface(const gfxSurface& rhs) = delete;
    gfxSurface& operator=(const gfxSurface& rhs) = delete;
    gfxSurface(gfxSurface&& rhs);
    gfxSurface& operator=(gfxSurface&& rhs);
    ~gfxSurface();

public:
    gfxQueueDescriptor CreateQueueDescriptor(const epiArray<epiFloat>& priorities, gfxQueueType type = gfxQueueType{0}) const;

    friend epiBool PhysicalDeviceIsCompatibleWithSurfaceForPresentation(const gfxPhysicalDevice& device, const gfxSurface& surface);

protected:
    internalgfx::gfxSurfaceImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
