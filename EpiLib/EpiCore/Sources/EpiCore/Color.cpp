EPI_GENREGION_BEGIN(include)
#include "EpiCore/Color.h"
#include "EpiCore/Color.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

const Color Color::kWhite = Color(0xff, 0xff, 0xff, 0xff);
const Color Color::kBlack = Color(0x0, 0x0, 0x0, 0xff);
const Color Color::kDarkGray = Color(0x33, 0x33, 0x33, 0xff);
const Color Color::kLightGray = Color(0xaa, 0xaa, 0xaa, 0xff);
const Color Color::kPurple = Color(0x9a, 0x02, 0xb5, 0xff);
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

Color Color::FromHSB(const epiVec3f& hsb)
{
    if (hsb.y == 0.0f)
    {
        return Color(hsb.z, hsb.z, hsb.z);
    }

    const epiS32 i = static_cast<epiS32>(hsb.x * 6.0f);
    const epiFloat f = (hsb.x * 6.0f) - i;
    const epiFloat p = hsb.z * (1.0f - hsb.y);
    const epiFloat q = hsb.z * (1.0f - hsb.y * f);
    const epiFloat t = hsb.z * (1.0f - hsb.y * (1.0f - f));

    switch (i % 6)
    {
    case 0: return Color(hsb.z, t, p);
    case 1: return Color(q, hsb.z, p);
    case 2: return Color(p, hsb.z, t);
    case 3: return Color(p, q, hsb.z);
    case 4: return Color(t, p, hsb.z);
    case 5: return Color(hsb.z, p, q);
    default: epiLogError("Couldn't be here! Invalid i=`{}`!", i); return Color{};
    }
}

Color Color::FromHSB(const epiVec3u8& hsb)
{
    return FromHSB(epiVec3f(hsb.x / 255.0f, hsb.y / 255.0f, hsb.z / 255.0f));
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

Color Color::Contrast(epiS8 contrastR, epiS8 contrastG, epiS8 contrastB) const
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

    const epiFloat fR = (259.0f * (255.0f + contrastR)) / (255.0f * (259.0f - contrastR));
    const epiFloat fG = (259.0f * (255.0f + contrastG)) / (255.0f * (259.0f - contrastG));
    const epiFloat fB = (259.0f * (255.0f + contrastB)) / (255.0f * (259.0f - contrastB));

    color.SetRu(std::clamp(static_cast<epiS32>(fR * (GetRu() - 128) + 128), 0, 255));
    color.SetGu(std::clamp(static_cast<epiS32>(fG * (GetGu() - 128) + 128), 0, 255));
    color.SetBu(std::clamp(static_cast<epiS32>(fB * (GetBu() - 128) + 128), 0, 255));
    color.SetAu(GetAu());

    return color;
#endif
}

Color Color::ContrastStretch(epiU8 lowerR,
                             epiU8 upperR,
                             epiU8 lowerG,
                             epiU8 upperG,
                             epiU8 lowerB,
                             epiU8 upperB) const
{
    const epiU8 r = lowerR >= upperR ? GetRu() : static_cast<epiU8>(std::clamp((255.0f / (upperR - lowerR)) * (GetRu() - lowerR), 0.0f, 255.0f));
    const epiU8 g = lowerG >= upperG ? GetGu() : static_cast<epiU8>(std::clamp((255.0f / (upperG - lowerG)) * (GetGu() - lowerG), 0.0f, 255.0f));
    const epiU8 b = lowerB >= upperB ? GetBu() : static_cast<epiU8>(std::clamp((255.0f / (upperB - lowerB)) * (GetBu() - lowerB), 0.0f, 255.0f));

    return Color(r, g, b);
}

Color Color::Shift(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB) const
{
    const epiU8 r = std::clamp(shiftR + GetRu(), 0, 255);
    const epiU8 g = std::clamp(shiftG + GetGu(), 0, 255);
    const epiU8 b = std::clamp(shiftB + GetBu(), 0, 255);

    return Color(r, g, b);
}

Color Color::ShiftRotate(epiS32 shiftR, epiS32 shiftG, epiS32 shiftB) const
{
    epiS32 r = (shiftR + GetRu()) % 256;
    if (r < 0)
    {
        r += 255;
    }

    epiS32 g = (shiftG + GetGu()) % 256;
    if (g < 0)
    {
        g += 255;
    }

    epiS32 b = (shiftB + GetBu()) % 256;
    if (b < 0)
    {
        b += 255;
    }

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

epiFloat Color::GetMinf_Callback() const
{
    return std::min({GetRf(), GetGf(), GetBf()});
}

epiU8 Color::GetMinu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetMinf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetMaxf_Callback() const
{
    return std::max({GetRf(), GetGf(), GetBf()});
}

epiU8 Color::GetMaxu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetMaxf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetHuef_Callback() const
{
    const epiFloat chroma = GetChromaf();
    if (chroma == 0.0f)
    {
        return 0.0f;
    }

    epiFloat h = 0.0f;

    const epiFloat max = GetMaxf();
    const epiFloat min = GetMinf();

    const epiFloat cR = (max - GetRf()) / chroma;
    const epiFloat cG = (max - GetGf()) / chroma;
    const epiFloat cB = (max - GetBf()) / chroma;

    if (epiEqual(GetRf(), max))
    {
        h = cB - cG;
    }
    else if (epiEqual(GetGf(), max))
    {
        h = 2.0f + cR - cB;
    }
    else
    {
        h = 4.0f + cG - cR;
    }

    h /= 6.0f;
    if (h < 0)
    {
        h += 1.0f;
    }

    return h;
}

epiU8 Color::GetHueu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetHuef(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetLumaf_Callback() const
{
    return GetLuma601f();
}

epiU8 Color::GetLumau_Callback() const
{
    return GetLuma601u();
}

epiFloat Color::GetLuma601f_Callback() const
{
    return GetRf() * 0.299f + GetGf() * 0.587f + GetBf() * 0.114f;
}

epiU8 Color::GetLuma601u_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetLuma601f(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetLuma240f_Callback() const
{
    return GetRf() * 0.212f + GetGf() * 0.701f + GetBf() * 0.087f;
}

epiU8 Color::GetLuma240u_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetLuma240f(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetLuma709f_Callback() const
{
    return GetRf() * 0.2126f + GetGf() * 0.7152f + GetBf() * 0.0722f;
}

epiU8 Color::GetLuma709u_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetLuma709f(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetLuma2020f_Callback() const
{
    return GetRf() * 0.2627f + GetGf() * 0.6780f + GetBf() * 0.0593f;
}

epiU8 Color::GetLuma2020u_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetLuma2020f(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetBrightnessf_Callback() const
{
    return GetMaxf();
}

epiU8 Color::GetBrightnessu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetBrightnessf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetLightnessf_Callback() const
{
    return 0.5f * (GetMaxf() + GetMinf());
}

epiU8 Color::GetLightnessu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetLightnessf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetIntensityf_Callback() const
{
    return (GetRf() + GetGf() + GetBf()) / 3.0f;
}

epiU8 Color::GetIntensityu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetIntensityf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetChromaf_Callback() const
{
    return GetMaxf() - GetMinf();
}

epiU8 Color::GetChromau_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetChromaf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetSaturationBf_Callback() const
{
    const epiFloat b = GetBrightnessf();
    return b != 0.0f ? GetChromaf() / b : 0.0f;
}

epiU8 Color::GetSaturationBu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetSaturationBf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetSaturationLf_Callback() const
{
    const epiFloat l = GetLightnessf();
    return l != 0.0f && l != 1.0f ? GetChromaf() / (1.0f - std::abs(2.0f * l - 1.0f)) : 0.0f;
}

epiU8 Color::GetSaturationLu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetSaturationLf(), 0.0f, 1.0f) * 255.0f);
}

epiFloat Color::GetSaturationIf_Callback() const
{
    const epiFloat i = GetIntensityf();
    return i != 0.0f ? 1.0f - (GetMinf() / i) : 0.0f;
}

epiU8 Color::GetSaturationIu_Callback() const
{
    return static_cast<epiU8>(std::clamp(GetSaturationIf(), 0.0f, 1.0f) * 255.0f);
}

epiVec3f Color::GetHSBf_Callback() const
{
    return epiVec3f{GetHuef(), GetSaturationBf(), GetBrightnessf()};
}

epiVec3u8 Color::GetHSBu_Callback() const
{
    const epiVec3f hsb = GetHSBf();
    return epiVec3u8
    {
        static_cast<epiU8>(std::clamp(hsb.x, 0.0f, 1.0f) * 255.0f),
        static_cast<epiU8>(std::clamp(hsb.y, 0.0f, 1.0f) * 255.0f),
        static_cast<epiU8>(std::clamp(hsb.z, 0.0f, 1.0f) * 255.0f)
    };
}

epiVec3f Color::GetHSLf_Callback() const
{
    return epiVec3f{GetHuef(), GetSaturationLf(), GetLightnessf()};
}

epiVec3u8 Color::GetHSLu_Callback() const
{
    const epiVec3f hsl = GetHSLf();
    return epiVec3u8
    {
        static_cast<epiU8>(std::clamp(hsl.x, 0.0f, 1.0f) * 255.0f),
        static_cast<epiU8>(std::clamp(hsl.y, 0.0f, 1.0f) * 255.0f),
        static_cast<epiU8>(std::clamp(hsl.z, 0.0f, 1.0f) * 255.0f)
    };
}

epiVec3f Color::GetHSIf_Callback() const
{
    return epiVec3f{GetHuef(), GetSaturationIf(), GetIntensityf()};
}

epiVec3u8 Color::GetHSIu_Callback() const
{
    const epiVec3f hsi = GetHSIf();
    return epiVec3u8
    {
        static_cast<epiU8>(std::clamp(hsi.x, 0.0f, 1.0f) * 255.0f),
        static_cast<epiU8>(std::clamp(hsi.y, 0.0f, 1.0f) * 255.0f),
        static_cast<epiU8>(std::clamp(hsi.z, 0.0f, 1.0f) * 255.0f)
    };
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
