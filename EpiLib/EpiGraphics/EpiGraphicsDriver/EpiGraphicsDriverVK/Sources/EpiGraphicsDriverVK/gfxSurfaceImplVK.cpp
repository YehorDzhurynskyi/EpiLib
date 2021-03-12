#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"

#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"

#include <vulkan/vulkan.hpp>

#ifdef EPI_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif // EPI_PLATFORM_WINDOWS

namespace
{

EPI_NAMESPACE_USING()

gfxSurfaceFormat ConvertSurfaceFormat(VkSurfaceFormatKHR formatVk)
{
    gfxFormat format = gfxFormat::UNDEFINED;
    switch (formatVk.format)
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

    gfxSurfaceColorSpace colorSpace = gfxSurfaceColorSpace::SRGB_NONLINEAR;
    switch (formatVk.colorSpace)
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

    gfxSurfaceFormat surfaceFormat{};
    surfaceFormat.SetFormat(format);
    surfaceFormat.SetColorSpace(colorSpace);

    return surfaceFormat;
}

}

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxSurfaceImplVK::gfxSurfaceImplVK(VkInstance_T* instance, const gfxWindow& window)
    : m_VkInstance{instance}
{
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = window.GetHWND();
    createInfo.hinstance = GetModuleHandle(nullptr);

    VkResult resultCreateWin32SurfaceKHR = vkCreateWin32SurfaceKHR(m_VkInstance, &createInfo, nullptr, &m_VkSurface);
    epiAssert(resultCreateWin32SurfaceKHR == VK_SUCCESS);
}

gfxSurfaceImplVK::~gfxSurfaceImplVK()
{
    if (m_VkSurface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(m_VkInstance, m_VkSurface, nullptr);
    }
}

epiBool gfxSurfaceImplVK::IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    return std::any_of(deviceVk.GetQueueFamilies().begin(), deviceVk.GetQueueFamilies().end(), [this, &deviceVk](const gfxQueueFamilyImpl& queueFamily)
    {
        return IsPresentSupportedFor(deviceVk, queueFamily);
    });
}

epiBool gfxSurfaceImplVK::IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device, const gfxQueueFamilyImpl& queueFamily) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);
    const gfxQueueFamilyImplVK& queueFamilyVk = static_cast<const gfxQueueFamilyImplVK&>(queueFamily);

    VkBool32 presentSupported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(deviceVk.GetVkPhysicalDevice(), queueFamilyVk.GetIndex(), GetVkSurface(), &presentSupported);

    return presentSupported;
}

gfxSurfaceCapabilities gfxSurfaceImplVK::GetCapabilitiesFor(const gfxPhysicalDeviceImpl& device) const
{
    gfxSurfaceCapabilities capabilities;

    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    VkSurfaceCapabilitiesKHR capabilitiesVk;
    const VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &capabilitiesVk);
    epiAssert(result == VK_SUCCESS);

    capabilities.SetMinImageCount(capabilitiesVk.minImageCount);
    capabilities.SetMaxImageCount(capabilitiesVk.maxImageCount);
    capabilities.SetMaxImageArrayLayers(capabilitiesVk.maxImageArrayLayers);
    capabilities.SetCurrentExtent(epiSize2u{capabilitiesVk.currentExtent.width, capabilitiesVk.currentExtent.height});
    capabilities.SetMinImageExtent(epiSize2u{capabilitiesVk.minImageExtent.width, capabilitiesVk.minImageExtent.height});
    capabilities.SetMaxImageExtent(epiSize2u{capabilitiesVk.maxImageExtent.width, capabilitiesVk.maxImageExtent.height});

    return capabilities;
}

epiArray<gfxSurfaceFormat> gfxSurfaceImplVK::GetSupportedFormatsFor(const gfxPhysicalDeviceImpl& device) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    epiU32 formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &formatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> formatsVk;
    formatsVk.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &formatCount, formatsVk.data());

    epiArray<gfxSurfaceFormat> formats;
    for (const VkSurfaceFormatKHR& format : formatsVk)
    {
        formats.push_back(ConvertSurfaceFormat(format));
    }

    return formats;
}

epiArray<gfxSurfacePresentMode> gfxSurfaceImplVK::GetSupportedPresentModesFor(const gfxPhysicalDeviceImpl& device) const
{
    const gfxPhysicalDeviceImplVK& deviceVk = static_cast<const gfxPhysicalDeviceImplVK&>(device);

    epiU32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &presentModeCount, nullptr);

    std::vector<VkPresentModeKHR> presentModesVk;
    presentModesVk.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(deviceVk.GetVkPhysicalDevice(), GetVkSurface(), &presentModeCount, presentModesVk.data());

    epiArray<gfxSurfacePresentMode> presentModes;
    for (const VkPresentModeKHR& presentModeVk : presentModesVk)
    {
        gfxSurfacePresentMode presentMode;
        switch (presentModeVk)
        {
            case VK_PRESENT_MODE_IMMEDIATE_KHR: presentMode = gfxSurfacePresentMode::IMMEDIATE; break;
            case VK_PRESENT_MODE_MAILBOX_KHR: presentMode = gfxSurfacePresentMode::MAILBOX; break;
            case VK_PRESENT_MODE_FIFO_KHR: presentMode = gfxSurfacePresentMode::FIFO; break;
            case VK_PRESENT_MODE_FIFO_RELAXED_KHR: presentMode = gfxSurfacePresentMode::FIFO_RELAXED; break;
            case VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR: presentMode = gfxSurfacePresentMode::SHARED_DEMAND_REFRESH; break;
            case VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR: presentMode = gfxSurfacePresentMode::SHARED_CONTINUOUS_REFRESH; break;
        }

        presentModes.push_back(presentMode);
    }

    return presentModes;
}

VkSurfaceKHR gfxSurfaceImplVK::GetVkSurface() const
{
    return m_VkSurface;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
