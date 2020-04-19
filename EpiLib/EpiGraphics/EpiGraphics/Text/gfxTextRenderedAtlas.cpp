#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

epiBool gfxTextRenderedAtlas::UVBoxOf(epiRect2f& uv, epiWChar ch) const
{
    auto it = m_CharMap.find(ch);
    if (it == m_CharMap.end())
    {
        // TODO: log
        epiAssert(false, "Failed to get uv coords of ch!");
        return false;
    }
    uv = it->second;
    return true;
}

EPI_NAMESPACE_END()
