EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxPhysicalDevice.h"
#include "EpiGraphics/gfxPhysicalDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxPhysicalDeviceImpl.h"

EPI_NAMESPACE_BEGIN()

gfxPhysicalDevice::gfxPhysicalDevice(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
    epiArray<gfxQueueFamilyDescriptor>& queueFamilyDescriptors = GetQueueFamilyDescriptors();

    queueFamilyDescriptors.Clear();
    queueFamilyDescriptors.Reserve(m_Impl->GetQueueFamilyDescriptors().Size());

    std::transform(m_Impl->GetQueueFamilyDescriptors().begin(),
                   m_Impl->GetQueueFamilyDescriptors().end(),
                   std::back_inserter(queueFamilyDescriptors),
                   [](const std::shared_ptr<gfxQueueFamilyDescriptor::Impl>& queueFamilyDescriptorImpl)
    {
        return gfxQueueFamilyDescriptor(queueFamilyDescriptorImpl);
    });
}

epiBool gfxPhysicalDevice::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiFloat gfxPhysicalDevice::GetMaxSamplerAnisotropy() const
{
    return m_Impl->GetMaxSamplerAnisotropy();
}

gfxFormatProperties gfxPhysicalDevice::FormatPropertiesFor(gfxFormat format) const
{
    return m_Impl->FormatPropertiesFor(format);
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
