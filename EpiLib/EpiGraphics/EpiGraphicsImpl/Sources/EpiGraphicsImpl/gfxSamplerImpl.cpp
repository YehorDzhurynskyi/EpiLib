#include "EpiGraphicsDriverVK/gfxSamplerImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxSamplerImplVK::gfxSamplerImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxSamplerImplVK::~gfxSamplerImplVK()
{
    vkDestroySampler(m_VkDevice, m_VkSampler, nullptr);
}

epiBool gfxSamplerImplVK::Init(const gfxSamplerCreateInfo& info)
{
    VkSamplerCreateInfo samplerCreateInfo{};
    samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerCreateInfo.flags = gfxSamplerCreateMaskTo(info.GetCreateMask());
    samplerCreateInfo.magFilter = gfxSamplerFilterModeTo(info.GetMagFilter());
    samplerCreateInfo.minFilter = gfxSamplerFilterModeTo(info.GetMinFilter());
    samplerCreateInfo.mipmapMode = gfxSamplerMipmapModeTo(info.GetMipmapMode());
    samplerCreateInfo.addressModeU = gfxSamplerAddressModeTo(info.GetAddressModeU());
    samplerCreateInfo.addressModeV = gfxSamplerAddressModeTo(info.GetAddressModeV());
    samplerCreateInfo.addressModeW = gfxSamplerAddressModeTo(info.GetAddressModeW());
    samplerCreateInfo.mipLodBias = info.GetMipmapLODBias();;
    samplerCreateInfo.anisotropyEnable = info.GetIsAnisotropyEnabled();
    samplerCreateInfo.maxAnisotropy = info.GetAnisotropyMax();
    samplerCreateInfo.compareEnable = info.GetIsCompareEnabled();
    samplerCreateInfo.compareOp = gfxCompareOpTo(info.GetCompareOp());
    samplerCreateInfo.minLod = info.GetMinLOD();
    samplerCreateInfo.maxLod = info.GetMaxLOD();
    samplerCreateInfo.borderColor = gfxSamplerBorderColorTo(info.GetBorderColor());
    samplerCreateInfo.unnormalizedCoordinates = info.GetIsUnnormalizedCoordinates();

    if (const VkResult result = vkCreateSampler(m_VkDevice, &samplerCreateInfo, nullptr, &m_VkSampler); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateSampler!");
        return false;
    }

    return true;
}

VkSampler gfxSamplerImplVK::GetVkSampler() const
{
    return m_VkSampler;
}

EPI_NAMESPACE_END()
