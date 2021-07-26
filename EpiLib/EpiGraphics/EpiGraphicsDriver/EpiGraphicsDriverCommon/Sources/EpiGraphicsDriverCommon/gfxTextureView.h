#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTextureView.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxTexture.h"

EPI_NAMESPACE_BEGIN()

class gfxTextureViewCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxTextureViewCreateInfo)

EPI_GENHIDDEN_gfxTextureViewCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xf520ccaf};

    enum gfxTextureViewCreateInfo_PIDs
    {
        PID_Image = 0x4fc2b5b,
        PID_ViewType = 0xf626a923,
        PID_Format = 0xd91677e9,
        PID_ComponentSwizzleMappingR = 0xf2df524c,
        PID_ComponentSwizzleMappingG = 0x9f02b6a7,
        PID_ComponentSwizzleMappingB = 0xef684228,
        PID_ComponentSwizzleMappingA = 0x76611392,
        PID_SubresourceRange = 0x5a75fb0e,
        PID_COUNT = 8
    };

protected:
    gfxTexture m_Image{};
    gfxTextureViewType m_ViewType{};
    gfxFormat m_Format{gfxFormat::UNDEFINED};
    gfxComponentSwizzle m_ComponentSwizzleMappingR{gfxComponentSwizzle::Identity};
    gfxComponentSwizzle m_ComponentSwizzleMappingG{gfxComponentSwizzle::Identity};
    gfxComponentSwizzle m_ComponentSwizzleMappingB{gfxComponentSwizzle::Identity};
    gfxComponentSwizzle m_ComponentSwizzleMappingA{gfxComponentSwizzle::Identity};
    gfxImageSubresourceRange m_SubresourceRange{};

EPI_GENREGION_END(gfxTextureViewCreateInfo)
};

class gfxTextureView : public Object
{
EPI_GENREGION_BEGIN(gfxTextureView)

EPI_GENHIDDEN_gfxTextureView()

public:
    constexpr static epiMetaTypeID TypeID{0xfed04145};

    enum gfxTextureView_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxTextureView)

public:
    class Impl;

public:
    gfxTextureView() = default;
    explicit gfxTextureView(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
