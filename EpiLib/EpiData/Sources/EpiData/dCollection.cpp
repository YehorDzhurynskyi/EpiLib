EPI_GENREGION_BEGIN(include)
#include "EpiData/dCollection.h"
#include "EpiData/dCollection.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void dCollection::PushBack(epiFloat value)
{
    m_Buffer.PushBack(std::move(value));
}

epiBool dCollection::IsEmpty() const
{
    return m_Buffer.IsEmpty();
}

void dCollection::Clear()
{
    m_Buffer.Clear();
}

void dCollection::Reserve(epiSize_t size)
{
    m_Buffer.Reserve(size);
}

epiSize_t dCollection::Size() const
{
    return m_Buffer.Size();
}

auto dCollection::begin() -> typename decltype(m_Buffer)::iterator
{
    return m_Buffer.begin();
}

auto dCollection::end() -> typename decltype(m_Buffer)::iterator
{
    return m_Buffer.end();
}

auto dCollection::begin() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.begin();
}

auto dCollection::end() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.end();
}

auto dCollection::cbegin() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.cbegin();
}

auto dCollection::cend() const -> typename decltype(m_Buffer)::const_iterator
{
    return m_Buffer.cend();
}

epiFloat dCollection::operator[](const epiS32 index) const
{
    return m_Buffer[index];
}

EPI_NAMESPACE_END()
