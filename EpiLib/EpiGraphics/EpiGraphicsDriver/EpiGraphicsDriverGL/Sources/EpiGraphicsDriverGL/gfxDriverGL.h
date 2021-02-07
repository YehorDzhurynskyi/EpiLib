#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxDriverGL : public gfxDriver
{
public:
    gfxDriverGL();

    epiPtrArray<gfxPhysicalDeviceImpl> ListOfPhysicalDevices() const override;
};

EPI_NAMESPACE_END()
