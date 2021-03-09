#include "EpiGraphicsDriverGL/gfxDriverImplGL.h"

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxDriverImplGL::gfxDriverImplGL()
{
    if (!gladLoadGL())
    {
        epiLogFatal("OpenGL Failed to `gladLoadGL`!");
    }
}

} // namespace internalgfx

EPI_NAMESPACE_END()
