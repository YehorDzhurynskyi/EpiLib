EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedGlyph.h"
#include "EpiGraphics/Text/gfxTextRenderedGlyph.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxTextRenderedGlyph* gfxTextRenderedABC::GlyphOf(epiWChar ch)
{
    auto it = m_ABC.find(ch);
    if (it == m_ABC.end())
    {
        // TODO: log
        epiAssert(false, "Failed to get uv coords of ch!");
        return nullptr;
    }
    return &it->second;
}

EPI_NAMESPACE_END()
