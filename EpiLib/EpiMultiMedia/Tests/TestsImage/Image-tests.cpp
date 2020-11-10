#include <gtest/gtest.h>

#include "EpiMultimedia/Image/mmImage.h"

#include "EpiData/Series/dSeries2Df.h"

EPI_NAMESPACE_BEGIN()

class mmImageTest : public ::testing::Test
{
public:
    void Setup(epiSize_t s, epiSize_t w)
    {
        const dSeries2Df series = dSeries2Df::Arange(s, w);
        Image = mmImage::FromSeries2Df_ToGRAYSCALE(series);
    }

public:
    mmImage Image;
};

class mmImage4x4Test : public mmImageTest
{
public:
    void SetUp() override
    {
        Setup(16, 4);
    }
};

class mmImage5x5Test : public mmImageTest
{
public:
    void SetUp() override
    {
        Setup(25, 5);
    }
};

TEST_F(mmImage4x4Test, CorrelateIdentityReflect)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Reflect).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateIdentityMirror)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Mirror).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateIdentityNearest)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Nearest).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateIdentityWrap)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Wrap).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateIdentityZero)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Zero).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateIdentityFF)
{
    const dSeries2Df expected = dSeries2Df::Arange(4 * 4, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::FF).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel3x3Reflect)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Reflect).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel3x3Mirror)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Mirror).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel3x3Nearest)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Nearest).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel3x3Wrap)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Wrap).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel3x3Zero)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Zero).ToSeries2Df(), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel3x3FF)
{
    const dSeries2Df expected({255.0f, 255.0f, 255.0f, 255.0f,
                               255.0f, 25.0f, 30.0f, 255.0f,
                               255.0f, 45.0f, 50.0f, 255.0f,
                               255.0f, 255.0f, 255.0f, 255.0f}, 4);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::FF).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateIdentityReflect)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Reflect).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateIdentityMirror)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Mirror).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateIdentityNearest)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Nearest).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateIdentityWrap)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Wrap).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateIdentityZero)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Zero).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateIdentityFF)
{
    const dSeries2Df expected = dSeries2Df::Arange(5 * 5, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(1, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::FF).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel3x3Reflect)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Reflect).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel3x3Mirror)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Mirror).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel3x3Nearest)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Nearest).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel3x3Wrap)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Wrap).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel3x3Zero)
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

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::Zero).ToSeries2Df(), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel3x3FF)
{
    const dSeries2Df expected({255.0f, 255.0f, 255.0f, 255.0f, 255.0f,
                               255.0f, 30.0f, 35.0f, 40.0f, 255.0f,
                               255.0f, 55.0f, 60.0f, 65.0f, 255.0f,
                               255.0f, 80.0f, 85.0f, 90.0f, 255.0f,
                               255.0f, 255.0f, 255.0f, 255.0f, 255.0f}, 5);

    dSeries2Df kernel = dSeries2Df::Full(3 * 3, 3, 0.0f);
    kernel.At(0, 1) = 1.0f;
    kernel.At(1, 0) = 1.0f;
    kernel.At(1, 1) = 1.0f;
    kernel.At(1, 2) = 1.0f;
    kernel.At(2, 1) = 1.0f;

    EXPECT_EQ(Image.Correlate(kernel, dSeriesEdgeHandling::FF).ToSeries2Df(), expected);
}

EPI_NAMESPACE_END()
