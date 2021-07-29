EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/drwContext.h"
#include "EpiDrawer/drwContext.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

drwContext::drwContext()
{
    GetDrawerText().CreateAtlas(m_TextManager.GetDefaultFace(), 18);
}

void drwContext::SceneBegin()
{
    m_DrawerText.SceneBegin();
    m_DrawerPrimitive.SceneBegin();
}

void drwContext::SceneEnd()
{
    if (drwCamera* camera = GetCamera())
    {
        m_DrawerText.SceneEnd(*camera);
        m_DrawerPrimitive.SceneEnd(*camera);
    }
}

EPI_NAMESPACE_END()
