#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Color.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class Color final : public Object
{
EPI_GENREGION_BEGIN(Color)

EPI_GENHIDDEN_Color()

public:
    constexpr static epiMetaTypeID TypeID{0xa79767ed};

    enum Color_PIDs
    {
        PID_Ru = 0xe93ba89a,
        PID_Gu = 0xde8e4e8e,
        PID_Bu = 0xa3f9bacb,
        PID_Au = 0x88d4e908,
        PID_Rf = 0x6d85e944,
        PID_Gf = 0x5a300f50,
        PID_Bf = 0x2747fb15,
        PID_Af = 0xc6aa8d6,
        PID_RGBA32 = 0x66aecff7,
        PID_BGRA32 = 0x35619af3,
        PID_RGB24 = 0x3de8f258,
        PID_BGR24 = 0x412ec6aa,
        PID_Minf = 0x50932d17,
        PID_Minu = 0xd42d6cc9,
        PID_Maxf = 0x4218c978,
        PID_Maxu = 0xc6a688a6,
        PID_Huef = 0x91855efa,
        PID_Hueu = 0x153b1f24,
        PID_Lumaf = 0x9ff8d403,
        PID_Lumau = 0x1b4695dd,
        PID_Luma601f = 0x26df340c,
        PID_Luma601u = 0xa26175d2,
        PID_Luma240f = 0xb7af3ac6,
        PID_Luma240u = 0x33117b18,
        PID_Luma709f = 0x56bad961,
        PID_Luma709u = 0xd20498bf,
        PID_Luma2020f = 0x64645ab4,
        PID_Luma2020u = 0xe0da1b6a,
        PID_Brightnessf = 0xc9956123,
        PID_Brightnessu = 0x4d2b20fd,
        PID_Lightnessf = 0xb986aa1c,
        PID_Lightnessu = 0x3d38ebc2,
        PID_Intensityf = 0x276668e0,
        PID_Intensityu = 0xa3d8293e,
        PID_Chromaf = 0x7447afaf,
        PID_Chromau = 0xf0f9ee71,
        PID_SaturationBf = 0x644bc7d1,
        PID_SaturationBu = 0xe0f5860f,
        PID_SaturationLf = 0xfac8ea5f,
        PID_SaturationLu = 0x7e76ab81,
        PID_SaturationIf = 0x87bf1e1a,
        PID_SaturationIu = 0x3015fc4,
        PID_HSBf = 0x7780d6cd,
        PID_HSBu = 0xf33e9713,
        PID_HSLf = 0xe903fb43,
        PID_HSLu = 0x6dbdba9d,
        PID_HSIf = 0x94740f06,
        PID_HSIu = 0x10ca4ed8,
        PID_Color = 0xa79767ed,
        PID_COUNT = 49
    };

protected:
    epiU8 GetRu_Callback() const;
    void SetRu_Callback(epiU8 value);
    epiU8 GetGu_Callback() const;
    void SetGu_Callback(epiU8 value);
    epiU8 GetBu_Callback() const;
    void SetBu_Callback(epiU8 value);
    epiU8 GetAu_Callback() const;
    void SetAu_Callback(epiU8 value);
    epiFloat GetRf_Callback() const;
    void SetRf_Callback(epiFloat value);
    epiFloat GetGf_Callback() const;
    void SetGf_Callback(epiFloat value);
    epiFloat GetBf_Callback() const;
    void SetBf_Callback(epiFloat value);
    epiFloat GetAf_Callback() const;
    void SetAf_Callback(epiFloat value);
    epiU32 GetRGBA32_Callback() const;
    void SetRGBA32_Callback(epiU32 value);
    epiU32 GetBGRA32_Callback() const;
    void SetBGRA32_Callback(epiU32 value);
    epiU32 GetRGB24_Callback() const;
    void SetRGB24_Callback(epiU32 value);
    epiU32 GetBGR24_Callback() const;
    void SetBGR24_Callback(epiU32 value);
    epiFloat GetMinf_Callback() const;
    epiU8 GetMinu_Callback() const;
    epiFloat GetMaxf_Callback() const;
    epiU8 GetMaxu_Callback() const;
    epiFloat GetHuef_Callback() const;
    epiU8 GetHueu_Callback() const;
    epiFloat GetLumaf_Callback() const;
    epiU8 GetLumau_Callback() const;
    epiFloat GetLuma601f_Callback() const;
    epiU8 GetLuma601u_Callback() const;
    epiFloat GetLuma240f_Callback() const;
    epiU8 GetLuma240u_Callback() const;
    epiFloat GetLuma709f_Callback() const;
    epiU8 GetLuma709u_Callback() const;
    epiFloat GetLuma2020f_Callback() const;
    epiU8 GetLuma2020u_Callback() const;
    epiFloat GetBrightnessf_Callback() const;
    epiU8 GetBrightnessu_Callback() const;
    epiFloat GetLightnessf_Callback() const;
    epiU8 GetLightnessu_Callback() const;
    epiFloat GetIntensityf_Callback() const;
    epiU8 GetIntensityu_Callback() const;
    epiFloat GetChromaf_Callback() const;
    epiU8 GetChromau_Callback() const;
    epiFloat GetSaturationBf_Callback() const;
    epiU8 GetSaturationBu_Callback() const;
    epiFloat GetSaturationLf_Callback() const;
    epiU8 GetSaturationLu_Callback() const;
    epiFloat GetSaturationIf_Callback() const;
    epiU8 GetSaturationIu_Callback() const;
    epiVec3f GetHSBf_Callback() const;
    epiVec3u8 GetHSBu_Callback() const;
    epiVec3f GetHSLf_Callback() const;
    epiVec3u8 GetHSLu_Callback() const;
    epiVec3f GetHSIf_Callback() const;
    epiVec3u8 GetHSIu_Callback() const;
    const epiVec4f& GetColor_Callback() const;
    void SetColor_Callback(const epiVec4f& value);

protected:
    epiVec4f m_Color{};

EPI_GENREGION_END(Color)
public:
    static const Color kWhite;
    static const Color kBlack;
    static const Color kDarkGray;
    static const Color kLightGray;
    static const Color kPurple;
    static const Color kMagenta;
    static const Color kLightRed;
    static const Color kDarkRed;
    static const Color kLightGreen;
    static const Color kDarkGreen;
    static const Color kLightBlue;
    static const Color kDarkBlue;

public:
    Color() = default;
    Color(const Color& rhs) = default;
    Color& operator=(const Color& rhs) = default;
    Color(Color&& rhs) = default;
    Color& operator=(Color&& rhs) = default;
    ~Color() = default;

    Color(epiFloat r, epiFloat g, epiFloat b, epiFloat a);
    Color(epiS32 r, epiS32 g, epiS32 b, epiS32 a);
    Color(epiU8 r, epiU8 g, epiU8 b, epiU8 a);
    Color(epiFloat r, epiFloat g, epiFloat b);
    Color(epiS32 r, epiS32 g, epiS32 b);
    Color(epiU8 r, epiU8 g, epiU8 b);

public:
    static Color FromHSB(const epiVec3f& hsb);
    static Color FromHSB(const epiVec3u8& hsb);
    static Color FromHSL(const epiVec3f& hsl);
    static Color FromHSL(const epiVec3u8& hsl);
    static Color FromHSI(const epiVec3f& hsi);
    static Color FromHSI(const epiVec3u8& hsi);

protected:
    epiBool Validate() const;

public:
    Color Contrast(epiS8 contrastR, epiS8 contrastG, epiS8 contrastB) const;
    Color ContrastStretch(epiU8 lowerR,
                          epiU8 upperR,
                          epiU8 lowerG,
                          epiU8 upperG,
                          epiU8 lowerB,
                          epiU8 upperB) const;

    Color& operator+=(const Color& rhs);
    Color& operator*=(const Color& rhs);

    friend Color operator+(const Color& lhs, const Color& rhs);

    friend Color operator*(const Color& lhs, const Color& rhs);
    friend Color operator*(const Color& lhs, epiFloat rhs);
    friend Color operator*(epiFloat lhs, const Color& rhs);
};

EPI_NAMESPACE_END()
