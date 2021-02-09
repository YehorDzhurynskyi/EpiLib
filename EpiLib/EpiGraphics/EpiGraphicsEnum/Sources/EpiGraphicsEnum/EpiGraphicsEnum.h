#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsEnum/EpiGraphicsEnum.hxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

enum class gfxDriverBackend : epiS32
{
EPI_GENREGION_BEGIN(gfxDriverBackend)
    None = -1,
    OpenGL = 0,
    Vulkan = 1,
    Software = 2,
    COUNT = 3
EPI_GENREGION_END(gfxDriverBackend)
};

enum class gfxTextureType : epiS32
{
EPI_GENREGION_BEGIN(gfxTextureType)
    None = 0,
    Texture2D = 1
EPI_GENREGION_END(gfxTextureType)
};

enum class gfxTextureFormat : epiS32
{
EPI_GENREGION_BEGIN(gfxTextureFormat)
    R = 0,
    RG = 1,
    RGB = 2,
    BGR = 3,
    RGBA = 4,
    BGRA = 5
EPI_GENREGION_END(gfxTextureFormat)
};

enum class gfxTexturePixelType : epiS32
{
EPI_GENREGION_BEGIN(gfxTexturePixelType)
    BYTE = 0,
    UBYTE = 1,
    SHORT = 2,
    USHORT = 3,
    INT = 4,
    UINT = 5
EPI_GENREGION_END(gfxTexturePixelType)
};

enum class gfxVertexBufferUsage : epiS32
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

enum class gfxVertexBufferMapAccess : epiS32
{
EPI_GENREGION_BEGIN(gfxVertexBufferMapAccess)
    Read = 0,
    Write = 1,
    ReadWrite = 2
EPI_GENREGION_END(gfxVertexBufferMapAccess)
};

enum class gfxShaderType : epiS32
{
EPI_GENREGION_BEGIN(gfxShaderType)
    None = 0,
    Vertex = 1,
    Geometry = 2,
    Pixel = 3
EPI_GENREGION_END(gfxShaderType)
};

enum class gfxVertexBufferLayoutAttributeType : epiS32
{
EPI_GENREGION_BEGIN(gfxVertexBufferLayoutAttributeType)
    NONE = 0,
    BYTE = 1,
    UBYTE = 2,
    SHORT = 3,
    USHORT = 4,
    INT = 5,
    UINT = 6,
    HALF_FLOAT = 7,
    FLOAT = 8,
    DOUBLE = 9
EPI_GENREGION_END(gfxVertexBufferLayoutAttributeType)
};

enum class gfxPhysicalDeviceType : epiS32
{
EPI_GENREGION_BEGIN(gfxPhysicalDeviceType)
    None = 0,
    IntegratedGPU = 1,
    DiscreteGPU = 2,
    VirtualGPU = 3,
    CPU = 4,
    Other = 5
EPI_GENREGION_END(gfxPhysicalDeviceType)
};

enum class gfxPhysicalDeviceFeature : epiS32
{
EPI_GENREGION_BEGIN(gfxPhysicalDeviceFeature)
    GeometryShader = 0,
    TessellationShader = 1,
    ShaderFloat64 = 2,
    ShaderInt64 = 3,
    ShaderInt16 = 4,
    COUNT = 5
EPI_GENREGION_END(gfxPhysicalDeviceFeature)
};

enum gfxQueueType : epiS32
{
EPI_GENREGION_BEGIN(gfxQueueType)
    gfxQueueType_Graphics = (1 << 0),
    gfxQueueType_Compute = (1 << 1),
    gfxQueueType_Transfer = (1 << 2),
    gfxQueueType_SparseBinding = (1 << 3),
    gfxQueueType_Protected = (1 << 4),
    gfxQueueType_MAX = (1 << 5),
    gfxQueueType_ALL = gfxQueueType_Graphics | gfxQueueType_Compute | gfxQueueType_Transfer | gfxQueueType_SparseBinding | gfxQueueType_Protected
EPI_GENREGION_END(gfxQueueType)
};

enum gfxDriverExtension : epiS32
{
EPI_GENREGION_BEGIN(gfxDriverExtension)
    gfxDriverExtension_Surface = (1 << 0),
    gfxDriverExtension_SurfaceWin32 = (1 << 1),
    gfxDriverExtension_MAX = (1 << 2),
    gfxDriverExtension_ALL = gfxDriverExtension_Surface | gfxDriverExtension_SurfaceWin32
EPI_GENREGION_END(gfxDriverExtension)
};

enum gfxPhysicalDeviceExtension : epiS32
{
EPI_GENREGION_BEGIN(gfxPhysicalDeviceExtension)
    gfxPhysicalDeviceExtension_SwapChain = (1 << 0),
    gfxPhysicalDeviceExtension_MAX = (1 << 1),
    gfxPhysicalDeviceExtension_ALL = gfxPhysicalDeviceExtension_SwapChain
EPI_GENREGION_END(gfxPhysicalDeviceExtension)
};

EPI_NAMESPACE_END()
