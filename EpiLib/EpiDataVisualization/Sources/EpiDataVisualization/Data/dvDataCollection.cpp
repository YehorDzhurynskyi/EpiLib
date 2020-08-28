EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Data/dvDataCollection.h"
#include "EpiDataVisualization/Data/dvDataCollection.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void dvDataCollection::PushBack(epiFloat value)
{
    m_Buffer.PushBack(std::move(value));
}

epiBool dvDataCollection::IsEmpty() const
{
    return m_Buffer.IsEmpty();
}

void dvDataCollection::Clear()
{
    m_Buffer.Clear();
}

void dvDataCollection::Reserve(epiSize_t size)
{
    m_Buffer.Reserve(size);
}

epiSize_t dvDataCollection::Size() const
{
    return m_Buffer.Size();
}

auto dvDataCollection::begin() -> typename decltype(m_Buffer)::iterator
{
    return m_Buffer.begin();
}

auto dvDataCollection::end() -> typename decltype(m_Buffer)::iterator
{
    return m_Buffer.end();
}

auto dvDataCollection::begin() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.begin();
}

auto dvDataCollection::end() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.end();
}

auto dvDataCollection::cbegin() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.cbegin();
}

auto dvDataCollection::cend() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.cend();
}

epiFloat dvDataCollection::operator[](const epiS32 index) const
{
    return m_Buffer[index];
}

EPI_NAMESPACE_END()
