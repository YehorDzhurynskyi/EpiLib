#pragma once

EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClassC.hxx"
EPI_GENREGION_END(include)

#include "TestsPropertyPointer/TestClassA.h"

EPI_NAMESPACE_BEGIN()

class TestClassC : public TestClassA
{
EPI_GENREGION_BEGIN(TestClassC)

EPI_GENHIDDEN_TestClassC()

public:
    constexpr static MetaTypeID TypeID{0x949d761a};

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
        PID_COUNT = 68
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

EPI_GENREGION_END(TestClassC)
};

EPI_NAMESPACE_END()
