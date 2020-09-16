project(EpiCore)

set(Epi_USE_METAPROPERTY_NAME ON CACHE BOOL "")

add_library(EpiCore
    Sources/EpiCore/epi_config.h.in

    Sources/EpiCore/types.h
    Sources/EpiCore/common.h

    Sources/EpiCore/Clock.h
    Sources/EpiCore/Clock.cpp

    Sources/EpiCore/Color.epi
    Sources/EpiCore/Color.h
    Sources/EpiCore/Color.cpp

    Sources/EpiCore/Hash.h
    Sources/EpiCore/Hash.cpp

    Sources/EpiCore/Platform/DisplayDevice.epi
    Sources/EpiCore/Platform/DisplayDevice.h
    Sources/EpiCore/Platform/DisplayDevice.cpp

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
    Sources/EpiCore/ObjectModel/Handle.h

    Sources/EpiCore/Event/EventBus.h
    Sources/EpiCore/Event/EventBus.cpp
)

get_target_property(EpiCore_SOURCES EpiCore SOURCES)
epi_pack_sources(${EpiCore_SOURCES})

add_subdirectory(Extern/exprtk)
epi_module_register(exprtk EXTERN
    FOLDER "EpiLib/Extern"
)

epi_extern_add(nlohmann_json)
epi_extern_add(glm)
epi_extern_add(fmt)

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
        [["EpiCore/common.h"]]
        [["EpiCore/Hash.h"]]
        [["EpiCore/ObjectModel/Serialization.h"]]
        [["EpiCore/ObjectModel/MetaObject.h"]]
        [["EpiCore/Containers/Array.h"]]
)

target_include_directories(EpiCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiCore
    PUBLIC
        nlohmann_json
        glm
        fmt
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
