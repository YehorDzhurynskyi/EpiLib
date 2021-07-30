#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxImageView.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxImage.h"

EPI_NAMESPACE_BEGIN()

class gfxImageViewCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxImageViewCreateInfo)

EPI_GENHIDDEN_gfxImageViewCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x2a8efe4c};

    enum gfxImageViewCreateInfo_PIDs
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
    gfxImage m_Image{};
    gfxImageViewType m_ViewType{};
    gfxFormat m_Format{gfxFormat::UNDEFINED};
    gfxComponentSwizzle m_ComponentSwizzleMappingR{gfxComponentSwizzle::Identity};
    gfxComponentSwizzle m_ComponentSwizzleMappingG{gfxComponentSwizzle::Identity};
    gfxComponentSwizzle m_ComponentSwizzleMappingB{gfxComponentSwizzle::Identity};
    gfxComponentSwizzle m_ComponentSwizzleMappingA{gfxComponentSwizzle::Identity};
    gfxImageSubresourceRange m_SubresourceRange{};

EPI_GENREGION_END(gfxImageViewCreateInfo)
};

class gfxImageView : public Object
{
EPI_GENREGION_BEGIN(gfxImageView)

EPI_GENHIDDEN_gfxImageView()

public:
    constexpr static epiMetaTypeID TypeID{0x555681eb};

    enum gfxImageView_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxImageView)

public:
    class Impl;

public:
    gfxImageView() = default;
    explicit gfxImageView(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
