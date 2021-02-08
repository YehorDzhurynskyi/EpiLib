#include "EpiGraphicsDriverVK/gfxDriverImplVK.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxSurfaceImplVK.h"

#ifdef EPI_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif // EPI_PLATFORM_WINDOWS

namespace
{

EPI_NAMESPACE_USING()

static VKAPI_ATTR VkBool32 VKAPI_CALL epiVKDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                         VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                         const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                         void* pUserData)
{
    const epiChar* type = nullptr;
    switch (messageType)
    {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: type = "GENERAL"; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: type = "SPEC Violation"; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: type = "NON-Optimal"; break;
    default: epiAssert(!"Unhandled case!");
    }

    // TODO: retrieve additional info from `pCallbackData`
    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: epiLogTrace("[{}]: {}", type, pCallbackData->pMessage); break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: epiLogDebug("[{}]: {}", type, pCallbackData->pMessage); break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: epiLogWarn("[{}]: {}", type, pCallbackData->pMessage); break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: epiLogError("[{}]: {}", type, pCallbackData->pMessage); break;
    default: epiAssert(!"Unhandled case!");
    }

    return VK_FALSE;
}

const epiChar* ExtensionNameOf(gfxDriverExtension extension)
{
    // TODO: check whether single bit provided
    static constexpr const epiChar* kNames[]
    {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    };

    static_assert(epiArrLen(kNames) == epiBitCount(gfxDriverExtension_ALL));

    const epiU32 at = epiBitPositionOf(extension);
    epiAssert(at < epiArrLen(kNames));

    return kNames[at];
}

gfxDriverExtension SupportedInstanceExtensionMask()
{
    epiU32 supportedExtensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionsCount, nullptr);

    std::vector<VkExtensionProperties> supportedExtensions(supportedExtensionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionsCount, supportedExtensions.data());

    epiU64 mask = 0;
    for (const auto& extension : supportedExtensions)
    {
        if (strcmp(extension.extensionName, VK_KHR_SURFACE_EXTENSION_NAME) == 0)
        {
            mask |= gfxDriverExtension_Surface;
        }
        else if (strcmp(extension.extensionName, VK_KHR_WIN32_SURFACE_EXTENSION_NAME) == 0)
        {
            mask |= gfxDriverExtension_SurfaceWin32;
        }
        else
        {
            epiLogWarn("Unrecognized Vulkan instance extension=`{}`!", extension.extensionName);
        }
    }

    return static_cast<gfxDriverExtension>(mask);
}

}

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxDriverImplVK::gfxDriverImplVK(epiU32 apiVersionMajor,
                                 epiU32 apiVersionMinor,
                                 epiU32 apiVersionPatch,
                                 const epiChar* appName,
                                 gfxDriverExtension extensionMaskRequired,
                                 epiU32 appVersionMajor,
                                 epiU32 appVersionMinor,
                                 epiU32 appVersionPatch,
                                 const epiChar* engineName,
                                 epiU32 engineVersionMajor,
                                 epiU32 engineVersionMinor,
                                 epiU32 engineVersionPatch)
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_VERSION(appVersionMajor, appVersionMinor, appVersionPatch);
    appInfo.pEngineName = engineName;
    appInfo.engineVersion = VK_MAKE_VERSION(engineVersionMajor, engineVersionMinor, engineVersionPatch);
    appInfo.apiVersion = VK_MAKE_VERSION(apiVersionMajor, apiVersionMinor, apiVersionPatch);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

#ifdef EPI_BUILD_DEBUG
    std::vector<const epiChar*> validationLayers {
        "VK_LAYER_KHRONOS_validation"
    };

    epiU32 availableLayersCount;
    vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(availableLayersCount);
    vkEnumerateInstanceLayerProperties(&availableLayersCount, availableLayers.data());

    const epiBool validationLayersSupported = std::all_of(validationLayers.begin(),
                                                          validationLayers.end(),
                                                          [availableLayers](const epiChar* validationLayer) {
        const epiBool validationLayerSupported = availableLayers.end() != std::find_if(availableLayers.begin(),
                                                                                       availableLayers.end(),
                                                                                       [validationLayer](const VkLayerProperties& layerProperties)
        {
            return strcmp(layerProperties.layerName, validationLayer) == 0;
        });

        return validationLayerSupported;
    });

    epiAssert(validationLayersSupported);

    createInfo.enabledLayerCount = static_cast<epiU32>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();

    VkDebugUtilsMessengerCreateInfoEXT createInfoDebugMessenger{};
    createInfoDebugMessenger.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfoDebugMessenger.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfoDebugMessenger.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfoDebugMessenger.pfnUserCallback = epiVKDebugCallback;
    createInfoDebugMessenger.pUserData = nullptr;

    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&createInfoDebugMessenger;
#endif // EPI_BUILD_DEBUG

    m_ExtensionMaskSupported = SupportedInstanceExtensionMask();

    epiS32 extensionMaskEnabled = 0;
    std::vector<const epiChar*> extensions;
    for (epiU32 bit = 1; bit < gfxDriverExtension_MAX; bit = bit << 1)
    {
        const gfxDriverExtension extension = static_cast<gfxDriverExtension>(bit);
        if (extension & extensionMaskRequired == 0)
        {
            continue;
        }

        if (extension & m_ExtensionMaskSupported == 0)
        {
            // TODO: get string representation
            epiLogFatal("Required Vulkan intance extension=`{}` is not supported!", extension);
            continue;
        }

        extensionMaskEnabled |= extension;

        extensions.push_back(ExtensionNameOf(extension));
    }

#ifdef EPI_BUILD_DEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledExtensionCount = extensions.size();
    m_ExtensionMaskEnabled = static_cast<gfxDriverExtension>(extensionMaskEnabled);

    VkResult resultCreateInstance = vkCreateInstance(&createInfo, nullptr, &m_VkInstance);
    epiAssert(resultCreateInstance == VK_SUCCESS);

#ifdef EPI_BUILD_DEBUG
    PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXTFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_VkInstance, "vkCreateDebugUtilsMessengerEXT");
    epiAssert(vkCreateDebugUtilsMessengerEXTFunc != nullptr);

    VkResult resultCreateDebugMessenger = vkCreateDebugUtilsMessengerEXTFunc(m_VkInstance, &createInfoDebugMessenger, nullptr, &m_VKDebugMessenger);
    epiAssert(resultCreateDebugMessenger == VK_SUCCESS);
#endif // EPI_BUILD_DEBUG

    m_Surface = std::make_unique<gfxSurfaceImplVK>(m_VkInstance);
}

gfxDriverImplVK::~gfxDriverImplVK()
{
#ifdef EPI_BUILD_DEBUG
    if (m_VKDebugMessenger != VK_NULL_HANDLE)
    {
        PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXTFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyDebugUtilsMessengerEXT");
        epiAssert(vkDestroyDebugUtilsMessengerEXTFunc != nullptr);

        vkDestroyDebugUtilsMessengerEXTFunc(m_VkInstance, m_VKDebugMessenger, nullptr);
    }
#endif // EPI_BUILD_DEBUG

    if (m_VkInstance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(m_VkInstance, nullptr);
    }

    epiU32 deviceCount = 0;
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, nullptr);
    epiAssert(deviceCount != 0);

    std::vector<VkPhysicalDevice> vkDevices(deviceCount);
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, vkDevices.data());

    for (const auto& vkDevice : vkDevices)
    {
        m_PhysicalDevices.push_back(new gfxPhysicalDeviceImplVK(vkDevice, *m_Surface));
    }
}

const epiPtrArray<gfxPhysicalDeviceImpl>& gfxDriverImplVK::GetPhysicalDevices() const
{
    return m_PhysicalDevices;
}

const epiBool gfxDriverImplVK::IsExtensionsSupported(gfxDriverExtension mask) const
{
    return (m_ExtensionMaskSupported & mask) == mask;
}

const epiBool gfxDriverImplVK::IsExtensionsEnabled(gfxDriverExtension mask) const
{
    return (m_ExtensionMaskEnabled & mask) == mask;
}

VkInstance gfxDriverImplVK::GetVkInstance() const
{
    return m_VkInstance;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
