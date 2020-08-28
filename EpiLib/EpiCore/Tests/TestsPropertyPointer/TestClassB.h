#pragma once

EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClassB.hxx"
EPI_GENREGION_END(include)

#include "TestsPropertyPointer/TestClassA.h"

EPI_NAMESPACE_BEGIN()

class TestClassB : public TestClassA
{
EPI_GENREGION_BEGIN(TestClassB)

EPI_GENHIDDEN_TestClassB()

public:
    constexpr static MetaTypeID TypeID{0xe39a468c};

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
        PID_COUNT = 68
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

EPI_GENREGION_END(TestClassB)
};

EPI_NAMESPACE_END()
