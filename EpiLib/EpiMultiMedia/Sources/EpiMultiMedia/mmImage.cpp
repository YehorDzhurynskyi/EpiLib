EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/mmImage.h"
#include "EpiMultimedia/mmImage.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/Color.h"

EPI_NAMESPACE_BEGIN()

epiU32 mmImage::BitDepthOf(mmImagePixelFormat fmt)
{
    switch (fmt)
    {
    case mmImagePixelFormat::R8G8B8: return 24;
    case mmImagePixelFormat::GRAYSCALE: return 8;
    }
}

void mmImage::BuildHistogram(dSeries1Df& histogram) const
{
    epiAssert(GetPixelFormat() == mmImagePixelFormat::GRAYSCALE);

    histogram.Resize(256);

    for (epiU32 i = 0; i < 256; ++i)
    {
        histogram[i] = 0.0f;
    }

    for (const auto& x : GetData())
    {
        histogram[x] += 1.0f;
    }
}

mmImage mmImage::toGrayScale() const
{
    mmImage to;
    to.SetPixelFormat(mmImagePixelFormat::GRAYSCALE);
    to.SetWidth(GetWidth());
    to.SetHeight(GetHeight());

    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE:
    {
        const epiArray<epiByte>& fromData = GetData();
        epiArray<epiByte>& toData = to.GetData();
        toData.Resize(fromData.Size());

        for (epiU32 i = 0; i < fromData.Size(); ++i)
        {
            toData[i] = fromData[i];
        }
    } break;
    case mmImagePixelFormat::R8G8B8:
    {
        const epiArray<epiByte>& fromData = GetData();
        epiArray<epiByte>& toData = to.GetData();

        epiAssert(fromData.Size() % 3 == 0);
        toData.Resize(fromData.Size() / 3);

        for (epiU32 i = 0; i < toData.Size(); ++i)
        {
            toData[i] = Color(fromData[i * 3 + 0], fromData[i * 3 + 1], fromData[i * 3 + 2]).GetLumau();
        }
    } break;
    }

    return to;
}

void mmImage::SetPixelFormat_Callback(mmImagePixelFormat value)
{
    m_PixelFormat = value;
    m_BitDepth = mmImage::BitDepthOf(value);
}

EPI_NAMESPACE_END()
