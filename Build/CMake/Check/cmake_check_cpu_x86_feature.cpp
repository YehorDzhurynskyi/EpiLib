#include <cpu_features/cpuinfo_x86.h>

#define CAT_EX(A, B) A ## B
#define CAT(A, B) CAT_EX(A, B)
#define FEATURE CAT(cpu_features::X86_, EPI_CPU_X86_FEATURE)

int main()
{
    cpu_features::X86Info info = cpu_features::GetX86Info();
    return cpu_features::GetX86FeaturesEnumValue(&info.features, FEATURE) ? 1 : 0;
}
