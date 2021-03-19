#pragma once

#include "EpiGraphicsDriverCommon/gfxEnum.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

gfxFormat gfxFormatFrom(VkFormat formatVk);
gfxSurfaceColorSpace gfxSurfaceColorSpaceFrom(VkColorSpaceKHR colorSpaceVk);
gfxSurfaceTransform gfxSurfaceTransformFrom(VkSurfaceTransformFlagsKHR transform);
gfxCompositeAlpha gfxCompositeAlphaFrom(VkCompositeAlphaFlagsKHR compositeAlpha);
gfxImageUsage gfxImageUsageFrom(VkImageUsageFlags usage);

VkFormat gfxFormatTo(gfxFormat format);
VkColorSpaceKHR gfxSurfaceColorSpaceTo(gfxSurfaceColorSpace colorSpace);
VkSurfaceTransformFlagBitsKHR gfxSurfaceTransformTo(gfxSurfaceTransform transform);
VkPresentModeKHR gfxSurfacePresentModeTo(gfxSurfacePresentMode presentMode);
VkPrimitiveTopology gfxPipelineInputAssemblyTypeTo(gfxPipelineInputAssemblyType type);
VkSampleCountFlagBits gfxSampleCountTo(gfxSampleCount sampleCount);
VkAttachmentLoadOp gfxAttachmentLoadOpTo(gfxAttachmentLoadOp loadOp);
VkAttachmentStoreOp gfxAttachmentStoreOpTo(gfxAttachmentStoreOp storeOp);
VkImageLayout gfxImageLayoutTo(gfxImageLayout layout);
VkPipelineBindPoint gfxPipelineBindPointTo(gfxPipelineBindPoint bindPoint);
VkPolygonMode gfxPolygonModeTo(gfxPolygonMode polygonMode);
VkCullModeFlagBits gfxCullModeTo(gfxCullMode cullMode);
VkFrontFace gfxFrontFaceTo(gfxFrontFace frontFace);
VkColorComponentFlagBits gfxColorComponentTo(gfxColorComponent colorComponent);
VkBlendFactor gfxBlendFactorTo(gfxBlendFactor blendFactor);
VkBlendOp gfxBlendOpTo(gfxBlendOp blendOp);
VkLogicOp gfxLogicOpTo(gfxLogicOp logicOp);
VkImageType gfxTextureTypeTo(gfxTextureType type);
VkImageViewType gfxTextureViewTypeTo(gfxTextureViewType viewType);
VkImageUsageFlagBits gfxImageUsageTo(gfxImageUsage usage);

EPI_NAMESPACE_END()
