#include <gtest/gtest.h>

#include "EpiMultimedia/Image/mmImage.h"

namespace
{

constexpr epiFloat kDFTTolerance = 1.0e-3f;

}

EPI_NAMESPACE_BEGIN()

class mmImageTest : public ::testing::Test
{
public:
    mmImageTest() {}
    virtual ~mmImageTest() {}

    void SetUp() override {}
    void TearDown() override {}

    void SetUp(epiSize_t w, epiSize_t h)
    {
        m_Image.SetPixelFormat(mmImagePixelFormat::GRAYSCALE);
        m_Image.SetWidth(w);
        m_Image.SetHeight(h);
        m_Image.GetData().Resize(w * h);
    }

public:
    mmImage& GetImage()
    {
        return m_Image;
    }

protected:
    mmImage m_Image;
};

TEST_F(mmImageTest, DFT_Empty)
{
    SetUp(0, 0);

    const dSeries2Dc X = GetImage().DFT();
    EXPECT_EQ(X.GetSize(), 0);
}

TEST_F(mmImageTest, DFT_EmptyWidth)
{
    SetUp(0, 5);

    const dSeries2Dc X = GetImage().DFT();
    EXPECT_EQ(X.GetSize(), 0);
}

TEST_F(mmImageTest, DFT_EmptyHeight)
{
    SetUp(5, 0);

    const dSeries2Dc X = GetImage().DFT();
    EXPECT_EQ(X.GetSize(), 0);
}

TEST_F(mmImageTest, DFT_DCComponent)
{
    SetUp(3, 3);
    GetImage().GetData() = {255u, 255u, 255u, 255u, 255u, 255u, 255u, 255u, 255u};

    const epiComplexf expectedValue[]{{2295.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}};
    const epiFloat expectedAbs[]{2295.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    const epiFloat expectedTheta[]{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    const dSeries2Dc X = GetImage().DFT();

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

TEST_F(mmImageTest, DFT_NElements1x1)
{
    SetUp(1, 1);
    GetImage().GetData() = {255u};

    const epiComplexf expectedValue[]{{255.0f, 0.0f}};
    const epiFloat expectedAbs[]{255.0f};
    const epiFloat expectedTheta[]{0.0f};

    const dSeries2Dc X = GetImage().DFT();

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

TEST_F(mmImageTest, DFT_NElements2x1)
{
    SetUp(2, 1);
    GetImage().GetData() = {128u, 255u};

    const epiComplexf expectedValue[]{{ 383.0f, 0.0f }, { -127.0f, 0.0f }};
    const epiFloat expectedAbs[]{383.0f, 127.0f};
    const epiFloat expectedTheta[]{0.0f, M_PI};

    const dSeries2Dc X = GetImage().DFT();

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

TEST_F(mmImageTest, DFT_NElements1x2)
{
    SetUp(1, 2);
    GetImage().GetData() = {128u, 255u};

    const epiComplexf expectedValue[]{{ 383.0f, 0.0f }, { -127.0f, 0.0f }};
    const epiFloat expectedAbs[]{383.0f, 127.0f};
    const epiFloat expectedTheta[]{0.0f, M_PI};

    const dSeries2Dc X = GetImage().DFT();

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

TEST_F(mmImageTest, DFT_NElements2x2)
{
    SetUp(2, 2);
    GetImage().GetData() = {128u, 255u, 0u, 72u};

    const epiComplexf expectedValue[]{{ 455.0f, 0.0f }, { -199.0f, 0.0f }, { 311.0f, 0.0f }, { -55.0f, 0.0f }};
    const epiFloat expectedAbs[]{455.0f, 199.0f, 311.0f, 55.0f};
    const epiFloat expectedTheta[]{0.0f, M_PI, 0.0f, M_PI};

    const dSeries2Dc X = GetImage().DFT();

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

TEST_F(mmImageTest, DFT_NElements3x3)
{
    SetUp(3, 3);
    GetImage().GetData() = {128u, 255u, 0u, 72u, 53u, 99u, 0u, 255u, 18u};

    const epiComplexf expectedValue[]{{ 880.0f, 0.0f },
                                      { -140.0f, -386.24733f },
                                      { 134.5f, 42.43524f },
                                      { 283.0f, -252.8794179f },
                                      { 134.5f, -42.43524f },
                                      { -141.5f, -23.38268f }};
    const epiFloat expectedAbs[]{880.0f, 410.83695f, 141.035456f, 379.52206787f, 141.03545653f, 143.41896667f};
    const epiFloat expectedTheta[]{0.0f, -1.91852977f, 0.30561897f, -0.72924948f, -0.30561897f, -2.97782397f};

    const dSeries2Dc X = GetImage().DFT();

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

TEST_F(mmImageTest, DFT_NElements3x4)
{
    SetUp(3, 4);
    GetImage().GetData() = {128u, 255u, 0u, 72u, 53u, 99u, 0u, 255u, 18u, 111u, 99u, 1u};

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

    const dSeries2Dc X = GetImage().DFT();

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

TEST_F(mmImageTest, DFT_NElements4x3)
{
    SetUp(4, 3);
    GetImage().GetData() = {128u, 255u, 0u, 72u, 53u, 99u, 0u, 255u, 18u, 111u, 99u, 1u};

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

    const dSeries2Dc X = GetImage().DFT();

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

EPI_NAMESPACE_END()
