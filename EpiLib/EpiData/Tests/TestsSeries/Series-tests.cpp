#include <gtest/gtest.h>

#include "EpiData/Series/dSeriesYComplex.h"

EPI_NAMESPACE_BEGIN()

TEST(dSeriesYComplex, Theta)
{
    // NOTE: ref https://en.wikipedia.org/wiki/Atan2

    const epiComplexf c[] {
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

    const epiFloat expected[] {
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
        const epiFloat theta = dSeriesYComplex{ c[i] }.AtTheta(0);
        EXPECT_NEAR(theta, expected[i], epiFloatingEqTolerance());
    }
}

EPI_NAMESPACE_END();
