EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/gfxContext.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxContext::gfxContext()
{
    GetDrawerText().CreateAtlas(m_TextManager.GetDefaultFace(), 18);
}

void gfxContext::SceneBegin()
{
    m_DrawerText.SceneBegin();
    m_DrawerPrimitive.SceneBegin();
}

void gfxContext::SceneEnd()
{
    if (gfxCamera* camera = GetCamera())
    {
        m_DrawerText.SceneEnd(*camera);
        m_DrawerPrimitive.SceneEnd(*camera);
    }
}

EPI_NAMESPACE_END()
