#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxSampler.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxSamplerCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxSamplerCreateInfo)

EPI_GENHIDDEN_gfxSamplerCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x247d82b7};

    enum gfxSamplerCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_MagFilter = 0x522ed938,
        PID_MinFilter = 0x1453875e,
        PID_AddressModeU = 0x7109aedd,
        PID_AddressModeV = 0xe800ff67,
        PID_AddressModeW = 0x9f07cff1,
        PID_MipmapMode = 0x12f96495,
        PID_MipmapLODBias = 0x6e7a7bce,
        PID_IsAnisotropyEnabled = 0xc235f51e,
        PID_AnisotropyMax = 0x4e138ac,
        PID_IsCompareEnabled = 0x2e489654,
        PID_CompareOp = 0xe502a448,
        PID_MinLOD = 0x320f8ffa,
        PID_MaxLOD = 0x770dcc78,
        PID_BorderColor = 0xb16a5455,
        PID_IsUnnormalizedCoordinates = 0xe23f3654,
        PID_COUNT = 16
    };

protected:
    gfxSamplerCreateMask m_CreateMask{};
    gfxSamplerFilterMode m_MagFilter{};
    gfxSamplerFilterMode m_MinFilter{};
    gfxSamplerAddressMode m_AddressModeU{};
    gfxSamplerAddressMode m_AddressModeV{};
    gfxSamplerAddressMode m_AddressModeW{};
    gfxSamplerMipmapMode m_MipmapMode{};
    epiFloat m_MipmapLODBias{0.0f};
    epiBool m_IsAnisotropyEnabled{false};
    epiFloat m_AnisotropyMax{0.0f};
    epiBool m_IsCompareEnabled{false};
    gfxCompareOp m_CompareOp{};
    epiFloat m_MinLOD{0.0f};
    epiFloat m_MaxLOD{0.0f};
    gfxSamplerBorderColor m_BorderColor{};
    epiBool m_IsUnnormalizedCoordinates{false};

EPI_GENREGION_END(gfxSamplerCreateInfo)
};

class gfxSampler : public Object
{
EPI_GENREGION_BEGIN(gfxSampler)

EPI_GENHIDDEN_gfxSampler()

public:
    constexpr static epiMetaTypeID TypeID{0xbc398477};

    enum gfxSampler_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxSampler)

public:
    class Impl;

public:
    gfxSampler() = default;
    explicit gfxSampler(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
