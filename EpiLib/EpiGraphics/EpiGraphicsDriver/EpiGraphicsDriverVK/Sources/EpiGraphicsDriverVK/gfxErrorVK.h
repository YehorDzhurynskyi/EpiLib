#pragma once

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

const epiChar* gfxErrorStr(VkResult result);

#define gfxLogError(r) do {((r) < 0 ? epiLogError("{}!", gfxErrorStr(r)) : epiLogInfo("{}.", gfxErrorStr(r)));} while (0)
#define gfxLogErrorEx(r, m) do {((r) < 0 ? epiLogError("{} {}!", m, gfxErrorStr(r)) : epiLogInfo("{} {}.", m, gfxErrorStr(r)));} while (0)
#define gfxLogErrorIfNotSuccess(r) do {if ((r) != VK_SUCCESS) { gfxLogError(r); }} while (0)
#define gfxLogErrorIfNotSuccessEx(r, m) do {if ((r) != VK_SUCCESS) { gfxLogErrorEx(r, m); }} while (0)

EPI_NAMESPACE_END()
