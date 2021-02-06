#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPIEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxDriver
{
public:
    virtual ~gfxDriver() = default;

    virtual void Init() = 0;
};

class gfxVertexArrayImpl
{
public:
    gfxVertexArrayImpl() = default;
    gfxVertexArrayImpl(const gfxVertexArrayImpl& rhs) = delete;
    gfxVertexArrayImpl& operator=(const gfxVertexArrayImpl& rhs) = delete;
    gfxVertexArrayImpl(gfxVertexArrayImpl&& rhs) = default;
    gfxVertexArrayImpl& operator=(gfxVertexArrayImpl&& rhs) = default;
    virtual ~gfxVertexArrayImpl() = default;

    virtual void Create() = 0;
    virtual void Destroy() = 0;

    virtual epiBool GetIsCreated() const = 0;
    virtual epiU32 GetID() const = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
};

class gfxVertexBufferLayoutAttributeImpl
{
public:
    gfxVertexBufferLayoutAttributeImpl() = default;
    gfxVertexBufferLayoutAttributeImpl(const gfxVertexBufferLayoutAttributeImpl& rhs) = delete;
    gfxVertexBufferLayoutAttributeImpl& operator=(const gfxVertexBufferLayoutAttributeImpl& rhs) = delete;
    gfxVertexBufferLayoutAttributeImpl(gfxVertexBufferLayoutAttributeImpl&& rhs) = default;
    gfxVertexBufferLayoutAttributeImpl& operator=(gfxVertexBufferLayoutAttributeImpl&& rhs) = default;
    virtual ~gfxVertexBufferLayoutAttributeImpl() = default;

    virtual epiU32 GetIndex() const = 0;
    virtual void SetIndex(epiU32 value) = 0;
    virtual epiSize_t GetSize() const = 0;
    virtual void SetSize(epiSize_t value) = 0;
    virtual gfxVertexBufferLayoutAttributeType GetType() const = 0;
    virtual void SetType(gfxVertexBufferLayoutAttributeType value) = 0;
    virtual epiBool GetNormalized() const = 0;
    virtual void SetNormalized(epiBool value) = 0;
    virtual epiSize_t GetStride() const = 0;
    virtual void SetStride(epiSize_t value) = 0;
    virtual epiSize_t GetOffset() const = 0;
    virtual void SetOffset(epiSize_t value) = 0;

    virtual void Apply() const = 0;
};

class gfxVertexBufferLayoutImpl
{
public:
    gfxVertexBufferLayoutImpl() = default;
    gfxVertexBufferLayoutImpl(const gfxVertexBufferLayoutImpl& rhs) = delete;
    gfxVertexBufferLayoutImpl& operator=(const gfxVertexBufferLayoutImpl& rhs) = delete;
    gfxVertexBufferLayoutImpl(gfxVertexBufferLayoutImpl&& rhs) = default;
    gfxVertexBufferLayoutImpl& operator=(gfxVertexBufferLayoutImpl&& rhs) = default;
    virtual ~gfxVertexBufferLayoutImpl() = default;

    virtual const epiArray<gfxVertexBufferLayoutAttributeImpl>& GetAttributes() const = 0;
    virtual void SetAttributes(const epiArray<gfxVertexBufferLayoutAttributeImpl>& value) = 0;

    virtual void Apply() const = 0;

    virtual void Add(gfxVertexBufferLayoutAttributeImpl&& attr) = 0;
};

class gfxVertexBufferImpl
{
public:
    gfxVertexBufferImpl() = default;
    gfxVertexBufferImpl(const gfxVertexBufferImpl& rhs) = delete;
    gfxVertexBufferImpl& operator=(const gfxVertexBufferImpl& rhs) = delete;
    gfxVertexBufferImpl(gfxVertexBufferImpl&& rhs) = default;
    gfxVertexBufferImpl& operator=(gfxVertexBufferImpl&& rhs) = default;
    virtual ~gfxVertexBufferImpl() = default;

    virtual void Create(const epiByte* initData, epiSize_t capacity, gfxVertexBufferUsage usage, const gfxVertexBufferLayoutImpl& layout) = 0;
    virtual void Destroy() = 0;

    virtual epiBool GetIsCreated() const = 0;
    virtual epiU32 GetID() const = 0;
    virtual epiSize_t GetCapacity() const = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    virtual epiByte* Map(gfxVertexBufferMapAccess access) = 0;
    virtual epiBool UnMap() = 0;
};

class gfxTextureImpl
{
public:
    gfxTextureImpl() = default;
    gfxTextureImpl(const gfxTextureImpl& rhs) = delete;
    gfxTextureImpl& operator=(const gfxTextureImpl& rhs) = delete;
    gfxTextureImpl(gfxTextureImpl&& rhs) = default;
    gfxTextureImpl& operator=(gfxTextureImpl&& rhs) = default;
    virtual ~gfxTextureImpl() = default;

    virtual void Create2D(const epiByte* initData,
                          epiU32 width,
                          epiU32 height,
                          gfxTextureFormat format,
                          gfxTexturePixelType pixelType) = 0;
    virtual void Destroy() = 0;

    virtual epiU32 GetWidth() const = 0;
    virtual epiU32 GetHeight() const = 0;
    virtual epiBool GetIsCreated() const = 0;
    virtual epiU32 GetID() const = 0;
    virtual gfxTextureType GetType() const = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
};

class gfxShaderImpl
{
public:
    gfxShaderImpl() = default;
    gfxShaderImpl(const gfxShaderImpl& rhs) = delete;
    gfxShaderImpl& operator=(const gfxShaderImpl& rhs) = delete;
    gfxShaderImpl(gfxShaderImpl&& rhs) = default;
    gfxShaderImpl& operator=(gfxShaderImpl&& rhs) = default;
    virtual ~gfxShaderImpl() = default;

    virtual void CreateFromSource(const epiChar* source, gfxShaderType type) = 0;
    virtual void Destroy() = 0;

    virtual epiBool GetIsCreated() const = 0;
    virtual epiU32 GetID() const = 0;
    virtual gfxShaderType GetType() const = 0;
};

class gfxShaderProgramImpl
{
public:
    gfxShaderProgramImpl() = default;
    gfxShaderProgramImpl(const gfxShaderProgramImpl& rhs) = delete;
    gfxShaderProgramImpl& operator=(const gfxShaderProgramImpl& rhs) = delete;
    gfxShaderProgramImpl(gfxShaderProgramImpl&& rhs) = default;
    gfxShaderProgramImpl& operator=(gfxShaderProgramImpl&& rhs) = default;
    virtual ~gfxShaderProgramImpl() = default;

    virtual void Create() = 0;
    virtual void Destroy() = 0;

    virtual epiBool GetIsCreated() const = 0;
    virtual epiU32 GetID() const = 0;

    virtual void ShaderAttach(const gfxShaderImpl& shader) = 0;
    virtual void ShaderDettach(gfxShaderType type) = 0;

    virtual void Build() = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
};

EPI_NAMESPACE_END()
