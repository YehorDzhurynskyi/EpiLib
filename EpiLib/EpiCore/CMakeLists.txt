project(EpiCore)

set(Epi_USE_METAPROPERTY_NAME ON CACHE BOOL "")

add_library(EpiCore
    Sources/EpiCore/epi_config.h.in

    Sources/EpiCore/types.h
    Sources/EpiCore/common.h
    Sources/EpiCore/common.cpp

    Sources/EpiCore/Clock.h
    Sources/EpiCore/Clock.cpp

    Sources/EpiCore/Color.epi
    Sources/EpiCore/Color.h
    Sources/EpiCore/Color.cpp

    Sources/EpiCore/Hash.h
    Sources/EpiCore/Hash.cpp

    Sources/EpiCore/epiBuildInfo.epi
    Sources/EpiCore/epiBuildInfo.h
    Sources/EpiCore/epiBuildInfo.cpp

    Sources/EpiCore/Platform/epiPlatform.epi
    Sources/EpiCore/Platform/epiPlatform.h
    Sources/EpiCore/Platform/epiPlatform.cpp
    Sources/EpiCore/Platform/epiDeviceDisplay.epi
    Sources/EpiCore/Platform/epiDeviceDisplay.h
    Sources/EpiCore/Platform/epiDeviceDisplay.cpp
    Sources/EpiCore/Platform/epiDeviceCPUBase.epi
    Sources/EpiCore/Platform/epiDeviceCPUBase.h
    Sources/EpiCore/Platform/epiDeviceCPUBase.cpp
    Sources/EpiCore/Platform/epiDeviceCPUX86.epi
    Sources/EpiCore/Platform/epiDeviceCPUX86.h
    Sources/EpiCore/Platform/epiDeviceCPUX86.cpp

    Sources/EpiCore/Expression.h
    Sources/EpiCore/Expression.cpp

    Sources/EpiCore/Singleton.h
    Sources/EpiCore/Pool.h
    Sources/EpiCore/RotatingBuffer.h

    Sources/EpiCore/Containers/Array.h
    Sources/EpiCore/Containers/HashMap.h

    Sources/EpiCore/ObjectModel/Serialization.h
    Sources/EpiCore/ObjectModel/Object.h
    Sources/EpiCore/ObjectModel/Object.cpp
    Sources/EpiCore/ObjectModel/MetaObject.h
    Sources/EpiCore/ObjectModel/MetaObject.cpp
    Sources/EpiCore/ObjectModel/PropertyPath.h
    Sources/EpiCore/ObjectModel/PropertyPath.cpp
    Sources/EpiCore/ObjectModel/PropertyPointer.h
    Sources/EpiCore/ObjectModel/PropertyPointer.cpp
    Sources/EpiCore/ObjectModel/epiPropertyGrouping.h
    Sources/EpiCore/ObjectModel/epiPropertyGrouping.cpp
    Sources/EpiCore/ObjectModel/epiIPropertyChangedHandler.h
    Sources/EpiCore/ObjectModel/epiIPropertyChangedHandler.cpp
    Sources/EpiCore/ObjectModel/Handle.h

    Sources/EpiCore/Event/EventBus.h
    Sources/EpiCore/Event/EventBus.cpp

    Sources/EpiCore/MT/JobSystem/epiJobScheduler.h
    Sources/EpiCore/MT/JobSystem/epiJobScheduler.cpp
    Sources/EpiCore/MT/JobSystem/epiIJob.epi
    Sources/EpiCore/MT/JobSystem/epiIJob.h
    Sources/EpiCore/MT/JobSystem/epiIJob.cpp
    Sources/EpiCore/MT/JobSystem/epiJobCallback.h
    Sources/EpiCore/MT/JobSystem/epiJobHandle.h
    Sources/EpiCore/MT/JobSystem/epiJobHandle.cpp
    Sources/EpiCore/MT/JobSystem/epiJobWorker.h
    Sources/EpiCore/MT/JobSystem/epiJobWorker.cpp

    Sources/EpiCore/MT/EventLoop/epiEventLoop.h
    Sources/EpiCore/MT/EventLoop/epiEventLoop.cpp
    Sources/EpiCore/MT/EventLoop/epiEventLoopPeriodicalTask.h
    Sources/EpiCore/MT/EventLoop/epiEventLoopPeriodicalTask.cpp

    Sources/EpiCore/CMD/epiCMDParser.h
    Sources/EpiCore/CMD/epiCMDParser.cpp
)

get_target_property(EpiCore_SOURCES EpiCore SOURCES)
epi_pack_sources(${EpiCore_SOURCES})

add_subdirectory(Extern/exprtk)
epi_module_register(exprtk EXTERN
    FOLDER "EpiLib/Extern"
)

epi_extern_add(spdlog)
epi_extern_add(nlohmann_json)
epi_extern_add(glm)
epi_extern_add(fmt)
epi_extern_add(cpu_features)
epi_extern_add(easy_profiler)

configure_file(Sources/EpiCore/epi_config.h.in Sources/EpiCore/epi_config.h)

if(MSVC)
    # needed for exprtk.hpp (probably?)
    # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/fatal-error-c1128?view=vs-2019
    set_target_properties(EpiCore PROPERTIES COMPILE_FLAGS "/bigobj" )
endif()

target_precompile_headers(EpiCore
    PUBLIC
        <vector>
        <algorithm>
        <map>
        <memory>
        <set>
        <array>
        <cmath>
        <cassert>
        <cstdint>
        <functional>
        <type_traits>
        <thread>
        <mutex>
        <condition_variable>
        <atomic>
        <future>

        [["EpiCore/epi_config.h"]]
        [["EpiCore/types.h"]]
        [["EpiCore/Hash.h"]]
        [["EpiCore/common.h"]]
        [["EpiCore/ObjectModel/Serialization.h"]]
        [["EpiCore/ObjectModel/MetaObject.h"]]
        [["EpiCore/Containers/Array.h"]]
)

target_compile_definitions(EpiCore
    PUBLIC
        $<$<CONFIG:Debug>:EPI_BUILD_DEBUG>
        $<$<CONFIG:Release>:EPI_BUILD_RELEASE>
        $<$<CONFIG:Profile>:EPI_BUILD_PROFILE>
)

target_include_directories(EpiCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiCore
    PUBLIC
        spdlog
        nlohmann_json
        glm
        fmt
        cpu_features
        $<$<CONFIG:Profile>:easy_profiler>
        exprtk
)

if (Epi_USE_METAPROPERTY_NAME)
    target_compile_definitions(EpiCore
        PUBLIC
            epiUSE_METAPROPERTY_NAME
    )
endif()

target_compile_definitions(EpiCore
    PUBLIC
        _USE_MATH_DEFINES 
)

epi_module_register(EpiCore
    FOLDER "EpiLib"
)
