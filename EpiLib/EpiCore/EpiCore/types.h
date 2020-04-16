#pragma once

#include "common.h"
#include <string>
#include <glm/glm.hpp>

using epiChar = char;
using epiBool = bool;
using epiByte = uint8_t;

using epiSize_t = size_t;
using epiHash_t = uint32_t;

using epiU8 = uint8_t;
using epiU16 = uint16_t;
using epiU32 = uint32_t;
using epiU64 = uint64_t;

using epiS8 = int8_t;
using epiS16 = int16_t;
using epiS32 = int32_t;
using epiS64 = int64_t;

using epiFloat = float;
using epiDouble = double;

using epiString = std::string;

template<size_t N, typename T>
using epiVec = glm::vec<N, T>;

template<typename T>
using epiVec2 = epiVec<2, T>;
using epiVec2f = epiVec2<epiFloat>;
using epiVec2d = epiVec2<epiDouble>;
using epiVec2s = epiVec2<epiS32>;
using epiVec2u = epiVec2<epiU32>;

template<typename T>
using epiVec3 = epiVec<3, T>;
using epiVec3f = epiVec3<epiFloat>;
using epiVec3d = epiVec3<epiDouble>;
using epiVec3s = epiVec3<epiS32>;
using epiVec3u = epiVec3<epiU32>;

template<typename T>
using epiVec4 = epiVec<4, T>;
using epiVec4f = epiVec4<epiFloat>;
using epiVec4d = epiVec4<epiDouble>;
using epiVec4s = epiVec4<epiS32>;
using epiVec4u = epiVec2<epiU32>;

using epiMat2x2f = glm::mat2x2;
using epiMat3x3f = glm::mat3x3;
using epiMat4x4f = glm::mat4x4;

template<typename T>
class epiRect2
{
public:
    epiRect2() = default;
    epiRect2(const epiRect2& rhs) = default;
    epiRect2& operator=(const epiRect2& rhs) = default;
    epiRect2(epiRect2&& rhs) = default;
    epiRect2& operator=(epiRect2&& rhs) = default;
    ~epiRect2() = default;

    epiBool Validate() const
    {
        epiBool isValid = true;

        epiValidate(Width > T{}, "Width should be greater than 0");
        epiValidate(Height > T{}, "Height should be greater than 0");

        return isValid;
    }

    epiRect2(const epiVec2<T>& tl, const epiVec2<T>& br)
        : X(tl.x)
        , Y(tl.y)
        , Width(br.x - tl.x)
        , Height(br.y - tl.y)
    {
        Validate();
    }

    epiRect2(T x, T y, T width, T height)
        : X(x)
        , Y(y)
        , Width(width)
        , Height(height)
    {}

    epiVec2<T> TopLeft() const
    {
        Validate();
        return epiVec2<T>(X, Y);
    }

    epiVec2<T> BottomRight() const
    {
        Validate();
        return epiVec2<T>(X + Width, Y + Height);
    }

public:
    T X{};
    T Y{};
    T Width{};
    T Height{};
};

using epiRect2f = epiRect2<epiFloat>;
using epiRect2d = epiRect2<epiDouble>;
using epiRect2s = epiRect2<epiS32>;
using epiRect2u = epiRect2<epiU32>;
