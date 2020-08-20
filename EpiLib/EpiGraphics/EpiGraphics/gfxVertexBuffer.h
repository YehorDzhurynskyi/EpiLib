#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

enum class gfxVertexBufferUsage
{
EPI_GENREGION_BEGIN(gfxVertexBufferUsage)
    StaticRead = 0,
    StaticDraw = 1,
    DynamicRead = 2,
    DynamicDraw = 3,
    StreamRead = 4,
    StreamDraw = 5
EPI_GENREGION_END(gfxVertexBufferUsage)
};

enum class gfxVertexBufferMapAccess
{
EPI_GENREGION_BEGIN(gfxVertexBufferMapAccess)
    Read = 0,
    Write = 1,
    ReadWrite = 2
EPI_GENREGION_END(gfxVertexBufferMapAccess)
};

class gfxVertexBuffer : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxVertexBuffer)

EPI_GENHIDDEN_gfxVertexBuffer()

public:
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

class gfxVertexBufferMapping final
{
public:
    gfxVertexBufferMapping(gfxVertexBuffer& buffer)
        : m_Buffer(buffer)
    {}

    ~gfxVertexBufferMapping()
    {
        if (m_Mapped != nullptr)
        {
            UnMap();
        }
    }

    void Map(gfxVertexBufferMapAccess access)
    {
        // TODO: make o
        m_Buffer.Bind();
        m_Mapped = reinterpret_cast<epiByte*>(m_Buffer.Map(access));
        m_Buffer.UnBind();
    }

    epiSize_t UnMap()
    {
        const epiSize_t size = m_Size;

        m_Buffer.Bind();
        m_Buffer.UnMap();
        m_Buffer.UnBind();
        m_Mapped = nullptr;
        m_Size = 0;

        return size;
    }

    template<typename T>
    T& PushBack(T&& t = T())
    {
        epiAssert(m_Mapped != nullptr, "should be mapped before pushing");
        epiAssert(m_Size + sizeof(T) <= m_Buffer.GetCapacity(), "buffer capacity overflow");

        const epiU32 size = m_Size;

        *((T*)(m_Mapped + size)) = std::forward<T&&>(t);
        m_Size += sizeof(T);

        return *((T*)(m_Mapped + size));
    }

private:
    gfxVertexBuffer& m_Buffer;
    epiByte* m_Mapped{nullptr};
    epiSize_t m_Size{0};
};

EPI_NAMESPACE_END()
