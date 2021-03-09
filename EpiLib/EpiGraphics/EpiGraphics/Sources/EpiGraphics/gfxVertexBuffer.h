#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexBuffer.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxVertexBufferLayoutAttributeImpl;
class gfxVertexBufferLayoutImpl;
class gfxVertexBufferImpl;

} // namespace internalgfx

class gfxVertexBufferLayoutAttribute : public Object
{
EPI_GENREGION_BEGIN(gfxVertexBufferLayoutAttribute)

EPI_GENHIDDEN_gfxVertexBufferLayoutAttribute()

public:
    constexpr static epiMetaTypeID TypeID{0x166eaa8f};

    enum gfxVertexBufferLayoutAttribute_PIDs
    {
        PID_Index = 0x41b24805,
        PID_Size = 0x57f28b54,
        PID_Type = 0x2cecf817,
        PID_Normalized = 0x364083c7,
        PID_Stride = 0x8df33e39,
        PID_Offset = 0x5ea6cfe6,
        PID_COUNT = 6
    };

protected:
    epiU32 GetIndex_Callback() const;
    void SetIndex_Callback(epiU32 value);
    epiSize_t GetSize_Callback() const;
    void SetSize_Callback(epiSize_t value);
    gfxVertexBufferLayoutAttributeType GetType_Callback() const;
    void SetType_Callback(gfxVertexBufferLayoutAttributeType value);
    epiBool GetNormalized_Callback() const;
    void SetNormalized_Callback(epiBool value);
    epiSize_t GetStride_Callback() const;
    void SetStride_Callback(epiSize_t value);
    epiSize_t GetOffset_Callback() const;
    void SetOffset_Callback(epiSize_t value);

EPI_GENREGION_END(gfxVertexBufferLayoutAttribute)

public:
    friend class gfxVertexBufferLayout;

protected:
    std::unique_ptr<internalgfx::gfxVertexBufferLayoutAttributeImpl> m_Impl;
};

class gfxVertexBufferLayout : public Object
{
EPI_GENREGION_BEGIN(gfxVertexBufferLayout)

EPI_GENHIDDEN_gfxVertexBufferLayout()

public:
    constexpr static epiMetaTypeID TypeID{0x7ff14d8b};

    enum gfxVertexBufferLayout_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxVertexBufferLayout)

public:
    friend class gfxVertexBuffer;

public:
    gfxVertexBufferLayout() = default;
    gfxVertexBufferLayout(const gfxVertexBufferLayout& rhs) = default;
    gfxVertexBufferLayout& operator=(const gfxVertexBufferLayout& rhs) = default;
    gfxVertexBufferLayout(gfxVertexBufferLayout&& rhs);
    gfxVertexBufferLayout& operator=(gfxVertexBufferLayout&& rhs);
    ~gfxVertexBufferLayout() override;

public:
    void Add(gfxVertexBufferLayoutAttribute&& attr);
    void Add(epiSize_t size, gfxVertexBufferLayoutAttributeType type, epiBool normalized, epiSize_t stride, epiSize_t offset);

protected:
    internalgfx::gfxVertexBufferLayoutImpl* m_Impl{nullptr};
    epiSize_t m_Size{0};
};

class gfxVertexBuffer : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxVertexBuffer)

EPI_GENHIDDEN_gfxVertexBuffer()

public:
    constexpr static epiMetaTypeID TypeID{0xf78a4476};

    enum gfxVertexBuffer_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_Capacity = 0x4c9ed322,
        PID_COUNT = 3
    };

protected:
    epiBool GetIsCreated_Callback() const;
    epiU32 GetID_Callback() const;
    epiSize_t GetCapacity_Callback() const;

EPI_GENREGION_END(gfxVertexBuffer)

public:
    gfxVertexBuffer() = default;
    gfxVertexBuffer(const gfxVertexBuffer& rhs) = delete;
    gfxVertexBuffer& operator=(const gfxVertexBuffer& rhs) = delete;
    gfxVertexBuffer(gfxVertexBuffer&& rhs);
    gfxVertexBuffer& operator=(gfxVertexBuffer&& rhs);
    ~gfxVertexBuffer();

public:
    void Create(const epiByte* initData, epiSize_t capacity, gfxVertexBufferUsage usage, const gfxVertexBufferLayout& layout);
    void Destroy();

    void Bind() override;
    void UnBind() override;

    epiByte* Map(gfxVertexBufferMapAccess access);
    epiBool UnMap();

protected:
    internalgfx::gfxVertexBufferImpl* m_Impl{nullptr};
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
