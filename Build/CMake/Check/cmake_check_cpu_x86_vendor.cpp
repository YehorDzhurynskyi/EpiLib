#include <stdio.h>

#include <cpu_features/cpuinfo_x86.h>

int main()
{
    cpu_features::X86Info info = cpu_features::GetX86Info();
    printf("%s", info.vendor);

    return 0;
}
