EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDeviceMemoryAllocator.h"
#include "EpiGraphics/gfxDeviceMemoryAllocator.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxDeviceMemoryAllocator::gfxDeviceMemoryAllocator(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxDeviceMemoryAllocator::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
