#include <stdio.h>

#include <cpu_features/cpuinfo_x86.h>

int main()
{
    cpu_features::X86Info info = cpu_features::GetX86Info();

    switch (cpu_features::GetX86Microarchitecture(&info))
    {
    case cpu_features::INTEL_CORE: printf("INTEL_CORE"); break;
    case cpu_features::INTEL_PNR: printf("INTEL_PENRYN"); break;
    case cpu_features::INTEL_NHM: printf("INTEL_NEHALEM"); break;
    case cpu_features::INTEL_ATOM_BNL: printf("INTEL_ATOMBONNELL"); break;
    case cpu_features::INTEL_WSM: printf("INTEL_WESTMERE"); break;
    case cpu_features::INTEL_SNB: printf("INTEL_SANDYBRIDGE"); break;
    case cpu_features::INTEL_IVB: printf("INTEL_IVYBRIDGE"); break;
    case cpu_features::INTEL_ATOM_SMT: printf("INTEL_ATOMSILVERMONT"); break;
    case cpu_features::INTEL_HSW: printf("INTEL_HASWELL"); break;
    case cpu_features::INTEL_BDW: printf("INTEL_BROADWELL"); break;
    case cpu_features::INTEL_SKL: printf("INTEL_SKYLAKE"); break;
    case cpu_features::INTEL_ATOM_GMT: printf("INTEL_ATOMGOLDMONT"); break;
    case cpu_features::INTEL_KBL: printf("INTEL_KABYLAKE"); break;
    case cpu_features::INTEL_CFL: printf("INTEL_COFFEELAKE"); break;
    case cpu_features::INTEL_WHL: printf("INTEL_WHISKEYLAKE"); break;
    case cpu_features::INTEL_CNL: printf("INTEL_CANNONLAKE"); break;
    case cpu_features::INTEL_ICL: printf("INTEL_ICELAKE"); break;
    case cpu_features::INTEL_TGL: printf("INTEL_TIGERLAKE"); break;
    case cpu_features::INTEL_SPR: printf("INTEL_SAPPHIRERAPIDS"); break;
    case cpu_features::AMD_HAMMER: printf("AMD_HAMMER"); break;
    case cpu_features::AMD_K10: printf("AMD_K10"); break;
    case cpu_features::AMD_BOBCAT: printf("AMD_BOBCAT"); break;
    case cpu_features::AMD_BULLDOZER: printf("AMD_BULLDOZER"); break;
    case cpu_features::AMD_JAGUAR: printf("AMD_JAGUAR"); break;
    case cpu_features::AMD_ZEN: printf("AMD_ZEN"); break;
    case cpu_features::X86_UNKNOWN:
    default:  printf("Unknown"); break;
    }

    return 0;
}
