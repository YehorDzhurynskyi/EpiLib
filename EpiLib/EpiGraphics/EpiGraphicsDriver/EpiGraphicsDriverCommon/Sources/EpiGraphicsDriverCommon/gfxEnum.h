#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxEnum.hxx"
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
    Texture1D = 0,
    Texture2D = 1,
    Texture3D = 2
EPI_GENREGION_END(gfxTextureType)
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
    Tesselation = 3,
    Fragment = 4
EPI_GENREGION_END(gfxShaderType)
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
    RobustBufferAccess = 0,
    FullDrawIndexUint32 = 1,
    ImageCubeArray = 2,
    IndependentBlend = 3,
    GeometryShader = 4,
    TessellationShader = 5,
    SampleRateShading = 6,
    DualSrcBlend = 7,
    LogicOp = 8,
    MultiDrawIndirect = 9,
    DrawIndirectFirstInstance = 10,
    DepthClamp = 11,
    DepthBiasClamp = 12,
    FillModeNonSolid = 13,
    DepthBounds = 14,
    WideLines = 15,
    LargePoints = 16,
    AlphaToOne = 17,
    MultiViewport = 18,
    SamplerAnisotropy = 19,
    TextureCompressionETC2 = 20,
    TextureCompressionASTC_LDR = 21,
    TextureCompressionBC = 22,
    OcclusionQueryPrecise = 23,
    PipelineStatisticsQuery = 24,
    VertexPipelineStoresAndAtomics = 25,
    FragmentStoresAndAtomics = 26,
    ShaderTessellationAndGeometryPointSize = 27,
    ShaderImageGatherExtended = 28,
    ShaderStorageImageExtendedFormats = 29,
    ShaderStorageImageMultisample = 30,
    ShaderStorageImageReadWithoutFormat = 31,
    ShaderStorageImageWriteWithoutFormat = 32,
    ShaderUniformBufferArrayDynamicIndexing = 33,
    ShaderSampledImageArrayDynamicIndexing = 34,
    ShaderStorageBufferArrayDynamicIndexing = 35,
    ShaderStorageImageArrayDynamicIndexing = 36,
    ShaderClipDistance = 37,
    ShaderCullDistance = 38,
    ShaderFloat64 = 39,
    ShaderInt64 = 40,
    ShaderInt16 = 41,
    ShaderResourceResidency = 42,
    ShaderResourceMinLod = 43,
    SparseBinding = 44,
    SparseResidencyBuffer = 45,
    SparseResidencyImage2D = 46,
    SparseResidencyImage3D = 47,
    SparseResidency2Samples = 48,
    SparseResidency4Samples = 49,
    SparseResidency8Samples = 50,
    SparseResidency16Samples = 51,
    SparseResidencyAliased = 52,
    VariableMultisampleRate = 53,
    InheritedQueries = 54,
    StorageBuffer16BitAccess = 55,
    UniformAndStorageBuffer16BitAccess = 56,
    StoragePushConstant16 = 57,
    StorageInputOutput16 = 58,
    Multiview = 59,
    MultiviewGeometryShader = 60,
    MultiviewTessellationShader = 61,
    VariablePointersStorageBuffer = 62,
    VariablePointers = 63,
    ProtectedMemory = 64,
    SamplerYcbcrConversion = 65,
    ShaderDrawParameters = 66,
    SamplerMirrorClampToEdge = 67,
    DrawIndirectCount = 68,
    StorageBuffer8BitAccess = 69,
    UniformAndStorageBuffer8BitAccess = 70,
    StoragePushConstant8 = 71,
    ShaderBufferInt64Atomics = 72,
    ShaderSharedInt64Atomics = 73,
    ShaderFloat16 = 74,
    ShaderInt8 = 75,
    DescriptorIndexing = 76,
    ShaderInputAttachmentArrayDynamicIndexing = 77,
    ShaderUniformTexelBufferArrayDynamicIndexing = 78,
    ShaderStorageTexelBufferArrayDynamicIndexing = 79,
    ShaderUniformBufferArrayNonUniformIndexing = 80,
    ShaderSampledImageArrayNonUniformIndexing = 81,
    ShaderStorageBufferArrayNonUniformIndexing = 82,
    ShaderStorageImageArrayNonUniformIndexing = 83,
    ShaderInputAttachmentArrayNonUniformIndexing = 84,
    ShaderUniformTexelBufferArrayNonUniformIndexing = 85,
    ShaderStorageTexelBufferArrayNonUniformIndexing = 86,
    DescriptorBindingUniformBufferUpdateAfterBind = 87,
    DescriptorBindingSampledImageUpdateAfterBind = 88,
    DescriptorBindingStorageImageUpdateAfterBind = 89,
    DescriptorBindingStorageBufferUpdateAfterBind = 90,
    DescriptorBindingUniformTexelBufferUpdateAfterBind = 91,
    DescriptorBindingStorageTexelBufferUpdateAfterBind = 92,
    DescriptorBindingUpdateUnusedWhilePending = 93,
    DescriptorBindingPartiallyBound = 94,
    DescriptorBindingVariableDescriptorCount = 95,
    RuntimeDescriptorArray = 96,
    SamplerFilterMinmax = 97,
    ScalarBlockLayout = 98,
    ImagelessFramebuffer = 99,
    UniformBufferStandardLayout = 100,
    ShaderSubgroupExtendedTypes = 101,
    SeparateDepthStencilLayouts = 102,
    HostQueryReset = 103,
    TimelineSemaphore = 104,
    BufferDeviceAddress = 105,
    BufferDeviceAddressCaptureReplay = 106,
    BufferDeviceAddressMultiDevice = 107,
    VulkanMemoryModel = 108,
    VulkanMemoryModelDeviceScope = 109,
    VulkanMemoryModelAvailabilityVisibilityChains = 110,
    ShaderOutputViewportIndex = 111,
    ShaderOutputLayer = 112,
    SubgroupBroadcastDynamicId = 113,
    COUNT = 114
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

enum class gfxDriverExtension : epiS32
{
EPI_GENREGION_BEGIN(gfxDriverExtension)
    Surface = 0,
    SurfaceWin32 = 1,
    COUNT = 2
EPI_GENREGION_END(gfxDriverExtension)
};

enum class gfxPhysicalDeviceExtension : epiS32
{
EPI_GENREGION_BEGIN(gfxPhysicalDeviceExtension)
    SwapChain = 0,
    ImageLessFrameBuffer = 1,
    ImageFormatList = 2,
    COUNT = 3
EPI_GENREGION_END(gfxPhysicalDeviceExtension)
};

enum class gfxSurfaceColorSpace : epiS32
{
EPI_GENREGION_BEGIN(gfxSurfaceColorSpace)
    SRGB_NONLINEAR = 0,
    DISPLAY_P3_NONLINEAR_EXT = 1,
    EXTENDED_SRGB_LINEAR_EXT = 2,
    DISPLAY_P3_LINEAR_EXT = 3,
    DCI_P3_NONLINEAR_EXT = 4,
    BT709_LINEAR_EXT = 5,
    BT709_NONLINEAR_EXT = 6,
    BT2020_LINEAR_EXT = 7,
    HDR10_ST2084_EXT = 8,
    DOLBYVISION_EXT = 9,
    HDR10_HLG_EXT = 10,
    ADOBERGB_LINEAR_EXT = 11,
    ADOBERGB_NONLINEAR_EXT = 12,
    PASS_THROUGH_EXT = 13,
    EXTENDED_SRGB_NONLINEAR_EXT = 14,
    DISPLAY_NATIVE_AMD = 15
EPI_GENREGION_END(gfxSurfaceColorSpace)
};

enum class gfxSurfacePresentMode : epiS32
{
EPI_GENREGION_BEGIN(gfxSurfacePresentMode)
    IMMEDIATE = 0,
    MAILBOX = 1,
    FIFO = 2,
    FIFO_RELAXED = 3,
    SHARED_DEMAND_REFRESH = 4,
    SHARED_CONTINUOUS_REFRESH = 5
EPI_GENREGION_END(gfxSurfacePresentMode)
};

enum class gfxFormat : epiS32
{
EPI_GENREGION_BEGIN(gfxFormat)
    UNDEFINED = 0,
    R4G4_UNORM_PACK8 = 1,
    R4G4B4A4_UNORM_PACK16 = 2,
    B4G4R4A4_UNORM_PACK16 = 3,
    R5G6B5_UNORM_PACK16 = 4,
    B5G6R5_UNORM_PACK16 = 5,
    R5G5B5A1_UNORM_PACK16 = 6,
    B5G5R5A1_UNORM_PACK16 = 7,
    A1R5G5B5_UNORM_PACK16 = 8,
    R8_UNORM = 9,
    R8_SNORM = 10,
    R8_USCALED = 11,
    R8_SSCALED = 12,
    R8_UINT = 13,
    R8_SINT = 14,
    R8_SRGB = 15,
    R8G8_UNORM = 16,
    R8G8_SNORM = 17,
    R8G8_USCALED = 18,
    R8G8_SSCALED = 19,
    R8G8_UINT = 20,
    R8G8_SINT = 21,
    R8G8_SRGB = 22,
    R8G8B8_UNORM = 23,
    R8G8B8_SNORM = 24,
    R8G8B8_USCALED = 25,
    R8G8B8_SSCALED = 26,
    R8G8B8_UINT = 27,
    R8G8B8_SINT = 28,
    R8G8B8_SRGB = 29,
    B8G8R8_UNORM = 30,
    B8G8R8_SNORM = 31,
    B8G8R8_USCALED = 32,
    B8G8R8_SSCALED = 33,
    B8G8R8_UINT = 34,
    B8G8R8_SINT = 35,
    B8G8R8_SRGB = 36,
    R8G8B8A8_UNORM = 37,
    R8G8B8A8_SNORM = 38,
    R8G8B8A8_USCALED = 39,
    R8G8B8A8_SSCALED = 40,
    R8G8B8A8_UINT = 41,
    R8G8B8A8_SINT = 42,
    R8G8B8A8_SRGB = 43,
    B8G8R8A8_UNORM = 44,
    B8G8R8A8_SNORM = 45,
    B8G8R8A8_USCALED = 46,
    B8G8R8A8_SSCALED = 47,
    B8G8R8A8_UINT = 48,
    B8G8R8A8_SINT = 49,
    B8G8R8A8_SRGB = 50,
    A8B8G8R8_UNORM_PACK32 = 51,
    A8B8G8R8_SNORM_PACK32 = 52,
    A8B8G8R8_USCALED_PACK32 = 53,
    A8B8G8R8_SSCALED_PACK32 = 54,
    A8B8G8R8_UINT_PACK32 = 55,
    A8B8G8R8_SINT_PACK32 = 56,
    A8B8G8R8_SRGB_PACK32 = 57,
    A2R10G10B10_UNORM_PACK32 = 58,
    A2R10G10B10_SNORM_PACK32 = 59,
    A2R10G10B10_USCALED_PACK32 = 60,
    A2R10G10B10_SSCALED_PACK32 = 61,
    A2R10G10B10_UINT_PACK32 = 62,
    A2R10G10B10_SINT_PACK32 = 63,
    A2B10G10R10_UNORM_PACK32 = 64,
    A2B10G10R10_SNORM_PACK32 = 65,
    A2B10G10R10_USCALED_PACK32 = 66,
    A2B10G10R10_SSCALED_PACK32 = 67,
    A2B10G10R10_UINT_PACK32 = 68,
    A2B10G10R10_SINT_PACK32 = 69,
    R16_UNORM = 70,
    R16_SNORM = 71,
    R16_USCALED = 72,
    R16_SSCALED = 73,
    R16_UINT = 74,
    R16_SINT = 75,
    R16_SFLOAT = 76,
    R16G16_UNORM = 77,
    R16G16_SNORM = 78,
    R16G16_USCALED = 79,
    R16G16_SSCALED = 80,
    R16G16_UINT = 81,
    R16G16_SINT = 82,
    R16G16_SFLOAT = 83,
    R16G16B16_UNORM = 84,
    R16G16B16_SNORM = 85,
    R16G16B16_USCALED = 86,
    R16G16B16_SSCALED = 87,
    R16G16B16_UINT = 88,
    R16G16B16_SINT = 89,
    R16G16B16_SFLOAT = 90,
    R16G16B16A16_UNORM = 91,
    R16G16B16A16_SNORM = 92,
    R16G16B16A16_USCALED = 93,
    R16G16B16A16_SSCALED = 94,
    R16G16B16A16_UINT = 95,
    R16G16B16A16_SINT = 96,
    R16G16B16A16_SFLOAT = 97,
    R32_UINT = 98,
    R32_SINT = 99,
    R32_SFLOAT = 100,
    R32G32_UINT = 101,
    R32G32_SINT = 102,
    R32G32_SFLOAT = 103,
    R32G32B32_UINT = 104,
    R32G32B32_SINT = 105,
    R32G32B32_SFLOAT = 106,
    R32G32B32A32_UINT = 107,
    R32G32B32A32_SINT = 108,
    R32G32B32A32_SFLOAT = 109,
    R64_UINT = 110,
    R64_SINT = 111,
    R64_SFLOAT = 112,
    R64G64_UINT = 113,
    R64G64_SINT = 114,
    R64G64_SFLOAT = 115,
    R64G64B64_UINT = 116,
    R64G64B64_SINT = 117,
    R64G64B64_SFLOAT = 118,
    R64G64B64A64_UINT = 119,
    R64G64B64A64_SINT = 120,
    R64G64B64A64_SFLOAT = 121,
    B10G11R11_UFLOAT_PACK32 = 122,
    E5B9G9R9_UFLOAT_PACK32 = 123,
    D16_UNORM = 124,
    X8_D24_UNORM_PACK32 = 125,
    D32_SFLOAT = 126,
    S8_UINT = 127,
    D16_UNORM_S8_UINT = 128,
    D24_UNORM_S8_UINT = 129,
    D32_SFLOAT_S8_UINT = 130,
    BC1_RGB_UNORM_BLOCK = 131,
    BC1_RGB_SRGB_BLOCK = 132,
    BC1_RGBA_UNORM_BLOCK = 133,
    BC1_RGBA_SRGB_BLOCK = 134,
    BC2_UNORM_BLOCK = 135,
    BC2_SRGB_BLOCK = 136,
    BC3_UNORM_BLOCK = 137,
    BC3_SRGB_BLOCK = 138,
    BC4_UNORM_BLOCK = 139,
    BC4_SNORM_BLOCK = 140,
    BC5_UNORM_BLOCK = 141,
    BC5_SNORM_BLOCK = 142,
    BC6H_UFLOAT_BLOCK = 143,
    BC6H_SFLOAT_BLOCK = 144,
    BC7_UNORM_BLOCK = 145,
    BC7_SRGB_BLOCK = 146,
    ETC2_R8G8B8_UNORM_BLOCK = 147,
    ETC2_R8G8B8_SRGB_BLOCK = 148,
    ETC2_R8G8B8A1_UNORM_BLOCK = 149,
    ETC2_R8G8B8A1_SRGB_BLOCK = 150,
    ETC2_R8G8B8A8_UNORM_BLOCK = 151,
    ETC2_R8G8B8A8_SRGB_BLOCK = 152,
    EAC_R11_UNORM_BLOCK = 153,
    EAC_R11_SNORM_BLOCK = 154,
    EAC_R11G11_UNORM_BLOCK = 155,
    EAC_R11G11_SNORM_BLOCK = 156,
    ASTC_4x4_UNORM_BLOCK = 157,
    ASTC_4x4_SRGB_BLOCK = 158,
    ASTC_5x4_UNORM_BLOCK = 159,
    ASTC_5x4_SRGB_BLOCK = 160,
    ASTC_5x5_UNORM_BLOCK = 161,
    ASTC_5x5_SRGB_BLOCK = 162,
    ASTC_6x5_UNORM_BLOCK = 163,
    ASTC_6x5_SRGB_BLOCK = 164,
    ASTC_6x6_UNORM_BLOCK = 165,
    ASTC_6x6_SRGB_BLOCK = 166,
    ASTC_8x5_UNORM_BLOCK = 167,
    ASTC_8x5_SRGB_BLOCK = 168,
    ASTC_8x6_UNORM_BLOCK = 169,
    ASTC_8x6_SRGB_BLOCK = 170,
    ASTC_8x8_UNORM_BLOCK = 171,
    ASTC_8x8_SRGB_BLOCK = 172,
    ASTC_10x5_UNORM_BLOCK = 173,
    ASTC_10x5_SRGB_BLOCK = 174,
    ASTC_10x6_UNORM_BLOCK = 175,
    ASTC_10x6_SRGB_BLOCK = 176,
    ASTC_10x8_UNORM_BLOCK = 177,
    ASTC_10x8_SRGB_BLOCK = 178,
    ASTC_10x10_UNORM_BLOCK = 179,
    ASTC_10x10_SRGB_BLOCK = 180,
    ASTC_12x10_UNORM_BLOCK = 181,
    ASTC_12x10_SRGB_BLOCK = 182,
    ASTC_12x12_UNORM_BLOCK = 183,
    ASTC_12x12_SRGB_BLOCK = 184,
    G8B8G8R8_422_UNORM = 185,
    B8G8R8G8_422_UNORM = 186,
    G8_B8_R8_3PLANE_420_UNORM = 187,
    G8_B8R8_2PLANE_420_UNORM = 188,
    G8_B8_R8_3PLANE_422_UNORM = 189,
    G8_B8R8_2PLANE_422_UNORM = 190,
    G8_B8_R8_3PLANE_444_UNORM = 191,
    R10X6_UNORM_PACK16 = 192,
    R10X6G10X6_UNORM_2PACK16 = 193,
    R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 194,
    G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 195,
    B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 196,
    G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 197,
    G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 198,
    G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 199,
    G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 200,
    G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 201,
    R12X4_UNORM_PACK16 = 202,
    R12X4G12X4_UNORM_2PACK16 = 203,
    R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 204,
    G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 205,
    B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 206,
    G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 207,
    G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 208,
    G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 209,
    G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 210,
    G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 211,
    G16B16G16R16_422_UNORM = 212,
    B16G16R16G16_422_UNORM = 213,
    G16_B16_R16_3PLANE_420_UNORM = 214,
    G16_B16R16_2PLANE_420_UNORM = 215,
    G16_B16_R16_3PLANE_422_UNORM = 216,
    G16_B16R16_2PLANE_422_UNORM = 217,
    G16_B16_R16_3PLANE_444_UNORM = 218,
    PVRTC1_2BPP_UNORM_BLOCK_IMG = 219,
    PVRTC1_4BPP_UNORM_BLOCK_IMG = 220,
    PVRTC2_2BPP_UNORM_BLOCK_IMG = 221,
    PVRTC2_4BPP_UNORM_BLOCK_IMG = 222,
    PVRTC1_2BPP_SRGB_BLOCK_IMG = 223,
    PVRTC1_4BPP_SRGB_BLOCK_IMG = 224,
    PVRTC2_2BPP_SRGB_BLOCK_IMG = 225,
    PVRTC2_4BPP_SRGB_BLOCK_IMG = 226,
    ASTC_4x4_SFLOAT_BLOCK_EXT = 227,
    ASTC_5x4_SFLOAT_BLOCK_EXT = 228,
    ASTC_5x5_SFLOAT_BLOCK_EXT = 229,
    ASTC_6x5_SFLOAT_BLOCK_EXT = 230,
    ASTC_6x6_SFLOAT_BLOCK_EXT = 231,
    ASTC_8x5_SFLOAT_BLOCK_EXT = 232,
    ASTC_8x6_SFLOAT_BLOCK_EXT = 233,
    ASTC_8x8_SFLOAT_BLOCK_EXT = 234,
    ASTC_10x5_SFLOAT_BLOCK_EXT = 235,
    ASTC_10x6_SFLOAT_BLOCK_EXT = 236,
    ASTC_10x8_SFLOAT_BLOCK_EXT = 237,
    ASTC_10x10_SFLOAT_BLOCK_EXT = 238,
    ASTC_12x10_SFLOAT_BLOCK_EXT = 239,
    ASTC_12x12_SFLOAT_BLOCK_EXT = 240,
    A4R4G4B4_UNORM_PACK16_EXT = 241,
    A4B4G4R4_UNORM_PACK16_EXT = 242
EPI_GENREGION_END(gfxFormat)
};

enum gfxSurfaceTransform : epiS32
{
EPI_GENREGION_BEGIN(gfxSurfaceTransform)
    gfxSurfaceTransform_IDENTITY = (1 << 0),
    gfxSurfaceTransform_ROTATE_90 = (1 << 1),
    gfxSurfaceTransform_ROTATE_180 = (1 << 2),
    gfxSurfaceTransform_ROTATE_270 = (1 << 3),
    gfxSurfaceTransform_HORIZONTAL_MIRROR = (1 << 4),
    gfxSurfaceTransform_HORIZONTAL_MIRROR_ROTATE_90 = (1 << 5),
    gfxSurfaceTransform_HORIZONTAL_MIRROR_ROTATE_180 = (1 << 6),
    gfxSurfaceTransform_HORIZONTAL_MIRROR_ROTATE_270 = (1 << 7),
    gfxSurfaceTransform_INHERIT = (1 << 8)
EPI_GENREGION_END(gfxSurfaceTransform)
};

enum gfxCompositeAlpha : epiS32
{
EPI_GENREGION_BEGIN(gfxCompositeAlpha)
    gfxCompositeAlpha_OPAQUE = (1 << 0),
    gfxCompositeAlpha_PRE_MULTIPLIED = (1 << 1),
    gfxCompositeAlpha_POST_MULTIPLIED = (1 << 2),
    gfxCompositeAlpha_INHERIT = (1 << 3)
EPI_GENREGION_END(gfxCompositeAlpha)
};

enum gfxImageUsage : epiS32
{
EPI_GENREGION_BEGIN(gfxImageUsage)
    gfxImageUsage_TRANSFER_SRC = (1 << 0),
    gfxImageUsage_TRANSFER_DST = (1 << 1),
    gfxImageUsage_SAMPLED = (1 << 2),
    gfxImageUsage_STORAGE = (1 << 3),
    gfxImageUsage_COLOR_ATTACHMENT = (1 << 4),
    gfxImageUsage_DEPTH_STENCIL_ATTACHMENT = (1 << 5),
    gfxImageUsage_TRANSIENT_ATTACHMENT = (1 << 6),
    gfxImageUsage_INPUT_ATTACHMENT = (1 << 7),
    gfxImageUsage_SHADING_RATE_IMAGE = (1 << 8),
    gfxImageUsage_FRAGMENT_DENSITY_MAP = (1 << 9)
EPI_GENREGION_END(gfxImageUsage)
};

enum class gfxPipelineInputAssemblyType : epiS32
{
EPI_GENREGION_BEGIN(gfxPipelineInputAssemblyType)
    None = 0,
    PointList = 1,
    LineList = 2,
    LineStrip = 3,
    TriangleList = 4,
    TriangleStrip = 5
EPI_GENREGION_END(gfxPipelineInputAssemblyType)
};

enum class gfxSampleCount : epiS32
{
EPI_GENREGION_BEGIN(gfxSampleCount)
    Sample1 = 0,
    Sample2 = 1,
    Sample4 = 2,
    Sample8 = 3,
    Sample16 = 4,
    Sample32 = 5,
    Sample64 = 6
EPI_GENREGION_END(gfxSampleCount)
};

enum class gfxAttachmentLoadOp : epiS32
{
EPI_GENREGION_BEGIN(gfxAttachmentLoadOp)
    Load = 0,
    Clear = 1,
    DontCare = 2
EPI_GENREGION_END(gfxAttachmentLoadOp)
};

enum class gfxAttachmentStoreOp : epiS32
{
EPI_GENREGION_BEGIN(gfxAttachmentStoreOp)
    Store = 0,
    DontCare = 1
EPI_GENREGION_END(gfxAttachmentStoreOp)
};

enum class gfxImageLayout : epiS32
{
EPI_GENREGION_BEGIN(gfxImageLayout)
    Undefined = 0,
    General = 1,
    ColorAttachmentOptimal = 2,
    DepthStencilAttachmentOptimal = 3,
    DepthStencilReadOnlyOptimal = 4,
    ShaderReadOnlyOptimal = 5,
    TransferSrcOptimal = 6,
    TransferDstOptimal = 7,
    Preinitialized = 8,
    DepthReadOnlyStencilAttachmentOptimal = 9,
    DepthAttachmentStencilReadOnlyOptimal = 10,
    DepthAttachmentOptimal = 11,
    DepthReadOnlyOptimal = 12,
    StencilAttachmentOptimal = 13,
    StencilReadOnlyOptimal = 14,
    PresentSrc = 15,
    SharedPresent = 16,
    ShadingRateOptimal = 17,
    FragmentDensityMapOptimal = 18
EPI_GENREGION_END(gfxImageLayout)
};

enum class gfxPipelineBindPoint : epiS32
{
EPI_GENREGION_BEGIN(gfxPipelineBindPoint)
    Graphics = 0,
    Compute = 1,
    RayTracing = 2
EPI_GENREGION_END(gfxPipelineBindPoint)
};

enum class gfxPolygonMode : epiS32
{
EPI_GENREGION_BEGIN(gfxPolygonMode)
    Fill = 0,
    Line = 1,
    Point = 2
EPI_GENREGION_END(gfxPolygonMode)
};

enum class gfxCullMode : epiS32
{
EPI_GENREGION_BEGIN(gfxCullMode)
    None = 0,
    Front = 1,
    Back = 2,
    FrontBack = 3
EPI_GENREGION_END(gfxCullMode)
};

enum class gfxFrontFace : epiS32
{
EPI_GENREGION_BEGIN(gfxFrontFace)
    CW = 0,
    CCW = 1
EPI_GENREGION_END(gfxFrontFace)
};

enum class gfxBlendFactor : epiS32
{
EPI_GENREGION_BEGIN(gfxBlendFactor)
    Zero = 0,
    One = 1,
    SrcColor = 2,
    OneMinusSrcColor = 3,
    DstColor = 4,
    OneMinusDstColor = 5,
    SrcAlpha = 6,
    OneMinusSrcAlpha = 7,
    DstAlpha = 8,
    OneMinusDstAlpha = 9,
    ConstantColor = 10,
    OneMinusConstantColor = 11,
    ConstantAlpha = 12,
    OneMinusConstantAlpha = 13,
    SrcAlphaSaturate = 14,
    Src1Color = 15,
    OneMinusSrc1Color = 16,
    Src1Alpha = 17,
    OneMinusSrc1Alpha = 18
EPI_GENREGION_END(gfxBlendFactor)
};

enum class gfxBlendOp : epiS32
{
EPI_GENREGION_BEGIN(gfxBlendOp)
    Add = 0,
    Subtract = 1,
    ReverseSubtract = 2,
    MIN = 3,
    MAX = 4,
    Zero = 5,
    Src = 6,
    Dst = 7,
    SrcOver = 8,
    DstOver = 9,
    SrcIn = 10,
    DstIn = 11,
    SrcOut = 12,
    DstOut = 13,
    SrcAtop = 14,
    DstAtop = 15,
    Xor = 16,
    Multiply = 17,
    Screen = 18,
    Overlay = 19,
    Darken = 20,
    Lighten = 21,
    ColorDodge = 22,
    ColorBurn = 23,
    Hardlight = 24,
    Softlight = 25,
    Difference = 26,
    Exclusion = 27,
    Invert = 28,
    InvertRGB = 29,
    LinearDodge = 30,
    LinearBurn = 31,
    VividLight = 32,
    LinearLight = 33,
    PinLight = 34,
    HardMix = 35,
    HSL_HUE = 36,
    HSL_Saturation = 37,
    HSL_Color = 38,
    HSL_Luminosity = 39,
    Plus = 40,
    PlusClamped = 41,
    PlusClampedAlpha = 42,
    PlusDarker = 43,
    Minus = 44,
    MinusClamped = 45,
    Contrast = 46,
    InvertOVG = 47,
    Red = 48,
    Green = 49,
    Blue = 50
EPI_GENREGION_END(gfxBlendOp)
};

enum gfxColorComponent : epiS32
{
EPI_GENREGION_BEGIN(gfxColorComponent)
    gfxColorComponent_R = (1 << 0),
    gfxColorComponent_G = (1 << 1),
    gfxColorComponent_B = (1 << 2),
    gfxColorComponent_A = (1 << 3),
    gfxColorComponent_RGB = gfxColorComponent_R | gfxColorComponent_G | gfxColorComponent_B,
    gfxColorComponent_RGBA = gfxColorComponent_R | gfxColorComponent_G | gfxColorComponent_B | gfxColorComponent_A
EPI_GENREGION_END(gfxColorComponent)
};

enum class gfxLogicOp : epiS32
{
EPI_GENREGION_BEGIN(gfxLogicOp)
    Clear = 0,
    And = 1,
    AndReverse = 2,
    Copy = 3,
    AndInverted = 4,
    None = 5,
    Xor = 6,
    Or = 7,
    Nor = 8,
    Equivalent = 9,
    Invert = 10,
    OrReverse = 11,
    CopyInverted = 12,
    OrInverted = 13,
    Nand = 14,
    Set = 15
EPI_GENREGION_END(gfxLogicOp)
};

enum class gfxTextureViewType : epiS32
{
EPI_GENREGION_BEGIN(gfxTextureViewType)
    TextureView1D = 0,
    TextureView2D = 1,
    TextureView3D = 2,
    TextureViewCube = 3,
    TextureView1DArray = 4,
    TextureView2DArray = 5,
    TextureViewCubeArray = 6
EPI_GENREGION_END(gfxTextureViewType)
};

enum gfxPipelineStage : epiS32
{
EPI_GENREGION_BEGIN(gfxPipelineStage)
    gfxPipelineStage_TopOfPipe = (1 << 0),
    gfxPipelineStage_DrawIndirect = (1 << 1),
    gfxPipelineStage_VertexInput = (1 << 2),
    gfxPipelineStage_VertexShader = (1 << 3),
    gfxPipelineStage_TessellationControlShader = (1 << 4),
    gfxPipelineStage_TessellationEvaluationShader = (1 << 5),
    gfxPipelineStage_GeometryShader = (1 << 6),
    gfxPipelineStage_FragmentShader = (1 << 7),
    gfxPipelineStage_EarlyFragmentTests = (1 << 8),
    gfxPipelineStage_LateFragmentTests = (1 << 9),
    gfxPipelineStage_ColorAttachmentOutput = (1 << 10),
    gfxPipelineStage_ComputeShader = (1 << 11),
    gfxPipelineStage_Transfer = (1 << 12),
    gfxPipelineStage_BottomOfPipe = (1 << 13),
    gfxPipelineStage_Host = (1 << 14),
    gfxPipelineStage_AllGraphics = (1 << 15),
    gfxPipelineStage_AllCommands = (1 << 16),
    gfxPipelineStage_TransformFeedback = (1 << 17),
    gfxPipelineStage_ConditionalRendering = (1 << 18),
    gfxPipelineStage_AccelerationStructureBuild = (1 << 19),
    gfxPipelineStage_RayTracingShader = (1 << 20),
    gfxPipelineStage_ShadingRateImage = (1 << 21),
    gfxPipelineStage_TaskShader = (1 << 22),
    gfxPipelineStage_MeshShader = (1 << 23),
    gfxPipelineStage_FragmentDensityProcess = (1 << 24),
    gfxPipelineStage_CommandPreprocess = (1 << 25)
EPI_GENREGION_END(gfxPipelineStage)
};

enum gfxAccess : epiS32
{
EPI_GENREGION_BEGIN(gfxAccess)
    gfxAccess_IndirectCommandRead = (1 << 0),
    gfxAccess_IndexRead = (1 << 1),
    gfxAccess_VertexAttributeRead = (1 << 2),
    gfxAccess_UniformRead = (1 << 3),
    gfxAccess_InputAttachmentRead = (1 << 4),
    gfxAccess_ShaderRead = (1 << 5),
    gfxAccess_ShaderWrite = (1 << 6),
    gfxAccess_ColorAttachmentRead = (1 << 7),
    gfxAccess_ColorAttachmentWrite = (1 << 8),
    gfxAccess_DepthStencilAttachmentRead = (1 << 9),
    gfxAccess_DepthStencilAttachmentWrite = (1 << 10),
    gfxAccess_TransferRead = (1 << 11),
    gfxAccess_TransferWrite = (1 << 12),
    gfxAccess_HostRead = (1 << 13),
    gfxAccess_HostWrite = (1 << 14),
    gfxAccess_MemoryRead = (1 << 15),
    gfxAccess_MemoryWrite = (1 << 16),
    gfxAccess_TransformFeedbackWrite = (1 << 17),
    gfxAccess_TransformFeedbackCounterRead = (1 << 18),
    gfxAccess_TransformFeedbackCounterWrite = (1 << 19),
    gfxAccess_ConditionalRenderingRead = (1 << 20),
    gfxAccess_ColorAttachmentReadNonCoherent = (1 << 21),
    gfxAccess_AccelerationStructureRead = (1 << 22),
    gfxAccess_AccelerationStructureWrite = (1 << 23),
    gfxAccess_ShadingRateImageRead = (1 << 24),
    gfxAccess_FragmentDensityMapRead = (1 << 25),
    gfxAccess_CommandPreprocessRead = (1 << 26),
    gfxAccess_CommandPreprocessWrite = (1 << 27)
EPI_GENREGION_END(gfxAccess)
};

enum gfxDependency : epiS32
{
EPI_GENREGION_BEGIN(gfxDependency)
    gfxDependency_ByRegion = (1 << 0),
    gfxDependency_DeviceGroup = (1 << 1),
    gfxDependency_ViewLocal = (1 << 2)
EPI_GENREGION_END(gfxDependency)
};

enum class gfxPipelineDynamicState : epiS32
{
EPI_GENREGION_BEGIN(gfxPipelineDynamicState)
    Viewport = 0,
    Scissor = 1,
    LineWidth = 2,
    DepthBias = 3,
    BlendConstants = 4,
    DepthBounds = 5,
    StencilCompareMask = 6,
    StencilWriteMask = 7,
    StencilReference = 8,
    ViewportWScaling = 9,
    DiscardRectangle = 10,
    SampleLocations = 11,
    RayTracingPipelineStackSize = 12,
    ViewportShadingRatePalette = 13,
    ViewportCoarseSampleOrder = 14,
    ExclusiveScissor = 15,
    FragmentShadingRate = 16,
    LineStipple = 17,
    CullMode = 18,
    FrontFace = 19,
    PrimitiveTopology = 20,
    ViewportWithCount = 21,
    ScissorWithCount = 22,
    VertexInputBindingStride = 23,
    DepthTestEnable = 24,
    DepthWriteEnable = 25,
    DepthCompareOp = 26,
    DepthBoundsTestEnable = 27,
    StencilTestEnable = 28,
    StencilOp = 29,
    COUNT = 30
EPI_GENREGION_END(gfxPipelineDynamicState)
};

enum class gfxPipelineVertexInputRate : epiS32
{
EPI_GENREGION_BEGIN(gfxPipelineVertexInputRate)
    Vertex = 0,
    Instance = 1
EPI_GENREGION_END(gfxPipelineVertexInputRate)
};

enum gfxBufferUsage : epiS32
{
EPI_GENREGION_BEGIN(gfxBufferUsage)
    gfxBufferUsage_TransferSrc = (1 << 0),
    gfxBufferUsage_TransferDst = (1 << 1),
    gfxBufferUsage_UniformTexelBuffer = (1 << 2),
    gfxBufferUsage_StorageTexelBuffer = (1 << 3),
    gfxBufferUsage_UniformBuffer = (1 << 4),
    gfxBufferUsage_StorageBuffer = (1 << 5),
    gfxBufferUsage_IndexBuffer = (1 << 6),
    gfxBufferUsage_VertexBuffer = (1 << 7),
    gfxBufferUsage_IndirectBuffer = (1 << 8),
    gfxBufferUsage_ShaderDeviceAddress = (1 << 9),
    gfxBufferUsage_TransformFeedbackBuffer = (1 << 10),
    gfxBufferUsage_TransformFeedbackCounterBuffer = (1 << 11),
    gfxBufferUsage_ConditionalRendering = (1 << 12),
    gfxBufferUsage_AccelerationStructureBuildInputReadOnly = (1 << 13),
    gfxBufferUsage_AccelerationStructureStorage = (1 << 14),
    gfxBufferUsage_ShaderBindingTable = (1 << 15)
EPI_GENREGION_END(gfxBufferUsage)
};

enum gfxDeviceMemoryProperty : epiS32
{
EPI_GENREGION_BEGIN(gfxDeviceMemoryProperty)
    gfxDeviceMemoryProperty_DeviceLocal = (1 << 0),
    gfxDeviceMemoryProperty_HostVisible = (1 << 1),
    gfxDeviceMemoryProperty_HostCoherent = (1 << 2),
    gfxDeviceMemoryProperty_HostCached = (1 << 3),
    gfxDeviceMemoryProperty_LazilyAllocated = (1 << 4),
    gfxDeviceMemoryProperty_Protected = (1 << 5),
    gfxDeviceMemoryProperty_DeviceCoherent = (1 << 6),
    gfxDeviceMemoryProperty_DeviceUncached = (1 << 7)
EPI_GENREGION_END(gfxDeviceMemoryProperty)
};

enum gfxCommandPoolUsage : epiS32
{
EPI_GENREGION_BEGIN(gfxCommandPoolUsage)
    gfxCommandPoolUsage_TRANSIENT = (1 << 0),
    gfxCommandPoolUsage_ResetCommandBuffer = (1 << 1),
    gfxCommandPoolUsage_Protected = (1 << 2)
EPI_GENREGION_END(gfxCommandPoolUsage)
};

enum gfxCommandBufferUsage : epiS32
{
EPI_GENREGION_BEGIN(gfxCommandBufferUsage)
    gfxCommandBufferUsage_OneTimeSubmit = (1 << 0),
    gfxCommandBufferUsage_RenderPassContinue = (1 << 1),
    gfxCommandBufferUsage_SimultaneousUse = (1 << 2)
EPI_GENREGION_END(gfxCommandBufferUsage)
};

enum class gfxIndexBufferType : epiS32
{
EPI_GENREGION_BEGIN(gfxIndexBufferType)
    UInt16 = 0,
    UInt32 = 1,
    None = 2,
    UInt8 = 3
EPI_GENREGION_END(gfxIndexBufferType)
};

enum gfxShaderStage : epiS32
{
EPI_GENREGION_BEGIN(gfxShaderStage)
    gfxShaderStage_Vertex = (1 << 0),
    gfxShaderStage_TessellationControl = (1 << 1),
    gfxShaderStage_TessellationEvaluation = (1 << 2),
    gfxShaderStage_Geometry = (1 << 3),
    gfxShaderStage_Fragment = (1 << 4),
    gfxShaderStage_Compute = (1 << 5),
    gfxShaderStage_AllGraphics = gfxShaderStage_Vertex | gfxShaderStage_TessellationControl | gfxShaderStage_TessellationEvaluation | gfxShaderStage_Geometry | gfxShaderStage_Fragment,
    gfxShaderStage_Raygen = (1 << 6),
    gfxShaderStage_AnyHit = (1 << 7),
    gfxShaderStage_ClosestHit = (1 << 8),
    gfxShaderStage_Miss = (1 << 9),
    gfxShaderStage_Intersection = (1 << 10),
    gfxShaderStage_Callable = (1 << 11),
    gfxShaderStage_Task = (1 << 12),
    gfxShaderStage_Mesh = (1 << 13),
    gfxShaderStage_All = gfxShaderStage_Vertex | gfxShaderStage_TessellationControl | gfxShaderStage_TessellationEvaluation | gfxShaderStage_Geometry | gfxShaderStage_Fragment | gfxShaderStage_Compute | gfxShaderStage_Raygen | gfxShaderStage_AnyHit | gfxShaderStage_ClosestHit | gfxShaderStage_Miss | gfxShaderStage_Intersection | gfxShaderStage_Callable | gfxShaderStage_Task | gfxShaderStage_Mesh
EPI_GENREGION_END(gfxShaderStage)
};

enum gfxDescriptorPoolUsage : epiS32
{
EPI_GENREGION_BEGIN(gfxDescriptorPoolUsage)
    gfxDescriptorPoolUsage_FreeDescriptorSet = (1 << 0),
    gfxDescriptorPoolUsage_UpdateAfterBind = (1 << 1),
    gfxDescriptorPoolUsage_HostOnly = (1 << 2)
EPI_GENREGION_END(gfxDescriptorPoolUsage)
};

enum class gfxDescriptorType : epiS32
{
EPI_GENREGION_BEGIN(gfxDescriptorType)
    None = 0,
    Sampler = 1,
    CombinedImageSampler = 2,
    SampledImage = 3,
    StorageImage = 4,
    UniformTexelBuffer = 5,
    StorageTexelBuffer = 6,
    UniformBuffer = 7,
    StorageBuffer = 8,
    UniformBufferDynamic = 9,
    StorageBufferDynamic = 10,
    InputAttachment = 11,
    InlineUniformBlock = 12,
    AccelerationStructure = 13,
    AccelerationStructureNV = 14,
    MutableValve = 15
EPI_GENREGION_END(gfxDescriptorType)
};

enum gfxDescriptorSetLayoutUsage : epiS32
{
EPI_GENREGION_BEGIN(gfxDescriptorSetLayoutUsage)
    gfxDescriptorSetLayoutUsage_UpdateAfterBindPool = (1 << 0),
    gfxDescriptorSetLayoutUsage_PushDescriptor = (1 << 1),
    gfxDescriptorSetLayoutUsage_HostOnlyPool = (1 << 2)
EPI_GENREGION_END(gfxDescriptorSetLayoutUsage)
};

enum gfxFenceCreateMask : epiS32
{
EPI_GENREGION_BEGIN(gfxFenceCreateMask)
    gfxFenceCreateMask_Signaled = (1 << 0)
EPI_GENREGION_END(gfxFenceCreateMask)
};

enum gfxSemaphoreCreateMask : epiS32
{
EPI_GENREGION_BEGIN(gfxSemaphoreCreateMask)
EPI_GENREGION_END(gfxSemaphoreCreateMask)
};

enum gfxSemaphoreWaitMask : epiS32
{
EPI_GENREGION_BEGIN(gfxSemaphoreWaitMask)
    gfxSemaphoreWaitMask_WaitAny = (1 << 0)
EPI_GENREGION_END(gfxSemaphoreWaitMask)
};

enum class gfxImageTiling : epiS32
{
EPI_GENREGION_BEGIN(gfxImageTiling)
    Optimal = 0,
    Linear = 1
EPI_GENREGION_END(gfxImageTiling)
};

enum gfxImageAspect : epiS32
{
EPI_GENREGION_BEGIN(gfxImageAspect)
    gfxImageAspect_Color = (1 << 0),
    gfxImageAspect_Depth = (1 << 1),
    gfxImageAspect_Stencil = (1 << 2),
    gfxImageAspect_Metadata = (1 << 3),
    gfxImageAspect_Plane0 = (1 << 4),
    gfxImageAspect_Plane1 = (1 << 5),
    gfxImageAspect_Plane2 = (1 << 6),
    gfxImageAspect_MemoryPlane0 = (1 << 7),
    gfxImageAspect_MemoryPlane1 = (1 << 8),
    gfxImageAspect_MemoryPlane2 = (1 << 9),
    gfxImageAspect_MemoryPlane3 = (1 << 10)
EPI_GENREGION_END(gfxImageAspect)
};

enum class gfxCompareOp : epiS32
{
EPI_GENREGION_BEGIN(gfxCompareOp)
    Never = 0,
    Less = 1,
    Equal = 2,
    LessOrEqual = 3,
    Greater = 4,
    NotEqual = 5,
    GreaterOrEqual = 6,
    Always = 7
EPI_GENREGION_END(gfxCompareOp)
};

enum gfxSamplerCreateMask : epiS32
{
EPI_GENREGION_BEGIN(gfxSamplerCreateMask)
    gfxSamplerCreateMask_Subsampled = (1 << 0),
    gfxSamplerCreateMask_SubsampledCoarseReconstruction = (1 << 1)
EPI_GENREGION_END(gfxSamplerCreateMask)
};

enum class gfxSamplerFilterMode : epiS32
{
EPI_GENREGION_BEGIN(gfxSamplerFilterMode)
    Nearest = 0,
    Linear = 1,
    Cubic = 2
EPI_GENREGION_END(gfxSamplerFilterMode)
};

enum class gfxSamplerMipmapMode : epiS32
{
EPI_GENREGION_BEGIN(gfxSamplerMipmapMode)
    Nearest = 0,
    Linear = 1
EPI_GENREGION_END(gfxSamplerMipmapMode)
};

enum class gfxSamplerAddressMode : epiS32
{
EPI_GENREGION_BEGIN(gfxSamplerAddressMode)
    Repeat = 0,
    MirroredRepeat = 1,
    ClampToEdge = 2,
    ClampToBorder = 3,
    MirroredClampToEdge = 4
EPI_GENREGION_END(gfxSamplerAddressMode)
};

enum class gfxSamplerBorderColor : epiS32
{
EPI_GENREGION_BEGIN(gfxSamplerBorderColor)
    FloatTransparentBlack = 0,
    IntTransparentBlack = 1,
    FloatOpaqueBlack = 2,
    IntOpaqueBlack = 3,
    FloatOpaqueWhite = 4,
    IntOpaqueWhite = 5,
    FloatCustom = 6,
    IntCustom = 7
EPI_GENREGION_END(gfxSamplerBorderColor)
};

enum class gfxComponentSwizzle : epiS32
{
EPI_GENREGION_BEGIN(gfxComponentSwizzle)
    Identity = 0,
    Zero = 1,
    One = 2,
    R = 3,
    G = 4,
    B = 5,
    A = 6
EPI_GENREGION_END(gfxComponentSwizzle)
};

EPI_NAMESPACE_END()
