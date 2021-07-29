EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Text/drwTextRenderedGlyph.h"
#include "EpiDrawer/Text/drwTextRenderedGlyph.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

drwTextRenderedGlyph* drwTextRenderedABC::GlyphOf(epiWChar ch)
{
    auto it = m_ABC.find(ch);
    if (it == m_ABC.end())
    {
        // TODO: mention `ch` value in log in some way
        epiLogError("Failed to get uv coords of `ch`!");
        return nullptr;
    }
    return &it->second;
}

EPI_NAMESPACE_END()
