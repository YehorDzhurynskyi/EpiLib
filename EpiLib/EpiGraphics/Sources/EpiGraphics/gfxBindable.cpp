EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxBindable.h"
#include "EpiGraphics/gfxBindable.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void gfxBindable::Bind()
{
    SetIsBounded(true);
}

void gfxBindable::UnBind()
{
    SetIsBounded(false);
}

EPI_NAMESPACE_END()
