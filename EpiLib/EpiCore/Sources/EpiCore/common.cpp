#include "EpiCore/common.h"

#ifdef EPI_BUILD_PROFILE
#include <easy/profiler.h>

profiler::color_t epiProfileColorOf(std::string name)
{
    profiler::color_t colors[] {
        profiler::colors::Amber,
        profiler::colors::Red,
        profiler::colors::Blue,
        profiler::colors::Magenta,
        profiler::colors::Pink,
        profiler::colors::Cyan,
        profiler::colors::Green,
        profiler::colors::Lime,
        profiler::colors::Brown800,
        profiler::colors::DeepOrange800,
        profiler::colors::DarkBlue,
        profiler::colors::DarkRed,
        profiler::colors::DarkGreen
    };

    const size_t hash = std::hash<std::string>()(name);
    return colors[hash % epiArrLen(colors)];
}
#endif
