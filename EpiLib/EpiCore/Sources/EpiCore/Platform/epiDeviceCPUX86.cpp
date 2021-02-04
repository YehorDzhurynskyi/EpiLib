EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/epiDeviceCPUX86.h"
#include "EpiCore/Platform/epiDeviceCPUX86.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Property/epiPropertyPointer.h"

namespace
{

// TODO: move to `epiString` class
epiString PrependWith(const epiString& str, const epiChar* prefix)
{
    std::stringstream ss(str);
    std::string line;

    epiString to;

    while (std::getline(ss, line, '\n'))
    {
        line = prefix + line;
        to += line + '\n';
    }

    return to;
}

}

EPI_NAMESPACE_BEGIN()

epiString epiDeviceCPUX86CacheLevelInfo::ToString() const
{
    epiString str;
    str.reserve(1024);

    const MetaClass& meta = GetMetaClass();
    const MetaClassData& metaData = meta.GetClassData();
    for (const auto& prty : metaData)
    {
        const epiMetaPropertyID pid = prty.GetPID();
        if (const MetaProperty* prty = metaData.GetPropertyBy(pid))
        {
            str += epiString(prty->GetName()) + ": ";
            if (pid == PID_CacheType)
            {
                // TODO: get string repr of enum
                str += '`';
                switch (GetCacheType())
                {
                    case epiDeviceCPUX86CacheType::Data: str += "Data"; break;
                    case epiDeviceCPUX86CacheType::Instruction: str += "Instruction"; break;
                    case epiDeviceCPUX86CacheType::Unified: str += "Unified"; break;
                    case epiDeviceCPUX86CacheType::TLB: str += "TLB"; break;
                    case epiDeviceCPUX86CacheType::DTLB: str += "DTLB"; break;
                    case epiDeviceCPUX86CacheType::STLB: str += "STLB"; break;
                    case epiDeviceCPUX86CacheType::Prefetch: str += "Prefetch"; break;
                    case epiDeviceCPUX86CacheType::Null:
                    default: str += "Null"; break;
                }
                str += '`';
            }
            else
            {
                epiPropertyPointer ptr = epiPropertyPointer::CreateFromPropertyConst(*this, prty);
                str += ptr.GetValueString(epiPropertyPointerValueStringStyle_Boolean_Enabled_Disabled |
                                          epiPropertyPointerValueStringStyle_String_Quoted |
                                          epiPropertyPointerValueStringStyle_Size_Repr_Bytes);
            }

            str += '\n';
        }
    }

    return str;
}

epiDeviceCPUX86CacheInfo::epiDeviceCPUX86CacheInfo()
{
    auto cacheTypeOf = [](const cpu_features::CacheType type)
    {
        switch (type)
        {
            case cpu_features::CPU_FEATURE_CACHE_NULL: return epiDeviceCPUX86CacheType::Null;
            case cpu_features::CPU_FEATURE_CACHE_DATA: return epiDeviceCPUX86CacheType::Data;
            case cpu_features::CPU_FEATURE_CACHE_INSTRUCTION: return epiDeviceCPUX86CacheType::Instruction;
            case cpu_features::CPU_FEATURE_CACHE_UNIFIED: return epiDeviceCPUX86CacheType::Unified;
            case cpu_features::CPU_FEATURE_CACHE_TLB: return epiDeviceCPUX86CacheType::TLB;
            case cpu_features::CPU_FEATURE_CACHE_DTLB: return epiDeviceCPUX86CacheType::DTLB;
            case cpu_features::CPU_FEATURE_CACHE_STLB: return epiDeviceCPUX86CacheType::STLB;
            case cpu_features::CPU_FEATURE_CACHE_PREFETCH: return epiDeviceCPUX86CacheType::Prefetch;
            default: return epiDeviceCPUX86CacheType::Null;
        }
    };

    const cpu_features::CacheInfo info = cpu_features::GetX86CacheInfo();
    for (epiS32 i = 0; i < info.size; ++i)
    {
        const cpu_features::CacheLevelInfo levelInfo = info.levels[i];
        epiDeviceCPUX86CacheLevelInfo& level = GetLevels().PushBack();

        level.SetLevel(levelInfo.level);
        level.SetCacheType(cacheTypeOf(levelInfo.cache_type));
        level.SetCacheSize(levelInfo.cache_size);
        level.SetWays(levelInfo.ways);
        level.SetLineSize(levelInfo.line_size);
        level.SetTLBEntries(levelInfo.tlb_entries);
        level.SetPartitioning(levelInfo.partitioning);
    }
}

epiString epiDeviceCPUX86CacheInfo::ToString() const
{
    epiString str;
    str.reserve(4096);

    epiS32 i = 0;
    for (const auto& level : GetLevels())
    {
        str += fmt::format("[{}]:\n", i++);
        str += PrependWith(level.ToString(), "\t") + '\n';
    }

    return str;
}

epiDeviceCPUX86::epiDeviceCPUX86()
    : m_X86Info{cpu_features::GetX86Info()}
{
}

epiString epiDeviceCPUX86::ToString() const
{
    epiString str = super::ToString();
    str.reserve(8192);

    const MetaClass& meta = epiDeviceCPUX86::GetMetaClass();
    const MetaClassData& metaData = meta.GetClassData();
    for (const auto& prty : metaData)
    {
        const epiMetaPropertyID pid = prty.GetPID();
        if (const MetaProperty* prty = metaData.GetPropertyBy(pid))
        {
            str += epiString(prty->GetName()) + ":";
            if (pid == PID_CacheInfo)
            {
                // TODO: write custom `epiString` class with `PrependWith` method
                str += "\n" + PrependWith(GetCacheInfo().ToString(), "\t");
            }
            else if (pid == PID_Microarchitecture)
            {
                str += " `";
                // TODO: get string repr of enum
                switch (GetMicroarchitecture())
                {
                case epiDeviceCPUX86Microarchitecture::IntelCore: str += "Intel Core"; break;
                case epiDeviceCPUX86Microarchitecture::IntelPenryn: str += "Intel Penryn"; break;
                case epiDeviceCPUX86Microarchitecture::IntelNehalem: str += "Intel Nehalem"; break;
                case epiDeviceCPUX86Microarchitecture::IntelAtomBonnell: str += "Intel Atom Bonnell"; break;
                case epiDeviceCPUX86Microarchitecture::IntelWestmere: str += "Intel Westmere"; break;
                case epiDeviceCPUX86Microarchitecture::IntelSandybridge: str += "Intel Sandybridge"; break;
                case epiDeviceCPUX86Microarchitecture::IntelIvybridge: str += "Intel Ivybridge"; break;
                case epiDeviceCPUX86Microarchitecture::IntelAtomSilvermont: str += "Intel Atom Silvermont"; break;
                case epiDeviceCPUX86Microarchitecture::IntelHaswell: str += "Intel Haswell"; break;
                case epiDeviceCPUX86Microarchitecture::IntelBroadwell: str += "Intel Broadwell"; break;
                case epiDeviceCPUX86Microarchitecture::IntelSkyLake: str += "Intel Sky Lake"; break;
                case epiDeviceCPUX86Microarchitecture::IntelAtomGoldmont: str += "Intel Atom Goldmont"; break;
                case epiDeviceCPUX86Microarchitecture::IntelKabyLake: str += "Intel KabyLake"; break;
                case epiDeviceCPUX86Microarchitecture::IntelCoffeeLake: str += "Intel Coffee Lake"; break;
                case epiDeviceCPUX86Microarchitecture::IntelWhiskeyLake: str += "Intel Whiskey Lake"; break;
                case epiDeviceCPUX86Microarchitecture::IntelCannonLake: str += "Intel Cannon Lake"; break;
                case epiDeviceCPUX86Microarchitecture::IntelIceLake: str += "Intel Ice Lake"; break;
                case epiDeviceCPUX86Microarchitecture::IntelTigerLake: str += "Intel Tiger Lake"; break;
                case epiDeviceCPUX86Microarchitecture::IntelSapphireRapids: str += "Intel Sapphire Rapids"; break;
                case epiDeviceCPUX86Microarchitecture::AMDHammer: str += "AMD Hammer"; break;
                case epiDeviceCPUX86Microarchitecture::AMDK10: str += "AMD K10"; break;
                case epiDeviceCPUX86Microarchitecture::AMDBobcat: str += "AMD Bobcat"; break;
                case epiDeviceCPUX86Microarchitecture::AMDBulldozer: str += "AMD Bulldozer"; break;
                case epiDeviceCPUX86Microarchitecture::AMDJaguar: str += "AMD Jaguar"; break;
                case epiDeviceCPUX86Microarchitecture::AMDZen: str += "AMD Zen"; break;
                case epiDeviceCPUX86Microarchitecture::Unknown:
                default: str += "Unknown"; break;
                }
                str += '`';
            }
            else
            {
                epiPropertyPointer ptr = epiPropertyPointer::CreateFromPropertyConst(*this, prty);
                str += ' ' + ptr.GetValueString(epiPropertyPointerValueStringStyle_Boolean_Enabled_Disabled |
                                                epiPropertyPointerValueStringStyle_String_Quoted | 
                                                epiPropertyPointerValueStringStyle_Size_Repr_Bytes);
            }

            str += '\n';
        }
    }

    return str;
}

epiS32 epiDeviceCPUX86::GetFamily_Callback() const
{
    return m_X86Info.family;
}

epiS32 epiDeviceCPUX86::GetModel_Callback() const
{
    return m_X86Info.model;
}

epiS32 epiDeviceCPUX86::GetStepping_Callback() const
{
    return m_X86Info.stepping;
}

epiString epiDeviceCPUX86::GetVendor_Callback() const
{
    return m_X86Info.vendor;
}

epiString epiDeviceCPUX86::GetBrandName_Callback() const
{
    epiChar brand[49];
    cpu_features::FillX86BrandString(brand);

    return epiString(brand);
}

epiDeviceCPUX86Microarchitecture epiDeviceCPUX86::GetMicroarchitecture_Callback() const
{
    auto microarchitectureOf = [](const cpu_features::X86Microarchitecture arch)
    {
        switch (arch)
        {
        case cpu_features::X86_UNKNOWN: return epiDeviceCPUX86Microarchitecture::Unknown;
        case cpu_features::INTEL_CORE: return epiDeviceCPUX86Microarchitecture::IntelCore;
        case cpu_features::INTEL_PNR: return epiDeviceCPUX86Microarchitecture::IntelPenryn;
        case cpu_features::INTEL_NHM: return epiDeviceCPUX86Microarchitecture::IntelNehalem;
        case cpu_features::INTEL_ATOM_BNL: return epiDeviceCPUX86Microarchitecture::IntelAtomBonnell;
        case cpu_features::INTEL_WSM: return epiDeviceCPUX86Microarchitecture::IntelWestmere;
        case cpu_features::INTEL_SNB: return epiDeviceCPUX86Microarchitecture::IntelSandybridge;
        case cpu_features::INTEL_IVB: return epiDeviceCPUX86Microarchitecture::IntelIvybridge;
        case cpu_features::INTEL_ATOM_SMT: return epiDeviceCPUX86Microarchitecture::IntelAtomSilvermont;
        case cpu_features::INTEL_HSW: return epiDeviceCPUX86Microarchitecture::IntelHaswell;
        case cpu_features::INTEL_BDW: return epiDeviceCPUX86Microarchitecture::IntelBroadwell;
        case cpu_features::INTEL_SKL: return epiDeviceCPUX86Microarchitecture::IntelSkyLake;
        case cpu_features::INTEL_ATOM_GMT: return epiDeviceCPUX86Microarchitecture::IntelAtomGoldmont;
        case cpu_features::INTEL_KBL: return epiDeviceCPUX86Microarchitecture::IntelKabyLake;
        case cpu_features::INTEL_CFL: return epiDeviceCPUX86Microarchitecture::IntelCoffeeLake;
        case cpu_features::INTEL_WHL: return epiDeviceCPUX86Microarchitecture::IntelWhiskeyLake;
        case cpu_features::INTEL_CNL: return epiDeviceCPUX86Microarchitecture::IntelCannonLake;
        case cpu_features::INTEL_ICL: return epiDeviceCPUX86Microarchitecture::IntelIceLake;
        case cpu_features::INTEL_TGL: return epiDeviceCPUX86Microarchitecture::IntelTigerLake;
        case cpu_features::INTEL_SPR: return epiDeviceCPUX86Microarchitecture::IntelSapphireRapids;
        case cpu_features::AMD_HAMMER: return epiDeviceCPUX86Microarchitecture::AMDHammer;
        case cpu_features::AMD_K10: return epiDeviceCPUX86Microarchitecture::AMDK10;
        case cpu_features::AMD_BOBCAT: return epiDeviceCPUX86Microarchitecture::AMDBobcat;
        case cpu_features::AMD_BULLDOZER: return epiDeviceCPUX86Microarchitecture::AMDBulldozer;
        case cpu_features::AMD_JAGUAR: return epiDeviceCPUX86Microarchitecture::AMDJaguar;
        case cpu_features::AMD_ZEN: return epiDeviceCPUX86Microarchitecture::AMDZen;
        default: return epiDeviceCPUX86Microarchitecture::Unknown;
        }
    };

    return microarchitectureOf(cpu_features::GetX86Microarchitecture(&m_X86Info));
}

epiBool epiDeviceCPUX86::GetFPU_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_FPU);
}

epiBool epiDeviceCPUX86::GetTSC_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_TSC);
}

epiBool epiDeviceCPUX86::GetCX8_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CX8);
}

epiBool epiDeviceCPUX86::GetCLFSH_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CLFSH);
}

epiBool epiDeviceCPUX86::GetMMX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_MMX);
}

epiBool epiDeviceCPUX86::GetAES_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AES);
}

epiBool epiDeviceCPUX86::GetERMS_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_ERMS);
}

epiBool epiDeviceCPUX86::GetF16C_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_F16C);
}

epiBool epiDeviceCPUX86::GetFMA4_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_FMA4);
}

epiBool epiDeviceCPUX86::GetFMA3_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_FMA3);
}

epiBool epiDeviceCPUX86::GetVAES_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_VAES);
}

epiBool epiDeviceCPUX86::GetVPCLMULQDQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_VPCLMULQDQ);
}

epiBool epiDeviceCPUX86::GetBMI1_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_BMI1);
}

epiBool epiDeviceCPUX86::GetHLE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_HLE);
}

epiBool epiDeviceCPUX86::GetBMI2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_BMI2);
}

epiBool epiDeviceCPUX86::GetRTM_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_RTM);
}

epiBool epiDeviceCPUX86::GetRDSEED_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_RDSEED);
}

epiBool epiDeviceCPUX86::GetCLFLUSHOPT_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CLFLUSHOPT);
}

epiBool epiDeviceCPUX86::GetCLWB_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CLWB);
}

epiBool epiDeviceCPUX86::GetSSE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE);
}

epiBool epiDeviceCPUX86::GetSSE2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE2);
}

epiBool epiDeviceCPUX86::GetSSE3_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE3);
}

epiBool epiDeviceCPUX86::GetSSSE3_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSSE3);
}

epiBool epiDeviceCPUX86::GetSSE4_1_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE4_1);
}

epiBool epiDeviceCPUX86::GetSSE4_2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE4_2);
}

epiBool epiDeviceCPUX86::GetSSE4A_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE4A);
}

epiBool epiDeviceCPUX86::GetAVX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX);
}

epiBool epiDeviceCPUX86::GetAVX2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX2);
}

epiBool epiDeviceCPUX86::GetAVX512F_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512F);
}

epiBool epiDeviceCPUX86::GetAVX512CD_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512CD);
}

epiBool epiDeviceCPUX86::GetAVX512ER_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512ER);
}

epiBool epiDeviceCPUX86::GetAVX512PF_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512PF);
}

epiBool epiDeviceCPUX86::GetAVX512BW_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512BW);
}

epiBool epiDeviceCPUX86::GetAVX512DQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512DQ);
}

epiBool epiDeviceCPUX86::GetAVX512VL_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VL);
}

epiBool epiDeviceCPUX86::GetAVX512IFMA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512IFMA);
}

epiBool epiDeviceCPUX86::GetAVX512VBMI_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VBMI);
}

epiBool epiDeviceCPUX86::GetAVX512VBMI2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VBMI2);
}

epiBool epiDeviceCPUX86::GetAVX512VNNI_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VNNI);
}

epiBool epiDeviceCPUX86::GetAVX512BITALG_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512BITALG);
}

epiBool epiDeviceCPUX86::GetAVX512VPOPCNTDQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VPOPCNTDQ);
}

epiBool epiDeviceCPUX86::GetAVX512_4VNNIW_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_4VNNIW);
}

epiBool epiDeviceCPUX86::GetAVX512_4VBMI2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_4VBMI2);
}

epiBool epiDeviceCPUX86::GetAVX512_SECOND_FMA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_SECOND_FMA);
}

epiBool epiDeviceCPUX86::GetAVX512_4FMAPS_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_4FMAPS);
}

epiBool epiDeviceCPUX86::GetAVX512_BF16_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_BF16);
}

epiBool epiDeviceCPUX86::GetAVX512_VP2INTERSECT_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_VP2INTERSECT);
}

epiBool epiDeviceCPUX86::GetAMX_BF16_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AMX_BF16);
}

epiBool epiDeviceCPUX86::GetAMX_TILE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AMX_TILE);
}

epiBool epiDeviceCPUX86::GetAMX_INT8_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AMX_INT8);
}

epiBool epiDeviceCPUX86::GetPCLMULQDQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_PCLMULQDQ);
}

epiBool epiDeviceCPUX86::GetSMX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SMX);
}

epiBool epiDeviceCPUX86::GetSGX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SGX);
}

epiBool epiDeviceCPUX86::GetCX16_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CX16);
}

epiBool epiDeviceCPUX86::GetSHA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SHA);
}

epiBool epiDeviceCPUX86::GetPOPCNT_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_POPCNT);
}

epiBool epiDeviceCPUX86::GetMOVBE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_MOVBE);
}

epiBool epiDeviceCPUX86::GetRDRND_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_RDRND);
}

epiBool epiDeviceCPUX86::GetDCA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_DCA);
}

epiBool epiDeviceCPUX86::GetSS_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SS);
}

EPI_NAMESPACE_END()
