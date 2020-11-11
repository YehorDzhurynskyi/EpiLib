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

TEST_F(mmImage4x4Test, CorrelateIdentityReflect)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, CorrelateIdentityMirror)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, CorrelateIdentityNearest)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, CorrelateIdentityWrap)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, CorrelateIdentityZero)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, CorrelateIdentityFF)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, CorrelateKernel7x7Reflect)
{
    const dSeries2Df expected({15.0f, 19.0f, 19.0f, 15.0f,
                               31.0f, 35.0f, 35.0f, 31.0f,
                               31.0f, 35.0f, 35.0f, 31.0f,
                               15.0f, 19.0f, 19.0f, 15.0f}, 4);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, 4.0f, 4.0f, 0.0f,
                               16.0f, 20.0f, 20.0f, 16.0f,
                               16.0f, 20.0f, 20.0f, 16.0f,
                               0.0f, 4.0f, 4.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel7x7Nearest)
{
    const dSeries2Df expected({30.0f, 32.0f, 32.0f, 30.0f,
                               38.0f, 40.0f, 40.0f, 38.0f,
                               38.0f, 40.0f, 40.0f, 38.0f,
                               30.0f, 32.0f, 32.0f, 30.0f}, 4);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel7x7Wrap)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel7x7Zero)
{
    const dSeries2Df expected({30.0f, 32.0f, 32.0f, 30.0f,
                               38.0f, 30.0f, 20.0f, 8.0f,
                               38.0f, 20.0f, 0.0f, 0.0f,
                               30.0f, 2.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST_F(mmImage4x4Test, CorrelateKernel7x7FF)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 30.0f,
                               0.0f, 0.0f, 20.0f, 255.0f,
                               0.0f, 20.0f, 255.0f, 255.0f,
                               30.0f, 255.0f, 255.0f, 255.0f}, 4);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

TEST_F(mmImage5x5Test, CorrelateIdentityReflect)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, CorrelateIdentityMirror)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, CorrelateIdentityNearest)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, CorrelateIdentityWrap)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, CorrelateIdentityZero)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, CorrelateIdentityFF)
{
    EXPECT_EQ(Image.Correlate(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, CorrelateKernel7x7Reflect)
{
    const dSeries2Df expected({18.0f, 23.0f, 25.0f, 23.0f, 18.0f,
                               43.0f, 48.0f, 50.0f, 48.0f, 43.0f,
                               53.0f, 58.0f, 60.0f, 58.0f, 53.0f,
                               43.0f, 48.0f, 50.0f, 48.0f, 43.0f,
                               18.0f, 23.0f, 25.0f, 23.0f, 18.0f}, 5);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, 6.0f, 8.0f, 6.0f, 0.0f,
                               30.0f, 36.0f, 38.0f, 36.0f, 30.0f,
                               40.0f, 46.0f, 48.0f, 46.0f, 40.0f,
                               30.0f, 36.0f, 38.0f, 36.0f, 30.0f,
                               0.0f, 6.0f, 8.0f, 6.0f, 0.0f}, 5);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel7x7Nearest)
{
    const dSeries2Df expected({36.0f, 39.0f, 40.0f, 39.0f, 36.0f,
                               51.0f, 54.0f, 55.0f, 54.0f, 51.0f,
                               56.0f, 59.0f, 60.0f, 59.0f, 56.0f,
                               51.0f, 54.0f, 55.0f, 54.0f, 51.0f,
                               36.0f, 39.0f, 40.0f, 39.0f, 36.0f}, 5);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel7x7Wrap)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               7.0f, 12.0f, 12.0f, 12.0f, 7.0f,
                               7.0f, 12.0f, 12.0f, 12.0f, 7.0f,
                               7.0f, 12.0f, 12.0f, 12.0f, 7.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 5);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel7x7Zero)
{
    const dSeries2Df expected({36.0f, 42.0f, 42.0f, 40.0f, 36.0f,
                               66.0f, 66.0f, 55.0f, 42.0f, 32.0f,
                               66.0f, 59.0f, 36.0f, 11.0f, 0.0f,
                               56.0f, 42.0f, 7.0f, 0.0f, 0.0f,
                               36.0f, 16.0f, 0.0f, 0.0f, 0.0f}, 5);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST_F(mmImage5x5Test, CorrelateKernel7x7FF)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f, 36.0f,
                                0.0f, 0.0f, 0.0f, 42.0f, 255.0f,
                                0.0f, 0.0f, 36.0f, 255.0f, 255.0f,
                                0.0f, 42.0f, 255.0f, 255.0f, 255.0f,
                                36.0f, 255.0f, 255.0f, 255.0f, 255.0f}, 5);

    EXPECT_EQ(Image.Correlate(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

TEST_F(mmImage4x4Test, ConvolveIdentityReflect)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, ConvolveIdentityMirror)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, ConvolveIdentityNearest)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, ConvolveIdentityWrap)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, ConvolveIdentityZero)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, ConvolveIdentityFF)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(4 * 4, 4));
}

TEST_F(mmImage4x4Test, ConvolveKernel7x7Reflect)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST_F(mmImage4x4Test, ConvolveKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST_F(mmImage4x4Test, ConvolveKernel7x7Nearest)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST_F(mmImage4x4Test, ConvolveKernel7x7Wrap)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST_F(mmImage4x4Test, ConvolveKernel7x7Zero)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 22.0f,
                               0.0f, 0.0f, 28.0f, 60.0f}, 4);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST_F(mmImage4x4Test, ConvolveKernel7x7FF)
{
    const dSeries2Df expected({255.0f, 255.0f, 255.0f, 0.0f,
                               255.0f, 255.0f, 0.0f, 0.0f,
                               255.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f}, 4);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

TEST_F(mmImage5x5Test, ConvolveIdentityReflect)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Reflect), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, ConvolveIdentityMirror)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Mirror), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, ConvolveIdentityNearest)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Nearest), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, ConvolveIdentityWrap)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Wrap), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, ConvolveIdentityZero)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::Zero), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, ConvolveIdentityFF)
{
    EXPECT_EQ(Image.Convolve(dSeries2Df::Identity(7), dSeriesEdgeHandling::FF), dSeries2Df::Arange(5 * 5, 5));
}

TEST_F(mmImage5x5Test, ConvolveKernel7x7Reflect)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 5);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Reflect), expected);
}

TEST_F(mmImage5x5Test, ConvolveKernel7x7Mirror)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 5);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Mirror), expected);
}

TEST_F(mmImage5x5Test, ConvolveKernel7x7Nearest)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 5);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Nearest), expected);
}

TEST_F(mmImage5x5Test, ConvolveKernel7x7Wrap)
{
    const dSeries2Df expected({18.0f, 13.0f, 13.0f, 13.0f, 18.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               18.0f, 13.0f, 13.0f, 13.0f, 18.0f}, 5);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Wrap), expected);
}

TEST_F(mmImage5x5Test, ConvolveKernel7x7Zero)
{
    const dSeries2Df expected({0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 6.0f,
                               0.0f, 0.0f, 0.0f, 30.0f, 54.0f,
                               0.0f, 0.0f, 30.0f, 78.0f, 108.0f}, 5);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::Zero), expected);
}

TEST_F(mmImage5x5Test, ConvolveKernel7x7FF)
{
    const dSeries2Df expected({255.0f, 255.0f, 255.0f, 215.0f, 0.0f,
                               255.0f, 255.0f, 255.0f, 0.0f, 0.0f,
                               255.0f, 255.0f, 0.0f, 0.0f, 0.0f,
                               199.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, 5);

    EXPECT_EQ(Image.Convolve(Kernel7x7(), dSeriesEdgeHandling::FF), expected);
}

EPI_NAMESPACE_END()
