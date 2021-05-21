EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDeviceMemory.h"
#include "EpiGraphicsDriverCommon/gfxDeviceMemory.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxDeviceMemory::gfxDeviceMemory(const std::shared_ptr<internalgfx::gfxDeviceMemoryImpl>& impl)
    : m_Impl{impl}
{
}

epiByte* gfxDeviceMemory::Map(epiSize_t size, epiSize_t offset)
{
    // TODO: add warning message if Map is used with a non-coherent memory to call flush:
    // - Use a memory heap that is host coherent, indicated with VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    // - Call vkFlushMappedMemoryRanges after writing to the mapped memory, and call vkInvalidateMappedMemoryRanges before reading from the mapped memory
    return m_Impl->Map(size, offset);
}

void gfxDeviceMemory::Unmap()
{
    m_Impl->Unmap();
}

EPI_NAMESPACE_END()
