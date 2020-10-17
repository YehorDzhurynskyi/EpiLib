#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiData/Series/dSeries2Dc.hxx"
EPI_GENREGION_END(include)

#include "EpiData/Series/dSeriesBase.h"

EPI_NAMESPACE_BEGIN()

class dSeries2Dc : public dSeriesBase
{
EPI_GENREGION_BEGIN(dSeries2Dc)

EPI_GENHIDDEN_dSeries2Dc()

public:
    constexpr static epiMetaTypeID TypeID{0xf347fcd2};

    enum dSeries2Dc_PIDs
    {
        PID_Data = 0xdc15c5d,
        PID_IsEmpty = 0xae6d7566,
        PID_Size = 0x57f28b54,
        PID_Height = 0xf2e1e039,
        PID_Width = 0x4ddb6a2b,
        PID_COUNT = 5
    };

protected:
    epiBool GetIsEmpty_Callback() const;
    epiSize_t GetSize_Callback() const;
    epiSize_t GetHeight_Callback() const;

protected:
    epiArray<epiComplexf> m_Data{};
    epiSize_t m_Width{0};

EPI_GENREGION_END(dSeries2Dc)

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
    dSeries2Dc() = default;
    dSeries2Dc(std::initializer_list<epiComplexf> list, epiSize_t width);

    void Reserve(epiSize_t capacity);
    void Resize(epiSize_t size);
    void Clear();

    epiComplexf& PushBack(epiComplexf&& value = epiComplexf());

    epiFloat AtAbs(epiS32 r, epiS32 c) const;
    epiFloat AtTheta(epiS32 r, epiS32 c) const;

    const epiComplexf& At(epiS32 r, epiS32 c) const;
    epiComplexf& At(epiS32 r, epiS32 c);

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
