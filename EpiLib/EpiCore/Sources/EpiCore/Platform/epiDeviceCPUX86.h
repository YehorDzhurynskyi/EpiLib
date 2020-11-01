#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/epiDeviceCPUX86.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/Platform/epiDeviceCPUBase.h"

#include <cpuinfo_x86.h>

EPI_NAMESPACE_BEGIN()

enum class epiDeviceCPUX86Microarchitecture : epiS32
{
EPI_GENREGION_BEGIN(epiDeviceCPUX86Microarchitecture)
    Unknown = 0,
    IntelCore = 1,
    IntelPenryn = 2,
    IntelNehalem = 3,
    IntelAtomBonnell = 4,
    IntelWestmere = 5,
    IntelSandybridge = 6,
    IntelIvybridge = 7,
    IntelAtomSilvermont = 8,
    IntelHaswell = 9,
    IntelBroadwell = 10,
    IntelSkyLake = 11,
    IntelAtomGoldmont = 12,
    IntelKabyLake = 13,
    IntelCoffeeLake = 14,
    IntelWhiskeyLake = 15,
    IntelCannonLake = 16,
    IntelIceLake = 17,
    IntelTigerLake = 18,
    IntelSapphireRapids = 19,
    AMDHammer = 20,
    AMDK10 = 21,
    AMDBobcat = 22,
    AMDBulldozer = 23,
    AMDJaguar = 24,
    AMDZen = 25
EPI_GENREGION_END(epiDeviceCPUX86Microarchitecture)
};

enum class epiDeviceCPUX86CacheType : epiS32
{
EPI_GENREGION_BEGIN(epiDeviceCPUX86CacheType)
    Null = 0,
    Data = 1,
    Instruction = 2,
    Unified = 3,
    TLB = 4,
    DTLB = 5,
    STLB = 6,
    Prefetch = 7
EPI_GENREGION_END(epiDeviceCPUX86CacheType)
};

class epiDeviceCPUX86CacheLevelInfo : public Object
{
EPI_GENREGION_BEGIN(epiDeviceCPUX86CacheLevelInfo)

EPI_GENHIDDEN_epiDeviceCPUX86CacheLevelInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xb1f18322};

    enum epiDeviceCPUX86CacheLevelInfo_PIDs
    {
        PID_Level = 0x5b2be317,
        PID_CacheType = 0x1fd48f30,
        PID_CacheSize = 0x64cafc73,
        PID_Ways = 0x97aab29,
        PID_LineSize = 0x10a4c3a2,
        PID_TLBEntries = 0x7f422ee0,
        PID_Partitioning = 0xde4a210c,
        PID_COUNT = 7
    };

protected:
    epiS32 m_Level{0};
    epiDeviceCPUX86CacheType m_CacheType{epiDeviceCPUX86CacheType::Null};
    epiSize_t m_CacheSize{0};
    epiS32 m_Ways{0};
    epiSize_t m_LineSize{0};
    epiS32 m_TLBEntries{0};
    epiS32 m_Partitioning{0};

EPI_GENREGION_END(epiDeviceCPUX86CacheLevelInfo)

public:
    epiString ToString() const override;
};

class epiDeviceCPUX86CacheInfo : public Object
{
EPI_GENREGION_BEGIN(epiDeviceCPUX86CacheInfo)

EPI_GENHIDDEN_epiDeviceCPUX86CacheInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x99b5cdb3};

    enum epiDeviceCPUX86CacheInfo_PIDs
    {
        PID_Levels = 0x9886612f,
        PID_COUNT = 1
    };

protected:
    epiArray<epiDeviceCPUX86CacheLevelInfo> m_Levels{};

EPI_GENREGION_END(epiDeviceCPUX86CacheInfo)

public:
    epiDeviceCPUX86CacheInfo();

    epiString ToString() const override;
};

class epiDeviceCPUX86 : public epiDeviceCPUBase
{
EPI_GENREGION_BEGIN(epiDeviceCPUX86)

EPI_GENHIDDEN_epiDeviceCPUX86()

public:
    constexpr static epiMetaTypeID TypeID{0xac7e3540};

    enum epiDeviceCPUX86_PIDs
    {
        PID_CacheInfo = 0x5883e94e,
        PID_Family = 0xa24a246d,
        PID_Model = 0x16545ddd,
        PID_Stepping = 0x3d643b3,
        PID_Vendor = 0xf28e36c0,
        PID_Microarchitecture = 0x1ca07b8e,
        PID_FPU = 0x2aecd04f,
        PID_TSC = 0xeab741c3,
        PID_CX8 = 0xd7fd8549,
        PID_CLFSH = 0x95350446,
        PID_MMX = 0xa7642f0f,
        PID_AES = 0xf17585eb,
        PID_ERMS = 0x5503bccb,
        PID_F16C = 0xdc5bd605,
        PID_FMA4 = 0x2faf4c9f,
        PID_FMA3 = 0xb1cbd93c,
        PID_VAES = 0xc116d39b,
        PID_VPCLMULQDQ = 0x769b1464,
        PID_BMI1 = 0x187ea54f,
        PID_HLE = 0xdbb2b07c,
        PID_BMI2 = 0x8177f4f5,
        PID_RTM = 0x46c386b1,
        PID_RDSEED = 0xea12778,
        PID_CLFLUSHOPT = 0x12d3ae68,
        PID_CLWB = 0xbc4db744,
        PID_SSE = 0x69bf273,
        PID_SSE2 = 0xd3df0579,
        PID_SSE3 = 0xa4d835ef,
        PID_SSSE3 = 0x3c0da8f5,
        PID_SSE4_1 = 0xa73eca03,
        PID_SSE4_2 = 0x3e379bb9,
        PID_SSE4A = 0xac892f90,
        PID_AVX = 0x7481df1,
        PID_AVX2 = 0xd068349a,
        PID_AVX512F = 0x3d37f9b3,
        PID_AVX512CD = 0x8c914b8e,
        PID_AVX512ER = 0x2e1f5959,
        PID_AVX512PF = 0x3706b30,
        PID_AVX512BW = 0x11343b11,
        PID_AVX512DQ = 0xae0d39a2,
        PID_AVX512VL = 0xb5ff25a8,
        PID_AVX512IFMA = 0x2de2c7f7,
        PID_AVX512VBMI = 0x2c4aa0d0,
        PID_AVX512VBMI2 = 0x9c2a2679,
        PID_AVX512VNNI = 0xe7d0a77,
        PID_AVX512BITALG = 0x6ed6b449,
        PID_AVX512VPOPCNTDQ = 0x4c0ce64d,
        PID_AVX512_4VNNIW = 0x26725d9d,
        PID_AVX512_4VBMI2 = 0x533ac9ab,
        PID_AVX512_SECOND_FMA = 0xc73ac9f5,
        PID_AVX512_4FMAPS = 0xc3164fcd,
        PID_AVX512_BF16 = 0x7de49c0e,
        PID_AVX512_VP2INTERSECT = 0xb757bfb6,
        PID_AMX_BF16 = 0xb3ba28cc,
        PID_AMX_TILE = 0x9e09408f,
        PID_AMX_INT8 = 0x959a4c90,
        PID_PCLMULQDQ = 0xc7129eb3,
        PID_SMX = 0xb1dca175,
        PID_SGX = 0x4b3349ff,
        PID_CX16 = 0xc3adc5ec,
        PID_SHA = 0xa8c0fdf0,
        PID_POPCNT = 0xdcc2ad91,
        PID_MOVBE = 0x9fee914,
        PID_RDRND = 0xe0f4b900,
        PID_DCA = 0x525d91ce,
        PID_SS = 0x222d1c26,
        PID_COUNT = 66
    };

protected:
    epiS32 GetFamily_Callback() const;
    epiS32 GetModel_Callback() const;
    epiS32 GetStepping_Callback() const;
    epiString GetVendor_Callback() const;
    epiDeviceCPUX86Microarchitecture GetMicroarchitecture_Callback() const;
    epiBool GetFPU_Callback() const;
    epiBool GetTSC_Callback() const;
    epiBool GetCX8_Callback() const;
    epiBool GetCLFSH_Callback() const;
    epiBool GetMMX_Callback() const;
    epiBool GetAES_Callback() const;
    epiBool GetERMS_Callback() const;
    epiBool GetF16C_Callback() const;
    epiBool GetFMA4_Callback() const;
    epiBool GetFMA3_Callback() const;
    epiBool GetVAES_Callback() const;
    epiBool GetVPCLMULQDQ_Callback() const;
    epiBool GetBMI1_Callback() const;
    epiBool GetHLE_Callback() const;
    epiBool GetBMI2_Callback() const;
    epiBool GetRTM_Callback() const;
    epiBool GetRDSEED_Callback() const;
    epiBool GetCLFLUSHOPT_Callback() const;
    epiBool GetCLWB_Callback() const;
    epiBool GetSSE_Callback() const;
    epiBool GetSSE2_Callback() const;
    epiBool GetSSE3_Callback() const;
    epiBool GetSSSE3_Callback() const;
    epiBool GetSSE4_1_Callback() const;
    epiBool GetSSE4_2_Callback() const;
    epiBool GetSSE4A_Callback() const;
    epiBool GetAVX_Callback() const;
    epiBool GetAVX2_Callback() const;
    epiBool GetAVX512F_Callback() const;
    epiBool GetAVX512CD_Callback() const;
    epiBool GetAVX512ER_Callback() const;
    epiBool GetAVX512PF_Callback() const;
    epiBool GetAVX512BW_Callback() const;
    epiBool GetAVX512DQ_Callback() const;
    epiBool GetAVX512VL_Callback() const;
    epiBool GetAVX512IFMA_Callback() const;
    epiBool GetAVX512VBMI_Callback() const;
    epiBool GetAVX512VBMI2_Callback() const;
    epiBool GetAVX512VNNI_Callback() const;
    epiBool GetAVX512BITALG_Callback() const;
    epiBool GetAVX512VPOPCNTDQ_Callback() const;
    epiBool GetAVX512_4VNNIW_Callback() const;
    epiBool GetAVX512_4VBMI2_Callback() const;
    epiBool GetAVX512_SECOND_FMA_Callback() const;
    epiBool GetAVX512_4FMAPS_Callback() const;
    epiBool GetAVX512_BF16_Callback() const;
    epiBool GetAVX512_VP2INTERSECT_Callback() const;
    epiBool GetAMX_BF16_Callback() const;
    epiBool GetAMX_TILE_Callback() const;
    epiBool GetAMX_INT8_Callback() const;
    epiBool GetPCLMULQDQ_Callback() const;
    epiBool GetSMX_Callback() const;
    epiBool GetSGX_Callback() const;
    epiBool GetCX16_Callback() const;
    epiBool GetSHA_Callback() const;
    epiBool GetPOPCNT_Callback() const;
    epiBool GetMOVBE_Callback() const;
    epiBool GetRDRND_Callback() const;
    epiBool GetDCA_Callback() const;
    epiBool GetSS_Callback() const;

protected:
    epiDeviceCPUX86CacheInfo m_CacheInfo{};

EPI_GENREGION_END(epiDeviceCPUX86)

public:
    epiDeviceCPUX86();

    epiString ToString() const override;

protected:
    cpu_features::X86Info m_X86Info;
};

EPI_NAMESPACE_END()
