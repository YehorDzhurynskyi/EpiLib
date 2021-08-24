EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxImage.h"
#include "EpiGraphics/gfxImage.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxImageImpl.h"

EPI_NAMESPACE_BEGIN()

gfxImage::gfxImage(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxImage::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

const gfxDevice& gfxImage::GetDevice_Callback() const
{
    epiAssert(HasImpl());

    return m_Impl->GetDevice();
}

EPI_NAMESPACE_END()
