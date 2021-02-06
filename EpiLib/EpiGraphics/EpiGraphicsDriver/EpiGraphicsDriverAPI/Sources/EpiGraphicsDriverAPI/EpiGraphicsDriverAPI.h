#pragma once

EPI_NAMESPACE_BEGIN()

class gfxDriver
{
public:
    virtual ~gfxDriver() = default;

    virtual void Init() = 0;
};

EPI_NAMESPACE_END()
