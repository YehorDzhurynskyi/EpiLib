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

    dSeries2Df series;
    series.SetWidth(kN);
    for (epiU32 i = 0; i < kN * kM; ++i)
    {
        epiFloat& x = series.PushBack();
        x = epiRand01();
    }

    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries2Df_dSeries2Dc, DFT_R2C_to_DFT_C2R_NElements10x11)
{
    constexpr epiSize_t kM = 11;
    constexpr epiSize_t kN = 10;

    dSeries2Df series;
    series.SetWidth(kN);
    for (epiU32 i = 0; i < kN * kM; ++i)
    {
        epiFloat& x = series.PushBack();
        x = epiRand01();
    }

    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries2Df_dSeries2Dc, DFT_R2C_to_DFT_C2R_NElements11x10)
{
    constexpr epiSize_t kM = 10;
    constexpr epiSize_t kN = 11;

    dSeries2Df series;
    series.SetWidth(kN);
    for (epiU32 i = 0; i < kN * kM; ++i)
    {
        epiFloat& x = series.PushBack();
        x = epiRand01();
    }

    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries2Df_dSeries2Dc, DFT_R2C_to_DFT_C2R_NElements11x11)
{
    constexpr epiSize_t kM = 11;
    constexpr epiSize_t kN = 11;

    dSeries2Df series;
    series.SetWidth(kN);
    for (epiU32 i = 0; i < kN * kM; ++i)
    {
        epiFloat& x = series.PushBack();
        x = epiRand01();
    }

    const dSeries2Df resultSeries = dSeries2Df(series).DFT_R2C().DFT_C2R(kN, kM);

    ASSERT_EQ(series, resultSeries);
}

EPI_NAMESPACE_END()
