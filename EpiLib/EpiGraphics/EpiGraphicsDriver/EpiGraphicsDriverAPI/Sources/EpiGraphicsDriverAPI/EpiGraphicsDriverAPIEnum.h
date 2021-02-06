#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPIEnum.hxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

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

EPI_NAMESPACE_END()
