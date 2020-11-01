EPI_GENREGION_BEGIN(include)
#include "EpiCore/epiBuildInfo.h"
#include "EpiCore/epiBuildInfo.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/Platform/epiPlatform.h"

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

epiString epiBuildInfo::ToString() const
{
    epiString str;
    str.reserve(8192);

    str = "Build Info:\n";

    str += "\tPlatform: ";

#if defined(EPI_PLATFORM_WINDOWS)
    str += "Windows\n";
#endif

    str += "\tBuild Configuration: ";

#if defined(EPI_BUILD_DEBUG)
    str += "Debug\n";
#elif defined(EPI_BUILD_RELEASE)
    str += "Release\n";
#endif

    if (const epiDeviceCPUBase* cpu = epiPlatform::GetInstance().GetDeviceCPU())
    {
        str += PrependWith("CPU Info:\n" + PrependWith(cpu->ToString(), "\t"), "\t");
    }

    return str;
}

EPI_NAMESPACE_END()
