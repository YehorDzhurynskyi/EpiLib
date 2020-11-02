EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesf.h"
#include "EpiData/Series/dSeriesf.cxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeries1Df.h"

EPI_NAMESPACE_BEGIN()

dSeriesf::dSeriesf(std::initializer_list<epiFloat> list)
    : m_Data{list}
{
}

epiBool dSeriesf::GetIsEmpty_Callback() const
{
    return GetData().IsEmpty();
}

epiSize_t dSeriesf::GetSize_Callback() const
{
    return GetData().GetSize();
}

void dSeriesf::Reserve(epiSize_t capacity)
{
    GetData().Reserve(capacity);
}

void dSeriesf::Resize(epiSize_t size)
{
    GetData().Resize(size);
}

void dSeriesf::Clear()
{
    GetData().Clear();
}

epiFloat& dSeriesf::PushBack(epiFloat&& value)
{
    return GetData().PushBack(std::move(value));
}

void dSeriesf::push_back(epiFloat value)
{
    return GetData().push_back(value);
}

dSeries1Df dSeriesf::Histogram() const
{
    const auto& [minIt, maxIt] = std::minmax_element(begin(), end());
    if (minIt == end() || maxIt == end())
    {
        epiLogWarn("Invalid `dSeriesf` while calculating histogram: Couldn't determine min, max elements!");
        return dSeries1Df{};
    }

    return Histogram(*maxIt - *minIt + 1);
}

dSeries1Df dSeriesf::Histogram(epiU32 width) const
{
    dSeries1Df histogram;
    histogram.Resize(width);

    // TODO: optimize
    for (epiU32 i = 0; i < width; ++i)
    {
        histogram[i] = 0.0f;
    }

    const auto& [minIt, maxIt] = std::minmax_element(begin(), end());
    if (minIt == end() || maxIt == end())
    {
        epiLogWarn("Invalid `dSeriesf` while calculating histogram: Couldn't determine min, max elements!");
        return dSeries1Df{};
    }

    const epiFloat min = *minIt;
    const epiFloat max = *maxIt;

    histogram.SetBoundLeft(min);

    for (epiFloat v : GetData())
    {
        const epiU32 at = ((v - min) / (max - min)) * (width - 1);
        histogram[at] += 1.0f;
    }

    return histogram;
}

dSeriesf& dSeriesf::Transform(std::function<epiFloat(epiFloat)>&& callback)
{
    for (epiFloat& v : GetData())
    {
        v = callback(v);
    }

    return *this;
}

epiFloat dSeriesf::At(epiS32 index) const
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiFloat& dSeriesf::At(epiS32 index)
{
    epiAssert(index >= 0 && index < GetSize());
    return GetData()[index];
}

epiFloat dSeriesf::operator[](epiS32 index) const
{
    return At(index);
}

epiFloat& dSeriesf::operator[](epiS32 index)
{
    return At(index);
}

epiBool operator==(const dSeriesf& lhs, const dSeriesf& rhs)
{
    return lhs.GetData() == rhs.GetData();
}

epiBool operator!=(const dSeriesf& lhs, const dSeriesf& rhs)
{
    return !(operator==(lhs, rhs));
}

EPI_NAMESPACE_END()
