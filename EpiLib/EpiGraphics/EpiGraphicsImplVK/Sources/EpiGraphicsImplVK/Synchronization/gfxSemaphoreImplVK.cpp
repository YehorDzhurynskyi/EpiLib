#include "EpiGraphicsImplVK/Synchronization/gfxSemaphoreImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxSemaphoreImplVK::gfxSemaphoreImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxSemaphoreImplVK::~gfxSemaphoreImplVK()
{
    vkDestroySemaphore(m_VkDevice, m_VkSemaphore, nullptr);
}

epiBool gfxSemaphoreImplVK::Init(const gfxSemaphoreCreateInfo& info)
{
    VkSemaphoreCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    createInfo.flags = gfxSemaphoreCreateMaskTo(info.GetCreateMask());

    if (const VkResult result = vkCreateSemaphore(m_VkDevice, &createInfo, nullptr, &m_VkSemaphore); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateSemaphore!");
        return false;
    }

    return true;
}

epiBool gfxSemaphoreImplVK::Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout)
{
    // TODO: should be called on timeline semaphores only

    const epiBool semaphoresAreValid = std::all_of(info.GetSemaphores().begin(),
                                                   info.GetSemaphores().end(),
                                                   [](const gfxSemaphore& semaphore)
    {
        return semaphore.HasImpl();
    });

    if (!semaphoresAreValid)
    {
        epiLogError("Failed to Wait on Semaphore! Some of the provided semaphore has no implementation!");
        return false;
    }

    std::vector<VkSemaphore> semaphores;
    semaphores.reserve(info.GetSemaphores().Size());

    std::transform(info.GetSemaphores().begin(),
                   info.GetSemaphores().end(),
                   std::back_inserter(semaphores),
                   [](const gfxSemaphore& semaphore)
    {
        const std::shared_ptr<gfxSemaphoreImplVK> semaphoreImpl =  ImplOf<gfxSemaphoreImplVK>(semaphore);
        epiAssert(semaphoreImpl != nullptr);

        return semaphoreImpl->GetVkSemaphore();
    });

    VkSemaphoreWaitInfo waitInfo{};
    waitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
    waitInfo.flags = gfxSemaphoreWaitMaskTo(info.GetWaitMask());
    waitInfo.semaphoreCount = semaphores.size();
    waitInfo.pSemaphores = semaphores.data();
    waitInfo.pValues = info.GetValues().data();

    if (const VkResult result = vkWaitSemaphores(m_VkDevice, &waitInfo, timeout); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkWaitSemaphores!");
        return false;
    }

    return true;
}

VkSemaphore gfxSemaphoreImplVK::GetVkSemaphore() const
{
    return m_VkSemaphore;
}

EPI_NAMESPACE_END()