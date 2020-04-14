#pragma once

#include <algorithm>

#define EPI_GENREGION_BEGIN(x)
#define EPI_GENREGION_END(x)

#define EPI_NAMESPACE_BEGIN() namespace epi {
#define EPI_NAMESPACE_END() }

#define epiAssert(_x, _msg) assert(_x && _msg)
#define epiExpect(_x, _msg) assert(_x && _msg)
#define epiValidate(_x, _msg) isValid = isValid && (_x); epiExpect(_x, _msg)

#define epiFor(_n) for (int index = 0; index < _n; ++index)

#define epiTriggerBreakpoint() __debugbreak()

#define epiAs(_T, _V) static_cast<_T>(_V)
#define epiArrLen(_V) (sizeof(_V) / sizeof(_V[0]))

#define epiRand01() ((epiFloat)rand() / RAND_MAX)
#define epiToRadians(_degree) ((epiFloat)(_degree) * (M_PI / 180.0f))
#define epiToDegree(_radians) ((epiFloat)(_radians) * (180.0f / M_PI))

namespace epi
{

template <typename T>
epiS32 sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

inline epiMat2x2f RotationMatrix2D(epiFloat orientation)
{
    const epiFloat c = std::cosf(epiToRadians(orientation));
    const epiFloat s = std::sinf(epiToRadians(orientation));

    epiMat2x2f rot;
    rot[0][0] = c;
    rot[0][1] = s;
    rot[1][0] = -s;
    rot[1][1] = c;

    return rot;
}

template<typename T>
union Rect2
{
    struct
    {
        T Top;
        T Left;
        T Bottom;
        T Right;
    };

    struct
    {
        epiVec2<T> TopLeft;
        epiVec2<T> BottomRight;
    } _corners;

    epiVec4<T> tlbr;
};

using Rect2f = Rect2<epiFloat>;
using Rect2d = Rect2<epiDouble>;
using Rect2s = Rect2<epiS32>;
using Rect2u = Rect2<epiU32>;

}
