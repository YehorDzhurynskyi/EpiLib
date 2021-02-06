#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxDriverGL : public gfxDriver
{
public:
    void Init() override;
};

EPI_NAMESPACE_END()
