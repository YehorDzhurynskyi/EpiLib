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

const epiPtrArray<gfxPhysicalDeviceImpl>& gfxDriverImplGL::GetPhysicalDevices() const
{
    static epiPtrArray<gfxPhysicalDeviceImpl> devices{};
    return devices;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
