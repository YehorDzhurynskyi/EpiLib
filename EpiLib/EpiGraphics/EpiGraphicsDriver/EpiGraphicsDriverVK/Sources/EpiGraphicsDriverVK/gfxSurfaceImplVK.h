#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

class gfxDriverVK;
class gfxSurfaceImplVK : public gfxSurfaceImpl
{
public:
    gfxSurfaceImplVK(VkInstance instance);
    gfxSurfaceImplVK(const gfxSurfaceImplVK& rhs) = delete;
    gfxSurfaceImplVK& operator=(const gfxSurfaceImplVK& rhs) = delete;
    gfxSurfaceImplVK(gfxSurfaceImplVK&& rhs) = default;
    gfxSurfaceImplVK& operator=(gfxSurfaceImplVK&& rhs) = default;
    ~gfxSurfaceImplVK() override;

    VkSurfaceKHR GetVkSurface() const;

protected:
    VkInstance m_VkInstance{VK_NULL_HANDLE};
    VkSurfaceKHR m_VkSurface{VK_NULL_HANDLE};
};

EPI_NAMESPACE_END()
