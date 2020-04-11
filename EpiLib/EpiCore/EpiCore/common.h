#pragma once

#include <algorithm>

#define EPI_GENREGION_BEGIN(x)
#define EPI_GENREGION_END(x)

#define EPI_NAMESPACE_BEGIN() namespace epi {
#define EPI_NAMESPACE_END() }

#define epiExpect(_x) assert(_x)

#define epiFor(_n) for (int index = 0; index < _n; ++index)

#define epiTriggerBreakpoint() __debugbreak()

#define epiAs(_T, _V) static_cast<_T>(_V)
#define epiArrLen(_V) (sizeof(_V) / sizeof(_V[0]))

#define epiRand01() ((epiFloat)rand() / RAND_MAX)
#define epiToRadians(_degree) ((epiFloat)(_degree) * (M_PI / 180.0f))
#define epiToDegree(_radians) ((epiFloat)(_radians) * (180.0f / M_PI))

namespace epi
{

template<typename T>
T clamp(const T& val, const T& min, const T& max)
{
    return std::min<T>(max, std::max<T>(val, min));
}

template <typename T> epiS32 sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

template<typename T>
epiFloat dir2degree(const epiV2<T>& dir)
{
    return epiToDegree(atan2(dir.y, dir.x)) - 90.0f;
}

template<typename T>
epiV2<T> degree2dir(epiFloat degree)
{
    return
    {
        std::cos(epiToRadians(degree + 90.0f)),
        std::sin(epiToRadians(degree + 90.0f))
    };
}

inline epiMat2x2F RotationMatrix2D(epiFloat orientation)
{
    const epiFloat c = std::cosf(epiToRadians(orientation));
    const epiFloat s = std::sinf(epiToRadians(orientation));

    epiMat2x2F rot;
    rot[0][0] = c;
    rot[0][1] = s;
    rot[1][0] = -s;
    rot[1][1] = c;

    return rot;
}

template<typename T>
union Rect
{
    struct
    {
        T Right;
        T Top;
        T Left;
        T Bottom;
    } _sides;

    struct
    {
        epiV2<T> RightTop;
        epiV2<T> LeftBottom;
    } _corners;

    epiV4<T> _rtlb;
};

using fRect = Rect<epiFloat>;
using sRect = Rect<epiS32>;

}
