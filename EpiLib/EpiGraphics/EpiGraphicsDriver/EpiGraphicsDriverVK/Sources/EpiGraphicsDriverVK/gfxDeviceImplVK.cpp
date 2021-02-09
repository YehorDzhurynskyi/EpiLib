#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

namespace
{

const epiChar* ExtensionNameOf(epi::gfxPhysicalDeviceExtension extension)
{
    // TODO: check whether single bit provided
    static constexpr const epiChar* kNames[]
    {
        "VK_KHR_swapchain"
    };

    static_assert(epiArrLen(kNames) == epiBitCount(epi::gfxPhysicalDeviceExtension_ALL));

    const epiU32 at = epiBitPositionOf(extension);
    epiAssert(at < epiArrLen(kNames));

    return kNames[at];
}

}

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxDeviceImplVK::gfxDeviceImplVK(const gfxPhysicalDeviceImplVK& physicalDevice, gfxQueueType queueTypeMask, gfxPhysicalDeviceExtension extensionMask, epiBool presentSupportRequired)
{
    epiAssert(physicalDevice.IsQueueTypeSupported(queueTypeMask));

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    epiU32 queueTypeMaskLeft = queueTypeMask;
    epiBool presentSupportRequiredLeft = presentSupportRequired;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::vector<std::vector<epiFloat>> queuePrioritiesVec;
    for (const auto& queueFamily : physicalDevice.GetQueueFamilies())
    {
        epiU32 availableQueueTypesOnFamily = 0;
        std::vector<epiFloat>& queuePriorities = queuePrioritiesVec.emplace_back();
        for (epiU32 bit = 1; bit < gfxQueueType_MAX; bit = bit << 1)
        {
            const gfxQueueType type = static_cast<gfxQueueType>(bit);
            if ((type & queueTypeMaskLeft) == 0)
            {
                continue;
            }

            queueTypeMaskLeft ^= bit;

            ++availableQueueTypesOnFamily;

            // TODO: prioritize via arguments
            epiFloat priority = 0.0f;
            switch (type)
            {
            case gfxQueueType_Graphics: priority = 1.0f; break;
            case gfxQueueType_Compute: priority = 1.0f; break;
            case gfxQueueType_Transfer: priority = 0.8f; break;
            case gfxQueueType_SparseBinding: priority = 0.3f; break;
            case gfxQueueType_Protected: priority = 0.3f; break;
            default: epiAssert(!"Unhandled case!");
            }
            queuePriorities.push_back(priority);
        }

        if (availableQueueTypesOnFamily == 0)
        {
            continue;
        }

        if (presentSupportRequiredLeft && queueFamily->IsPresentSupported())
        {
            presentSupportRequiredLeft = false;
        }

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueCount = availableQueueTypesOnFamily;
        queueCreateInfo.queueFamilyIndex = static_cast<gfxQueueFamilyImplVK*>(queueFamily)->GetIndex();
        queueCreateInfo.pQueuePriorities = queuePriorities.data();

        queueCreateInfos.push_back(queueCreateInfo);
    }

    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = queueCreateInfos.size();

    std::vector<const epiChar*> extensions;
    for (epiU32 bit = 1; bit < gfxPhysicalDeviceExtension_MAX; bit = bit << 1)
    {
        const gfxPhysicalDeviceExtension extension = static_cast<gfxPhysicalDeviceExtension>(bit);
        if ((extension & extensionMask) == 0)
        {
            continue;
        }

        extensions.push_back(ExtensionNameOf(extension));
    }
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledExtensionCount = extensions.size();

    // TODO: set required features
    VkPhysicalDeviceFeatures deviceFeatures{};
    createInfo.pEnabledFeatures = &deviceFeatures;

    const VkResult resultCreateDevice = vkCreateDevice(physicalDevice.GetVkPhysicalDevice(), &createInfo, nullptr, &m_VkDevice);
    epiAssert(resultCreateDevice == VK_SUCCESS);
}

gfxDeviceImplVK::~gfxDeviceImplVK()
{
    if (m_VkDevice != VK_NULL_HANDLE)
    {
        vkDestroyDevice(m_VkDevice, nullptr);
    }
}

VkDevice gfxDeviceImplVK::GetVkDevice() const
{
    return m_VkDevice;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
