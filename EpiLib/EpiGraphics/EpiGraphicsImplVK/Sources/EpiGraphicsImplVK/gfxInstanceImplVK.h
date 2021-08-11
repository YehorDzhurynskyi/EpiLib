#pragma once

#include "EpiGraphicsImpl/gfxInstanceImpl.h"

struct VkDebugUtilsMessengerEXT_T;
struct VkInstance_T;

EPI_NAMESPACE_BEGIN()

class gfxInstanceImplVK : public gfxInstance::Impl
{
public:
    gfxInstanceImplVK() = default;
    gfxInstanceImplVK(const gfxInstanceImplVK& rhs) = delete;
    gfxInstanceImplVK& operator=(const gfxInstanceImplVK& rhs) = delete;
    gfxInstanceImplVK(gfxInstanceImplVK&& rhs) = delete;
    gfxInstanceImplVK& operator=(gfxInstanceImplVK&& rhs) = delete;
    ~gfxInstanceImplVK() override;

    epiBool Init(epiU32 apiVersionMajor,
                 epiU32 apiVersionMinor,
                 epiU32 apiVersionPatch,
                 const epiChar* appName,
                 const epiArray<gfxInstanceExtension>& extensionRequired,
                 epiU32 appVersionMajor = 1u,
                 epiU32 appVersionMinor = 0u,
                 epiU32 appVersionPatch = 0u,
                 const epiChar* engineName = "No Engine",
                 epiU32 engineVersionMajor = 1u,
                 epiU32 engineVersionMinor = 0u,
                 epiU32 engineVersionPatch = 0u);

    std::shared_ptr<gfxSurface::Impl> CreateSurface(const gfxWindow& window) const override;
    std::shared_ptr<gfxDevice::Impl> CreateDevice(const gfxDeviceCreateInfo& info) const override;

    epiBool IsExtensionSupported(gfxInstanceExtension extension) const override;
    epiBool IsExtensionEnabled(gfxInstanceExtension extension) const override;

    VkInstance_T* GetVkInstance() const;

protected:
    void FillExtensionsSupported();

protected:
    VkInstance_T* m_VkInstance{nullptr};
    EPI_BUILD_DEBUG_ONLY(VkDebugUtilsMessengerEXT_T* m_VKDebugMessenger{nullptr});
    epiBool m_ExtensionSupported[static_cast<epiU32>(gfxInstanceExtension::COUNT)]{};
    epiBool m_ExtensionEnabled[static_cast<epiU32>(gfxInstanceExtension::COUNT)]{};
};

EPI_NAMESPACE_END()
