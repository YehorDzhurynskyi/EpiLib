#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries1Df.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"
#include "EpiData/Series/dSeries1Dc.h"

EPI_NAMESPACE_BEGIN()

class dSeries1Df : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeries1Df)

EPI_GENHIDDEN_dSeries1Df()

public:
    constexpr static epiMetaTypeID TypeID{0x816bb604};

    enum dSeries1Df_PIDs
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

EPI_GENREGION_END(dSeries1Df)

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
    dSeries1Df() = default;
    dSeries1Df(std::initializer_list<epiFloat> list);

    void Reserve(epiSize_t capacity);
    void Resize(epiSize_t size);
    void Clear();

    epiFloat& PushBack(epiFloat && value = epiFloat());

    dSeries1Dc DFT_R2C() const;

    epiFloat At(epiS32 index) const;
    epiFloat& At(epiS32 index);

    epiFloat operator[](epiS32 index) const;
    epiFloat& operator[](epiS32 index);

    friend epiBool operator==(const dSeries1Df& lhs, const dSeries1Df& rhs);
    friend epiBool operator!=(const dSeries1Df& lhs, const dSeries1Df& rhs);

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
