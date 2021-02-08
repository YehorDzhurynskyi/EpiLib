#pragma once

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDriverImplGL : public gfxDriverImpl
{
public:
    gfxDriverImplGL();

    const epiPtrArray<gfxPhysicalDeviceImpl>& GetPhysicalDevices() const override;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
