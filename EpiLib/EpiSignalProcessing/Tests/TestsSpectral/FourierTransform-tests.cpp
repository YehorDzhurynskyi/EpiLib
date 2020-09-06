#include <gtest/gtest.h>

#include "EpiSignalProcessing/spMath.h"

EPI_NAMESPACE_BEGIN()

TEST(DFT_Real, Empty)
{
    const dSeriesYComplex X = spMath::DFT_Real({});
    EXPECT_EQ(X.GetSize(), 0);
}

TEST(DFT_Real, DCComponent)
{
    const epiComplexf expectedValue[] { { 4.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } };
    const epiFloat expectedAbs[] { 4.0f, 0.0f, 0.0f };
    const epiFloat expectedTheta[] { 0.0f, 0.0f, 0.0f };

    const dSeriesYComplex X = spMath::DFT_Real({ 1.0f, 1.0f, 1.0f, 1.0f });

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.AtY(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(DFT_Real, NElements1)
{
    const epiComplexf expectedValue[] { { 1.0f, 0.0f } };
    const epiFloat expectedAbs[] { 1.0f };
    const epiFloat expectedTheta[] { 0.0f };

    const dSeriesYComplex X = spMath::DFT_Real({ 1.0f });

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.AtY(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(DFT_Real, NElements2)
{
    const epiComplexf expectedValue[] { { 3.0f, 0.0f }, { -1.0f, 0.0f } };
    const epiFloat expectedAbs[] { 3.0f, 1.0f };
    const epiFloat expectedTheta[] { 0.0f, M_PI };

    const dSeriesYComplex X = spMath::DFT_Real({ 1.0f, 2.0f });

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.AtY(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(DFT_Real, NElements3)
{
    const epiComplexf expectedValue[] { { 6.0f, 0.0f }, { -1.5f, 0.8660254f } };
    const epiFloat expectedAbs[] { 6.0f, 1.73205081f };
    const epiFloat expectedTheta[] { 0.0f, 2.61799388 };

    const dSeriesYComplex X = spMath::DFT_Real({ 1.0f, 2.0f, 3.0f });

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.AtY(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(DFT_Real, SequencePositive)
{
    const epiComplexf expectedValue[] { { 10.0f, 0.0f }, { -2.0f, 2.0f }, { -2.0f, 0.0f } };
    const epiFloat expectedAbs[] { 10.0f, 2.0f * std::sqrt(2.0f), 2.0f };
    const epiFloat expectedTheta[] { 0.0f, -M_PI_4 + M_PI, M_PI };

    const dSeriesYComplex X = spMath::DFT_Real({ 1.0f, 2.0f, 3.0f, 4.0f });

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.AtY(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(DFT_Real, SequenceNegative)
{
    const epiComplexf expectedValue[] { { -10.0f, 0.0f }, { 2.0f, -2.0f }, { 2.0f, 0.0f } };
    const epiFloat expectedAbs[] { 10.0f, 2.0f * std::sqrt(2.0f), 2.0f };
    const epiFloat expectedTheta[] { M_PI, -M_PI_4, 0.0f };

    const dSeriesYComplex X = spMath::DFT_Real({ -1.0f, -2.0f, -3.0f, -4.0f });

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.AtY(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(DFT_Real, SequencePositiveNegative)
{
    const epiComplexf expectedValue[] { { 4.0f, 0.0f }, { 4.14459608f, 0.05189464f }, { 3.65010441f, 13.94691472f }, { -13.29470049f, -3.19857416f } };
    const epiFloat expectedAbs[] { 4.0f, 4.14492096f, 14.41664637f, 13.67406076f };
    const epiFloat expectedTheta[] { 0.0f, 0.01252038f, 1.31482336f, -2.90548973f };

    const dSeriesYComplex X = spMath::DFT_Real({ -1.0f, 1.0f, -2.0f, 5.0f, -3.0f, -4.0f, 8.0f });

    ASSERT_EQ(X.GetSize(), epiArrLen(expectedValue));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedAbs));
    ASSERT_EQ(X.GetSize(), epiArrLen(expectedTheta));

    for (epiU32 i = 0; i < X.GetSize(); ++i)
    {
        EXPECT_TRUE(epiFloatingEq(X.AtY(i), expectedValue[i]));
        EXPECT_NEAR(X.AtAbs(i), expectedAbs[i], epiFloatingEqTolerance());
        EXPECT_NEAR(X.AtTheta(i), expectedTheta[i], epiFloatingEqTolerance());
    }
}

TEST(IDFT_Real, Empty)
{
    const dSeriesY y = spMath::IDFT_Real({});
    EXPECT_EQ(y.GetSize(), 0);
}

TEST(IDFT_Real, DCComponent)
{
    const epiFloat expectedValue[] { 1.0f, 1.0f, 1.0f, 1.0f };

    const dSeriesY y = spMath::IDFT_Real({ { 4.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } });

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.AtY(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(IDFT_Real, NElements1)
{
    const epiFloat expectedValue[] { 1.0f };

    const dSeriesY y = spMath::IDFT_Real({ { 1.0f, 0.0f } }, 1);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.AtY(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(IDFT_Real, NElements2)
{
    const epiFloat expectedValue[] { 1.0f, 2.0f };

    const dSeriesY y = spMath::IDFT_Real({ { 3.0f, 0.0f }, { -1.0f, 0.0f } });

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.AtY(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(IDFT_Real, NElements3)
{
    const epiFloat expectedValue[] { 1.0f, 2.0f, 3.0f };

    const dSeriesY y = spMath::IDFT_Real({ { 6.0f, 0.0f }, { -1.5f, 0.8660254f } }, 3);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.AtY(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(IDFT_Real, SequencePositive)
{
    const epiFloat expectedValue[] { 1.0f, 2.0f, 3.0f, 4.0f };

    const dSeriesY y = spMath::IDFT_Real({ { 10.0f, 0.0f }, { -2.0f, 2.0f }, { -2.0f, 0.0f } });

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.AtY(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(IDFT_Real, SequenceNegative)
{
    const epiFloat expectedValue[] { -1.0f, -2.0f, -3.0f, -4.0f };

    const dSeriesY y = spMath::IDFT_Real({ { -10.0f, 0.0f }, { 2.0f, -2.0f }, { 2.0f, 0.0f } });

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.AtY(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(IDFT_Real, SequencePositiveNegative)
{
    const epiFloat expectedValue[] { -1.0f, 1.0f, -2.0f, 5.0f, -3.0f, -4.0f, 8.0f };

    const dSeriesY y = spMath::IDFT_Real({ { 4.0f, 0.0f }, { 4.14459608f, 0.05189464f }, { 3.65010441f, 13.94691472f }, { -13.29470049f, -3.19857416f } }, 7);

    ASSERT_EQ(y.GetSize(), epiArrLen(expectedValue));

    for (epiU32 i = 0; i < y.GetSize(); ++i)
    {
        EXPECT_NEAR(y.AtY(i), expectedValue[i], epiFloatingEqTolerance());
    }
}

TEST(DFT_Real_to_IDFT_Real, NElements100)
{
    constexpr epiSize_t kN = 100;

    dSeriesY series;
    for (epiU32 i = 0; i < kN; ++i)
    {
        epiFloat& x = series.PushBack();
        x = epiRand01();
    }

    const dSeriesY resultSeries = spMath::IDFT_Real(spMath::DFT_Real(series), kN);

    ASSERT_EQ(series, resultSeries);
}

TEST(DFT_Real_to_IDFT_Real, NElements101)
{
    constexpr epiSize_t kN = 101;

    dSeriesY series;
    for (epiU32 i = 0; i < kN; ++i)
    {
        epiFloat& x = series.PushBack();
        x = epiRand01();
    }

    const dSeriesY resultSeries = spMath::IDFT_Real(spMath::DFT_Real(series), kN);

    ASSERT_EQ(series, resultSeries);
}

EPI_NAMESPACE_END()
