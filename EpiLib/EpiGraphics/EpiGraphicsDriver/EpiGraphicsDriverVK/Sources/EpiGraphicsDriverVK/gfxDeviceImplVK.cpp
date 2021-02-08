#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
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

gfxDeviceImplVK::gfxDeviceImplVK(const gfxPhysicalDeviceImplVK& physicalDevice, gfxQueueFamily queueFamilyMask, gfxPhysicalDeviceExtension extensionMask)
{
    epiAssert(physicalDevice.IsQueueFamilySupported(queueFamilyMask));

    gfxPhysicalDeviceImpl::QueueFamilyIndices queueFamilyIndices = physicalDevice.GetQueueFamilyIndices();

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (epiU32 bit = 1; bit < gfxQueueFamily_MAX; bit = bit << 1)
    {
        const gfxQueueFamily family = static_cast<gfxQueueFamily>(bit);
        if (family & queueFamilyMask == 0)
        {
            continue;
        }

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueCount = 1;

        // TODO: provide `queuePriority` through parameters
        switch (family)
        {
        case gfxQueueFamily_Graphics:
        {
            epiAssert(queueFamilyIndices.FamilyGraphics.has_value());
            const epiFloat queuePriority = 1.0f;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndices.FamilyGraphics.value();
            queueCreateInfo.pQueuePriorities = &queuePriority;
        } break;
        case gfxQueueFamily_Compute:
        {
            epiAssert(queueFamilyIndices.FamilyCompute.has_value());
            const epiFloat queuePriority = 0.8f;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndices.FamilyCompute.value();
            queueCreateInfo.pQueuePriorities = &queuePriority;
        } break;
        case gfxQueueFamily_Transfer:
        {
            epiAssert(queueFamilyIndices.FamilyTransfer.has_value());
            const epiFloat queuePriority = 0.7f;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndices.FamilyTransfer.value();
            queueCreateInfo.pQueuePriorities = &queuePriority;
        } break;
        case gfxQueueFamily_SparseBinding:
        {
            epiAssert(queueFamilyIndices.FamilySparseBinding.has_value());
            const epiFloat queuePriority = 0.6f;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndices.FamilySparseBinding.value();
            queueCreateInfo.pQueuePriorities = &queuePriority;
        } break;
        case gfxQueueFamily_Protected:
        {
            epiAssert(queueFamilyIndices.FamilyProtected.has_value());
            const epiFloat queuePriority = 0.5f;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndices.FamilyProtected.value();
            queueCreateInfo.pQueuePriorities = &queuePriority;
        } break;
        case gfxQueueFamily_Presentation:
        {
            epiAssert(queueFamilyIndices.FamilyPresentation.has_value());
            const epiFloat queuePriority = 1.0f;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndices.FamilyPresentation.value();
            queueCreateInfo.pQueuePriorities = &queuePriority;
        } break;
        default: epiAssert(!"Unhandled case!");
        }

        queueCreateInfos.push_back(queueCreateInfo);
    }

    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = queueCreateInfos.size();

    std::vector<const epiChar*> extensions;
    for (epiU32 bit = 1; bit < gfxPhysicalDeviceExtension_MAX; bit = bit << 1)
    {
        const gfxPhysicalDeviceExtension extension = static_cast<gfxPhysicalDeviceExtension>(bit);
        if (extension & extensionMask == 0)
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

    for (epiU32 bit = 1; bit < gfxQueueFamily_MAX; bit = bit << 1)
    {
        const gfxQueueFamily family = static_cast<gfxQueueFamily>(bit);
        if (family & queueFamilyMask == 0)
        {
            continue;
        }

        switch (family)
        {
        case gfxQueueFamily_Graphics:
        {
            epiAssert(queueFamilyIndices.FamilyGraphics.has_value());
            m_QueueGraphics = std::make_unique<gfxQueueImplVK>(*this, queueFamilyIndices.FamilyGraphics.value());
        } break;
        case gfxQueueFamily_Compute:
        {
            epiAssert(queueFamilyIndices.FamilyCompute.has_value());
            m_QueueCompute = std::make_unique<gfxQueueImplVK>(*this, queueFamilyIndices.FamilyCompute.value());
        } break;
        case gfxQueueFamily_Transfer:
        {
            epiAssert(queueFamilyIndices.FamilyTransfer.has_value());
            m_QueueCompute = std::make_unique<gfxQueueImplVK>(*this, queueFamilyIndices.FamilyTransfer.value());
        } break;
        case gfxQueueFamily_SparseBinding:
        {
            epiAssert(queueFamilyIndices.FamilySparseBinding.has_value());
            m_QueueSparseBinding = std::make_unique<gfxQueueImplVK>(*this, queueFamilyIndices.FamilySparseBinding.value());
        } break;
        case gfxQueueFamily_Protected:
        {
            epiAssert(queueFamilyIndices.FamilyProtected.has_value());
            m_QueueProtected = std::make_unique<gfxQueueImplVK>(*this, queueFamilyIndices.FamilyProtected.value());
        } break;
        case gfxQueueFamily_Presentation:
        {
            epiAssert(queueFamilyIndices.FamilyPresentation.has_value());
            m_QueuePresentation = std::make_unique<gfxQueueImplVK>(*this, queueFamilyIndices.FamilyPresentation.value());
        } break;
        default: epiAssert(!"Unhandled case!");
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

gfxQueueImpl* gfxDeviceImplVK::GetQueue(gfxQueueFamily family) const
{
    gfxQueueImplVK* queue = nullptr;

    // TODO: check whether family is only single value
    if (family & gfxQueueFamily_Graphics)
    {
        queue = m_QueueGraphics.get();
    }
    else if (family & gfxQueueFamily_Compute)
    {
        queue = m_QueueCompute.get();
    }
    else if (family & gfxQueueFamily_Transfer)
    {
        queue = m_QueueTransfer.get();
    }
    else if (family & gfxQueueFamily_SparseBinding)
    {
        queue = m_QueueSparseBinding.get();
    }
    else if (family & gfxQueueFamily_Protected)
    {
        queue = m_QueueProtected.get();
    }
    else if (family & gfxQueueFamily_Presentation)
    {
        queue = m_QueuePresentation.get();
    }

    epiAssert(queue != nullptr);

    return queue;
}

VkDevice gfxDeviceImplVK::GetVkDevice() const
{
    return m_VkDevice;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
