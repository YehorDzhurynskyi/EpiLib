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

epiBool gfxDeviceMemoryAllocation::Mapping::Init(const std::shared_ptr<Impl>& deviceMemoryAllocationImpl)
{
    if (deviceMemoryAllocationImpl == nullptr)
    {
        epiLogError("Failed to initialize DeviceMemoryAllocation mapping! The provided DeviceMemoryAllocation has no implementation!");
        return false;
    }

    m_DeviceMemoryAllocationImpl = deviceMemoryAllocationImpl;
    m_DeviceMemoryAllocationImpl->Map();

    return true;
}

gfxDeviceMemoryAllocation::Mapping::Mapping(Mapping&& rhs)
{
    m_DeviceMemoryAllocationImpl = std::move(rhs.m_DeviceMemoryAllocationImpl);

    rhs.m_DeviceMemoryAllocationImpl.reset();
}

gfxDeviceMemoryAllocation::Mapping& gfxDeviceMemoryAllocation::Mapping::operator=(Mapping&& rhs)
{
    if (this != &rhs)
    {
        m_DeviceMemoryAllocationImpl = std::move(rhs.m_DeviceMemoryAllocationImpl);

        rhs.m_DeviceMemoryAllocationImpl.reset();
    }

    return *this;
}

gfxDeviceMemoryAllocation::Mapping::~Mapping()
{
    if (IsMapped())
    {
        m_DeviceMemoryAllocationImpl->Unmap();
    }
}

epiBool gfxDeviceMemoryAllocation::Mapping::IsMapped() const
{
    return m_DeviceMemoryAllocationImpl != nullptr && m_DeviceMemoryAllocationImpl->IsMapped();
}

gfxDeviceMemoryAllocation::Mapping::operator epiBool() const
{
    return IsMapped();
}

epiByte* gfxDeviceMemoryAllocation::Mapping::Mapped()
{
    if (m_DeviceMemoryAllocationImpl == nullptr)
    {
        epiLogError("Failed to retrieve mapped pointer! Calling object has no implementation!");
        return nullptr;
    }

    return m_DeviceMemoryAllocationImpl->Mapped();
}

gfxDeviceMemoryAllocation::gfxDeviceMemoryAllocation(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxDeviceMemoryAllocation::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxDeviceMemoryAllocation::IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const
{
    if (!HasImpl())
    {
        epiLogError("Failed to query DeviceMemoryProperty status! Calling object has no implementation!");
        return false;
    }

    return m_Impl->IsPropertyEnabled(mask);
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

gfxDeviceMemoryAllocation::Mapping gfxDeviceMemoryAllocation::Map()
{
    // TODO: check whether the following memory is already mapped
    // Mapping the same VkDeviceMemory block multiple times is illegal, but only
    // one mapping at a time is allowed.This includes mapping disjoint regions.

    // TODO: add warning message if Map is used with a non-coherent memory to call flush:
    // - Use a memory heap that is host coherent, indicated with VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    // - Call vkFlushMappedMemoryRanges after writing to the mapped memory, and call vkInvalidateMappedMemoryRanges before reading from the mapped memory
    //
    // Add `epiBool flush = true` parameter:
    // call vkFlushMappedMemoryRanges if memory isn't coherent
    // Regions of memory specified for flush/invalidate must be aligned to VkPhysicalDeviceLimits::nonCoherentAtomSize.
    // This is automatically ensured by the library. In any memory type that is HOST_VISIBLE but not HOST_COHERENT,
    // all allocations within blocks are aligned to this value, so their offsets are always multiply of nonCoherentAtomSize
    // and two different allocations never share same "line" of this size.

    Mapping mapping;

    // TODO: implement flush/invalidate logic
    epiAssert(IsPropertyEnabled(gfxDeviceMemoryPropertyMask_HostCoherent));

    if (!GetIsMappable())
    {
        epiLogError("Failed to map DeviceMemory! The memory isn't mappable!");
        return mapping;
    }

    if (!mapping.Init(m_Impl))
    {
        epiLogError("Failed to map DeviceMemory! The mapping initialization has failed!");
        return mapping;
    }

    return mapping;
}

const gfxDeviceMemoryAllocator& gfxDeviceMemoryAllocation::GetAllocator_Callback() const
{
    epiAssert(HasImpl());

    return m_Impl->GetAllocator();
}

epiBool gfxDeviceMemoryAllocation::GetIsMappable_Callback() const
{
    return IsPropertyEnabled(gfxDeviceMemoryPropertyMask_HostVisible);
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
