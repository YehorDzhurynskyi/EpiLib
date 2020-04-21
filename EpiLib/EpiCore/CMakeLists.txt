project(EpiCore)

set(Epi_USE_METAPROPERTY_NAME ON CACHE BOOL "")

add_library(EpiCore
    EpiCore/epi_config.h.in

    EpiCore/pch.h
    EpiCore/pch.cpp

    EpiCore/types.h
    EpiCore/common.h

    EpiCore/Clock.h
    EpiCore/Clock.cpp

    EpiCore/Color.epi
    EpiCore/Color.h
    EpiCore/Color.cpp

    EpiCore/Hash.h
    EpiCore/Hash.cpp

    EpiCore/Platform/DisplayDevice.epi
    EpiCore/Platform/DisplayDevice.h
    EpiCore/Platform/DisplayDevice.cpp

    EpiCore/Expression.h
    EpiCore/Expression.cpp

    EpiCore/Singleton.h
    EpiCore/Pool.h
    EpiCore/RotatingBuffer.h

    EpiCore/Containers/Array.h
    EpiCore/Containers/HashMap.h

    EpiCore/ObjectModel/Serialization.h
    EpiCore/ObjectModel/Object.h
    EpiCore/ObjectModel/Object.cpp
    EpiCore/ObjectModel/MetaObject.h
    EpiCore/ObjectModel/MetaObject.cpp
    EpiCore/ObjectModel/PropertyPath.h
    EpiCore/ObjectModel/PropertyPath.cpp
    EpiCore/ObjectModel/PropertyPointer.h
    EpiCore/ObjectModel/PropertyPointer.cpp
    EpiCore/ObjectModel/Handle.h
)
get_target_property(EpiCore_SRCs EpiCore SOURCES)
epi_add_precompiled_header(EpiCore EpiCore/pch.h SOURCE_CXX EpiCore/pch.cpp)
epi_pack_sources(${EpiCore_SRCs})

add_subdirectory(Extern/exprtk)
epi_extern_register(exprtk)

epi_extern_add(nlohmann_json)
epi_extern_add(glm)

configure_file(EpiCore/epi_config.h.in EpiCore/epi_config.h)

if(MSVC)
    # needed for exprtk.hpp (probably?)
    # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/fatal-error-c1128?view=vs-2019
    set_target_properties(EpiCore PROPERTIES COMPILE_FLAGS "/bigobj" )
endif()

target_include_directories(EpiCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiCore
    PUBLIC
        nlohmann_json
        glm
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

epi_module_register(EpiCore)
