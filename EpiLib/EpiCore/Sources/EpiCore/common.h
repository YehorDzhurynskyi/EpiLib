#pragma once

#include <algorithm>
#include <chrono>

using namespace std::chrono_literals;

#define EPI_GENREGION_BEGIN(x)
#define EPI_GENREGION_END(x)

#define EPI_NAMESPACE_BEGIN() namespace epi {
#define EPI_NAMESPACE_END() }
#define EPI_NAMESPACE_USING() using namespace epi;

#define epiAssert(_x, _msg) assert(_x && "Function (" __FUNCTION__ "):" #_msg)
#define epiAssertStatic(_x) static_assert(_x)
#define epiAssertStaticEx(_x, _msg) static_assert(_x, _msg)
#define epiExpect(_x, _msg) assert(_x && "Function (" __FUNCTION__ "):" #_msg)
#define epiValidate(_x, _msg) isValid = isValid && (_x); epiExpect(_x, _msg)

#define epiFor(_n) for (int index = 0; index < _n; ++index)

#define epiTriggerBreakpoint() __debugbreak()

#define epiArrLen(_V) (sizeof(_V) / sizeof(_V[0]))

#define epiFloatingEqTolerance() 5.0e-5f
#define epiFloatingEqEx(_a, _b, _t) (std::abs((_a) - (_b)) < (_t))
#define epiFloatingEq(_a, _b) epiFloatingEqEx(_a, _b, epiFloatingEqTolerance())

#define epiRand01() ((epiFloat)rand() / RAND_MAX)
#define epiToRadians(_degree) ((epiFloat)(_degree) * (M_PI / 180.0f))
#define epiToDegree(_radians) ((epiFloat)(_radians) * (180.0f / M_PI))

#define epiStringify(_X) #_X
#define epiStringConcat(_X0, _X1) _X0 ## _X1

template<typename ...T>
constexpr auto epiMask(T... args) -> typename std::tuple_element<0, std::tuple<T...>>::type
{
    using MaskT = typename std::tuple_element<0, std::tuple<T...>>::type;
    return static_cast<MaskT>((... | args));
}

template<typename T>
constexpr size_t epiBitCount(T mask)
{
    // TODO: use POPCOUNT CPU feature
    static_assert(std::is_integral_v<T> || std::is_enum_v<T>);

    uint64_t mmask = static_cast<uint64_t>(mask);
    size_t count = 0;
    for (; mmask; ++count)
    {
        mmask &= mmask - 1;
    }

    return count;
}

template<typename T>
constexpr uint32_t epiBitPositionOf(T mask)
{
    static_assert(std::is_integral_v<T> || std::is_enum_v<T>);

    epiAssert(epiBitCount(mask) == 1);

    uint64_t mmask = static_cast<uint64_t>(mask);
    int32_t position = -1;
    for (; mmask; ++position)
    {
        mmask >>= 1;
    }

    return static_cast<uint32_t>(position);
}

template<typename T>
constexpr bool epiEqual(const T& lhs, const T& rhs)
{
    if constexpr (std::is_floating_point_v<T>)
    {
        return epiFloatingEq(lhs, rhs);
    }
    else
    {
        return lhs == rhs;
    }
}

#include <spdlog/spdlog.h>

#define epiLogTrace(MSG, ...)   spdlog::trace(MSG, __VA_ARGS__)
#define epiLogDebug(MSG, ...)   spdlog::debug(MSG, __VA_ARGS__)
#define epiLogInfo(MSG, ...)    spdlog::info(MSG, __VA_ARGS__)
#define epiLogWarn(MSG, ...)    spdlog::warn(MSG, __VA_ARGS__)
#define epiLogError(MSG, ...)   spdlog::error(MSG, __VA_ARGS__)
#define epiLogFatal(MSG, ...)   spdlog::critical(MSG, __VA_ARGS__)

#ifdef EPI_BUILD_PROFILE
#include <easy/profiler.h>

profiler::color_t epiProfileColorOf(std::string name);

#define epiProfileFunction              EASY_FUNCTION(epiProfileColorOf(__FUNCTION__))
#define epiProfileBlock(NAME)           EASY_BLOCK(NAME, epiProfileColorOf(NAME))
#define epiProfileBlockEnd              EASY_END_BLOCK
#define epiProfileThread(NAME)          EASY_THREAD(NAME)
#define epiProfileCaptureStart          EASY_START_CAPTURE
#define epiProfileCaptureStop           EASY_STOP_CAPTURE
#define epiProfileListenStart           profiler::startListen()
#define epiProfileListenStop            profiler::stopListen()
#define epiProfileListenStartEx(PORT)   profiler::startListen(PORT)
#define epiProfileListenStopEx(PORT)    profiler::stopListen(PORT)
#define epiProfileDump(FILENAME)        profiler::dumpBlocksToFile(FILENAME)
#else
#define epiProfileFunction
#define epiProfileBlock(NAME)
#define epiProfileBlockEnd
#define epiProfileThread(NAME)
#define epiProfileCaptureStart
#define epiProfileCaptureStop
#define epiProfileListenStart
#define epiProfileListenStop
#define epiProfileListenStartEx(PORT)
#define epiProfileListenStopEx(PORT)
#define epiProfileDump(FILENAME)
#endif
