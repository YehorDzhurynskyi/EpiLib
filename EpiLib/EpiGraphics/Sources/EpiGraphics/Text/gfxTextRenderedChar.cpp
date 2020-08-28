#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedChar.h"
#include "EpiGraphics/Text/gfxTextRenderedChar.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

const gfxTextRenderedGlyph* gfxTextRenderedABC::GlyphOf(epiWChar ch) const
{
    auto it = m_CharMap.find(ch);
    if (it == m_CharMap.end())
    {
        // TODO: log
        epiAssert(false, "Failed to get uv coords of ch!");
        return nullptr;
    }
    return &it->second;
}

EPI_NAMESPACE_END()
