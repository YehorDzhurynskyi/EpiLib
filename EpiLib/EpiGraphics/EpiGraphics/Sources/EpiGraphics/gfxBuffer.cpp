EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxBuffer.h"
#include "EpiGraphics/gfxBuffer.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxBufferImpl.h"

EPI_NAMESPACE_BEGIN()

gfxBuffer::gfxBuffer(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxBuffer::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

const gfxDevice& gfxBuffer::GetDevice_Callback() const
{
    epiAssert(HasImpl());

    return m_Impl->GetDevice();
}

EPI_NAMESPACE_END()
