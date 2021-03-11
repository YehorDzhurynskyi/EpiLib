#pragma once

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"

#include "EpiCore/common.h"
#include "EpiCore/types.h"
#include "EpiCore/Containers/Array.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueImpl
{
public:
    gfxQueueImpl() = default;
    gfxQueueImpl(const gfxQueueImpl& rhs) = delete;
    gfxQueueImpl& operator=(const gfxQueueImpl& rhs) = delete;
    gfxQueueImpl(gfxQueueImpl&& rhs) = default;
    gfxQueueImpl& operator=(gfxQueueImpl&& rhs) = default;
    virtual ~gfxQueueImpl() = default;

    virtual gfxQueueType GetType() const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
};

class gfxQueueFamilyImpl
{
public:
    gfxQueueFamilyImpl() = default;
    gfxQueueFamilyImpl(const gfxQueueFamilyImpl& rhs) = delete;
    gfxQueueFamilyImpl& operator=(const gfxQueueFamilyImpl& rhs) = delete;
    gfxQueueFamilyImpl(gfxQueueFamilyImpl&& rhs) = default;
    gfxQueueFamilyImpl& operator=(gfxQueueFamilyImpl&& rhs) = default;
    virtual ~gfxQueueFamilyImpl() = default;

    virtual gfxQueueType GetQueueTypeSupported() const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
    virtual epiU32 GetQueueCount() const = 0;
};

class gfxDeviceImpl
{
public:
    gfxDeviceImpl() = default;
    gfxDeviceImpl(const gfxDeviceImpl& rhs) = delete;
    gfxDeviceImpl& operator=(const gfxDeviceImpl& rhs) = delete;
    gfxDeviceImpl(gfxDeviceImpl&& rhs) = default;
    gfxDeviceImpl& operator=(gfxDeviceImpl&& rhs) = default;
    virtual ~gfxDeviceImpl() = default;
};

class gfxSurfaceImpl
{
public:
    gfxSurfaceImpl() = default;
    gfxSurfaceImpl(const gfxSurfaceImpl& rhs) = delete;
    gfxSurfaceImpl& operator=(const gfxSurfaceImpl& rhs) = delete;
    gfxSurfaceImpl(gfxSurfaceImpl&& rhs) = default;
    gfxSurfaceImpl& operator=(gfxSurfaceImpl&& rhs) = default;
    virtual ~gfxSurfaceImpl() = default;
};

class gfxPhysicalDeviceImpl
{
public:
    gfxPhysicalDeviceImpl() = default;
    gfxPhysicalDeviceImpl(const gfxPhysicalDeviceImpl& rhs) = delete;
    gfxPhysicalDeviceImpl& operator=(const gfxPhysicalDeviceImpl& rhs) = delete;
    gfxPhysicalDeviceImpl(gfxPhysicalDeviceImpl&& rhs) = default;
    gfxPhysicalDeviceImpl& operator=(gfxPhysicalDeviceImpl&& rhs) = default;
    virtual ~gfxPhysicalDeviceImpl() = default;

    virtual epiString GetName() const = 0;
    virtual gfxPhysicalDeviceType GetType() const = 0;

    virtual std::unique_ptr<gfxDeviceImpl> CreateDevice(gfxQueueDescriptorList& queueDescriptorList,
                                                        gfxPhysicalDeviceExtension extensionMask) const = 0;

    virtual epiBool IsPresentSupported(const gfxSurfaceImpl& surface) const = 0;
    virtual epiBool IsPresentSupported(const gfxSurfaceImpl& surface, const gfxQueueFamilyImpl& queueFamily) const = 0;
    virtual epiBool IsExtensionsSupported(gfxPhysicalDeviceExtension mask) const = 0;
    virtual epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
};

class gfxDriverImpl
{
public:
    virtual ~gfxDriverImpl() = default;

    virtual std::unique_ptr<gfxSurfaceImpl> CreateSurface(const gfxWindow& window) = 0;
    virtual std::unique_ptr<gfxPhysicalDeviceImpl> FindAppropriatePhysicalDevice(std::function<epiBool(const gfxPhysicalDevice&)> isAppropiateCallback) const = 0;

    virtual epiBool IsExtensionsSupported(gfxDriverExtension mask) const = 0;
    virtual epiBool IsExtensionsEnabled(gfxDriverExtension mask) const = 0;
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

    virtual void Texture(const epiChar* name, epiU32 value) = 0;

    virtual void UniformFloat(const epiChar* name, epiFloat value) = 0;
    virtual void UniformVec2f(const epiChar* name, const epiVec2f& value) = 0;
    virtual void UniformVec3f(const epiChar* name, const epiVec3f& value) = 0;
    virtual void UniformVec4f(const epiChar* name, const epiVec4f& value) = 0;
    virtual void UniformMat4x4f(const epiChar* name, const epiMat4x4f& value, epiBool transpose) = 0;

    virtual void UniformS32(const epiChar* name, epiS32 value) = 0;
    virtual void UniformVec2s(const epiChar* name, const epiVec2s& value) = 0;
    virtual void UniformVec3s(const epiChar* name, const epiVec3s& value) = 0;
    virtual void UniformVec4s(const epiChar* name, const epiVec4s& value) = 0;

    virtual void UniformU32(const epiChar* name, epiU32 value) = 0;
    virtual void UniformVec2u(const epiChar* name, const epiVec2u& value) = 0;
    virtual void UniformVec3u(const epiChar* name, const epiVec3u& value) = 0;
    virtual void UniformVec4u(const epiChar* name, const epiVec4u& value) = 0;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
