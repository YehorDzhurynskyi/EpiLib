EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxBuffer.h"
#include "EpiGraphicsDriverCommon/gfxBuffer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxBuffer::gfxBuffer(const std::shared_ptr<internalgfx::gfxBufferImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
