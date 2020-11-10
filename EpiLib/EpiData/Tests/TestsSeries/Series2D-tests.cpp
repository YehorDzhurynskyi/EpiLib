#include <gtest/gtest.h>

#include "EpiData/Series/dSeries2Df.h"
#include "EpiData/Series/dSeries2Dc.h"

namespace
{

constexpr epiFloat kDFTTolerance = 1.0e-4f;

}

EPI_NAMESPACE_BEGIN()

TEST(dSeries2Df, DFT_R2C_Empty)
{
    const dSeries2Dc X = dSeries2Df().DFT_R2C();
    EXPECT_EQ(X.GetSize(), 0);
    EXPECT_EQ(X.GetWidth(), 0);
}

TEST(dSeries2Df, DFT_R2C_EmptyWidth)
{
    const dSeries2Dc X = dSeries2Df({1.0f, 2.0f, 3.0f}, 0).DFT_R2C();
    EXPECT_EQ(X.GetSize(), 0);
    EXPECT_EQ(X.GetWidth(), 0);
}

TEST(dSeries2Df, DFT_R2C_EmptyHeight)
{
    const dSeries2Dc X = dSeries2Df({}, 5).DFT_R2C();
    EXPECT_EQ(X.GetSize(), 0);
    EXPECT_EQ(X.GetWidth(), 0);
}

TEST(dSeries2Df, DFT_R2C_DCComponent)
{
    const epiComplexf expectedValue[]{{2295.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}};
    const epiFloat expectedAbs[]{2295.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    const epiFloat expectedTheta[]{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    const dSeries2Dc X = dSeries2Df({255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f}, 3).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Df, DFT_R2C_NElements1x1)
{
    const epiComplexf expectedValue[]{{255.0f, 0.0f}};
    const epiFloat expectedAbs[]{255.0f};
    const epiFloat expectedTheta[]{0.0f};

    const dSeries2Dc X = dSeries2Df({255.0f}, 1).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Df, DFT_R2C_NElements2x1)
{
    const epiComplexf expectedValue[]{{ 383.0f, 0.0f }, { -127.0f, 0.0f }};
    const epiFloat expectedAbs[]{383.0f, 127.0f};
    const epiFloat expectedTheta[]{0.0f, M_PI};

    const dSeries2Dc X = dSeries2Df({128.0f, 255.0f}, 2).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Df, DFT_R2C_NElements1x2)
{
    const epiComplexf expectedValue[]{{ 383.0f, 0.0f }, { -127.0f, 0.0f }};
    const epiFloat expectedAbs[]{383.0f, 127.0f};
    const epiFloat expectedTheta[]{0.0f, M_PI};

    const dSeries2Dc X = dSeries2Df({128.0f, 255.0f}, 1).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Df, DFT_R2C_NElements2x2)
{
    const epiComplexf expectedValue[]{{ 455.0f, 0.0f }, { -199.0f, 0.0f }, { 311.0f, 0.0f }, { -55.0f, 0.0f }};
    const epiFloat expectedAbs[]{455.0f, 199.0f, 311.0f, 55.0f};
    const epiFloat expectedTheta[]{0.0f, M_PI, 0.0f, M_PI};

    const dSeries2Dc X = dSeries2Df({128.0f, 255.0f, 0.0f, 72.0f}, 2).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Df, DFT_R2C_NElements3x3)
{
    const epiComplexf expectedValue[]{{ 880.0f, 0.0f },
                                      { -140.0f, -386.24733f },
                                      { 134.5f, 42.43524f },
                                      { 283.0f, -252.8794179f },
                                      { 134.5f, -42.43524f },
                                      { -141.5f, -23.38268f }};
    const epiFloat expectedAbs[]{880.0f, 410.83695f, 141.035456f, 379.52206787f, 141.03545653f, 143.41896667f};
    const epiFloat expectedTheta[]{0.0f, -1.91852977f, 0.30561897f, -0.72924948f, -0.30561897f, -2.97782397f};

    const dSeries2Dc X = dSeries2Df({128.0f, 255.0f, 0.0f, 72.0f, 53.0f, 99.0f, 0.0f, 255.0f, 18.0f}, 3).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Df, DFT_R2C_NElements3x4)
{
    const epiComplexf expectedValue[]{{ 1091.0f, 0.0f },
                                      { -79.0f, -471.1178196f },
                                      { 110.0f, -13.0f },
                                      { 261.70765814f, 49.4115427f },
                                      { 221.0f, 0.0f },
                                      { -193.0f, -381.0511776f },
                                      { 110.0f, 13.0f },
                                      { 12.292341f, -80.58845f }};
    const epiFloat expectedAbs[]{1091.0f, 477.69550971f, 110.7655181f, 266.33137045f, 221.0f, 427.14049211f, 110.7655181f, 81.52055638f};
    const epiFloat expectedTheta[]{0.0f, -1.73693691f, -0.11763617f, 0.1866077f, 0.0f, -2.03962535f, 0.11763617f, -1.41943074f};

    const dSeries2Dc X = dSeries2Df({128.0f, 255.0f, 0.0f, 72.0f, 53.0f, 99.0f, 0.0f, 255.0f, 18.0f, 111.0f, 99.0f, 1.0f}, 3).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Df, DFT_R2C_NElements4x3)
{
    const epiComplexf expectedValue[]{{ 1091.0f, 0.0f },
                                      { 100.0f, -137.0f },
                                      { -495.0f, 0.0f },
                                      { 137.0f, -154.15252187f },
                                      { 372.36275741f, -322.04740411f },
                                      { -51.0f, 265.00377356f },
                                      { 137.0f, 154.15252187f },
                                      { -88.36275741f, -89.95259589f },
                                      { -51.0f, -265.00377356f }};
    const epiFloat expectedAbs[]{1091.0f, 169.61426827f, 495.0f, 206.23287808f, 492.3094084f, 269.86663373f, 206.23287808f, 126.09300696f, 269.86663373f};
    const epiFloat expectedTheta[]{0.0f, -0.94026619f, M_PI, -0.84424265f, -0.71306688f, 1.76092193f, 0.84424265f, -2.34727885f, -1.76092193f};

    const dSeries2Dc X = dSeries2Df({128.0f, 255.0f, 0.0f, 72.0f, 53.0f, 99.0f, 0.0f, 255.0f, 18.0f, 111.0f, 99.0f, 1.0f}, 4).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        const epiU32 r = i / X.GetWidth();
        const epiU32 c = i % X.GetWidth();

        EXPECT_TRUE(epiFloatingEqEx(X.At(r, c), expectedValue[i], kDFTTolerance));
        EXPECT_NEAR(X.AtAbs(r, c), expectedAbs[i], kDFTTolerance);
        EXPECT_NEAR(X.AtTheta(r, c), expectedTheta[i], kDFTTolerance);
    }
}

TEST(dSeries2Dc, DFT_C2R_Empty)
{
    const dSeries2Df y = dSeries2Dc().DFT_C2R();
    EXPECT_EQ(y.GetSize(), 0);
    EXPECT_EQ(y.GetWidth(), 0);
}

TEST(dSeries2Dc, DFT_C2R_EmptyWidth)
{
    const dSeries2Df y = dSeries2Dc({1.0f, 2.0f, 3.0f}, 0).DFT_C2R();
    EXPECT_EQ(y.GetSize(), 0);
    EXPECT_EQ(y.GetWidth(), 0);
}

TEST(dSeries2Dc, DFT_C2R_EmptyHeight)
{
    const dSeries2Df y = dSeries2Dc({}, 5).DFT_C2R();
    EXPECT_EQ(y.GetSize(), 0);
    EXPECT_EQ(y.GetWidth(), 0);
}

TEST(dSeries2Dc, DFT_C2R_DCComponent)
{
    const epiFloat expectedValue[]{255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f, 255.0f};

    const dSeries2Df y = dSeries2Dc({{2295.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}}, 2).DFT_C2R(3, 3);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Dc, DFT_C2R_NElements1x1)
{
    const epiFloat expectedValue[]{255.0f};

    const dSeries2Df y = dSeries2Dc({{255.0f, 0.0f}}, 1).DFT_C2R(1, 1);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Dc, DFT_C2R_NElements2x1)
{
    const epiFloat expectedValue[]{128.0f, 255.0f};

    const dSeries2Df y = dSeries2Dc({{ 383.0f, 0.0f }, { -127.0f, 0.0f }}, 2).DFT_C2R();

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Dc, DFT_C2R_NElements1x2)
{
    const epiFloat expectedValue[]{128.0f, 255.0f};

    const dSeries2Df y = dSeries2Dc({{ 383.0f, 0.0f }, { -127.0f, 0.0f }}, 1).DFT_C2R(1, 2);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Dc, DFT_C2R_NElements2x2)
{
    const epiFloat expectedValue[]{128.0f, 255.0f, 0.0f, 72.0f};

    const dSeries2Df y = dSeries2Dc({{ 455.0f, 0.0f }, { -199.0f, 0.0f }, { 311.0f, 0.0f }, { -55.0f, 0.0f }}, 2).DFT_C2R();

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Dc, DFT_C2R_NElements3x3)
{
    const epiFloat expectedValue[]{128.0f, 255.0f, 0.0f, 72.0f, 53.0f, 99.0f, 0.0f, 255.0f, 18.0f};

    const dSeries2Df y = dSeries2Dc({{ 880.0f, 0.0f },
                                      { -140.0f, -386.24733f },
                                      { 134.5f, 42.43524f },
                                      { 283.0f, -252.8794179f },
                                      { 134.5f, -42.43524f },
                                      { -141.5f, -23.38268f }}, 2).DFT_C2R(3, 3);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Dc, DFT_C2R_NElements3x4)
{
    const epiFloat expectedValue[]{128.0f, 255.0f, 0.0f, 72.0f, 53.0f, 99.0f, 0.0f, 255.0f, 18.0f, 111.0f, 99.0f, 1.0f};

    const dSeries2Df y = dSeries2Dc({{ 1091.0f, 0.0f },
                                      { -79.0f, -471.1178196f },
                                      { 110.0f, -13.0f },
                                      { 261.70765814f, 49.4115427f },
                                      { 221.0f, 0.0f },
                                      { -193.0f, -381.0511776f },
                                      { 110.0f, 13.0f },
                                      { 12.292341f, -80.58845f }}, 2).DFT_C2R(3, 4);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Dc, DFT_C2R_NElements4x3)
{
    const epiFloat expectedValue[]{128.0f, 255.0f, 0.0f, 72.0f, 53.0f, 99.0f, 0.0f, 255.0f, 18.0f, 111.0f, 99.0f, 1.0f};

    const dSeries2Df y = dSeries2Dc({{ 1091.0f, 0.0f },
                                      { 100.0f, -137.0f },
                                      { -495.0f, 0.0f },
                                      { 137.0f, -154.15252187f },
                                      { 372.36275741f, -322.04740411f },
                                      { -51.0f, 265.00377356f },
                                      { 137.0f, 154.15252187f },
                                      { -88.36275741f, -89.95259589f },
                                      { -51.0f, -265.00377356f }}, 3).DFT_C2R();

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df_dSeries2Dc, DFT_R2C_to_DFT_C2R_NElements10x10)
{
    constexpr epiSize_t kM = 10;
    constexpr epiSize_t kN = 10;

    const dSeries2Df series = dSeries2Df::Rand(kM * kN, kN);
    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries2Df_dSeries2Dc, DFT_R2C_to_DFT_C2R_NElements10x11)
{
    constexpr epiSize_t kM = 11;
    constexpr epiSize_t kN = 10;

    const dSeries2Df series = dSeries2Df::Rand(kM * kN, kN);
    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries2Df_dSeries2Dc, DFT_R2C_to_DFT_C2R_NElements11x10)
{
    constexpr epiSize_t kM = 10;
    constexpr epiSize_t kN = 11;

    const dSeries2Df series = dSeries2Df::Rand(kM * kN, kN);
    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries2Df_dSeries2Dc, DFT_R2C_to_DFT_C2R_NElements11x11)
{
    constexpr epiSize_t kM = 11;
    constexpr epiSize_t kN = 11;

    const dSeries2Df series = dSeries2Df::Rand(kM * kN, kN);
    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries2Df, DFT_Shift_NElements0x0)
{
    EXPECT_EQ(dSeries2Df().DFT_Shift().GetSize(), 0);
}

TEST(dSeries2Df, DFT_Shift_NElements1x1)
{
    const epiFloat expectedValue[]{1.0f};

    const dSeries2Df shift = dSeries2Df({1.0f}, 1).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_Shift_NElements2x2)
{
    const epiFloat expectedValue[]{4.0f, 3.0f, 2.0f, 1.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f}, 2).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_Shift_NElements2x3)
{
    const epiFloat expectedValue[]{6.0f, 5.0f, 2.0f, 1.0f, 4.0f, 3.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}, 2).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_Shift_NElements3x2)
{
    const epiFloat expectedValue[]{6.0f, 4.0f, 5.0f, 3.0f, 1.0f, 2.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}, 3).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_Shift_NElements4x4)
{
    const epiFloat expectedValue[]{11.0f, 12.0f, 9.0f, 10.0f,
                                   15.0f, 16.0f, 13.0f, 14.0f,
                                   3.0f, 4.0f, 1.0f, 2.0f,
                                   7.0f, 8.0f, 5.0f, 6.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f,
                                         5.0f, 6.0f, 7.0f, 8.0f,
                                         9.0f, 10.0f, 11.0f, 12.0f,
                                         13.0f, 14.0f, 15.0f, 16.0f}, 4).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_Shift_NElements5x5)
{
    const epiFloat expectedValue[]{19.0f, 20.0f, 16.0f, 17.0f, 18.0f,
                                   24.0f, 25.0f, 21.0f, 22.0f, 23.0f,
                                   4.0f, 5.0f, 1.0f, 2.0f, 3.0f,
                                   9.0f, 10.0f, 6.0f, 7.0f, 8.0f,
                                   14.0f, 15.0f, 11.0f, 12.0f, 13.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                         6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                                         11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                                         16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                         21.0f, 22.0f, 23.0f, 24.0f, 25.0f}, 5).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IShift_NElements0x0)
{
    EXPECT_EQ(dSeries2Df().DFT_IShift().GetSize(), 0);
}

TEST(dSeries2Df, DFT_IShift_NElements1x1)
{
    const epiFloat expectedValue[]{1.0f};

    const dSeries2Df shift = dSeries2Df({1.0f}, 1).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IShift_NElements2x2)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f};

    const dSeries2Df shift = dSeries2Df({4.0f, 3.0f, 2.0f, 1.0f}, 2).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IShift_NElements2x3)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};

    const dSeries2Df shift = dSeries2Df({6.0f, 5.0f, 2.0f, 1.0f, 4.0f, 3.0f}, 2).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IShift_NElements3x2)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};

    const dSeries2Df shift = dSeries2Df({6.0f, 4.0f, 5.0f, 3.0f, 1.0f, 2.0f}, 3).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IShift_NElements4x4)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f,
                                   5.0f, 6.0f, 7.0f, 8.0f,
                                   9.0f, 10.0f, 11.0f, 12.0f,
                                   13.0f, 14.0f, 15.0f, 16.0f};

    const dSeries2Df shift = dSeries2Df({11.0f, 12.0f, 9.0f, 10.0f,
                                         15.0f, 16.0f, 13.0f, 14.0f,
                                         3.0f, 4.0f, 1.0f, 2.0f,
                                         7.0f, 8.0f, 5.0f, 6.0f}, 4).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IShift_NElements5x5)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                   6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                                   11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                                   16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                   21.0f, 22.0f, 23.0f, 24.0f, 25.0f};

    const dSeries2Df shift = dSeries2Df({19.0f, 20.0f, 16.0f, 17.0f, 18.0f,
                                         24.0f, 25.0f, 21.0f, 22.0f, 23.0f,
                                         4.0f, 5.0f, 1.0f, 2.0f, 3.0f,
                                         9.0f, 10.0f, 6.0f, 7.0f, 8.0f,
                                         14.0f, 15.0f, 11.0f, 12.0f, 13.0f}, 5).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_RShift_NElements0x0)
{
    EXPECT_EQ(dSeries2Df().DFT_RShift().GetSize(), 0);
}

TEST(dSeries2Df, DFT_RShift_NElements1x1)
{
    const epiFloat expectedValue[]{1.0f};

    const dSeries2Df shift = dSeries2Df({1.0f}, 1).DFT_RShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_RShift_NElements2x2)
{
    const epiFloat expectedValue[]{3.0f, 4.0f, 1.0f, 2.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f}, 2).DFT_RShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_RShift_NElements2x3)
{
    const epiFloat expectedValue[]{5.0f, 6.0f, 1.0f, 2.0f, 3.0f, 4.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}, 2).DFT_RShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_RShift_NElements3x2)
{
    const epiFloat expectedValue[]{4.0f, 5.0f, 6.0f, 1.0f, 2.0f, 3.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f}, 3).DFT_RShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_RShift_NElements4x4)
{
    const epiFloat expectedValue[]{9.0f, 10.0f, 11.0f, 12.0f,
                                   13.0f, 14.0f, 15.0f, 16.0f,
                                   1.0f, 2.0f, 3.0f, 4.0f,
                                   5.0f, 6.0f, 7.0f, 8.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f,
                                         5.0f, 6.0f, 7.0f, 8.0f,
                                         9.0f, 10.0f, 11.0f, 12.0f,
                                         13.0f, 14.0f, 15.0f, 16.0f}, 4).DFT_RShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_RShift_NElements5x5)
{
    const epiFloat expectedValue[]{16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                   21.0f, 22.0f, 23.0f, 24.0f, 25.0f,
                                   1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                   6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                                   11.0f, 12.0f, 13.0f, 14.0f, 15.0f};

    const dSeries2Df shift = dSeries2Df({1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                         6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                                         11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                                         16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                         21.0f, 22.0f, 23.0f, 24.0f, 25.0f}, 5).DFT_RShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IRShift_NElements0x0)
{
    EXPECT_EQ(dSeries2Df().DFT_IRShift().GetSize(), 0);
}

TEST(dSeries2Df, DFT_IRShift_NElements1x1)
{
    const epiFloat expectedValue[]{1.0f};

    const dSeries2Df shift = dSeries2Df({1.0f}, 1).DFT_IRShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IRShift_NElements2x2)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f};

    const dSeries2Df shift = dSeries2Df({3.0f, 4.0f, 1.0f, 2.0f}, 2).DFT_IRShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IRShift_NElements2x3)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};

    const dSeries2Df shift = dSeries2Df({5.0f, 6.0f, 1.0f, 2.0f, 3.0f, 4.0f}, 2).DFT_IRShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IRShift_NElements3x2)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};

    const dSeries2Df shift = dSeries2Df({4.0f, 5.0f, 6.0f, 1.0f, 2.0f, 3.0f}, 3).DFT_IRShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IRShift_NElements4x4)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f,
                                   5.0f, 6.0f, 7.0f, 8.0f,
                                   9.0f, 10.0f, 11.0f, 12.0f,
                                   13.0f, 14.0f, 15.0f, 16.0f};

    const dSeries2Df shift = dSeries2Df({9.0f, 10.0f, 11.0f, 12.0f,
                                         13.0f, 14.0f, 15.0f, 16.0f,
                                         1.0f, 2.0f, 3.0f, 4.0f,
                                         5.0f, 6.0f, 7.0f, 8.0f}, 4).DFT_IRShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, DFT_IRShift_NElements5x5)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                   6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                                   11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                                   16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                   21.0f, 22.0f, 23.0f, 24.0f, 25.0f};

    const dSeries2Df shift = dSeries2Df({16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                         21.0f, 22.0f, 23.0f, 24.0f, 25.0f,
                                         1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                         6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                                         11.0f, 12.0f, 13.0f, 14.0f, 15.0f}, 5).DFT_IRShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries2Df, 4x4CorrelateIdentityReflect)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 4x4CorrelateIdentityMirror)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 4x4CorrelateIdentityNearest)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 4x4CorrelateIdentityWrap)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 4x4CorrelateIdentityZero)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 4x4CorrelateIdentityFF)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::FF), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel3x3Reflect)
{
    const dSeries2Df expected({5.0f, 9.0f, 14.0f, 18.0f,
                               21.0f, 25.0f, 30.0f, 34.0f,
                               41.0f, 45.0f, 50.0f, 54.0f,
                               57.0f, 61.0f, 66.0f, 70.0f}, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel3x3Mirror)
{
    const dSeries2Df expected({10.0f, 13.0f, 18.0f, 21.0f,
                               22.0f, 25.0f, 30.0f, 33.0f,
                               42.0f, 45.0f, 50.0f, 53.0f,
                               54.0f, 57.0f, 62.0f, 65.0f}, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel3x3Nearest)
{
    const dSeries2Df expected({5.0f, 9.0f, 14.0f, 18.0f,
                               21.0f, 25.0f, 30.0f, 34.0f,
                               41.0f, 45.0f, 50.0f, 54.0f,
                               57.0f, 61.0f, 66.0f, 70.0f}, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel3x3Wrap)
{
    const dSeries2Df expected({20.0f, 21.0f, 26.0f, 27.0f,
                               24.0f, 25.0f, 30.0f, 31.0f,
                               44.0f, 45.0f, 50.0f, 51.0f,
                               48.0f, 49.0f, 54.0f, 55.0f}, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel3x3Zero)
{
    const dSeries2Df expected({5.0f, 8.0f, 12.0f, 12.0f,
                               17.0f, 25.0f, 30.0f, 27.0f,
                               33.0f, 45.0f, 50.0f, 43.0f,
                               33.0f, 48.0f, 52.0f, 40.0f}, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel3x3FF)
{
    const dSeries2Df expected({515.0f, 263.0f, 267.0f, 522.0f,
                               272.0f, 25.0f, 30.0f, 282.0f,
                               288.0f, 45.0f, 50.0f, 298.0f,
                               543.0f, 303.0f, 307.0f, 550.0f}, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(kernel, dSeriesEdgeHandling::FF), expected);
}

TEST(dSeries2Df, 5x5CorrelateIdentityReflect)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 5x5CorrelateIdentityMirror)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 5x5CorrelateIdentityNearest)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 5x5CorrelateIdentityWrap)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 5x5CorrelateIdentityZero)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 5x5CorrelateIdentityFF)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::FF), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel3x3Reflect)
{
    const dSeries2Df expected({6.0f, 10.0f, 15.0f, 20.0f, 24.0f,
                               26.0f, 30.0f, 35.0f, 40.0f, 44.0f,
                               51.0f, 55.0f, 60.0f, 65.0f, 69.0f,
                               76.0f, 80.0f, 85.0f, 90.0f, 94.0f,
                               96.0f, 100.0f, 105.0f, 110.0f, 114.0f}, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel3x3Mirror)
{
    const dSeries2Df expected({12.0f, 15.0f, 20.0f, 25.0f, 28.0f,
                               27.0f, 30.0f, 35.0f, 40.0f, 43.0f,
                               52.0f, 55.0f, 60.0f, 65.0f, 68.0f,
                               77.0f, 80.0f, 85.0f, 90.0f, 93.0f,
                               92.0f, 95.0f, 100.0f, 105.0f, 108.0f}, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel3x3Nearest)
{
    const dSeries2Df expected({6.0f, 10.0f, 15.0f, 20.0f, 24.0f,
                               26.0f, 30.0f, 35.0f, 40.0f, 44.0f,
                               51.0f, 55.0f, 60.0f, 65.0f, 69.0f,
                               76.0f, 80.0f, 85.0f, 90.0f, 94.0f,
                               96.0f, 100.0f, 105.0f, 110.0f, 114.0f}, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel3x3Wrap)
{
    const dSeries2Df expected({30.0f, 30.0f, 35.0f, 40.0f, 40.0f,
                               30.0f, 30.0f, 35.0f, 40.0f, 40.0f,
                               55.0f, 55.0f, 60.0f, 65.0f, 65.0f,
                               80.0f, 80.0f, 85.0f, 90.0f, 90.0f,
                               80.0f, 80.0f, 85.0f, 90.0f, 90.0f}, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel3x3Zero)
{
    const dSeries2Df expected({6.0f, 9.0f, 13.0f, 17.0f, 16.0f,
                               21.0f, 30.0f, 35.0f, 40.0f, 35.0f,
                               41.0f, 55.0f, 60.0f, 65.0f, 55.0f,
                               61.0f, 80.0f, 85.0f, 90.0f, 75.0f,
                               56.0f, 79.0f, 83.0f, 87.0f, 66.0f}, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel3x3FF)
{
    const dSeries2Df expected({516.0f, 264.0f, 268.0f, 272.0f, 526.0f,
                               276.0f, 30.0f, 35.0f, 40.0f, 290.0f,
                               296.0f, 55.0f, 60.0f, 65.0f, 310.0f,
                               316.0f, 80.0f, 85.0f, 90.0f, 330.0f,
                               566.0f, 334.0f, 338.0f, 342.0f, 576.0f}, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(kernel, dSeriesEdgeHandling::FF), expected);
}

EPI_NAMESPACE_END()
