#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

class gfxSurfaceImplVK;
class gfxDriverVK : public gfxDriver
{
public:
    gfxDriverVK(epiU32 apiVersionMajor,
                epiU32 apiVersionMinor,
                epiU32 apiVersionPatch,
                const epiChar* appName,
                gfxDriverExtension extensionMask,
                epiU32 appVersionMajor = 1u,
                epiU32 appVersionMinor = 0u,
                epiU32 appVersionPatch = 0u,
                const epiChar* engineName = "No Engine",
                epiU32 engineVersionMajor = 1u,
                epiU32 engineVersionMinor = 0u,
                epiU32 engineVersionPatch = 0u);
    ~gfxDriverVK() override;

    epiPtrArray<gfxPhysicalDeviceImpl> ListOfPhysicalDevices() const override;

    VkInstance GetVkInstance() const;

protected:
    VkInstance m_VkInstance{VK_NULL_HANDLE};
    EPI_BUILD_DEBUG_ONLY(VkDebugUtilsMessengerEXT m_VKDebugMessenger{VK_NULL_HANDLE});
    std::unique_ptr<gfxSurfaceImplVK> m_Surface;
};

EPI_NAMESPACE_END()
