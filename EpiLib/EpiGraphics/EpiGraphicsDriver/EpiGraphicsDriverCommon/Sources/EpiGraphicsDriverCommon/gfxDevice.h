#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxQueue.h"
#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxPipeline.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxTexture.h"
#include "EpiGraphicsDriverCommon/gfxTextureView.h"
#include "EpiGraphicsDriverCommon/gfxCommandPool.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDeviceImpl;

} // namespace internalgfx

class gfxDevice : public Object
{
EPI_GENREGION_BEGIN(gfxDevice)

EPI_GENHIDDEN_gfxDevice()

public:
    constexpr static epiMetaTypeID TypeID{0xa849dda8};

    enum gfxDevice_PIDs
    {
        PID_QueueFamilies = 0x459d6c2c,
        PID_COUNT = 1
    };

protected:
    epiArray<gfxQueueFamily> m_QueueFamilies{};

EPI_GENREGION_END(gfxDevice)

public:
    gfxDevice() = default;
    explicit gfxDevice(const std::shared_ptr<internalgfx::gfxDeviceImpl>& impl);

    epiBool IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const;
    epiBool IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const;

    std::optional<gfxSwapChain> CreateSwapChain(const gfxSwapChainCreateInfo& info) const;
    std::optional<gfxRenderPass> CreateRenderPass(const gfxRenderPassCreateInfo& info) const;
    std::optional<gfxRenderPass> CreateRenderPassFromSchema(const gfxRenderPassSchema& schema) const;
    std::optional<gfxPipelineGraphics> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info, const gfxRenderPass& renderPass) const;
    std::optional<gfxShader> CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") const;
    std::optional<gfxShader> CreateShaderFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint = "main") const;
    std::optional<gfxShaderProgram> CreateShaderProgram(const gfxShaderProgramCreateInfo& info) const;
    std::optional<gfxFrameBuffer> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info) const;
    std::optional<gfxTexture> CreateTexture(const gfxTextureCreateInfo& info) const;
    std::optional<gfxTextureView> CreateTextureView(const gfxTextureViewCreateInfo& info) const;
    std::optional<gfxCommandPool> CreateCommandPool(const gfxCommandPoolCreateInfo& info) const;

protected:
    epiPimpl<internalgfx::gfxDeviceImpl> m_Impl;
};

EPI_NAMESPACE_END()
