#pragma once

EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClass.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

class InplaceClass : public Object
{
EPI_GENREGION_BEGIN(InplaceClass)

EPI_GENHIDDEN_InplaceClass()

public:
    constexpr static epiMetaTypeID TypeID{0x8c2da82a};

    enum InplaceClass_PIDs
    {
        PID_InplacePrty0 = 0x147cfcef,
        PID_InplacePrty1 = 0x637bcc79,
        PID_InplacePrty2 = 0xfa729dc3,
        PID_InplacePrty3 = 0x8d75ad55,
        PID_COUNT = 4
    };

protected:
    epiS32 m_InplacePrty0{0};
    epiFloat m_InplacePrty1{0.0f};
    epiString m_InplacePrty2{epiDEBUG_ONLY("Empty")};
    epiRect2f m_InplacePrty3{};

EPI_GENREGION_END(InplaceClass)

public:
    InplaceClass() = default;
    InplaceClass(epiS32 p0, epiFloat p1, epiString p2, epiRect2f p3)
        : m_InplacePrty0(p0)
        , m_InplacePrty1(p1)
        , m_InplacePrty2(p2)
        , m_InplacePrty3(p3)
    {
    }

    friend epiBool operator==(const InplaceClass& lhs, const InplaceClass& rhs)
    {
        return
            epiEqual(lhs.m_InplacePrty0, rhs.m_InplacePrty0) &&
            epiEqual(lhs.m_InplacePrty1, rhs.m_InplacePrty1) &&
            epiEqual(lhs.m_InplacePrty2, rhs.m_InplacePrty2) &&
            epiEqual(lhs.m_InplacePrty3, rhs.m_InplacePrty3);
    }

    friend epiBool operator!=(const InplaceClass& lhs, const InplaceClass& rhs)
    {
        return !(operator==(lhs, rhs));
    }
};

class TestClassA : public Object
{
EPI_GENREGION_BEGIN(TestClassA)

EPI_GENHIDDEN_TestClassA()

public:
    constexpr static epiMetaTypeID TypeID{0x7a931736};

    enum TestClassA_PIDs
    {
        PID_APrty0 = 0x73fed29,
        PID_APrty1 = 0x7038ddbf,
        PID_APrty2 = 0xe9318c05,
        PID_APrty3 = 0x9e36bc93,
        PID_APrty4 = 0x522930,
        PID_APrty5 = 0x775519a6,
        PID_APrty6 = 0xee5c481c,
        PID_APrty7 = 0x995b788a,
        PID_APrty8 = 0x9e4651b,
        PID_APrty9 = 0x7ee3558d,
        PID_APrty10 = 0xaf7549e1,
        PID_APrty11 = 0xd8727977,
        PID_APrty12 = 0x417b28cd,
        PID_APrty13 = 0x367c185b,
        PID_APrty14 = 0xa8188df8,
        PID_APrty15 = 0xdf1fbd6e,
        PID_APrty16 = 0x4616ecd4,
        PID_APrty17 = 0x3111dc42,
        PID_APrty18 = 0xa1aec1d3,
        PID_APrty19 = 0xd6a9f145,
        PID_APrty20 = 0x84581a22,
        PID_APrty21 = 0xf35f2ab4,
        PID_APrty22 = 0x6a567b0e,
        PID_APrty23 = 0x1d514b98,
        PID_APrty24 = 0x8335de3b,
        PID_APrty25 = 0xf432eead,
        PID_APrty26 = 0x6d3bbf17,
        PID_APrty27 = 0x1a3c8f81,
        PID_APrty28 = 0x8a839210,
        PID_APrty29 = 0xfd84a286,
        PID_APrty30 = 0x9d432b63,
        PID_APrty31 = 0xea441bf5,
        PID_APrty32 = 0x734d4a4f,
        PID_APrty33 = 0x44a7ad9,
        PID_APrty34 = 0x9a2eef7a,
        PID_APrty35 = 0xed29dfec,
        PID_APrty36 = 0x74208e56,
        PID_APrty37 = 0x327bec0,
        PID_APrty38 = 0x9398a351,
        PID_APrty39 = 0xe49f93c7,
        PID_APrty40 = 0xd202bda4,
        PID_APrty41 = 0xa5058d32,
        PID_APrty42 = 0x3c0cdc88,
        PID_APrty43 = 0x4b0bec1e,
        PID_APrtyVirtual0 = 0x6b4213f2,
        PID_APrtyVirtual1 = 0x1c452364,
        PID_APrtyVirtual2 = 0x854c72de,
        PID_APrtyVirtual3 = 0xf24b4248,
        PID_APrtyVirtual4 = 0x6c2fd7eb,
        PID_APrtyVirtual5 = 0x1b28e77d,
        PID_APrtyVirtual6 = 0x8221b6c7,
        PID_APrtyVirtual7 = 0xf5268651,
        PID_APrtyVirtual8 = 0x65999bc0,
        PID_APrtyVirtual9 = 0x129eab56,
        PID_APrtyVirtual10 = 0xbe183f43,
        PID_APrtyVirtual11 = 0xc91f0fd5,
        PID_APrtyVirtual12 = 0x50165e6f,
        PID_APrtyVirtual13 = 0x27116ef9,
        PID_APrtyVirtual14 = 0xb975fb5a,
        PID_APrtyVirtual15 = 0xce72cbcc,
        PID_APrtyVirtual16 = 0x577b9a76,
        PID_APrtyVirtual17 = 0x207caae0,
        PID_APrtyVirtual18 = 0xb0c3b771,
        PID_APrtyVirtual19 = 0xc7c487e7,
        PID_APrtyVirtual20 = 0x95356c80,
        PID_APrtyVirtual21 = 0xe2325c16,
        PID_APrtyVirtual22 = 0x7b3b0dac,
        PID_APrtyVirtual23 = 0xc3c3d3a,
        PID_APrtyVirtual24 = 0x9258a899,
        PID_APrtyVirtual25 = 0xe55f980f,
        PID_APrtyVirtual26 = 0x7c56c9b5,
        PID_APrtyVirtual27 = 0xb51f923,
        PID_APrtyVirtual28 = 0x9beee4b2,
        PID_APrtyVirtual29 = 0xece9d424,
        PID_APrtyVirtual30 = 0x8c2e5dc1,
        PID_APrtyVirtual31 = 0xfb296d57,
        PID_APrtyVirtual32 = 0x62203ced,
        PID_APrtyVirtual33 = 0x15270c7b,
        PID_APrtyVirtual34 = 0x8b4399d8,
        PID_APrtyVirtual35 = 0xfc44a94e,
        PID_APrtyVirtual36 = 0x654df8f4,
        PID_APrtyVirtual37 = 0x124ac862,
        PID_APrtyVirtual38 = 0x82f5d5f3,
        PID_APrtyVirtual39 = 0xf5f2e565,
        PID_APrtyVirtual40 = 0xc36fcb06,
        PID_APrtyVirtual41 = 0xb468fb90,
        PID_APrtyVirtual42 = 0x2d61aa2a,
        PID_APrtyVirtual43 = 0x5a669abc,
        PID_APrtyReadCallback0 = 0x3a2ad180,
        PID_APrtyReadCallback1 = 0x4d2de116,
        PID_APrtyReadCallback2 = 0xd424b0ac,
        PID_APrtyReadCallback3 = 0xa323803a,
        PID_APrtyReadCallback4 = 0x3d471599,
        PID_APrtyReadCallback5 = 0x4a40250f,
        PID_APrtyReadCallback6 = 0xd34974b5,
        PID_APrtyReadCallback7 = 0xa44e4423,
        PID_APrtyReadCallback8 = 0x34f159b2,
        PID_APrtyReadCallback9 = 0x43f66924,
        PID_APrtyReadCallback10 = 0x424791,
        PID_APrtyReadCallback11 = 0x77457707,
        PID_APrtyReadCallback12 = 0xee4c26bd,
        PID_APrtyReadCallback13 = 0x994b162b,
        PID_APrtyReadCallback14 = 0x72f8388,
        PID_APrtyReadCallback15 = 0x7028b31e,
        PID_APrtyReadCallback16 = 0xe921e2a4,
        PID_APrtyReadCallback17 = 0x9e26d232,
        PID_APrtyReadCallback18 = 0xe99cfa3,
        PID_APrtyReadCallback19 = 0x799eff35,
        PID_APrtyReadCallback20 = 0x2b6f1452,
        PID_APrtyReadCallback21 = 0x5c6824c4,
        PID_APrtyReadCallback22 = 0xc561757e,
        PID_APrtyReadCallback23 = 0xb26645e8,
        PID_APrtyReadCallback24 = 0x2c02d04b,
        PID_APrtyReadCallback25 = 0x5b05e0dd,
        PID_APrtyReadCallback26 = 0xc20cb167,
        PID_APrtyReadCallback27 = 0xb50b81f1,
        PID_APrtyReadCallback28 = 0x25b49c60,
        PID_APrtyReadCallback29 = 0x52b3acf6,
        PID_APrtyReadCallback30 = 0x32742513,
        PID_APrtyReadCallback31 = 0x45731585,
        PID_APrtyReadCallback32 = 0xdc7a443f,
        PID_APrtyReadCallback33 = 0xab7d74a9,
        PID_APrtyReadCallback34 = 0x3519e10a,
        PID_APrtyReadCallback35 = 0x421ed19c,
        PID_APrtyReadCallback36 = 0xdb178026,
        PID_APrtyReadCallback37 = 0xac10b0b0,
        PID_APrtyReadCallback38 = 0x3cafad21,
        PID_APrtyReadCallback39 = 0x4ba89db7,
        PID_APrtyReadCallback40 = 0x7d35b3d4,
        PID_APrtyReadCallback41 = 0xa328342,
        PID_APrtyReadCallback42 = 0x933bd2f8,
        PID_APrtyReadCallback43 = 0xe43ce26e,
        PID_APrtyWriteCallback0 = 0x9cac065,
        PID_APrtyWriteCallback1 = 0x7ecdf0f3,
        PID_APrtyWriteCallback2 = 0xe7c4a149,
        PID_APrtyWriteCallback3 = 0x90c391df,
        PID_APrtyWriteCallback4 = 0xea7047c,
        PID_APrtyWriteCallback5 = 0x79a034ea,
        PID_APrtyWriteCallback6 = 0xe0a96550,
        PID_APrtyWriteCallback7 = 0x97ae55c6,
        PID_APrtyWriteCallback8 = 0x7114857,
        PID_APrtyWriteCallback9 = 0x701678c1,
        PID_APrtyWriteCallback10 = 0xd011b177,
        PID_APrtyWriteCallback11 = 0xa71681e1,
        PID_APrtyWriteCallback12 = 0x3e1fd05b,
        PID_APrtyWriteCallback13 = 0x4918e0cd,
        PID_APrtyWriteCallback14 = 0xd77c756e,
        PID_APrtyWriteCallback15 = 0xa07b45f8,
        PID_APrtyWriteCallback16 = 0x39721442,
        PID_APrtyWriteCallback17 = 0x4e7524d4,
        PID_APrtyWriteCallback18 = 0xdeca3945,
        PID_APrtyWriteCallback19 = 0xa9cd09d3,
        PID_APrtyWriteCallback20 = 0xfb3ce2b4,
        PID_APrtyWriteCallback21 = 0x8c3bd222,
        PID_APrtyWriteCallback22 = 0x15328398,
        PID_APrtyWriteCallback23 = 0x6235b30e,
        PID_APrtyWriteCallback24 = 0xfc5126ad,
        PID_APrtyWriteCallback25 = 0x8b56163b,
        PID_APrtyWriteCallback26 = 0x125f4781,
        PID_APrtyWriteCallback27 = 0x65587717,
        PID_APrtyWriteCallback28 = 0xf5e76a86,
        PID_APrtyWriteCallback29 = 0x82e05a10,
        PID_APrtyWriteCallback30 = 0xe227d3f5,
        PID_APrtyWriteCallback31 = 0x9520e363,
        PID_APrtyWriteCallback32 = 0xc29b2d9,
        PID_APrtyWriteCallback33 = 0x7b2e824f,
        PID_APrtyWriteCallback34 = 0xe54a17ec,
        PID_APrtyWriteCallback35 = 0x924d277a,
        PID_APrtyWriteCallback36 = 0xb4476c0,
        PID_APrtyWriteCallback37 = 0x7c434656,
        PID_APrtyWriteCallback38 = 0xecfc5bc7,
        PID_APrtyWriteCallback39 = 0x9bfb6b51,
        PID_APrtyWriteCallback40 = 0xad664532,
        PID_APrtyWriteCallback41 = 0xda6175a4,
        PID_APrtyWriteCallback42 = 0x4368241e,
        PID_APrtyWriteCallback43 = 0x346f1488,
        PID_COUNT = 176
    };

protected:
    epiChar GetAPrtyVirtual0_Callback() const;
    void SetAPrtyVirtual0_Callback(epiChar value);
    epiWChar GetAPrtyVirtual1_Callback() const;
    void SetAPrtyVirtual1_Callback(epiWChar value);
    epiBool GetAPrtyVirtual2_Callback() const;
    void SetAPrtyVirtual2_Callback(epiBool value);
    epiByte GetAPrtyVirtual3_Callback() const;
    void SetAPrtyVirtual3_Callback(epiByte value);
    epiFloat GetAPrtyVirtual4_Callback() const;
    void SetAPrtyVirtual4_Callback(epiFloat value);
    epiDouble GetAPrtyVirtual5_Callback() const;
    void SetAPrtyVirtual5_Callback(epiDouble value);
    epiSize_t GetAPrtyVirtual6_Callback() const;
    void SetAPrtyVirtual6_Callback(epiSize_t value);
    epiU8 GetAPrtyVirtual7_Callback() const;
    void SetAPrtyVirtual7_Callback(epiU8 value);
    epiU16 GetAPrtyVirtual8_Callback() const;
    void SetAPrtyVirtual8_Callback(epiU16 value);
    epiU32 GetAPrtyVirtual9_Callback() const;
    void SetAPrtyVirtual9_Callback(epiU32 value);
    epiU64 GetAPrtyVirtual10_Callback() const;
    void SetAPrtyVirtual10_Callback(epiU64 value);
    epiS8 GetAPrtyVirtual11_Callback() const;
    void SetAPrtyVirtual11_Callback(epiS8 value);
    epiS16 GetAPrtyVirtual12_Callback() const;
    void SetAPrtyVirtual12_Callback(epiS16 value);
    epiS32 GetAPrtyVirtual13_Callback() const;
    void SetAPrtyVirtual13_Callback(epiS32 value);
    epiS64 GetAPrtyVirtual14_Callback() const;
    void SetAPrtyVirtual14_Callback(epiS64 value);
    const epiString& GetAPrtyVirtual15_Callback() const;
    void SetAPrtyVirtual15_Callback(const epiString& value);
    const epiWString& GetAPrtyVirtual16_Callback() const;
    void SetAPrtyVirtual16_Callback(const epiWString& value);
    const epiArray<epiS32>& GetAPrtyVirtual17_Callback() const;
    void SetAPrtyVirtual17_Callback(const epiArray<epiS32>& value);
    const epiPtrArray<epiS32>& GetAPrtyVirtual18_Callback() const;
    void SetAPrtyVirtual18_Callback(const epiPtrArray<epiS32>& value);
    const epiArray<epiString>& GetAPrtyVirtual19_Callback() const;
    void SetAPrtyVirtual19_Callback(const epiArray<epiString>& value);
    const epiPtrArray<epiString>& GetAPrtyVirtual20_Callback() const;
    void SetAPrtyVirtual20_Callback(const epiPtrArray<epiString>& value);
    const epiVec2f& GetAPrtyVirtual21_Callback() const;
    void SetAPrtyVirtual21_Callback(const epiVec2f& value);
    const epiVec2d& GetAPrtyVirtual22_Callback() const;
    void SetAPrtyVirtual22_Callback(const epiVec2d& value);
    const epiVec2s& GetAPrtyVirtual23_Callback() const;
    void SetAPrtyVirtual23_Callback(const epiVec2s& value);
    const epiVec2u& GetAPrtyVirtual24_Callback() const;
    void SetAPrtyVirtual24_Callback(const epiVec2u& value);
    const epiVec3f& GetAPrtyVirtual25_Callback() const;
    void SetAPrtyVirtual25_Callback(const epiVec3f& value);
    const epiVec3d& GetAPrtyVirtual26_Callback() const;
    void SetAPrtyVirtual26_Callback(const epiVec3d& value);
    const epiVec3s& GetAPrtyVirtual27_Callback() const;
    void SetAPrtyVirtual27_Callback(const epiVec3s& value);
    const epiVec3u& GetAPrtyVirtual28_Callback() const;
    void SetAPrtyVirtual28_Callback(const epiVec3u& value);
    const epiVec4f& GetAPrtyVirtual29_Callback() const;
    void SetAPrtyVirtual29_Callback(const epiVec4f& value);
    const epiVec4d& GetAPrtyVirtual30_Callback() const;
    void SetAPrtyVirtual30_Callback(const epiVec4d& value);
    const epiVec4s& GetAPrtyVirtual31_Callback() const;
    void SetAPrtyVirtual31_Callback(const epiVec4s& value);
    const epiVec4u& GetAPrtyVirtual32_Callback() const;
    void SetAPrtyVirtual32_Callback(const epiVec4u& value);
    const epiMat2x2f& GetAPrtyVirtual33_Callback() const;
    void SetAPrtyVirtual33_Callback(const epiMat2x2f& value);
    const epiMat3x3f& GetAPrtyVirtual34_Callback() const;
    void SetAPrtyVirtual34_Callback(const epiMat3x3f& value);
    const epiMat4x4f& GetAPrtyVirtual35_Callback() const;
    void SetAPrtyVirtual35_Callback(const epiMat4x4f& value);
    const epiComplexf& GetAPrtyVirtual36_Callback() const;
    void SetAPrtyVirtual36_Callback(const epiComplexf& value);
    const epiComplexd& GetAPrtyVirtual37_Callback() const;
    void SetAPrtyVirtual37_Callback(const epiComplexd& value);
    const epiRect2f& GetAPrtyVirtual38_Callback() const;
    void SetAPrtyVirtual38_Callback(const epiRect2f& value);
    const epiRect2d& GetAPrtyVirtual39_Callback() const;
    void SetAPrtyVirtual39_Callback(const epiRect2d& value);
    const epiRect2s& GetAPrtyVirtual40_Callback() const;
    void SetAPrtyVirtual40_Callback(const epiRect2s& value);
    const epiRect2u& GetAPrtyVirtual41_Callback() const;
    void SetAPrtyVirtual41_Callback(const epiRect2u& value);
    const InplaceClass& GetAPrtyVirtual42_Callback() const;
    void SetAPrtyVirtual42_Callback(const InplaceClass& value);
    const InplaceClass* GetAPrtyVirtual43_Callback() const;
    void SetAPrtyVirtual43_Callback(InplaceClass* value);
    epiChar GetAPrtyReadCallback0_Callback() const;
    epiWChar GetAPrtyReadCallback1_Callback() const;
    epiBool GetAPrtyReadCallback2_Callback() const;
    epiByte GetAPrtyReadCallback3_Callback() const;
    epiFloat GetAPrtyReadCallback4_Callback() const;
    epiDouble GetAPrtyReadCallback5_Callback() const;
    epiSize_t GetAPrtyReadCallback6_Callback() const;
    epiU8 GetAPrtyReadCallback7_Callback() const;
    epiU16 GetAPrtyReadCallback8_Callback() const;
    epiU32 GetAPrtyReadCallback9_Callback() const;
    epiU64 GetAPrtyReadCallback10_Callback() const;
    epiS8 GetAPrtyReadCallback11_Callback() const;
    epiS16 GetAPrtyReadCallback12_Callback() const;
    epiS32 GetAPrtyReadCallback13_Callback() const;
    epiS64 GetAPrtyReadCallback14_Callback() const;
    const epiString& GetAPrtyReadCallback15_Callback() const;
    const epiWString& GetAPrtyReadCallback16_Callback() const;
    const epiArray<epiS32>& GetAPrtyReadCallback17_Callback() const;
    const epiPtrArray<epiS32>& GetAPrtyReadCallback18_Callback() const;
    const epiArray<epiString>& GetAPrtyReadCallback19_Callback() const;
    const epiPtrArray<epiString>& GetAPrtyReadCallback20_Callback() const;
    const epiVec2f& GetAPrtyReadCallback21_Callback() const;
    const epiVec2d& GetAPrtyReadCallback22_Callback() const;
    const epiVec2s& GetAPrtyReadCallback23_Callback() const;
    const epiVec2u& GetAPrtyReadCallback24_Callback() const;
    const epiVec3f& GetAPrtyReadCallback25_Callback() const;
    const epiVec3d& GetAPrtyReadCallback26_Callback() const;
    const epiVec3s& GetAPrtyReadCallback27_Callback() const;
    const epiVec3u& GetAPrtyReadCallback28_Callback() const;
    const epiVec4f& GetAPrtyReadCallback29_Callback() const;
    const epiVec4d& GetAPrtyReadCallback30_Callback() const;
    const epiVec4s& GetAPrtyReadCallback31_Callback() const;
    const epiVec4u& GetAPrtyReadCallback32_Callback() const;
    const epiMat2x2f& GetAPrtyReadCallback33_Callback() const;
    const epiMat3x3f& GetAPrtyReadCallback34_Callback() const;
    const epiMat4x4f& GetAPrtyReadCallback35_Callback() const;
    const epiComplexf& GetAPrtyReadCallback36_Callback() const;
    const epiComplexd& GetAPrtyReadCallback37_Callback() const;
    const epiRect2f& GetAPrtyReadCallback38_Callback() const;
    const epiRect2d& GetAPrtyReadCallback39_Callback() const;
    const epiRect2s& GetAPrtyReadCallback40_Callback() const;
    const epiRect2u& GetAPrtyReadCallback41_Callback() const;
    const InplaceClass& GetAPrtyReadCallback42_Callback() const;
    const InplaceClass* GetAPrtyReadCallback43_Callback() const;
    void SetAPrtyWriteCallback0_Callback(epiChar value);
    void SetAPrtyWriteCallback1_Callback(epiWChar value);
    void SetAPrtyWriteCallback2_Callback(epiBool value);
    void SetAPrtyWriteCallback3_Callback(epiByte value);
    void SetAPrtyWriteCallback4_Callback(epiFloat value);
    void SetAPrtyWriteCallback5_Callback(epiDouble value);
    void SetAPrtyWriteCallback6_Callback(epiSize_t value);
    void SetAPrtyWriteCallback7_Callback(epiU8 value);
    void SetAPrtyWriteCallback8_Callback(epiU16 value);
    void SetAPrtyWriteCallback9_Callback(epiU32 value);
    void SetAPrtyWriteCallback10_Callback(epiU64 value);
    void SetAPrtyWriteCallback11_Callback(epiS8 value);
    void SetAPrtyWriteCallback12_Callback(epiS16 value);
    void SetAPrtyWriteCallback13_Callback(epiS32 value);
    void SetAPrtyWriteCallback14_Callback(epiS64 value);
    void SetAPrtyWriteCallback15_Callback(const epiString& value);
    void SetAPrtyWriteCallback16_Callback(const epiWString& value);
    void SetAPrtyWriteCallback17_Callback(const epiArray<epiS32>& value);
    void SetAPrtyWriteCallback18_Callback(const epiPtrArray<epiS32>& value);
    void SetAPrtyWriteCallback19_Callback(const epiArray<epiString>& value);
    void SetAPrtyWriteCallback20_Callback(const epiPtrArray<epiString>& value);
    void SetAPrtyWriteCallback21_Callback(const epiVec2f& value);
    void SetAPrtyWriteCallback22_Callback(const epiVec2d& value);
    void SetAPrtyWriteCallback23_Callback(const epiVec2s& value);
    void SetAPrtyWriteCallback24_Callback(const epiVec2u& value);
    void SetAPrtyWriteCallback25_Callback(const epiVec3f& value);
    void SetAPrtyWriteCallback26_Callback(const epiVec3d& value);
    void SetAPrtyWriteCallback27_Callback(const epiVec3s& value);
    void SetAPrtyWriteCallback28_Callback(const epiVec3u& value);
    void SetAPrtyWriteCallback29_Callback(const epiVec4f& value);
    void SetAPrtyWriteCallback30_Callback(const epiVec4d& value);
    void SetAPrtyWriteCallback31_Callback(const epiVec4s& value);
    void SetAPrtyWriteCallback32_Callback(const epiVec4u& value);
    void SetAPrtyWriteCallback33_Callback(const epiMat2x2f& value);
    void SetAPrtyWriteCallback34_Callback(const epiMat3x3f& value);
    void SetAPrtyWriteCallback35_Callback(const epiMat4x4f& value);
    void SetAPrtyWriteCallback36_Callback(const epiComplexf& value);
    void SetAPrtyWriteCallback37_Callback(const epiComplexd& value);
    void SetAPrtyWriteCallback38_Callback(const epiRect2f& value);
    void SetAPrtyWriteCallback39_Callback(const epiRect2d& value);
    void SetAPrtyWriteCallback40_Callback(const epiRect2s& value);
    void SetAPrtyWriteCallback41_Callback(const epiRect2u& value);
    void SetAPrtyWriteCallback42_Callback(const InplaceClass& value);
    void SetAPrtyWriteCallback43_Callback(InplaceClass* value);

protected:
    epiChar m_APrty0{'\0'};
    epiWChar m_APrty1{L'\0'};
    epiBool m_APrty2{false};
    epiByte m_APrty3{0};
    epiFloat m_APrty4{0.0f};
    epiDouble m_APrty5{0.0};
    epiSize_t m_APrty6{0};
    epiU8 m_APrty7{0};
    epiU16 m_APrty8{0};
    epiU32 m_APrty9{0};
    epiU64 m_APrty10{0};
    epiS8 m_APrty11{0};
    epiS16 m_APrty12{0};
    epiS32 m_APrty13{0};
    epiS64 m_APrty14{0};
    epiString m_APrty15{epiDEBUG_ONLY("Empty")};
    epiWString m_APrty16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_APrty17{};
    epiPtrArray<epiS32> m_APrty18{};
    epiArray<epiString> m_APrty19{};
    epiPtrArray<epiString> m_APrty20{};
    epiVec2f m_APrty21{};
    epiVec2d m_APrty22{};
    epiVec2s m_APrty23{};
    epiVec2u m_APrty24{};
    epiVec3f m_APrty25{};
    epiVec3d m_APrty26{};
    epiVec3s m_APrty27{};
    epiVec3u m_APrty28{};
    epiVec4f m_APrty29{};
    epiVec4d m_APrty30{};
    epiVec4s m_APrty31{};
    epiVec4u m_APrty32{};
    epiMat2x2f m_APrty33{};
    epiMat3x3f m_APrty34{};
    epiMat4x4f m_APrty35{};
    epiComplexf m_APrty36{};
    epiComplexd m_APrty37{};
    epiRect2f m_APrty38{};
    epiRect2d m_APrty39{};
    epiRect2s m_APrty40{};
    epiRect2u m_APrty41{};
    InplaceClass m_APrty42{};
    InplaceClass* m_APrty43{nullptr};
    epiChar m_APrtyReadCallback0{'\0'};
    epiWChar m_APrtyReadCallback1{L'\0'};
    epiBool m_APrtyReadCallback2{false};
    epiByte m_APrtyReadCallback3{0};
    epiFloat m_APrtyReadCallback4{0.0f};
    epiDouble m_APrtyReadCallback5{0.0};
    epiSize_t m_APrtyReadCallback6{0};
    epiU8 m_APrtyReadCallback7{0};
    epiU16 m_APrtyReadCallback8{0};
    epiU32 m_APrtyReadCallback9{0};
    epiU64 m_APrtyReadCallback10{0};
    epiS8 m_APrtyReadCallback11{0};
    epiS16 m_APrtyReadCallback12{0};
    epiS32 m_APrtyReadCallback13{0};
    epiS64 m_APrtyReadCallback14{0};
    epiString m_APrtyReadCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_APrtyReadCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_APrtyReadCallback17{};
    epiPtrArray<epiS32> m_APrtyReadCallback18{};
    epiArray<epiString> m_APrtyReadCallback19{};
    epiPtrArray<epiString> m_APrtyReadCallback20{};
    epiVec2f m_APrtyReadCallback21{};
    epiVec2d m_APrtyReadCallback22{};
    epiVec2s m_APrtyReadCallback23{};
    epiVec2u m_APrtyReadCallback24{};
    epiVec3f m_APrtyReadCallback25{};
    epiVec3d m_APrtyReadCallback26{};
    epiVec3s m_APrtyReadCallback27{};
    epiVec3u m_APrtyReadCallback28{};
    epiVec4f m_APrtyReadCallback29{};
    epiVec4d m_APrtyReadCallback30{};
    epiVec4s m_APrtyReadCallback31{};
    epiVec4u m_APrtyReadCallback32{};
    epiMat2x2f m_APrtyReadCallback33{};
    epiMat3x3f m_APrtyReadCallback34{};
    epiMat4x4f m_APrtyReadCallback35{};
    epiComplexf m_APrtyReadCallback36{};
    epiComplexd m_APrtyReadCallback37{};
    epiRect2f m_APrtyReadCallback38{};
    epiRect2d m_APrtyReadCallback39{};
    epiRect2s m_APrtyReadCallback40{};
    epiRect2u m_APrtyReadCallback41{};
    InplaceClass m_APrtyReadCallback42{};
    InplaceClass* m_APrtyReadCallback43{nullptr};
    epiChar m_APrtyWriteCallback0{'\0'};
    epiWChar m_APrtyWriteCallback1{L'\0'};
    epiBool m_APrtyWriteCallback2{false};
    epiByte m_APrtyWriteCallback3{0};
    epiFloat m_APrtyWriteCallback4{0.0f};
    epiDouble m_APrtyWriteCallback5{0.0};
    epiSize_t m_APrtyWriteCallback6{0};
    epiU8 m_APrtyWriteCallback7{0};
    epiU16 m_APrtyWriteCallback8{0};
    epiU32 m_APrtyWriteCallback9{0};
    epiU64 m_APrtyWriteCallback10{0};
    epiS8 m_APrtyWriteCallback11{0};
    epiS16 m_APrtyWriteCallback12{0};
    epiS32 m_APrtyWriteCallback13{0};
    epiS64 m_APrtyWriteCallback14{0};
    epiString m_APrtyWriteCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_APrtyWriteCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_APrtyWriteCallback17{};
    epiPtrArray<epiS32> m_APrtyWriteCallback18{};
    epiArray<epiString> m_APrtyWriteCallback19{};
    epiPtrArray<epiString> m_APrtyWriteCallback20{};
    epiVec2f m_APrtyWriteCallback21{};
    epiVec2d m_APrtyWriteCallback22{};
    epiVec2s m_APrtyWriteCallback23{};
    epiVec2u m_APrtyWriteCallback24{};
    epiVec3f m_APrtyWriteCallback25{};
    epiVec3d m_APrtyWriteCallback26{};
    epiVec3s m_APrtyWriteCallback27{};
    epiVec3u m_APrtyWriteCallback28{};
    epiVec4f m_APrtyWriteCallback29{};
    epiVec4d m_APrtyWriteCallback30{};
    epiVec4s m_APrtyWriteCallback31{};
    epiVec4u m_APrtyWriteCallback32{};
    epiMat2x2f m_APrtyWriteCallback33{};
    epiMat3x3f m_APrtyWriteCallback34{};
    epiMat4x4f m_APrtyWriteCallback35{};
    epiComplexf m_APrtyWriteCallback36{};
    epiComplexd m_APrtyWriteCallback37{};
    epiRect2f m_APrtyWriteCallback38{};
    epiRect2d m_APrtyWriteCallback39{};
    epiRect2s m_APrtyWriteCallback40{};
    epiRect2u m_APrtyWriteCallback41{};
    InplaceClass m_APrtyWriteCallback42{};
    InplaceClass* m_APrtyWriteCallback43{nullptr};

EPI_GENREGION_END(TestClassA)

public:
    virtual void Reset();
};

class TestClassB : public TestClassA
{
EPI_GENREGION_BEGIN(TestClassB)

EPI_GENHIDDEN_TestClassB()

public:
    constexpr static epiMetaTypeID TypeID{0xe39a468c};

    enum TestClassB_PIDs
    {
        PID_BPrty0 = 0x81ab9f87,
        PID_BPrty1 = 0xf6acaf11,
        PID_BPrty2 = 0x6fa5feab,
        PID_BPrty3 = 0x18a2ce3d,
        PID_BPrty4 = 0x86c65b9e,
        PID_BPrty5 = 0xf1c16b08,
        PID_BPrty6 = 0x68c83ab2,
        PID_BPrty7 = 0x1fcf0a24,
        PID_BPrty8 = 0x8f7017b5,
        PID_BPrty9 = 0xf8772723,
        PID_BPrty10 = 0x9e9d537c,
        PID_BPrty11 = 0xe99a63ea,
        PID_BPrty12 = 0x70933250,
        PID_BPrty13 = 0x79402c6,
        PID_BPrty14 = 0x99f09765,
        PID_BPrty15 = 0xeef7a7f3,
        PID_BPrty16 = 0x77fef649,
        PID_BPrty17 = 0xf9c6df,
        PID_BPrty18 = 0x9046db4e,
        PID_BPrty19 = 0xe741ebd8,
        PID_BPrty20 = 0xb5b000bf,
        PID_BPrty21 = 0xc2b73029,
        PID_BPrty22 = 0x5bbe6193,
        PID_BPrty23 = 0x2cb95105,
        PID_BPrty24 = 0xb2ddc4a6,
        PID_BPrty25 = 0xc5daf430,
        PID_BPrty26 = 0x5cd3a58a,
        PID_BPrty27 = 0x2bd4951c,
        PID_BPrty28 = 0xbb6b888d,
        PID_BPrty29 = 0xcc6cb81b,
        PID_BPrty30 = 0xacab31fe,
        PID_BPrty31 = 0xdbac0168,
        PID_BPrty32 = 0x42a550d2,
        PID_BPrty33 = 0x35a26044,
        PID_BPrty34 = 0xabc6f5e7,
        PID_BPrty35 = 0xdcc1c571,
        PID_BPrty36 = 0x45c894cb,
        PID_BPrty37 = 0x32cfa45d,
        PID_BPrty38 = 0xa270b9cc,
        PID_BPrty39 = 0xd577895a,
        PID_BPrty40 = 0xe3eaa739,
        PID_BPrty41 = 0x94ed97af,
        PID_BPrty42 = 0xde4c615,
        PID_BPrty43 = 0x7ae3f683,
        PID_BPrtyVirtual0 = 0xd6887f3c,
        PID_BPrtyVirtual1 = 0xa18f4faa,
        PID_BPrtyVirtual2 = 0x38861e10,
        PID_BPrtyVirtual3 = 0x4f812e86,
        PID_BPrtyVirtual4 = 0xd1e5bb25,
        PID_BPrtyVirtual5 = 0xa6e28bb3,
        PID_BPrtyVirtual6 = 0x3febda09,
        PID_BPrtyVirtual7 = 0x48ecea9f,
        PID_BPrtyVirtual8 = 0xd853f70e,
        PID_BPrtyVirtual9 = 0xaf54c798,
        PID_BPrtyVirtual10 = 0xc2791a98,
        PID_BPrtyVirtual11 = 0xb57e2a0e,
        PID_BPrtyVirtual12 = 0x2c777bb4,
        PID_BPrtyVirtual13 = 0x5b704b22,
        PID_BPrtyVirtual14 = 0xc514de81,
        PID_BPrtyVirtual15 = 0xb213ee17,
        PID_BPrtyVirtual16 = 0x2b1abfad,
        PID_BPrtyVirtual17 = 0x5c1d8f3b,
        PID_BPrtyVirtual18 = 0xcca292aa,
        PID_BPrtyVirtual19 = 0xbba5a23c,
        PID_BPrtyVirtual20 = 0xe954495b,
        PID_BPrtyVirtual21 = 0x9e5379cd,
        PID_BPrtyVirtual22 = 0x75a2877,
        PID_BPrtyVirtual23 = 0x705d18e1,
        PID_BPrtyVirtual24 = 0xee398d42,
        PID_BPrtyVirtual25 = 0x993ebdd4,
        PID_BPrtyVirtual26 = 0x37ec6e,
        PID_BPrtyVirtual27 = 0x7730dcf8,
        PID_BPrtyVirtual28 = 0xe78fc169,
        PID_BPrtyVirtual29 = 0x9088f1ff,
        PID_BPrtyVirtual30 = 0xf04f781a,
        PID_BPrtyVirtual31 = 0x8748488c,
        PID_BPrtyVirtual32 = 0x1e411936,
        PID_BPrtyVirtual33 = 0x694629a0,
        PID_BPrtyVirtual34 = 0xf722bc03,
        PID_BPrtyVirtual35 = 0x80258c95,
        PID_BPrtyVirtual36 = 0x192cdd2f,
        PID_BPrtyVirtual37 = 0x6e2bedb9,
        PID_BPrtyVirtual38 = 0xfe94f028,
        PID_BPrtyVirtual39 = 0x8993c0be,
        PID_BPrtyVirtual40 = 0xbf0eeedd,
        PID_BPrtyVirtual41 = 0xc809de4b,
        PID_BPrtyVirtual42 = 0x51008ff1,
        PID_BPrtyVirtual43 = 0x2607bf67,
        PID_BPrtyReadCallback0 = 0xd0ac0ce2,
        PID_BPrtyReadCallback1 = 0xa7ab3c74,
        PID_BPrtyReadCallback2 = 0x3ea26dce,
        PID_BPrtyReadCallback3 = 0x49a55d58,
        PID_BPrtyReadCallback4 = 0xd7c1c8fb,
        PID_BPrtyReadCallback5 = 0xa0c6f86d,
        PID_BPrtyReadCallback6 = 0x39cfa9d7,
        PID_BPrtyReadCallback7 = 0x4ec89941,
        PID_BPrtyReadCallback8 = 0xde7784d0,
        PID_BPrtyReadCallback9 = 0xa970b446,
        PID_BPrtyReadCallback10 = 0xa314c138,
        PID_BPrtyReadCallback11 = 0xd413f1ae,
        PID_BPrtyReadCallback12 = 0x4d1aa014,
        PID_BPrtyReadCallback13 = 0x3a1d9082,
        PID_BPrtyReadCallback14 = 0xa4790521,
        PID_BPrtyReadCallback15 = 0xd37e35b7,
        PID_BPrtyReadCallback16 = 0x4a77640d,
        PID_BPrtyReadCallback17 = 0x3d70549b,
        PID_BPrtyReadCallback18 = 0xadcf490a,
        PID_BPrtyReadCallback19 = 0xdac8799c,
        PID_BPrtyReadCallback20 = 0x883992fb,
        PID_BPrtyReadCallback21 = 0xff3ea26d,
        PID_BPrtyReadCallback22 = 0x6637f3d7,
        PID_BPrtyReadCallback23 = 0x1130c341,
        PID_BPrtyReadCallback24 = 0x8f5456e2,
        PID_BPrtyReadCallback25 = 0xf8536674,
        PID_BPrtyReadCallback26 = 0x615a37ce,
        PID_BPrtyReadCallback27 = 0x165d0758,
        PID_BPrtyReadCallback28 = 0x86e21ac9,
        PID_BPrtyReadCallback29 = 0xf1e52a5f,
        PID_BPrtyReadCallback30 = 0x9122a3ba,
        PID_BPrtyReadCallback31 = 0xe625932c,
        PID_BPrtyReadCallback32 = 0x7f2cc296,
        PID_BPrtyReadCallback33 = 0x82bf200,
        PID_BPrtyReadCallback34 = 0x964f67a3,
        PID_BPrtyReadCallback35 = 0xe1485735,
        PID_BPrtyReadCallback36 = 0x7841068f,
        PID_BPrtyReadCallback37 = 0xf463619,
        PID_BPrtyReadCallback38 = 0x9ff92b88,
        PID_BPrtyReadCallback39 = 0xe8fe1b1e,
        PID_BPrtyReadCallback40 = 0xde63357d,
        PID_BPrtyReadCallback41 = 0xa96405eb,
        PID_BPrtyReadCallback42 = 0x306d5451,
        PID_BPrtyReadCallback43 = 0x476a64c7,
        PID_BPrtyWriteCallback0 = 0xaa9c46cc,
        PID_BPrtyWriteCallback1 = 0xdd9b765a,
        PID_BPrtyWriteCallback2 = 0x449227e0,
        PID_BPrtyWriteCallback3 = 0x33951776,
        PID_BPrtyWriteCallback4 = 0xadf182d5,
        PID_BPrtyWriteCallback5 = 0xdaf6b243,
        PID_BPrtyWriteCallback6 = 0x43ffe3f9,
        PID_BPrtyWriteCallback7 = 0x34f8d36f,
        PID_BPrtyWriteCallback8 = 0xa447cefe,
        PID_BPrtyWriteCallback9 = 0xd340fe68,
        PID_BPrtyWriteCallback10 = 0x7fb8fcbd,
        PID_BPrtyWriteCallback11 = 0x8bfcc2b,
        PID_BPrtyWriteCallback12 = 0x91b69d91,
        PID_BPrtyWriteCallback13 = 0xe6b1ad07,
        PID_BPrtyWriteCallback14 = 0x78d538a4,
        PID_BPrtyWriteCallback15 = 0xfd20832,
        PID_BPrtyWriteCallback16 = 0x96db5988,
        PID_BPrtyWriteCallback17 = 0xe1dc691e,
        PID_BPrtyWriteCallback18 = 0x7163748f,
        PID_BPrtyWriteCallback19 = 0x6644419,
        PID_BPrtyWriteCallback20 = 0x5495af7e,
        PID_BPrtyWriteCallback21 = 0x23929fe8,
        PID_BPrtyWriteCallback22 = 0xba9bce52,
        PID_BPrtyWriteCallback23 = 0xcd9cfec4,
        PID_BPrtyWriteCallback24 = 0x53f86b67,
        PID_BPrtyWriteCallback25 = 0x24ff5bf1,
        PID_BPrtyWriteCallback26 = 0xbdf60a4b,
        PID_BPrtyWriteCallback27 = 0xcaf13add,
        PID_BPrtyWriteCallback28 = 0x5a4e274c,
        PID_BPrtyWriteCallback29 = 0x2d4917da,
        PID_BPrtyWriteCallback30 = 0x4d8e9e3f,
        PID_BPrtyWriteCallback31 = 0x3a89aea9,
        PID_BPrtyWriteCallback32 = 0xa380ff13,
        PID_BPrtyWriteCallback33 = 0xd487cf85,
        PID_BPrtyWriteCallback34 = 0x4ae35a26,
        PID_BPrtyWriteCallback35 = 0x3de46ab0,
        PID_BPrtyWriteCallback36 = 0xa4ed3b0a,
        PID_BPrtyWriteCallback37 = 0xd3ea0b9c,
        PID_BPrtyWriteCallback38 = 0x4355160d,
        PID_BPrtyWriteCallback39 = 0x3452269b,
        PID_BPrtyWriteCallback40 = 0x2cf08f8,
        PID_BPrtyWriteCallback41 = 0x75c8386e,
        PID_BPrtyWriteCallback42 = 0xecc169d4,
        PID_BPrtyWriteCallback43 = 0x9bc65942,
        PID_COUNT = 176
    };

protected:
    epiChar GetBPrtyVirtual0_Callback() const;
    void SetBPrtyVirtual0_Callback(epiChar value);
    epiWChar GetBPrtyVirtual1_Callback() const;
    void SetBPrtyVirtual1_Callback(epiWChar value);
    epiBool GetBPrtyVirtual2_Callback() const;
    void SetBPrtyVirtual2_Callback(epiBool value);
    epiByte GetBPrtyVirtual3_Callback() const;
    void SetBPrtyVirtual3_Callback(epiByte value);
    epiFloat GetBPrtyVirtual4_Callback() const;
    void SetBPrtyVirtual4_Callback(epiFloat value);
    epiDouble GetBPrtyVirtual5_Callback() const;
    void SetBPrtyVirtual5_Callback(epiDouble value);
    epiSize_t GetBPrtyVirtual6_Callback() const;
    void SetBPrtyVirtual6_Callback(epiSize_t value);
    epiU8 GetBPrtyVirtual7_Callback() const;
    void SetBPrtyVirtual7_Callback(epiU8 value);
    epiU16 GetBPrtyVirtual8_Callback() const;
    void SetBPrtyVirtual8_Callback(epiU16 value);
    epiU32 GetBPrtyVirtual9_Callback() const;
    void SetBPrtyVirtual9_Callback(epiU32 value);
    epiU64 GetBPrtyVirtual10_Callback() const;
    void SetBPrtyVirtual10_Callback(epiU64 value);
    epiS8 GetBPrtyVirtual11_Callback() const;
    void SetBPrtyVirtual11_Callback(epiS8 value);
    epiS16 GetBPrtyVirtual12_Callback() const;
    void SetBPrtyVirtual12_Callback(epiS16 value);
    epiS32 GetBPrtyVirtual13_Callback() const;
    void SetBPrtyVirtual13_Callback(epiS32 value);
    epiS64 GetBPrtyVirtual14_Callback() const;
    void SetBPrtyVirtual14_Callback(epiS64 value);
    const epiString& GetBPrtyVirtual15_Callback() const;
    void SetBPrtyVirtual15_Callback(const epiString& value);
    const epiWString& GetBPrtyVirtual16_Callback() const;
    void SetBPrtyVirtual16_Callback(const epiWString& value);
    const epiArray<epiS32>& GetBPrtyVirtual17_Callback() const;
    void SetBPrtyVirtual17_Callback(const epiArray<epiS32>& value);
    const epiPtrArray<epiS32>& GetBPrtyVirtual18_Callback() const;
    void SetBPrtyVirtual18_Callback(const epiPtrArray<epiS32>& value);
    const epiArray<epiString>& GetBPrtyVirtual19_Callback() const;
    void SetBPrtyVirtual19_Callback(const epiArray<epiString>& value);
    const epiPtrArray<epiString>& GetBPrtyVirtual20_Callback() const;
    void SetBPrtyVirtual20_Callback(const epiPtrArray<epiString>& value);
    const epiVec2f& GetBPrtyVirtual21_Callback() const;
    void SetBPrtyVirtual21_Callback(const epiVec2f& value);
    const epiVec2d& GetBPrtyVirtual22_Callback() const;
    void SetBPrtyVirtual22_Callback(const epiVec2d& value);
    const epiVec2s& GetBPrtyVirtual23_Callback() const;
    void SetBPrtyVirtual23_Callback(const epiVec2s& value);
    const epiVec2u& GetBPrtyVirtual24_Callback() const;
    void SetBPrtyVirtual24_Callback(const epiVec2u& value);
    const epiVec3f& GetBPrtyVirtual25_Callback() const;
    void SetBPrtyVirtual25_Callback(const epiVec3f& value);
    const epiVec3d& GetBPrtyVirtual26_Callback() const;
    void SetBPrtyVirtual26_Callback(const epiVec3d& value);
    const epiVec3s& GetBPrtyVirtual27_Callback() const;
    void SetBPrtyVirtual27_Callback(const epiVec3s& value);
    const epiVec3u& GetBPrtyVirtual28_Callback() const;
    void SetBPrtyVirtual28_Callback(const epiVec3u& value);
    const epiVec4f& GetBPrtyVirtual29_Callback() const;
    void SetBPrtyVirtual29_Callback(const epiVec4f& value);
    const epiVec4d& GetBPrtyVirtual30_Callback() const;
    void SetBPrtyVirtual30_Callback(const epiVec4d& value);
    const epiVec4s& GetBPrtyVirtual31_Callback() const;
    void SetBPrtyVirtual31_Callback(const epiVec4s& value);
    const epiVec4u& GetBPrtyVirtual32_Callback() const;
    void SetBPrtyVirtual32_Callback(const epiVec4u& value);
    const epiMat2x2f& GetBPrtyVirtual33_Callback() const;
    void SetBPrtyVirtual33_Callback(const epiMat2x2f& value);
    const epiMat3x3f& GetBPrtyVirtual34_Callback() const;
    void SetBPrtyVirtual34_Callback(const epiMat3x3f& value);
    const epiMat4x4f& GetBPrtyVirtual35_Callback() const;
    void SetBPrtyVirtual35_Callback(const epiMat4x4f& value);
    const epiComplexf& GetBPrtyVirtual36_Callback() const;
    void SetBPrtyVirtual36_Callback(const epiComplexf& value);
    const epiComplexd& GetBPrtyVirtual37_Callback() const;
    void SetBPrtyVirtual37_Callback(const epiComplexd& value);
    const epiRect2f& GetBPrtyVirtual38_Callback() const;
    void SetBPrtyVirtual38_Callback(const epiRect2f& value);
    const epiRect2d& GetBPrtyVirtual39_Callback() const;
    void SetBPrtyVirtual39_Callback(const epiRect2d& value);
    const epiRect2s& GetBPrtyVirtual40_Callback() const;
    void SetBPrtyVirtual40_Callback(const epiRect2s& value);
    const epiRect2u& GetBPrtyVirtual41_Callback() const;
    void SetBPrtyVirtual41_Callback(const epiRect2u& value);
    const InplaceClass& GetBPrtyVirtual42_Callback() const;
    void SetBPrtyVirtual42_Callback(const InplaceClass& value);
    const InplaceClass* GetBPrtyVirtual43_Callback() const;
    void SetBPrtyVirtual43_Callback(InplaceClass* value);
    epiChar GetBPrtyReadCallback0_Callback() const;
    epiWChar GetBPrtyReadCallback1_Callback() const;
    epiBool GetBPrtyReadCallback2_Callback() const;
    epiByte GetBPrtyReadCallback3_Callback() const;
    epiFloat GetBPrtyReadCallback4_Callback() const;
    epiDouble GetBPrtyReadCallback5_Callback() const;
    epiSize_t GetBPrtyReadCallback6_Callback() const;
    epiU8 GetBPrtyReadCallback7_Callback() const;
    epiU16 GetBPrtyReadCallback8_Callback() const;
    epiU32 GetBPrtyReadCallback9_Callback() const;
    epiU64 GetBPrtyReadCallback10_Callback() const;
    epiS8 GetBPrtyReadCallback11_Callback() const;
    epiS16 GetBPrtyReadCallback12_Callback() const;
    epiS32 GetBPrtyReadCallback13_Callback() const;
    epiS64 GetBPrtyReadCallback14_Callback() const;
    const epiString& GetBPrtyReadCallback15_Callback() const;
    const epiWString& GetBPrtyReadCallback16_Callback() const;
    const epiArray<epiS32>& GetBPrtyReadCallback17_Callback() const;
    const epiPtrArray<epiS32>& GetBPrtyReadCallback18_Callback() const;
    const epiArray<epiString>& GetBPrtyReadCallback19_Callback() const;
    const epiPtrArray<epiString>& GetBPrtyReadCallback20_Callback() const;
    const epiVec2f& GetBPrtyReadCallback21_Callback() const;
    const epiVec2d& GetBPrtyReadCallback22_Callback() const;
    const epiVec2s& GetBPrtyReadCallback23_Callback() const;
    const epiVec2u& GetBPrtyReadCallback24_Callback() const;
    const epiVec3f& GetBPrtyReadCallback25_Callback() const;
    const epiVec3d& GetBPrtyReadCallback26_Callback() const;
    const epiVec3s& GetBPrtyReadCallback27_Callback() const;
    const epiVec3u& GetBPrtyReadCallback28_Callback() const;
    const epiVec4f& GetBPrtyReadCallback29_Callback() const;
    const epiVec4d& GetBPrtyReadCallback30_Callback() const;
    const epiVec4s& GetBPrtyReadCallback31_Callback() const;
    const epiVec4u& GetBPrtyReadCallback32_Callback() const;
    const epiMat2x2f& GetBPrtyReadCallback33_Callback() const;
    const epiMat3x3f& GetBPrtyReadCallback34_Callback() const;
    const epiMat4x4f& GetBPrtyReadCallback35_Callback() const;
    const epiComplexf& GetBPrtyReadCallback36_Callback() const;
    const epiComplexd& GetBPrtyReadCallback37_Callback() const;
    const epiRect2f& GetBPrtyReadCallback38_Callback() const;
    const epiRect2d& GetBPrtyReadCallback39_Callback() const;
    const epiRect2s& GetBPrtyReadCallback40_Callback() const;
    const epiRect2u& GetBPrtyReadCallback41_Callback() const;
    const InplaceClass& GetBPrtyReadCallback42_Callback() const;
    const InplaceClass* GetBPrtyReadCallback43_Callback() const;
    void SetBPrtyWriteCallback0_Callback(epiChar value);
    void SetBPrtyWriteCallback1_Callback(epiWChar value);
    void SetBPrtyWriteCallback2_Callback(epiBool value);
    void SetBPrtyWriteCallback3_Callback(epiByte value);
    void SetBPrtyWriteCallback4_Callback(epiFloat value);
    void SetBPrtyWriteCallback5_Callback(epiDouble value);
    void SetBPrtyWriteCallback6_Callback(epiSize_t value);
    void SetBPrtyWriteCallback7_Callback(epiU8 value);
    void SetBPrtyWriteCallback8_Callback(epiU16 value);
    void SetBPrtyWriteCallback9_Callback(epiU32 value);
    void SetBPrtyWriteCallback10_Callback(epiU64 value);
    void SetBPrtyWriteCallback11_Callback(epiS8 value);
    void SetBPrtyWriteCallback12_Callback(epiS16 value);
    void SetBPrtyWriteCallback13_Callback(epiS32 value);
    void SetBPrtyWriteCallback14_Callback(epiS64 value);
    void SetBPrtyWriteCallback15_Callback(const epiString& value);
    void SetBPrtyWriteCallback16_Callback(const epiWString& value);
    void SetBPrtyWriteCallback17_Callback(const epiArray<epiS32>& value);
    void SetBPrtyWriteCallback18_Callback(const epiPtrArray<epiS32>& value);
    void SetBPrtyWriteCallback19_Callback(const epiArray<epiString>& value);
    void SetBPrtyWriteCallback20_Callback(const epiPtrArray<epiString>& value);
    void SetBPrtyWriteCallback21_Callback(const epiVec2f& value);
    void SetBPrtyWriteCallback22_Callback(const epiVec2d& value);
    void SetBPrtyWriteCallback23_Callback(const epiVec2s& value);
    void SetBPrtyWriteCallback24_Callback(const epiVec2u& value);
    void SetBPrtyWriteCallback25_Callback(const epiVec3f& value);
    void SetBPrtyWriteCallback26_Callback(const epiVec3d& value);
    void SetBPrtyWriteCallback27_Callback(const epiVec3s& value);
    void SetBPrtyWriteCallback28_Callback(const epiVec3u& value);
    void SetBPrtyWriteCallback29_Callback(const epiVec4f& value);
    void SetBPrtyWriteCallback30_Callback(const epiVec4d& value);
    void SetBPrtyWriteCallback31_Callback(const epiVec4s& value);
    void SetBPrtyWriteCallback32_Callback(const epiVec4u& value);
    void SetBPrtyWriteCallback33_Callback(const epiMat2x2f& value);
    void SetBPrtyWriteCallback34_Callback(const epiMat3x3f& value);
    void SetBPrtyWriteCallback35_Callback(const epiMat4x4f& value);
    void SetBPrtyWriteCallback36_Callback(const epiComplexf& value);
    void SetBPrtyWriteCallback37_Callback(const epiComplexd& value);
    void SetBPrtyWriteCallback38_Callback(const epiRect2f& value);
    void SetBPrtyWriteCallback39_Callback(const epiRect2d& value);
    void SetBPrtyWriteCallback40_Callback(const epiRect2s& value);
    void SetBPrtyWriteCallback41_Callback(const epiRect2u& value);
    void SetBPrtyWriteCallback42_Callback(const InplaceClass& value);
    void SetBPrtyWriteCallback43_Callback(InplaceClass* value);

protected:
    epiChar m_BPrty0{'\0'};
    epiWChar m_BPrty1{L'\0'};
    epiBool m_BPrty2{false};
    epiByte m_BPrty3{0};
    epiFloat m_BPrty4{0.0f};
    epiDouble m_BPrty5{0.0};
    epiSize_t m_BPrty6{0};
    epiU8 m_BPrty7{0};
    epiU16 m_BPrty8{0};
    epiU32 m_BPrty9{0};
    epiU64 m_BPrty10{0};
    epiS8 m_BPrty11{0};
    epiS16 m_BPrty12{0};
    epiS32 m_BPrty13{0};
    epiS64 m_BPrty14{0};
    epiString m_BPrty15{epiDEBUG_ONLY("Empty")};
    epiWString m_BPrty16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_BPrty17{};
    epiPtrArray<epiS32> m_BPrty18{};
    epiArray<epiString> m_BPrty19{};
    epiPtrArray<epiString> m_BPrty20{};
    epiVec2f m_BPrty21{};
    epiVec2d m_BPrty22{};
    epiVec2s m_BPrty23{};
    epiVec2u m_BPrty24{};
    epiVec3f m_BPrty25{};
    epiVec3d m_BPrty26{};
    epiVec3s m_BPrty27{};
    epiVec3u m_BPrty28{};
    epiVec4f m_BPrty29{};
    epiVec4d m_BPrty30{};
    epiVec4s m_BPrty31{};
    epiVec4u m_BPrty32{};
    epiMat2x2f m_BPrty33{};
    epiMat3x3f m_BPrty34{};
    epiMat4x4f m_BPrty35{};
    epiComplexf m_BPrty36{};
    epiComplexd m_BPrty37{};
    epiRect2f m_BPrty38{};
    epiRect2d m_BPrty39{};
    epiRect2s m_BPrty40{};
    epiRect2u m_BPrty41{};
    InplaceClass m_BPrty42{};
    InplaceClass* m_BPrty43{nullptr};
    epiChar m_BPrtyReadCallback0{'\0'};
    epiWChar m_BPrtyReadCallback1{L'\0'};
    epiBool m_BPrtyReadCallback2{false};
    epiByte m_BPrtyReadCallback3{0};
    epiFloat m_BPrtyReadCallback4{0.0f};
    epiDouble m_BPrtyReadCallback5{0.0};
    epiSize_t m_BPrtyReadCallback6{0};
    epiU8 m_BPrtyReadCallback7{0};
    epiU16 m_BPrtyReadCallback8{0};
    epiU32 m_BPrtyReadCallback9{0};
    epiU64 m_BPrtyReadCallback10{0};
    epiS8 m_BPrtyReadCallback11{0};
    epiS16 m_BPrtyReadCallback12{0};
    epiS32 m_BPrtyReadCallback13{0};
    epiS64 m_BPrtyReadCallback14{0};
    epiString m_BPrtyReadCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_BPrtyReadCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_BPrtyReadCallback17{};
    epiPtrArray<epiS32> m_BPrtyReadCallback18{};
    epiArray<epiString> m_BPrtyReadCallback19{};
    epiPtrArray<epiString> m_BPrtyReadCallback20{};
    epiVec2f m_BPrtyReadCallback21{};
    epiVec2d m_BPrtyReadCallback22{};
    epiVec2s m_BPrtyReadCallback23{};
    epiVec2u m_BPrtyReadCallback24{};
    epiVec3f m_BPrtyReadCallback25{};
    epiVec3d m_BPrtyReadCallback26{};
    epiVec3s m_BPrtyReadCallback27{};
    epiVec3u m_BPrtyReadCallback28{};
    epiVec4f m_BPrtyReadCallback29{};
    epiVec4d m_BPrtyReadCallback30{};
    epiVec4s m_BPrtyReadCallback31{};
    epiVec4u m_BPrtyReadCallback32{};
    epiMat2x2f m_BPrtyReadCallback33{};
    epiMat3x3f m_BPrtyReadCallback34{};
    epiMat4x4f m_BPrtyReadCallback35{};
    epiComplexf m_BPrtyReadCallback36{};
    epiComplexd m_BPrtyReadCallback37{};
    epiRect2f m_BPrtyReadCallback38{};
    epiRect2d m_BPrtyReadCallback39{};
    epiRect2s m_BPrtyReadCallback40{};
    epiRect2u m_BPrtyReadCallback41{};
    InplaceClass m_BPrtyReadCallback42{};
    InplaceClass* m_BPrtyReadCallback43{nullptr};
    epiChar m_BPrtyWriteCallback0{'\0'};
    epiWChar m_BPrtyWriteCallback1{L'\0'};
    epiBool m_BPrtyWriteCallback2{false};
    epiByte m_BPrtyWriteCallback3{0};
    epiFloat m_BPrtyWriteCallback4{0.0f};
    epiDouble m_BPrtyWriteCallback5{0.0};
    epiSize_t m_BPrtyWriteCallback6{0};
    epiU8 m_BPrtyWriteCallback7{0};
    epiU16 m_BPrtyWriteCallback8{0};
    epiU32 m_BPrtyWriteCallback9{0};
    epiU64 m_BPrtyWriteCallback10{0};
    epiS8 m_BPrtyWriteCallback11{0};
    epiS16 m_BPrtyWriteCallback12{0};
    epiS32 m_BPrtyWriteCallback13{0};
    epiS64 m_BPrtyWriteCallback14{0};
    epiString m_BPrtyWriteCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_BPrtyWriteCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_BPrtyWriteCallback17{};
    epiPtrArray<epiS32> m_BPrtyWriteCallback18{};
    epiArray<epiString> m_BPrtyWriteCallback19{};
    epiPtrArray<epiString> m_BPrtyWriteCallback20{};
    epiVec2f m_BPrtyWriteCallback21{};
    epiVec2d m_BPrtyWriteCallback22{};
    epiVec2s m_BPrtyWriteCallback23{};
    epiVec2u m_BPrtyWriteCallback24{};
    epiVec3f m_BPrtyWriteCallback25{};
    epiVec3d m_BPrtyWriteCallback26{};
    epiVec3s m_BPrtyWriteCallback27{};
    epiVec3u m_BPrtyWriteCallback28{};
    epiVec4f m_BPrtyWriteCallback29{};
    epiVec4d m_BPrtyWriteCallback30{};
    epiVec4s m_BPrtyWriteCallback31{};
    epiVec4u m_BPrtyWriteCallback32{};
    epiMat2x2f m_BPrtyWriteCallback33{};
    epiMat3x3f m_BPrtyWriteCallback34{};
    epiMat4x4f m_BPrtyWriteCallback35{};
    epiComplexf m_BPrtyWriteCallback36{};
    epiComplexd m_BPrtyWriteCallback37{};
    epiRect2f m_BPrtyWriteCallback38{};
    epiRect2d m_BPrtyWriteCallback39{};
    epiRect2s m_BPrtyWriteCallback40{};
    epiRect2u m_BPrtyWriteCallback41{};
    InplaceClass m_BPrtyWriteCallback42{};
    InplaceClass* m_BPrtyWriteCallback43{nullptr};

EPI_GENREGION_END(TestClassB)

public:
    void Reset() override;
};

class IFoo
{
public:
    virtual void Buzz() = 0;
};

class TestClassC : public TestClassA, public IFoo
{
EPI_GENREGION_BEGIN(TestClassC)

EPI_GENHIDDEN_TestClassC()

public:
    constexpr static epiMetaTypeID TypeID{0x949d761a};

    enum TestClassC_PIDs
    {
        PID_CPrty0 = 0x4af74c22,
        PID_CPrty1 = 0x3df07cb4,
        PID_CPrty2 = 0xa4f92d0e,
        PID_CPrty3 = 0xd3fe1d98,
        PID_CPrty4 = 0x4d9a883b,
        PID_CPrty5 = 0x3a9db8ad,
        PID_CPrty6 = 0xa394e917,
        PID_CPrty7 = 0xd493d981,
        PID_CPrty8 = 0x442cc410,
        PID_CPrty9 = 0x332bf486,
        PID_CPrty10 = 0x38ea58c8,
        PID_CPrty11 = 0x4fed685e,
        PID_CPrty12 = 0xd6e439e4,
        PID_CPrty13 = 0xa1e30972,
        PID_CPrty14 = 0x3f879cd1,
        PID_CPrty15 = 0x4880ac47,
        PID_CPrty16 = 0xd189fdfd,
        PID_CPrty17 = 0xa68ecd6b,
        PID_CPrty18 = 0x3631d0fa,
        PID_CPrty19 = 0x4136e06c,
        PID_CPrty20 = 0x13c70b0b,
        PID_CPrty21 = 0x64c03b9d,
        PID_CPrty22 = 0xfdc96a27,
        PID_CPrty23 = 0x8ace5ab1,
        PID_CPrty24 = 0x14aacf12,
        PID_CPrty25 = 0x63adff84,
        PID_CPrty26 = 0xfaa4ae3e,
        PID_CPrty27 = 0x8da39ea8,
        PID_CPrty28 = 0x1d1c8339,
        PID_CPrty29 = 0x6a1bb3af,
        PID_CPrty30 = 0xadc3a4a,
        PID_CPrty31 = 0x7ddb0adc,
        PID_CPrty32 = 0xe4d25b66,
        PID_CPrty33 = 0x93d56bf0,
        PID_CPrty34 = 0xdb1fe53,
        PID_CPrty35 = 0x7ab6cec5,
        PID_CPrty36 = 0xe3bf9f7f,
        PID_CPrty37 = 0x94b8afe9,
        PID_CPrty38 = 0x407b278,
        PID_CPrty39 = 0x730082ee,
        PID_CPrty40 = 0x459dac8d,
        PID_CPrty41 = 0x329a9c1b,
        PID_CPrty42 = 0xab93cda1,
        PID_CPrty43 = 0xdc94fd37,
        PID_CPrtyVirtual0 = 0xb1ea6b9,
        PID_CPrtyVirtual1 = 0x7c19962f,
        PID_CPrtyVirtual2 = 0xe510c795,
        PID_CPrtyVirtual3 = 0x9217f703,
        PID_CPrtyVirtual4 = 0xc7362a0,
        PID_CPrtyVirtual5 = 0x7b745236,
        PID_CPrtyVirtual6 = 0xe27d038c,
        PID_CPrtyVirtual7 = 0x957a331a,
        PID_CPrtyVirtual8 = 0x5c52e8b,
        PID_CPrtyVirtual9 = 0x72c21e1d,
        PID_CPrtyVirtual10 = 0x5f76fbee,
        PID_CPrtyVirtual11 = 0x2871cb78,
        PID_CPrtyVirtual12 = 0xb1789ac2,
        PID_CPrtyVirtual13 = 0xc67faa54,
        PID_CPrtyVirtual14 = 0x581b3ff7,
        PID_CPrtyVirtual15 = 0x2f1c0f61,
        PID_CPrtyVirtual16 = 0xb6155edb,
        PID_CPrtyVirtual17 = 0xc1126e4d,
        PID_CPrtyVirtual18 = 0x51ad73dc,
        PID_CPrtyVirtual19 = 0x26aa434a,
        PID_CPrtyVirtual20 = 0x745ba82d,
        PID_CPrtyVirtual21 = 0x35c98bb,
        PID_CPrtyVirtual22 = 0x9a55c901,
        PID_CPrtyVirtual23 = 0xed52f997,
        PID_CPrtyVirtual24 = 0x73366c34,
        PID_CPrtyVirtual25 = 0x4315ca2,
        PID_CPrtyVirtual26 = 0x9d380d18,
        PID_CPrtyVirtual27 = 0xea3f3d8e,
        PID_CPrtyVirtual28 = 0x7a80201f,
        PID_CPrtyVirtual29 = 0xd871089,
        PID_CPrtyVirtual30 = 0x6d40996c,
        PID_CPrtyVirtual31 = 0x1a47a9fa,
        PID_CPrtyVirtual32 = 0x834ef840,
        PID_CPrtyVirtual33 = 0xf449c8d6,
        PID_CPrtyVirtual34 = 0x6a2d5d75,
        PID_CPrtyVirtual35 = 0x1d2a6de3,
        PID_CPrtyVirtual36 = 0x84233c59,
        PID_CPrtyVirtual37 = 0xf3240ccf,
        PID_CPrtyVirtual38 = 0x639b115e,
        PID_CPrtyVirtual39 = 0x149c21c8,
        PID_CPrtyVirtual40 = 0x22010fab,
        PID_CPrtyVirtual41 = 0x55063f3d,
        PID_CPrtyVirtual42 = 0xcc0f6e87,
        PID_CPrtyVirtual43 = 0xbb085e11,
        PID_CPrtyReadCallback0 = 0x3ffeba03,
        PID_CPrtyReadCallback1 = 0x48f98a95,
        PID_CPrtyReadCallback2 = 0xd1f0db2f,
        PID_CPrtyReadCallback3 = 0xa6f7ebb9,
        PID_CPrtyReadCallback4 = 0x38937e1a,
        PID_CPrtyReadCallback5 = 0x4f944e8c,
        PID_CPrtyReadCallback6 = 0xd69d1f36,
        PID_CPrtyReadCallback7 = 0xa19a2fa0,
        PID_CPrtyReadCallback8 = 0x31253231,
        PID_CPrtyReadCallback9 = 0x462202a7,
        PID_CPrtyReadCallback10 = 0x74f64160,
        PID_CPrtyReadCallback11 = 0x3f171f6,
        PID_CPrtyReadCallback12 = 0x9af8204c,
        PID_CPrtyReadCallback13 = 0xedff10da,
        PID_CPrtyReadCallback14 = 0x739b8579,
        PID_CPrtyReadCallback15 = 0x49cb5ef,
        PID_CPrtyReadCallback16 = 0x9d95e455,
        PID_CPrtyReadCallback17 = 0xea92d4c3,
        PID_CPrtyReadCallback18 = 0x7a2dc952,
        PID_CPrtyReadCallback19 = 0xd2af9c4,
        PID_CPrtyReadCallback20 = 0x5fdb12a3,
        PID_CPrtyReadCallback21 = 0x28dc2235,
        PID_CPrtyReadCallback22 = 0xb1d5738f,
        PID_CPrtyReadCallback23 = 0xc6d24319,
        PID_CPrtyReadCallback24 = 0x58b6d6ba,
        PID_CPrtyReadCallback25 = 0x2fb1e62c,
        PID_CPrtyReadCallback26 = 0xb6b8b796,
        PID_CPrtyReadCallback27 = 0xc1bf8700,
        PID_CPrtyReadCallback28 = 0x51009a91,
        PID_CPrtyReadCallback29 = 0x2607aa07,
        PID_CPrtyReadCallback30 = 0x46c023e2,
        PID_CPrtyReadCallback31 = 0x31c71374,
        PID_CPrtyReadCallback32 = 0xa8ce42ce,
        PID_CPrtyReadCallback33 = 0xdfc97258,
        PID_CPrtyReadCallback34 = 0x41ade7fb,
        PID_CPrtyReadCallback35 = 0x36aad76d,
        PID_CPrtyReadCallback36 = 0xafa386d7,
        PID_CPrtyReadCallback37 = 0xd8a4b641,
        PID_CPrtyReadCallback38 = 0x481babd0,
        PID_CPrtyReadCallback39 = 0x3f1c9b46,
        PID_CPrtyReadCallback40 = 0x981b525,
        PID_CPrtyReadCallback41 = 0x7e8685b3,
        PID_CPrtyReadCallback42 = 0xe78fd409,
        PID_CPrtyReadCallback43 = 0x9088e49f,
        PID_CPrtyWriteCallback0 = 0x7d7ec694,
        PID_CPrtyWriteCallback1 = 0xa79f602,
        PID_CPrtyWriteCallback2 = 0x9370a7b8,
        PID_CPrtyWriteCallback3 = 0xe477972e,
        PID_CPrtyWriteCallback4 = 0x7a13028d,
        PID_CPrtyWriteCallback5 = 0xd14321b,
        PID_CPrtyWriteCallback6 = 0x941d63a1,
        PID_CPrtyWriteCallback7 = 0xe31a5337,
        PID_CPrtyWriteCallback8 = 0x73a54ea6,
        PID_CPrtyWriteCallback9 = 0x4a27e30,
        PID_CPrtyWriteCallback10 = 0x1adfc7fb,
        PID_CPrtyWriteCallback11 = 0x6dd8f76d,
        PID_CPrtyWriteCallback12 = 0xf4d1a6d7,
        PID_CPrtyWriteCallback13 = 0x83d69641,
        PID_CPrtyWriteCallback14 = 0x1db203e2,
        PID_CPrtyWriteCallback15 = 0x6ab53374,
        PID_CPrtyWriteCallback16 = 0xf3bc62ce,
        PID_CPrtyWriteCallback17 = 0x84bb5258,
        PID_CPrtyWriteCallback18 = 0x14044fc9,
        PID_CPrtyWriteCallback19 = 0x63037f5f,
        PID_CPrtyWriteCallback20 = 0x31f29438,
        PID_CPrtyWriteCallback21 = 0x46f5a4ae,
        PID_CPrtyWriteCallback22 = 0xdffcf514,
        PID_CPrtyWriteCallback23 = 0xa8fbc582,
        PID_CPrtyWriteCallback24 = 0x369f5021,
        PID_CPrtyWriteCallback25 = 0x419860b7,
        PID_CPrtyWriteCallback26 = 0xd891310d,
        PID_CPrtyWriteCallback27 = 0xaf96019b,
        PID_CPrtyWriteCallback28 = 0x3f291c0a,
        PID_CPrtyWriteCallback29 = 0x482e2c9c,
        PID_CPrtyWriteCallback30 = 0x28e9a579,
        PID_CPrtyWriteCallback31 = 0x5fee95ef,
        PID_CPrtyWriteCallback32 = 0xc6e7c455,
        PID_CPrtyWriteCallback33 = 0xb1e0f4c3,
        PID_CPrtyWriteCallback34 = 0x2f846160,
        PID_CPrtyWriteCallback35 = 0x588351f6,
        PID_CPrtyWriteCallback36 = 0xc18a004c,
        PID_CPrtyWriteCallback37 = 0xb68d30da,
        PID_CPrtyWriteCallback38 = 0x26322d4b,
        PID_CPrtyWriteCallback39 = 0x51351ddd,
        PID_CPrtyWriteCallback40 = 0x67a833be,
        PID_CPrtyWriteCallback41 = 0x10af0328,
        PID_CPrtyWriteCallback42 = 0x89a65292,
        PID_CPrtyWriteCallback43 = 0xfea16204,
        PID_COUNT = 176
    };

protected:
    epiChar GetCPrtyVirtual0_Callback() const;
    void SetCPrtyVirtual0_Callback(epiChar value);
    epiWChar GetCPrtyVirtual1_Callback() const;
    void SetCPrtyVirtual1_Callback(epiWChar value);
    epiBool GetCPrtyVirtual2_Callback() const;
    void SetCPrtyVirtual2_Callback(epiBool value);
    epiByte GetCPrtyVirtual3_Callback() const;
    void SetCPrtyVirtual3_Callback(epiByte value);
    epiFloat GetCPrtyVirtual4_Callback() const;
    void SetCPrtyVirtual4_Callback(epiFloat value);
    epiDouble GetCPrtyVirtual5_Callback() const;
    void SetCPrtyVirtual5_Callback(epiDouble value);
    epiSize_t GetCPrtyVirtual6_Callback() const;
    void SetCPrtyVirtual6_Callback(epiSize_t value);
    epiU8 GetCPrtyVirtual7_Callback() const;
    void SetCPrtyVirtual7_Callback(epiU8 value);
    epiU16 GetCPrtyVirtual8_Callback() const;
    void SetCPrtyVirtual8_Callback(epiU16 value);
    epiU32 GetCPrtyVirtual9_Callback() const;
    void SetCPrtyVirtual9_Callback(epiU32 value);
    epiU64 GetCPrtyVirtual10_Callback() const;
    void SetCPrtyVirtual10_Callback(epiU64 value);
    epiS8 GetCPrtyVirtual11_Callback() const;
    void SetCPrtyVirtual11_Callback(epiS8 value);
    epiS16 GetCPrtyVirtual12_Callback() const;
    void SetCPrtyVirtual12_Callback(epiS16 value);
    epiS32 GetCPrtyVirtual13_Callback() const;
    void SetCPrtyVirtual13_Callback(epiS32 value);
    epiS64 GetCPrtyVirtual14_Callback() const;
    void SetCPrtyVirtual14_Callback(epiS64 value);
    const epiString& GetCPrtyVirtual15_Callback() const;
    void SetCPrtyVirtual15_Callback(const epiString& value);
    const epiWString& GetCPrtyVirtual16_Callback() const;
    void SetCPrtyVirtual16_Callback(const epiWString& value);
    const epiArray<epiS32>& GetCPrtyVirtual17_Callback() const;
    void SetCPrtyVirtual17_Callback(const epiArray<epiS32>& value);
    const epiPtrArray<epiS32>& GetCPrtyVirtual18_Callback() const;
    void SetCPrtyVirtual18_Callback(const epiPtrArray<epiS32>& value);
    const epiArray<epiString>& GetCPrtyVirtual19_Callback() const;
    void SetCPrtyVirtual19_Callback(const epiArray<epiString>& value);
    const epiPtrArray<epiString>& GetCPrtyVirtual20_Callback() const;
    void SetCPrtyVirtual20_Callback(const epiPtrArray<epiString>& value);
    const epiVec2f& GetCPrtyVirtual21_Callback() const;
    void SetCPrtyVirtual21_Callback(const epiVec2f& value);
    const epiVec2d& GetCPrtyVirtual22_Callback() const;
    void SetCPrtyVirtual22_Callback(const epiVec2d& value);
    const epiVec2s& GetCPrtyVirtual23_Callback() const;
    void SetCPrtyVirtual23_Callback(const epiVec2s& value);
    const epiVec2u& GetCPrtyVirtual24_Callback() const;
    void SetCPrtyVirtual24_Callback(const epiVec2u& value);
    const epiVec3f& GetCPrtyVirtual25_Callback() const;
    void SetCPrtyVirtual25_Callback(const epiVec3f& value);
    const epiVec3d& GetCPrtyVirtual26_Callback() const;
    void SetCPrtyVirtual26_Callback(const epiVec3d& value);
    const epiVec3s& GetCPrtyVirtual27_Callback() const;
    void SetCPrtyVirtual27_Callback(const epiVec3s& value);
    const epiVec3u& GetCPrtyVirtual28_Callback() const;
    void SetCPrtyVirtual28_Callback(const epiVec3u& value);
    const epiVec4f& GetCPrtyVirtual29_Callback() const;
    void SetCPrtyVirtual29_Callback(const epiVec4f& value);
    const epiVec4d& GetCPrtyVirtual30_Callback() const;
    void SetCPrtyVirtual30_Callback(const epiVec4d& value);
    const epiVec4s& GetCPrtyVirtual31_Callback() const;
    void SetCPrtyVirtual31_Callback(const epiVec4s& value);
    const epiVec4u& GetCPrtyVirtual32_Callback() const;
    void SetCPrtyVirtual32_Callback(const epiVec4u& value);
    const epiMat2x2f& GetCPrtyVirtual33_Callback() const;
    void SetCPrtyVirtual33_Callback(const epiMat2x2f& value);
    const epiMat3x3f& GetCPrtyVirtual34_Callback() const;
    void SetCPrtyVirtual34_Callback(const epiMat3x3f& value);
    const epiMat4x4f& GetCPrtyVirtual35_Callback() const;
    void SetCPrtyVirtual35_Callback(const epiMat4x4f& value);
    const epiComplexf& GetCPrtyVirtual36_Callback() const;
    void SetCPrtyVirtual36_Callback(const epiComplexf& value);
    const epiComplexd& GetCPrtyVirtual37_Callback() const;
    void SetCPrtyVirtual37_Callback(const epiComplexd& value);
    const epiRect2f& GetCPrtyVirtual38_Callback() const;
    void SetCPrtyVirtual38_Callback(const epiRect2f& value);
    const epiRect2d& GetCPrtyVirtual39_Callback() const;
    void SetCPrtyVirtual39_Callback(const epiRect2d& value);
    const epiRect2s& GetCPrtyVirtual40_Callback() const;
    void SetCPrtyVirtual40_Callback(const epiRect2s& value);
    const epiRect2u& GetCPrtyVirtual41_Callback() const;
    void SetCPrtyVirtual41_Callback(const epiRect2u& value);
    const InplaceClass& GetCPrtyVirtual42_Callback() const;
    void SetCPrtyVirtual42_Callback(const InplaceClass& value);
    const InplaceClass* GetCPrtyVirtual43_Callback() const;
    void SetCPrtyVirtual43_Callback(InplaceClass* value);
    epiChar GetCPrtyReadCallback0_Callback() const;
    epiWChar GetCPrtyReadCallback1_Callback() const;
    epiBool GetCPrtyReadCallback2_Callback() const;
    epiByte GetCPrtyReadCallback3_Callback() const;
    epiFloat GetCPrtyReadCallback4_Callback() const;
    epiDouble GetCPrtyReadCallback5_Callback() const;
    epiSize_t GetCPrtyReadCallback6_Callback() const;
    epiU8 GetCPrtyReadCallback7_Callback() const;
    epiU16 GetCPrtyReadCallback8_Callback() const;
    epiU32 GetCPrtyReadCallback9_Callback() const;
    epiU64 GetCPrtyReadCallback10_Callback() const;
    epiS8 GetCPrtyReadCallback11_Callback() const;
    epiS16 GetCPrtyReadCallback12_Callback() const;
    epiS32 GetCPrtyReadCallback13_Callback() const;
    epiS64 GetCPrtyReadCallback14_Callback() const;
    const epiString& GetCPrtyReadCallback15_Callback() const;
    const epiWString& GetCPrtyReadCallback16_Callback() const;
    const epiArray<epiS32>& GetCPrtyReadCallback17_Callback() const;
    const epiPtrArray<epiS32>& GetCPrtyReadCallback18_Callback() const;
    const epiArray<epiString>& GetCPrtyReadCallback19_Callback() const;
    const epiPtrArray<epiString>& GetCPrtyReadCallback20_Callback() const;
    const epiVec2f& GetCPrtyReadCallback21_Callback() const;
    const epiVec2d& GetCPrtyReadCallback22_Callback() const;
    const epiVec2s& GetCPrtyReadCallback23_Callback() const;
    const epiVec2u& GetCPrtyReadCallback24_Callback() const;
    const epiVec3f& GetCPrtyReadCallback25_Callback() const;
    const epiVec3d& GetCPrtyReadCallback26_Callback() const;
    const epiVec3s& GetCPrtyReadCallback27_Callback() const;
    const epiVec3u& GetCPrtyReadCallback28_Callback() const;
    const epiVec4f& GetCPrtyReadCallback29_Callback() const;
    const epiVec4d& GetCPrtyReadCallback30_Callback() const;
    const epiVec4s& GetCPrtyReadCallback31_Callback() const;
    const epiVec4u& GetCPrtyReadCallback32_Callback() const;
    const epiMat2x2f& GetCPrtyReadCallback33_Callback() const;
    const epiMat3x3f& GetCPrtyReadCallback34_Callback() const;
    const epiMat4x4f& GetCPrtyReadCallback35_Callback() const;
    const epiComplexf& GetCPrtyReadCallback36_Callback() const;
    const epiComplexd& GetCPrtyReadCallback37_Callback() const;
    const epiRect2f& GetCPrtyReadCallback38_Callback() const;
    const epiRect2d& GetCPrtyReadCallback39_Callback() const;
    const epiRect2s& GetCPrtyReadCallback40_Callback() const;
    const epiRect2u& GetCPrtyReadCallback41_Callback() const;
    const InplaceClass& GetCPrtyReadCallback42_Callback() const;
    const InplaceClass* GetCPrtyReadCallback43_Callback() const;
    void SetCPrtyWriteCallback0_Callback(epiChar value);
    void SetCPrtyWriteCallback1_Callback(epiWChar value);
    void SetCPrtyWriteCallback2_Callback(epiBool value);
    void SetCPrtyWriteCallback3_Callback(epiByte value);
    void SetCPrtyWriteCallback4_Callback(epiFloat value);
    void SetCPrtyWriteCallback5_Callback(epiDouble value);
    void SetCPrtyWriteCallback6_Callback(epiSize_t value);
    void SetCPrtyWriteCallback7_Callback(epiU8 value);
    void SetCPrtyWriteCallback8_Callback(epiU16 value);
    void SetCPrtyWriteCallback9_Callback(epiU32 value);
    void SetCPrtyWriteCallback10_Callback(epiU64 value);
    void SetCPrtyWriteCallback11_Callback(epiS8 value);
    void SetCPrtyWriteCallback12_Callback(epiS16 value);
    void SetCPrtyWriteCallback13_Callback(epiS32 value);
    void SetCPrtyWriteCallback14_Callback(epiS64 value);
    void SetCPrtyWriteCallback15_Callback(const epiString& value);
    void SetCPrtyWriteCallback16_Callback(const epiWString& value);
    void SetCPrtyWriteCallback17_Callback(const epiArray<epiS32>& value);
    void SetCPrtyWriteCallback18_Callback(const epiPtrArray<epiS32>& value);
    void SetCPrtyWriteCallback19_Callback(const epiArray<epiString>& value);
    void SetCPrtyWriteCallback20_Callback(const epiPtrArray<epiString>& value);
    void SetCPrtyWriteCallback21_Callback(const epiVec2f& value);
    void SetCPrtyWriteCallback22_Callback(const epiVec2d& value);
    void SetCPrtyWriteCallback23_Callback(const epiVec2s& value);
    void SetCPrtyWriteCallback24_Callback(const epiVec2u& value);
    void SetCPrtyWriteCallback25_Callback(const epiVec3f& value);
    void SetCPrtyWriteCallback26_Callback(const epiVec3d& value);
    void SetCPrtyWriteCallback27_Callback(const epiVec3s& value);
    void SetCPrtyWriteCallback28_Callback(const epiVec3u& value);
    void SetCPrtyWriteCallback29_Callback(const epiVec4f& value);
    void SetCPrtyWriteCallback30_Callback(const epiVec4d& value);
    void SetCPrtyWriteCallback31_Callback(const epiVec4s& value);
    void SetCPrtyWriteCallback32_Callback(const epiVec4u& value);
    void SetCPrtyWriteCallback33_Callback(const epiMat2x2f& value);
    void SetCPrtyWriteCallback34_Callback(const epiMat3x3f& value);
    void SetCPrtyWriteCallback35_Callback(const epiMat4x4f& value);
    void SetCPrtyWriteCallback36_Callback(const epiComplexf& value);
    void SetCPrtyWriteCallback37_Callback(const epiComplexd& value);
    void SetCPrtyWriteCallback38_Callback(const epiRect2f& value);
    void SetCPrtyWriteCallback39_Callback(const epiRect2d& value);
    void SetCPrtyWriteCallback40_Callback(const epiRect2s& value);
    void SetCPrtyWriteCallback41_Callback(const epiRect2u& value);
    void SetCPrtyWriteCallback42_Callback(const InplaceClass& value);
    void SetCPrtyWriteCallback43_Callback(InplaceClass* value);

protected:
    epiChar m_CPrty0{'\0'};
    epiWChar m_CPrty1{L'\0'};
    epiBool m_CPrty2{false};
    epiByte m_CPrty3{0};
    epiFloat m_CPrty4{0.0f};
    epiDouble m_CPrty5{0.0};
    epiSize_t m_CPrty6{0};
    epiU8 m_CPrty7{0};
    epiU16 m_CPrty8{0};
    epiU32 m_CPrty9{0};
    epiU64 m_CPrty10{0};
    epiS8 m_CPrty11{0};
    epiS16 m_CPrty12{0};
    epiS32 m_CPrty13{0};
    epiS64 m_CPrty14{0};
    epiString m_CPrty15{epiDEBUG_ONLY("Empty")};
    epiWString m_CPrty16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CPrty17{};
    epiPtrArray<epiS32> m_CPrty18{};
    epiArray<epiString> m_CPrty19{};
    epiPtrArray<epiString> m_CPrty20{};
    epiVec2f m_CPrty21{};
    epiVec2d m_CPrty22{};
    epiVec2s m_CPrty23{};
    epiVec2u m_CPrty24{};
    epiVec3f m_CPrty25{};
    epiVec3d m_CPrty26{};
    epiVec3s m_CPrty27{};
    epiVec3u m_CPrty28{};
    epiVec4f m_CPrty29{};
    epiVec4d m_CPrty30{};
    epiVec4s m_CPrty31{};
    epiVec4u m_CPrty32{};
    epiMat2x2f m_CPrty33{};
    epiMat3x3f m_CPrty34{};
    epiMat4x4f m_CPrty35{};
    epiComplexf m_CPrty36{};
    epiComplexd m_CPrty37{};
    epiRect2f m_CPrty38{};
    epiRect2d m_CPrty39{};
    epiRect2s m_CPrty40{};
    epiRect2u m_CPrty41{};
    InplaceClass m_CPrty42{};
    InplaceClass* m_CPrty43{nullptr};
    epiChar m_CPrtyReadCallback0{'\0'};
    epiWChar m_CPrtyReadCallback1{L'\0'};
    epiBool m_CPrtyReadCallback2{false};
    epiByte m_CPrtyReadCallback3{0};
    epiFloat m_CPrtyReadCallback4{0.0f};
    epiDouble m_CPrtyReadCallback5{0.0};
    epiSize_t m_CPrtyReadCallback6{0};
    epiU8 m_CPrtyReadCallback7{0};
    epiU16 m_CPrtyReadCallback8{0};
    epiU32 m_CPrtyReadCallback9{0};
    epiU64 m_CPrtyReadCallback10{0};
    epiS8 m_CPrtyReadCallback11{0};
    epiS16 m_CPrtyReadCallback12{0};
    epiS32 m_CPrtyReadCallback13{0};
    epiS64 m_CPrtyReadCallback14{0};
    epiString m_CPrtyReadCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_CPrtyReadCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CPrtyReadCallback17{};
    epiPtrArray<epiS32> m_CPrtyReadCallback18{};
    epiArray<epiString> m_CPrtyReadCallback19{};
    epiPtrArray<epiString> m_CPrtyReadCallback20{};
    epiVec2f m_CPrtyReadCallback21{};
    epiVec2d m_CPrtyReadCallback22{};
    epiVec2s m_CPrtyReadCallback23{};
    epiVec2u m_CPrtyReadCallback24{};
    epiVec3f m_CPrtyReadCallback25{};
    epiVec3d m_CPrtyReadCallback26{};
    epiVec3s m_CPrtyReadCallback27{};
    epiVec3u m_CPrtyReadCallback28{};
    epiVec4f m_CPrtyReadCallback29{};
    epiVec4d m_CPrtyReadCallback30{};
    epiVec4s m_CPrtyReadCallback31{};
    epiVec4u m_CPrtyReadCallback32{};
    epiMat2x2f m_CPrtyReadCallback33{};
    epiMat3x3f m_CPrtyReadCallback34{};
    epiMat4x4f m_CPrtyReadCallback35{};
    epiComplexf m_CPrtyReadCallback36{};
    epiComplexd m_CPrtyReadCallback37{};
    epiRect2f m_CPrtyReadCallback38{};
    epiRect2d m_CPrtyReadCallback39{};
    epiRect2s m_CPrtyReadCallback40{};
    epiRect2u m_CPrtyReadCallback41{};
    InplaceClass m_CPrtyReadCallback42{};
    InplaceClass* m_CPrtyReadCallback43{nullptr};
    epiChar m_CPrtyWriteCallback0{'\0'};
    epiWChar m_CPrtyWriteCallback1{L'\0'};
    epiBool m_CPrtyWriteCallback2{false};
    epiByte m_CPrtyWriteCallback3{0};
    epiFloat m_CPrtyWriteCallback4{0.0f};
    epiDouble m_CPrtyWriteCallback5{0.0};
    epiSize_t m_CPrtyWriteCallback6{0};
    epiU8 m_CPrtyWriteCallback7{0};
    epiU16 m_CPrtyWriteCallback8{0};
    epiU32 m_CPrtyWriteCallback9{0};
    epiU64 m_CPrtyWriteCallback10{0};
    epiS8 m_CPrtyWriteCallback11{0};
    epiS16 m_CPrtyWriteCallback12{0};
    epiS32 m_CPrtyWriteCallback13{0};
    epiS64 m_CPrtyWriteCallback14{0};
    epiString m_CPrtyWriteCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_CPrtyWriteCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CPrtyWriteCallback17{};
    epiPtrArray<epiS32> m_CPrtyWriteCallback18{};
    epiArray<epiString> m_CPrtyWriteCallback19{};
    epiPtrArray<epiString> m_CPrtyWriteCallback20{};
    epiVec2f m_CPrtyWriteCallback21{};
    epiVec2d m_CPrtyWriteCallback22{};
    epiVec2s m_CPrtyWriteCallback23{};
    epiVec2u m_CPrtyWriteCallback24{};
    epiVec3f m_CPrtyWriteCallback25{};
    epiVec3d m_CPrtyWriteCallback26{};
    epiVec3s m_CPrtyWriteCallback27{};
    epiVec3u m_CPrtyWriteCallback28{};
    epiVec4f m_CPrtyWriteCallback29{};
    epiVec4d m_CPrtyWriteCallback30{};
    epiVec4s m_CPrtyWriteCallback31{};
    epiVec4u m_CPrtyWriteCallback32{};
    epiMat2x2f m_CPrtyWriteCallback33{};
    epiMat3x3f m_CPrtyWriteCallback34{};
    epiMat4x4f m_CPrtyWriteCallback35{};
    epiComplexf m_CPrtyWriteCallback36{};
    epiComplexd m_CPrtyWriteCallback37{};
    epiRect2f m_CPrtyWriteCallback38{};
    epiRect2d m_CPrtyWriteCallback39{};
    epiRect2s m_CPrtyWriteCallback40{};
    epiRect2u m_CPrtyWriteCallback41{};
    InplaceClass m_CPrtyWriteCallback42{};
    InplaceClass* m_CPrtyWriteCallback43{nullptr};

EPI_GENREGION_END(TestClassC)

public:
    void Reset() override;

    void Buzz() override
    {
        printf("buzz\n");
    }
};

class TestClassBB : public TestClassB
{
EPI_GENREGION_BEGIN(TestClassBB)

EPI_GENHIDDEN_TestClassBB()

public:
    constexpr static epiMetaTypeID TypeID{0xae3d9a7c};

    enum TestClassBB_PIDs
    {
        PID_BBPrty0 = 0x7e91850a,
        PID_BBPrty1 = 0x996b59c,
        PID_BBPrty2 = 0x909fe426,
        PID_BBPrty3 = 0xe798d4b0,
        PID_BBPrty4 = 0x79fc4113,
        PID_BBPrty5 = 0xefb7185,
        PID_BBPrty6 = 0x97f2203f,
        PID_BBPrty7 = 0xe0f510a9,
        PID_BBPrty8 = 0x704a0d38,
        PID_BBPrty9 = 0x74d3dae,
        PID_BBPrty10 = 0xd6b96fb,
        PID_BBPrty11 = 0x7a6ca66d,
        PID_BBPrty12 = 0xe365f7d7,
        PID_BBPrty13 = 0x9462c741,
        PID_BBPrty14 = 0xa0652e2,
        PID_BBPrty15 = 0x7d016274,
        PID_BBPrty16 = 0xe40833ce,
        PID_BBPrty17 = 0x930f0358,
        PID_BBPrty18 = 0x3b01ec9,
        PID_BBPrty19 = 0x74b72e5f,
        PID_BBPrty20 = 0x2646c538,
        PID_BBPrty21 = 0x5141f5ae,
        PID_BBPrty22 = 0xc848a414,
        PID_BBPrty23 = 0xbf4f9482,
        PID_BBPrty24 = 0x212b0121,
        PID_BBPrty25 = 0x562c31b7,
        PID_BBPrty26 = 0xcf25600d,
        PID_BBPrty27 = 0xb822509b,
        PID_BBPrty28 = 0x289d4d0a,
        PID_BBPrty29 = 0x5f9a7d9c,
        PID_BBPrty30 = 0x3f5df479,
        PID_BBPrty31 = 0x485ac4ef,
        PID_BBPrty32 = 0xd1539555,
        PID_BBPrty33 = 0xa654a5c3,
        PID_BBPrty34 = 0x38303060,
        PID_BBPrty35 = 0x4f3700f6,
        PID_BBPrty36 = 0xd63e514c,
        PID_BBPrty37 = 0xa13961da,
        PID_BBPrty38 = 0x31867c4b,
        PID_BBPrty39 = 0x46814cdd,
        PID_BBPrty40 = 0x701c62be,
        PID_BBPrty41 = 0x71b5228,
        PID_BBPrty42 = 0x9e120392,
        PID_BBPrty43 = 0xe9153304,
        PID_BBPrtyVirtual0 = 0xa8907325,
        PID_BBPrtyVirtual1 = 0xdf9743b3,
        PID_BBPrtyVirtual2 = 0x469e1209,
        PID_BBPrtyVirtual3 = 0x3199229f,
        PID_BBPrtyVirtual4 = 0xaffdb73c,
        PID_BBPrtyVirtual5 = 0xd8fa87aa,
        PID_BBPrtyVirtual6 = 0x41f3d610,
        PID_BBPrtyVirtual7 = 0x36f4e686,
        PID_BBPrtyVirtual8 = 0xa64bfb17,
        PID_BBPrtyVirtual9 = 0xd14ccb81,
        PID_BBPrtyVirtual10 = 0xa66caa54,
        PID_BBPrtyVirtual11 = 0xd16b9ac2,
        PID_BBPrtyVirtual12 = 0x4862cb78,
        PID_BBPrtyVirtual13 = 0x3f65fbee,
        PID_BBPrtyVirtual14 = 0xa1016e4d,
        PID_BBPrtyVirtual15 = 0xd6065edb,
        PID_BBPrtyVirtual16 = 0x4f0f0f61,
        PID_BBPrtyVirtual17 = 0x38083ff7,
        PID_BBPrtyVirtual18 = 0xa8b72266,
        PID_BBPrtyVirtual19 = 0xdfb012f0,
        PID_BBPrtyVirtual20 = 0x8d41f997,
        PID_BBPrtyVirtual21 = 0xfa46c901,
        PID_BBPrtyVirtual22 = 0x634f98bb,
        PID_BBPrtyVirtual23 = 0x1448a82d,
        PID_BBPrtyVirtual24 = 0x8a2c3d8e,
        PID_BBPrtyVirtual25 = 0xfd2b0d18,
        PID_BBPrtyVirtual26 = 0x64225ca2,
        PID_BBPrtyVirtual27 = 0x13256c34,
        PID_BBPrtyVirtual28 = 0x839a71a5,
        PID_BBPrtyVirtual29 = 0xf49d4133,
        PID_BBPrtyVirtual30 = 0x945ac8d6,
        PID_BBPrtyVirtual31 = 0xe35df840,
        PID_BBPrtyVirtual32 = 0x7a54a9fa,
        PID_BBPrtyVirtual33 = 0xd53996c,
        PID_BBPrtyVirtual34 = 0x93370ccf,
        PID_BBPrtyVirtual35 = 0xe4303c59,
        PID_BBPrtyVirtual36 = 0x7d396de3,
        PID_BBPrtyVirtual37 = 0xa3e5d75,
        PID_BBPrtyVirtual38 = 0x9a8140e4,
        PID_BBPrtyVirtual39 = 0xed867072,
        PID_BBPrtyVirtual40 = 0xdb1b5e11,
        PID_BBPrtyVirtual41 = 0xac1c6e87,
        PID_BBPrtyVirtual42 = 0x35153f3d,
        PID_BBPrtyVirtual43 = 0x42120fab,
        PID_BBPrtyReadCallback0 = 0x5403e019,
        PID_BBPrtyReadCallback1 = 0x2304d08f,
        PID_BBPrtyReadCallback2 = 0xba0d8135,
        PID_BBPrtyReadCallback3 = 0xcd0ab1a3,
        PID_BBPrtyReadCallback4 = 0x536e2400,
        PID_BBPrtyReadCallback5 = 0x24691496,
        PID_BBPrtyReadCallback6 = 0xbd60452c,
        PID_BBPrtyReadCallback7 = 0xca6775ba,
        PID_BBPrtyReadCallback8 = 0x5ad8682b,
        PID_BBPrtyReadCallback9 = 0x2ddf58bd,
        PID_BBPrtyReadCallback10 = 0x89ff4540,
        PID_BBPrtyReadCallback11 = 0xfef875d6,
        PID_BBPrtyReadCallback12 = 0x67f1246c,
        PID_BBPrtyReadCallback13 = 0x10f614fa,
        PID_BBPrtyReadCallback14 = 0x8e928159,
        PID_BBPrtyReadCallback15 = 0xf995b1cf,
        PID_BBPrtyReadCallback16 = 0x609ce075,
        PID_BBPrtyReadCallback17 = 0x179bd0e3,
        PID_BBPrtyReadCallback18 = 0x8724cd72,
        PID_BBPrtyReadCallback19 = 0xf023fde4,
        PID_BBPrtyReadCallback20 = 0xa2d21683,
        PID_BBPrtyReadCallback21 = 0xd5d52615,
        PID_BBPrtyReadCallback22 = 0x4cdc77af,
        PID_BBPrtyReadCallback23 = 0x3bdb4739,
        PID_BBPrtyReadCallback24 = 0xa5bfd29a,
        PID_BBPrtyReadCallback25 = 0xd2b8e20c,
        PID_BBPrtyReadCallback26 = 0x4bb1b3b6,
        PID_BBPrtyReadCallback27 = 0x3cb68320,
        PID_BBPrtyReadCallback28 = 0xac099eb1,
        PID_BBPrtyReadCallback29 = 0xdb0eae27,
        PID_BBPrtyReadCallback30 = 0xbbc927c2,
        PID_BBPrtyReadCallback31 = 0xccce1754,
        PID_BBPrtyReadCallback32 = 0x55c746ee,
        PID_BBPrtyReadCallback33 = 0x22c07678,
        PID_BBPrtyReadCallback34 = 0xbca4e3db,
        PID_BBPrtyReadCallback35 = 0xcba3d34d,
        PID_BBPrtyReadCallback36 = 0x52aa82f7,
        PID_BBPrtyReadCallback37 = 0x25adb261,
        PID_BBPrtyReadCallback38 = 0xb512aff0,
        PID_BBPrtyReadCallback39 = 0xc2159f66,
        PID_BBPrtyReadCallback40 = 0xf488b105,
        PID_BBPrtyReadCallback41 = 0x838f8193,
        PID_BBPrtyReadCallback42 = 0x1a86d029,
        PID_BBPrtyReadCallback43 = 0x6d81e0bf,
        PID_BBPrtyWriteCallback0 = 0x8077c2b4,
        PID_BBPrtyWriteCallback1 = 0xf770f222,
        PID_BBPrtyWriteCallback2 = 0x6e79a398,
        PID_BBPrtyWriteCallback3 = 0x197e930e,
        PID_BBPrtyWriteCallback4 = 0x871a06ad,
        PID_BBPrtyWriteCallback5 = 0xf01d363b,
        PID_BBPrtyWriteCallback6 = 0x69146781,
        PID_BBPrtyWriteCallback7 = 0x1e135717,
        PID_BBPrtyWriteCallback8 = 0x8eac4a86,
        PID_BBPrtyWriteCallback9 = 0xf9ab7a10,
        PID_BBPrtyWriteCallback10 = 0x214cee37,
        PID_BBPrtyWriteCallback11 = 0x564bdea1,
        PID_BBPrtyWriteCallback12 = 0xcf428f1b,
        PID_BBPrtyWriteCallback13 = 0xb845bf8d,
        PID_BBPrtyWriteCallback14 = 0x26212a2e,
        PID_BBPrtyWriteCallback15 = 0x51261ab8,
        PID_BBPrtyWriteCallback16 = 0xc82f4b02,
        PID_BBPrtyWriteCallback17 = 0xbf287b94,
        PID_BBPrtyWriteCallback18 = 0x2f976605,
        PID_BBPrtyWriteCallback19 = 0x58905693,
        PID_BBPrtyWriteCallback20 = 0xa61bdf4,
        PID_BBPrtyWriteCallback21 = 0x7d668d62,
        PID_BBPrtyWriteCallback22 = 0xe46fdcd8,
        PID_BBPrtyWriteCallback23 = 0x9368ec4e,
        PID_BBPrtyWriteCallback24 = 0xd0c79ed,
        PID_BBPrtyWriteCallback25 = 0x7a0b497b,
        PID_BBPrtyWriteCallback26 = 0xe30218c1,
        PID_BBPrtyWriteCallback27 = 0x94052857,
        PID_BBPrtyWriteCallback28 = 0x4ba35c6,
        PID_BBPrtyWriteCallback29 = 0x73bd0550,
        PID_BBPrtyWriteCallback30 = 0x137a8cb5,
        PID_BBPrtyWriteCallback31 = 0x647dbc23,
        PID_BBPrtyWriteCallback32 = 0xfd74ed99,
        PID_BBPrtyWriteCallback33 = 0x8a73dd0f,
        PID_BBPrtyWriteCallback34 = 0x141748ac,
        PID_BBPrtyWriteCallback35 = 0x6310783a,
        PID_BBPrtyWriteCallback36 = 0xfa192980,
        PID_BBPrtyWriteCallback37 = 0x8d1e1916,
        PID_BBPrtyWriteCallback38 = 0x1da10487,
        PID_BBPrtyWriteCallback39 = 0x6aa63411,
        PID_BBPrtyWriteCallback40 = 0x5c3b1a72,
        PID_BBPrtyWriteCallback41 = 0x2b3c2ae4,
        PID_BBPrtyWriteCallback42 = 0xb2357b5e,
        PID_BBPrtyWriteCallback43 = 0xc5324bc8,
        PID_COUNT = 176
    };

protected:
    epiChar GetBBPrtyVirtual0_Callback() const;
    void SetBBPrtyVirtual0_Callback(epiChar value);
    epiWChar GetBBPrtyVirtual1_Callback() const;
    void SetBBPrtyVirtual1_Callback(epiWChar value);
    epiBool GetBBPrtyVirtual2_Callback() const;
    void SetBBPrtyVirtual2_Callback(epiBool value);
    epiByte GetBBPrtyVirtual3_Callback() const;
    void SetBBPrtyVirtual3_Callback(epiByte value);
    epiFloat GetBBPrtyVirtual4_Callback() const;
    void SetBBPrtyVirtual4_Callback(epiFloat value);
    epiDouble GetBBPrtyVirtual5_Callback() const;
    void SetBBPrtyVirtual5_Callback(epiDouble value);
    epiSize_t GetBBPrtyVirtual6_Callback() const;
    void SetBBPrtyVirtual6_Callback(epiSize_t value);
    epiU8 GetBBPrtyVirtual7_Callback() const;
    void SetBBPrtyVirtual7_Callback(epiU8 value);
    epiU16 GetBBPrtyVirtual8_Callback() const;
    void SetBBPrtyVirtual8_Callback(epiU16 value);
    epiU32 GetBBPrtyVirtual9_Callback() const;
    void SetBBPrtyVirtual9_Callback(epiU32 value);
    epiU64 GetBBPrtyVirtual10_Callback() const;
    void SetBBPrtyVirtual10_Callback(epiU64 value);
    epiS8 GetBBPrtyVirtual11_Callback() const;
    void SetBBPrtyVirtual11_Callback(epiS8 value);
    epiS16 GetBBPrtyVirtual12_Callback() const;
    void SetBBPrtyVirtual12_Callback(epiS16 value);
    epiS32 GetBBPrtyVirtual13_Callback() const;
    void SetBBPrtyVirtual13_Callback(epiS32 value);
    epiS64 GetBBPrtyVirtual14_Callback() const;
    void SetBBPrtyVirtual14_Callback(epiS64 value);
    const epiString& GetBBPrtyVirtual15_Callback() const;
    void SetBBPrtyVirtual15_Callback(const epiString& value);
    const epiWString& GetBBPrtyVirtual16_Callback() const;
    void SetBBPrtyVirtual16_Callback(const epiWString& value);
    const epiArray<epiS32>& GetBBPrtyVirtual17_Callback() const;
    void SetBBPrtyVirtual17_Callback(const epiArray<epiS32>& value);
    const epiPtrArray<epiS32>& GetBBPrtyVirtual18_Callback() const;
    void SetBBPrtyVirtual18_Callback(const epiPtrArray<epiS32>& value);
    const epiArray<epiString>& GetBBPrtyVirtual19_Callback() const;
    void SetBBPrtyVirtual19_Callback(const epiArray<epiString>& value);
    const epiPtrArray<epiString>& GetBBPrtyVirtual20_Callback() const;
    void SetBBPrtyVirtual20_Callback(const epiPtrArray<epiString>& value);
    const epiVec2f& GetBBPrtyVirtual21_Callback() const;
    void SetBBPrtyVirtual21_Callback(const epiVec2f& value);
    const epiVec2d& GetBBPrtyVirtual22_Callback() const;
    void SetBBPrtyVirtual22_Callback(const epiVec2d& value);
    const epiVec2s& GetBBPrtyVirtual23_Callback() const;
    void SetBBPrtyVirtual23_Callback(const epiVec2s& value);
    const epiVec2u& GetBBPrtyVirtual24_Callback() const;
    void SetBBPrtyVirtual24_Callback(const epiVec2u& value);
    const epiVec3f& GetBBPrtyVirtual25_Callback() const;
    void SetBBPrtyVirtual25_Callback(const epiVec3f& value);
    const epiVec3d& GetBBPrtyVirtual26_Callback() const;
    void SetBBPrtyVirtual26_Callback(const epiVec3d& value);
    const epiVec3s& GetBBPrtyVirtual27_Callback() const;
    void SetBBPrtyVirtual27_Callback(const epiVec3s& value);
    const epiVec3u& GetBBPrtyVirtual28_Callback() const;
    void SetBBPrtyVirtual28_Callback(const epiVec3u& value);
    const epiVec4f& GetBBPrtyVirtual29_Callback() const;
    void SetBBPrtyVirtual29_Callback(const epiVec4f& value);
    const epiVec4d& GetBBPrtyVirtual30_Callback() const;
    void SetBBPrtyVirtual30_Callback(const epiVec4d& value);
    const epiVec4s& GetBBPrtyVirtual31_Callback() const;
    void SetBBPrtyVirtual31_Callback(const epiVec4s& value);
    const epiVec4u& GetBBPrtyVirtual32_Callback() const;
    void SetBBPrtyVirtual32_Callback(const epiVec4u& value);
    const epiMat2x2f& GetBBPrtyVirtual33_Callback() const;
    void SetBBPrtyVirtual33_Callback(const epiMat2x2f& value);
    const epiMat3x3f& GetBBPrtyVirtual34_Callback() const;
    void SetBBPrtyVirtual34_Callback(const epiMat3x3f& value);
    const epiMat4x4f& GetBBPrtyVirtual35_Callback() const;
    void SetBBPrtyVirtual35_Callback(const epiMat4x4f& value);
    const epiComplexf& GetBBPrtyVirtual36_Callback() const;
    void SetBBPrtyVirtual36_Callback(const epiComplexf& value);
    const epiComplexd& GetBBPrtyVirtual37_Callback() const;
    void SetBBPrtyVirtual37_Callback(const epiComplexd& value);
    const epiRect2f& GetBBPrtyVirtual38_Callback() const;
    void SetBBPrtyVirtual38_Callback(const epiRect2f& value);
    const epiRect2d& GetBBPrtyVirtual39_Callback() const;
    void SetBBPrtyVirtual39_Callback(const epiRect2d& value);
    const epiRect2s& GetBBPrtyVirtual40_Callback() const;
    void SetBBPrtyVirtual40_Callback(const epiRect2s& value);
    const epiRect2u& GetBBPrtyVirtual41_Callback() const;
    void SetBBPrtyVirtual41_Callback(const epiRect2u& value);
    const InplaceClass& GetBBPrtyVirtual42_Callback() const;
    void SetBBPrtyVirtual42_Callback(const InplaceClass& value);
    const InplaceClass* GetBBPrtyVirtual43_Callback() const;
    void SetBBPrtyVirtual43_Callback(InplaceClass* value);
    epiChar GetBBPrtyReadCallback0_Callback() const;
    epiWChar GetBBPrtyReadCallback1_Callback() const;
    epiBool GetBBPrtyReadCallback2_Callback() const;
    epiByte GetBBPrtyReadCallback3_Callback() const;
    epiFloat GetBBPrtyReadCallback4_Callback() const;
    epiDouble GetBBPrtyReadCallback5_Callback() const;
    epiSize_t GetBBPrtyReadCallback6_Callback() const;
    epiU8 GetBBPrtyReadCallback7_Callback() const;
    epiU16 GetBBPrtyReadCallback8_Callback() const;
    epiU32 GetBBPrtyReadCallback9_Callback() const;
    epiU64 GetBBPrtyReadCallback10_Callback() const;
    epiS8 GetBBPrtyReadCallback11_Callback() const;
    epiS16 GetBBPrtyReadCallback12_Callback() const;
    epiS32 GetBBPrtyReadCallback13_Callback() const;
    epiS64 GetBBPrtyReadCallback14_Callback() const;
    const epiString& GetBBPrtyReadCallback15_Callback() const;
    const epiWString& GetBBPrtyReadCallback16_Callback() const;
    const epiArray<epiS32>& GetBBPrtyReadCallback17_Callback() const;
    const epiPtrArray<epiS32>& GetBBPrtyReadCallback18_Callback() const;
    const epiArray<epiString>& GetBBPrtyReadCallback19_Callback() const;
    const epiPtrArray<epiString>& GetBBPrtyReadCallback20_Callback() const;
    const epiVec2f& GetBBPrtyReadCallback21_Callback() const;
    const epiVec2d& GetBBPrtyReadCallback22_Callback() const;
    const epiVec2s& GetBBPrtyReadCallback23_Callback() const;
    const epiVec2u& GetBBPrtyReadCallback24_Callback() const;
    const epiVec3f& GetBBPrtyReadCallback25_Callback() const;
    const epiVec3d& GetBBPrtyReadCallback26_Callback() const;
    const epiVec3s& GetBBPrtyReadCallback27_Callback() const;
    const epiVec3u& GetBBPrtyReadCallback28_Callback() const;
    const epiVec4f& GetBBPrtyReadCallback29_Callback() const;
    const epiVec4d& GetBBPrtyReadCallback30_Callback() const;
    const epiVec4s& GetBBPrtyReadCallback31_Callback() const;
    const epiVec4u& GetBBPrtyReadCallback32_Callback() const;
    const epiMat2x2f& GetBBPrtyReadCallback33_Callback() const;
    const epiMat3x3f& GetBBPrtyReadCallback34_Callback() const;
    const epiMat4x4f& GetBBPrtyReadCallback35_Callback() const;
    const epiComplexf& GetBBPrtyReadCallback36_Callback() const;
    const epiComplexd& GetBBPrtyReadCallback37_Callback() const;
    const epiRect2f& GetBBPrtyReadCallback38_Callback() const;
    const epiRect2d& GetBBPrtyReadCallback39_Callback() const;
    const epiRect2s& GetBBPrtyReadCallback40_Callback() const;
    const epiRect2u& GetBBPrtyReadCallback41_Callback() const;
    const InplaceClass& GetBBPrtyReadCallback42_Callback() const;
    const InplaceClass* GetBBPrtyReadCallback43_Callback() const;
    void SetBBPrtyWriteCallback0_Callback(epiChar value);
    void SetBBPrtyWriteCallback1_Callback(epiWChar value);
    void SetBBPrtyWriteCallback2_Callback(epiBool value);
    void SetBBPrtyWriteCallback3_Callback(epiByte value);
    void SetBBPrtyWriteCallback4_Callback(epiFloat value);
    void SetBBPrtyWriteCallback5_Callback(epiDouble value);
    void SetBBPrtyWriteCallback6_Callback(epiSize_t value);
    void SetBBPrtyWriteCallback7_Callback(epiU8 value);
    void SetBBPrtyWriteCallback8_Callback(epiU16 value);
    void SetBBPrtyWriteCallback9_Callback(epiU32 value);
    void SetBBPrtyWriteCallback10_Callback(epiU64 value);
    void SetBBPrtyWriteCallback11_Callback(epiS8 value);
    void SetBBPrtyWriteCallback12_Callback(epiS16 value);
    void SetBBPrtyWriteCallback13_Callback(epiS32 value);
    void SetBBPrtyWriteCallback14_Callback(epiS64 value);
    void SetBBPrtyWriteCallback15_Callback(const epiString& value);
    void SetBBPrtyWriteCallback16_Callback(const epiWString& value);
    void SetBBPrtyWriteCallback17_Callback(const epiArray<epiS32>& value);
    void SetBBPrtyWriteCallback18_Callback(const epiPtrArray<epiS32>& value);
    void SetBBPrtyWriteCallback19_Callback(const epiArray<epiString>& value);
    void SetBBPrtyWriteCallback20_Callback(const epiPtrArray<epiString>& value);
    void SetBBPrtyWriteCallback21_Callback(const epiVec2f& value);
    void SetBBPrtyWriteCallback22_Callback(const epiVec2d& value);
    void SetBBPrtyWriteCallback23_Callback(const epiVec2s& value);
    void SetBBPrtyWriteCallback24_Callback(const epiVec2u& value);
    void SetBBPrtyWriteCallback25_Callback(const epiVec3f& value);
    void SetBBPrtyWriteCallback26_Callback(const epiVec3d& value);
    void SetBBPrtyWriteCallback27_Callback(const epiVec3s& value);
    void SetBBPrtyWriteCallback28_Callback(const epiVec3u& value);
    void SetBBPrtyWriteCallback29_Callback(const epiVec4f& value);
    void SetBBPrtyWriteCallback30_Callback(const epiVec4d& value);
    void SetBBPrtyWriteCallback31_Callback(const epiVec4s& value);
    void SetBBPrtyWriteCallback32_Callback(const epiVec4u& value);
    void SetBBPrtyWriteCallback33_Callback(const epiMat2x2f& value);
    void SetBBPrtyWriteCallback34_Callback(const epiMat3x3f& value);
    void SetBBPrtyWriteCallback35_Callback(const epiMat4x4f& value);
    void SetBBPrtyWriteCallback36_Callback(const epiComplexf& value);
    void SetBBPrtyWriteCallback37_Callback(const epiComplexd& value);
    void SetBBPrtyWriteCallback38_Callback(const epiRect2f& value);
    void SetBBPrtyWriteCallback39_Callback(const epiRect2d& value);
    void SetBBPrtyWriteCallback40_Callback(const epiRect2s& value);
    void SetBBPrtyWriteCallback41_Callback(const epiRect2u& value);
    void SetBBPrtyWriteCallback42_Callback(const InplaceClass& value);
    void SetBBPrtyWriteCallback43_Callback(InplaceClass* value);

protected:
    epiChar m_BBPrty0{'\0'};
    epiWChar m_BBPrty1{L'\0'};
    epiBool m_BBPrty2{false};
    epiByte m_BBPrty3{0};
    epiFloat m_BBPrty4{0.0f};
    epiDouble m_BBPrty5{0.0};
    epiSize_t m_BBPrty6{0};
    epiU8 m_BBPrty7{0};
    epiU16 m_BBPrty8{0};
    epiU32 m_BBPrty9{0};
    epiU64 m_BBPrty10{0};
    epiS8 m_BBPrty11{0};
    epiS16 m_BBPrty12{0};
    epiS32 m_BBPrty13{0};
    epiS64 m_BBPrty14{0};
    epiString m_BBPrty15{epiDEBUG_ONLY("Empty")};
    epiWString m_BBPrty16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_BBPrty17{};
    epiPtrArray<epiS32> m_BBPrty18{};
    epiArray<epiString> m_BBPrty19{};
    epiPtrArray<epiString> m_BBPrty20{};
    epiVec2f m_BBPrty21{};
    epiVec2d m_BBPrty22{};
    epiVec2s m_BBPrty23{};
    epiVec2u m_BBPrty24{};
    epiVec3f m_BBPrty25{};
    epiVec3d m_BBPrty26{};
    epiVec3s m_BBPrty27{};
    epiVec3u m_BBPrty28{};
    epiVec4f m_BBPrty29{};
    epiVec4d m_BBPrty30{};
    epiVec4s m_BBPrty31{};
    epiVec4u m_BBPrty32{};
    epiMat2x2f m_BBPrty33{};
    epiMat3x3f m_BBPrty34{};
    epiMat4x4f m_BBPrty35{};
    epiComplexf m_BBPrty36{};
    epiComplexd m_BBPrty37{};
    epiRect2f m_BBPrty38{};
    epiRect2d m_BBPrty39{};
    epiRect2s m_BBPrty40{};
    epiRect2u m_BBPrty41{};
    InplaceClass m_BBPrty42{};
    InplaceClass* m_BBPrty43{nullptr};
    epiChar m_BBPrtyReadCallback0{'\0'};
    epiWChar m_BBPrtyReadCallback1{L'\0'};
    epiBool m_BBPrtyReadCallback2{false};
    epiByte m_BBPrtyReadCallback3{0};
    epiFloat m_BBPrtyReadCallback4{0.0f};
    epiDouble m_BBPrtyReadCallback5{0.0};
    epiSize_t m_BBPrtyReadCallback6{0};
    epiU8 m_BBPrtyReadCallback7{0};
    epiU16 m_BBPrtyReadCallback8{0};
    epiU32 m_BBPrtyReadCallback9{0};
    epiU64 m_BBPrtyReadCallback10{0};
    epiS8 m_BBPrtyReadCallback11{0};
    epiS16 m_BBPrtyReadCallback12{0};
    epiS32 m_BBPrtyReadCallback13{0};
    epiS64 m_BBPrtyReadCallback14{0};
    epiString m_BBPrtyReadCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_BBPrtyReadCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_BBPrtyReadCallback17{};
    epiPtrArray<epiS32> m_BBPrtyReadCallback18{};
    epiArray<epiString> m_BBPrtyReadCallback19{};
    epiPtrArray<epiString> m_BBPrtyReadCallback20{};
    epiVec2f m_BBPrtyReadCallback21{};
    epiVec2d m_BBPrtyReadCallback22{};
    epiVec2s m_BBPrtyReadCallback23{};
    epiVec2u m_BBPrtyReadCallback24{};
    epiVec3f m_BBPrtyReadCallback25{};
    epiVec3d m_BBPrtyReadCallback26{};
    epiVec3s m_BBPrtyReadCallback27{};
    epiVec3u m_BBPrtyReadCallback28{};
    epiVec4f m_BBPrtyReadCallback29{};
    epiVec4d m_BBPrtyReadCallback30{};
    epiVec4s m_BBPrtyReadCallback31{};
    epiVec4u m_BBPrtyReadCallback32{};
    epiMat2x2f m_BBPrtyReadCallback33{};
    epiMat3x3f m_BBPrtyReadCallback34{};
    epiMat4x4f m_BBPrtyReadCallback35{};
    epiComplexf m_BBPrtyReadCallback36{};
    epiComplexd m_BBPrtyReadCallback37{};
    epiRect2f m_BBPrtyReadCallback38{};
    epiRect2d m_BBPrtyReadCallback39{};
    epiRect2s m_BBPrtyReadCallback40{};
    epiRect2u m_BBPrtyReadCallback41{};
    InplaceClass m_BBPrtyReadCallback42{};
    InplaceClass* m_BBPrtyReadCallback43{nullptr};
    epiChar m_BBPrtyWriteCallback0{'\0'};
    epiWChar m_BBPrtyWriteCallback1{L'\0'};
    epiBool m_BBPrtyWriteCallback2{false};
    epiByte m_BBPrtyWriteCallback3{0};
    epiFloat m_BBPrtyWriteCallback4{0.0f};
    epiDouble m_BBPrtyWriteCallback5{0.0};
    epiSize_t m_BBPrtyWriteCallback6{0};
    epiU8 m_BBPrtyWriteCallback7{0};
    epiU16 m_BBPrtyWriteCallback8{0};
    epiU32 m_BBPrtyWriteCallback9{0};
    epiU64 m_BBPrtyWriteCallback10{0};
    epiS8 m_BBPrtyWriteCallback11{0};
    epiS16 m_BBPrtyWriteCallback12{0};
    epiS32 m_BBPrtyWriteCallback13{0};
    epiS64 m_BBPrtyWriteCallback14{0};
    epiString m_BBPrtyWriteCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_BBPrtyWriteCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_BBPrtyWriteCallback17{};
    epiPtrArray<epiS32> m_BBPrtyWriteCallback18{};
    epiArray<epiString> m_BBPrtyWriteCallback19{};
    epiPtrArray<epiString> m_BBPrtyWriteCallback20{};
    epiVec2f m_BBPrtyWriteCallback21{};
    epiVec2d m_BBPrtyWriteCallback22{};
    epiVec2s m_BBPrtyWriteCallback23{};
    epiVec2u m_BBPrtyWriteCallback24{};
    epiVec3f m_BBPrtyWriteCallback25{};
    epiVec3d m_BBPrtyWriteCallback26{};
    epiVec3s m_BBPrtyWriteCallback27{};
    epiVec3u m_BBPrtyWriteCallback28{};
    epiVec4f m_BBPrtyWriteCallback29{};
    epiVec4d m_BBPrtyWriteCallback30{};
    epiVec4s m_BBPrtyWriteCallback31{};
    epiVec4u m_BBPrtyWriteCallback32{};
    epiMat2x2f m_BBPrtyWriteCallback33{};
    epiMat3x3f m_BBPrtyWriteCallback34{};
    epiMat4x4f m_BBPrtyWriteCallback35{};
    epiComplexf m_BBPrtyWriteCallback36{};
    epiComplexd m_BBPrtyWriteCallback37{};
    epiRect2f m_BBPrtyWriteCallback38{};
    epiRect2d m_BBPrtyWriteCallback39{};
    epiRect2s m_BBPrtyWriteCallback40{};
    epiRect2u m_BBPrtyWriteCallback41{};
    InplaceClass m_BBPrtyWriteCallback42{};
    InplaceClass* m_BBPrtyWriteCallback43{nullptr};

EPI_GENREGION_END(TestClassBB)

public:
    void Reset() override;
};

class IBuzz
{
public:
    virtual void Foo() = 0;
};

class TestClassCC : public TestClassC, IBuzz
{
EPI_GENREGION_BEGIN(TestClassCC)

EPI_GENHIDDEN_TestClassCC()

public:
    constexpr static epiMetaTypeID TypeID{0xc0219bab};

    enum TestClassCC_PIDs
    {
        PID_CCPrty0 = 0x13ba5d1b,
        PID_CCPrty1 = 0x64bd6d8d,
        PID_CCPrty2 = 0xfdb43c37,
        PID_CCPrty3 = 0x8ab30ca1,
        PID_CCPrty4 = 0x14d79902,
        PID_CCPrty5 = 0x63d0a994,
        PID_CCPrty6 = 0xfad9f82e,
        PID_CCPrty7 = 0x8ddec8b8,
        PID_CCPrty8 = 0x1d61d529,
        PID_CCPrty9 = 0x6a66e5bf,
        PID_CCPrty10 = 0x67b69dd1,
        PID_CCPrty11 = 0x10b1ad47,
        PID_CCPrty12 = 0x89b8fcfd,
        PID_CCPrty13 = 0xfebfcc6b,
        PID_CCPrty14 = 0x60db59c8,
        PID_CCPrty15 = 0x17dc695e,
        PID_CCPrty16 = 0x8ed538e4,
        PID_CCPrty17 = 0xf9d20872,
        PID_CCPrty18 = 0x696d15e3,
        PID_CCPrty19 = 0x1e6a2575,
        PID_CCPrty20 = 0x4c9bce12,
        PID_CCPrty21 = 0x3b9cfe84,
        PID_CCPrty22 = 0xa295af3e,
        PID_CCPrty23 = 0xd5929fa8,
        PID_CCPrty24 = 0x4bf60a0b,
        PID_CCPrty25 = 0x3cf13a9d,
        PID_CCPrty26 = 0xa5f86b27,
        PID_CCPrty27 = 0xd2ff5bb1,
        PID_CCPrty28 = 0x42404620,
        PID_CCPrty29 = 0x354776b6,
        PID_CCPrty30 = 0x5580ff53,
        PID_CCPrty31 = 0x2287cfc5,
        PID_CCPrty32 = 0xbb8e9e7f,
        PID_CCPrty33 = 0xcc89aee9,
        PID_CCPrty34 = 0x52ed3b4a,
        PID_CCPrty35 = 0x25ea0bdc,
        PID_CCPrty36 = 0xbce35a66,
        PID_CCPrty37 = 0xcbe46af0,
        PID_CCPrty38 = 0x5b5b7761,
        PID_CCPrty39 = 0x2c5c47f7,
        PID_CCPrty40 = 0x1ac16994,
        PID_CCPrty41 = 0x6dc65902,
        PID_CCPrty42 = 0xf4cf08b8,
        PID_CCPrty43 = 0x83c8382e,
        PID_CCPrtyVirtual0 = 0xe8094bd6,
        PID_CCPrtyVirtual1 = 0x9f0e7b40,
        PID_CCPrtyVirtual2 = 0x6072afa,
        PID_CCPrtyVirtual3 = 0x71001a6c,
        PID_CCPrtyVirtual4 = 0xef648fcf,
        PID_CCPrtyVirtual5 = 0x9863bf59,
        PID_CCPrtyVirtual6 = 0x16aeee3,
        PID_CCPrtyVirtual7 = 0x766dde75,
        PID_CCPrtyVirtual8 = 0xe6d2c3e4,
        PID_CCPrtyVirtual9 = 0x91d5f372,
        PID_CCPrtyVirtual10 = 0x829890ca,
        PID_CCPrtyVirtual11 = 0xf59fa05c,
        PID_CCPrtyVirtual12 = 0x6c96f1e6,
        PID_CCPrtyVirtual13 = 0x1b91c170,
        PID_CCPrtyVirtual14 = 0x85f554d3,
        PID_CCPrtyVirtual15 = 0xf2f26445,
        PID_CCPrtyVirtual16 = 0x6bfb35ff,
        PID_CCPrtyVirtual17 = 0x1cfc0569,
        PID_CCPrtyVirtual18 = 0x8c4318f8,
        PID_CCPrtyVirtual19 = 0xfb44286e,
        PID_CCPrtyVirtual20 = 0xa9b5c309,
        PID_CCPrtyVirtual21 = 0xdeb2f39f,
        PID_CCPrtyVirtual22 = 0x47bba225,
        PID_CCPrtyVirtual23 = 0x30bc92b3,
        PID_CCPrtyVirtual24 = 0xaed80710,
        PID_CCPrtyVirtual25 = 0xd9df3786,
        PID_CCPrtyVirtual26 = 0x40d6663c,
        PID_CCPrtyVirtual27 = 0x37d156aa,
        PID_CCPrtyVirtual28 = 0xa76e4b3b,
        PID_CCPrtyVirtual29 = 0xd0697bad,
        PID_CCPrtyVirtual30 = 0xb0aef248,
        PID_CCPrtyVirtual31 = 0xc7a9c2de,
        PID_CCPrtyVirtual32 = 0x5ea09364,
        PID_CCPrtyVirtual33 = 0x29a7a3f2,
        PID_CCPrtyVirtual34 = 0xb7c33651,
        PID_CCPrtyVirtual35 = 0xc0c406c7,
        PID_CCPrtyVirtual36 = 0x59cd577d,
        PID_CCPrtyVirtual37 = 0x2eca67eb,
        PID_CCPrtyVirtual38 = 0xbe757a7a,
        PID_CCPrtyVirtual39 = 0xc9724aec,
        PID_CCPrtyVirtual40 = 0xffef648f,
        PID_CCPrtyVirtual41 = 0x88e85419,
        PID_CCPrtyVirtual42 = 0x11e105a3,
        PID_CCPrtyVirtual43 = 0x66e63535,
        PID_CCPrtyReadCallback0 = 0x6cb3d6a0,
        PID_CCPrtyReadCallback1 = 0x1bb4e636,
        PID_CCPrtyReadCallback2 = 0x82bdb78c,
        PID_CCPrtyReadCallback3 = 0xf5ba871a,
        PID_CCPrtyReadCallback4 = 0x6bde12b9,
        PID_CCPrtyReadCallback5 = 0x1cd9222f,
        PID_CCPrtyReadCallback6 = 0x85d07395,
        PID_CCPrtyReadCallback7 = 0xf2d74303,
        PID_CCPrtyReadCallback8 = 0x62685e92,
        PID_CCPrtyReadCallback9 = 0x156f6e04,
        PID_CCPrtyReadCallback10 = 0x3b7afe5e,
        PID_CCPrtyReadCallback11 = 0x4c7dcec8,
        PID_CCPrtyReadCallback12 = 0xd5749f72,
        PID_CCPrtyReadCallback13 = 0xa273afe4,
        PID_CCPrtyReadCallback14 = 0x3c173a47,
        PID_CCPrtyReadCallback15 = 0x4b100ad1,
        PID_CCPrtyReadCallback16 = 0xd2195b6b,
        PID_CCPrtyReadCallback17 = 0xa51e6bfd,
        PID_CCPrtyReadCallback18 = 0x35a1766c,
        PID_CCPrtyReadCallback19 = 0x42a646fa,
        PID_CCPrtyReadCallback20 = 0x1057ad9d,
        PID_CCPrtyReadCallback21 = 0x67509d0b,
        PID_CCPrtyReadCallback22 = 0xfe59ccb1,
        PID_CCPrtyReadCallback23 = 0x895efc27,
        PID_CCPrtyReadCallback24 = 0x173a6984,
        PID_CCPrtyReadCallback25 = 0x603d5912,
        PID_CCPrtyReadCallback26 = 0xf93408a8,
        PID_CCPrtyReadCallback27 = 0x8e33383e,
        PID_CCPrtyReadCallback28 = 0x1e8c25af,
        PID_CCPrtyReadCallback29 = 0x698b1539,
        PID_CCPrtyReadCallback30 = 0x94c9cdc,
        PID_CCPrtyReadCallback31 = 0x7e4bac4a,
        PID_CCPrtyReadCallback32 = 0xe742fdf0,
        PID_CCPrtyReadCallback33 = 0x9045cd66,
        PID_CCPrtyReadCallback34 = 0xe2158c5,
        PID_CCPrtyReadCallback35 = 0x79266853,
        PID_CCPrtyReadCallback36 = 0xe02f39e9,
        PID_CCPrtyReadCallback37 = 0x9728097f,
        PID_CCPrtyReadCallback38 = 0x79714ee,
        PID_CCPrtyReadCallback39 = 0x70902478,
        PID_CCPrtyReadCallback40 = 0x460d0a1b,
        PID_CCPrtyReadCallback41 = 0x310a3a8d,
        PID_CCPrtyReadCallback42 = 0xa8036b37,
        PID_CCPrtyReadCallback43 = 0xdf045ba1,
        PID_CCPrtyWriteCallback0 = 0x32f279aa,
        PID_CCPrtyWriteCallback1 = 0x45f5493c,
        PID_CCPrtyWriteCallback2 = 0xdcfc1886,
        PID_CCPrtyWriteCallback3 = 0xabfb2810,
        PID_CCPrtyWriteCallback4 = 0x359fbdb3,
        PID_CCPrtyWriteCallback5 = 0x42988d25,
        PID_CCPrtyWriteCallback6 = 0xdb91dc9f,
        PID_CCPrtyWriteCallback7 = 0xac96ec09,
        PID_CCPrtyWriteCallback8 = 0x3c29f198,
        PID_CCPrtyWriteCallback9 = 0x4b2ec10e,
        PID_CCPrtyWriteCallback10 = 0xdbf156ef,
        PID_CCPrtyWriteCallback11 = 0xacf66679,
        PID_CCPrtyWriteCallback12 = 0x35ff37c3,
        PID_CCPrtyWriteCallback13 = 0x42f80755,
        PID_CCPrtyWriteCallback14 = 0xdc9c92f6,
        PID_CCPrtyWriteCallback15 = 0xab9ba260,
        PID_CCPrtyWriteCallback16 = 0x3292f3da,
        PID_CCPrtyWriteCallback17 = 0x4595c34c,
        PID_CCPrtyWriteCallback18 = 0xd52adedd,
        PID_CCPrtyWriteCallback19 = 0xa22dee4b,
        PID_CCPrtyWriteCallback20 = 0xf0dc052c,
        PID_CCPrtyWriteCallback21 = 0x87db35ba,
        PID_CCPrtyWriteCallback22 = 0x1ed26400,
        PID_CCPrtyWriteCallback23 = 0x69d55496,
        PID_CCPrtyWriteCallback24 = 0xf7b1c135,
        PID_CCPrtyWriteCallback25 = 0x80b6f1a3,
        PID_CCPrtyWriteCallback26 = 0x19bfa019,
        PID_CCPrtyWriteCallback27 = 0x6eb8908f,
        PID_CCPrtyWriteCallback28 = 0xfe078d1e,
        PID_CCPrtyWriteCallback29 = 0x8900bd88,
        PID_CCPrtyWriteCallback30 = 0xe9c7346d,
        PID_CCPrtyWriteCallback31 = 0x9ec004fb,
        PID_CCPrtyWriteCallback32 = 0x7c95541,
        PID_CCPrtyWriteCallback33 = 0x70ce65d7,
        PID_CCPrtyWriteCallback34 = 0xeeaaf074,
        PID_CCPrtyWriteCallback35 = 0x99adc0e2,
        PID_CCPrtyWriteCallback36 = 0xa49158,
        PID_CCPrtyWriteCallback37 = 0x77a3a1ce,
        PID_CCPrtyWriteCallback38 = 0xe71cbc5f,
        PID_CCPrtyWriteCallback39 = 0x901b8cc9,
        PID_CCPrtyWriteCallback40 = 0xa686a2aa,
        PID_CCPrtyWriteCallback41 = 0xd181923c,
        PID_CCPrtyWriteCallback42 = 0x4888c386,
        PID_CCPrtyWriteCallback43 = 0x3f8ff310,
        PID_COUNT = 176
    };

protected:
    epiChar GetCCPrtyVirtual0_Callback() const;
    void SetCCPrtyVirtual0_Callback(epiChar value);
    epiWChar GetCCPrtyVirtual1_Callback() const;
    void SetCCPrtyVirtual1_Callback(epiWChar value);
    epiBool GetCCPrtyVirtual2_Callback() const;
    void SetCCPrtyVirtual2_Callback(epiBool value);
    epiByte GetCCPrtyVirtual3_Callback() const;
    void SetCCPrtyVirtual3_Callback(epiByte value);
    epiFloat GetCCPrtyVirtual4_Callback() const;
    void SetCCPrtyVirtual4_Callback(epiFloat value);
    epiDouble GetCCPrtyVirtual5_Callback() const;
    void SetCCPrtyVirtual5_Callback(epiDouble value);
    epiSize_t GetCCPrtyVirtual6_Callback() const;
    void SetCCPrtyVirtual6_Callback(epiSize_t value);
    epiU8 GetCCPrtyVirtual7_Callback() const;
    void SetCCPrtyVirtual7_Callback(epiU8 value);
    epiU16 GetCCPrtyVirtual8_Callback() const;
    void SetCCPrtyVirtual8_Callback(epiU16 value);
    epiU32 GetCCPrtyVirtual9_Callback() const;
    void SetCCPrtyVirtual9_Callback(epiU32 value);
    epiU64 GetCCPrtyVirtual10_Callback() const;
    void SetCCPrtyVirtual10_Callback(epiU64 value);
    epiS8 GetCCPrtyVirtual11_Callback() const;
    void SetCCPrtyVirtual11_Callback(epiS8 value);
    epiS16 GetCCPrtyVirtual12_Callback() const;
    void SetCCPrtyVirtual12_Callback(epiS16 value);
    epiS32 GetCCPrtyVirtual13_Callback() const;
    void SetCCPrtyVirtual13_Callback(epiS32 value);
    epiS64 GetCCPrtyVirtual14_Callback() const;
    void SetCCPrtyVirtual14_Callback(epiS64 value);
    const epiString& GetCCPrtyVirtual15_Callback() const;
    void SetCCPrtyVirtual15_Callback(const epiString& value);
    const epiWString& GetCCPrtyVirtual16_Callback() const;
    void SetCCPrtyVirtual16_Callback(const epiWString& value);
    const epiArray<epiS32>& GetCCPrtyVirtual17_Callback() const;
    void SetCCPrtyVirtual17_Callback(const epiArray<epiS32>& value);
    const epiPtrArray<epiS32>& GetCCPrtyVirtual18_Callback() const;
    void SetCCPrtyVirtual18_Callback(const epiPtrArray<epiS32>& value);
    const epiArray<epiString>& GetCCPrtyVirtual19_Callback() const;
    void SetCCPrtyVirtual19_Callback(const epiArray<epiString>& value);
    const epiPtrArray<epiString>& GetCCPrtyVirtual20_Callback() const;
    void SetCCPrtyVirtual20_Callback(const epiPtrArray<epiString>& value);
    const epiVec2f& GetCCPrtyVirtual21_Callback() const;
    void SetCCPrtyVirtual21_Callback(const epiVec2f& value);
    const epiVec2d& GetCCPrtyVirtual22_Callback() const;
    void SetCCPrtyVirtual22_Callback(const epiVec2d& value);
    const epiVec2s& GetCCPrtyVirtual23_Callback() const;
    void SetCCPrtyVirtual23_Callback(const epiVec2s& value);
    const epiVec2u& GetCCPrtyVirtual24_Callback() const;
    void SetCCPrtyVirtual24_Callback(const epiVec2u& value);
    const epiVec3f& GetCCPrtyVirtual25_Callback() const;
    void SetCCPrtyVirtual25_Callback(const epiVec3f& value);
    const epiVec3d& GetCCPrtyVirtual26_Callback() const;
    void SetCCPrtyVirtual26_Callback(const epiVec3d& value);
    const epiVec3s& GetCCPrtyVirtual27_Callback() const;
    void SetCCPrtyVirtual27_Callback(const epiVec3s& value);
    const epiVec3u& GetCCPrtyVirtual28_Callback() const;
    void SetCCPrtyVirtual28_Callback(const epiVec3u& value);
    const epiVec4f& GetCCPrtyVirtual29_Callback() const;
    void SetCCPrtyVirtual29_Callback(const epiVec4f& value);
    const epiVec4d& GetCCPrtyVirtual30_Callback() const;
    void SetCCPrtyVirtual30_Callback(const epiVec4d& value);
    const epiVec4s& GetCCPrtyVirtual31_Callback() const;
    void SetCCPrtyVirtual31_Callback(const epiVec4s& value);
    const epiVec4u& GetCCPrtyVirtual32_Callback() const;
    void SetCCPrtyVirtual32_Callback(const epiVec4u& value);
    const epiMat2x2f& GetCCPrtyVirtual33_Callback() const;
    void SetCCPrtyVirtual33_Callback(const epiMat2x2f& value);
    const epiMat3x3f& GetCCPrtyVirtual34_Callback() const;
    void SetCCPrtyVirtual34_Callback(const epiMat3x3f& value);
    const epiMat4x4f& GetCCPrtyVirtual35_Callback() const;
    void SetCCPrtyVirtual35_Callback(const epiMat4x4f& value);
    const epiComplexf& GetCCPrtyVirtual36_Callback() const;
    void SetCCPrtyVirtual36_Callback(const epiComplexf& value);
    const epiComplexd& GetCCPrtyVirtual37_Callback() const;
    void SetCCPrtyVirtual37_Callback(const epiComplexd& value);
    const epiRect2f& GetCCPrtyVirtual38_Callback() const;
    void SetCCPrtyVirtual38_Callback(const epiRect2f& value);
    const epiRect2d& GetCCPrtyVirtual39_Callback() const;
    void SetCCPrtyVirtual39_Callback(const epiRect2d& value);
    const epiRect2s& GetCCPrtyVirtual40_Callback() const;
    void SetCCPrtyVirtual40_Callback(const epiRect2s& value);
    const epiRect2u& GetCCPrtyVirtual41_Callback() const;
    void SetCCPrtyVirtual41_Callback(const epiRect2u& value);
    const InplaceClass& GetCCPrtyVirtual42_Callback() const;
    void SetCCPrtyVirtual42_Callback(const InplaceClass& value);
    const InplaceClass* GetCCPrtyVirtual43_Callback() const;
    void SetCCPrtyVirtual43_Callback(InplaceClass* value);
    epiChar GetCCPrtyReadCallback0_Callback() const;
    epiWChar GetCCPrtyReadCallback1_Callback() const;
    epiBool GetCCPrtyReadCallback2_Callback() const;
    epiByte GetCCPrtyReadCallback3_Callback() const;
    epiFloat GetCCPrtyReadCallback4_Callback() const;
    epiDouble GetCCPrtyReadCallback5_Callback() const;
    epiSize_t GetCCPrtyReadCallback6_Callback() const;
    epiU8 GetCCPrtyReadCallback7_Callback() const;
    epiU16 GetCCPrtyReadCallback8_Callback() const;
    epiU32 GetCCPrtyReadCallback9_Callback() const;
    epiU64 GetCCPrtyReadCallback10_Callback() const;
    epiS8 GetCCPrtyReadCallback11_Callback() const;
    epiS16 GetCCPrtyReadCallback12_Callback() const;
    epiS32 GetCCPrtyReadCallback13_Callback() const;
    epiS64 GetCCPrtyReadCallback14_Callback() const;
    const epiString& GetCCPrtyReadCallback15_Callback() const;
    const epiWString& GetCCPrtyReadCallback16_Callback() const;
    const epiArray<epiS32>& GetCCPrtyReadCallback17_Callback() const;
    const epiPtrArray<epiS32>& GetCCPrtyReadCallback18_Callback() const;
    const epiArray<epiString>& GetCCPrtyReadCallback19_Callback() const;
    const epiPtrArray<epiString>& GetCCPrtyReadCallback20_Callback() const;
    const epiVec2f& GetCCPrtyReadCallback21_Callback() const;
    const epiVec2d& GetCCPrtyReadCallback22_Callback() const;
    const epiVec2s& GetCCPrtyReadCallback23_Callback() const;
    const epiVec2u& GetCCPrtyReadCallback24_Callback() const;
    const epiVec3f& GetCCPrtyReadCallback25_Callback() const;
    const epiVec3d& GetCCPrtyReadCallback26_Callback() const;
    const epiVec3s& GetCCPrtyReadCallback27_Callback() const;
    const epiVec3u& GetCCPrtyReadCallback28_Callback() const;
    const epiVec4f& GetCCPrtyReadCallback29_Callback() const;
    const epiVec4d& GetCCPrtyReadCallback30_Callback() const;
    const epiVec4s& GetCCPrtyReadCallback31_Callback() const;
    const epiVec4u& GetCCPrtyReadCallback32_Callback() const;
    const epiMat2x2f& GetCCPrtyReadCallback33_Callback() const;
    const epiMat3x3f& GetCCPrtyReadCallback34_Callback() const;
    const epiMat4x4f& GetCCPrtyReadCallback35_Callback() const;
    const epiComplexf& GetCCPrtyReadCallback36_Callback() const;
    const epiComplexd& GetCCPrtyReadCallback37_Callback() const;
    const epiRect2f& GetCCPrtyReadCallback38_Callback() const;
    const epiRect2d& GetCCPrtyReadCallback39_Callback() const;
    const epiRect2s& GetCCPrtyReadCallback40_Callback() const;
    const epiRect2u& GetCCPrtyReadCallback41_Callback() const;
    const InplaceClass& GetCCPrtyReadCallback42_Callback() const;
    const InplaceClass* GetCCPrtyReadCallback43_Callback() const;
    void SetCCPrtyWriteCallback0_Callback(epiChar value);
    void SetCCPrtyWriteCallback1_Callback(epiWChar value);
    void SetCCPrtyWriteCallback2_Callback(epiBool value);
    void SetCCPrtyWriteCallback3_Callback(epiByte value);
    void SetCCPrtyWriteCallback4_Callback(epiFloat value);
    void SetCCPrtyWriteCallback5_Callback(epiDouble value);
    void SetCCPrtyWriteCallback6_Callback(epiSize_t value);
    void SetCCPrtyWriteCallback7_Callback(epiU8 value);
    void SetCCPrtyWriteCallback8_Callback(epiU16 value);
    void SetCCPrtyWriteCallback9_Callback(epiU32 value);
    void SetCCPrtyWriteCallback10_Callback(epiU64 value);
    void SetCCPrtyWriteCallback11_Callback(epiS8 value);
    void SetCCPrtyWriteCallback12_Callback(epiS16 value);
    void SetCCPrtyWriteCallback13_Callback(epiS32 value);
    void SetCCPrtyWriteCallback14_Callback(epiS64 value);
    void SetCCPrtyWriteCallback15_Callback(const epiString& value);
    void SetCCPrtyWriteCallback16_Callback(const epiWString& value);
    void SetCCPrtyWriteCallback17_Callback(const epiArray<epiS32>& value);
    void SetCCPrtyWriteCallback18_Callback(const epiPtrArray<epiS32>& value);
    void SetCCPrtyWriteCallback19_Callback(const epiArray<epiString>& value);
    void SetCCPrtyWriteCallback20_Callback(const epiPtrArray<epiString>& value);
    void SetCCPrtyWriteCallback21_Callback(const epiVec2f& value);
    void SetCCPrtyWriteCallback22_Callback(const epiVec2d& value);
    void SetCCPrtyWriteCallback23_Callback(const epiVec2s& value);
    void SetCCPrtyWriteCallback24_Callback(const epiVec2u& value);
    void SetCCPrtyWriteCallback25_Callback(const epiVec3f& value);
    void SetCCPrtyWriteCallback26_Callback(const epiVec3d& value);
    void SetCCPrtyWriteCallback27_Callback(const epiVec3s& value);
    void SetCCPrtyWriteCallback28_Callback(const epiVec3u& value);
    void SetCCPrtyWriteCallback29_Callback(const epiVec4f& value);
    void SetCCPrtyWriteCallback30_Callback(const epiVec4d& value);
    void SetCCPrtyWriteCallback31_Callback(const epiVec4s& value);
    void SetCCPrtyWriteCallback32_Callback(const epiVec4u& value);
    void SetCCPrtyWriteCallback33_Callback(const epiMat2x2f& value);
    void SetCCPrtyWriteCallback34_Callback(const epiMat3x3f& value);
    void SetCCPrtyWriteCallback35_Callback(const epiMat4x4f& value);
    void SetCCPrtyWriteCallback36_Callback(const epiComplexf& value);
    void SetCCPrtyWriteCallback37_Callback(const epiComplexd& value);
    void SetCCPrtyWriteCallback38_Callback(const epiRect2f& value);
    void SetCCPrtyWriteCallback39_Callback(const epiRect2d& value);
    void SetCCPrtyWriteCallback40_Callback(const epiRect2s& value);
    void SetCCPrtyWriteCallback41_Callback(const epiRect2u& value);
    void SetCCPrtyWriteCallback42_Callback(const InplaceClass& value);
    void SetCCPrtyWriteCallback43_Callback(InplaceClass* value);

protected:
    epiChar m_CCPrty0{'\0'};
    epiWChar m_CCPrty1{L'\0'};
    epiBool m_CCPrty2{false};
    epiByte m_CCPrty3{0};
    epiFloat m_CCPrty4{0.0f};
    epiDouble m_CCPrty5{0.0};
    epiSize_t m_CCPrty6{0};
    epiU8 m_CCPrty7{0};
    epiU16 m_CCPrty8{0};
    epiU32 m_CCPrty9{0};
    epiU64 m_CCPrty10{0};
    epiS8 m_CCPrty11{0};
    epiS16 m_CCPrty12{0};
    epiS32 m_CCPrty13{0};
    epiS64 m_CCPrty14{0};
    epiString m_CCPrty15{epiDEBUG_ONLY("Empty")};
    epiWString m_CCPrty16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CCPrty17{};
    epiPtrArray<epiS32> m_CCPrty18{};
    epiArray<epiString> m_CCPrty19{};
    epiPtrArray<epiString> m_CCPrty20{};
    epiVec2f m_CCPrty21{};
    epiVec2d m_CCPrty22{};
    epiVec2s m_CCPrty23{};
    epiVec2u m_CCPrty24{};
    epiVec3f m_CCPrty25{};
    epiVec3d m_CCPrty26{};
    epiVec3s m_CCPrty27{};
    epiVec3u m_CCPrty28{};
    epiVec4f m_CCPrty29{};
    epiVec4d m_CCPrty30{};
    epiVec4s m_CCPrty31{};
    epiVec4u m_CCPrty32{};
    epiMat2x2f m_CCPrty33{};
    epiMat3x3f m_CCPrty34{};
    epiMat4x4f m_CCPrty35{};
    epiComplexf m_CCPrty36{};
    epiComplexd m_CCPrty37{};
    epiRect2f m_CCPrty38{};
    epiRect2d m_CCPrty39{};
    epiRect2s m_CCPrty40{};
    epiRect2u m_CCPrty41{};
    InplaceClass m_CCPrty42{};
    InplaceClass* m_CCPrty43{nullptr};
    epiChar m_CCPrtyReadCallback0{'\0'};
    epiWChar m_CCPrtyReadCallback1{L'\0'};
    epiBool m_CCPrtyReadCallback2{false};
    epiByte m_CCPrtyReadCallback3{0};
    epiFloat m_CCPrtyReadCallback4{0.0f};
    epiDouble m_CCPrtyReadCallback5{0.0};
    epiSize_t m_CCPrtyReadCallback6{0};
    epiU8 m_CCPrtyReadCallback7{0};
    epiU16 m_CCPrtyReadCallback8{0};
    epiU32 m_CCPrtyReadCallback9{0};
    epiU64 m_CCPrtyReadCallback10{0};
    epiS8 m_CCPrtyReadCallback11{0};
    epiS16 m_CCPrtyReadCallback12{0};
    epiS32 m_CCPrtyReadCallback13{0};
    epiS64 m_CCPrtyReadCallback14{0};
    epiString m_CCPrtyReadCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_CCPrtyReadCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CCPrtyReadCallback17{};
    epiPtrArray<epiS32> m_CCPrtyReadCallback18{};
    epiArray<epiString> m_CCPrtyReadCallback19{};
    epiPtrArray<epiString> m_CCPrtyReadCallback20{};
    epiVec2f m_CCPrtyReadCallback21{};
    epiVec2d m_CCPrtyReadCallback22{};
    epiVec2s m_CCPrtyReadCallback23{};
    epiVec2u m_CCPrtyReadCallback24{};
    epiVec3f m_CCPrtyReadCallback25{};
    epiVec3d m_CCPrtyReadCallback26{};
    epiVec3s m_CCPrtyReadCallback27{};
    epiVec3u m_CCPrtyReadCallback28{};
    epiVec4f m_CCPrtyReadCallback29{};
    epiVec4d m_CCPrtyReadCallback30{};
    epiVec4s m_CCPrtyReadCallback31{};
    epiVec4u m_CCPrtyReadCallback32{};
    epiMat2x2f m_CCPrtyReadCallback33{};
    epiMat3x3f m_CCPrtyReadCallback34{};
    epiMat4x4f m_CCPrtyReadCallback35{};
    epiComplexf m_CCPrtyReadCallback36{};
    epiComplexd m_CCPrtyReadCallback37{};
    epiRect2f m_CCPrtyReadCallback38{};
    epiRect2d m_CCPrtyReadCallback39{};
    epiRect2s m_CCPrtyReadCallback40{};
    epiRect2u m_CCPrtyReadCallback41{};
    InplaceClass m_CCPrtyReadCallback42{};
    InplaceClass* m_CCPrtyReadCallback43{nullptr};
    epiChar m_CCPrtyWriteCallback0{'\0'};
    epiWChar m_CCPrtyWriteCallback1{L'\0'};
    epiBool m_CCPrtyWriteCallback2{false};
    epiByte m_CCPrtyWriteCallback3{0};
    epiFloat m_CCPrtyWriteCallback4{0.0f};
    epiDouble m_CCPrtyWriteCallback5{0.0};
    epiSize_t m_CCPrtyWriteCallback6{0};
    epiU8 m_CCPrtyWriteCallback7{0};
    epiU16 m_CCPrtyWriteCallback8{0};
    epiU32 m_CCPrtyWriteCallback9{0};
    epiU64 m_CCPrtyWriteCallback10{0};
    epiS8 m_CCPrtyWriteCallback11{0};
    epiS16 m_CCPrtyWriteCallback12{0};
    epiS32 m_CCPrtyWriteCallback13{0};
    epiS64 m_CCPrtyWriteCallback14{0};
    epiString m_CCPrtyWriteCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_CCPrtyWriteCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CCPrtyWriteCallback17{};
    epiPtrArray<epiS32> m_CCPrtyWriteCallback18{};
    epiArray<epiString> m_CCPrtyWriteCallback19{};
    epiPtrArray<epiString> m_CCPrtyWriteCallback20{};
    epiVec2f m_CCPrtyWriteCallback21{};
    epiVec2d m_CCPrtyWriteCallback22{};
    epiVec2s m_CCPrtyWriteCallback23{};
    epiVec2u m_CCPrtyWriteCallback24{};
    epiVec3f m_CCPrtyWriteCallback25{};
    epiVec3d m_CCPrtyWriteCallback26{};
    epiVec3s m_CCPrtyWriteCallback27{};
    epiVec3u m_CCPrtyWriteCallback28{};
    epiVec4f m_CCPrtyWriteCallback29{};
    epiVec4d m_CCPrtyWriteCallback30{};
    epiVec4s m_CCPrtyWriteCallback31{};
    epiVec4u m_CCPrtyWriteCallback32{};
    epiMat2x2f m_CCPrtyWriteCallback33{};
    epiMat3x3f m_CCPrtyWriteCallback34{};
    epiMat4x4f m_CCPrtyWriteCallback35{};
    epiComplexf m_CCPrtyWriteCallback36{};
    epiComplexd m_CCPrtyWriteCallback37{};
    epiRect2f m_CCPrtyWriteCallback38{};
    epiRect2d m_CCPrtyWriteCallback39{};
    epiRect2s m_CCPrtyWriteCallback40{};
    epiRect2u m_CCPrtyWriteCallback41{};
    InplaceClass m_CCPrtyWriteCallback42{};
    InplaceClass* m_CCPrtyWriteCallback43{nullptr};

EPI_GENREGION_END(TestClassCC)

public:
    void Reset() override;

    void Foo() override
    {
        printf("foo\n");
    }
};

class TestClassCCC : public TestClassCC, public epiIPropertyChangedHandler
{
EPI_GENREGION_BEGIN(TestClassCCC)

EPI_GENHIDDEN_TestClassCCC()

public:
    constexpr static epiMetaTypeID TypeID{0x7c13a45c};

    enum TestClassCCC_PIDs
    {
        PID_CCCPrty0 = 0x4ce69802,
        PID_CCCPrty1 = 0x3be1a894,
        PID_CCCPrty2 = 0xa2e8f92e,
        PID_CCCPrty3 = 0xd5efc9b8,
        PID_CCCPrty4 = 0x4b8b5c1b,
        PID_CCCPrty5 = 0x3c8c6c8d,
        PID_CCCPrty6 = 0xa5853d37,
        PID_CCCPrty7 = 0xd2820da1,
        PID_CCCPrty8 = 0x423d1030,
        PID_CCCPrty9 = 0x353a20a6,
        PID_CCCPrty10 = 0x38269d4,
        PID_CCCPrty11 = 0x74855942,
        PID_CCCPrty12 = 0xed8c08f8,
        PID_CCCPrty13 = 0x9a8b386e,
        PID_CCCPrty14 = 0x4efadcd,
        PID_CCCPrty15 = 0x73e89d5b,
        PID_CCCPrty16 = 0xeae1cce1,
        PID_CCCPrty17 = 0x9de6fc77,
        PID_CCCPrty18 = 0xd59e1e6,
        PID_CCCPrty19 = 0x7a5ed170,
        PID_CCCPrty20 = 0x28af3a17,
        PID_CCCPrty21 = 0x5fa80a81,
        PID_CCCPrty22 = 0xc6a15b3b,
        PID_CCCPrty23 = 0xb1a66bad,
        PID_CCCPrty24 = 0x2fc2fe0e,
        PID_CCCPrty25 = 0x58c5ce98,
        PID_CCCPrty26 = 0xc1cc9f22,
        PID_CCCPrty27 = 0xb6cbafb4,
        PID_CCCPrty28 = 0x2674b225,
        PID_CCCPrty29 = 0x517382b3,
        PID_CCCPrty30 = 0x31b40b56,
        PID_CCCPrty31 = 0x46b33bc0,
        PID_CCCPrty32 = 0xdfba6a7a,
        PID_CCCPrty33 = 0xa8bd5aec,
        PID_CCCPrty34 = 0x36d9cf4f,
        PID_CCCPrty35 = 0x41deffd9,
        PID_CCCPrty36 = 0xd8d7ae63,
        PID_CCCPrty37 = 0xafd09ef5,
        PID_CCCPrty38 = 0x3f6f8364,
        PID_CCCPrty39 = 0x4868b3f2,
        PID_CCCPrty40 = 0x7ef59d91,
        PID_CCCPrty41 = 0x9f2ad07,
        PID_CCCPrty42 = 0x90fbfcbd,
        PID_CCCPrty43 = 0xe7fccc2b,
        PID_CCCPrtyVirtual0 = 0x35e720f2,
        PID_CCCPrtyVirtual1 = 0x42e01064,
        PID_CCCPrtyVirtual2 = 0xdbe941de,
        PID_CCCPrtyVirtual3 = 0xacee7148,
        PID_CCCPrtyVirtual4 = 0x328ae4eb,
        PID_CCCPrtyVirtual5 = 0x458dd47d,
        PID_CCCPrtyVirtual6 = 0xdc8485c7,
        PID_CCCPrtyVirtual7 = 0xab83b551,
        PID_CCCPrtyVirtual8 = 0x3b3ca8c0,
        PID_CCCPrtyVirtual9 = 0x4c3b9856,
        PID_CCCPrtyVirtual10 = 0xbe469a70,
        PID_CCCPrtyVirtual11 = 0xc941aae6,
        PID_CCCPrtyVirtual12 = 0x5048fb5c,
        PID_CCCPrtyVirtual13 = 0x274fcbca,
        PID_CCCPrtyVirtual14 = 0xb92b5e69,
        PID_CCCPrtyVirtual15 = 0xce2c6eff,
        PID_CCCPrtyVirtual16 = 0x57253f45,
        PID_CCCPrtyVirtual17 = 0x20220fd3,
        PID_CCCPrtyVirtual18 = 0xb09d1242,
        PID_CCCPrtyVirtual19 = 0xc79a22d4,
        PID_CCCPrtyVirtual20 = 0x956bc9b3,
        PID_CCCPrtyVirtual21 = 0xe26cf925,
        PID_CCCPrtyVirtual22 = 0x7b65a89f,
        PID_CCCPrtyVirtual23 = 0xc629809,
        PID_CCCPrtyVirtual24 = 0x92060daa,
        PID_CCCPrtyVirtual25 = 0xe5013d3c,
        PID_CCCPrtyVirtual26 = 0x7c086c86,
        PID_CCCPrtyVirtual27 = 0xb0f5c10,
        PID_CCCPrtyVirtual28 = 0x9bb04181,
        PID_CCCPrtyVirtual29 = 0xecb77117,
        PID_CCCPrtyVirtual30 = 0x8c70f8f2,
        PID_CCCPrtyVirtual31 = 0xfb77c864,
        PID_CCCPrtyVirtual32 = 0x627e99de,
        PID_CCCPrtyVirtual33 = 0x1579a948,
        PID_CCCPrtyVirtual34 = 0x8b1d3ceb,
        PID_CCCPrtyVirtual35 = 0xfc1a0c7d,
        PID_CCCPrtyVirtual36 = 0x65135dc7,
        PID_CCCPrtyVirtual37 = 0x12146d51,
        PID_CCCPrtyVirtual38 = 0x82ab70c0,
        PID_CCCPrtyVirtual39 = 0xf5ac4056,
        PID_CCCPrtyVirtual40 = 0xc3316e35,
        PID_CCCPrtyVirtual41 = 0xb4365ea3,
        PID_CCCPrtyVirtual42 = 0x2d3f0f19,
        PID_CCCPrtyVirtual43 = 0x5a383f8f,
        PID_CCCPrtyReadCallback0 = 0x233f699e,
        PID_CCCPrtyReadCallback1 = 0x54385908,
        PID_CCCPrtyReadCallback2 = 0xcd3108b2,
        PID_CCCPrtyReadCallback3 = 0xba363824,
        PID_CCCPrtyReadCallback4 = 0x2452ad87,
        PID_CCCPrtyReadCallback5 = 0x53559d11,
        PID_CCCPrtyReadCallback6 = 0xca5cccab,
        PID_CCCPrtyReadCallback7 = 0xbd5bfc3d,
        PID_CCCPrtyReadCallback8 = 0x2de4e1ac,
        PID_CCCPrtyReadCallback9 = 0x5ae3d13a,
        PID_CCCPrtyReadCallback10 = 0xfa546f4a,
        PID_CCCPrtyReadCallback11 = 0x8d535fdc,
        PID_CCCPrtyReadCallback12 = 0x145a0e66,
        PID_CCCPrtyReadCallback13 = 0x635d3ef0,
        PID_CCCPrtyReadCallback14 = 0xfd39ab53,
        PID_CCCPrtyReadCallback15 = 0x8a3e9bc5,
        PID_CCCPrtyReadCallback16 = 0x1337ca7f,
        PID_CCCPrtyReadCallback17 = 0x6430fae9,
        PID_CCCPrtyReadCallback18 = 0xf48fe778,
        PID_CCCPrtyReadCallback19 = 0x8388d7ee,
        PID_CCCPrtyReadCallback20 = 0xd1793c89,
        PID_CCCPrtyReadCallback21 = 0xa67e0c1f,
        PID_CCCPrtyReadCallback22 = 0x3f775da5,
        PID_CCCPrtyReadCallback23 = 0x48706d33,
        PID_CCCPrtyReadCallback24 = 0xd614f890,
        PID_CCCPrtyReadCallback25 = 0xa113c806,
        PID_CCCPrtyReadCallback26 = 0x381a99bc,
        PID_CCCPrtyReadCallback27 = 0x4f1da92a,
        PID_CCCPrtyReadCallback28 = 0xdfa2b4bb,
        PID_CCCPrtyReadCallback29 = 0xa8a5842d,
        PID_CCCPrtyReadCallback30 = 0xc8620dc8,
        PID_CCCPrtyReadCallback31 = 0xbf653d5e,
        PID_CCCPrtyReadCallback32 = 0x266c6ce4,
        PID_CCCPrtyReadCallback33 = 0x516b5c72,
        PID_CCCPrtyReadCallback34 = 0xcf0fc9d1,
        PID_CCCPrtyReadCallback35 = 0xb808f947,
        PID_CCCPrtyReadCallback36 = 0x2101a8fd,
        PID_CCCPrtyReadCallback37 = 0x5606986b,
        PID_CCCPrtyReadCallback38 = 0xc6b985fa,
        PID_CCCPrtyReadCallback39 = 0xb1beb56c,
        PID_CCCPrtyReadCallback40 = 0x87239b0f,
        PID_CCCPrtyReadCallback41 = 0xf024ab99,
        PID_CCCPrtyReadCallback42 = 0x692dfa23,
        PID_CCCPrtyReadCallback43 = 0x1e2acab5,
        PID_CCCPrtyWriteCallback0 = 0xf3dce8be,
        PID_CCCPrtyWriteCallback1 = 0x84dbd828,
        PID_CCCPrtyWriteCallback2 = 0x1dd28992,
        PID_CCCPrtyWriteCallback3 = 0x6ad5b904,
        PID_CCCPrtyWriteCallback4 = 0xf4b12ca7,
        PID_CCCPrtyWriteCallback5 = 0x83b61c31,
        PID_CCCPrtyWriteCallback6 = 0x1abf4d8b,
        PID_CCCPrtyWriteCallback7 = 0x6db87d1d,
        PID_CCCPrtyWriteCallback8 = 0xfd07608c,
        PID_CCCPrtyWriteCallback9 = 0x8a00501a,
        PID_CCCPrtyWriteCallback10 = 0xc1eaac03,
        PID_CCCPrtyWriteCallback11 = 0xb6ed9c95,
        PID_CCCPrtyWriteCallback12 = 0x2fe4cd2f,
        PID_CCCPrtyWriteCallback13 = 0x58e3fdb9,
        PID_CCCPrtyWriteCallback14 = 0xc687681a,
        PID_CCCPrtyWriteCallback15 = 0xb180588c,
        PID_CCCPrtyWriteCallback16 = 0x28890936,
        PID_CCCPrtyWriteCallback17 = 0x5f8e39a0,
        PID_CCCPrtyWriteCallback18 = 0xcf312431,
        PID_CCCPrtyWriteCallback19 = 0xb83614a7,
        PID_CCCPrtyWriteCallback20 = 0xeac7ffc0,
        PID_CCCPrtyWriteCallback21 = 0x9dc0cf56,
        PID_CCCPrtyWriteCallback22 = 0x4c99eec,
        PID_CCCPrtyWriteCallback23 = 0x73ceae7a,
        PID_CCCPrtyWriteCallback24 = 0xedaa3bd9,
        PID_CCCPrtyWriteCallback25 = 0x9aad0b4f,
        PID_CCCPrtyWriteCallback26 = 0x3a45af5,
        PID_CCCPrtyWriteCallback27 = 0x74a36a63,
        PID_CCCPrtyWriteCallback28 = 0xe41c77f2,
        PID_CCCPrtyWriteCallback29 = 0x931b4764,
        PID_CCCPrtyWriteCallback30 = 0xf3dcce81,
        PID_CCCPrtyWriteCallback31 = 0x84dbfe17,
        PID_CCCPrtyWriteCallback32 = 0x1dd2afad,
        PID_CCCPrtyWriteCallback33 = 0x6ad59f3b,
        PID_CCCPrtyWriteCallback34 = 0xf4b10a98,
        PID_CCCPrtyWriteCallback35 = 0x83b63a0e,
        PID_CCCPrtyWriteCallback36 = 0x1abf6bb4,
        PID_CCCPrtyWriteCallback37 = 0x6db85b22,
        PID_CCCPrtyWriteCallback38 = 0xfd0746b3,
        PID_CCCPrtyWriteCallback39 = 0x8a007625,
        PID_CCCPrtyWriteCallback40 = 0xbc9d5846,
        PID_CCCPrtyWriteCallback41 = 0xcb9a68d0,
        PID_CCCPrtyWriteCallback42 = 0x5293396a,
        PID_CCCPrtyWriteCallback43 = 0x259409fc,
        PID_COUNT = 176
    };

protected:
    epiChar GetCCCPrtyVirtual0_Callback() const;
    void SetCCCPrtyVirtual0_Callback(epiChar value);
    epiWChar GetCCCPrtyVirtual1_Callback() const;
    void SetCCCPrtyVirtual1_Callback(epiWChar value);
    epiBool GetCCCPrtyVirtual2_Callback() const;
    void SetCCCPrtyVirtual2_Callback(epiBool value);
    epiByte GetCCCPrtyVirtual3_Callback() const;
    void SetCCCPrtyVirtual3_Callback(epiByte value);
    epiFloat GetCCCPrtyVirtual4_Callback() const;
    void SetCCCPrtyVirtual4_Callback(epiFloat value);
    epiDouble GetCCCPrtyVirtual5_Callback() const;
    void SetCCCPrtyVirtual5_Callback(epiDouble value);
    epiSize_t GetCCCPrtyVirtual6_Callback() const;
    void SetCCCPrtyVirtual6_Callback(epiSize_t value);
    epiU8 GetCCCPrtyVirtual7_Callback() const;
    void SetCCCPrtyVirtual7_Callback(epiU8 value);
    epiU16 GetCCCPrtyVirtual8_Callback() const;
    void SetCCCPrtyVirtual8_Callback(epiU16 value);
    epiU32 GetCCCPrtyVirtual9_Callback() const;
    void SetCCCPrtyVirtual9_Callback(epiU32 value);
    epiU64 GetCCCPrtyVirtual10_Callback() const;
    void SetCCCPrtyVirtual10_Callback(epiU64 value);
    epiS8 GetCCCPrtyVirtual11_Callback() const;
    void SetCCCPrtyVirtual11_Callback(epiS8 value);
    epiS16 GetCCCPrtyVirtual12_Callback() const;
    void SetCCCPrtyVirtual12_Callback(epiS16 value);
    epiS32 GetCCCPrtyVirtual13_Callback() const;
    void SetCCCPrtyVirtual13_Callback(epiS32 value);
    epiS64 GetCCCPrtyVirtual14_Callback() const;
    void SetCCCPrtyVirtual14_Callback(epiS64 value);
    const epiString& GetCCCPrtyVirtual15_Callback() const;
    void SetCCCPrtyVirtual15_Callback(const epiString& value);
    const epiWString& GetCCCPrtyVirtual16_Callback() const;
    void SetCCCPrtyVirtual16_Callback(const epiWString& value);
    const epiArray<epiS32>& GetCCCPrtyVirtual17_Callback() const;
    void SetCCCPrtyVirtual17_Callback(const epiArray<epiS32>& value);
    const epiPtrArray<epiS32>& GetCCCPrtyVirtual18_Callback() const;
    void SetCCCPrtyVirtual18_Callback(const epiPtrArray<epiS32>& value);
    const epiArray<epiString>& GetCCCPrtyVirtual19_Callback() const;
    void SetCCCPrtyVirtual19_Callback(const epiArray<epiString>& value);
    const epiPtrArray<epiString>& GetCCCPrtyVirtual20_Callback() const;
    void SetCCCPrtyVirtual20_Callback(const epiPtrArray<epiString>& value);
    const epiVec2f& GetCCCPrtyVirtual21_Callback() const;
    void SetCCCPrtyVirtual21_Callback(const epiVec2f& value);
    const epiVec2d& GetCCCPrtyVirtual22_Callback() const;
    void SetCCCPrtyVirtual22_Callback(const epiVec2d& value);
    const epiVec2s& GetCCCPrtyVirtual23_Callback() const;
    void SetCCCPrtyVirtual23_Callback(const epiVec2s& value);
    const epiVec2u& GetCCCPrtyVirtual24_Callback() const;
    void SetCCCPrtyVirtual24_Callback(const epiVec2u& value);
    const epiVec3f& GetCCCPrtyVirtual25_Callback() const;
    void SetCCCPrtyVirtual25_Callback(const epiVec3f& value);
    const epiVec3d& GetCCCPrtyVirtual26_Callback() const;
    void SetCCCPrtyVirtual26_Callback(const epiVec3d& value);
    const epiVec3s& GetCCCPrtyVirtual27_Callback() const;
    void SetCCCPrtyVirtual27_Callback(const epiVec3s& value);
    const epiVec3u& GetCCCPrtyVirtual28_Callback() const;
    void SetCCCPrtyVirtual28_Callback(const epiVec3u& value);
    const epiVec4f& GetCCCPrtyVirtual29_Callback() const;
    void SetCCCPrtyVirtual29_Callback(const epiVec4f& value);
    const epiVec4d& GetCCCPrtyVirtual30_Callback() const;
    void SetCCCPrtyVirtual30_Callback(const epiVec4d& value);
    const epiVec4s& GetCCCPrtyVirtual31_Callback() const;
    void SetCCCPrtyVirtual31_Callback(const epiVec4s& value);
    const epiVec4u& GetCCCPrtyVirtual32_Callback() const;
    void SetCCCPrtyVirtual32_Callback(const epiVec4u& value);
    const epiMat2x2f& GetCCCPrtyVirtual33_Callback() const;
    void SetCCCPrtyVirtual33_Callback(const epiMat2x2f& value);
    const epiMat3x3f& GetCCCPrtyVirtual34_Callback() const;
    void SetCCCPrtyVirtual34_Callback(const epiMat3x3f& value);
    const epiMat4x4f& GetCCCPrtyVirtual35_Callback() const;
    void SetCCCPrtyVirtual35_Callback(const epiMat4x4f& value);
    const epiComplexf& GetCCCPrtyVirtual36_Callback() const;
    void SetCCCPrtyVirtual36_Callback(const epiComplexf& value);
    const epiComplexd& GetCCCPrtyVirtual37_Callback() const;
    void SetCCCPrtyVirtual37_Callback(const epiComplexd& value);
    const epiRect2f& GetCCCPrtyVirtual38_Callback() const;
    void SetCCCPrtyVirtual38_Callback(const epiRect2f& value);
    const epiRect2d& GetCCCPrtyVirtual39_Callback() const;
    void SetCCCPrtyVirtual39_Callback(const epiRect2d& value);
    const epiRect2s& GetCCCPrtyVirtual40_Callback() const;
    void SetCCCPrtyVirtual40_Callback(const epiRect2s& value);
    const epiRect2u& GetCCCPrtyVirtual41_Callback() const;
    void SetCCCPrtyVirtual41_Callback(const epiRect2u& value);
    const InplaceClass& GetCCCPrtyVirtual42_Callback() const;
    void SetCCCPrtyVirtual42_Callback(const InplaceClass& value);
    const InplaceClass* GetCCCPrtyVirtual43_Callback() const;
    void SetCCCPrtyVirtual43_Callback(InplaceClass* value);
    epiChar GetCCCPrtyReadCallback0_Callback() const;
    epiWChar GetCCCPrtyReadCallback1_Callback() const;
    epiBool GetCCCPrtyReadCallback2_Callback() const;
    epiByte GetCCCPrtyReadCallback3_Callback() const;
    epiFloat GetCCCPrtyReadCallback4_Callback() const;
    epiDouble GetCCCPrtyReadCallback5_Callback() const;
    epiSize_t GetCCCPrtyReadCallback6_Callback() const;
    epiU8 GetCCCPrtyReadCallback7_Callback() const;
    epiU16 GetCCCPrtyReadCallback8_Callback() const;
    epiU32 GetCCCPrtyReadCallback9_Callback() const;
    epiU64 GetCCCPrtyReadCallback10_Callback() const;
    epiS8 GetCCCPrtyReadCallback11_Callback() const;
    epiS16 GetCCCPrtyReadCallback12_Callback() const;
    epiS32 GetCCCPrtyReadCallback13_Callback() const;
    epiS64 GetCCCPrtyReadCallback14_Callback() const;
    const epiString& GetCCCPrtyReadCallback15_Callback() const;
    const epiWString& GetCCCPrtyReadCallback16_Callback() const;
    const epiArray<epiS32>& GetCCCPrtyReadCallback17_Callback() const;
    const epiPtrArray<epiS32>& GetCCCPrtyReadCallback18_Callback() const;
    const epiArray<epiString>& GetCCCPrtyReadCallback19_Callback() const;
    const epiPtrArray<epiString>& GetCCCPrtyReadCallback20_Callback() const;
    const epiVec2f& GetCCCPrtyReadCallback21_Callback() const;
    const epiVec2d& GetCCCPrtyReadCallback22_Callback() const;
    const epiVec2s& GetCCCPrtyReadCallback23_Callback() const;
    const epiVec2u& GetCCCPrtyReadCallback24_Callback() const;
    const epiVec3f& GetCCCPrtyReadCallback25_Callback() const;
    const epiVec3d& GetCCCPrtyReadCallback26_Callback() const;
    const epiVec3s& GetCCCPrtyReadCallback27_Callback() const;
    const epiVec3u& GetCCCPrtyReadCallback28_Callback() const;
    const epiVec4f& GetCCCPrtyReadCallback29_Callback() const;
    const epiVec4d& GetCCCPrtyReadCallback30_Callback() const;
    const epiVec4s& GetCCCPrtyReadCallback31_Callback() const;
    const epiVec4u& GetCCCPrtyReadCallback32_Callback() const;
    const epiMat2x2f& GetCCCPrtyReadCallback33_Callback() const;
    const epiMat3x3f& GetCCCPrtyReadCallback34_Callback() const;
    const epiMat4x4f& GetCCCPrtyReadCallback35_Callback() const;
    const epiComplexf& GetCCCPrtyReadCallback36_Callback() const;
    const epiComplexd& GetCCCPrtyReadCallback37_Callback() const;
    const epiRect2f& GetCCCPrtyReadCallback38_Callback() const;
    const epiRect2d& GetCCCPrtyReadCallback39_Callback() const;
    const epiRect2s& GetCCCPrtyReadCallback40_Callback() const;
    const epiRect2u& GetCCCPrtyReadCallback41_Callback() const;
    const InplaceClass& GetCCCPrtyReadCallback42_Callback() const;
    const InplaceClass* GetCCCPrtyReadCallback43_Callback() const;
    void SetCCCPrtyWriteCallback0_Callback(epiChar value);
    void SetCCCPrtyWriteCallback1_Callback(epiWChar value);
    void SetCCCPrtyWriteCallback2_Callback(epiBool value);
    void SetCCCPrtyWriteCallback3_Callback(epiByte value);
    void SetCCCPrtyWriteCallback4_Callback(epiFloat value);
    void SetCCCPrtyWriteCallback5_Callback(epiDouble value);
    void SetCCCPrtyWriteCallback6_Callback(epiSize_t value);
    void SetCCCPrtyWriteCallback7_Callback(epiU8 value);
    void SetCCCPrtyWriteCallback8_Callback(epiU16 value);
    void SetCCCPrtyWriteCallback9_Callback(epiU32 value);
    void SetCCCPrtyWriteCallback10_Callback(epiU64 value);
    void SetCCCPrtyWriteCallback11_Callback(epiS8 value);
    void SetCCCPrtyWriteCallback12_Callback(epiS16 value);
    void SetCCCPrtyWriteCallback13_Callback(epiS32 value);
    void SetCCCPrtyWriteCallback14_Callback(epiS64 value);
    void SetCCCPrtyWriteCallback15_Callback(const epiString& value);
    void SetCCCPrtyWriteCallback16_Callback(const epiWString& value);
    void SetCCCPrtyWriteCallback17_Callback(const epiArray<epiS32>& value);
    void SetCCCPrtyWriteCallback18_Callback(const epiPtrArray<epiS32>& value);
    void SetCCCPrtyWriteCallback19_Callback(const epiArray<epiString>& value);
    void SetCCCPrtyWriteCallback20_Callback(const epiPtrArray<epiString>& value);
    void SetCCCPrtyWriteCallback21_Callback(const epiVec2f& value);
    void SetCCCPrtyWriteCallback22_Callback(const epiVec2d& value);
    void SetCCCPrtyWriteCallback23_Callback(const epiVec2s& value);
    void SetCCCPrtyWriteCallback24_Callback(const epiVec2u& value);
    void SetCCCPrtyWriteCallback25_Callback(const epiVec3f& value);
    void SetCCCPrtyWriteCallback26_Callback(const epiVec3d& value);
    void SetCCCPrtyWriteCallback27_Callback(const epiVec3s& value);
    void SetCCCPrtyWriteCallback28_Callback(const epiVec3u& value);
    void SetCCCPrtyWriteCallback29_Callback(const epiVec4f& value);
    void SetCCCPrtyWriteCallback30_Callback(const epiVec4d& value);
    void SetCCCPrtyWriteCallback31_Callback(const epiVec4s& value);
    void SetCCCPrtyWriteCallback32_Callback(const epiVec4u& value);
    void SetCCCPrtyWriteCallback33_Callback(const epiMat2x2f& value);
    void SetCCCPrtyWriteCallback34_Callback(const epiMat3x3f& value);
    void SetCCCPrtyWriteCallback35_Callback(const epiMat4x4f& value);
    void SetCCCPrtyWriteCallback36_Callback(const epiComplexf& value);
    void SetCCCPrtyWriteCallback37_Callback(const epiComplexd& value);
    void SetCCCPrtyWriteCallback38_Callback(const epiRect2f& value);
    void SetCCCPrtyWriteCallback39_Callback(const epiRect2d& value);
    void SetCCCPrtyWriteCallback40_Callback(const epiRect2s& value);
    void SetCCCPrtyWriteCallback41_Callback(const epiRect2u& value);
    void SetCCCPrtyWriteCallback42_Callback(const InplaceClass& value);
    void SetCCCPrtyWriteCallback43_Callback(InplaceClass* value);

protected:
    epiChar m_CCCPrty0{'\0'};
    epiWChar m_CCCPrty1{L'\0'};
    epiBool m_CCCPrty2{false};
    epiByte m_CCCPrty3{0};
    epiFloat m_CCCPrty4{0.0f};
    epiDouble m_CCCPrty5{0.0};
    epiSize_t m_CCCPrty6{0};
    epiU8 m_CCCPrty7{0};
    epiU16 m_CCCPrty8{0};
    epiU32 m_CCCPrty9{0};
    epiU64 m_CCCPrty10{0};
    epiS8 m_CCCPrty11{0};
    epiS16 m_CCCPrty12{0};
    epiS32 m_CCCPrty13{0};
    epiS64 m_CCCPrty14{0};
    epiString m_CCCPrty15{epiDEBUG_ONLY("Empty")};
    epiWString m_CCCPrty16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CCCPrty17{};
    epiPtrArray<epiS32> m_CCCPrty18{};
    epiArray<epiString> m_CCCPrty19{};
    epiPtrArray<epiString> m_CCCPrty20{};
    epiVec2f m_CCCPrty21{};
    epiVec2d m_CCCPrty22{};
    epiVec2s m_CCCPrty23{};
    epiVec2u m_CCCPrty24{};
    epiVec3f m_CCCPrty25{};
    epiVec3d m_CCCPrty26{};
    epiVec3s m_CCCPrty27{};
    epiVec3u m_CCCPrty28{};
    epiVec4f m_CCCPrty29{};
    epiVec4d m_CCCPrty30{};
    epiVec4s m_CCCPrty31{};
    epiVec4u m_CCCPrty32{};
    epiMat2x2f m_CCCPrty33{};
    epiMat3x3f m_CCCPrty34{};
    epiMat4x4f m_CCCPrty35{};
    epiComplexf m_CCCPrty36{};
    epiComplexd m_CCCPrty37{};
    epiRect2f m_CCCPrty38{};
    epiRect2d m_CCCPrty39{};
    epiRect2s m_CCCPrty40{};
    epiRect2u m_CCCPrty41{};
    InplaceClass m_CCCPrty42{};
    InplaceClass* m_CCCPrty43{nullptr};
    epiChar m_CCCPrtyReadCallback0{'\0'};
    epiWChar m_CCCPrtyReadCallback1{L'\0'};
    epiBool m_CCCPrtyReadCallback2{false};
    epiByte m_CCCPrtyReadCallback3{0};
    epiFloat m_CCCPrtyReadCallback4{0.0f};
    epiDouble m_CCCPrtyReadCallback5{0.0};
    epiSize_t m_CCCPrtyReadCallback6{0};
    epiU8 m_CCCPrtyReadCallback7{0};
    epiU16 m_CCCPrtyReadCallback8{0};
    epiU32 m_CCCPrtyReadCallback9{0};
    epiU64 m_CCCPrtyReadCallback10{0};
    epiS8 m_CCCPrtyReadCallback11{0};
    epiS16 m_CCCPrtyReadCallback12{0};
    epiS32 m_CCCPrtyReadCallback13{0};
    epiS64 m_CCCPrtyReadCallback14{0};
    epiString m_CCCPrtyReadCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_CCCPrtyReadCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CCCPrtyReadCallback17{};
    epiPtrArray<epiS32> m_CCCPrtyReadCallback18{};
    epiArray<epiString> m_CCCPrtyReadCallback19{};
    epiPtrArray<epiString> m_CCCPrtyReadCallback20{};
    epiVec2f m_CCCPrtyReadCallback21{};
    epiVec2d m_CCCPrtyReadCallback22{};
    epiVec2s m_CCCPrtyReadCallback23{};
    epiVec2u m_CCCPrtyReadCallback24{};
    epiVec3f m_CCCPrtyReadCallback25{};
    epiVec3d m_CCCPrtyReadCallback26{};
    epiVec3s m_CCCPrtyReadCallback27{};
    epiVec3u m_CCCPrtyReadCallback28{};
    epiVec4f m_CCCPrtyReadCallback29{};
    epiVec4d m_CCCPrtyReadCallback30{};
    epiVec4s m_CCCPrtyReadCallback31{};
    epiVec4u m_CCCPrtyReadCallback32{};
    epiMat2x2f m_CCCPrtyReadCallback33{};
    epiMat3x3f m_CCCPrtyReadCallback34{};
    epiMat4x4f m_CCCPrtyReadCallback35{};
    epiComplexf m_CCCPrtyReadCallback36{};
    epiComplexd m_CCCPrtyReadCallback37{};
    epiRect2f m_CCCPrtyReadCallback38{};
    epiRect2d m_CCCPrtyReadCallback39{};
    epiRect2s m_CCCPrtyReadCallback40{};
    epiRect2u m_CCCPrtyReadCallback41{};
    InplaceClass m_CCCPrtyReadCallback42{};
    InplaceClass* m_CCCPrtyReadCallback43{nullptr};
    epiChar m_CCCPrtyWriteCallback0{'\0'};
    epiWChar m_CCCPrtyWriteCallback1{L'\0'};
    epiBool m_CCCPrtyWriteCallback2{false};
    epiByte m_CCCPrtyWriteCallback3{0};
    epiFloat m_CCCPrtyWriteCallback4{0.0f};
    epiDouble m_CCCPrtyWriteCallback5{0.0};
    epiSize_t m_CCCPrtyWriteCallback6{0};
    epiU8 m_CCCPrtyWriteCallback7{0};
    epiU16 m_CCCPrtyWriteCallback8{0};
    epiU32 m_CCCPrtyWriteCallback9{0};
    epiU64 m_CCCPrtyWriteCallback10{0};
    epiS8 m_CCCPrtyWriteCallback11{0};
    epiS16 m_CCCPrtyWriteCallback12{0};
    epiS32 m_CCCPrtyWriteCallback13{0};
    epiS64 m_CCCPrtyWriteCallback14{0};
    epiString m_CCCPrtyWriteCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_CCCPrtyWriteCallback16{epiDEBUG_ONLY(L"Empty")};
    epiArray<epiS32> m_CCCPrtyWriteCallback17{};
    epiPtrArray<epiS32> m_CCCPrtyWriteCallback18{};
    epiArray<epiString> m_CCCPrtyWriteCallback19{};
    epiPtrArray<epiString> m_CCCPrtyWriteCallback20{};
    epiVec2f m_CCCPrtyWriteCallback21{};
    epiVec2d m_CCCPrtyWriteCallback22{};
    epiVec2s m_CCCPrtyWriteCallback23{};
    epiVec2u m_CCCPrtyWriteCallback24{};
    epiVec3f m_CCCPrtyWriteCallback25{};
    epiVec3d m_CCCPrtyWriteCallback26{};
    epiVec3s m_CCCPrtyWriteCallback27{};
    epiVec3u m_CCCPrtyWriteCallback28{};
    epiVec4f m_CCCPrtyWriteCallback29{};
    epiVec4d m_CCCPrtyWriteCallback30{};
    epiVec4s m_CCCPrtyWriteCallback31{};
    epiVec4u m_CCCPrtyWriteCallback32{};
    epiMat2x2f m_CCCPrtyWriteCallback33{};
    epiMat3x3f m_CCCPrtyWriteCallback34{};
    epiMat4x4f m_CCCPrtyWriteCallback35{};
    epiComplexf m_CCCPrtyWriteCallback36{};
    epiComplexd m_CCCPrtyWriteCallback37{};
    epiRect2f m_CCCPrtyWriteCallback38{};
    epiRect2d m_CCCPrtyWriteCallback39{};
    epiRect2s m_CCCPrtyWriteCallback40{};
    epiRect2u m_CCCPrtyWriteCallback41{};
    InplaceClass m_CCCPrtyWriteCallback42{};
    InplaceClass* m_CCCPrtyWriteCallback43{nullptr};

EPI_GENREGION_END(TestClassCCC)
public:
    void Reset() override;
};

EPI_NAMESPACE_END()
