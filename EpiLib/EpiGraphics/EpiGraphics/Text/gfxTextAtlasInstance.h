#pragma once

EPI_GENREGION_BEGIN(include)
#include "Extern\EpiLib\EpiLib\EpiGraphics\EpiGraphics\Text\gfxTextAtlasInstance.hxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

class gfxTextAtlasInstance : public gfxTextInstance
{
    friend class gfxTextFont;
EPI_GENREGION_BEGIN(gfxTextAtlasInstance)
public:
    EPI_GENHIDDEN_gfxTextAtlasInstance()

    constexpr static MetaTypeID TypeID{0x9d1bad2f};

    enum gfxTextAtlasInstance_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextAtlasInstance)
};

EPI_NAMESPACE_END()
