#include "EpiGraphicsDriverVK/gfxVertexBufferImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxVertexBufferLayoutAttributeImplVK::gfxVertexBufferLayoutAttributeImplVK(gfxVertexBufferLayoutAttributeImplVK&& rhs)
{
    m_Location = rhs.m_Location;
    m_Format = rhs.m_Format;
    m_Offset = rhs.m_Offset;

    rhs.m_Location = 0;
    rhs.m_Format = gfxFormat::UNDEFINED;
    rhs.m_Offset = 0;
}

gfxVertexBufferLayoutAttributeImplVK& gfxVertexBufferLayoutAttributeImplVK::operator=(gfxVertexBufferLayoutAttributeImplVK&& rhs)
{
    m_Location = rhs.m_Location;
    m_Format = rhs.m_Format;
    m_Offset = rhs.m_Offset;

    rhs.m_Location = 0;
    rhs.m_Format = gfxFormat::UNDEFINED;
    rhs.m_Offset = 0;

    return *this;
}

epiU32 gfxVertexBufferLayoutAttributeImplVK::GetLocation() const
{
    return m_Location;
}

void gfxVertexBufferLayoutAttributeImplVK::SetLocation(epiU32 value)
{
    m_Location = value;
}

epiSize_t gfxVertexBufferLayoutAttributeImplVK::GetOffset() const
{
    return m_Offset;
}

void gfxVertexBufferLayoutAttributeImplVK::SetOffset(epiSize_t value)
{
    m_Offset = value;
}

gfxFormat gfxVertexBufferLayoutAttributeImplVK::GetFormat() const
{
    return m_Format;
}

void gfxVertexBufferLayoutAttributeImplVK::SetFormat(gfxFormat value)
{
    m_Format = value;
}

void gfxVertexBufferLayoutAttributeImplVK::Apply() const
{
    VkVertexInputAttributeDescription attrDesc{};
    attrDesc.binding = 0;
    attrDesc.location = GetLocation();
    attrDesc.offset = GetOffset();
    attrDesc.format = gfxFormatTo(GetFormat());
}

void gfxVertexBufferLayoutImplVK::Apply() const
{
    VkVertexInputBindingDescription bindingDesc{};
    bindingDesc.binding = 0;
    bindingDesc.stride = GetStride();
    bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    for (auto& attr : m_Attributes)
    {
        attr.Apply();
    }
}

void gfxVertexBufferLayoutImplVK::Add(gfxVertexBufferLayoutAttributeImpl&& attr)
{
    // TODO: implement
}

#if 0
epiBool gfxVertexBufferImplVK::Create(const epiByte* initData, epiSize_t capacity, gfxVertexBufferUsage usage, const gfxVertexBufferLayoutImpl& layout)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = capacity;
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (const VkResult result = vkCreateBuffer(m_VkDevice, &bufferInfo, nullptr, &m_VkBuffer); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateBuffer!");
        return false;
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_VkDevice, m_VkBuffer, &memRequirements);

#if 0
    GLenum glUsage;
    switch (usage)
    {
    case gfxVertexBufferUsage::StaticRead: glUsage = GL_STATIC_READ; break;
    case gfxVertexBufferUsage::StaticDraw: glUsage = GL_STATIC_DRAW; break;
    case gfxVertexBufferUsage::DynamicRead:  glUsage = GL_DYNAMIC_READ; break;
    case gfxVertexBufferUsage::DynamicDraw: glUsage = GL_DYNAMIC_DRAW; break;
    case gfxVertexBufferUsage::StreamRead:  glUsage = GL_STREAM_READ; break;
    case gfxVertexBufferUsage::StreamDraw: glUsage = GL_STREAM_DRAW; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    glGenBuffers(1, &m_ID);
    if (m_ID == 0)
    {
        return;
    }

    Bind();
    glBufferData(GL_ARRAY_BUFFER, capacity, initData, glUsage);
    m_Capacity = capacity;

    layout.Apply();
#endif
}

void gfxVertexBufferImplVK::Destroy()
{
    if (m_VkDevice != nullptr && m_VkBuffer != nullptr)
    {
        vkDestroyBuffer(m_VkDevice, m_VkBuffer, nullptr);
    }

    m_VkBuffer = nullptr;
    m_Capacity = 0;
}

epiBool gfxVertexBufferImplVK::GetIsCreated() const
{
    return m_VkBuffer != nullptr;
}

epiSize_t gfxVertexBufferImplVK::GetCapacity() const
{
    return m_Capacity;
}

void gfxVertexBufferImplVK::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void gfxVertexBufferImplVK::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

epiByte* gfxVertexBufferImplVK::Map(gfxVertexBufferMapAccess access)
{
    GLenum glAccess;
    switch (access)
    {
    case gfxVertexBufferMapAccess::Read: glAccess = GL_READ_ONLY; break;
    case gfxVertexBufferMapAccess::Write: glAccess = GL_WRITE_ONLY; break;
    case gfxVertexBufferMapAccess::ReadWrite: glAccess = GL_READ_WRITE; break;
    default: epiAssert(false, "Unhandled case"); return nullptr;
    }

    return reinterpret_cast<epiByte*>(glMapBuffer(GL_ARRAY_BUFFER, glAccess));
}

epiBool gfxVertexBufferImplVK::UnMap()
{
    return glUnmapBuffer(GL_ARRAY_BUFFER);
}
#endif

} // namespace internalgfx

EPI_NAMESPACE_END()
