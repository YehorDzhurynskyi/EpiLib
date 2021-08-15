#pragma once

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

const epiChar* gfxVkResultStr(VkResult result);

#define gfxLogVkResult(r) do {((r) < 0 ? epiLogError("{}!", gfxVkResultStr(r)) : epiLogInfo("{}.", gfxVkResultStr(r)));} while (0)
#define gfxLogVkResultEx(r, m) do {((r) < 0 ? epiLogError("{} {}!", m, gfxVkResultStr(r)) : epiLogInfo("{} {}.", m, gfxVkResultStr(r)));} while (0)

EPI_NAMESPACE_END()
