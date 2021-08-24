#include "EpiGraphicsImplVK/gfxInstanceImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxSurfaceImplVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"

#include <vulkan/vulkan.h>

#ifdef EPI_PLATFORM_WINDOWS
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif // EPI_PLATFORM_WINDOWS

namespace
{

EPI_NAMESPACE_USING()

static constexpr const epiChar* kDriverExtensionNames[]
{
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME
};
static_assert(epiArrLen(kDriverExtensionNames) == static_cast<epiU32>(gfxInstanceExtension::COUNT));

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

const epiChar* ExtensionNameOf(gfxInstanceExtension extension)
{
    const epiU32 at = static_cast<epiU32>(extension);
    epiAssert(at < epiArrLen(kDriverExtensionNames));

    return kDriverExtensionNames[at];
}

}

EPI_NAMESPACE_BEGIN()

epiBool gfxInstanceImplVK::Init(epiU32 apiVersionMajor,
                                epiU32 apiVersionMinor,
                                epiU32 apiVersionPatch,
                                const epiChar* appName,
                                const epiArray<gfxInstanceExtension>& extensionRequired,
                                epiU32 appVersionMajor,
                                epiU32 appVersionMinor,
                                epiU32 appVersionPatch,
                                const epiChar* engineName,
                                epiU32 engineVersionMajor,
                                epiU32 engineVersionMinor,
                                epiU32 engineVersionPatch)
{
    FillExtensionsSupported();

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_VERSION(appVersionMajor, appVersionMinor, appVersionPatch);
    appInfo.pEngineName = engineName;
    appInfo.engineVersion = VK_MAKE_VERSION(engineVersionMajor, engineVersionMinor, engineVersionPatch);
    appInfo.apiVersion = VK_MAKE_VERSION(apiVersionMajor, apiVersionMinor, apiVersionPatch);

    m_VkAPIVersion = appInfo.apiVersion;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

#ifdef EPI_BUILD_DEBUG
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

    std::vector<const epiChar*> validationLayers;

#ifdef EPI_BUILD_DEBUG
    validationLayers.push_back("VK_LAYER_KHRONOS_validation");
    //validationLayers.push_back("VK_LAYER_RENDERDOC_Capture");
    //validationLayers.push_back("VK_LAYER_LUNARG_api_dump");
    //validationLayers.push_back("VK_LAYER_NV_optimus");
#endif // EPI_BUILD_DEBUG

    epiU32 availableLayersCount;
    vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(availableLayersCount);
    vkEnumerateInstanceLayerProperties(&availableLayersCount, availableLayers.data());

    const epiBool validationLayersSupported = std::all_of(validationLayers.begin(),
                                                          validationLayers.end(),
                                                          [availableLayers](const epiChar* validationLayer)
    {
        const epiBool validationLayerSupported = availableLayers.end() != std::find_if(availableLayers.begin(),
                                                                                       availableLayers.end(),
                                                                                       [validationLayer](const VkLayerProperties& layerProperties)
        {
            return strcmp(layerProperties.layerName, validationLayer) == 0;
        });

        return validationLayerSupported;
    });

    if (!validationLayersSupported)
    {
        epiLogError("Some validation layer isn't supported!");
        return false;
    }

    createInfo.enabledLayerCount = static_cast<epiU32>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();

    std::vector<const epiChar*> extensions;
    for (gfxInstanceExtension extension : extensionRequired)
    {
        if (!IsExtensionSupported(extension))
        {
            // TODO: get string representation
            epiLogError("Required Vulkan intance extension=`{}` is not supported!", extension);
            return false;
        }

        m_ExtensionEnabled[static_cast<epiU32>(extension)] = true;

        extensions.push_back(ExtensionNameOf(extension));
    }

#ifdef EPI_BUILD_DEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    // extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif // EPI_BUILD_DEBUG

    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledExtensionCount = extensions.size();

    if (const VkResult result = vkCreateInstance(&createInfo, nullptr, &m_VkInstance); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateInstance!");
        return false;
    }

#ifdef EPI_BUILD_DEBUG
    PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXTFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_VkInstance, "vkCreateDebugUtilsMessengerEXT");
    if (vkCreateDebugUtilsMessengerEXTFunc == nullptr)
    {
        epiLogError("Failed to get 'PFN_vkCreateDebugUtilsMessengerEXT' func address via 'vkGetInstanceProcAddr'!");
        return false;
    }

    if (const VkResult result = vkCreateDebugUtilsMessengerEXTFunc(m_VkInstance, &createInfoDebugMessenger, nullptr, &m_VKDebugMessenger); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateDebugUtilsMessengerEXTFunc!");
        return false;
    }
#endif // EPI_BUILD_DEBUG

    epiU32 deviceCount = 0;
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, nullptr);
    epiAssert(deviceCount != 0);

    std::vector<VkPhysicalDevice> vkDevices(deviceCount);
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, vkDevices.data());

    gfxInstance instance(shared_from_this());
    for (const VkPhysicalDevice& vkDevice : vkDevices)
    {
        std::shared_ptr<gfxPhysicalDeviceImplVK> physicalDevice = std::make_shared<gfxPhysicalDeviceImplVK>(instance);
        physicalDevice->Init(vkDevice);

        m_PhysicalDevices.push_back(std::move(physicalDevice));
    }

    return true;
}

gfxInstanceImplVK::~gfxInstanceImplVK()
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
}

std::shared_ptr<gfxSurface::Impl> gfxInstanceImplVK::CreateSurface(const gfxWindow& window) const
{
    std::shared_ptr<gfxSurfaceImplVK> impl = std::make_shared<gfxSurfaceImplVK>(m_VkInstance);
    if (!impl->Init(window))
    {
        impl.reset();
    }

    return impl;
}

epiBool gfxInstanceImplVK::IsExtensionSupported(gfxInstanceExtension extension) const
{
    return m_ExtensionSupported[static_cast<epiU32>(extension)];
}

epiBool gfxInstanceImplVK::IsExtensionEnabled(gfxInstanceExtension extension) const
{
    return m_ExtensionEnabled[static_cast<epiU32>(extension)];
}

VkInstance gfxInstanceImplVK::GetVkInstance() const
{
    return m_VkInstance;
}

epiU32 gfxInstanceImplVK::GetVkAPIVersion() const
{
    return m_VkAPIVersion;
}

void gfxInstanceImplVK::FillExtensionsSupported()
{
    epiU32 supportedExtensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionsCount, nullptr);

    std::vector<VkExtensionProperties> supportedExtensions(supportedExtensionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionsCount, supportedExtensions.data());

    for (const auto& extension : supportedExtensions)
    {
        const auto it = std::find_if(kDriverExtensionNames,
                                     kDriverExtensionNames + epiArrLen(kDriverExtensionNames),
                                     [needle = extension.extensionName](const epiChar* name) {
            return strncmp(needle, name, strlen(name)) == 0;
        });

        if (it != kDriverExtensionNames + epiArrLen(kDriverExtensionNames))
        {
            m_ExtensionSupported[std::distance(kDriverExtensionNames, it)] = true;
        }
        else
        {
            epiLogWarn("Unrecognized Vulkan instance extension=`{}`!", extension.extensionName);
        }
    }
}

EPI_NAMESPACE_END()