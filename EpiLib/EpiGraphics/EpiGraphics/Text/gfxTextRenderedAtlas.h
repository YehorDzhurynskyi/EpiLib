#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/Text/gfxTextRenderedAtlas.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/Text/gfxTextRendered.h"

EPI_NAMESPACE_BEGIN()

class gfxTextRenderedAtlas : public gfxTextRendered
{
    friend class gfxTextFace;
EPI_GENREGION_BEGIN(gfxTextRenderedAtlas)
public:
    EPI_GENHIDDEN_gfxTextRenderedAtlas()

    constexpr static MetaTypeID TypeID{0x6de735c2};

    enum gfxTextRenderedAtlas_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextRenderedAtlas)

public:
    epiBool UVBoxOf(epiRect2f& uv, epiWChar ch) const;

private:
    std::map<epiWChar, epiRect2f> m_CharMap;
};

EPI_NAMESPACE_END()
