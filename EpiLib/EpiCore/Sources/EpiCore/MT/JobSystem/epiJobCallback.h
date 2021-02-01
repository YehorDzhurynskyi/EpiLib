#pragma once

#include "EpiCore/MT/JobSystem/epiIJob.h"
#include "EpiCore/types.h"

namespace
{

template <typename Return, epiSize_t N>
struct ApplyMemberFunc
{
    template <typename T, typename... ArgsF, typename... ArgsT, typename... Args>
    static Return ApplyTuple(T* object,
                             Return(T::*f)(ArgsF...),
                             const std::tuple<ArgsT...>& t,
                             Args... args)
    {
        return ApplyMemberFunc<Return, N - 1>::ApplyTuple(object, f, t, std::get<N - 1>(t), args...);
    }
};

template <typename Return>
struct ApplyMemberFunc<Return, 0>
{
    template <typename T, typename... ArgsF, typename... ArgsT, typename... Args>
    static Return ApplyTuple(T* object,
                             Return (T::*f)(ArgsF...),
                             const std::tuple<ArgsT...>&,
                             Args... args)
    {
        return (object->*f)(args...);
    }
};

template <typename Return, epiSize_t N>
struct ApplyFunc
{
    template <typename... ArgsF, typename... ArgsT, typename... Args>
    static Return ApplyTuple(Return(*f)(ArgsF...),
                             const std::tuple<ArgsT...>& t,
                             Args... args)
    {
        return ApplyFunc<Return, N - 1>::ApplyTuple(f, t, std::get<N - 1>(t), args...);
    }
};

template <typename Return>
struct ApplyFunc<Return, 0>
{
    template <typename... ArgsF, typename... ArgsT, typename... Args>
    static Return ApplyTuple(Return(*f)(ArgsF...),
                             const std::tuple<ArgsT...>&,
                             Args... args)
    {
        return (*f)(args...);
    }
};

}

namespace epi
{

template<typename T, typename Callback, typename ...Args>
class epiJobCallbackMember : public epiIJob
{
    static_assert(std::is_base_of_v<Object, T>);
    static_assert(std::is_member_function_pointer_v<Callback>);

public:
    using Return = typename std::result_of_t<Callback*(Args...)>;

public:
    epiJobCallbackMember(const T& object, Callback callback, Args ...args)
        : m_Object{object.Duplicate()}
        , m_Callback{callback}
        , m_Args{std::forward<Args>(args)...}
    {
    }

public:
    void Execute() override
    {
        epiProfileFunction;
        m_Result = ApplyMemberFunc<Return, sizeof...(Args)>::ApplyTuple(&m_Object, m_Callback, m_Args);
    }

    const T& GetObject() const { return m_Object; }
    T& GetObject() { return m_Object; }
    const Return& GetResult() const { return m_Result; }
    Return& GetResult() { return m_Result; }

protected:
    T m_Object;
    Callback* m_Callback;
    std::tuple<Args...> m_Args;
    Return m_Result;
};

template<typename Callback, typename ...Args>
class epiJobCallback : public epiIJob
{
    static_assert(std::is_function_v<Callback>);

public:
    using Return = typename std::result_of_t<Callback*(Args...)>;

public:
    epiJobCallback(Callback callback, Args ...args)
        : m_Callback{callback}
        , m_Args{std::forward<Args>(args)...}
    {
    }

public:
    void Execute() override
    {
        epiProfileFunction;
        m_Result = ApplyFunc<Return, sizeof...(Args)>::ApplyTuple(m_Callback, m_Args);
    }

    const Return& GetResult() const { return m_Result; }
    Return& GetResult() { return m_Result; }

protected:
    Callback* m_Callback;
    std::tuple<Args...> m_Args;
    Return m_Result;
};

}
