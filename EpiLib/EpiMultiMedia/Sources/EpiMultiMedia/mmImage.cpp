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

mmImage mmImage::toGrayScale() const
{
    mmImage to;
    to.SetPixelFormat(mmImagePixelFormat::GRAYSCALE);
    to.SetWidth(GetWidth());
    to.SetHeight(GetHeight());

    switch (GetPixelFormat())
    {
    case mmImagePixelFormat::GRAYSCALE: return *this;
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
