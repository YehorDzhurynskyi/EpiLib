#include "EpiGraphicsImplVK/gfxImageImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxQueueFamilyImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxImageImplVK::gfxImageImplVK(const gfxDevice& device)
    : gfxImage::Impl{device}
{
}

gfxImageImplVK::~gfxImageImplVK()
{
    const std::shared_ptr<gfxDeviceImplVK> deviceImpl = ImplOf<gfxDeviceImplVK>(m_Device);

    vkDestroyImage(deviceImpl->GetVkDevice(), m_VkImage, nullptr);
}

epiBool gfxImageImplVK::Init(const gfxImageCreateInfo& info)
{
    VkImageCreateInfo imageCreateInfo{};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.flags = gfxImageCreateMaskTo(info.GetCreateMask());
    imageCreateInfo.imageType = gfxImageTypeTo(info.GetType());
    imageCreateInfo.format = gfxFormatTo(info.GetFormat());
    imageCreateInfo.extent.width = info.GetExtent().x;
    imageCreateInfo.extent.height = info.GetExtent().y;
    imageCreateInfo.extent.depth = info.GetExtent().z;
    imageCreateInfo.mipLevels = info.GetMipLevels();
    imageCreateInfo.arrayLayers = info.GetArrayLayers();
    imageCreateInfo.samples = gfxSampleCountMaskTo(info.GetSampleCount());
    imageCreateInfo.tiling = gfxImageTilingTo(info.GetTiling());
    imageCreateInfo.usage = gfxImageUsageMaskTo(info.GetUsageMask());
    imageCreateInfo.sharingMode = gfxSharingModeTo(info.GetSharingMode());
    imageCreateInfo.initialLayout = gfxImageLayoutTo(info.GetInitialLayout());

    std::vector<epiU32> queueFamilyIndices;
    if (info.GetSharingMode() == gfxSharingMode::Concurrent)
    {
        queueFamilyIndices.reserve(info.GetQueueFamilies().Size());

        std::transform(info.GetQueueFamilies().begin(),
                       info.GetQueueFamilies().end(),
                       std::back_inserter(queueFamilyIndices),
                       [](const gfxQueueFamily& family)
        {
            const std::shared_ptr<gfxQueueFamilyImplVK> familyImpl = ImplOf<gfxQueueFamilyImplVK>(family);

            return familyImpl->GetIndex();
        });

        imageCreateInfo.queueFamilyIndexCount = queueFamilyIndices.size();
        imageCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
    }

    const std::shared_ptr<gfxDeviceImplVK> deviceImpl = ImplOf<gfxDeviceImplVK>(m_Device);
    if (const VkResult result = vkCreateImage(deviceImpl->GetVkDevice(), &imageCreateInfo, nullptr, &m_VkImage); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateImage!");
        return false;
    }

    return true;
}

epiBool gfxImageImplVK::Init(VkImage image)
{
    m_VkImage = image;

    return true;
}

VkImage gfxImageImplVK::GetVkImage() const
{
    return m_VkImage;
}

gfxImageImplVKSwapChain::gfxImageImplVKSwapChain(const gfxDevice& device, VkImage image)
    : gfxImage::Impl{device}
    , m_VkImage{image}
{
}

VkImage gfxImageImplVKSwapChain::GetVkImage() const
{
    return m_VkImage;
}

EPI_NAMESPACE_END()
