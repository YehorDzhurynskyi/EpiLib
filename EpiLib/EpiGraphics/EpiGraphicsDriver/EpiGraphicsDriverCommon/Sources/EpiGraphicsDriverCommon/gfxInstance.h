#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxInstance.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class gfxInstance : public Object
{
EPI_GENREGION_BEGIN(gfxInstance)

EPI_GENHIDDEN_gfxInstance()

public:
    constexpr static epiMetaTypeID TypeID{0x5b8e2b4c};

    enum gfxInstance_PIDs
    {
        PID_PhysicalDevices = 0x16b8cc07,
        PID_COUNT = 1
    };

protected:
    epiArray<gfxPhysicalDevice> m_PhysicalDevices{};

EPI_GENREGION_END(gfxInstance)

public:
    class Impl;

public:
    gfxInstance() = default;
    explicit gfxInstance(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    std::optional<gfxSurface> CreateSurface(const gfxWindow& window) const;
    std::optional<gfxDevice> CreateDevice(const gfxDeviceCreateInfo& info) const;

    epiBool IsExtensionSupported(gfxInstanceExtension extension) const;
    epiBool IsExtensionEnabled(gfxInstanceExtension extension) const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
