#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"
#include "EpiGraphicsDriverVK/gfxSwapChainImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"
#include "EpiGraphicsDriverVK/gfxShaderProgramImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureViewImplVK.h"
#include "EpiGraphicsDriverVK/gfxCommandPoolImplVK.h"

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

    struct gfxQueueDescriptorBinding
    {
        gfxQueueDescriptorBinding(gfxQueueDescriptor& desc, std::unique_ptr<gfxQueueFamilyImplVK>&& queueFamily)
            : Desc{desc}
            , QueueFamily{std::move(queueFamily)}
        {
        }

        gfxQueueDescriptor& Desc;
        std::unique_ptr<gfxQueueFamilyImplVK> QueueFamily;
    };

    std::vector<gfxQueueDescriptorBinding> queueDescriptorBindings;
    queueDescriptorBindings.reserve(queueDescriptorList.GetSize());

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (gfxQueueDescriptor& queueDescriptor : queueDescriptorList)
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

                if (!surfaceVk->IsPresentSupportedFor(physicalDevice, queueFamily))
                {
                    continue;
                }
            }

            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueCount = queueDescriptor.GetDesiredQueueCount();
            queueCreateInfo.queueFamilyIndex = queueFamily.GetIndex();
            queueCreateInfo.pQueuePriorities = queueDescriptor.GetPriorities().data();

            std::unique_ptr<gfxQueueFamilyImplVK> family = std::make_unique<gfxQueueFamilyImplVK>(queueFamily.GetIndex(),
                                                                                                  queueFamily.GetQueueCount(),
                                                                                                  queueFamily.GetQueueTypeSupported());
            queueDescriptorBindings.emplace_back(queueDescriptor, std::move(family));

            queueCreateInfos.push_back(queueCreateInfo);

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

    for (gfxQueueDescriptorBinding& queueDescBinding : queueDescriptorBindings)
    {
        for (epiU32 queueIndex = 0; queueIndex < queueDescBinding.Desc.GetDesiredQueueCount(); ++queueIndex)
        {
            gfxQueue queue(new gfxQueueImplVK(*this, *queueDescBinding.QueueFamily, queueIndex));
            queueDescBinding.Desc.TryResolveQueue(std::move(queue));
        }

        queueDescBinding.Desc.SetQueueFamily(new gfxQueueFamily(queueDescBinding.QueueFamily.release())); // TODO: handle `new`
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

std::unique_ptr<gfxSwapChainImpl> gfxDeviceImplVK::CreateSwapChain(const gfxSwapChainCreateInfo& info,
                                                                   const gfxSurfaceImpl& surfaceImpl,
                                                                   const gfxRenderPassImpl& renderPassImpl,
                                                                   const gfxQueueFamilyImpl& queueFamilyImpl) const
{
    std::unique_ptr<gfxSwapChainImplVK> impl = std::make_unique<gfxSwapChainImplVK>(*this);
    if (!impl->Init(info, surfaceImpl, renderPassImpl, queueFamilyImpl))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxRenderPassImpl> gfxDeviceImplVK::CreateRenderPass(const gfxRenderPassCreateInfo& info) const
{
    std::unique_ptr<gfxRenderPassImplVK> impl = std::make_unique<gfxRenderPassImplVK>(m_VkDevice);
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxPipelineImpl> gfxDeviceImplVK::CreatePipeline(const gfxPipelineCreateInfo& info,
                                                                 const gfxShaderProgramImpl& shaderProgramImpl,
                                                                 const gfxRenderPassImpl& renderPassImpl) const
{
    std::unique_ptr<gfxPipelineImplVK> impl = std::make_unique<gfxPipelineImplVK>(*this);
    if (!impl->Init(info, shaderProgramImpl, renderPassImpl))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxShaderImpl> gfxDeviceImplVK::CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint) const
{
    std::unique_ptr<gfxShaderImplVK> impl = std::make_unique<gfxShaderImplVK>(m_VkDevice);
    if (!impl->InitFromSource(source, type, entryPoint))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxShaderProgramImpl> gfxDeviceImplVK::CreateShaderProgram(const gfxShaderProgramCreateInfoImpl& info) const
{
    std::unique_ptr<gfxShaderProgramImplVK> impl = std::make_unique<gfxShaderProgramImplVK>();
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxFrameBufferImpl> gfxDeviceImplVK::CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl) const
{
    std::unique_ptr<gfxFrameBufferImplVK> impl = std::make_unique<gfxFrameBufferImplVK>(m_VkDevice);
    if (!impl->Init(info, renderPassImpl))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxTextureImpl> gfxDeviceImplVK::CreateTexture(const gfxTextureCreateInfo& info) const
{
    std::unique_ptr<gfxTextureImplVKOwner> impl = std::make_unique<gfxTextureImplVKOwner>(m_VkDevice);
    if (!impl->Init(info))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxTextureViewImpl> gfxDeviceImplVK::CreateTextureView(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl) const
{
    std::unique_ptr<gfxTextureViewImplVK> impl = std::make_unique<gfxTextureViewImplVK>(m_VkDevice);
    if (!impl->Init(info, textureImpl))
    {
        impl.reset();
    }

    return impl;
}

std::unique_ptr<gfxCommandPoolImpl> gfxDeviceImplVK::CreateCommandPool(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl) const
{
    std::unique_ptr<gfxCommandPoolImplVK> impl = std::make_unique<gfxCommandPoolImplVK>(m_VkDevice);
    if (!impl->Init(info, queueFamilyImpl))
    {
        impl.reset();
    }

    return impl;
}

VkDevice gfxDeviceImplVK::GetVkDevice() const
{
    return m_VkDevice;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
