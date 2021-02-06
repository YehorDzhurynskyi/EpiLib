#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexArray.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxVertexArray : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxVertexArray)

EPI_GENHIDDEN_gfxVertexArray()

public:
    constexpr static epiMetaTypeID TypeID{0x7d61d88d};

    enum gfxVertexArray_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_COUNT = 2
    };

protected:
    epiBool GetIsCreated_Callback() const;
    epiU32 GetID_Callback() const;

EPI_GENREGION_END(gfxVertexArray)

public:
    gfxVertexArray();
    gfxVertexArray(const gfxVertexArray& rhs) = delete;
    gfxVertexArray& operator=(const gfxVertexArray& rhs) = delete;
    gfxVertexArray(gfxVertexArray&& rhs) = default;
    gfxVertexArray& operator=(gfxVertexArray&& rhs) = default;
    ~gfxVertexArray();

public:
    void Create();
    void Destroy();

    void Bind() override;
    void UnBind() override;

protected:
    std::unique_ptr<gfxVertexArrayImpl> m_Impl;
};

EPI_NAMESPACE_END()
