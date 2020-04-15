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

template<typename... T>
class gfxBindableScoped final
{
public:
    gfxBindableScoped(const gfxBindableScoped&) = delete;
    gfxBindableScoped& operator=(const gfxBindableScoped&) = delete;
    gfxBindableScoped(gfxBindableScoped&&) = delete;
    gfxBindableScoped& operator=(gfxBindableScoped&&) = delete;

public:
    explicit gfxBindableScoped(T&... t)
        : m_Bindables(std::tie(t...))
    {
        std::apply([](T&... t)
        {
            char i[] = { (t.Bind(), 0)... };
            (void)i;
        }, m_Bindables);
    }

    ~gfxBindableScoped()
    {
        std::apply([](T&... t)
        {
            char i[] = { (t.UnBind(), 0)... };
            (void)i;
        }, m_Bindables);
    }

private:
    std::tuple<T&...> m_Bindables;
};

EPI_NAMESPACE_END()
