#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDataVisualization/Data/dvDataCollection.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

class dvDataCollection : public Object
{
EPI_GENREGION_BEGIN(dvDataCollection)

EPI_GENHIDDEN_dvDataCollection()

public:
    constexpr static MetaTypeID TypeID{0x489102dd};

    enum dvDataCollection_PIDs
    {
        PID_Buffer = 0x36f6f5c4,
        PID_COUNT = 1
    };

protected:
    epiArray<epiFloat> m_Buffer;

EPI_GENREGION_END(dvDataCollection)

public:
    epiBool IsEmpty() const;
    epiSize_t Size() const;

    void PushBack(epiFloat value);
    void Clear();
    void Reserve(epiSize_t size);

    epiFloat operator[](const epiS32 index) const;

public:
    auto begin() -> typename decltype(m_Buffer)::iterator;
    auto end() -> typename decltype(m_Buffer)::iterator;
    auto begin() const -> typename decltype(m_Buffer)::const_iterator;
    auto end() const -> typename decltype(m_Buffer)::const_iterator;
};

EPI_NAMESPACE_END()
