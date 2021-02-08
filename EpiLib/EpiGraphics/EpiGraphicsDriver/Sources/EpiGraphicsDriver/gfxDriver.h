#pragma once

#include "EpiGraphicsEnum/EpiGraphicsEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDriverImpl;

} // namespace internalgfx

class gfxDriver
{
public:
    static gfxDriver& GetInstance();

public:
    gfxDriver(const gfxDriver& rhs) = delete;
    gfxDriver& operator=(const gfxDriver& rhs) = delete;
    gfxDriver(gfxDriver&& rhs) = delete;
    gfxDriver& operator=(gfxDriver&& rhs) = delete;
    ~gfxDriver();

protected:
    gfxDriver() = default;

public:
    void ChangeDriverBackend(gfxDriverBackend backend);

protected:
    internalgfx::gfxDriverImpl* m_DriverImpl{nullptr};
    gfxDriverBackend m_Backend{gfxDriverBackend::None};
};

EPI_NAMESPACE_END()
