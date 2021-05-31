#pragma once

#include "common.h"
#include <string>
#include <cwchar>
#include <ccomplex>
#include <glm/glm.hpp>

using epiChar = char;
using epiWChar = wchar_t;
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
using epiWString = std::wstring;

template<size_t N, typename T>
using epiVec = glm::vec<N, T>;

template<typename T>
using epiVec2 = epiVec<2, T>;

using epiSize2 = epiVec2<epiSize_t>;
using epiSize2f = epiVec2<epiFloat>;
using epiSize2d = epiVec2<epiDouble>;
using epiSize2s = epiVec2<epiS32>;
using epiSize2u = epiVec2<epiU32>;

using epiVec2f = epiVec2<epiFloat>;
using epiVec2d = epiVec2<epiDouble>;
using epiVec2s = epiVec2<epiS32>;
using epiVec2u = epiVec2<epiU32>;
using epiVec2s8 = epiVec2<epiS8>;
using epiVec2s16 = epiVec2<epiS16>;
using epiVec2s32 = epiVec2<epiS32>;
using epiVec2s64 = epiVec2<epiS64>;
using epiVec2u8 = epiVec2<epiU8>;
using epiVec2u16 = epiVec2<epiU16>;
using epiVec2u32 = epiVec2<epiU32>;
using epiVec2u64 = epiVec2<epiU64>;

template<typename T>
using epiVec3 = epiVec<3, T>;
using epiVec3f = epiVec3<epiFloat>;
using epiVec3d = epiVec3<epiDouble>;
using epiVec3s = epiVec3<epiS32>;
using epiVec3u = epiVec3<epiU32>;
using epiVec3s8 = epiVec3<epiS8>;
using epiVec3s16 = epiVec3<epiS16>;
using epiVec3s32 = epiVec3<epiS32>;
using epiVec3s64 = epiVec3<epiS64>;
using epiVec3u8 = epiVec3<epiU8>;
using epiVec3u16 = epiVec3<epiU16>;
using epiVec3u32 = epiVec3<epiU32>;
using epiVec3u64 = epiVec3<epiU64>;

template<typename T>
using epiVec4 = epiVec<4, T>;
using epiVec4f = epiVec4<epiFloat>;
using epiVec4d = epiVec4<epiDouble>;
using epiVec4s = epiVec4<epiS32>;
using epiVec4u = epiVec4<epiU32>;
using epiVec4s8 = epiVec4<epiS8>;
using epiVec4s16 = epiVec4<epiS16>;
using epiVec4s32 = epiVec4<epiS32>;
using epiVec4s64 = epiVec4<epiS64>;
using epiVec4u8 = epiVec4<epiU8>;
using epiVec4u16 = epiVec4<epiU16>;
using epiVec4u32 = epiVec4<epiU32>;
using epiVec4u64 = epiVec4<epiU64>;

using epiMat2x2f = glm::mat2x2;
using epiMat3x3f = glm::mat3x3;
using epiMat4x4f = glm::mat4x4;

using epiComplexf = std::complex<epiFloat>;
using epiComplexd = std::complex<epiDouble>;

template<typename T>
class epiRect2
{
public:
    using value_type = T;

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

        epiValidate(Left <= Right, "Left should be <= Right");
        epiValidate(Bottom <= Top, "Bottom should be <= Top");
        epiValidate(GetWidth() >= T{}, "Width should be >= 0");
        epiValidate(GetHeight() >= T{}, "Height should be >= 0");

        return isValid;
    }

    epiRect2(const epiVec2<T>& lb, const epiVec2<T>& rt)
        : Left(lb.x)
        , Bottom(lb.y)
        , Right(rt.x)
        , Top(rt.y)
    {
        Validate();
    }

    epiRect2(T left, T bottom, T width, T height)
        : Left(left)
        , Bottom(bottom)
        , Right(left + width)
        , Top(bottom + height)
    {
        epiAssert(width >= T{});
        epiAssert(height >= T{});

        Validate();
    }

    epiVec2<T> LeftBottom() const
    {
        Validate();
        return epiVec2<T>(Left, Bottom);
    }

    epiVec2<T> RightTop() const
    {
        Validate();
        return epiVec2<T>(Right, Top);
    }

    epiVec2<T> LeftTop() const
    {
        Validate();
        return epiVec2<T>(Left, Top);
    }

    epiVec2<T> RightBottom() const
    {
        Validate();
        return epiVec2<T>(Right, Bottom);
    }

    T GetWidth() const
    {
        return Right - Left;
    }

    T GetHeight() const
    {
        return Top - Bottom;
    }

    epiVec2<T> GetSize() const
    {
        return epiVec2<T>(GetWidth(), GetHeight());
    }

    epiBool IsEmpty() const
    {
        return GetWidth() <= T{} || GetHeight() <= T{};
    }

    epiBool IsIn(const epiVec2<T>& vec) const
    {
        return
            vec.x >= Left &&
            vec.y >= Bottom &&
            vec.x <= Right &&
            vec.y <= Top;
    }

    friend epiBool operator==(const epiRect2<T>& lhs, const epiRect2<T>& rhs)
    {
        return
            epiEqual(lhs.Left, rhs.Left) &&
            epiEqual(lhs.Bottom, rhs.Bottom) &&
            epiEqual(lhs.Right, rhs.Right) &&
            epiEqual(lhs.Top, rhs.Top);
    }

    friend epiBool operator!=(const epiRect2<T>& lhs, const epiRect2<T>& rhs)
    {
        return !(operator==(lhs, rhs));
    }

    friend epiRect2<T> operator*(const epiRect2<T>& lhs, epiFloat rhs)
    {
        epiRect2<T> rect;

        rect.Left = lhs.Left * rhs;
        rect.Bottom = lhs.Bottom * rhs;
        rect.Right = lhs.Right * rhs;
        rect.Top = lhs.Top * rhs;

        return rect;
    }

    friend epiRect2<T> operator*(epiFloat lhs, const epiRect2<T>& rhs)
    {
        epiRect2<T> rect;

        rect.Left = rhs.Left * lhs;
        rect.Bottom = rhs.Bottom * lhs;
        rect.Right = rhs.Right * lhs;
        rect.Top = rhs.Top * lhs;

        return rect;
    }

    friend epiRect2<T> operator+(const epiRect2<T>& lhs, const epiVec2<T>& rhs)
    {
        epiRect2<T> rect;

        rect.Left = lhs.Left + rhs.x;
        rect.Bottom = lhs.Bottom + rhs.y;
        rect.Right = lhs.Right + rhs.x;
        rect.Top = lhs.Top + rhs.y;

        return rect;
    }

    friend epiRect2<T> operator+(const epiVec2<T>& lhs, const epiRect2<T>& rhs)
    {
        epiRect2<T> rect;

        rect.Left = rhs.Left + lhs.x;
        rect.Bottom = rhs.Bottom + lhs.y;
        rect.Right = rhs.Right + lhs.x;
        rect.Top = rhs.Top + lhs.y;

        return rect;
    }

    epiRect2<T>& operator*=(const epiVec2<T>& rhs)
    {
        Left *=  rhs.x;
        Bottom *= rhs.y;
        Right *= rhs.x;
        Top *= rhs.y;

        return *this;
    }

    epiRect2<T>& operator/=(const epiVec2<T>& rhs)
    {
        Left /= rhs.x;
        Bottom /= rhs.y;
        Right /= rhs.x;
        Top /= rhs.y;

        return *this;
    }

    friend epiRect2<T> operator*(const epiRect2<T>& lhs, const epiVec2<T>& rhs)
    {
        epiRect2<T> rect;

        rect.Left = lhs.Left * rhs.x;
        rect.Bottom = lhs.Bottom * rhs.y;
        rect.Right = lhs.Right * rhs.x;
        rect.Top = lhs.Top * rhs.y;

        return rect;
    }

    friend epiRect2<T> operator*(const epiVec2<T>& lhs, const epiRect2<T>& rhs)
    {
        epiRect2<T> rect;

        rect.Left = rhs.Left * lhs.x;
        rect.Bottom = rhs.Bottom * lhs.y;
        rect.Right = rhs.Right * lhs.x;
        rect.Top = rhs.Top * lhs.y;

        return rect;
    }

    friend epiRect2<T> operator/(const epiRect2<T>& lhs, const epiVec2<T>& rhs)
    {
        epiRect2<T> rect;

        rect.Left = lhs.Left / rhs.x;
        rect.Bottom = lhs.Bottom / rhs.y;
        rect.Right = lhs.Right / rhs.x;
        rect.Top = lhs.Top / rhs.y;

        return rect;
    }

    friend epiRect2<T> operator/(const epiVec2<T>& lhs, const epiRect2<T>& rhs)
    {
        epiRect2<T> rect;

        rect.Left = rhs.Left / lhs.x;
        rect.Bottom = rhs.Bottom / lhs.y;
        rect.Right = rhs.Right / lhs.x;
        rect.Top = rhs.Top / lhs.y;

        return rect;
    }

    friend epiRect2<T>& operator&=(epiRect2<T>& a, const epiRect2<T>& b)
    {
        T left = std::max(a.Left, b.Left);
        T bottom = std::max(a.Bottom, b.Bottom);
        T right = std::min(a.Right, b.Right);
        T top = std::min(a.Top, b.Top);

        a.Left = left;
        a.Bottom = bottom;
        a.Right = right;
        a.Top = top;

        if (a.IsEmpty())
        {
            a = epiRect2<T>();
        }

        return a;
    }

    friend epiRect2<T>& operator|=(epiRect2<T>& a, const epiRect2<T>& b)
    {
        if (a.IsEmpty())
        {
            a = b;
        }
        else if (!b.IsEmpty())
        {
            T left = std::min(a.Left, b.Left);
            T bottom = std::min(a.Bottom, b.Bottom);
            T right = std::max(a.Right, b.Right);
            T top = std::max(a.Top, b.Top);

            a.Left = left;
            a.Bottom = bottom;
            a.Right = right;
            a.Top = top;
        }

        return a;
    }

    friend epiRect2<T> operator&(const epiRect2<T>& a, const epiRect2<T>& b)
    {
        epiRect2<T> c = a;
        return c &= b;
    }

    friend epiRect2<T> operator|(const epiRect2<T>& a, const epiRect2<T>& b)
    {
        epiRect2<T> c = a;
        return c |= b;
    }

public:
    T Left{};
    T Bottom{};
    T Right{};
    T Top{};
};

using epiRect2f = epiRect2<epiFloat>;
using epiRect2d = epiRect2<epiDouble>;
using epiRect2s = epiRect2<epiS32>;
using epiRect2u = epiRect2<epiU32>;

template<typename TImpl>
class epiPimpl final
{
public:
    epiPimpl() = default;

    explicit epiPimpl(const std::shared_ptr<TImpl>& impl)
        : m_Impl{impl}
    {
    }

    explicit epiPimpl(std::shared_ptr<TImpl>&& impl)
        : m_Impl{std::move(impl)}
    {
    }

    epiPimpl& operator=(const std::shared_ptr<TImpl>& impl)
    {
        m_Impl = impl;
        return *this;
    }

    epiPimpl& operator=(std::shared_ptr<TImpl>&& impl)
    {
        m_Impl = std::move(impl);
        return *this;
    }

    void Reset()
    {
        m_Impl.reset();
    }

    operator epiBool() const { return static_cast<epiBool>(m_Impl); }

    TImpl* operator->() { return Ptr(); }
    const TImpl* operator->() const { return Ptr(); }

    TImpl& operator*() { return *Ptr(); }
    const TImpl& operator*() const { return *Ptr(); }

    const TImpl* Ptr() const { return m_Impl.get(); }
    TImpl* Ptr() { return m_Impl.get(); }

private:
    std::shared_ptr<TImpl> m_Impl{nullptr};
};
