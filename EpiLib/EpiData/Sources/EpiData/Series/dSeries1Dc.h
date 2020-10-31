#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Dc.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeries1Df;
class dSeries1Dc : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeries1Dc)

EPI_GENHIDDEN_dSeries1Dc()

public:
    constexpr static epiMetaTypeID TypeID{0xf101428b};

    enum dSeries1Dc_PIDs
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
    epiArray<epiComplexf> m_Data{};

EPI_GENREGION_END(dSeries1Dc)

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
    dSeries1Dc() = default;
    dSeries1Dc(std::initializer_list<epiComplexf> list);

    void Reserve(epiSize_t capacity);
    void Resize(epiSize_t size);
    void Clear();

    epiComplexf& PushBack(epiComplexf&& value = epiComplexf());

    dSeries1Df DFT_C2R() const;
    dSeries1Df DFT_C2R(epiSize_t N) const;

    epiFloat AtAbs(epiS32 index) const;
    epiFloat AtTheta(epiS32 index) const;

    const epiComplexf& At(epiS32 index) const;
    epiComplexf& At(epiS32 index);

    const epiComplexf& operator[](epiS32 index) const;
    epiComplexf& operator[](epiS32 index);

    friend epiBool operator==(const dSeries1Dc& lhs, const dSeries1Dc& rhs);
    friend epiBool operator!=(const dSeries1Dc& lhs, const dSeries1Dc& rhs);

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
};

EPI_NAMESPACE_END()
