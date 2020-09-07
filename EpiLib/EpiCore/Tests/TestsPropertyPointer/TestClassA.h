#pragma once

EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClassA.hxx"
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
        PID_COUNT = 68
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

EPI_GENREGION_END(TestClassA)
};

EPI_NAMESPACE_END()
