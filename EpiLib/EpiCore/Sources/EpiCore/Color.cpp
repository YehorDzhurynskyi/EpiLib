EPI_GENREGION_BEGIN(include)
#include "EpiCore/Color.h"
#include "EpiCore/Color.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

const Color Color::kWhite = Color(0xff, 0xff, 0xff, 0xff);
const Color Color::kBlack = Color(0x0, 0x0, 0x0, 0xff);
const Color Color::kDarkGray = Color(0x33, 0x33, 0x33, 0xff);
const Color Color::kLightGray = Color(0xaa, 0xaa, 0xaa, 0xff);
const Color Color::kMagenta = Color(0xff, 0x0, 0xff, 0xff);
const Color Color::kLightRed = Color(0xfc, 0x4a, 0x03, 0xff);
const Color Color::kDarkRed = Color(0xd4, 0x02, 0x02, 0xff);
const Color Color::kLightGreen = Color(0x7b, 0xfc, 0x03, 0xff);
const Color Color::kDarkGreen = Color(0x61, 0xc9, 0x00, 0xff);
const Color Color::kLightBlue = Color(0x03, 0xc2, 0xfc, 0xff);
const Color Color::kDarkBlue = Color(0x03, 0x84, 0xfc, 0xff);

Color::Color(epiFloat r, epiFloat g, epiFloat b, epiFloat a)
{
    SetRf(r);
    SetGf(g);
    SetBf(b);
    SetAf(a);
}

Color::Color(epiS32 r, epiS32 g, epiS32 b, epiS32 a)
    : Color(static_cast<epiU8>(r), static_cast<epiU8>(g), static_cast<epiU8>(b), static_cast<epiU8>(a))
{
}

Color::Color(epiU8 r, epiU8 g, epiU8 b, epiU8 a)
{
    SetRu(r);
    SetGu(g);
    SetBu(b);
    SetAu(a);
}

Color::Color(epiFloat r, epiFloat g, epiFloat b)
    : Color(r, g, b, 1.0f)
{
}

Color::Color(epiS32 r, epiS32 g, epiS32 b)
    : Color(static_cast<epiU8>(r), static_cast<epiU8>(g), static_cast<epiU8>(b))
{
}

Color::Color(epiU8 r, epiU8 g, epiU8 b)
    : Color(r, g, b, static_cast<epiU8>(255))
{
}

// TODO: create an interface IValidation with `epiBool IValidate()` & `epiBool IValidate_Callback()`
// methods and call on each accessor method, declare IValidate as a wrapper for IValidate_Callback
// and soround IValidation with EPI_DEBUG
epiBool Color::Validate() const
{
    epiBool isValid = true;

    epiValidate(m_Color.r >= 0.0f && m_Color.r <= 1.0f, "R channel should be in range [0 - 1]");
    epiValidate(m_Color.g >= 0.0f && m_Color.g <= 1.0f, "G channel should be in range [0 - 1]");
    epiValidate(m_Color.b >= 0.0f && m_Color.b <= 1.0f, "B channel should be in range [0 - 1]");
    epiValidate(m_Color.a >= 0.0f && m_Color.a <= 1.0f, "A channel should be in range [0 - 1]");

    return isValid;
}

Color Color::Contrast(epiS8 contrast) const
{
#if 0 // TODO: investigate this filter
    Color color;

    const epiFloat f = 259.0f * (255.0f + contrast) / 255.0f * (259.0f - contrast);
    color.SetRf(std::clamp(f * (GetRf() - 0.5f) + 0.5f, 0.0f, 1.0f));
    color.SetGf(std::clamp(f * (GetGf() - 0.5f) + 0.5f, 0.0f, 1.0f));
    color.SetBf(std::clamp(f * (GetBf() - 0.5f) + 0.5f, 0.0f, 1.0f));
    color.SetAf(GetAf());

    return color;
#else
    Color color;

    const epiFloat f = (259.0f * (255.0f + contrast)) / (255.0f * (259.0f - contrast));
    color.SetRu(std::clamp(static_cast<epiS32>(f * (GetRu() - 128) + 128), 0, 255));
    color.SetGu(std::clamp(static_cast<epiS32>(f * (GetGu() - 128) + 128), 0, 255));
    color.SetBu(std::clamp(static_cast<epiS32>(f * (GetBu() - 128) + 128), 0, 255));
    color.SetAu(GetAu());

    return color;
#endif
}

Color Color::ContrastStretch(epiU8 lower, epiU8 upper) const
{
    epiAssert(lower < upper);

    const epiU8 c = static_cast<epiU8>(std::clamp((255.0f / (upper - lower)) * (GetLumau() - lower), 0.0f, 255.0f));
    return Color(c, c, c);
}

Color Color::ContrastStretch(epiU8 lowerR,
                             epiU8 upperR,
                             epiU8 lowerG,
                             epiU8 upperG,
                             epiU8 lowerB,
                             epiU8 upperB) const
{
    epiAssert(lowerR < upperR);
    epiAssert(lowerG < upperG);
    epiAssert(lowerB < upperB);

    const epiU8 r = static_cast<epiU8>(std::clamp((255.0f / (upperR - lowerR)) * (GetRu() - lowerR), 0.0f, 255.0f));
    const epiU8 g = static_cast<epiU8>(std::clamp((255.0f / (upperG - lowerG)) * (GetGu() - lowerG), 0.0f, 255.0f));
    const epiU8 b = static_cast<epiU8>(std::clamp((255.0f / (upperB - lowerB)) * (GetBu() - lowerB), 0.0f, 255.0f));

    return Color(r, g, b);
}

epiU8 Color::GetRu_Callback() const
{
    return static_cast<epiU8>(m_Color.r * 255.0f);
}

void Color::SetRu_Callback(epiU8 value)
{
    m_Color.r = static_cast<epiFloat>(value / 255.0f);
}

epiU8 Color::GetGu_Callback() const
{
    return static_cast<epiU8>(m_Color.g * 255.0f);
}

void Color::SetGu_Callback(epiU8 value)
{
    m_Color.g = static_cast<epiFloat>(value / 255.0f);
}

epiU8 Color::GetBu_Callback() const
{
    return static_cast<epiU8>(m_Color.b * 255.0f);
}

void Color::SetBu_Callback(epiU8 value)
{
    m_Color.b = static_cast<epiFloat>(value / 255.0f);
}

epiU8 Color::GetAu_Callback() const
{
    return static_cast<epiU8>(m_Color.a * 255.0f);
}

void Color::SetAu_Callback(epiU8 value)
{
    m_Color.a = static_cast<epiFloat>(value / 255.0f);
}

epiFloat Color::GetRf_Callback() const
{
    return m_Color.r;
}

void Color::SetRf_Callback(epiFloat value)
{
    epiExpect(value >= 0.0f && value <= 1.0f, "color channel value should be in range [0 - 1]");
    m_Color.r = value;
}

epiFloat Color::GetGf_Callback() const
{
    return m_Color.g;
}

void Color::SetGf_Callback(epiFloat value)
{
    epiExpect(value >= 0.0f && value <= 1.0f, "Color channels should be in range [0 - 1]");
    m_Color.g = value;
}

epiFloat Color::GetBf_Callback() const
{
    return m_Color.b;
}

void Color::SetBf_Callback(epiFloat value)
{
    epiExpect(value >= 0.0f && value <= 1.0f, "color channel value should be in range [0 - 1]");
    m_Color.b = value;
}

epiFloat Color::GetAf_Callback() const
{
    return m_Color.a;
}

void Color::SetAf_Callback(epiFloat value)
{
    epiExpect(value >= 0.0f && value <= 1.0f, "color channel value should be in range [0 - 1]");
    m_Color.a = value;
}

epiU32 Color::GetRGBA32_Callback() const
{
    Validate();

    const epiU32 r = static_cast<epiU32>(m_Color.r * 255.0f);
    const epiU32 g = static_cast<epiU32>(m_Color.g * 255.0f);
    const epiU32 b = static_cast<epiU32>(m_Color.b * 255.0f);
    const epiU32 a = static_cast<epiU32>(m_Color.a * 255.0f);

    return r << 24 | g << 16 | b << 8 | a;
}

void Color::SetRGBA32_Callback(epiU32 value)
{
    SetRu((value >> 24) & 0xff);
    SetGu((value >> 16) & 0xff);
    SetBu((value >> 8) & 0xff);
    SetAu((value >> 0) & 0xff);

    Validate();
}

epiU32 Color::GetBGRA32_Callback() const
{
    Validate();

    const epiU32 r = static_cast<epiU32>(m_Color.r * 255.0f);
    const epiU32 g = static_cast<epiU32>(m_Color.g * 255.0f);
    const epiU32 b = static_cast<epiU32>(m_Color.b * 255.0f);
    const epiU32 a = static_cast<epiU32>(m_Color.a * 255.0f);

    return b << 24 | g << 16 | r << 8 | a;
}

void Color::SetBGRA32_Callback(epiU32 value)
{
    SetBu((value >> 24) & 0xff);
    SetGu((value >> 16) & 0xff);
    SetRu((value >> 8) & 0xff);
    SetAu((value >> 0) & 0xff);

    Validate();
}

epiU32 Color::GetRGB24_Callback() const
{
    Validate();

    const epiU32 r = static_cast<epiU32>(m_Color.r * 255.0f);
    const epiU32 g = static_cast<epiU32>(m_Color.g * 255.0f);
    const epiU32 b = static_cast<epiU32>(m_Color.b * 255.0f);

    return r << 24 | g << 16 | b << 8;
}

void Color::SetRGB24_Callback(epiU32 value)
{
    SetRu((value >> 24) & 0xff);
    SetGu((value >> 16) & 0xff);
    SetBu((value >> 8) & 0xff);
    SetAu(0);

    Validate();
}

epiU32 Color::GetBGR24_Callback() const
{
    Validate();

    const epiU32 r = static_cast<epiU32>(m_Color.r * 255.0f);
    const epiU32 g = static_cast<epiU32>(m_Color.g * 255.0f);
    const epiU32 b = static_cast<epiU32>(m_Color.b * 255.0f);

    return b << 24 | g << 16 | r << 8;
}

void Color::SetBGR24_Callback(epiU32 value)
{
    SetBu((value >> 24) & 0xff);
    SetGu((value >> 16) & 0xff);
    SetRu((value >> 8) & 0xff);
    SetAu(0);

    Validate();
}

epiFloat Color::GetLumaf_Callback() const
{
    return GetRf() * 0.299f + GetGf() * 0.587f + GetBf() * 0.114f;
}

epiU8 Color::GetLumau_Callback() const
{
    return static_cast<epiU8>(GetLumaf() * 255.0f);
}

const epiVec4f& Color::GetColor_Callback() const
{
    Validate();
    return m_Color;
}

void Color::SetColor_Callback(const epiVec4f& value)
{
    m_Color = value;
    Validate();
}

Color& Color::operator+=(const Color& rhs)
{
    Validate();
    rhs.Validate();

    m_Color.r = std::clamp(m_Color.r + rhs.m_Color.r, 0.0f, 1.0f);
    m_Color.g = std::clamp(m_Color.g + rhs.m_Color.g, 0.0f, 1.0f);
    m_Color.b = std::clamp(m_Color.b + rhs.m_Color.b, 0.0f, 1.0f);
    m_Color.a = std::clamp(m_Color.a + rhs.m_Color.a, 0.0f, 1.0f);

    Validate();

    return *this;
}

Color& Color::operator*=(const Color& rhs)
{
    Validate();
    rhs.Validate();

    m_Color *= rhs.m_Color;

    Validate();

    return *this;
}

Color operator+(const Color& lhs, const Color& rhs)
{
    lhs.Validate();
    rhs.Validate();

    Color color;

    color.SetRf(std::clamp(lhs.m_Color.r + rhs.m_Color.r, 0.0f, 1.0f));
    color.SetGf(std::clamp(lhs.m_Color.g + rhs.m_Color.g, 0.0f, 1.0f));
    color.SetBf(std::clamp(lhs.m_Color.b + rhs.m_Color.b, 0.0f, 1.0f));
    color.SetAf(std::clamp(lhs.m_Color.a + rhs.m_Color.a, 0.0f, 1.0f));

    color.Validate();

    return color;
}

Color operator*(const Color& lhs, const Color& rhs)
{
    lhs.Validate();
    rhs.Validate();

    Color color;

    color.m_Color = lhs.m_Color * rhs.m_Color;

    color.Validate();

    return color;
}

Color operator*(const Color& lhs, epiFloat rhs)
{
    lhs.Validate();

    Color color;

    color.SetRf(std::clamp(lhs.m_Color.r * rhs, 0.0f, 1.0f));
    color.SetGf(std::clamp(lhs.m_Color.g * rhs, 0.0f, 1.0f));
    color.SetBf(std::clamp(lhs.m_Color.b * rhs, 0.0f, 1.0f));
    color.SetAf(std::clamp(lhs.m_Color.a * rhs, 0.0f, 1.0f));

    color.Validate();

    return color;
}

Color operator*(epiFloat lhs, const Color& rhs)
{
    rhs.Validate();

    Color color;

    color.SetRf(std::clamp(lhs * rhs.m_Color.r, 0.0f, 1.0f));
    color.SetGf(std::clamp(lhs * rhs.m_Color.g, 0.0f, 1.0f));
    color.SetBf(std::clamp(lhs * rhs.m_Color.b, 0.0f, 1.0f));
    color.SetAf(std::clamp(lhs * rhs.m_Color.a, 0.0f, 1.0f));

    color.Validate();

    return color;
}

EPI_NAMESPACE_END()
