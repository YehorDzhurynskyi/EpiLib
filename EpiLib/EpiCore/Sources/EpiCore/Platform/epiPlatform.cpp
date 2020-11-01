EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/epiPlatform.h"
#include "EpiCore/Platform/epiPlatform.cxx"
EPI_GENREGION_END(include)

#ifdef EPI_CPU_X86
#include "EpiCore/Platform/epiDeviceCPUX86.h";
#endif // EPI_CPU_X86

EPI_NAMESPACE_BEGIN()

epiPlatform::epiPlatform()
    : EPI_CPU_X86_ONLY(m_DeviceCPU{new epiDeviceCPUX86()})
{
}

EPI_NAMESPACE_END()
