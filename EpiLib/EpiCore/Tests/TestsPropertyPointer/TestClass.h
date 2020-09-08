#pragma once

EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClass.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

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
        PID_COUNT = 168
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

EPI_GENREGION_END(TestClassA)
};

EPI_NAMESPACE_END()
