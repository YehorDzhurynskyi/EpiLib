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

gfxDeviceMemory::Mapping::Mapping(const std::shared_ptr<Impl>& impl, epiSize_t size, epiSize_t offset)
    : m_Impl{impl}
{
    if (m_Impl)
    {
        m_Data = m_Impl->Map(size, offset);
    }
}

gfxDeviceMemory::Mapping::~Mapping()
{
    if (IsMapped())
    {
        m_Impl->Unmap();
    }
}

epiBool gfxDeviceMemory::Mapping::IsMapped() const
{
    return m_Impl != nullptr && m_Data != nullptr;
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
    //
    // check whether memory is host-local
    return Mapping(m_Impl, size, offset);
}

EPI_NAMESPACE_END()
