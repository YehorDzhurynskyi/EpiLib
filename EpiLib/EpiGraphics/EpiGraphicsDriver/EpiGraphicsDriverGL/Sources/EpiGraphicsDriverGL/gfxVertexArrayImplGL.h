#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxVertexArrayImplGL : public gfxVertexArrayImpl
{
public:
    gfxVertexArrayImplGL() = default;
    gfxVertexArrayImplGL(const gfxVertexArrayImplGL& rhs) = delete;
    gfxVertexArrayImplGL& operator=(const gfxVertexArrayImplGL& rhs) = delete;
    gfxVertexArrayImplGL(gfxVertexArrayImplGL&& rhs);
    gfxVertexArrayImplGL& operator=(gfxVertexArrayImplGL&& rhs);
    ~gfxVertexArrayImplGL() override = default;

    void Create() override;
    void Destroy() override;

    epiBool GetIsCreated() const override;
    epiU32 GetID() const override;

    void Bind() override;
    void UnBind() override;

protected:
    epiU32 m_ID{0};
};

EPI_NAMESPACE_END()
