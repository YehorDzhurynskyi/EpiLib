#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexArray.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

class gfxVertexArray : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxVertexArray)
public:
    EPI_GENHIDDEN_gfxVertexArray()

    constexpr static MetaTypeID TypeID{0x7d61d88d};

    enum gfxVertexArray_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_COUNT = 2
    };

protected:
    epiBool GetIsCreated_Callback() const;

protected:
    epiU32 m_ID{0};

EPI_GENREGION_END(gfxVertexArray)

public:
    gfxVertexArray();
    gfxVertexArray(const gfxVertexArray& rhs) = delete;
    gfxVertexArray& operator=(const gfxVertexArray& rhs) = delete;
    gfxVertexArray(gfxVertexArray&& rhs);
    gfxVertexArray& operator=(gfxVertexArray&& rhs);
    ~gfxVertexArray();

public:
    void Create();
    void Destroy();

    void Bind() override;
    void UnBind() override;
};

EPI_NAMESPACE_END()
