#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxVertexBufferLayoutAttributeImplGL : public gfxVertexBufferLayoutAttributeImpl
{
public:
    gfxVertexBufferLayoutAttributeImplGL() = default;
    gfxVertexBufferLayoutAttributeImplGL(const gfxVertexBufferLayoutAttributeImplGL& rhs) = delete;
    gfxVertexBufferLayoutAttributeImplGL& operator=(const gfxVertexBufferLayoutAttributeImplGL& rhs) = delete;
    gfxVertexBufferLayoutAttributeImplGL(gfxVertexBufferLayoutAttributeImplGL&& rhs);
    gfxVertexBufferLayoutAttributeImplGL& operator=(gfxVertexBufferLayoutAttributeImplGL&& rhs);
    ~gfxVertexBufferLayoutAttributeImplGL() override = default;

    epiU32 GetIndex() const override;
    void SetIndex(epiU32 value) override;
    epiSize_t GetSize() const override;
    void SetSize(epiSize_t value) override;
    gfxVertexBufferLayoutAttributeType GetType() const override;
    void SetType(gfxVertexBufferLayoutAttributeType value) override;
    epiBool GetNormalized() const override;
    void SetNormalized(epiBool value) override;
    epiSize_t GetStride() const override;
    void SetStride(epiSize_t value) override;
    epiSize_t GetOffset() const override;
    void SetOffset(epiSize_t value) override;

    void Apply() const override;

protected:
    epiU32 m_Index{0};
    epiSize_t m_Size{0};
    gfxVertexBufferLayoutAttributeType m_Type{gfxVertexBufferLayoutAttributeType::NONE};
    epiBool m_Normalized{false};
    epiSize_t m_Stride{0};
    epiSize_t m_Offset{0};
};

class gfxVertexBufferLayoutImplGL : public gfxVertexBufferLayoutImpl
{
public:
    gfxVertexBufferLayoutImplGL() = default;
    gfxVertexBufferLayoutImplGL(const gfxVertexBufferLayoutImplGL& rhs) = delete;
    gfxVertexBufferLayoutImplGL& operator=(const gfxVertexBufferLayoutImplGL& rhs) = delete;
    gfxVertexBufferLayoutImplGL(gfxVertexBufferLayoutImplGL&& rhs) = default;
    gfxVertexBufferLayoutImplGL& operator=(gfxVertexBufferLayoutImplGL&& rhs) = default;
    ~gfxVertexBufferLayoutImplGL() override = default;

    const epiArray<gfxVertexBufferLayoutAttributeImpl>& GetAttributes() const override;
    void SetAttributes(const epiArray<gfxVertexBufferLayoutAttributeImpl>& value) override;

    void Apply() const override;

    void Add(gfxVertexBufferLayoutAttributeImpl&& attr) override;

protected:
    epiArray<gfxVertexBufferLayoutAttributeImplGL> m_Attributes;
};

class gfxVertexBufferImplGL : public gfxVertexBufferImpl
{
public:
    gfxVertexBufferImplGL() = default;
    gfxVertexBufferImplGL(const gfxVertexBufferImplGL& rhs) = delete;
    gfxVertexBufferImplGL& operator=(const gfxVertexBufferImplGL& rhs) = delete;
    gfxVertexBufferImplGL(gfxVertexBufferImplGL&& rhs);
    gfxVertexBufferImplGL& operator=(gfxVertexBufferImplGL&& rhs);
    ~gfxVertexBufferImplGL() override = default;

    void Create(const epiByte* initData, epiSize_t capacity, gfxVertexBufferUsage usage, const gfxVertexBufferLayoutImpl& layout) override;
    void Destroy() override;

    epiBool GetIsCreated() const override;
    epiU32 GetID() const override;
    epiSize_t GetCapacity() const override;

    void Bind() override;
    void UnBind() override;

    epiByte* Map(gfxVertexBufferMapAccess access) override;
    epiBool UnMap() override;

protected:
    epiU32 m_ID{0};
    epiSize_t m_Capacity{0};
};

EPI_NAMESPACE_END()
