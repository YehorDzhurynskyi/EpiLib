EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxSurface.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSurface::gfxSurface(internalgfx::gfxSurfaceImpl* impl)
    : m_Impl{impl}
{
}

gfxSurface::gfxSurface(gfxSurface&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxSurface& gfxSurface::operator=(gfxSurface&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxSurface::~gfxSurface()
{
    delete m_Impl;
}

gfxQueueDescriptor gfxSurface::CreateQueueDescriptor(const epiArray<epiFloat>& priorities, gfxQueueType type) const
{
    gfxQueueDescriptor desc;
    desc.SetType(epiMask(gfxQueueType_Graphics, type));
    desc.SetPresentSurface(m_Impl);

    for (const epiFloat priority : priorities)
    {
        desc.AddDesiredQueue(priority);
    }

    return desc;
}

EPI_NAMESPACE_END()
