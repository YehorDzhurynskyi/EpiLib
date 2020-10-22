EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/CPUDeviceX86.h"
#include "EpiCore/Platform/CPUDeviceX86.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/PropertyPointer.h"

namespace
{

// TODO: move to utils or smth
epiString PrependWithIndentation(const epiString& str, epiU32 tab)
{
    std::stringstream ss(str);
    std::string line;

    epiString to;

    while (std::getline(ss, line, '\n'))
    {
        for (epiU32 t = 0; t < tab; ++t)
        {
            line = '\t' + line;
        }

        to += line + '\n';
    }

    return to;
}

}

EPI_NAMESPACE_BEGIN()

epiString CPUDeviceX86CacheLevelInfo::ToString() const
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
                    case CPUDeviceX86CacheType::Data: str += "Data"; break;
                    case CPUDeviceX86CacheType::Instruction: str += "Instruction"; break;
                    case CPUDeviceX86CacheType::Unified: str += "Unified"; break;
                    case CPUDeviceX86CacheType::TLB: str += "TLB"; break;
                    case CPUDeviceX86CacheType::DTLB: str += "DTLB"; break;
                    case CPUDeviceX86CacheType::STLB: str += "STLB"; break;
                    case CPUDeviceX86CacheType::Prefetch: str += "Prefetch"; break;
                    case CPUDeviceX86CacheType::Null:
                    default: str += "Null"; break;
                }
                str += '`';
            }
            else
            {
                PropertyPointer ptr = PropertyPointer::CreateFromProperty(*this, prty);
                str += ptr.GetValueString(PropertyPointerValueStringStyle_Boolean_Enabled_Disabled |
                                          PropertyPointerValueStringStyle_String_Quoted |
                                          PropertyPointerValueStringStyle_Size_Repr_Bytes);
            }

            str += '\n';
        }
    }

    return str;
}

CPUDeviceX86CacheInfo::CPUDeviceX86CacheInfo()
{
    auto cacheTypeOf = [](const cpu_features::CacheType type)
    {
        switch (type)
        {
            case cpu_features::CPU_FEATURE_CACHE_NULL: return CPUDeviceX86CacheType::Null;
            case cpu_features::CPU_FEATURE_CACHE_DATA: return CPUDeviceX86CacheType::Data;
            case cpu_features::CPU_FEATURE_CACHE_INSTRUCTION: return CPUDeviceX86CacheType::Instruction;
            case cpu_features::CPU_FEATURE_CACHE_UNIFIED: return CPUDeviceX86CacheType::Unified;
            case cpu_features::CPU_FEATURE_CACHE_TLB: return CPUDeviceX86CacheType::TLB;
            case cpu_features::CPU_FEATURE_CACHE_DTLB: return CPUDeviceX86CacheType::DTLB;
            case cpu_features::CPU_FEATURE_CACHE_STLB: return CPUDeviceX86CacheType::STLB;
            case cpu_features::CPU_FEATURE_CACHE_PREFETCH: return CPUDeviceX86CacheType::Prefetch;
            default: return CPUDeviceX86CacheType::Null;
        }
    };

    const cpu_features::CacheInfo info = cpu_features::GetX86CacheInfo();
    for (epiS32 i = 0; i < info.size; ++i)
    {
        const cpu_features::CacheLevelInfo levelInfo = info.levels[i];
        CPUDeviceX86CacheLevelInfo& level = GetLevels().PushBack();

        level.SetLevel(levelInfo.level);
        level.SetCacheType(cacheTypeOf(levelInfo.cache_type));
        level.SetCacheSize(levelInfo.cache_size);
        level.SetWays(levelInfo.ways);
        level.SetLineSize(levelInfo.line_size);
        level.SetTLBEntries(levelInfo.tlb_entries);
        level.SetPartitioning(levelInfo.partitioning);
    }
}

epiString CPUDeviceX86CacheInfo::ToString() const
{
    epiString str;
    str.reserve(4096);

    epiS32 i = 0;
    for (const auto& level : GetLevels())
    {
        str += fmt::format("[{}]:\n", i++);
        str += PrependWithIndentation(level.ToString(), 1) + '\n';
    }

    return str;
}

CPUDeviceX86::CPUDeviceX86()
    : m_X86Info{cpu_features::GetX86Info()}
{
}

epiString CPUDeviceX86::ToString() const
{
    epiString str;
    str.reserve(8192);

    const MetaClass& meta = GetMetaClass();
    const MetaClassData& metaData = meta.GetClassData();
    for (const auto& prty : metaData)
    {
        const epiMetaPropertyID pid = prty.GetPID();
        if (const MetaProperty* prty = metaData.GetPropertyBy(pid))
        {
            str += epiString(prty->GetName()) + ":";
            if (pid == PID_CacheInfo)
            {
                str += "\n" + PrependWithIndentation(GetCacheInfo().ToString(), 1);
            }
            else if (pid == PID_Microarchitecture)
            {
                str += ' `';
                // TODO: get string repr of enum
                switch (GetMicroarchitecture())
                {
                case CPUDeviceX86Microarchitecture::IntelCore: str += "Intel Core"; break;
                case CPUDeviceX86Microarchitecture::IntelPenryn: str += "Intel Penryn"; break;
                case CPUDeviceX86Microarchitecture::IntelNehalem: str += "Intel Nehalem"; break;
                case CPUDeviceX86Microarchitecture::IntelAtomBonnell: str += "Intel Atom Bonnell"; break;
                case CPUDeviceX86Microarchitecture::IntelWestmere: str += "Intel Westmere"; break;
                case CPUDeviceX86Microarchitecture::IntelSandybridge: str += "Intel Sandybridge"; break;
                case CPUDeviceX86Microarchitecture::IntelIvybridge: str += "Intel Ivybridge"; break;
                case CPUDeviceX86Microarchitecture::IntelAtomSilvermont: str += "Intel Atom Silvermont"; break;
                case CPUDeviceX86Microarchitecture::IntelHaswell: str += "Intel Haswell"; break;
                case CPUDeviceX86Microarchitecture::IntelBroadwell: str += "Intel Broadwell"; break;
                case CPUDeviceX86Microarchitecture::IntelSkyLake: str += "Intel Sky Lake"; break;
                case CPUDeviceX86Microarchitecture::IntelAtomGoldmont: str += "Intel Atom Goldmont"; break;
                case CPUDeviceX86Microarchitecture::IntelKabyLake: str += "Intel KabyLake"; break;
                case CPUDeviceX86Microarchitecture::IntelCoffeeLake: str += "Intel Coffee Lake"; break;
                case CPUDeviceX86Microarchitecture::IntelWhiskeyLake: str += "Intel Whiskey Lake"; break;
                case CPUDeviceX86Microarchitecture::IntelCannonLake: str += "Intel Cannon Lake"; break;
                case CPUDeviceX86Microarchitecture::IntelIceLake: str += "Intel Ice Lake"; break;
                case CPUDeviceX86Microarchitecture::IntelTigerLake: str += "Intel Tiger Lake"; break;
                case CPUDeviceX86Microarchitecture::IntelSapphireRapids: str += "Intel Sapphire Rapids"; break;
                case CPUDeviceX86Microarchitecture::AMDHammer: str += "AMD Hammer"; break;
                case CPUDeviceX86Microarchitecture::AMDK10: str += "AMD K10"; break;
                case CPUDeviceX86Microarchitecture::AMDBobcat: str += "AMD Bobcat"; break;
                case CPUDeviceX86Microarchitecture::AMDBulldozer: str += "AMD Bulldozer"; break;
                case CPUDeviceX86Microarchitecture::AMDJaguar: str += "AMD Jaguar"; break;
                case CPUDeviceX86Microarchitecture::AMDZen: str += "AMD Zen"; break;
                case CPUDeviceX86Microarchitecture::Unknown:
                default: str += "Unknown"; break;
                }
                str += '`';
            }
            else
            {
                PropertyPointer ptr = PropertyPointer::CreateFromProperty(*this, prty);
                str += ' ' + ptr.GetValueString(PropertyPointerValueStringStyle_Boolean_Enabled_Disabled |
                                                PropertyPointerValueStringStyle_String_Quoted | 
                                                PropertyPointerValueStringStyle_Size_Repr_Bytes);
            }

            str += '\n';
        }
    }

    return str;
}

epiS32 CPUDeviceX86::GetFamily_Callback() const
{
    return m_X86Info.family;
}

epiS32 CPUDeviceX86::GetModel_Callback() const
{
    return m_X86Info.model;
}

epiS32 CPUDeviceX86::GetStepping_Callback() const
{
    return m_X86Info.stepping;
}

epiString CPUDeviceX86::GetVendor_Callback() const
{
    return m_X86Info.vendor;
}

CPUDeviceX86Microarchitecture CPUDeviceX86::GetMicroarchitecture_Callback() const
{
    auto microarchitectureOf = [](const cpu_features::X86Microarchitecture arch)
    {
        switch (arch)
        {
        case cpu_features::X86_UNKNOWN: return CPUDeviceX86Microarchitecture::Unknown;
        case cpu_features::INTEL_CORE: return CPUDeviceX86Microarchitecture::IntelCore;
        case cpu_features::INTEL_PNR: return CPUDeviceX86Microarchitecture::IntelPenryn;
        case cpu_features::INTEL_NHM: return CPUDeviceX86Microarchitecture::IntelNehalem;
        case cpu_features::INTEL_ATOM_BNL: return CPUDeviceX86Microarchitecture::IntelAtomBonnell;
        case cpu_features::INTEL_WSM: return CPUDeviceX86Microarchitecture::IntelWestmere;
        case cpu_features::INTEL_SNB: return CPUDeviceX86Microarchitecture::IntelSandybridge;
        case cpu_features::INTEL_IVB: return CPUDeviceX86Microarchitecture::IntelIvybridge;
        case cpu_features::INTEL_ATOM_SMT: return CPUDeviceX86Microarchitecture::IntelAtomSilvermont;
        case cpu_features::INTEL_HSW: return CPUDeviceX86Microarchitecture::IntelHaswell;
        case cpu_features::INTEL_BDW: return CPUDeviceX86Microarchitecture::IntelBroadwell;
        case cpu_features::INTEL_SKL: return CPUDeviceX86Microarchitecture::IntelSkyLake;
        case cpu_features::INTEL_ATOM_GMT: return CPUDeviceX86Microarchitecture::IntelAtomGoldmont;
        case cpu_features::INTEL_KBL: return CPUDeviceX86Microarchitecture::IntelKabyLake;
        case cpu_features::INTEL_CFL: return CPUDeviceX86Microarchitecture::IntelCoffeeLake;
        case cpu_features::INTEL_WHL: return CPUDeviceX86Microarchitecture::IntelWhiskeyLake;
        case cpu_features::INTEL_CNL: return CPUDeviceX86Microarchitecture::IntelCannonLake;
        case cpu_features::INTEL_ICL: return CPUDeviceX86Microarchitecture::IntelIceLake;
        case cpu_features::INTEL_TGL: return CPUDeviceX86Microarchitecture::IntelTigerLake;
        case cpu_features::INTEL_SPR: return CPUDeviceX86Microarchitecture::IntelSapphireRapids;
        case cpu_features::AMD_HAMMER: return CPUDeviceX86Microarchitecture::AMDHammer;
        case cpu_features::AMD_K10: return CPUDeviceX86Microarchitecture::AMDK10;
        case cpu_features::AMD_BOBCAT: return CPUDeviceX86Microarchitecture::AMDBobcat;
        case cpu_features::AMD_BULLDOZER: return CPUDeviceX86Microarchitecture::AMDBulldozer;
        case cpu_features::AMD_JAGUAR: return CPUDeviceX86Microarchitecture::AMDJaguar;
        case cpu_features::AMD_ZEN: return CPUDeviceX86Microarchitecture::AMDZen;
        default: return CPUDeviceX86Microarchitecture::Unknown;
        }
    };

    return microarchitectureOf(cpu_features::GetX86Microarchitecture(&m_X86Info));
}

epiBool CPUDeviceX86::GetFPU_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_FPU);
}

epiBool CPUDeviceX86::GetTSC_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_TSC);
}

epiBool CPUDeviceX86::GetCX8_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CX8);
}

epiBool CPUDeviceX86::GetCLFSH_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CLFSH);
}

epiBool CPUDeviceX86::GetMMX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_MMX);
}

epiBool CPUDeviceX86::GetAES_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AES);
}

epiBool CPUDeviceX86::GetERMS_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_ERMS);
}

epiBool CPUDeviceX86::GetF16C_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_F16C);
}

epiBool CPUDeviceX86::GetFMA4_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_FMA4);
}

epiBool CPUDeviceX86::GetFMA3_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_FMA3);
}

epiBool CPUDeviceX86::GetVAES_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_VAES);
}

epiBool CPUDeviceX86::GetVPCLMULQDQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_VPCLMULQDQ);
}

epiBool CPUDeviceX86::GetBMI1_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_BMI1);
}

epiBool CPUDeviceX86::GetHLE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_HLE);
}

epiBool CPUDeviceX86::GetBMI2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_BMI2);
}

epiBool CPUDeviceX86::GetRTM_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_RTM);
}

epiBool CPUDeviceX86::GetRDSEED_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_RDSEED);
}

epiBool CPUDeviceX86::GetCLFLUSHOPT_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CLFLUSHOPT);
}

epiBool CPUDeviceX86::GetCLWB_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CLWB);
}

epiBool CPUDeviceX86::GetSSE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE);
}

epiBool CPUDeviceX86::GetSSE2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE2);
}

epiBool CPUDeviceX86::GetSSE3_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE3);
}

epiBool CPUDeviceX86::GetSSSE3_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSSE3);
}

epiBool CPUDeviceX86::GetSSE4_1_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE4_1);
}

epiBool CPUDeviceX86::GetSSE4_2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE4_2);
}

epiBool CPUDeviceX86::GetSSE4A_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SSE4A);
}

epiBool CPUDeviceX86::GetAVX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX);
}

epiBool CPUDeviceX86::GetAVX2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX2);
}

epiBool CPUDeviceX86::GetAVX512F_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512F);
}

epiBool CPUDeviceX86::GetAVX512CD_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512CD);
}

epiBool CPUDeviceX86::GetAVX512ER_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512ER);
}

epiBool CPUDeviceX86::GetAVX512PF_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512PF);
}

epiBool CPUDeviceX86::GetAVX512BW_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512BW);
}

epiBool CPUDeviceX86::GetAVX512DQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512DQ);
}

epiBool CPUDeviceX86::GetAVX512VL_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VL);
}

epiBool CPUDeviceX86::GetAVX512IFMA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512IFMA);
}

epiBool CPUDeviceX86::GetAVX512VBMI_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VBMI);
}

epiBool CPUDeviceX86::GetAVX512VBMI2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VBMI2);
}

epiBool CPUDeviceX86::GetAVX512VNNI_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VNNI);
}

epiBool CPUDeviceX86::GetAVX512BITALG_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512BITALG);
}

epiBool CPUDeviceX86::GetAVX512VPOPCNTDQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512VPOPCNTDQ);
}

epiBool CPUDeviceX86::GetAVX512_4VNNIW_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_4VNNIW);
}

epiBool CPUDeviceX86::GetAVX512_4VBMI2_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_4VBMI2);
}

epiBool CPUDeviceX86::GetAVX512_SECOND_FMA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_SECOND_FMA);
}

epiBool CPUDeviceX86::GetAVX512_4FMAPS_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_4FMAPS);
}

epiBool CPUDeviceX86::GetAVX512_BF16_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_BF16);
}

epiBool CPUDeviceX86::GetAVX512_VP2INTERSECT_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AVX512_VP2INTERSECT);
}

epiBool CPUDeviceX86::GetAMX_BF16_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AMX_BF16);
}

epiBool CPUDeviceX86::GetAMX_TILE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AMX_TILE);
}

epiBool CPUDeviceX86::GetAMX_INT8_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_AMX_INT8);
}

epiBool CPUDeviceX86::GetPCLMULQDQ_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_PCLMULQDQ);
}

epiBool CPUDeviceX86::GetSMX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SMX);
}

epiBool CPUDeviceX86::GetSGX_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SGX);
}

epiBool CPUDeviceX86::GetCX16_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_CX16);
}

epiBool CPUDeviceX86::GetSHA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SHA);
}

epiBool CPUDeviceX86::GetPOPCNT_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_POPCNT);
}

epiBool CPUDeviceX86::GetMOVBE_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_MOVBE);
}

epiBool CPUDeviceX86::GetRDRND_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_RDRND);
}

epiBool CPUDeviceX86::GetDCA_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_DCA);
}

epiBool CPUDeviceX86::GetSS_Callback() const
{
    return cpu_features::GetX86FeaturesEnumValue(&m_X86Info.features, cpu_features::X86_SS);
}

EPI_NAMESPACE_END()
