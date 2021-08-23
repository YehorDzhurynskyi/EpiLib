#include "EpiGraphicsImplVK/gfxEnumVK.h"

EPI_NAMESPACE_BEGIN()

gfxFormat gfxFormatFrom(VkFormat formatVk)
{
    gfxFormat format = gfxFormat::UNDEFINED;
    switch (formatVk)
    {
    case VK_FORMAT_UNDEFINED: format = gfxFormat::UNDEFINED; break;
    case VK_FORMAT_R4G4_UNORM_PACK8: format = gfxFormat::R4G4_UNORM_PACK8; break;
    case VK_FORMAT_R4G4B4A4_UNORM_PACK16: format = gfxFormat::R4G4B4A4_UNORM_PACK16; break;
    case VK_FORMAT_B4G4R4A4_UNORM_PACK16: format = gfxFormat::B4G4R4A4_UNORM_PACK16; break;
    case VK_FORMAT_R5G6B5_UNORM_PACK16: format = gfxFormat::R5G6B5_UNORM_PACK16; break;
    case VK_FORMAT_B5G6R5_UNORM_PACK16: format = gfxFormat::B5G6R5_UNORM_PACK16; break;
    case VK_FORMAT_R5G5B5A1_UNORM_PACK16: format = gfxFormat::R5G5B5A1_UNORM_PACK16; break;
    case VK_FORMAT_B5G5R5A1_UNORM_PACK16: format = gfxFormat::B5G5R5A1_UNORM_PACK16; break;
    case VK_FORMAT_A1R5G5B5_UNORM_PACK16: format = gfxFormat::A1R5G5B5_UNORM_PACK16; break;
    case VK_FORMAT_R8_UNORM: format = gfxFormat::R8_UNORM; break;
    case VK_FORMAT_R8_SNORM: format = gfxFormat::R8_SNORM; break;
    case VK_FORMAT_R8_USCALED: format = gfxFormat::R8_USCALED; break;
    case VK_FORMAT_R8_SSCALED: format = gfxFormat::R8_SSCALED; break;
    case VK_FORMAT_R8_UINT: format = gfxFormat::R8_UINT; break;
    case VK_FORMAT_R8_SINT: format = gfxFormat::R8_SINT; break;
    case VK_FORMAT_R8_SRGB: format = gfxFormat::R8_SRGB; break;
    case VK_FORMAT_R8G8_UNORM: format = gfxFormat::R8G8_UNORM; break;
    case VK_FORMAT_R8G8_SNORM: format = gfxFormat::R8G8_SNORM; break;
    case VK_FORMAT_R8G8_USCALED: format = gfxFormat::R8G8_USCALED; break;
    case VK_FORMAT_R8G8_SSCALED: format = gfxFormat::R8G8_SSCALED; break;
    case VK_FORMAT_R8G8_UINT: format = gfxFormat::R8G8_UINT; break;
    case VK_FORMAT_R8G8_SINT: format = gfxFormat::R8G8_SINT; break;
    case VK_FORMAT_R8G8_SRGB: format = gfxFormat::R8G8_SRGB; break;
    case VK_FORMAT_R8G8B8_UNORM: format = gfxFormat::R8G8B8_UNORM; break;
    case VK_FORMAT_R8G8B8_SNORM: format = gfxFormat::R8G8B8_SNORM; break;
    case VK_FORMAT_R8G8B8_USCALED: format = gfxFormat::R8G8B8_USCALED; break;
    case VK_FORMAT_R8G8B8_SSCALED: format = gfxFormat::R8G8B8_SSCALED; break;
    case VK_FORMAT_R8G8B8_UINT: format = gfxFormat::R8G8B8_UINT; break;
    case VK_FORMAT_R8G8B8_SINT: format = gfxFormat::R8G8B8_SINT; break;
    case VK_FORMAT_R8G8B8_SRGB: format = gfxFormat::R8G8B8_SRGB; break;
    case VK_FORMAT_B8G8R8_UNORM: format = gfxFormat::B8G8R8_UNORM; break;
    case VK_FORMAT_B8G8R8_SNORM: format = gfxFormat::B8G8R8_SNORM; break;
    case VK_FORMAT_B8G8R8_USCALED: format = gfxFormat::B8G8R8_USCALED; break;
    case VK_FORMAT_B8G8R8_SSCALED: format = gfxFormat::B8G8R8_SSCALED; break;
    case VK_FORMAT_B8G8R8_UINT: format = gfxFormat::B8G8R8_UINT; break;
    case VK_FORMAT_B8G8R8_SINT: format = gfxFormat::B8G8R8_SINT; break;
    case VK_FORMAT_B8G8R8_SRGB: format = gfxFormat::B8G8R8_SRGB; break;
    case VK_FORMAT_R8G8B8A8_UNORM: format = gfxFormat::R8G8B8A8_UNORM; break;
    case VK_FORMAT_R8G8B8A8_SNORM: format = gfxFormat::R8G8B8A8_SNORM; break;
    case VK_FORMAT_R8G8B8A8_USCALED: format = gfxFormat::R8G8B8A8_USCALED; break;
    case VK_FORMAT_R8G8B8A8_SSCALED: format = gfxFormat::R8G8B8A8_SSCALED; break;
    case VK_FORMAT_R8G8B8A8_UINT: format = gfxFormat::R8G8B8A8_UINT; break;
    case VK_FORMAT_R8G8B8A8_SINT: format = gfxFormat::R8G8B8A8_SINT; break;
    case VK_FORMAT_R8G8B8A8_SRGB: format = gfxFormat::R8G8B8A8_SRGB; break;
    case VK_FORMAT_B8G8R8A8_UNORM: format = gfxFormat::B8G8R8A8_UNORM; break;
    case VK_FORMAT_B8G8R8A8_SNORM: format = gfxFormat::B8G8R8A8_SNORM; break;
    case VK_FORMAT_B8G8R8A8_USCALED: format = gfxFormat::B8G8R8A8_USCALED; break;
    case VK_FORMAT_B8G8R8A8_SSCALED: format = gfxFormat::B8G8R8A8_SSCALED; break;
    case VK_FORMAT_B8G8R8A8_UINT: format = gfxFormat::B8G8R8A8_UINT; break;
    case VK_FORMAT_B8G8R8A8_SINT: format = gfxFormat::B8G8R8A8_SINT; break;
    case VK_FORMAT_B8G8R8A8_SRGB: format = gfxFormat::B8G8R8A8_SRGB; break;
    case VK_FORMAT_A8B8G8R8_UNORM_PACK32: format = gfxFormat::A8B8G8R8_UNORM_PACK32; break;
    case VK_FORMAT_A8B8G8R8_SNORM_PACK32: format = gfxFormat::A8B8G8R8_SNORM_PACK32; break;
    case VK_FORMAT_A8B8G8R8_USCALED_PACK32: format = gfxFormat::A8B8G8R8_USCALED_PACK32; break;
    case VK_FORMAT_A8B8G8R8_SSCALED_PACK32: format = gfxFormat::A8B8G8R8_SSCALED_PACK32; break;
    case VK_FORMAT_A8B8G8R8_UINT_PACK32: format = gfxFormat::A8B8G8R8_UINT_PACK32; break;
    case VK_FORMAT_A8B8G8R8_SINT_PACK32: format = gfxFormat::A8B8G8R8_SINT_PACK32; break;
    case VK_FORMAT_A8B8G8R8_SRGB_PACK32: format = gfxFormat::A8B8G8R8_SRGB_PACK32; break;
    case VK_FORMAT_A2R10G10B10_UNORM_PACK32: format = gfxFormat::A2R10G10B10_UNORM_PACK32; break;
    case VK_FORMAT_A2R10G10B10_SNORM_PACK32: format = gfxFormat::A2R10G10B10_SNORM_PACK32; break;
    case VK_FORMAT_A2R10G10B10_USCALED_PACK32: format = gfxFormat::A2R10G10B10_USCALED_PACK32; break;
    case VK_FORMAT_A2R10G10B10_SSCALED_PACK32: format = gfxFormat::A2R10G10B10_SSCALED_PACK32; break;
    case VK_FORMAT_A2R10G10B10_UINT_PACK32: format = gfxFormat::A2R10G10B10_UINT_PACK32; break;
    case VK_FORMAT_A2R10G10B10_SINT_PACK32: format = gfxFormat::A2R10G10B10_SINT_PACK32; break;
    case VK_FORMAT_A2B10G10R10_UNORM_PACK32: format = gfxFormat::A2B10G10R10_UNORM_PACK32; break;
    case VK_FORMAT_A2B10G10R10_SNORM_PACK32: format = gfxFormat::A2B10G10R10_SNORM_PACK32; break;
    case VK_FORMAT_A2B10G10R10_USCALED_PACK32: format = gfxFormat::A2B10G10R10_USCALED_PACK32; break;
    case VK_FORMAT_A2B10G10R10_SSCALED_PACK32: format = gfxFormat::A2B10G10R10_SSCALED_PACK32; break;
    case VK_FORMAT_A2B10G10R10_UINT_PACK32: format = gfxFormat::A2B10G10R10_UINT_PACK32; break;
    case VK_FORMAT_A2B10G10R10_SINT_PACK32: format = gfxFormat::A2B10G10R10_SINT_PACK32; break;
    case VK_FORMAT_R16_UNORM: format = gfxFormat::R16_UNORM; break;
    case VK_FORMAT_R16_SNORM: format = gfxFormat::R16_SNORM; break;
    case VK_FORMAT_R16_USCALED: format = gfxFormat::R16_USCALED; break;
    case VK_FORMAT_R16_SSCALED: format = gfxFormat::R16_SSCALED; break;
    case VK_FORMAT_R16_UINT: format = gfxFormat::R16_UINT; break;
    case VK_FORMAT_R16_SINT: format = gfxFormat::R16_SINT; break;
    case VK_FORMAT_R16_SFLOAT: format = gfxFormat::R16_SFLOAT; break;
    case VK_FORMAT_R16G16_UNORM: format = gfxFormat::R16G16_UNORM; break;
    case VK_FORMAT_R16G16_SNORM: format = gfxFormat::R16G16_SNORM; break;
    case VK_FORMAT_R16G16_USCALED: format = gfxFormat::R16G16_USCALED; break;
    case VK_FORMAT_R16G16_SSCALED: format = gfxFormat::R16G16_SSCALED; break;
    case VK_FORMAT_R16G16_UINT: format = gfxFormat::R16G16_UINT; break;
    case VK_FORMAT_R16G16_SINT: format = gfxFormat::R16G16_SINT; break;
    case VK_FORMAT_R16G16_SFLOAT: format = gfxFormat::R16G16_SFLOAT; break;
    case VK_FORMAT_R16G16B16_UNORM: format = gfxFormat::R16G16B16_UNORM; break;
    case VK_FORMAT_R16G16B16_SNORM: format = gfxFormat::R16G16B16_SNORM; break;
    case VK_FORMAT_R16G16B16_USCALED: format = gfxFormat::R16G16B16_USCALED; break;
    case VK_FORMAT_R16G16B16_SSCALED: format = gfxFormat::R16G16B16_SSCALED; break;
    case VK_FORMAT_R16G16B16_UINT: format = gfxFormat::R16G16B16_UINT; break;
    case VK_FORMAT_R16G16B16_SINT: format = gfxFormat::R16G16B16_SINT; break;
    case VK_FORMAT_R16G16B16_SFLOAT: format = gfxFormat::R16G16B16_SFLOAT; break;
    case VK_FORMAT_R16G16B16A16_UNORM: format = gfxFormat::R16G16B16A16_UNORM; break;
    case VK_FORMAT_R16G16B16A16_SNORM: format = gfxFormat::R16G16B16A16_SNORM; break;
    case VK_FORMAT_R16G16B16A16_USCALED: format = gfxFormat::R16G16B16A16_USCALED; break;
    case VK_FORMAT_R16G16B16A16_SSCALED: format = gfxFormat::R16G16B16A16_SSCALED; break;
    case VK_FORMAT_R16G16B16A16_UINT: format = gfxFormat::R16G16B16A16_UINT; break;
    case VK_FORMAT_R16G16B16A16_SINT: format = gfxFormat::R16G16B16A16_SINT; break;
    case VK_FORMAT_R16G16B16A16_SFLOAT: format = gfxFormat::R16G16B16A16_SFLOAT; break;
    case VK_FORMAT_R32_UINT: format = gfxFormat::R32_UINT; break;
    case VK_FORMAT_R32_SINT: format = gfxFormat::R32_SINT; break;
    case VK_FORMAT_R32_SFLOAT: format = gfxFormat::R32_SFLOAT; break;
    case VK_FORMAT_R32G32_UINT: format = gfxFormat::R32G32_UINT; break;
    case VK_FORMAT_R32G32_SINT: format = gfxFormat::R32G32_SINT; break;
    case VK_FORMAT_R32G32_SFLOAT: format = gfxFormat::R32G32_SFLOAT; break;
    case VK_FORMAT_R32G32B32_UINT: format = gfxFormat::R32G32B32_UINT; break;
    case VK_FORMAT_R32G32B32_SINT: format = gfxFormat::R32G32B32_SINT; break;
    case VK_FORMAT_R32G32B32_SFLOAT: format = gfxFormat::R32G32B32_SFLOAT; break;
    case VK_FORMAT_R32G32B32A32_UINT: format = gfxFormat::R32G32B32A32_UINT; break;
    case VK_FORMAT_R32G32B32A32_SINT: format = gfxFormat::R32G32B32A32_SINT; break;
    case VK_FORMAT_R32G32B32A32_SFLOAT: format = gfxFormat::R32G32B32A32_SFLOAT; break;
    case VK_FORMAT_R64_UINT: format = gfxFormat::R64_UINT; break;
    case VK_FORMAT_R64_SINT: format = gfxFormat::R64_SINT; break;
    case VK_FORMAT_R64_SFLOAT: format = gfxFormat::R64_SFLOAT; break;
    case VK_FORMAT_R64G64_UINT: format = gfxFormat::R64G64_UINT; break;
    case VK_FORMAT_R64G64_SINT: format = gfxFormat::R64G64_SINT; break;
    case VK_FORMAT_R64G64_SFLOAT: format = gfxFormat::R64G64_SFLOAT; break;
    case VK_FORMAT_R64G64B64_UINT: format = gfxFormat::R64G64B64_UINT; break;
    case VK_FORMAT_R64G64B64_SINT: format = gfxFormat::R64G64B64_SINT; break;
    case VK_FORMAT_R64G64B64_SFLOAT: format = gfxFormat::R64G64B64_SFLOAT; break;
    case VK_FORMAT_R64G64B64A64_UINT: format = gfxFormat::R64G64B64A64_UINT; break;
    case VK_FORMAT_R64G64B64A64_SINT: format = gfxFormat::R64G64B64A64_SINT; break;
    case VK_FORMAT_R64G64B64A64_SFLOAT: format = gfxFormat::R64G64B64A64_SFLOAT; break;
    case VK_FORMAT_B10G11R11_UFLOAT_PACK32: format = gfxFormat::B10G11R11_UFLOAT_PACK32; break;
    case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32: format = gfxFormat::E5B9G9R9_UFLOAT_PACK32; break;
    case VK_FORMAT_D16_UNORM: format = gfxFormat::D16_UNORM; break;
    case VK_FORMAT_X8_D24_UNORM_PACK32: format = gfxFormat::X8_D24_UNORM_PACK32; break;
    case VK_FORMAT_D32_SFLOAT: format = gfxFormat::D32_SFLOAT; break;
    case VK_FORMAT_S8_UINT: format = gfxFormat::S8_UINT; break;
    case VK_FORMAT_D16_UNORM_S8_UINT: format = gfxFormat::D16_UNORM_S8_UINT; break;
    case VK_FORMAT_D24_UNORM_S8_UINT: format = gfxFormat::D24_UNORM_S8_UINT; break;
    case VK_FORMAT_D32_SFLOAT_S8_UINT: format = gfxFormat::D32_SFLOAT_S8_UINT; break;
    case VK_FORMAT_BC1_RGB_UNORM_BLOCK: format = gfxFormat::BC1_RGB_UNORM_BLOCK; break;
    case VK_FORMAT_BC1_RGB_SRGB_BLOCK: format = gfxFormat::BC1_RGB_SRGB_BLOCK; break;
    case VK_FORMAT_BC1_RGBA_UNORM_BLOCK: format = gfxFormat::BC1_RGBA_UNORM_BLOCK; break;
    case VK_FORMAT_BC1_RGBA_SRGB_BLOCK: format = gfxFormat::BC1_RGBA_SRGB_BLOCK; break;
    case VK_FORMAT_BC2_UNORM_BLOCK: format = gfxFormat::BC2_UNORM_BLOCK; break;
    case VK_FORMAT_BC2_SRGB_BLOCK: format = gfxFormat::BC2_SRGB_BLOCK; break;
    case VK_FORMAT_BC3_UNORM_BLOCK: format = gfxFormat::BC3_UNORM_BLOCK; break;
    case VK_FORMAT_BC3_SRGB_BLOCK: format = gfxFormat::BC3_SRGB_BLOCK; break;
    case VK_FORMAT_BC4_UNORM_BLOCK: format = gfxFormat::BC4_UNORM_BLOCK; break;
    case VK_FORMAT_BC4_SNORM_BLOCK: format = gfxFormat::BC4_SNORM_BLOCK; break;
    case VK_FORMAT_BC5_UNORM_BLOCK: format = gfxFormat::BC5_UNORM_BLOCK; break;
    case VK_FORMAT_BC5_SNORM_BLOCK: format = gfxFormat::BC5_SNORM_BLOCK; break;
    case VK_FORMAT_BC6H_UFLOAT_BLOCK: format = gfxFormat::BC6H_UFLOAT_BLOCK; break;
    case VK_FORMAT_BC6H_SFLOAT_BLOCK: format = gfxFormat::BC6H_SFLOAT_BLOCK; break;
    case VK_FORMAT_BC7_UNORM_BLOCK: format = gfxFormat::BC7_UNORM_BLOCK; break;
    case VK_FORMAT_BC7_SRGB_BLOCK: format = gfxFormat::BC7_SRGB_BLOCK; break;
    case VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK: format = gfxFormat::ETC2_R8G8B8_UNORM_BLOCK; break;
    case VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK: format = gfxFormat::ETC2_R8G8B8_SRGB_BLOCK; break;
    case VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK: format = gfxFormat::ETC2_R8G8B8A1_UNORM_BLOCK; break;
    case VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK: format = gfxFormat::ETC2_R8G8B8A1_SRGB_BLOCK; break;
    case VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK: format = gfxFormat::ETC2_R8G8B8A8_UNORM_BLOCK; break;
    case VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK: format = gfxFormat::ETC2_R8G8B8A8_SRGB_BLOCK; break;
    case VK_FORMAT_EAC_R11_UNORM_BLOCK: format = gfxFormat::EAC_R11_UNORM_BLOCK; break;
    case VK_FORMAT_EAC_R11_SNORM_BLOCK: format = gfxFormat::EAC_R11_SNORM_BLOCK; break;
    case VK_FORMAT_EAC_R11G11_UNORM_BLOCK: format = gfxFormat::EAC_R11G11_UNORM_BLOCK; break;
    case VK_FORMAT_EAC_R11G11_SNORM_BLOCK: format = gfxFormat::EAC_R11G11_SNORM_BLOCK; break;
    case VK_FORMAT_ASTC_4x4_UNORM_BLOCK: format = gfxFormat::ASTC_4x4_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_4x4_SRGB_BLOCK: format = gfxFormat::ASTC_4x4_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_5x4_UNORM_BLOCK: format = gfxFormat::ASTC_5x4_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_5x4_SRGB_BLOCK: format = gfxFormat::ASTC_5x4_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_5x5_UNORM_BLOCK: format = gfxFormat::ASTC_5x5_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_5x5_SRGB_BLOCK: format = gfxFormat::ASTC_5x5_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_6x5_UNORM_BLOCK: format = gfxFormat::ASTC_6x5_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_6x5_SRGB_BLOCK: format = gfxFormat::ASTC_6x5_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_6x6_UNORM_BLOCK: format = gfxFormat::ASTC_6x6_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_6x6_SRGB_BLOCK: format = gfxFormat::ASTC_6x6_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_8x5_UNORM_BLOCK: format = gfxFormat::ASTC_8x5_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_8x5_SRGB_BLOCK: format = gfxFormat::ASTC_8x5_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_8x6_UNORM_BLOCK: format = gfxFormat::ASTC_8x6_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_8x6_SRGB_BLOCK: format = gfxFormat::ASTC_8x6_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_8x8_UNORM_BLOCK: format = gfxFormat::ASTC_8x8_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_8x8_SRGB_BLOCK: format = gfxFormat::ASTC_8x8_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_10x5_UNORM_BLOCK: format = gfxFormat::ASTC_10x5_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_10x5_SRGB_BLOCK: format = gfxFormat::ASTC_10x5_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_10x6_UNORM_BLOCK: format = gfxFormat::ASTC_10x6_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_10x6_SRGB_BLOCK: format = gfxFormat::ASTC_10x6_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_10x8_UNORM_BLOCK: format = gfxFormat::ASTC_10x8_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_10x8_SRGB_BLOCK: format = gfxFormat::ASTC_10x8_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_10x10_UNORM_BLOCK: format = gfxFormat::ASTC_10x10_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_10x10_SRGB_BLOCK: format = gfxFormat::ASTC_10x10_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_12x10_UNORM_BLOCK: format = gfxFormat::ASTC_12x10_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_12x10_SRGB_BLOCK: format = gfxFormat::ASTC_12x10_SRGB_BLOCK; break;
    case VK_FORMAT_ASTC_12x12_UNORM_BLOCK: format = gfxFormat::ASTC_12x12_UNORM_BLOCK; break;
    case VK_FORMAT_ASTC_12x12_SRGB_BLOCK: format = gfxFormat::ASTC_12x12_SRGB_BLOCK; break;
    case VK_FORMAT_G8B8G8R8_422_UNORM: format = gfxFormat::G8B8G8R8_422_UNORM; break;
    case VK_FORMAT_B8G8R8G8_422_UNORM: format = gfxFormat::B8G8R8G8_422_UNORM; break;
    case VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM: format = gfxFormat::G8_B8_R8_3PLANE_420_UNORM; break;
    case VK_FORMAT_G8_B8R8_2PLANE_420_UNORM: format = gfxFormat::G8_B8R8_2PLANE_420_UNORM; break;
    case VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM: format = gfxFormat::G8_B8_R8_3PLANE_422_UNORM; break;
    case VK_FORMAT_G8_B8R8_2PLANE_422_UNORM: format = gfxFormat::G8_B8R8_2PLANE_422_UNORM; break;
    case VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM: format = gfxFormat::G8_B8_R8_3PLANE_444_UNORM; break;
    case VK_FORMAT_R10X6_UNORM_PACK16: format = gfxFormat::R10X6_UNORM_PACK16; break;
    case VK_FORMAT_R10X6G10X6_UNORM_2PACK16: format = gfxFormat::R10X6G10X6_UNORM_2PACK16; break;
    case VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16: format = gfxFormat::R10X6G10X6B10X6A10X6_UNORM_4PACK16; break;
    case VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16: format = gfxFormat::G10X6B10X6G10X6R10X6_422_UNORM_4PACK16; break;
    case VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16: format = gfxFormat::B10X6G10X6R10X6G10X6_422_UNORM_4PACK16; break;
    case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: format = gfxFormat::G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16; break;
    case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16: format = gfxFormat::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16; break;
    case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: format = gfxFormat::G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16; break;
    case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16: format = gfxFormat::G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16; break;
    case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: format = gfxFormat::G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16; break;
    case VK_FORMAT_R12X4_UNORM_PACK16: format = gfxFormat::R12X4_UNORM_PACK16; break;
    case VK_FORMAT_R12X4G12X4_UNORM_2PACK16: format = gfxFormat::R12X4G12X4_UNORM_2PACK16; break;
    case VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16: format = gfxFormat::R12X4G12X4B12X4A12X4_UNORM_4PACK16; break;
    case VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16: format = gfxFormat::G12X4B12X4G12X4R12X4_422_UNORM_4PACK16; break;
    case VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16: format = gfxFormat::B12X4G12X4R12X4G12X4_422_UNORM_4PACK16; break;
    case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16: format = gfxFormat::G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16; break;
    case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16: format = gfxFormat::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16; break;
    case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16: format = gfxFormat::G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16; break;
    case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16: format = gfxFormat::G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16; break;
    case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16: format = gfxFormat::G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16; break;
    case VK_FORMAT_G16B16G16R16_422_UNORM: format = gfxFormat::G16B16G16R16_422_UNORM; break;
    case VK_FORMAT_B16G16R16G16_422_UNORM: format = gfxFormat::B16G16R16G16_422_UNORM; break;
    case VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM: format = gfxFormat::G16_B16_R16_3PLANE_420_UNORM; break;
    case VK_FORMAT_G16_B16R16_2PLANE_420_UNORM: format = gfxFormat::G16_B16R16_2PLANE_420_UNORM; break;
    case VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM: format = gfxFormat::G16_B16_R16_3PLANE_422_UNORM; break;
    case VK_FORMAT_G16_B16R16_2PLANE_422_UNORM: format = gfxFormat::G16_B16R16_2PLANE_422_UNORM; break;
    case VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM: format = gfxFormat::G16_B16_R16_3PLANE_444_UNORM; break;
    case VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG: format = gfxFormat::PVRTC1_2BPP_UNORM_BLOCK_IMG; break;
    case VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG: format = gfxFormat::PVRTC1_4BPP_UNORM_BLOCK_IMG; break;
    case VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG: format = gfxFormat::PVRTC2_2BPP_UNORM_BLOCK_IMG; break;
    case VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG: format = gfxFormat::PVRTC2_4BPP_UNORM_BLOCK_IMG; break;
    case VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG: format = gfxFormat::PVRTC1_2BPP_SRGB_BLOCK_IMG; break;
    case VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG: format = gfxFormat::PVRTC1_4BPP_SRGB_BLOCK_IMG; break;
    case VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG: format = gfxFormat::PVRTC2_2BPP_SRGB_BLOCK_IMG; break;
    case VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG: format = gfxFormat::PVRTC2_4BPP_SRGB_BLOCK_IMG; break;
    case VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_4x4_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_5x4_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_5x5_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_6x5_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_6x6_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_8x5_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_8x6_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_8x8_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_10x5_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_10x6_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_10x8_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_10x10_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_12x10_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT: format = gfxFormat::ASTC_12x12_SFLOAT_BLOCK_EXT; break;
    case VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT: format = gfxFormat::A4R4G4B4_UNORM_PACK16_EXT; break;
    case VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT: format = gfxFormat::A4B4G4R4_UNORM_PACK16_EXT; break;
    }

    return format;
}

gfxSurfaceColorSpace gfxSurfaceColorSpaceFrom(VkColorSpaceKHR colorSpaceVk)
{
    gfxSurfaceColorSpace colorSpace = gfxSurfaceColorSpace::SRGB_NONLINEAR;
    switch (colorSpaceVk)
    {
    case VK_COLOR_SPACE_SRGB_NONLINEAR_KHR: colorSpace = gfxSurfaceColorSpace::SRGB_NONLINEAR; break;
    case VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT: colorSpace = gfxSurfaceColorSpace::DISPLAY_P3_NONLINEAR_EXT; break;
    case VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT: colorSpace = gfxSurfaceColorSpace::EXTENDED_SRGB_LINEAR_EXT; break;
    case VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT: colorSpace = gfxSurfaceColorSpace::DISPLAY_P3_LINEAR_EXT; break;
    case VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT: colorSpace = gfxSurfaceColorSpace::DCI_P3_NONLINEAR_EXT; break;
    case VK_COLOR_SPACE_BT709_LINEAR_EXT: colorSpace = gfxSurfaceColorSpace::BT709_LINEAR_EXT; break;
    case VK_COLOR_SPACE_BT709_NONLINEAR_EXT: colorSpace = gfxSurfaceColorSpace::BT709_NONLINEAR_EXT; break;
    case VK_COLOR_SPACE_BT2020_LINEAR_EXT: colorSpace = gfxSurfaceColorSpace::BT2020_LINEAR_EXT; break;
    case VK_COLOR_SPACE_HDR10_ST2084_EXT: colorSpace = gfxSurfaceColorSpace::HDR10_ST2084_EXT; break;
    case VK_COLOR_SPACE_DOLBYVISION_EXT: colorSpace = gfxSurfaceColorSpace::DOLBYVISION_EXT; break;
    case VK_COLOR_SPACE_HDR10_HLG_EXT: colorSpace = gfxSurfaceColorSpace::HDR10_HLG_EXT; break;
    case VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT: colorSpace = gfxSurfaceColorSpace::ADOBERGB_LINEAR_EXT; break;
    case VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT: colorSpace = gfxSurfaceColorSpace::ADOBERGB_NONLINEAR_EXT; break;
    case VK_COLOR_SPACE_PASS_THROUGH_EXT: colorSpace = gfxSurfaceColorSpace::PASS_THROUGH_EXT; break;
    case VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT: colorSpace = gfxSurfaceColorSpace::EXTENDED_SRGB_NONLINEAR_EXT; break;
    case VK_COLOR_SPACE_DISPLAY_NATIVE_AMD: colorSpace = gfxSurfaceColorSpace::DISPLAY_NATIVE_AMD; break;
    }

    return colorSpace;
}

gfxSurfaceTransformMask gfxSurfaceTransformMaskFrom(VkSurfaceTransformFlagsKHR mask)
{
    return epiMask((mask & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) ? gfxSurfaceTransformMask_Identity : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR) ? gfxSurfaceTransformMask_Rotate90 : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR) ? gfxSurfaceTransformMask_Rotate180 : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR) ? gfxSurfaceTransformMask_Rotate270 : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR) ? gfxSurfaceTransformMask_HorizontalMirror : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR) ? gfxSurfaceTransformMask_HorizontalMirrorRotate90 : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR) ? gfxSurfaceTransformMask_HorizontalMirrorRotate180 : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR) ? gfxSurfaceTransformMask_HorizontalMirrorRotate270 : gfxSurfaceTransformMask{0},
                   (mask & VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR) ? gfxSurfaceTransformMask_Inherit : gfxSurfaceTransformMask{0});
}

gfxCompositeAlphaMask gfxCompositeAlphaMaskFrom(VkCompositeAlphaFlagsKHR mask)
{
    return epiMask((mask & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR) ? gfxCompositeAlphaMask_Opaque : gfxCompositeAlphaMask{0},
                   (mask & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR) ? gfxCompositeAlphaMask_PreMultiplied : gfxCompositeAlphaMask{0},
                   (mask & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR) ? gfxCompositeAlphaMask_PostMultiplied : gfxCompositeAlphaMask{0},
                   (mask & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR) ? gfxCompositeAlphaMask_Inherit : gfxCompositeAlphaMask{0});
}

gfxImageUsageMask gfxImageUsageMaskFrom(VkImageUsageFlags mask)
{
    return epiMask((mask & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) ? gfxImageUsageMask_TransferSrc : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_TRANSFER_DST_BIT) ? gfxImageUsageMask_TransferDst : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_SAMPLED_BIT) ? gfxImageUsageMask_Sampled : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_STORAGE_BIT) ? gfxImageUsageMask_Storage : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) ? gfxImageUsageMask_ColorAttachment : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) ? gfxImageUsageMask_DepthStencilAttachment : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT) ? gfxImageUsageMask_TransientAttachment : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT) ? gfxImageUsageMask_InputAttachment : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV) ? gfxImageUsageMask_ShadingRateImage : gfxImageUsageMask{0},
                   (mask & VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT) ? gfxImageUsageMask_FragmentDensityMap : gfxImageUsageMask{0});
}

gfxFormatFeatureMask gfxFormatFeatureMaskFrom(VkFormatFeatureFlags mask)
{
    return epiMask((mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) ? gfxFormatFeatureMask_SampledImage : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT) ? gfxFormatFeatureMask_StorageImage : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT) ? gfxFormatFeatureMask_StorageImageAtomic : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT) ? gfxFormatFeatureMask_UniformTexelBuffer : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT) ? gfxFormatFeatureMask_StorageTexelBuffer : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT) ? gfxFormatFeatureMask_StorageTexelBufferAtomic : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT) ? gfxFormatFeatureMask_VertexBuffer : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT) ? gfxFormatFeatureMask_ColorAttachment : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT) ? gfxFormatFeatureMask_ColorAttachmentBlend : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) ? gfxFormatFeatureMask_DepthStencilAttachment : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_BLIT_SRC_BIT) ? gfxFormatFeatureMask_BlitSrc : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_BLIT_DST_BIT) ? gfxFormatFeatureMask_BlitDst : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT) ? gfxFormatFeatureMask_SampledImageFilterLinear : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_TRANSFER_SRC_BIT) ? gfxFormatFeatureMask_TransferSrc : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_TRANSFER_DST_BIT) ? gfxFormatFeatureMask_TransferDst : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT) ? gfxFormatFeatureMask_MidpointChromaSamples : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT) ? gfxFormatFeatureMask_SampledImageYCbCrConversionLinearFilter : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT) ? gfxFormatFeatureMask_SampledImageYCbCrConversionSeparateReconstructionFilter : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT) ? gfxFormatFeatureMask_SampledImageYCbCrConversionChromaReconstructionExplicit : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT) ? gfxFormatFeatureMask_SampledImageYCbCrConversionChromaReconstructionExplicitForceable : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_DISJOINT_BIT) ? gfxFormatFeatureMask_Disjoint : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT) ? gfxFormatFeatureMask_CositedChromaSamples : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT) ? gfxFormatFeatureMask_SampledImageFilterMinmax : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT) ? gfxFormatFeatureMask_SampledImageFilterCubic : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_ACCELERATION_STRUCTURE_VERTEX_BUFFER_BIT_KHR) ? gfxFormatFeatureMask_AccelerationStructureVertexBuffer : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_FRAGMENT_DENSITY_MAP_BIT_EXT) ? gfxFormatFeatureMask_FragmentDensityMap : gfxFormatFeatureMask{0},
                   (mask & VK_FORMAT_FEATURE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR) ? gfxFormatFeatureMask_FragmentShadingRateAttachment : gfxFormatFeatureMask{0});
}

VkFormat gfxFormatTo(gfxFormat format)
{
    switch (format)
    {
    case gfxFormat::UNDEFINED: return VK_FORMAT_UNDEFINED; break;
    case gfxFormat::R4G4_UNORM_PACK8: return VK_FORMAT_R4G4_UNORM_PACK8; break;
    case gfxFormat::R4G4B4A4_UNORM_PACK16: return VK_FORMAT_R4G4B4A4_UNORM_PACK16; break;
    case gfxFormat::B4G4R4A4_UNORM_PACK16: return VK_FORMAT_B4G4R4A4_UNORM_PACK16; break;
    case gfxFormat::R5G6B5_UNORM_PACK16: return VK_FORMAT_R5G6B5_UNORM_PACK16; break;
    case gfxFormat::B5G6R5_UNORM_PACK16: return VK_FORMAT_B5G6R5_UNORM_PACK16; break;
    case gfxFormat::R5G5B5A1_UNORM_PACK16: return VK_FORMAT_R5G5B5A1_UNORM_PACK16; break;
    case gfxFormat::B5G5R5A1_UNORM_PACK16: return VK_FORMAT_B5G5R5A1_UNORM_PACK16; break;
    case gfxFormat::A1R5G5B5_UNORM_PACK16: return VK_FORMAT_A1R5G5B5_UNORM_PACK16; break;
    case gfxFormat::R8_UNORM: return VK_FORMAT_R8_UNORM; break;
    case gfxFormat::R8_SNORM: return VK_FORMAT_R8_SNORM; break;
    case gfxFormat::R8_USCALED: return VK_FORMAT_R8_USCALED; break;
    case gfxFormat::R8_SSCALED: return VK_FORMAT_R8_SSCALED; break;
    case gfxFormat::R8_UINT: return VK_FORMAT_R8_UINT; break;
    case gfxFormat::R8_SINT: return VK_FORMAT_R8_SINT; break;
    case gfxFormat::R8_SRGB: return VK_FORMAT_R8_SRGB; break;
    case gfxFormat::R8G8_UNORM: return VK_FORMAT_R8G8_UNORM; break;
    case gfxFormat::R8G8_SNORM: return VK_FORMAT_R8G8_SNORM; break;
    case gfxFormat::R8G8_USCALED: return VK_FORMAT_R8G8_USCALED; break;
    case gfxFormat::R8G8_SSCALED: return VK_FORMAT_R8G8_SSCALED; break;
    case gfxFormat::R8G8_UINT: return VK_FORMAT_R8G8_UINT; break;
    case gfxFormat::R8G8_SINT: return VK_FORMAT_R8G8_SINT; break;
    case gfxFormat::R8G8_SRGB: return VK_FORMAT_R8G8_SRGB; break;
    case gfxFormat::R8G8B8_UNORM: return VK_FORMAT_R8G8B8_UNORM; break;
    case gfxFormat::R8G8B8_SNORM: return VK_FORMAT_R8G8B8_SNORM; break;
    case gfxFormat::R8G8B8_USCALED: return VK_FORMAT_R8G8B8_USCALED; break;
    case gfxFormat::R8G8B8_SSCALED: return VK_FORMAT_R8G8B8_SSCALED; break;
    case gfxFormat::R8G8B8_UINT: return VK_FORMAT_R8G8B8_UINT; break;
    case gfxFormat::R8G8B8_SINT: return VK_FORMAT_R8G8B8_SINT; break;
    case gfxFormat::R8G8B8_SRGB: return VK_FORMAT_R8G8B8_SRGB; break;
    case gfxFormat::B8G8R8_UNORM: return VK_FORMAT_B8G8R8_UNORM; break;
    case gfxFormat::B8G8R8_SNORM: return VK_FORMAT_B8G8R8_SNORM; break;
    case gfxFormat::B8G8R8_USCALED: return VK_FORMAT_B8G8R8_USCALED; break;
    case gfxFormat::B8G8R8_SSCALED: return VK_FORMAT_B8G8R8_SSCALED; break;
    case gfxFormat::B8G8R8_UINT: return VK_FORMAT_B8G8R8_UINT; break;
    case gfxFormat::B8G8R8_SINT: return VK_FORMAT_B8G8R8_SINT; break;
    case gfxFormat::B8G8R8_SRGB: return VK_FORMAT_B8G8R8_SRGB; break;
    case gfxFormat::R8G8B8A8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM; break;
    case gfxFormat::R8G8B8A8_SNORM: return VK_FORMAT_R8G8B8A8_SNORM; break;
    case gfxFormat::R8G8B8A8_USCALED: return VK_FORMAT_R8G8B8A8_USCALED; break;
    case gfxFormat::R8G8B8A8_SSCALED: return VK_FORMAT_R8G8B8A8_SSCALED; break;
    case gfxFormat::R8G8B8A8_UINT: return VK_FORMAT_R8G8B8A8_UINT; break;
    case gfxFormat::R8G8B8A8_SINT: return VK_FORMAT_R8G8B8A8_SINT; break;
    case gfxFormat::R8G8B8A8_SRGB: return VK_FORMAT_R8G8B8A8_SRGB; break;
    case gfxFormat::B8G8R8A8_UNORM: return VK_FORMAT_B8G8R8A8_UNORM; break;
    case gfxFormat::B8G8R8A8_SNORM: return VK_FORMAT_B8G8R8A8_SNORM; break;
    case gfxFormat::B8G8R8A8_USCALED: return VK_FORMAT_B8G8R8A8_USCALED; break;
    case gfxFormat::B8G8R8A8_SSCALED: return VK_FORMAT_B8G8R8A8_SSCALED; break;
    case gfxFormat::B8G8R8A8_UINT: return VK_FORMAT_B8G8R8A8_UINT; break;
    case gfxFormat::B8G8R8A8_SINT: return VK_FORMAT_B8G8R8A8_SINT; break;
    case gfxFormat::B8G8R8A8_SRGB: return VK_FORMAT_B8G8R8A8_SRGB; break;
    case gfxFormat::A8B8G8R8_UNORM_PACK32: return VK_FORMAT_A8B8G8R8_UNORM_PACK32; break;
    case gfxFormat::A8B8G8R8_SNORM_PACK32: return VK_FORMAT_A8B8G8R8_SNORM_PACK32; break;
    case gfxFormat::A8B8G8R8_USCALED_PACK32: return VK_FORMAT_A8B8G8R8_USCALED_PACK32; break;
    case gfxFormat::A8B8G8R8_SSCALED_PACK32: return VK_FORMAT_A8B8G8R8_SSCALED_PACK32; break;
    case gfxFormat::A8B8G8R8_UINT_PACK32: return VK_FORMAT_A8B8G8R8_UINT_PACK32; break;
    case gfxFormat::A8B8G8R8_SINT_PACK32: return VK_FORMAT_A8B8G8R8_SINT_PACK32; break;
    case gfxFormat::A8B8G8R8_SRGB_PACK32: return VK_FORMAT_A8B8G8R8_SRGB_PACK32; break;
    case gfxFormat::A2R10G10B10_UNORM_PACK32: return VK_FORMAT_A2R10G10B10_UNORM_PACK32; break;
    case gfxFormat::A2R10G10B10_SNORM_PACK32: return VK_FORMAT_A2R10G10B10_SNORM_PACK32; break;
    case gfxFormat::A2R10G10B10_USCALED_PACK32: return VK_FORMAT_A2R10G10B10_USCALED_PACK32; break;
    case gfxFormat::A2R10G10B10_SSCALED_PACK32: return VK_FORMAT_A2R10G10B10_SSCALED_PACK32; break;
    case gfxFormat::A2R10G10B10_UINT_PACK32: return VK_FORMAT_A2R10G10B10_UINT_PACK32; break;
    case gfxFormat::A2R10G10B10_SINT_PACK32: return VK_FORMAT_A2R10G10B10_SINT_PACK32; break;
    case gfxFormat::A2B10G10R10_UNORM_PACK32: return VK_FORMAT_A2B10G10R10_UNORM_PACK32; break;
    case gfxFormat::A2B10G10R10_SNORM_PACK32: return VK_FORMAT_A2B10G10R10_SNORM_PACK32; break;
    case gfxFormat::A2B10G10R10_USCALED_PACK32: return VK_FORMAT_A2B10G10R10_USCALED_PACK32; break;
    case gfxFormat::A2B10G10R10_SSCALED_PACK32: return VK_FORMAT_A2B10G10R10_SSCALED_PACK32; break;
    case gfxFormat::A2B10G10R10_UINT_PACK32: return VK_FORMAT_A2B10G10R10_UINT_PACK32; break;
    case gfxFormat::A2B10G10R10_SINT_PACK32: return VK_FORMAT_A2B10G10R10_SINT_PACK32; break;
    case gfxFormat::R16_UNORM: return VK_FORMAT_R16_UNORM; break;
    case gfxFormat::R16_SNORM: return VK_FORMAT_R16_SNORM; break;
    case gfxFormat::R16_USCALED: return VK_FORMAT_R16_USCALED; break;
    case gfxFormat::R16_SSCALED: return VK_FORMAT_R16_SSCALED; break;
    case gfxFormat::R16_UINT: return VK_FORMAT_R16_UINT; break;
    case gfxFormat::R16_SINT: return VK_FORMAT_R16_SINT; break;
    case gfxFormat::R16_SFLOAT: return VK_FORMAT_R16_SFLOAT; break;
    case gfxFormat::R16G16_UNORM: return VK_FORMAT_R16G16_UNORM; break;
    case gfxFormat::R16G16_SNORM: return VK_FORMAT_R16G16_SNORM; break;
    case gfxFormat::R16G16_USCALED: return VK_FORMAT_R16G16_USCALED; break;
    case gfxFormat::R16G16_SSCALED: return VK_FORMAT_R16G16_SSCALED; break;
    case gfxFormat::R16G16_UINT: return VK_FORMAT_R16G16_UINT; break;
    case gfxFormat::R16G16_SINT: return VK_FORMAT_R16G16_SINT; break;
    case gfxFormat::R16G16_SFLOAT: return VK_FORMAT_R16G16_SFLOAT; break;
    case gfxFormat::R16G16B16_UNORM: return VK_FORMAT_R16G16B16_UNORM; break;
    case gfxFormat::R16G16B16_SNORM: return VK_FORMAT_R16G16B16_SNORM; break;
    case gfxFormat::R16G16B16_USCALED: return VK_FORMAT_R16G16B16_USCALED; break;
    case gfxFormat::R16G16B16_SSCALED: return VK_FORMAT_R16G16B16_SSCALED; break;
    case gfxFormat::R16G16B16_UINT: return VK_FORMAT_R16G16B16_UINT; break;
    case gfxFormat::R16G16B16_SINT: return VK_FORMAT_R16G16B16_SINT; break;
    case gfxFormat::R16G16B16_SFLOAT: return VK_FORMAT_R16G16B16_SFLOAT; break;
    case gfxFormat::R16G16B16A16_UNORM: return VK_FORMAT_R16G16B16A16_UNORM; break;
    case gfxFormat::R16G16B16A16_SNORM: return VK_FORMAT_R16G16B16A16_SNORM; break;
    case gfxFormat::R16G16B16A16_USCALED: return VK_FORMAT_R16G16B16A16_USCALED; break;
    case gfxFormat::R16G16B16A16_SSCALED: return VK_FORMAT_R16G16B16A16_SSCALED; break;
    case gfxFormat::R16G16B16A16_UINT: return VK_FORMAT_R16G16B16A16_UINT; break;
    case gfxFormat::R16G16B16A16_SINT: return VK_FORMAT_R16G16B16A16_SINT; break;
    case gfxFormat::R16G16B16A16_SFLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT; break;
    case gfxFormat::R32_UINT: return VK_FORMAT_R32_UINT; break;
    case gfxFormat::R32_SINT: return VK_FORMAT_R32_SINT; break;
    case gfxFormat::R32_SFLOAT: return VK_FORMAT_R32_SFLOAT; break;
    case gfxFormat::R32G32_UINT: return VK_FORMAT_R32G32_UINT; break;
    case gfxFormat::R32G32_SINT: return VK_FORMAT_R32G32_SINT; break;
    case gfxFormat::R32G32_SFLOAT: return VK_FORMAT_R32G32_SFLOAT; break;
    case gfxFormat::R32G32B32_UINT: return VK_FORMAT_R32G32B32_UINT; break;
    case gfxFormat::R32G32B32_SINT: return VK_FORMAT_R32G32B32_SINT; break;
    case gfxFormat::R32G32B32_SFLOAT: return VK_FORMAT_R32G32B32_SFLOAT; break;
    case gfxFormat::R32G32B32A32_UINT: return VK_FORMAT_R32G32B32A32_UINT; break;
    case gfxFormat::R32G32B32A32_SINT: return VK_FORMAT_R32G32B32A32_SINT; break;
    case gfxFormat::R32G32B32A32_SFLOAT: return VK_FORMAT_R32G32B32A32_SFLOAT; break;
    case gfxFormat::R64_UINT: return VK_FORMAT_R64_UINT; break;
    case gfxFormat::R64_SINT: return VK_FORMAT_R64_SINT; break;
    case gfxFormat::R64_SFLOAT: return VK_FORMAT_R64_SFLOAT; break;
    case gfxFormat::R64G64_UINT: return VK_FORMAT_R64G64_UINT; break;
    case gfxFormat::R64G64_SINT: return VK_FORMAT_R64G64_SINT; break;
    case gfxFormat::R64G64_SFLOAT: return VK_FORMAT_R64G64_SFLOAT; break;
    case gfxFormat::R64G64B64_UINT: return VK_FORMAT_R64G64B64_UINT; break;
    case gfxFormat::R64G64B64_SINT: return VK_FORMAT_R64G64B64_SINT; break;
    case gfxFormat::R64G64B64_SFLOAT: return VK_FORMAT_R64G64B64_SFLOAT; break;
    case gfxFormat::R64G64B64A64_UINT: return VK_FORMAT_R64G64B64A64_UINT; break;
    case gfxFormat::R64G64B64A64_SINT: return VK_FORMAT_R64G64B64A64_SINT; break;
    case gfxFormat::R64G64B64A64_SFLOAT: return VK_FORMAT_R64G64B64A64_SFLOAT; break;
    case gfxFormat::B10G11R11_UFLOAT_PACK32: return VK_FORMAT_B10G11R11_UFLOAT_PACK32; break;
    case gfxFormat::E5B9G9R9_UFLOAT_PACK32: return VK_FORMAT_E5B9G9R9_UFLOAT_PACK32; break;
    case gfxFormat::D16_UNORM: return VK_FORMAT_D16_UNORM; break;
    case gfxFormat::X8_D24_UNORM_PACK32: return VK_FORMAT_X8_D24_UNORM_PACK32; break;
    case gfxFormat::D32_SFLOAT: return VK_FORMAT_D32_SFLOAT; break;
    case gfxFormat::S8_UINT: return VK_FORMAT_S8_UINT; break;
    case gfxFormat::D16_UNORM_S8_UINT: return VK_FORMAT_D16_UNORM_S8_UINT; break;
    case gfxFormat::D24_UNORM_S8_UINT: return VK_FORMAT_D24_UNORM_S8_UINT; break;
    case gfxFormat::D32_SFLOAT_S8_UINT: return VK_FORMAT_D32_SFLOAT_S8_UINT; break;
    case gfxFormat::BC1_RGB_UNORM_BLOCK: return VK_FORMAT_BC1_RGB_UNORM_BLOCK; break;
    case gfxFormat::BC1_RGB_SRGB_BLOCK: return VK_FORMAT_BC1_RGB_SRGB_BLOCK; break;
    case gfxFormat::BC1_RGBA_UNORM_BLOCK: return VK_FORMAT_BC1_RGBA_UNORM_BLOCK; break;
    case gfxFormat::BC1_RGBA_SRGB_BLOCK: return VK_FORMAT_BC1_RGBA_SRGB_BLOCK; break;
    case gfxFormat::BC2_UNORM_BLOCK: return VK_FORMAT_BC2_UNORM_BLOCK; break;
    case gfxFormat::BC2_SRGB_BLOCK: return VK_FORMAT_BC2_SRGB_BLOCK; break;
    case gfxFormat::BC3_UNORM_BLOCK: return VK_FORMAT_BC3_UNORM_BLOCK; break;
    case gfxFormat::BC3_SRGB_BLOCK: return VK_FORMAT_BC3_SRGB_BLOCK; break;
    case gfxFormat::BC4_UNORM_BLOCK: return VK_FORMAT_BC4_UNORM_BLOCK; break;
    case gfxFormat::BC4_SNORM_BLOCK: return VK_FORMAT_BC4_SNORM_BLOCK; break;
    case gfxFormat::BC5_UNORM_BLOCK: return VK_FORMAT_BC5_UNORM_BLOCK; break;
    case gfxFormat::BC5_SNORM_BLOCK: return VK_FORMAT_BC5_SNORM_BLOCK; break;
    case gfxFormat::BC6H_UFLOAT_BLOCK: return VK_FORMAT_BC6H_UFLOAT_BLOCK; break;
    case gfxFormat::BC6H_SFLOAT_BLOCK: return VK_FORMAT_BC6H_SFLOAT_BLOCK; break;
    case gfxFormat::BC7_UNORM_BLOCK: return VK_FORMAT_BC7_UNORM_BLOCK; break;
    case gfxFormat::BC7_SRGB_BLOCK: return VK_FORMAT_BC7_SRGB_BLOCK; break;
    case gfxFormat::ETC2_R8G8B8_UNORM_BLOCK: return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK; break;
    case gfxFormat::ETC2_R8G8B8_SRGB_BLOCK: return VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK; break;
    case gfxFormat::ETC2_R8G8B8A1_UNORM_BLOCK: return VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK; break;
    case gfxFormat::ETC2_R8G8B8A1_SRGB_BLOCK: return VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK; break;
    case gfxFormat::ETC2_R8G8B8A8_UNORM_BLOCK: return VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK; break;
    case gfxFormat::ETC2_R8G8B8A8_SRGB_BLOCK: return VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK; break;
    case gfxFormat::EAC_R11_UNORM_BLOCK: return VK_FORMAT_EAC_R11_UNORM_BLOCK; break;
    case gfxFormat::EAC_R11_SNORM_BLOCK: return VK_FORMAT_EAC_R11_SNORM_BLOCK; break;
    case gfxFormat::EAC_R11G11_UNORM_BLOCK: return VK_FORMAT_EAC_R11G11_UNORM_BLOCK; break;
    case gfxFormat::EAC_R11G11_SNORM_BLOCK: return VK_FORMAT_EAC_R11G11_SNORM_BLOCK; break;
    case gfxFormat::ASTC_4x4_UNORM_BLOCK: return VK_FORMAT_ASTC_4x4_UNORM_BLOCK; break;
    case gfxFormat::ASTC_4x4_SRGB_BLOCK: return VK_FORMAT_ASTC_4x4_SRGB_BLOCK; break;
    case gfxFormat::ASTC_5x4_UNORM_BLOCK: return VK_FORMAT_ASTC_5x4_UNORM_BLOCK; break;
    case gfxFormat::ASTC_5x4_SRGB_BLOCK: return VK_FORMAT_ASTC_5x4_SRGB_BLOCK; break;
    case gfxFormat::ASTC_5x5_UNORM_BLOCK: return VK_FORMAT_ASTC_5x5_UNORM_BLOCK; break;
    case gfxFormat::ASTC_5x5_SRGB_BLOCK: return VK_FORMAT_ASTC_5x5_SRGB_BLOCK; break;
    case gfxFormat::ASTC_6x5_UNORM_BLOCK: return VK_FORMAT_ASTC_6x5_UNORM_BLOCK; break;
    case gfxFormat::ASTC_6x5_SRGB_BLOCK: return VK_FORMAT_ASTC_6x5_SRGB_BLOCK; break;
    case gfxFormat::ASTC_6x6_UNORM_BLOCK: return VK_FORMAT_ASTC_6x6_UNORM_BLOCK; break;
    case gfxFormat::ASTC_6x6_SRGB_BLOCK: return VK_FORMAT_ASTC_6x6_SRGB_BLOCK; break;
    case gfxFormat::ASTC_8x5_UNORM_BLOCK: return VK_FORMAT_ASTC_8x5_UNORM_BLOCK; break;
    case gfxFormat::ASTC_8x5_SRGB_BLOCK: return VK_FORMAT_ASTC_8x5_SRGB_BLOCK; break;
    case gfxFormat::ASTC_8x6_UNORM_BLOCK: return VK_FORMAT_ASTC_8x6_UNORM_BLOCK; break;
    case gfxFormat::ASTC_8x6_SRGB_BLOCK: return VK_FORMAT_ASTC_8x6_SRGB_BLOCK; break;
    case gfxFormat::ASTC_8x8_UNORM_BLOCK: return VK_FORMAT_ASTC_8x8_UNORM_BLOCK; break;
    case gfxFormat::ASTC_8x8_SRGB_BLOCK: return VK_FORMAT_ASTC_8x8_SRGB_BLOCK; break;
    case gfxFormat::ASTC_10x5_UNORM_BLOCK: return VK_FORMAT_ASTC_10x5_UNORM_BLOCK; break;
    case gfxFormat::ASTC_10x5_SRGB_BLOCK: return VK_FORMAT_ASTC_10x5_SRGB_BLOCK; break;
    case gfxFormat::ASTC_10x6_UNORM_BLOCK: return VK_FORMAT_ASTC_10x6_UNORM_BLOCK; break;
    case gfxFormat::ASTC_10x6_SRGB_BLOCK: return VK_FORMAT_ASTC_10x6_SRGB_BLOCK; break;
    case gfxFormat::ASTC_10x8_UNORM_BLOCK: return VK_FORMAT_ASTC_10x8_UNORM_BLOCK; break;
    case gfxFormat::ASTC_10x8_SRGB_BLOCK: return VK_FORMAT_ASTC_10x8_SRGB_BLOCK; break;
    case gfxFormat::ASTC_10x10_UNORM_BLOCK: return VK_FORMAT_ASTC_10x10_UNORM_BLOCK; break;
    case gfxFormat::ASTC_10x10_SRGB_BLOCK: return VK_FORMAT_ASTC_10x10_SRGB_BLOCK; break;
    case gfxFormat::ASTC_12x10_UNORM_BLOCK: return VK_FORMAT_ASTC_12x10_UNORM_BLOCK; break;
    case gfxFormat::ASTC_12x10_SRGB_BLOCK: return VK_FORMAT_ASTC_12x10_SRGB_BLOCK; break;
    case gfxFormat::ASTC_12x12_UNORM_BLOCK: return VK_FORMAT_ASTC_12x12_UNORM_BLOCK; break;
    case gfxFormat::ASTC_12x12_SRGB_BLOCK: return VK_FORMAT_ASTC_12x12_SRGB_BLOCK; break;
    case gfxFormat::G8B8G8R8_422_UNORM: return VK_FORMAT_G8B8G8R8_422_UNORM; break;
    case gfxFormat::B8G8R8G8_422_UNORM: return VK_FORMAT_B8G8R8G8_422_UNORM; break;
    case gfxFormat::G8_B8_R8_3PLANE_420_UNORM: return VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM; break;
    case gfxFormat::G8_B8R8_2PLANE_420_UNORM: return VK_FORMAT_G8_B8R8_2PLANE_420_UNORM; break;
    case gfxFormat::G8_B8_R8_3PLANE_422_UNORM: return VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM; break;
    case gfxFormat::G8_B8R8_2PLANE_422_UNORM: return VK_FORMAT_G8_B8R8_2PLANE_422_UNORM; break;
    case gfxFormat::G8_B8_R8_3PLANE_444_UNORM: return VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM; break;
    case gfxFormat::R10X6_UNORM_PACK16: return VK_FORMAT_R10X6_UNORM_PACK16; break;
    case gfxFormat::R10X6G10X6_UNORM_2PACK16: return VK_FORMAT_R10X6G10X6_UNORM_2PACK16; break;
    case gfxFormat::R10X6G10X6B10X6A10X6_UNORM_4PACK16: return VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16; break;
    case gfxFormat::G10X6B10X6G10X6R10X6_422_UNORM_4PACK16: return VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16; break;
    case gfxFormat::B10X6G10X6R10X6G10X6_422_UNORM_4PACK16: return VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16; break;
    case gfxFormat::G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16; break;
    case gfxFormat::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16: return VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16; break;
    case gfxFormat::G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16; break;
    case gfxFormat::G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16: return VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16; break;
    case gfxFormat::G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16; break;
    case gfxFormat::R12X4_UNORM_PACK16: return VK_FORMAT_R12X4_UNORM_PACK16; break;
    case gfxFormat::R12X4G12X4_UNORM_2PACK16: return VK_FORMAT_R12X4G12X4_UNORM_2PACK16; break;
    case gfxFormat::R12X4G12X4B12X4A12X4_UNORM_4PACK16: return VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16; break;
    case gfxFormat::G12X4B12X4G12X4R12X4_422_UNORM_4PACK16: return VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16; break;
    case gfxFormat::B12X4G12X4R12X4G12X4_422_UNORM_4PACK16: return VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16; break;
    case gfxFormat::G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16: return VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16; break;
    case gfxFormat::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16: return VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16; break;
    case gfxFormat::G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16: return VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16; break;
    case gfxFormat::G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16: return VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16; break;
    case gfxFormat::G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16: return VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16; break;
    case gfxFormat::G16B16G16R16_422_UNORM: return VK_FORMAT_G16B16G16R16_422_UNORM; break;
    case gfxFormat::B16G16R16G16_422_UNORM: return VK_FORMAT_B16G16R16G16_422_UNORM; break;
    case gfxFormat::G16_B16_R16_3PLANE_420_UNORM: return VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM; break;
    case gfxFormat::G16_B16R16_2PLANE_420_UNORM: return VK_FORMAT_G16_B16R16_2PLANE_420_UNORM; break;
    case gfxFormat::G16_B16_R16_3PLANE_422_UNORM: return VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM; break;
    case gfxFormat::G16_B16R16_2PLANE_422_UNORM: return VK_FORMAT_G16_B16R16_2PLANE_422_UNORM; break;
    case gfxFormat::G16_B16_R16_3PLANE_444_UNORM: return VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM; break;
    case gfxFormat::PVRTC1_2BPP_UNORM_BLOCK_IMG: return VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG; break;
    case gfxFormat::PVRTC1_4BPP_UNORM_BLOCK_IMG: return VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG; break;
    case gfxFormat::PVRTC2_2BPP_UNORM_BLOCK_IMG: return VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG; break;
    case gfxFormat::PVRTC2_4BPP_UNORM_BLOCK_IMG: return VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG; break;
    case gfxFormat::PVRTC1_2BPP_SRGB_BLOCK_IMG: return VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG; break;
    case gfxFormat::PVRTC1_4BPP_SRGB_BLOCK_IMG: return VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG; break;
    case gfxFormat::PVRTC2_2BPP_SRGB_BLOCK_IMG: return VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG; break;
    case gfxFormat::PVRTC2_4BPP_SRGB_BLOCK_IMG: return VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG; break;
    case gfxFormat::ASTC_4x4_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_5x4_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_5x5_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_6x5_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_6x6_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_8x5_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_8x6_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_8x8_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_10x5_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_10x6_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_10x8_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_10x10_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_12x10_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::ASTC_12x12_SFLOAT_BLOCK_EXT: return VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT; break;
    case gfxFormat::A4R4G4B4_UNORM_PACK16_EXT: return VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT; break;
    case gfxFormat::A4B4G4R4_UNORM_PACK16_EXT: return VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT; break;
    }
}

VkColorSpaceKHR gfxSurfaceColorSpaceTo(gfxSurfaceColorSpace colorSpace)
{
    switch (colorSpace)
    {
    case gfxSurfaceColorSpace::SRGB_NONLINEAR: return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; break;
    case gfxSurfaceColorSpace::DISPLAY_P3_NONLINEAR_EXT: return VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT; break;
    case gfxSurfaceColorSpace::EXTENDED_SRGB_LINEAR_EXT: return VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT; break;
    case gfxSurfaceColorSpace::DISPLAY_P3_LINEAR_EXT: return VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT; break;
    case gfxSurfaceColorSpace::DCI_P3_NONLINEAR_EXT: return VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT; break;
    case gfxSurfaceColorSpace::BT709_LINEAR_EXT: return VK_COLOR_SPACE_BT709_LINEAR_EXT; break;
    case gfxSurfaceColorSpace::BT709_NONLINEAR_EXT: return VK_COLOR_SPACE_BT709_NONLINEAR_EXT; break;
    case gfxSurfaceColorSpace::BT2020_LINEAR_EXT: return VK_COLOR_SPACE_BT2020_LINEAR_EXT; break;
    case gfxSurfaceColorSpace::HDR10_ST2084_EXT: return VK_COLOR_SPACE_HDR10_ST2084_EXT; break;
    case gfxSurfaceColorSpace::DOLBYVISION_EXT: return VK_COLOR_SPACE_DOLBYVISION_EXT; break;
    case gfxSurfaceColorSpace::HDR10_HLG_EXT: return VK_COLOR_SPACE_HDR10_HLG_EXT; break;
    case gfxSurfaceColorSpace::ADOBERGB_LINEAR_EXT: return VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT; break;
    case gfxSurfaceColorSpace::ADOBERGB_NONLINEAR_EXT: return VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT; break;
    case gfxSurfaceColorSpace::PASS_THROUGH_EXT: return VK_COLOR_SPACE_PASS_THROUGH_EXT; break;
    case gfxSurfaceColorSpace::EXTENDED_SRGB_NONLINEAR_EXT: return VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT; break;
    case gfxSurfaceColorSpace::DISPLAY_NATIVE_AMD: return VK_COLOR_SPACE_DISPLAY_NATIVE_AMD; break;
    }
}

VkSurfaceTransformFlagBitsKHR gfxSurfaceTransformMaskTo(gfxSurfaceTransformMask mask)
{
    return epiMask((mask & gfxSurfaceTransformMask_Identity) ? VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_Rotate90) ? VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_Rotate180) ? VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_Rotate270) ? VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_HorizontalMirror) ? VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_HorizontalMirrorRotate90) ? VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_HorizontalMirrorRotate180) ? VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_HorizontalMirrorRotate270) ? VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR : VkSurfaceTransformFlagBitsKHR{},
                   (mask & gfxSurfaceTransformMask_Inherit) ? VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR : VkSurfaceTransformFlagBitsKHR{});
}

VkCompositeAlphaFlagBitsKHR gfxCompositeAlphaMaskTo(gfxCompositeAlphaMask mask)
{
    return epiMask((mask & gfxCompositeAlphaMask_Opaque) ? VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR : VkCompositeAlphaFlagBitsKHR{},
                   (mask & gfxCompositeAlphaMask_PreMultiplied) ? VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR : VkCompositeAlphaFlagBitsKHR{},
                   (mask & gfxCompositeAlphaMask_PostMultiplied) ? VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR : VkCompositeAlphaFlagBitsKHR{},
                   (mask & gfxCompositeAlphaMask_Inherit) ? VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR : VkCompositeAlphaFlagBitsKHR{});
}

VkPresentModeKHR gfxSurfacePresentModeTo(gfxSurfacePresentMode presentMode)
{
    switch (presentMode)
    {
    case gfxSurfacePresentMode::IMMEDIATE: return VK_PRESENT_MODE_IMMEDIATE_KHR;
    case gfxSurfacePresentMode::MAILBOX: return VK_PRESENT_MODE_MAILBOX_KHR;
    case gfxSurfacePresentMode::FIFO: return VK_PRESENT_MODE_FIFO_KHR;
    case gfxSurfacePresentMode::FIFO_RELAXED: return VK_PRESENT_MODE_FIFO_RELAXED_KHR;
    case gfxSurfacePresentMode::SHARED_DEMAND_REFRESH: return VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR;
    case gfxSurfacePresentMode::SHARED_CONTINUOUS_REFRESH: return VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR;
    }
}

VkPrimitiveTopology gfxPipelineInputAssemblyTypeTo(gfxPipelineInputAssemblyType type)
{
    switch (type)
    {
    case gfxPipelineInputAssemblyType::PointList: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case gfxPipelineInputAssemblyType::LineList: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case gfxPipelineInputAssemblyType::LineStrip: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case gfxPipelineInputAssemblyType::TriangleList: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case gfxPipelineInputAssemblyType::TriangleStrip: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    default: epiLogError("Unrecognized enum value = {}!", type); return VK_PRIMITIVE_TOPOLOGY_POINT_LIST; // TODO: use str repr of enum
    }
}

VkSampleCountFlagBits gfxSampleCountMaskTo(gfxSampleCountMask mask)
{
    return epiMask((mask & gfxSampleCountMask_Sample1) ? VK_SAMPLE_COUNT_1_BIT : VkSampleCountFlagBits{},
                   (mask & gfxSampleCountMask_Sample2) ? VK_SAMPLE_COUNT_2_BIT : VkSampleCountFlagBits{},
                   (mask & gfxSampleCountMask_Sample4) ? VK_SAMPLE_COUNT_4_BIT : VkSampleCountFlagBits{},
                   (mask & gfxSampleCountMask_Sample8) ? VK_SAMPLE_COUNT_8_BIT : VkSampleCountFlagBits{},
                   (mask & gfxSampleCountMask_Sample16) ? VK_SAMPLE_COUNT_16_BIT : VkSampleCountFlagBits{},
                   (mask & gfxSampleCountMask_Sample32) ? VK_SAMPLE_COUNT_32_BIT : VkSampleCountFlagBits{},
                   (mask & gfxSampleCountMask_Sample64) ? VK_SAMPLE_COUNT_64_BIT : VkSampleCountFlagBits{});
}

VkAttachmentLoadOp gfxAttachmentLoadOpTo(gfxAttachmentLoadOp loadOp)
{
    switch (loadOp)
    {
    case gfxAttachmentLoadOp::Load: return VK_ATTACHMENT_LOAD_OP_LOAD;
    case gfxAttachmentLoadOp::Clear: return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case gfxAttachmentLoadOp::DontCare: return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    default: epiLogError("Unhandled gfxAttachmentLoadOp=`{}`", loadOp); return VK_ATTACHMENT_LOAD_OP_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkAttachmentStoreOp gfxAttachmentStoreOpTo(gfxAttachmentStoreOp storeOp)
{
    switch (storeOp)
    {
    case gfxAttachmentStoreOp::Store: return VK_ATTACHMENT_STORE_OP_STORE;
    case gfxAttachmentStoreOp::DontCare: return VK_ATTACHMENT_STORE_OP_DONT_CARE;
    default: epiLogError("Unhandled gfxAttachmentStoreOp=`{}`", storeOp); return VK_ATTACHMENT_STORE_OP_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkImageLayout gfxImageLayoutTo(gfxImageLayout layout)
{
    switch (layout)
    {
    case gfxImageLayout::Undefined: return VK_IMAGE_LAYOUT_UNDEFINED;
    case gfxImageLayout::General: return VK_IMAGE_LAYOUT_GENERAL;
    case gfxImageLayout::ColorAttachmentOptimal: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    case gfxImageLayout::DepthStencilAttachmentOptimal: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    case gfxImageLayout::DepthStencilReadOnlyOptimal: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    case gfxImageLayout::ShaderReadOnlyOptimal: return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    case gfxImageLayout::TransferSrcOptimal: return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    case gfxImageLayout::TransferDstOptimal: return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    case gfxImageLayout::Preinitialized: return VK_IMAGE_LAYOUT_PREINITIALIZED;
    case gfxImageLayout::DepthReadOnlyStencilAttachmentOptimal: return VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL;
    case gfxImageLayout::DepthAttachmentStencilReadOnlyOptimal: return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL;
    case gfxImageLayout::DepthAttachmentOptimal: return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
    case gfxImageLayout::DepthReadOnlyOptimal: return VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
    case gfxImageLayout::StencilAttachmentOptimal: return VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL;
    case gfxImageLayout::StencilReadOnlyOptimal: return VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL;
    case gfxImageLayout::PresentSrc: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    case gfxImageLayout::SharedPresent: return VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR;
    case gfxImageLayout::ShadingRateOptimal: return VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV;
    case gfxImageLayout::FragmentDensityMapOptimal: return VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT;
    default: epiLogError("Unhandled gfxImageLayout=`{}`", layout); return VK_IMAGE_LAYOUT_UNDEFINED; // TODO: use str repr of enum
    }
}

VkPipelineBindPoint gfxPipelineBindPointTo(gfxPipelineBindPoint bindPoint)
{
    switch (bindPoint)
    {
    case gfxPipelineBindPoint::Graphics: return VK_PIPELINE_BIND_POINT_GRAPHICS;
    case gfxPipelineBindPoint::Compute: return VK_PIPELINE_BIND_POINT_COMPUTE;
    case gfxPipelineBindPoint::RayTracing: return VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
    default: epiLogError("Unhandled gfxPipelineBindPoint=`{}`", bindPoint); return VK_PIPELINE_BIND_POINT_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkPolygonMode gfxPolygonModeTo(gfxPolygonMode polygonMode)
{
    switch (polygonMode)
    {
    case gfxPolygonMode::Fill: return VK_POLYGON_MODE_FILL;
    case gfxPolygonMode::Line: return VK_POLYGON_MODE_LINE;
    case gfxPolygonMode::Point: return VK_POLYGON_MODE_POINT;
    default: epiLogError("Unhandled gfxPolygonMode=`{}`", polygonMode); return VK_POLYGON_MODE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkCullModeFlagBits gfxCullModeTo(gfxCullMode cullMode)
{
    switch (cullMode)
    {
    case gfxCullMode::None: return VK_CULL_MODE_NONE;
    case gfxCullMode::Front: return VK_CULL_MODE_FRONT_BIT;
    case gfxCullMode::Back: return VK_CULL_MODE_BACK_BIT;
    case gfxCullMode::FrontBack: return VK_CULL_MODE_FRONT_AND_BACK;
    default: epiLogError("Unhandled gfxCullMode=`{}`", cullMode); return VK_CULL_MODE_FLAG_BITS_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkFrontFace gfxFrontFaceTo(gfxFrontFace frontFace)
{
    switch (frontFace)
    {
    case gfxFrontFace::CW: return VK_FRONT_FACE_CLOCKWISE;
    case gfxFrontFace::CCW: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    default: epiLogError("Unhandled gfxFrontFace=`{}`", frontFace); return VK_FRONT_FACE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkColorComponentFlagBits gfxColorComponentTo(gfxColorComponent colorComponent)
{
    return epiMask((colorComponent & gfxColorComponent_R) ? VK_COLOR_COMPONENT_R_BIT : VkColorComponentFlagBits{},
                   (colorComponent & gfxColorComponent_G) ? VK_COLOR_COMPONENT_G_BIT : VkColorComponentFlagBits{},
                   (colorComponent & gfxColorComponent_B) ? VK_COLOR_COMPONENT_B_BIT : VkColorComponentFlagBits{},
                   (colorComponent & gfxColorComponent_A) ? VK_COLOR_COMPONENT_A_BIT : VkColorComponentFlagBits{});
}

VkBlendFactor gfxBlendFactorTo(gfxBlendFactor blendFactor)
{
    switch (blendFactor)
    {
    case gfxBlendFactor::Zero: return VK_BLEND_FACTOR_ZERO;
    case gfxBlendFactor::One: return VK_BLEND_FACTOR_ONE;
    case gfxBlendFactor::SrcColor: return VK_BLEND_FACTOR_SRC_COLOR;
    case gfxBlendFactor::OneMinusSrcColor: return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
    case gfxBlendFactor::DstColor: return VK_BLEND_FACTOR_DST_COLOR;
    case gfxBlendFactor::OneMinusDstColor: return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
    case gfxBlendFactor::SrcAlpha: return VK_BLEND_FACTOR_SRC_ALPHA;
    case gfxBlendFactor::OneMinusSrcAlpha: return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    case gfxBlendFactor::DstAlpha: return VK_BLEND_FACTOR_DST_ALPHA;
    case gfxBlendFactor::OneMinusDstAlpha: return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
    case gfxBlendFactor::ConstantColor: return VK_BLEND_FACTOR_CONSTANT_COLOR;
    case gfxBlendFactor::OneMinusConstantColor: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
    case gfxBlendFactor::ConstantAlpha: return VK_BLEND_FACTOR_CONSTANT_ALPHA;
    case gfxBlendFactor::OneMinusConstantAlpha: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
    case gfxBlendFactor::SrcAlphaSaturate: return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
    case gfxBlendFactor::Src1Color: return VK_BLEND_FACTOR_SRC1_COLOR;
    case gfxBlendFactor::OneMinusSrc1Color: return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
    case gfxBlendFactor::Src1Alpha: return VK_BLEND_FACTOR_SRC1_ALPHA;
    case gfxBlendFactor::OneMinusSrc1Alpha: return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
    default: epiLogError("Unhandled gfxBlendFactor=`{}`", blendFactor); return VK_BLEND_FACTOR_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkBlendOp gfxBlendOpTo(gfxBlendOp blendOp)
{
    switch (blendOp)
    {
    case gfxBlendOp::Add: return VK_BLEND_OP_ADD;
    case gfxBlendOp::Subtract: return VK_BLEND_OP_SUBTRACT;
    case gfxBlendOp::ReverseSubtract: return VK_BLEND_OP_REVERSE_SUBTRACT;
    case gfxBlendOp::MIN: return VK_BLEND_OP_MIN;
    case gfxBlendOp::MAX: return VK_BLEND_OP_MAX;
    case gfxBlendOp::Zero: return VK_BLEND_OP_ZERO_EXT;
    case gfxBlendOp::Src: return VK_BLEND_OP_SRC_EXT;
    case gfxBlendOp::Dst: return VK_BLEND_OP_DST_EXT;
    case gfxBlendOp::SrcOver: return VK_BLEND_OP_SRC_OVER_EXT;
    case gfxBlendOp::DstOver: return VK_BLEND_OP_DST_OVER_EXT;
    case gfxBlendOp::SrcIn: return VK_BLEND_OP_SRC_IN_EXT;
    case gfxBlendOp::DstIn: return VK_BLEND_OP_DST_IN_EXT;
    case gfxBlendOp::SrcOut: return VK_BLEND_OP_SRC_OUT_EXT;
    case gfxBlendOp::DstOut: return VK_BLEND_OP_DST_OUT_EXT;
    case gfxBlendOp::SrcAtop: return VK_BLEND_OP_SRC_ATOP_EXT;
    case gfxBlendOp::DstAtop: return VK_BLEND_OP_DST_ATOP_EXT;
    case gfxBlendOp::Xor: return VK_BLEND_OP_XOR_EXT;
    case gfxBlendOp::Multiply: return VK_BLEND_OP_MULTIPLY_EXT;
    case gfxBlendOp::Screen: return VK_BLEND_OP_SCREEN_EXT;
    case gfxBlendOp::Overlay: return VK_BLEND_OP_OVERLAY_EXT;
    case gfxBlendOp::Darken: return VK_BLEND_OP_DARKEN_EXT;
    case gfxBlendOp::Lighten: return VK_BLEND_OP_LIGHTEN_EXT;
    case gfxBlendOp::ColorDodge: return VK_BLEND_OP_COLORDODGE_EXT;
    case gfxBlendOp::ColorBurn: return VK_BLEND_OP_COLORBURN_EXT;
    case gfxBlendOp::Hardlight: return VK_BLEND_OP_HARDLIGHT_EXT;
    case gfxBlendOp::Softlight: return VK_BLEND_OP_SOFTLIGHT_EXT;
    case gfxBlendOp::Difference: return VK_BLEND_OP_DIFFERENCE_EXT;
    case gfxBlendOp::Exclusion: return VK_BLEND_OP_EXCLUSION_EXT;
    case gfxBlendOp::Invert: return VK_BLEND_OP_INVERT_EXT;
    case gfxBlendOp::InvertRGB: return VK_BLEND_OP_INVERT_RGB_EXT;
    case gfxBlendOp::LinearDodge: return VK_BLEND_OP_LINEARDODGE_EXT;
    case gfxBlendOp::LinearBurn: return VK_BLEND_OP_LINEARBURN_EXT;
    case gfxBlendOp::VividLight: return VK_BLEND_OP_VIVIDLIGHT_EXT;
    case gfxBlendOp::LinearLight: return VK_BLEND_OP_LINEARLIGHT_EXT;
    case gfxBlendOp::PinLight: return VK_BLEND_OP_PINLIGHT_EXT;
    case gfxBlendOp::HardMix: return VK_BLEND_OP_HARDMIX_EXT;
    case gfxBlendOp::HSL_HUE: return VK_BLEND_OP_HSL_HUE_EXT;
    case gfxBlendOp::HSL_Saturation: return VK_BLEND_OP_HSL_SATURATION_EXT;
    case gfxBlendOp::HSL_Color: return VK_BLEND_OP_HSL_COLOR_EXT;
    case gfxBlendOp::HSL_Luminosity: return VK_BLEND_OP_HSL_LUMINOSITY_EXT;
    case gfxBlendOp::Plus: return VK_BLEND_OP_PLUS_EXT;
    case gfxBlendOp::PlusClamped: return VK_BLEND_OP_PLUS_CLAMPED_EXT;
    case gfxBlendOp::PlusClampedAlpha: return VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT;
    case gfxBlendOp::PlusDarker: return VK_BLEND_OP_PLUS_DARKER_EXT;
    case gfxBlendOp::Minus: return VK_BLEND_OP_MINUS_EXT;
    case gfxBlendOp::MinusClamped: return VK_BLEND_OP_MINUS_CLAMPED_EXT;
    case gfxBlendOp::Contrast: return VK_BLEND_OP_CONTRAST_EXT;
    case gfxBlendOp::InvertOVG: return VK_BLEND_OP_INVERT_OVG_EXT;
    case gfxBlendOp::Red: return VK_BLEND_OP_RED_EXT;
    case gfxBlendOp::Green: return VK_BLEND_OP_GREEN_EXT;
    case gfxBlendOp::Blue: return VK_BLEND_OP_BLUE_EXT;
    default: epiLogError("Unhandled gfxBlendOp=`{}`", blendOp); return VK_BLEND_OP_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkLogicOp gfxLogicOpTo(gfxLogicOp logicOp)
{
    switch (logicOp)
    {
    case gfxLogicOp::Clear: return VK_LOGIC_OP_CLEAR;
    case gfxLogicOp::And: return VK_LOGIC_OP_AND;
    case gfxLogicOp::AndReverse: return VK_LOGIC_OP_AND_REVERSE;
    case gfxLogicOp::Copy: return VK_LOGIC_OP_COPY;
    case gfxLogicOp::AndInverted: return VK_LOGIC_OP_AND_INVERTED;
    case gfxLogicOp::None: return VK_LOGIC_OP_NO_OP;
    case gfxLogicOp::Xor: return VK_LOGIC_OP_XOR;
    case gfxLogicOp::Or: return VK_LOGIC_OP_OR;
    case gfxLogicOp::Nor: return VK_LOGIC_OP_NOR;
    case gfxLogicOp::Equivalent: return VK_LOGIC_OP_EQUIVALENT;
    case gfxLogicOp::Invert: return VK_LOGIC_OP_INVERT;
    case gfxLogicOp::OrReverse: return VK_LOGIC_OP_OR_REVERSE;
    case gfxLogicOp::CopyInverted: return VK_LOGIC_OP_COPY_INVERTED;
    case gfxLogicOp::OrInverted: return VK_LOGIC_OP_OR_INVERTED;
    case gfxLogicOp::Nand: return VK_LOGIC_OP_NAND;
    case gfxLogicOp::Set: return VK_LOGIC_OP_SET;
    default: epiLogError("Unhandled gfxLogicOp=`{}`", logicOp); return VK_LOGIC_OP_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkImageType gfxImageTypeTo(gfxImageType type)
{
    switch (type)
    {
    case gfxImageType::Image1D: return VK_IMAGE_TYPE_1D;
    case gfxImageType::Image2D: return VK_IMAGE_TYPE_2D;
    case gfxImageType::Image3D: return VK_IMAGE_TYPE_3D;
    default: epiLogError("Unhandled gfxImageType=`{}`", type); return VK_IMAGE_TYPE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkImageViewType gfxImageViewTypeTo(gfxImageViewType viewType)
{
    switch (viewType)
    {
    case gfxImageViewType::ImageView1D: return VK_IMAGE_VIEW_TYPE_1D;
    case gfxImageViewType::ImageView2D: return VK_IMAGE_VIEW_TYPE_2D;
    case gfxImageViewType::ImageView3D: return VK_IMAGE_VIEW_TYPE_3D;
    case gfxImageViewType::ImageViewCube: return VK_IMAGE_VIEW_TYPE_CUBE;
    case gfxImageViewType::ImageView1DArray: return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
    case gfxImageViewType::ImageView2DArray: return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    case gfxImageViewType::ImageViewCubeArray: return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
    default: epiLogError("Unhandled gfxImageViewType=`{}`", viewType); return VK_IMAGE_VIEW_TYPE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkImageUsageFlagBits gfxImageUsageMaskTo(gfxImageUsageMask mask)
{
    return epiMask((mask & gfxImageUsageMask_TransferSrc) ? VK_IMAGE_USAGE_TRANSFER_SRC_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_TransferDst) ? VK_IMAGE_USAGE_TRANSFER_DST_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_Sampled) ? VK_IMAGE_USAGE_SAMPLED_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_Storage) ? VK_IMAGE_USAGE_STORAGE_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_ColorAttachment) ? VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_DepthStencilAttachment) ? VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_TransientAttachment) ? VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_InputAttachment) ? VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_ShadingRateImage) ? VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV : VkImageUsageFlagBits{},
                   (mask & gfxImageUsageMask_FragmentDensityMap) ? VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT : VkImageUsageFlagBits{});
}

VkPipelineStageFlagBits gfxPipelineStageTo(gfxPipelineStage stage)
{
    return epiMask((stage & gfxPipelineStage_TopOfPipe) ? VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_DrawIndirect) ? VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_VertexInput) ? VK_PIPELINE_STAGE_VERTEX_INPUT_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_VertexShader) ? VK_PIPELINE_STAGE_VERTEX_SHADER_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_TessellationControlShader) ? VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_TessellationEvaluationShader) ? VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_GeometryShader) ? VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_FragmentShader) ? VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_EarlyFragmentTests) ? VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_LateFragmentTests) ? VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_ColorAttachmentOutput) ? VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_ComputeShader) ? VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_Transfer) ? VK_PIPELINE_STAGE_TRANSFER_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_BottomOfPipe) ? VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_Host) ? VK_PIPELINE_STAGE_HOST_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_AllGraphics) ? VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_AllCommands) ? VK_PIPELINE_STAGE_ALL_COMMANDS_BIT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_TransformFeedback) ? VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_ConditionalRendering) ? VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_AccelerationStructureBuild) ? VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_RayTracingShader) ? VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_ShadingRateImage) ? VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_TaskShader) ? VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_MeshShader) ? VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_FragmentDensityProcess) ? VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT : VkPipelineStageFlagBits{},
                   (stage & gfxPipelineStage_CommandPreprocess) ? VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV : VkPipelineStageFlagBits{});
}

VkAccessFlagBits gfxAccessTo(gfxAccess access)
{
    return epiMask((access & gfxAccess_IndirectCommandRead) ? VK_ACCESS_INDIRECT_COMMAND_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_IndexRead) ? VK_ACCESS_INDEX_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_VertexAttributeRead) ? VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_UniformRead) ? VK_ACCESS_UNIFORM_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_InputAttachmentRead) ? VK_ACCESS_INPUT_ATTACHMENT_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_ShaderRead) ? VK_ACCESS_SHADER_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_ShaderWrite) ? VK_ACCESS_SHADER_WRITE_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_ColorAttachmentRead) ? VK_ACCESS_COLOR_ATTACHMENT_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_ColorAttachmentWrite) ? VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_DepthStencilAttachmentRead) ? VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_DepthStencilAttachmentWrite) ? VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_TransferRead) ? VK_ACCESS_TRANSFER_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_TransferWrite) ? VK_ACCESS_TRANSFER_WRITE_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_HostRead) ? VK_ACCESS_HOST_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_HostWrite) ? VK_ACCESS_HOST_WRITE_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_MemoryRead) ? VK_ACCESS_MEMORY_READ_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_MemoryWrite) ? VK_ACCESS_MEMORY_WRITE_BIT : VkAccessFlagBits{},
                   (access & gfxAccess_TransformFeedbackWrite) ? VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT : VkAccessFlagBits{},
                   (access & gfxAccess_TransformFeedbackCounterRead) ? VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT : VkAccessFlagBits{},
                   (access & gfxAccess_TransformFeedbackCounterWrite) ? VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT : VkAccessFlagBits{},
                   (access & gfxAccess_ConditionalRenderingRead) ? VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT : VkAccessFlagBits{},
                   (access & gfxAccess_ColorAttachmentReadNonCoherent) ? VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT : VkAccessFlagBits{},
                   (access & gfxAccess_AccelerationStructureRead) ? VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR : VkAccessFlagBits{},
                   (access & gfxAccess_AccelerationStructureWrite) ? VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR : VkAccessFlagBits{},
                   (access & gfxAccess_ShadingRateImageRead) ? VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV : VkAccessFlagBits{},
                   (access & gfxAccess_FragmentDensityMapRead) ? VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT : VkAccessFlagBits{},
                   (access & gfxAccess_CommandPreprocessRead) ? VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV : VkAccessFlagBits{},
                   (access & gfxAccess_CommandPreprocessWrite) ? VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV : VkAccessFlagBits{});
}

VkDependencyFlagBits gfxDependencyTo(gfxDependency dependency)
{
    return epiMask((dependency & gfxDependency_ByRegion) ? VK_DEPENDENCY_BY_REGION_BIT : VkDependencyFlagBits{},
                   (dependency & gfxDependency_DeviceGroup) ? VK_DEPENDENCY_DEVICE_GROUP_BIT : VkDependencyFlagBits{},
                   (dependency & gfxDependency_ViewLocal) ? VK_DEPENDENCY_VIEW_LOCAL_BIT : VkDependencyFlagBits{});
}

VkDynamicState gfxPipelineDynamicStateTo(gfxPipelineDynamicState state)
{
    switch (state)
    {
    case gfxPipelineDynamicState::Viewport: return VK_DYNAMIC_STATE_VIEWPORT;
    case gfxPipelineDynamicState::Scissor: return VK_DYNAMIC_STATE_SCISSOR;
    case gfxPipelineDynamicState::LineWidth: return VK_DYNAMIC_STATE_LINE_WIDTH;
    case gfxPipelineDynamicState::DepthBias: return VK_DYNAMIC_STATE_DEPTH_BIAS;
    case gfxPipelineDynamicState::BlendConstants: return VK_DYNAMIC_STATE_BLEND_CONSTANTS;
    case gfxPipelineDynamicState::DepthBounds: return VK_DYNAMIC_STATE_DEPTH_BOUNDS;
    case gfxPipelineDynamicState::StencilCompareMask: return VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK;
    case gfxPipelineDynamicState::StencilWriteMask: return VK_DYNAMIC_STATE_STENCIL_WRITE_MASK;
    case gfxPipelineDynamicState::StencilReference: return VK_DYNAMIC_STATE_STENCIL_REFERENCE;
    case gfxPipelineDynamicState::ViewportWScaling: return VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV;
    case gfxPipelineDynamicState::DiscardRectangle: return VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT;
    case gfxPipelineDynamicState::SampleLocations: return VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT;
    case gfxPipelineDynamicState::RayTracingPipelineStackSize: return VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR;
    case gfxPipelineDynamicState::ViewportShadingRatePalette: return VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV;
    case gfxPipelineDynamicState::ViewportCoarseSampleOrder: return VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV;
    case gfxPipelineDynamicState::ExclusiveScissor: return VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV;
    case gfxPipelineDynamicState::FragmentShadingRate: return VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR;
    case gfxPipelineDynamicState::LineStipple: return VK_DYNAMIC_STATE_LINE_STIPPLE_EXT;
    case gfxPipelineDynamicState::CullMode: return VK_DYNAMIC_STATE_CULL_MODE_EXT;
    case gfxPipelineDynamicState::FrontFace: return VK_DYNAMIC_STATE_FRONT_FACE_EXT;
    case gfxPipelineDynamicState::PrimitiveTopology: return VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT;
    case gfxPipelineDynamicState::ViewportWithCount: return VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT_EXT;
    case gfxPipelineDynamicState::ScissorWithCount: return VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT_EXT;
    case gfxPipelineDynamicState::VertexInputBindingStride: return VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT;
    case gfxPipelineDynamicState::DepthTestEnable: return VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT;
    case gfxPipelineDynamicState::DepthWriteEnable: return VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE_EXT;
    case gfxPipelineDynamicState::DepthCompareOp: return VK_DYNAMIC_STATE_DEPTH_COMPARE_OP_EXT;
    case gfxPipelineDynamicState::DepthBoundsTestEnable: return VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT;
    case gfxPipelineDynamicState::StencilTestEnable: return VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT;
    case gfxPipelineDynamicState::StencilOp: return VK_DYNAMIC_STATE_STENCIL_OP_EXT;
    default: epiLogError("Unhandled gfxPipelineDynamicState=`{}`", state); return VK_DYNAMIC_STATE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkVertexInputRate gfxPipelineVertexInputRateTo(gfxPipelineVertexInputRate rate)
{
    switch (rate)
    {
    case gfxPipelineVertexInputRate::Vertex: return VK_VERTEX_INPUT_RATE_VERTEX;
    case gfxPipelineVertexInputRate::Instance: return VK_VERTEX_INPUT_RATE_INSTANCE;
    default: epiLogError("Unhandled gfxPipelineVertexInputRate=`{}`", rate); return VK_VERTEX_INPUT_RATE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkBufferUsageFlagBits gfxBufferUsageMaskTo(gfxBufferUsageMask mask)
{
    return epiMask((mask & gfxBufferUsageMask_TransferSrc) ? VK_BUFFER_USAGE_TRANSFER_SRC_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_TransferDst) ? VK_BUFFER_USAGE_TRANSFER_DST_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_UniformTexelBuffer) ? VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_StorageTexelBuffer) ? VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_UniformBuffer) ? VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_StorageBuffer) ? VK_BUFFER_USAGE_STORAGE_BUFFER_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_IndexBuffer) ? VK_BUFFER_USAGE_INDEX_BUFFER_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_VertexBuffer) ? VK_BUFFER_USAGE_VERTEX_BUFFER_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_IndirectBuffer) ? VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_ShaderDeviceAddress) ? VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_TransformFeedbackBuffer) ? VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_TransformFeedbackCounterBuffer) ? VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_ConditionalRendering) ? VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_AccelerationStructureBuildInputReadOnly) ? VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_AccelerationStructureStorage) ? VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR : VkBufferUsageFlagBits{},
                   (mask & gfxBufferUsageMask_ShaderBindingTable) ? VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR : VkBufferUsageFlagBits{});
}

VkMemoryPropertyFlagBits gfxDeviceMemoryPropertyMaskTo(gfxDeviceMemoryPropertyMask mask)
{
    return epiMask((mask & gfxDeviceMemoryPropertyMask_DeviceLocal) ? VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT : VkMemoryPropertyFlagBits{},
                   (mask & gfxDeviceMemoryPropertyMask_HostVisible) ? VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT : VkMemoryPropertyFlagBits{},
                   (mask & gfxDeviceMemoryPropertyMask_HostCoherent) ? VK_MEMORY_PROPERTY_HOST_COHERENT_BIT : VkMemoryPropertyFlagBits{},
                   (mask & gfxDeviceMemoryPropertyMask_HostCached) ? VK_MEMORY_PROPERTY_HOST_CACHED_BIT : VkMemoryPropertyFlagBits{},
                   (mask & gfxDeviceMemoryPropertyMask_LazilyAllocated) ? VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT : VkMemoryPropertyFlagBits{},
                   (mask & gfxDeviceMemoryPropertyMask_Protected) ? VK_MEMORY_PROPERTY_PROTECTED_BIT : VkMemoryPropertyFlagBits{},
                   (mask & gfxDeviceMemoryPropertyMask_DeviceCoherent) ? VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD : VkMemoryPropertyFlagBits{},
                   (mask & gfxDeviceMemoryPropertyMask_DeviceUncached) ? VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD : VkMemoryPropertyFlagBits{});
}

VkCommandBufferUsageFlagBits gfxCommandBufferUsageTo(gfxCommandBufferUsage usage)
{
    return epiMask((usage & gfxCommandBufferUsage_OneTimeSubmit) ? VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT : VkCommandBufferUsageFlagBits{},
                   (usage & gfxCommandBufferUsage_RenderPassContinue) ? VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT : VkCommandBufferUsageFlagBits{},
                   (usage & gfxCommandBufferUsage_SimultaneousUse) ? VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT : VkCommandBufferUsageFlagBits{});
}

VkCommandPoolCreateFlagBits gfxCommandPoolUsageTo(gfxCommandPoolUsage usage)
{
    return epiMask((usage & gfxCommandPoolUsage_TRANSIENT) ? VK_COMMAND_POOL_CREATE_TRANSIENT_BIT : VkCommandPoolCreateFlagBits{},
                   (usage & gfxCommandPoolUsage_ResetCommandBuffer) ? VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT : VkCommandPoolCreateFlagBits{},
                   (usage & gfxCommandPoolUsage_Protected) ? VK_COMMAND_POOL_CREATE_PROTECTED_BIT : VkCommandPoolCreateFlagBits{});
}

VkIndexType gfxIndexBufferTypeTo(gfxIndexBufferType type)
{
    switch (type)
    {
    case gfxIndexBufferType::UInt16: return VK_INDEX_TYPE_UINT16;
    case gfxIndexBufferType::UInt32: return VK_INDEX_TYPE_UINT32;
    case gfxIndexBufferType::None: return VK_INDEX_TYPE_NONE_KHR;
    case gfxIndexBufferType::UInt8: return VK_INDEX_TYPE_UINT8_EXT;
    default: epiLogError("Unhandled gfxIndexBufferType=`{}`", type); return VK_INDEX_TYPE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkDescriptorSetLayoutCreateFlagBits gfxDescriptorSetLayoutUsageTo(gfxDescriptorSetLayoutUsage usage)
{
    return epiMask((usage & gfxDescriptorSetLayoutUsage_UpdateAfterBindPool) ? VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT : VkDescriptorSetLayoutCreateFlagBits{},
                   (usage & gfxDescriptorSetLayoutUsage_PushDescriptor) ? VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR : VkDescriptorSetLayoutCreateFlagBits{});
}

VkDescriptorType gfxDescriptorTypeTo(gfxDescriptorType type)
{
    switch (type)
    {
    case gfxDescriptorType::Sampler: return VK_DESCRIPTOR_TYPE_SAMPLER;
    case gfxDescriptorType::CombinedImageSampler: return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    case gfxDescriptorType::SampledImage: return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
    case gfxDescriptorType::StorageImage: return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    case gfxDescriptorType::UniformTexelBuffer: return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
    case gfxDescriptorType::StorageTexelBuffer: return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
    case gfxDescriptorType::UniformBuffer: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    case gfxDescriptorType::StorageBuffer: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    case gfxDescriptorType::UniformBufferDynamic: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    case gfxDescriptorType::StorageBufferDynamic: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
    case gfxDescriptorType::InputAttachment: return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
    case gfxDescriptorType::InlineUniformBlock: return VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT;
    case gfxDescriptorType::AccelerationStructure: return VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
    case gfxDescriptorType::AccelerationStructureNV: return VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
    default: epiLogError("Unhandled gfxDescriptorType=`{}`", type); return VK_DESCRIPTOR_TYPE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkShaderStageFlagBits gfxShaderStageTo(gfxShaderStage mask)
{
    return epiMask((mask & gfxShaderStage_Vertex) ? VK_SHADER_STAGE_VERTEX_BIT : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_TessellationControl) ? VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT: VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_TessellationEvaluation) ? VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Geometry) ? VK_SHADER_STAGE_GEOMETRY_BIT : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Fragment) ? VK_SHADER_STAGE_FRAGMENT_BIT : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Compute) ? VK_SHADER_STAGE_COMPUTE_BIT : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_AllGraphics) == gfxShaderStage_AllGraphics ? VK_SHADER_STAGE_ALL_GRAPHICS : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Raygen) ? VK_SHADER_STAGE_RAYGEN_BIT_KHR : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_AnyHit) ? VK_SHADER_STAGE_ANY_HIT_BIT_KHR : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_ClosestHit) ? VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Miss) ? VK_SHADER_STAGE_MISS_BIT_KHR : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Intersection) ? VK_SHADER_STAGE_INTERSECTION_BIT_KHR : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Callable) ? VK_SHADER_STAGE_CALLABLE_BIT_KHR : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Task) ? VK_SHADER_STAGE_TASK_BIT_NV : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_Mesh) ? VK_SHADER_STAGE_MESH_BIT_NV : VkShaderStageFlagBits{},
                   (mask & gfxShaderStage_All) == gfxShaderStage_All ? VK_SHADER_STAGE_ALL : VkShaderStageFlagBits{});
}

VkDescriptorPoolCreateFlags gfxDescriptorPoolUsageTo(gfxDescriptorPoolUsage usage)
{
    return epiMask((usage & gfxDescriptorPoolUsage_FreeDescriptorSet) ? VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT : VkDescriptorPoolCreateFlags{},
                   (usage & gfxDescriptorPoolUsage_UpdateAfterBind) ? VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT : VkDescriptorPoolCreateFlags{});
}

VkFenceCreateFlagBits gfxFenceCreateMaskTo(gfxFenceCreateMask mask)
{
    return epiMask((mask & gfxFenceCreateMask_Signaled) ? VK_FENCE_CREATE_SIGNALED_BIT : VkFenceCreateFlagBits{});
}

VkSemaphoreCreateFlags gfxSemaphoreCreateMaskTo(gfxSemaphoreCreateMask)
{
    return VkSemaphoreCreateFlags{};
}

VkSemaphoreWaitFlagBits gfxSemaphoreWaitMaskTo(gfxSemaphoreWaitMask mask)
{
    return epiMask((mask & gfxSemaphoreWaitMask_WaitAny) ? VK_SEMAPHORE_WAIT_ANY_BIT : VkSemaphoreWaitFlagBits{});
}

VkImageTiling gfxImageTilingTo(gfxImageTiling tiling)
{
    switch (tiling)
    {
    case gfxImageTiling::Optimal: return VK_IMAGE_TILING_OPTIMAL;
    case gfxImageTiling::Linear: return VK_IMAGE_TILING_LINEAR;
    default: epiLogError("Unhandled gfxImageTiling=`{}`", tiling); return VK_IMAGE_TILING_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkImageAspectFlagBits gfxImageAspectTo(gfxImageAspect mask)
{
    return epiMask((mask & gfxImageAspect_Color) ? VK_IMAGE_ASPECT_COLOR_BIT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_Depth) ? VK_IMAGE_ASPECT_DEPTH_BIT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_Stencil) ? VK_IMAGE_ASPECT_STENCIL_BIT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_Metadata) ? VK_IMAGE_ASPECT_METADATA_BIT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_Plane0) ? VK_IMAGE_ASPECT_PLANE_0_BIT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_Plane1) ? VK_IMAGE_ASPECT_PLANE_1_BIT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_Plane2) ? VK_IMAGE_ASPECT_PLANE_2_BIT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_MemoryPlane0) ? VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_MemoryPlane1) ? VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_MemoryPlane2) ? VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT : VkImageAspectFlagBits{},
                   (mask & gfxImageAspect_MemoryPlane3) ? VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT : VkImageAspectFlagBits{});
}

VkCompareOp gfxCompareOpTo(gfxCompareOp op)
{
    switch (op)
    {
    case gfxCompareOp::Never: return VK_COMPARE_OP_NEVER;
    case gfxCompareOp::Less: return VK_COMPARE_OP_LESS;
    case gfxCompareOp::Equal: return VK_COMPARE_OP_EQUAL;
    case gfxCompareOp::LessOrEqual: return VK_COMPARE_OP_LESS_OR_EQUAL;
    case gfxCompareOp::Greater: return VK_COMPARE_OP_GREATER;
    case gfxCompareOp::NotEqual: return VK_COMPARE_OP_NOT_EQUAL;
    case gfxCompareOp::GreaterOrEqual: return VK_COMPARE_OP_GREATER_OR_EQUAL;
    case gfxCompareOp::Always: return VK_COMPARE_OP_ALWAYS;
    default: epiLogError("Unhandled gfxCompareOp=`{}`", op); return VK_COMPARE_OP_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkSamplerCreateFlagBits gfxSamplerCreateMaskTo(gfxSamplerCreateMask mask)
{
    return epiMask((mask & gfxSamplerCreateMask_Subsampled) ? VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT : VkSamplerCreateFlagBits{},
                   (mask & gfxSamplerCreateMask_SubsampledCoarseReconstruction) ? VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT : VkSamplerCreateFlagBits{});
}

VkFilter gfxSamplerFilterModeTo(gfxSamplerFilterMode mode)
{
    switch (mode)
    {
    case gfxSamplerFilterMode::Nearest: return VK_FILTER_NEAREST;
    case gfxSamplerFilterMode::Linear: return VK_FILTER_LINEAR;
    case gfxSamplerFilterMode::Cubic: return VK_FILTER_CUBIC_IMG;
    default: epiLogError("Unhandled gfxSamplerFilterMode=`{}`", mode); return VK_FILTER_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkSamplerMipmapMode gfxSamplerMipmapModeTo(gfxSamplerMipmapMode mode)
{
    switch (mode)
    {
    case gfxSamplerMipmapMode::Nearest: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
    case gfxSamplerMipmapMode::Linear: return VK_SAMPLER_MIPMAP_MODE_LINEAR;
    default: epiLogError("Unhandled gfxSamplerMipmapMode=`{}`", mode); return VK_SAMPLER_MIPMAP_MODE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkSamplerAddressMode gfxSamplerAddressModeTo(gfxSamplerAddressMode mode)
{
    switch (mode)
    {
    case gfxSamplerAddressMode::Repeat: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
    case gfxSamplerAddressMode::MirroredRepeat: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
    case gfxSamplerAddressMode::ClampToEdge: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    case gfxSamplerAddressMode::ClampToBorder: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
    case gfxSamplerAddressMode::MirroredClampToEdge: return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
    default: epiLogError("Unhandled gfxSamplerAddressMode=`{}`", mode); return VK_SAMPLER_ADDRESS_MODE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkBorderColor gfxSamplerBorderColorTo(gfxSamplerBorderColor borderColor)
{
    switch (borderColor)
    {
    case gfxSamplerBorderColor::FloatTransparentBlack: return VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    case gfxSamplerBorderColor::IntTransparentBlack: return VK_BORDER_COLOR_INT_TRANSPARENT_BLACK;
    case gfxSamplerBorderColor::FloatOpaqueBlack: return VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
    case gfxSamplerBorderColor::IntOpaqueBlack: return VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    case gfxSamplerBorderColor::FloatOpaqueWhite: return VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
    case gfxSamplerBorderColor::IntOpaqueWhite: return VK_BORDER_COLOR_INT_OPAQUE_WHITE;
    case gfxSamplerBorderColor::FloatCustom: return VK_BORDER_COLOR_FLOAT_CUSTOM_EXT;
    case gfxSamplerBorderColor::IntCustom: return VK_BORDER_COLOR_INT_CUSTOM_EXT;
    default: epiLogError("Unhandled gfxSamplerBorderColor=`{}`", borderColor); return VK_BORDER_COLOR_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkComponentSwizzle gfxComponentSwizzleTo(gfxComponentSwizzle swizzle)
{
    switch (swizzle)
    {
    case gfxComponentSwizzle::Identity: return VK_COMPONENT_SWIZZLE_IDENTITY;
    case gfxComponentSwizzle::Zero: return VK_COMPONENT_SWIZZLE_ZERO;
    case gfxComponentSwizzle::One: return VK_COMPONENT_SWIZZLE_ONE;
    case gfxComponentSwizzle::R: return VK_COMPONENT_SWIZZLE_R;
    case gfxComponentSwizzle::G: return VK_COMPONENT_SWIZZLE_G;
    case gfxComponentSwizzle::B: return VK_COMPONENT_SWIZZLE_B;
    case gfxComponentSwizzle::A: return VK_COMPONENT_SWIZZLE_A;
    default: epiLogError("Unhandled gfxComponentSwizzle=`{}`", swizzle); return VK_COMPONENT_SWIZZLE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkSharingMode gfxSharingModeTo(gfxSharingMode mode)
{
    switch (mode)
    {
    case gfxSharingMode::Exclusive: return VK_SHARING_MODE_EXCLUSIVE;
    case gfxSharingMode::Concurrent: return VK_SHARING_MODE_CONCURRENT;
    default: epiLogError("Unhandled gfxSharingMode=`{}`", mode); return VK_SHARING_MODE_MAX_ENUM; // TODO: use str repr of enum
    }
}

VkBufferCreateFlagBits gfxBufferCreateMaskTo(gfxBufferCreateMask mask)
{
    return epiMask((mask & gfxBufferCreateMask_SparseBinding) ? VK_BUFFER_CREATE_SPARSE_BINDING_BIT : VkBufferCreateFlagBits{},
                   (mask & gfxBufferCreateMask_SparseResidency) ? VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT : VkBufferCreateFlagBits{},
                   (mask & gfxBufferCreateMask_SparseAliased) ? VK_BUFFER_CREATE_SPARSE_ALIASED_BIT : VkBufferCreateFlagBits{},
                   (mask & gfxBufferCreateMask_Protected) ? VK_BUFFER_CREATE_PROTECTED_BIT : VkBufferCreateFlagBits{},
                   (mask & gfxBufferCreateMask_DeviceAddressCaptureReplay) ? VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT : VkBufferCreateFlagBits{});
}

VkImageCreateFlagBits gfxImageCreateMaskTo(gfxImageCreateMask mask)
{
    return epiMask((mask & gfxImageCreateMask_SparseBinding) ? VK_IMAGE_CREATE_SPARSE_BINDING_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_SparseResidency) ? VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_SparseAliased) ? VK_IMAGE_CREATE_SPARSE_ALIASED_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_MutableFormat) ? VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_CubeCompatible) ? VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_Alias) ? VK_IMAGE_CREATE_ALIAS_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_SplitInstanceBindRegions) ? VK_IMAGE_CREATE_SPARSE_ALIASED_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_TwoDimensionalArrayCompatible) ? VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_BlockTexelViewCompatible) ? VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_ExtendedUsage) ? VK_IMAGE_CREATE_EXTENDED_USAGE_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_Protected) ? VK_IMAGE_CREATE_PROTECTED_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_Disjoint) ? VK_IMAGE_CREATE_DISJOINT_BIT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_CornerSampled) ? VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_SampleLocationsCompatibleDepth) ? VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT : VkImageCreateFlagBits{},
                   (mask & gfxImageCreateMask_Subsampled) ? VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT : VkImageCreateFlagBits{});
}

EPI_NAMESPACE_END()
