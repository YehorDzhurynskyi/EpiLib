EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDeviceMemory.h"
#include "EpiGraphics/gfxDeviceMemory.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxDeviceMemoryImpl.h"

EPI_NAMESPACE_BEGIN()

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

gfxDeviceMemory::Mapping gfxDeviceMemory::Map(epiSize_t size, epiSize_t offset)
{
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
