#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"

struct VkDebugUtilsMessengerEXT_T;
struct VkInstance_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImplVK;
class gfxDriverImplVK : public gfxDriverImpl
{
public:
    gfxDriverImplVK() = default;
    gfxDriverImplVK(const gfxDriverImplVK& rhs) = delete;
    gfxDriverImplVK& operator=(const gfxDriverImplVK& rhs) = delete;
    gfxDriverImplVK(gfxDriverImplVK&& rhs) = delete;
    gfxDriverImplVK& operator=(gfxDriverImplVK&& rhs) = delete;
    ~gfxDriverImplVK() override;

    epiBool Init(epiU32 apiVersionMajor,
                 epiU32 apiVersionMinor,
                 epiU32 apiVersionPatch,
                 const epiChar* appName,
                 const epiArray<gfxDriverExtension>& extensionRequired,
                 epiU32 appVersionMajor = 1u,
                 epiU32 appVersionMinor = 0u,
                 epiU32 appVersionPatch = 0u,
                 const epiChar* engineName = "No Engine",
                 epiU32 engineVersionMajor = 1u,
                 epiU32 engineVersionMinor = 0u,
                 epiU32 engineVersionPatch = 0u);

    std::shared_ptr<gfxSurfaceImpl> CreateSurface(const gfxWindow& window) override;

    epiBool IsExtensionSupported(gfxDriverExtension extension) const override;
    epiBool IsExtensionEnabled(gfxDriverExtension extension) const override;

    VkInstance_T* GetVkInstance() const;

protected:
    void FillExtensionsSupported();

protected:
    VkInstance_T* m_VkInstance{nullptr};
    EPI_BUILD_DEBUG_ONLY(VkDebugUtilsMessengerEXT_T* m_VKDebugMessenger{nullptr});
    epiBool m_ExtensionSupported[static_cast<epiU32>(gfxDriverExtension::COUNT)]{};
    epiBool m_ExtensionEnabled[static_cast<epiU32>(gfxDriverExtension::COUNT)]{};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
