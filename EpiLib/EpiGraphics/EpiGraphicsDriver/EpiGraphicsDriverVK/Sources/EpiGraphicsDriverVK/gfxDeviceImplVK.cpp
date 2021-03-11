#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

#include "EpiGraphicsDriverCommon/gfxSurface.h"

#include <vulkan/vulkan.hpp>

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

epiBool gfxDeviceImplVK::Init(const gfxPhysicalDeviceImplVK& physicalDevice,
                              gfxQueueDescriptorList& queueDescriptorList,
                              gfxPhysicalDeviceExtension extensionMask)
{

    epiBool isSuitable = std::all_of(queueDescriptorList.begin(),
                                     queueDescriptorList.end(),
                                     [&physicalDevice](const gfxQueueDescriptor& queueDescriptor)
    {
        return physicalDevice.IsQueueTypeSupported(queueDescriptor.GetType());
    });
    isSuitable = isSuitable && physicalDevice.IsExtensionsSupported(extensionMask);

    if (!isSuitable)
    {
        return false;
    }

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    struct gfxQueueCreateInfo
    {
        gfxQueueCreateInfo(gfxQueueDescriptor& desc, const gfxQueueFamilyImplVK& queueFamily)
            : Desc{desc}
            , QueueFamily{queueFamily} {}

        gfxQueueDescriptor& Desc;
        const gfxQueueFamilyImplVK& QueueFamily;
    };

    std::vector<gfxQueueCreateInfo> queueDescCreateInfos;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (auto& queueDescriptor : queueDescriptorList)
    {
        epiAssert(!queueDescriptor.IsResolved());

        for (const gfxQueueFamilyImplVK& queueFamily : physicalDevice.GetQueueFamilies())
        {
            if (queueFamily.GetQueueCount() < queueDescriptor.GetDesiredQueueCount() ||
               !queueFamily.IsQueueTypeSupported(queueDescriptor.GetType()))
            {
                continue;
            }

            if (queueDescriptor.IsPresentRequired())
            {
                const gfxSurfaceImpl* surfaceVk = queueDescriptor.GetPresentSurface();
                epiAssert(surfaceVk != nullptr);

                if (!physicalDevice.IsPresentSupported(*surfaceVk, queueFamily))
                {
                    continue;
                }
            }

            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueCount = queueDescriptor.GetDesiredQueueCount();
            queueCreateInfo.queueFamilyIndex = queueFamily.GetIndex();
            queueCreateInfo.pQueuePriorities = queueDescriptor.GetPriorities().data();

            queueCreateInfos.push_back(queueCreateInfo);

            queueDescCreateInfos.emplace_back(queueDescriptor, queueFamily);

            break;
        }
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
    if (resultCreateDevice != VK_SUCCESS)
    {
        return false;
    }

    for (gfxQueueCreateInfo& queueDescCreateInfo : queueDescCreateInfos)
    {
        for (epiU32 queueIndex = 0; queueIndex < queueDescCreateInfo.Desc.GetDesiredQueueCount(); ++queueIndex)
        {
            gfxQueue queue(new gfxQueueImplVK(*this, queueDescCreateInfo.QueueFamily, queueIndex));
            queueDescCreateInfo.Desc.TryResolveQueue(std::move(queue));
        }
    }

    const epiBool allQueueDescriptorsResolved = std::all_of(queueDescriptorList.begin(),
                                                            queueDescriptorList.end(),
                                                            [](const gfxQueueDescriptor& desc)
    {
        return desc.IsResolved();
    });

    if (!allQueueDescriptorsResolved)
    {
        return false;
    }

    return true;
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
