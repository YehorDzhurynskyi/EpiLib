#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

namespace
{

EPI_NAMESPACE_USING()

const epiChar* ExtensionNameOf(gfxPhysicalDeviceExtension extension)
{
    // TODO: check whether single bit provided
    static constexpr const epiChar* kNames[]
    {
        "VK_KHR_swapchain"
    };

    static_assert(epiArrLen(kNames) == epiBitCount(gfxPhysicalDeviceExtension_ALL));

    const epiU32 at = epiBitPositionOf(extension);
    epiAssert(at < epiArrLen(kNames));

    return kNames[at];
}

}

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxDeviceImplVK::gfxDeviceImplVK(const gfxPhysicalDeviceImplVK& physicalDevice, gfxQueueType queueTypeMask, gfxPhysicalDeviceExtension extensionMask, epiBool presentSupportRequired)
    : m_PhysicalDevice{physicalDevice}
{
    epiAssert(m_PhysicalDevice.IsQueueTypeSupported(queueTypeMask));
    epiAssert(m_PhysicalDevice.IsExtensionsSupported(extensionMask));
    epiAssert(!presentSupportRequired || m_PhysicalDevice.IsPresentSupported());

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    epiU32 queueTypeMaskLeft = queueTypeMask;
    epiBool presentSupportRequiredLeft = presentSupportRequired;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::vector<std::vector<epiFloat>> queuePrioritiesVec;
    for (const auto& queueFamily : m_PhysicalDevice.GetQueueFamilies())
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
        }

        if (availableQueueTypesOnFamily == 0)
        {
            continue;
        }

        if (presentSupportRequiredLeft && queueFamily->IsPresentSupported())
        {
            presentSupportRequiredLeft = false;
        }

        // TODO: prioritize via arguments
        epiFloat priority = 1.0f;
        queuePriorities.push_back(priority);

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.queueFamilyIndex = static_cast<gfxQueueFamilyImplVK*>(queueFamily)->GetIndex();
        queueCreateInfo.pQueuePriorities = queuePriorities.data();

        queueCreateInfos.push_back(queueCreateInfo);
    }

    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = queueCreateInfos.size();

    epiAssert(queueTypeMaskLeft == 0);
    epiAssert(presentSupportRequiredLeft == false);

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

    const VkResult resultCreateDevice = vkCreateDevice(m_PhysicalDevice.GetVkPhysicalDevice(), &createInfo, nullptr, &m_VkDevice);
    epiAssert(resultCreateDevice == VK_SUCCESS);

    const epiPtrArray<gfxQueueFamilyImpl>& queueFamilies = m_PhysicalDevice.GetQueueFamilies();
    for (const auto& queueInfo : queueCreateInfos)
    {
        const gfxQueueFamilyImplVK* queueFamily = static_cast<const gfxQueueFamilyImplVK*>(queueFamilies[queueInfo.queueFamilyIndex]);
        for (epiU32 queueIndex = 0; queueIndex < queueInfo.queueCount; ++queueIndex)
        {
            m_Queues.push_back(new gfxQueueImplVK(*this, *queueFamily, queueIndex));
        }
    }
}

gfxDeviceImplVK::~gfxDeviceImplVK()
{
    if (m_VkDevice != VK_NULL_HANDLE)
    {
        vkDestroyDevice(m_VkDevice, nullptr);
    }
}

gfxQueueImpl* gfxDeviceImplVK::GetQueue(gfxQueueType queueTypeMask, epiBool presentSupportRequired) const
{
    auto it = std::find_if(m_Queues.begin(), m_Queues.end(), [queueTypeMask, presentSupportRequired](const gfxQueueImpl* queue)
    {
        return queue->IsQueueTypeSupported(queueTypeMask) && (!presentSupportRequired || queue->IsPresentSupported());
    });

    return it != m_Queues.end() ? *it : nullptr;
}

VkDevice gfxDeviceImplVK::GetVkDevice() const
{
    return m_VkDevice;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
