#include "EpiGraphicsDriverGL/gfxDriverGL.h"

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

gfxDriverGL::gfxDriverGL()
{
    if (!gladLoadGL())
    {
        epiLogFatal("OpenGL Failed to `gladLoadGL`!");
    }
}

epiPtrArray<gfxPhysicalDeviceImpl> gfxDriverGL::ListOfPhysicalDevices() const
{
    return epiPtrArray<gfxPhysicalDeviceImpl>{};
}

EPI_NAMESPACE_END()
