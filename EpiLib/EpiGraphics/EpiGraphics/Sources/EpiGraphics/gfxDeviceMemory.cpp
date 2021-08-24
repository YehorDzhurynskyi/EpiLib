EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDeviceMemory.h"
#include "EpiGraphics/gfxDeviceMemory.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxDeviceMemoryImpl.h"

EPI_NAMESPACE_BEGIN()

gfxBindBufferMemoryInfo gfxBindBufferMemoryInfo::FromBuffer(const gfxBuffer& buffer, epiSize_t offset)
{
    gfxBindBufferMemoryInfo info{};
    info.SetBuffer(buffer);
    info.SetOffset(offset);

    return info;
}

gfxBindImageMemoryInfo gfxBindImageMemoryInfo::FromImage(const gfxImage& image, epiSize_t offset)
{
    gfxBindImageMemoryInfo info{};
    info.SetImage(image);
    info.SetOffset(offset);

    return info;
}

epiBool gfxDeviceMemory::Mapping::Init(const std::shared_ptr<Impl>& deviceMemoryImpl, epiSize_t size, epiSize_t offset)
{
    if (deviceMemoryImpl == nullptr)
    {
        epiLogError("Failed to initialize DeviceMemory mapping! The provided DeviceMemory has no implementation!");
        return false;
    }

    m_DeviceMemoryImpl = deviceMemoryImpl;
    m_Data = m_DeviceMemoryImpl->Map(size, offset);

    return true;
}

gfxDeviceMemory::Mapping::~Mapping()
{
    if (IsMapped())
    {
        m_DeviceMemoryImpl->Unmap();
    }
}

epiBool gfxDeviceMemory::Mapping::IsMapped() const
{
    return m_DeviceMemoryImpl != nullptr && m_Data != nullptr;
}

gfxDeviceMemory::Mapping::operator epiBool() const
{
    return IsMapped();
}

epiByte* gfxDeviceMemory::Mapping::Data()
{
    return m_Data;
}

gfxDeviceMemory::gfxDeviceMemory(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxDeviceMemory::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxDeviceMemory::IsPropertyEnabled(gfxDeviceMemoryPropertyMask mask) const
{
    if (!HasImpl())
    {
        epiLogError("Failed to query DeviceMemoryProperty status! Calling object has no implementation!");
        return false;
    }

    return m_Impl->IsPropertyEnabled(mask);
}

epiBool gfxDeviceMemory::BindBuffer(const gfxBindBufferMemoryInfo& info)
{
    if (!HasImpl())
    {
        epiLogError("Failed to bind Buffer! Calling object has no implementation!");
        return false;
    }

    if (!info.GetBuffer().HasImpl())
    {
        epiLogError("Failed to bind Buffer! The provided Buffer has no implementation!");
        return false;
    }

    return m_Impl->BindBuffer(info);
}

epiBool gfxDeviceMemory::BindImage(const gfxBindImageMemoryInfo& info)
{
    if (!HasImpl())
    {
        epiLogError("Failed to bind Image! Calling object has no implementation!");
        return false;
    }

    if (!info.GetImage().HasImpl())
    {
        epiLogError("Failed to bind Image! The provided Image has no implementation!");
        return false;
    }

    return m_Impl->BindImage(info);
}

gfxDeviceMemory::Mapping gfxDeviceMemory::Map(epiSize_t size, epiSize_t offset)
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

    if (!IsPropertyEnabled(gfxDeviceMemoryPropertyMask_HostVisible))
    {
        epiLogError("Failed to map DeviceMemory! The memory couldn't be mapped on non-host-visible DeviceMemory!");
        return mapping;
    }

    if (!mapping.Init(m_Impl, size, offset))
    {
        epiLogError("Failed to map DeviceMemory! The mapping initialization has failed!");
        return mapping;
    }

    return mapping;
}

EPI_NAMESPACE_END()
