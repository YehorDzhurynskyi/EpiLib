#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxBindable.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

// TODO: make an interface in epi
class gfxBindable : public Object
{
EPI_GENREGION_BEGIN(gfxBindable)
public:
    EPI_GENHIDDEN_gfxBindable()

    constexpr static MetaTypeID TypeID{0x92696af8};

    enum gfxBindable_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxBindable)

public:
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
};

template<typename T>
class gfxBindableGuard final
{
    static_assert(std::is_base_of_v<gfxBindable, T>);
public:
    gfxBindableGuard(const gfxBindableGuard&) = delete;
    gfxBindableGuard& operator=(const gfxBindableGuard&) = delete;
    gfxBindableGuard(gfxBindableGuard&&) = delete;;
    gfxBindableGuard& operator=(gfxBindableGuard&&) = delete;

    gfxBindableGuard(gfxBindable& bindable)
        : m_Bindable(bindable)
    {
        m_Bindable.Bind();
    }

    ~gfxBindableGuard()
    {
        m_Bindable.UnBind();
    }

private:
    gfxBindable& m_Bindable;
};

EPI_NAMESPACE_END()
