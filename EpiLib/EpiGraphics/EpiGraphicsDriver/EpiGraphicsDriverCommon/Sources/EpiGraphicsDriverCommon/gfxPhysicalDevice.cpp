EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

gfxPhysicalDevice::gfxPhysicalDevice(const std::shared_ptr<internalgfx::gfxPhysicalDeviceImpl>& impl)
    : m_Impl{impl}
{
}

std::optional<gfxDevice> gfxPhysicalDevice::CreateDevice(gfxQueueDescriptorList& queueDescriptorList,
                                                         const epiArray<gfxPhysicalDeviceExtension>& extensionsRequired,
                                                         const epiArray<gfxPhysicalDeviceFeature>& featuresRequired) const
{
    std::optional<gfxDevice> device;

    if (std::shared_ptr<internalgfx::gfxDeviceImpl> impl = m_Impl->CreateDevice(queueDescriptorList, extensionsRequired, featuresRequired))
    {
        device = gfxDevice(std::move(impl));
    }

    return device;
}

epiString gfxPhysicalDevice::GetName_Callback() const
{
    return m_Impl->GetName();
}

gfxPhysicalDeviceType gfxPhysicalDevice::GetType_Callback() const
{
    return m_Impl->GetType();
}

epiBool gfxPhysicalDevice::IsExtensionSupported(gfxPhysicalDeviceExtension extension) const
{
    return m_Impl->IsExtensionSupported(extension);
}

epiBool gfxPhysicalDevice::IsFeatureSupported(gfxPhysicalDeviceFeature feature) const
{
    return m_Impl->IsFeatureSupported(feature);
}

epiBool gfxPhysicalDevice::IsQueueTypeSupported(gfxQueueType mask) const
{
    return m_Impl->IsQueueTypeSupported(mask);
}

EPI_NAMESPACE_END()
