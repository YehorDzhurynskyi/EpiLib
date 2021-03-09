#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriver/gfxDriver.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDriverImpl;

} // namespace internalgfx

class gfxDriver : public Object
{
EPI_GENREGION_BEGIN(gfxDriver)

EPI_GENHIDDEN_gfxDriver()

public:
    constexpr static epiMetaTypeID TypeID{0xb00017ff};

    enum gfxDriver_PIDs
    {
        PID_Backend = 0x4058f0ed,
        PID_COUNT = 1
    };

protected:
    void SetBackend_Callback(gfxDriverBackend value);

protected:
    gfxDriverBackend m_Backend{};

EPI_GENREGION_END(gfxDriver)

public:
    static gfxDriver& GetInstance();

public:
    gfxDriver(const gfxDriver& rhs) = delete;
    gfxDriver& operator=(const gfxDriver& rhs) = delete;
    gfxDriver(gfxDriver&& rhs) = delete;
    gfxDriver& operator=(gfxDriver&& rhs) = delete;
    ~gfxDriver();

    std::unique_ptr<gfxSurface> CreateSurface(const gfxWindow& window);

    std::optional<gfxPhysicalDevice> CreatePhysicalDevice(gfxPhysicalDeviceType deviceType,
                                                          gfxPhysicalDeviceExtension deviceExtensionMask,
                                                          gfxQueueType queueTypeMask,
                                                          const gfxPhysicalDeviceFeature* features = nullptr,
                                                          size_t featureCount = 0,
                                                          const gfxSurface* targetSurface = nullptr);

protected:
    gfxDriver() = default;

protected:
    internalgfx::gfxDriverImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
