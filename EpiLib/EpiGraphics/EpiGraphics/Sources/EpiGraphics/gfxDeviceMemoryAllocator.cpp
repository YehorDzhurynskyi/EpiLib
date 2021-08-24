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

epiBool gfxDeviceMemoryAllocation::BindBuffer(const gfxBuffer& buffer)
{
    if (!HasImpl())
    {
        epiLogError("Failed to bind Buffer! Calling object has no implementation!");
        return false;
    }

    if (!buffer.HasImpl())
    {
        epiLogError("Failed to bind Buffer! The provided Buffer has no implementation!");
        return false;
    }

    return m_Impl->BindBuffer(buffer);
}

epiBool gfxDeviceMemoryAllocation::BindImage(const gfxImage& image)
{
    if (!HasImpl())
    {
        epiLogError("Failed to bind Image! Calling object has no implementation!");
        return false;
    }

    if (!image.HasImpl())
    {
        epiLogError("Failed to bind Buffer! The provided Image has no implementation!");
        return false;
    }

    return m_Impl->BindImage(image);
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

std::optional<gfxDeviceMemoryAllocationBuffer> gfxDeviceMemoryAllocator::CreateBuffer(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                                      const gfxBufferCreateInfo& bufferInfo)
{
    if (!HasImpl())
    {
        epiLogError("Failed to create Buffer! Calling object has no implementation!");
        return std::nullopt;
    }

    return m_Impl->CreateBuffer(allocationInfo, bufferInfo);
}

std::optional<gfxDeviceMemoryAllocationImage> gfxDeviceMemoryAllocator::CreateImage(const gfxDeviceMemoryAllocationCreateInfo& allocationInfo,
                                                                                    const gfxImageCreateInfo& imageInfo)
{
    if (!HasImpl())
    {
        epiLogError("Failed to create Image! Calling object has no implementation!");
        return std::nullopt;
    }

    return m_Impl->CreateImage(allocationInfo, imageInfo);
}

std::optional<gfxDeviceMemoryAllocation> gfxDeviceMemoryAllocator::AllocateBuffer(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                                  const gfxBuffer& buffer)
{
    if (!HasImpl())
    {
        epiLogError("Failed to allocate Buffer! Calling object has no implementation!");
        return std::nullopt;
    }

    if (!buffer.HasImpl())
    {
        epiLogError("Failed to allocate Buffer! The provided Buffer has no implementation!");
        return std::nullopt;
    }

    return m_Impl->AllocateBuffer(info, buffer);
}

std::optional<gfxDeviceMemoryAllocation> gfxDeviceMemoryAllocator::AllocateImage(const gfxDeviceMemoryAllocationCreateInfo& info,
                                                                                 const gfxImage& image)
{
    if (!HasImpl())
    {
        epiLogError("Failed to allocate Buffer! Calling object has no implementation!");
        return std::nullopt;
    }

    if (!image.HasImpl())
    {
        epiLogError("Failed to allocate Image! The provided Image has no implementation!");
        return std::nullopt;
    }

    return m_Impl->AllocateImage(info, image);
}

const gfxDevice& gfxDeviceMemoryAllocator::GetDevice_Callback() const
{
    return m_Impl->GetDevice();
}

EPI_NAMESPACE_END()
