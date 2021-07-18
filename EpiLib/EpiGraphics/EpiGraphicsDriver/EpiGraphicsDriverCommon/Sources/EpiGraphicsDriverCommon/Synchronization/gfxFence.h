#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/Synchronization/gfxFence.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxFenceImpl;

} // namespace internalgfx

class gfxFenceCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxFenceCreateInfo)

EPI_GENHIDDEN_gfxFenceCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xe6f3956f};

    enum gfxFenceCreateInfo_PIDs
    {
        PID_CreateMask = 0xc2e0d2f0,
        PID_COUNT = 1
    };

protected:
    gfxFenceCreateMask m_CreateMask{};

EPI_GENREGION_END(gfxFenceCreateInfo)
};

class gfxFence : public Object
{
EPI_GENREGION_BEGIN(gfxFence)

EPI_GENHIDDEN_gfxFence()

public:
    constexpr static epiMetaTypeID TypeID{0x5a1161f9};

    enum gfxFence_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxFence)

public:
    class Impl;

public:
    gfxFence() = default;
    explicit gfxFence(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool Reset();
    epiBool Wait(epiU64 timeout = std::numeric_limits<epiU64>::max());

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
