#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkBuffer_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxVertexBufferLayoutAttributeImplVK : public gfxVertexBufferLayoutAttributeImpl
{
public:
    gfxVertexBufferLayoutAttributeImplVK() = default;
    gfxVertexBufferLayoutAttributeImplVK(const gfxVertexBufferLayoutAttributeImplVK& rhs) = delete;
    gfxVertexBufferLayoutAttributeImplVK& operator=(const gfxVertexBufferLayoutAttributeImplVK& rhs) = delete;
    gfxVertexBufferLayoutAttributeImplVK(gfxVertexBufferLayoutAttributeImplVK&& rhs);
    gfxVertexBufferLayoutAttributeImplVK& operator=(gfxVertexBufferLayoutAttributeImplVK&& rhs);
    ~gfxVertexBufferLayoutAttributeImplVK() override = default;

    epiU32 GetLocation() const override;
    void SetLocation(epiU32 value) override;
    epiSize_t GetOffset() const override;
    void SetOffset(epiSize_t value) override;
    gfxFormat GetFormat() const override;
    void SetFormat(gfxFormat value) override;

    void Apply() const override;

protected:
    epiU32 m_Location{0};
    epiSize_t m_Offset{0};
    gfxFormat m_Format{gfxFormat::UNDEFINED};
};

class gfxVertexBufferLayoutImplVK : public gfxVertexBufferLayoutImpl
{
public:
    gfxVertexBufferLayoutImplVK() = default;
    gfxVertexBufferLayoutImplVK(const gfxVertexBufferLayoutImplVK& rhs) = delete;
    gfxVertexBufferLayoutImplVK& operator=(const gfxVertexBufferLayoutImplVK& rhs) = delete;
    gfxVertexBufferLayoutImplVK(gfxVertexBufferLayoutImplVK&& rhs) = default;
    gfxVertexBufferLayoutImplVK& operator=(gfxVertexBufferLayoutImplVK&& rhs) = default;
    ~gfxVertexBufferLayoutImplVK() override = default;

    epiU32 GetStride() const override;
    void SetStride(epiU32 value) override;

    void Apply() const override;

    void Add(gfxVertexBufferLayoutAttributeImpl&& attr) override;

protected:
    epiArray<gfxVertexBufferLayoutAttributeImplVK> m_Attributes;
    epiU32 m_Stride{0};
};

class gfxVertexBufferImplVK : public gfxVertexBufferImpl
{
public:
    gfxVertexBufferImplVK() = default;
    gfxVertexBufferImplVK(const gfxVertexBufferImplVK& rhs) = delete;
    gfxVertexBufferImplVK& operator=(const gfxVertexBufferImplVK& rhs) = delete;
    gfxVertexBufferImplVK(gfxVertexBufferImplVK&& rhs) = default;
    gfxVertexBufferImplVK& operator=(gfxVertexBufferImplVK&& rhs) = default;
    ~gfxVertexBufferImplVK() override = default;
};

} // internalgfx

EPI_NAMESPACE_END()
