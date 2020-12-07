#pragma once

#include "EpiCore/MT/JobSystem/epiIJob.h"

#include "EpiMultimedia/Image/mmImage.h"

namespace
{

template <epiSize_t N>
struct ApplyMemberFunc
{
    template <typename T, typename... ArgsF, typename... ArgsT, typename... Args>
    static void ApplyTuple(T* pObj,
                           void (T::* f)(ArgsF...),
                           const std::tuple<ArgsT...>& t,
                           Args... args)
    {
        ApplyMemberFunc<N - 1>::ApplyTuple(pObj, f, t, std::get<N - 1>(t), args...);
    }
};

template <>
struct ApplyMemberFunc<0>
{
    template <typename T, typename... ArgsF, typename... ArgsT, typename... Args>
    static void ApplyTuple(T* pObj,
                           void (T::* f)(ArgsF...),
                           const std::tuple<ArgsT...>& /* t */,
                           Args... args)
    {
        (pObj->*f)(args...);
    }
};

}

namespace epi
{

template<typename ...Args>
class mmJobImage : public epiIJob
{
public:
    using Callback = void(mmImage::*)(Args ...args);

public:
    mmJobImage(const mmImage& image, Callback&& callback, Args ...args)
        : m_Image{image.Duplicate()}
        , m_Callback{std::move(callback)}
        , m_Args{std::forward<Args>(args)...}
    {
    }

public:
    void Execute() override
    {
        ApplyMemberFunc<sizeof...(Args)>::ApplyTuple(&m_Image, m_Callback, m_Args);
    }

    const mmImage& GetImage() const { return m_Image; }
    mmImage& GetImage() { return m_Image; }

protected:
    mmImage m_Image;
    Callback m_Callback;
    std::tuple<Args...> m_Args;
};

}
