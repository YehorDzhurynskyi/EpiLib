#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxDriverVK : public gfxDriver
{
public:
    void Init() override;
};

EPI_NAMESPACE_END()
