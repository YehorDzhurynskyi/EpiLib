#include <gtest/gtest.h>

#include "EpiData/Series/dSeries1Df.h"
#include "EpiData/Series/dSeries1Dc.h"

EPI_NAMESPACE_BEGIN()

TEST(dSeries1Df, DFT_R2C_Empty)
{
    const dSeries1Dc X = dSeries1Df({}).DFT_R2C();
    EXPECT_EQ(X.GetSize(), 0);
}

TEST(dSeries1Df, DFT_R2C_DCComponent)
{
    const epiComplexf expectedValue[]{{ 4.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }};
    const epiFloat expectedAbs[]{4.0f, 0.0f, 0.0f};
    const epiFloat expectedTheta[]{0.0f, 0.0f, 0.0f};

    const dSeries1Dc X = dSeries1Df({1.0f, 1.0f, 1.0f, 1.0f}).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.At(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_R2C_NElements1)
{
    const epiComplexf expectedValue[]{{1.0f, 0.0f}};
    const epiFloat expectedAbs[]{1.0f};
    const epiFloat expectedTheta[]{0.0f};

    const dSeries1Dc X = dSeries1Df({1.0f}).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.At(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_R2C_NElements2)
{
    const epiComplexf expectedValue[]{{ 3.0f, 0.0f }, { -1.0f, 0.0f }};
    const epiFloat expectedAbs[]{3.0f, 1.0f};
    const epiFloat expectedTheta[]{0.0f, M_PI};

    const dSeries1Dc X = dSeries1Df({1.0f, 2.0f}).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.At(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_R2C_NElements3)
{
    const epiComplexf expectedValue[]{{ 6.0f, 0.0f }, { -1.5f, 0.8660254f }};
    const epiFloat expectedAbs[]{6.0f, 1.73205081f};
    const epiFloat expectedTheta[]{0.0f, 2.61799388};

    const dSeries1Dc X = dSeries1Df({1.0f, 2.0f, 3.0f}).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.At(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_R2C_SequencePositive)
{
    const epiComplexf expectedValue[]{{ 10.0f, 0.0f }, { -2.0f, 2.0f }, { -2.0f, 0.0f }};
    const epiFloat expectedAbs[]{10.0f, 2.0f * std::sqrt(2.0f), 2.0f};
    const epiFloat expectedTheta[]{0.0f, -M_PI_4 + M_PI, M_PI};

    const dSeries1Dc X = dSeries1Df({1.0f, 2.0f, 3.0f, 4.0f}).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.At(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_R2C_SequenceNegative)
{
    const epiComplexf expectedValue[]{{ -10.0f, 0.0f }, { 2.0f, -2.0f }, { 2.0f, 0.0f }};
    const epiFloat expectedAbs[]{10.0f, 2.0f * std::sqrt(2.0f), 2.0f};
    const epiFloat expectedTheta[]{M_PI, -M_PI_4, 0.0f};

    const dSeries1Dc X = dSeries1Df({-1.0f, -2.0f, -3.0f, -4.0f}).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.At(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_R2C_SequencePositiveNegative)
{
    const epiComplexf expectedValue[]{{ 4.0f, 0.0f }, { 4.14459608f, 0.05189464f }, { 3.65010441f, 13.94691472f }, { -13.29470049f, -3.19857416f }};
    const epiFloat expectedAbs[]{4.0f, 4.14492096f, 14.41664637f, 13.67406076f};
    const epiFloat expectedTheta[]{0.0f, 0.01252038f, 1.31482336f, -2.90548973f};

    const dSeries1Dc X = dSeries1Df({-1.0f, 1.0f, -2.0f, 5.0f, -3.0f, -4.0f, 8.0f}).DFT_R2C();

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.At(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, Theta)
{
    // NOTE: ref https://en.wikipedia.org/wiki/Atan2

    const epiComplexf c[]{
        { 1.0f, 1.0f },
        { 1.0f, -1.0f },
        { 1.0f, 0.0f },
        { -1.0f, 0.0f },
        { -1.0f, 1.0f },
        { -1.0f, -1.0f },
        { 0.0f, 1.0f },
        { 0.0f, -1.0f },
        { 0.0f, 0.0f },
        { 2.6e-15f, 0.0f },
        { 0.0f, 2.6e-15f },
        { -2.6e-15f, 0.0f },
        { 0.0f, -2.6e-15f },
        { 1.3e-7f, 0.0f },
        { 0.0f, 1.3e-7f },
        { -1.3e-7f, 0.0f },
        { 0.0f, -1.3e-7f }
    };

    const epiFloat expected[]{
        std::atan(1.0f / 1.0f),
        std::atan(-1.0f / 1.0f),
        std::atan(0.0f / 1.0f),
        std::atan(0.0f / -1.0f) + M_PI,
        std::atan(1.0f / -1.0f) + M_PI,
        std::atan(-1.0f / -1.0f) - M_PI,
        M_PI_2,
        -M_PI_2,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };

    ASSERT_EQ(epiArrLen(c), epiArrLen(expected));

    for (epiU32 i = 0; i < epiArrLen(c); ++i)
    {
        const epiFloat theta = dSeries1Dc{c[i]}.AtTheta(0);
        EXPECT_NEAR(theta, expected[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, DFT_C2R_Empty)
{
    const dSeries1Df y = dSeries1Dc({}).DFT_C2R();
    EXPECT_EQ(y.GetSize(), 0);
}

TEST(dSeries1Dc, DFT_C2R_DCComponent)
{
    const epiFloat expectedValue[]{1.0f, 1.0f, 1.0f, 1.0f};

    const dSeries1Df y = dSeries1Dc({{ 4.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }}).DFT_C2R();

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, DFT_C2R_NElements1)
{
    const epiFloat expectedValue[]{1.0f};

    const dSeries1Df y = dSeries1Dc({{ 1.0f, 0.0f }}).DFT_C2R(1);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, DFT_C2R_NElements2)
{
    const epiFloat expectedValue[]{1.0f, 2.0f};

    const dSeries1Df y = dSeries1Dc({{ 3.0f, 0.0f }, { -1.0f, 0.0f }}).DFT_C2R();

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, DFT_C2R_NElements3)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f};

    const dSeries1Df y = dSeries1Dc({{ 6.0f, 0.0f }, { -1.5f, 0.8660254f }}).DFT_C2R(3);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, DFT_C2R_SequencePositive)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f};

    const dSeries1Df y = dSeries1Dc({{ 10.0f, 0.0f }, { -2.0f, 2.0f }, { -2.0f, 0.0f }}).DFT_C2R();

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, DFT_C2R_SequenceNegative)
{
    const epiFloat expectedValue[]{-1.0f, -2.0f, -3.0f, -4.0f};

    const dSeries1Df y = dSeries1Dc({{ -10.0f, 0.0f }, { 2.0f, -2.0f }, { 2.0f, 0.0f }}).DFT_C2R();

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Dc, DFT_C2R_SequencePositiveNegative)
{
    const epiFloat expectedValue[]{-1.0f, 1.0f, -2.0f, 5.0f, -3.0f, -4.0f, 8.0f};

    const dSeries1Df y = dSeries1Dc({{ 4.0f, 0.0f }, { 4.14459608f, 0.05189464f }, { 3.65010441f, 13.94691472f }, { -13.29470049f, -3.19857416f }}).DFT_C2R(7);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df_dSeries1Dc, DFT_R2C_to_DFT_C2R_NElements100)
{
    constexpr epiSize_t kN = 100;

    const dSeries1Df series = dSeries1Df::Rand(kN);
    const dSeries1Df resultSeries = dSeries1Df(series).DFT_R2C().DFT_C2R(kN);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries1Df_dSeries1Dc, DFT_R2C_to_DFT_C2R_NElements101)
{
    constexpr epiSize_t kN = 101;

    const dSeries1Df series = dSeries1Df::Rand(kN);
    const dSeries1Df resultSeries = dSeries1Df(series).DFT_R2C().DFT_C2R(kN);

    ASSERT_EQ(series, resultSeries);
}

TEST(dSeries1Df, DFT_Shift_NElements0)
{
    EXPECT_EQ(dSeries1Df().DFT_Shift().GetSize(), 0);
}

TEST(dSeries1Df, DFT_Shift_NElements1)
{
    const epiFloat expectedValue[]{1.0f};

    const dSeries1Df shift = dSeries1Df({1.0f}).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_Shift_NElements2)
{
    const epiFloat expectedValue[]{2.0f, 1.0f};

    const dSeries1Df shift = dSeries1Df({1.0f, 2.0f}).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_Shift_NElements4)
{
    const epiFloat expectedValue[]{3.0f, 4.0f, 1.0f, 2.0f};

    const dSeries1Df shift = dSeries1Df({1.0f, 2.0f, 3.0f, 4.0f}).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_Shift_NElements5)
{
    const epiFloat expectedValue[]{4.0f, 5.0f, 1.0f, 2.0f, 3.0f};

    const dSeries1Df shift = dSeries1Df({1.0f, 2.0f, 3.0f, 4.0f, 5.0f}).DFT_Shift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_IShift_NElements0)
{
    EXPECT_EQ(dSeries1Df().DFT_IShift().GetSize(), 0);
}

TEST(dSeries1Df, DFT_IShift_NElements1)
{
    const epiFloat expectedValue[]{1.0f};

    const dSeries1Df shift = dSeries1Df({1.0f}).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_IShift_NElements2)
{
    const epiFloat expectedValue[]{1.0f, 2.0f};

    const dSeries1Df shift = dSeries1Df({2.0f, 1.0f}).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_IShift_NElements4)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f};

    const dSeries1Df shift = dSeries1Df({3.0f, 4.0f, 1.0f, 2.0f}).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(dSeries1Df, DFT_IShift_NElements5)
{
    const epiFloat expectedValue[]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

    const dSeries1Df shift = dSeries1Df({4.0f, 5.0f, 1.0f, 2.0f, 3.0f}).DFT_IShift();

    ASSERT_EQ(shift.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < shift.GetSize(); ++i)
    {
        EXPECT_NEAR(shift.At(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

EPI_NAMESPACE_END()
