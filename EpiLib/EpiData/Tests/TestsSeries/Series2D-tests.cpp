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

namespace
{

dSeries2Df Kernel7x7()
{
    const epiSize_t w = 7;

    dSeries2Df kernel = dSeries2Df::Full(w * w, w, 0.0f);

    for (epiU32 i = 0; i < w; ++i)
    {
        kernel.At(w / 2, i) = i < w / 2 ? -1.0f : 1.0f;
        kernel.At(i, w / 2) = i < w / 2 ? -1.0f : 1.0f;
    }

    kernel.At(w / 2, w / 2) = 0.0f;

    return kernel;
}

}

TEST(dSeries2Df, 4x4CorrelateIdentityReflect)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4CorrelateIdentityMirror)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4CorrelateIdentityNearest)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4CorrelateIdentityWrap)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4CorrelateIdentityZero)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4CorrelateIdentityFF)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4CorrelateKernel7x7Reflect)
{
    const dSeries2Df expected({15.0f, 19.0f, 19.0f, 15.0f,
                               31.0f, 35.0f, 35.0f, 31.0f,
                               31.0f, 35.0f, 35.0f, 31.0f,
                               15.0f, 19.0f, 19.0f, 15.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, 4.0f, 4.0f, 0.0f,
                               16.0f, 20.0f, 20.0f, 16.0f,
                               16.0f, 20.0f, 20.0f, 16.0f,
                               0.0f, 4.0f, 4.0f, 0.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel7x7Nearest)
{
    const dSeries2Df expected({30.0f, 32.0f, 32.0f, 30.0f,
                               38.0f, 40.0f, 40.0f, 38.0f,
                               38.0f, 40.0f, 40.0f, 38.0f,
                               30.0f, 32.0f, 32.0f, 30.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel7x7Wrap)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel7x7Zero)
{
    const dSeries2Df expected({30.0f, 32.0f, 32.0f, 30.0f,
                               38.0f, 30.0f, 20.0f, 8.0f,
                               38.0f, 20.0f, 0.0f, -22.0f,
                               30.0f, 2.0f, -28.0f, -60.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 4x4CorrelateKernel7x7FF)
{
    const dSeries2Df expected({-1500.0f, -988.0f, -478.0f, 30.0f,
                               -982.0f, -480.0f, 20.0f, 518.0f,
                               -472.0f, 20.0f, 510.0f, 998.0f,
                               30.0f, 512.0f, 992.0f, 1470.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Correlate(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

TEST(dSeries2Df, 5x5CorrelateIdentityReflect)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5CorrelateIdentityMirror)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5CorrelateIdentityNearest)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5CorrelateIdentityWrap)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5CorrelateIdentityZero)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5CorrelateIdentityFF)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5CorrelateKernel7x7Reflect)
{
    const dSeries2Df expected({18.0f, 23.0f, 25.0f, 23.0f, 18.0f,
                               43.0f, 48.0f, 50.0f, 48.0f, 43.0f,
                               53.0f, 58.0f, 60.0f, 58.0f, 53.0f,
                               43.0f, 48.0f, 50.0f, 48.0f, 43.0f,
                               18.0f, 23.0f, 25.0f, 23.0f, 18.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, 6.0f, 8.0f, 6.0f, 0.0f,
                               30.0f, 36.0f, 38.0f, 36.0f, 30.0f,
                               40.0f, 46.0f, 48.0f, 46.0f, 40.0f,
                               30.0f, 36.0f, 38.0f, 36.0f, 30.0f,
                               0.0f, 6.0f, 8.0f, 6.0f, 0.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel7x7Nearest)
{
    const dSeries2Df expected({36.0f, 39.0f, 40.0f, 39.0f, 36.0f,
                               51.0f, 54.0f, 55.0f, 54.0f, 51.0f,
                               56.0f, 59.0f, 60.0f, 59.0f, 56.0f,
                               51.0f, 54.0f, 55.0f, 54.0f, 51.0f,
                               36.0f, 39.0f, 40.0f, 39.0f, 36.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel7x7Wrap)
{
    const dSeries2Df expected({-18.0f, -13.0f, -13.0f, -13.0f, -18.0f,
                               7.0f, 12.0f, 12.0f, 12.0f, 7.0f,
                               7.0f, 12.0f, 12.0f, 12.0f, 7.0f,
                               7.0f, 12.0f, 12.0f, 12.0f, 7.0f,
                               -18.0f, -13.0f, -13.0f, -13.0f, -18.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel7x7Zero)
{
    const dSeries2Df expected({36.0f, 42.0f, 42.0f, 40.0f, 36.0f,
                               66.0f, 66.0f, 55.0f, 42.0f, 32.0f,
                               66.0f, 59.0f, 36.0f, 11.0f, -6.0f,
                               56.0f, 42.0f, 7.0f, -30.0f, -54.0f,
                               36.0f, 16.0f, -30.0f, -78.0f, -108.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 5x5CorrelateKernel7x7FF)
{
    const dSeries2Df expected({-1494.0f, -1233.0f, -723.0f, -215.0f, 36.0f,
                                -1209.0f, -954.0f, -455.0f, 42.0f, 287.0f,
                                -699.0f, -451.0f, 36.0f, 521.0f, 759.0f,
                                -199.0f, 42.0f, 517.0f, 990.0f, 1221.0f,
                                36.0f, 271.0f, 735.0f, 1197.0f, 1422.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Correlate(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

TEST(dSeries2Df, 4x4ConvolveIdentityReflect)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4ConvolveIdentityMirror)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4ConvolveIdentityNearest)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4ConvolveIdentityWrap)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4ConvolveIdentityZero)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4ConvolveIdentityFF)
{
    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(4 * 4, 4));
}

TEST(dSeries2Df, 4x4ConvolveKernel7x7Reflect)
{
    const dSeries2Df expected({-15.0f, -19.0f, -19.0f, -15.0f,
                               -31.0f, -35.0f, -35.0f, -31.0f,
                               -31.0f, -35.0f, -35.0f, -31.0f,
                               -15.0f, -19.0f, -19.0f, -15.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 4x4ConvolveKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, -4.0f, -4.0f, 0.0f,
                               -16.0f, -20.0f, -20.0f, -16.0f,
                               -16.0f, -20.0f, -20.0f, -16.0f,
                               0.0f, -4.0f, -4.0f, 0.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 4x4ConvolveKernel7x7Nearest)
{
    const dSeries2Df expected({-30.0f, -32.0f, -32.0f, -30.0f,
                               -38.0f, -40.0f, -40.0f, -38.0f,
                               -38.0f, -40.0f, -40.0f, -38.0f,
                               -30.0f, -32.0f, -32.0f, -30.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 4x4ConvolveKernel7x7Wrap)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 4x4ConvolveKernel7x7Zero)
{
    const dSeries2Df expected({-30.0f, -32.0f, -32.0f, -30.0f,
                               -38.0f, -30.0f, -20.0f, -8.0f,
                               -38.0f, -20.0f, 0.0f, 22.0f,
                               -30.0f, -2.0f, 28.0f, 60.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 4x4ConvolveKernel7x7FF)
{
    const dSeries2Df expected({1500.0f, 988.0f, 478.0f, -30.0f,
                               982.0f, 480.0f, -20.0f, -518.0f,
                               472.0f, -20.0f, -510.0f, -998.0f,
                               -30.0f, -512.0f, -992.0f, -1470.0f}, 4);

    EXPECT_EQ(dSeries2Df::Arange(4 * 4, 4).Convolve(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

TEST(dSeries2Df, 5x5ConvolveIdentityReflect)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5ConvolveIdentityMirror)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5ConvolveIdentityNearest)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5ConvolveIdentityWrap)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5ConvolveIdentityZero)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5ConvolveIdentityFF)
{
    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(5 * 5, 5));
}

TEST(dSeries2Df, 5x5ConvolveKernel7x7Reflect)
{
    const dSeries2Df expected({-18.0f, -23.0f, -25.0f, -23.0f, -18.0f,
                               -43.0f, -48.0f, -50.0f, -48.0f, -43.0f,
                               -53.0f, -58.0f, -60.0f, -58.0f, -53.0f,
                               -43.0f, -48.0f, -50.0f, -48.0f, -43.0f,
                               -18.0f, -23.0f, -25.0f, -23.0f, -18.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST(dSeries2Df, 5x5ConvolveKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, -6.0f, -8.0f, -6.0f, 0.0f,
                               -30.0f, -36.0f, -38.0f, -36.0f, -30.0f,
                               -40.0f, -46.0f, -48.0f, -46.0f, -40.0f,
                               -30.0f, -36.0f, -38.0f, -36.0f, -30.0f,
                               0.0f, -6.0f, -8.0f, -6.0f, 0.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST(dSeries2Df, 5x5ConvolveKernel7x7Nearest)
{
    const dSeries2Df expected({-36.0f, -39.0f, -40.0f, -39.0f, -36.0f,
                               -51.0f, -54.0f, -55.0f, -54.0f, -51.0f,
                               -56.0f, -59.0f, -60.0f, -59.0f, -56.0f,
                               -51.0f, -54.0f, -55.0f, -54.0f, -51.0f,
                               -36.0f, -39.0f, -40.0f, -39.0f, -36.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST(dSeries2Df, 5x5ConvolveKernel7x7Wrap)
{
    const dSeries2Df expected({18.0f, 13.0f, 13.0f, 13.0f, 18.0f,
                               -7.0f, -12.0f, -12.0f, -12.0f, -7.0f,
                               -7.0f, -12.0f, -12.0f, -12.0f, -7.0f,
                               -7.0f, -12.0f, -12.0f, -12.0f, -7.0f,
                               18.0f, 13.0f, 13.0f, 13.0f, 18.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST(dSeries2Df, 5x5ConvolveKernel7x7Zero)
{
    const dSeries2Df expected({-36.0f, -42.0f, -42.0f, -40.0f, -36.0f,
                               -66.0f, -66.0f, -55.0f, -42.0f, -32.0f,
                               -66.0f, -59.0f, -36.0f, -11.0f, 6.0f,
                               -56.0f, -42.0f, -7.0f, 30.0f, 54.0f,
                               -36.0f, -16.0f, 30.0f, 78.0f, 108.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST(dSeries2Df, 5x5ConvolveKernel7x7FF)
{
    const dSeries2Df expected({1494.0f, 1233.0f, 723.0f, 215.0f, -36.0f,
                               1209.0f, 954.0f, 455.0f, -42.0f, -287.0f,
                               699.0f, 451.0f, -36.0f, -521.0f, -759.0f,
                               199.0f, -42.0f, -517.0f, -990.0f, -1221.0f,
                               -36.0f, -271.0f, -735.0f, -1197.0f, -1422.0f}, 5);

    EXPECT_EQ(dSeries2Df::Arange(5 * 5, 5).Convolve(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

EPI_NAMESPACE_END()
