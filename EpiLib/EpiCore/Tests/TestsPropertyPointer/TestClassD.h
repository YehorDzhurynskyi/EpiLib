#pragma once

EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClassD.hxx"
EPI_GENREGION_END(include)

#include "TestsPropertyPointer/TestClassB.h"

EPI_NAMESPACE_BEGIN()

#include "TestClassB.h"

class TestClassD : public TestClassB
{
EPI_GENREGION_BEGIN(TestClassD)

EPI_GENHIDDEN_TestClassD()

public:
    constexpr static epiMetaTypeID TypeID{0xaf9e3b9};

    enum TestClassD_PIDs
    {
        PID_DPrty0 = 0x57f27c9a,
        PID_DPrty1 = 0x20f54c0c,
        PID_DPrty2 = 0xb9fc1db6,
        PID_DPrty3 = 0xcefb2d20,
        PID_DPrty4 = 0x509fb883,
        PID_DPrty5 = 0x27988815,
        PID_DPrty6 = 0xbe91d9af,
        PID_DPrty7 = 0xc996e939,
        PID_DPrty8 = 0x5929f4a8,
        PID_DPrty9 = 0x2e2ec43e,
        PID_DPrty10 = 0xfd4d6646,
        PID_DPrty11 = 0x8a4a56d0,
        PID_DPrty12 = 0x1343076a,
        PID_DPrty13 = 0x644437fc,
        PID_DPrty14 = 0xfa20a25f,
        PID_DPrty15 = 0x8d2792c9,
        PID_DPrty16 = 0x142ec373,
        PID_DPrtyVirtual0 = 0x766da0e1,
        PID_DPrtyVirtual1 = 0x16a9077,
        PID_DPrtyVirtual2 = 0x9863c1cd,
        PID_DPrtyVirtual3 = 0xef64f15b,
        PID_DPrtyVirtual4 = 0x710064f8,
        PID_DPrtyVirtual5 = 0x607546e,
        PID_DPrtyVirtual6 = 0x9f0e05d4,
        PID_DPrtyVirtual7 = 0xe8093542,
        PID_DPrtyVirtual8 = 0x78b628d3,
        PID_DPrtyVirtual9 = 0xfb11845,
        PID_DPrtyVirtual10 = 0x3abb512e,
        PID_DPrtyVirtual11 = 0x4dbc61b8,
        PID_DPrtyVirtual12 = 0xd4b53002,
        PID_DPrtyVirtual13 = 0xa3b20094,
        PID_DPrtyVirtual14 = 0x3dd69537,
        PID_DPrtyVirtual15 = 0x4ad1a5a1,
        PID_DPrtyVirtual16 = 0xd3d8f41b,
        PID_DPrtyReadCallback0 = 0xded0b067,
        PID_DPrtyReadCallback1 = 0xa9d780f1,
        PID_DPrtyReadCallback2 = 0x30ded14b,
        PID_DPrtyReadCallback3 = 0x47d9e1dd,
        PID_DPrtyReadCallback4 = 0xd9bd747e,
        PID_DPrtyReadCallback5 = 0xaeba44e8,
        PID_DPrtyReadCallback6 = 0x37b31552,
        PID_DPrtyReadCallback7 = 0x40b425c4,
        PID_DPrtyReadCallback8 = 0xd00b3855,
        PID_DPrtyReadCallback9 = 0xa70c08c3,
        PID_DPrtyReadCallback10 = 0x3ec8ca2b,
        PID_DPrtyReadCallback11 = 0x49cffabd,
        PID_DPrtyReadCallback12 = 0xd0c6ab07,
        PID_DPrtyReadCallback13 = 0xa7c19b91,
        PID_DPrtyReadCallback14 = 0x39a50e32,
        PID_DPrtyReadCallback15 = 0x4ea23ea4,
        PID_DPrtyReadCallback16 = 0xd7ab6f1e,
        PID_DPrtyWriteCallback0 = 0x37404ddf,
        PID_DPrtyWriteCallback1 = 0x40477d49,
        PID_DPrtyWriteCallback2 = 0xd94e2cf3,
        PID_DPrtyWriteCallback3 = 0xae491c65,
        PID_DPrtyWriteCallback4 = 0x302d89c6,
        PID_DPrtyWriteCallback5 = 0x472ab950,
        PID_DPrtyWriteCallback6 = 0xde23e8ea,
        PID_DPrtyWriteCallback7 = 0xa924d87c,
        PID_DPrtyWriteCallback8 = 0x399bc5ed,
        PID_DPrtyWriteCallback9 = 0x4e9cf57b,
        PID_DPrtyWriteCallback10 = 0xfb9b6168,
        PID_DPrtyWriteCallback11 = 0x8c9c51fe,
        PID_DPrtyWriteCallback12 = 0x15950044,
        PID_DPrtyWriteCallback13 = 0x629230d2,
        PID_DPrtyWriteCallback14 = 0xfcf6a571,
        PID_DPrtyWriteCallback15 = 0x8bf195e7,
        PID_DPrtyWriteCallback16 = 0x12f8c45d,
        PID_COUNT = 68
    };

protected:
    epiChar GetDPrtyVirtual0_Callback() const;
    void SetDPrtyVirtual0_Callback(epiChar value);
    epiWChar GetDPrtyVirtual1_Callback() const;
    void SetDPrtyVirtual1_Callback(epiWChar value);
    epiBool GetDPrtyVirtual2_Callback() const;
    void SetDPrtyVirtual2_Callback(epiBool value);
    epiByte GetDPrtyVirtual3_Callback() const;
    void SetDPrtyVirtual3_Callback(epiByte value);
    epiFloat GetDPrtyVirtual4_Callback() const;
    void SetDPrtyVirtual4_Callback(epiFloat value);
    epiDouble GetDPrtyVirtual5_Callback() const;
    void SetDPrtyVirtual5_Callback(epiDouble value);
    epiSize_t GetDPrtyVirtual6_Callback() const;
    void SetDPrtyVirtual6_Callback(epiSize_t value);
    epiU8 GetDPrtyVirtual7_Callback() const;
    void SetDPrtyVirtual7_Callback(epiU8 value);
    epiU16 GetDPrtyVirtual8_Callback() const;
    void SetDPrtyVirtual8_Callback(epiU16 value);
    epiU32 GetDPrtyVirtual9_Callback() const;
    void SetDPrtyVirtual9_Callback(epiU32 value);
    epiU64 GetDPrtyVirtual10_Callback() const;
    void SetDPrtyVirtual10_Callback(epiU64 value);
    epiS8 GetDPrtyVirtual11_Callback() const;
    void SetDPrtyVirtual11_Callback(epiS8 value);
    epiS16 GetDPrtyVirtual12_Callback() const;
    void SetDPrtyVirtual12_Callback(epiS16 value);
    epiS32 GetDPrtyVirtual13_Callback() const;
    void SetDPrtyVirtual13_Callback(epiS32 value);
    epiS64 GetDPrtyVirtual14_Callback() const;
    void SetDPrtyVirtual14_Callback(epiS64 value);
    const epiString& GetDPrtyVirtual15_Callback() const;
    void SetDPrtyVirtual15_Callback(const epiString& value);
    const epiWString& GetDPrtyVirtual16_Callback() const;
    void SetDPrtyVirtual16_Callback(const epiWString& value);
    epiChar GetDPrtyReadCallback0_Callback() const;
    epiWChar GetDPrtyReadCallback1_Callback() const;
    epiBool GetDPrtyReadCallback2_Callback() const;
    epiByte GetDPrtyReadCallback3_Callback() const;
    epiFloat GetDPrtyReadCallback4_Callback() const;
    epiDouble GetDPrtyReadCallback5_Callback() const;
    epiSize_t GetDPrtyReadCallback6_Callback() const;
    epiU8 GetDPrtyReadCallback7_Callback() const;
    epiU16 GetDPrtyReadCallback8_Callback() const;
    epiU32 GetDPrtyReadCallback9_Callback() const;
    epiU64 GetDPrtyReadCallback10_Callback() const;
    epiS8 GetDPrtyReadCallback11_Callback() const;
    epiS16 GetDPrtyReadCallback12_Callback() const;
    epiS32 GetDPrtyReadCallback13_Callback() const;
    epiS64 GetDPrtyReadCallback14_Callback() const;
    const epiString& GetDPrtyReadCallback15_Callback() const;
    const epiWString& GetDPrtyReadCallback16_Callback() const;
    void SetDPrtyWriteCallback0_Callback(epiChar value);
    void SetDPrtyWriteCallback1_Callback(epiWChar value);
    void SetDPrtyWriteCallback2_Callback(epiBool value);
    void SetDPrtyWriteCallback3_Callback(epiByte value);
    void SetDPrtyWriteCallback4_Callback(epiFloat value);
    void SetDPrtyWriteCallback5_Callback(epiDouble value);
    void SetDPrtyWriteCallback6_Callback(epiSize_t value);
    void SetDPrtyWriteCallback7_Callback(epiU8 value);
    void SetDPrtyWriteCallback8_Callback(epiU16 value);
    void SetDPrtyWriteCallback9_Callback(epiU32 value);
    void SetDPrtyWriteCallback10_Callback(epiU64 value);
    void SetDPrtyWriteCallback11_Callback(epiS8 value);
    void SetDPrtyWriteCallback12_Callback(epiS16 value);
    void SetDPrtyWriteCallback13_Callback(epiS32 value);
    void SetDPrtyWriteCallback14_Callback(epiS64 value);
    void SetDPrtyWriteCallback15_Callback(const epiString& value);
    void SetDPrtyWriteCallback16_Callback(const epiWString& value);

protected:
    epiChar m_DPrty0{'\0'};
    epiWChar m_DPrty1{L'\0'};
    epiBool m_DPrty2{false};
    epiByte m_DPrty3{0};
    epiFloat m_DPrty4{0.0f};
    epiDouble m_DPrty5{0.0};
    epiSize_t m_DPrty6{0};
    epiU8 m_DPrty7{0};
    epiU16 m_DPrty8{0};
    epiU32 m_DPrty9{0};
    epiU64 m_DPrty10{0};
    epiS8 m_DPrty11{0};
    epiS16 m_DPrty12{0};
    epiS32 m_DPrty13{0};
    epiS64 m_DPrty14{0};
    epiString m_DPrty15{epiDEBUG_ONLY("Empty")};
    epiWString m_DPrty16{epiDEBUG_ONLY(L"Empty")};
    epiChar m_DPrtyReadCallback0{'\0'};
    epiWChar m_DPrtyReadCallback1{L'\0'};
    epiBool m_DPrtyReadCallback2{false};
    epiByte m_DPrtyReadCallback3{0};
    epiFloat m_DPrtyReadCallback4{0.0f};
    epiDouble m_DPrtyReadCallback5{0.0};
    epiSize_t m_DPrtyReadCallback6{0};
    epiU8 m_DPrtyReadCallback7{0};
    epiU16 m_DPrtyReadCallback8{0};
    epiU32 m_DPrtyReadCallback9{0};
    epiU64 m_DPrtyReadCallback10{0};
    epiS8 m_DPrtyReadCallback11{0};
    epiS16 m_DPrtyReadCallback12{0};
    epiS32 m_DPrtyReadCallback13{0};
    epiS64 m_DPrtyReadCallback14{0};
    epiString m_DPrtyReadCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_DPrtyReadCallback16{epiDEBUG_ONLY(L"Empty")};
    epiChar m_DPrtyWriteCallback0{'\0'};
    epiWChar m_DPrtyWriteCallback1{L'\0'};
    epiBool m_DPrtyWriteCallback2{false};
    epiByte m_DPrtyWriteCallback3{0};
    epiFloat m_DPrtyWriteCallback4{0.0f};
    epiDouble m_DPrtyWriteCallback5{0.0};
    epiSize_t m_DPrtyWriteCallback6{0};
    epiU8 m_DPrtyWriteCallback7{0};
    epiU16 m_DPrtyWriteCallback8{0};
    epiU32 m_DPrtyWriteCallback9{0};
    epiU64 m_DPrtyWriteCallback10{0};
    epiS8 m_DPrtyWriteCallback11{0};
    epiS16 m_DPrtyWriteCallback12{0};
    epiS32 m_DPrtyWriteCallback13{0};
    epiS64 m_DPrtyWriteCallback14{0};
    epiString m_DPrtyWriteCallback15{epiDEBUG_ONLY("Empty")};
    epiWString m_DPrtyWriteCallback16{epiDEBUG_ONLY(L"Empty")};

EPI_GENREGION_END(TestClassD)
};

EPI_NAMESPACE_END()
