#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxTextureView.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxTexture.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxTextureViewImpl;

} // internalgfx

class gfxTextureViewCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxTextureViewCreateInfo)

EPI_GENHIDDEN_gfxTextureViewCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xf520ccaf};

    enum gfxTextureViewCreateInfo_PIDs
    {
        PID_Texture = 0x4ddb34ee,
        PID_ViewType = 0xf626a923,
        PID_Format = 0xd91677e9,
        PID_COUNT = 3
    };

protected:
    gfxTexture* m_Texture{nullptr};
    gfxTextureViewType m_ViewType{gfxTextureViewType::None};
    gfxFormat m_Format{gfxFormat::UNDEFINED};

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
    gfxTextureView() = default;
    explicit gfxTextureView(internalgfx::gfxTextureViewImpl* impl);
    gfxTextureView(const gfxTextureView& rhs) = delete;
    gfxTextureView& operator=(const gfxTextureView& rhs) = delete;
    gfxTextureView(gfxTextureView&& rhs);
    gfxTextureView& operator=(gfxTextureView&& rhs);
    ~gfxTextureView();

protected:
    internalgfx::gfxTextureViewImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
