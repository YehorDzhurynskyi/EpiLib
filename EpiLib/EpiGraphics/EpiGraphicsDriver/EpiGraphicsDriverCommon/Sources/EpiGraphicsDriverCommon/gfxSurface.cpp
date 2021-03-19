EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxSurface.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSurface::gfxSurface(internalgfx::gfxSurfaceImpl* impl)
    : m_Impl{impl}
{
}

gfxSurface::gfxSurface(gfxSurface&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxSurface& gfxSurface::operator=(gfxSurface&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxSurface::~gfxSurface()
{
    delete m_Impl;
}

gfxQueueDescriptor gfxSurface::CreateQueueDescriptor(const epiArray<epiFloat>& priorities, gfxQueueType type) const
{
    gfxQueueDescriptor desc;
    desc.SetType(epiMask(gfxQueueType_Graphics, type));
    desc.SetPresentSurface(m_Impl);

    for (const epiFloat priority : priorities)
    {
        desc.AddDesiredQueue(priority);
    }

    return desc;
}

std::optional<gfxSwapChain> gfxSurface::CreateSwapChain(const gfxDevice& device,
                                                        const gfxSurfaceCapabilities& capabilities,
                                                        const gfxSurfaceFormat& format,
                                                        gfxSurfacePresentMode presentMode,
                                                        const epiSize2u& extent)
{
    epiAssert(m_Impl != nullptr && device.m_Impl != nullptr);

    std::optional<gfxSwapChain> swapchain;

    if (std::unique_ptr<internalgfx::gfxSwapChainImpl> impl = m_Impl->CreateSwapChain(*device.m_Impl, capabilities, format, presentMode, extent))
    {
        swapchain = gfxSwapChain(impl.release());
    }

    return swapchain;
}

epiBool gfxSurface::IsPresentSupportedFor(const gfxPhysicalDevice& device) const
{
    epiAssert(m_Impl != nullptr && device.m_Impl != nullptr);

    return m_Impl->IsPresentSupportedFor(*device.m_Impl);
}

gfxSurfaceCapabilities gfxSurface::GetCapabilitiesFor(const gfxPhysicalDevice& device) const
{
    epiAssert(m_Impl != nullptr && device.m_Impl != nullptr);

    return m_Impl->GetCapabilitiesFor(*device.m_Impl);
}

epiArray<gfxSurfaceFormat> gfxSurface::GetSupportedFormatsFor(const gfxPhysicalDevice& device) const
{
    epiAssert(m_Impl != nullptr && device.m_Impl != nullptr);

    return m_Impl->GetSupportedFormatsFor(*device.m_Impl);
}

epiArray<gfxSurfacePresentMode> gfxSurface::GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const
{
    epiAssert(m_Impl != nullptr && device.m_Impl != nullptr);

    return m_Impl->GetSupportedPresentModesFor(*device.m_Impl);
}

EPI_NAMESPACE_END()
