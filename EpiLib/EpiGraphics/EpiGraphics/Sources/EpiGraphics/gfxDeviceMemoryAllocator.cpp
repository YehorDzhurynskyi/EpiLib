EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDeviceMemoryAllocator.h"
#include "EpiGraphics/gfxDeviceMemoryAllocator.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxDeviceMemoryAllocatorImpl.h"

#include "EpiGraphics/gfxDevice.h"

EPI_NAMESPACE_BEGIN()

gfxDeviceMemoryAllocationCreateInfo gfxDeviceMemoryAllocationCreateInfo::FromUsage(gfxDeviceMemoryAllocationCreateMask createMask,
                                                                                   gfxDeviceMemoryAllocationUsage usage)
{
    gfxDeviceMemoryAllocationCreateInfo info{};
    info.SetCreateMask(createMask);
    info.SetUsage(usage);

    return info;
}

gfxDeviceMemoryAllocationCreateInfo gfxDeviceMemoryAllocationCreateInfo::FromPropertiesFlags(gfxDeviceMemoryAllocationCreateMask createMask,
                                                                                             gfxDeviceMemoryPropertyMask requiredPropertiesMask,
                                                                                             gfxDeviceMemoryPropertyMask preferredPropertiesMask)
{
    gfxDeviceMemoryAllocationCreateInfo info{};
    info.SetCreateMask(createMask);
    info.SetRequiredPropertiesMask(requiredPropertiesMask);
    info.SetPreferredPropertiesMask(preferredPropertiesMask);

    return info;
}

gfxDeviceMemoryAllocation::gfxDeviceMemoryAllocation(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxDeviceMemoryAllocation::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

const gfxDeviceMemoryAllocator& gfxDeviceMemoryAllocation::GetAllocator_Callback() const
{
    epiAssert(HasImpl());

    return m_Impl->GetAllocator();
}

gfxDeviceMemoryAllocationBuffer::gfxDeviceMemoryAllocationBuffer(const std::shared_ptr<Impl>& impl, gfxBuffer&& buffer)
    : gfxDeviceMemoryAllocation{impl}
    , m_Buffer{std::move(buffer)}
{
}

gfxDeviceMemoryAllocationImage::gfxDeviceMemoryAllocationImage(const std::shared_ptr<Impl>& impl, gfxImage&& image)
    : gfxDeviceMemoryAllocation{impl}
    , m_Image{std::move(image)}
{
}

gfxDeviceMemoryAllocator::gfxDeviceMemoryAllocator(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxDeviceMemoryAllocator::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

const gfxDevice& gfxDeviceMemoryAllocator::GetDevice_Callback() const
{
    return m_Impl->GetDevice();
}

EPI_NAMESPACE_END()
