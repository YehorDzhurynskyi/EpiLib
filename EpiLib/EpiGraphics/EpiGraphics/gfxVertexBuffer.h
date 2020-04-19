#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

// TODO: move to epi
enum class gfxVertexBufferUsage
{
    StaticRead,
    StaticDraw,
    DynamicRead,
    DynamicDraw,
    COUNT
};

// TODO: move to epi
enum class gfxVertexBufferMapAccess
{
    ReadOnly,
    WriteOnly,
    ReadWrite,
    COUNT
};

class gfxVertexBuffer : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxVertexBuffer)
public:
    EPI_GENHIDDEN_gfxVertexBuffer()

    constexpr static MetaTypeID TypeID{0xf78a4476};

    enum gfxVertexBuffer_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_Capacity = 0x4c9ed322,
        PID_COUNT = 3
    };

protected:
    epiBool GetIsCreated_Callback() const;

protected:
    epiU32 m_ID{0};
    epiSize_t m_Capacity{0};

EPI_GENREGION_END(gfxVertexBuffer)

public:
    gfxVertexBuffer() = default;
    gfxVertexBuffer(const gfxVertexBuffer& rhs) = delete;
    gfxVertexBuffer& operator=(const gfxVertexBuffer& rhs) = delete;
    gfxVertexBuffer(gfxVertexBuffer&& rhs);
    gfxVertexBuffer& operator=(gfxVertexBuffer&& rhs);
    ~gfxVertexBuffer();

public:
    void Create(void* initData, epiSize_t capacity, gfxVertexBufferUsage usage);
    void Destroy();

    void Bind() override;
    void UnBind() override;

    void* Map(gfxVertexBufferMapAccess access);
    epiBool UnMap();

private:
    epiBool m_IsMapped{false};
};

EPI_NAMESPACE_END()
