#include <gtest/gtest.h>

#include "EpiCore/Color.h"

namespace
{

void ExpectVec3f(const epiVec3f& lhs, const epiVec3f& rhs)
{
    EXPECT_NEAR(lhs.x, rhs.x, epiFloatingEqTolerance());
    EXPECT_NEAR(lhs.y, rhs.y, epiFloatingEqTolerance());
    EXPECT_NEAR(lhs.z, rhs.z, epiFloatingEqTolerance());
}

}

EPI_NAMESPACE_BEGIN()

TEST(Color, ToHSB)
{
    ExpectVec3f(Color().GetHSBf(), epiVec3f{});
    ExpectVec3f(Color(0.0f, 0.0f, 0.0f).GetHSBf(), epiVec3f(0.0f, 0.0f, 0.0f));
    ExpectVec3f(Color(1.0f, 0.0f, 0.0f).GetHSBf(), epiVec3f(0.0f, 1.0f, 1.0f));
    ExpectVec3f(Color(0.0f, 1.0f, 0.0f).GetHSBf(), epiVec3f(0.33333f, 1.0f, 1.0f));
    ExpectVec3f(Color(0.0f, 0.0f, 1.0f).GetHSBf(), epiVec3f(0.66666f, 1.0f, 1.0f));
    ExpectVec3f(Color(0.5f, 0.314f, 0.42f).GetHSBf(), epiVec3f(0.90501792f, 0.372f, 0.5f));
    ExpectVec3f(Color(0.314f, 0.5f, 0.42f).GetHSBf(), epiVec3f(0.4283154121863799f, 0.372f, 0.5f));
    ExpectVec3f(Color(0.314f, 0.42f, 0.5f).GetHSBf(), epiVec3f(0.57168458781362f, 0.372f, 0.5f));
    ExpectVec3f(Color(0.42f, 0.42f, 0.42f).GetHSBf(), epiVec3f(0.0f, 0.0f, 0.42f));
    ExpectVec3f(Color(1.0f, 1.0f, 0.2f).GetHSBf(), epiVec3f(0.16666666f, 0.8f, 1.0f));
}

TEST(Color, FromHSB)
{
    ExpectVec3f(Color::FromHSB(Color().GetHSBf()).GetColor(), epiVec3f{});
    ExpectVec3f(Color::FromHSB(Color(0.0f, 0.0f, 0.0f).GetHSBf()).GetColor(), epiVec3f(0.0f, 0.0f, 0.0f));
    ExpectVec3f(Color::FromHSB(Color(1.0f, 0.0f, 0.0f).GetHSBf()).GetColor(), epiVec3f(1.0f, 0.0f, 0.0f));
    ExpectVec3f(Color::FromHSB(Color(0.0f, 1.0f, 0.0f).GetHSBf()).GetColor(), epiVec3f(0.0f, 1.0f, 0.0f));
    ExpectVec3f(Color::FromHSB(Color(0.0f, 0.0f, 1.0f).GetHSBf()).GetColor(), epiVec3f(0.0f, 0.0f, 1.0f));
    ExpectVec3f(Color::FromHSB(Color(0.5f, 0.314f, 0.42f).GetHSBf()).GetColor(), epiVec3f(0.5f, 0.314f, 0.42f));
    ExpectVec3f(Color::FromHSB(Color(0.314f, 0.5f, 0.42f).GetHSBf()).GetColor(), epiVec3f(0.314f, 0.5f, 0.42f));
    ExpectVec3f(Color::FromHSB(Color(0.314f, 0.42f, 0.5f).GetHSBf()).GetColor(), epiVec3f(0.314f, 0.42f, 0.5f));
    ExpectVec3f(Color::FromHSB(Color(0.42f, 0.42f, 0.42f).GetHSBf()).GetColor(), epiVec3f(0.42f, 0.42f, 0.42f));
    ExpectVec3f(Color::FromHSB(Color(1.0f, 1.0f, 0.2f).GetHSBf()).GetColor(), epiVec3f(1.0f, 1.0f, 0.2f));
}

EPI_NAMESPACE_END()
