EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxBuffer.h"
#include "EpiGraphicsDriverCommon/gfxBuffer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxBuffer::gfxBuffer(const std::shared_ptr<gfxBuffer::Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxBuffer::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
