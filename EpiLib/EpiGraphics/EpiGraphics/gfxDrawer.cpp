#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDrawer.h"
#include "EpiGraphics/gfxDrawer.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxDrawer::gfxDrawer(const gfxCamera& camera)
    : m_Camera(camera)
{}

EPI_NAMESPACE_END()
