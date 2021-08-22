#pragma once

#include "EpiGraphics/gfxInstance.h"

EPI_NAMESPACE_BEGIN()

class gfxInstance::Impl : public std::enable_shared_from_this<gfxInstance::Impl>
{
public:
    static std::shared_ptr<gfxInstance::Impl> ExtractImpl(const gfxInstance& instance) { return instance.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual std::shared_ptr<gfxSurface::Impl> CreateSurface(const gfxWindow& window) const = 0;

    virtual epiBool IsExtensionSupported(gfxInstanceExtension extension) const = 0;
    virtual epiBool IsExtensionEnabled(gfxInstanceExtension extension) const = 0;

    const epiArray<std::shared_ptr<gfxPhysicalDevice::Impl>>& GetPhysicalDevices() const { return m_PhysicalDevices; }

protected:
    epiArray<std::shared_ptr<gfxPhysicalDevice::Impl>> m_PhysicalDevices;
};

EPI_NAMESPACE_END()
