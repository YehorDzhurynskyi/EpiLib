#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeriesf.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeries1Df;
class dSeriesf : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeriesf)

EPI_GENHIDDEN_dSeriesf()

public:
    constexpr static epiMetaTypeID TypeID{0x5064f05e};

    enum dSeriesf_PIDs
    {
        PID_Data = 0xdc15c5d,
        PID_IsEmpty = 0xae6d7566,
        PID_Size = 0x57f28b54,
        PID_COUNT = 3
    };

protected:
    epiBool GetIsEmpty_Callback() const;
    epiSize_t GetSize_Callback() const;

protected:
    epiArray<epiFloat> m_Data{};

EPI_GENREGION_END(dSeriesf)

public:
    using value_type = typename decltype(m_Data)::value_type;
    using allocator_type = typename decltype(m_Data)::allocator_type;
    using pointer = typename decltype(m_Data)::pointer;
    using const_pointer = typename decltype(m_Data)::const_pointer;
    using reference = typename decltype(m_Data)::reference;
    using const_reference = typename decltype(m_Data)::const_reference;
    using size_type = typename decltype(m_Data)::size_type;
    using difference_type = typename decltype(m_Data)::difference_type;
    using iterator = typename decltype(m_Data)::iterator;
    using const_iterator = typename decltype(m_Data)::const_iterator;
    using reverse_iterator = typename decltype(m_Data)::reverse_iterator;
    using const_reverse_iterator = typename decltype(m_Data)::const_reverse_iterator;

public:
    dSeriesf() = default;
    dSeriesf(std::initializer_list<epiFloat> list);

    void Reserve(epiSize_t capacity);
    void Resize(epiSize_t size);
    void Clear();

    epiFloat& PushBack(epiFloat && value = epiFloat());
    void push_back(epiFloat value);

    dSeries1Df Histogram() const;
    dSeries1Df Histogram(epiU32 width) const;

    epiFloat Min() const;
    epiFloat Max() const;
    epiVec2f MinMax() const;

    dSeriesf& Transform(std::function<epiFloat(epiFloat)>&& callback);

    epiFloat At(epiS32 index) const;
    epiFloat& At(epiS32 index);

    epiFloat operator[](epiS32 index) const;
    epiFloat& operator[](epiS32 index);

    friend epiBool operator==(const dSeriesf& lhs, const dSeriesf& rhs);
    friend epiBool operator!=(const dSeriesf& lhs, const dSeriesf& rhs);

    auto begin() -> typename iterator { return m_Data.begin(); }
    auto end() -> typename iterator { return m_Data.end(); }
    auto begin() const -> typename const_iterator { return m_Data.cbegin(); }
    auto end() const -> typename const_iterator { return m_Data.cend(); }
    auto cbegin() const -> typename const_iterator { return m_Data.cbegin(); }
    auto cend() const -> typename const_iterator { return m_Data.cend(); }
    auto rbegin() -> typename reverse_iterator { return m_Data.rbegin(); }
    auto rend() -> typename reverse_iterator { return m_Data.rend(); }
    auto crbegin() -> typename const_reverse_iterator { return m_Data.crbegin(); }
    auto crend() -> typename const_reverse_iterator { return m_Data.crend(); }

protected:
    void Arange_Internal(epiSize_t size, epiFloat start, epiFloat step);
    void Rand_Internal(epiSize_t size, epiFloat min, epiFloat max);
    void Full_Internal(epiSize_t size, epiFloat value);
};

EPI_NAMESPACE_END()
