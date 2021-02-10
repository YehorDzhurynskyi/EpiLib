#pragma once

#include "EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h"

struct VkDebugUtilsMessengerEXT_T;
struct VkInstance_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImplVK;
class gfxDriverImplVK : public gfxDriverImpl
{
public:
    gfxDriverImplVK(epiU32 apiVersionMajor,
                    epiU32 apiVersionMinor,
                    epiU32 apiVersionPatch,
                    const epiChar* appName,
                    gfxDriverExtension extensionMaskRequired,
                    epiU32 appVersionMajor = 1u,
                    epiU32 appVersionMinor = 0u,
                    epiU32 appVersionPatch = 0u,
                    const epiChar* engineName = "No Engine",
                    epiU32 engineVersionMajor = 1u,
                    epiU32 engineVersionMinor = 0u,
                    epiU32 engineVersionPatch = 0u);
    ~gfxDriverImplVK() override;

    const epiPtrArray<gfxPhysicalDeviceImpl>& GetPhysicalDevices() const override;

    epiBool IsExtensionsSupported(gfxDriverExtension mask) const override;
    epiBool IsExtensionsEnabled(gfxDriverExtension mask) const override;

    VkInstance_T* GetVkInstance() const;

protected:
    VkInstance_T* m_VkInstance{nullptr};
    EPI_BUILD_DEBUG_ONLY(VkDebugUtilsMessengerEXT_T* m_VKDebugMessenger{nullptr});
    std::unique_ptr<gfxSurfaceImplVK> m_Surface;
    epiPtrArray<gfxPhysicalDeviceImpl> m_PhysicalDevices;
    gfxDriverExtension m_ExtensionMaskSupported{0};
    gfxDriverExtension m_ExtensionMaskEnabled{0};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
