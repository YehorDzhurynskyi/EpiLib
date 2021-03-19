#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxQueue.h"
#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxPipeline.h"

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
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDevice)

public:
    friend class gfxSurface;

public:
    gfxDevice() = default;
    explicit gfxDevice(internalgfx::gfxDeviceImpl* impl);
    gfxDevice(const gfxDevice& rhs) = delete;
    gfxDevice& operator=(const gfxDevice& rhs) = delete;
    gfxDevice(gfxDevice&& rhs);
    gfxDevice& operator=(gfxDevice&& rhs);
    ~gfxDevice();

    std::optional<gfxRenderPass> CreateRenderPass(const gfxRenderPassCreateInfo& info) const;
    std::optional<gfxPipeline> CreatePipeline(const gfxPipelineCreateInfo& info) const;
    std::optional<gfxShader> CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") const;
    std::optional<gfxShaderProgram> CreateShaderProgram(const gfxShaderProgramCreateInfo& info) const;

protected:
    internalgfx::gfxDeviceImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
