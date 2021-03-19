#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTexture.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxTextureImpl;

} // namespace internalgfx

class gfxTextureCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxTextureCreateInfo)

EPI_GENHIDDEN_gfxTextureCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x724865ad};

    enum gfxTextureCreateInfo_PIDs
    {
        PID_Type = 0x2cecf817,
        PID_Format = 0xd91677e9,
        PID_Extent = 0x21a25c7e,
        PID_MipLevels = 0xc35c5bc9,
        PID_ArrayLayers = 0x65ffb52d,
        PID_SampleCount = 0x2397b6e7,
        PID_Usage = 0x112a7174,
        PID_InitialLayout = 0xcf791b4,
        PID_COUNT = 8
    };

protected:
    gfxTextureType m_Type{gfxTextureType::None};
    gfxFormat m_Format{gfxFormat::UNDEFINED};
    epiVec3u m_Extent{};
    epiU32 m_MipLevels{0};
    epiU32 m_ArrayLayers{0};
    gfxSampleCount m_SampleCount{gfxSampleCount::Sample1};
    gfxImageUsage m_Usage{};
    gfxImageLayout m_InitialLayout{gfxImageLayout::Undefined};

EPI_GENREGION_END(gfxTextureCreateInfo)
};

class gfxTexture : public Object
{
EPI_GENREGION_BEGIN(gfxTexture)

EPI_GENHIDDEN_gfxTexture()

public:
    constexpr static epiMetaTypeID TypeID{0x50caeee4};

    enum gfxTexture_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTexture)

public:
    friend class gfxDevice;

public:
    gfxTexture() = default;
    explicit gfxTexture(internalgfx::gfxTextureImpl* impl);
    gfxTexture(const gfxTexture& rhs) = delete;
    gfxTexture& operator=(const gfxTexture& rhs) = delete;
    gfxTexture(gfxTexture&& rhs);
    gfxTexture& operator=(gfxTexture&& rhs);
    ~gfxTexture();

protected:
    internalgfx::gfxTextureImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
