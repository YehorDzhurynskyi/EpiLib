cmake_minimum_required(VERSION 3.1)

project(EpiLib VERSION 1.0.0)

fbl_status_message("Configuring EpiSys")

fbl_include_script(PrecompiledHeader.cmake)

add_subdirectory(Extern/rapidjson)
find_package(RapidJSON REQUIRED)

add_subdirectory(Extern/glm)
add_subdirectory(Extern/exprtk)

set(EpiLib_SRCS

    EpiLib/pch.h
    EpiLib/pch.cpp

    EpiLib/types.h
    EpiLib/common.h

    EpiLib/Clock.h
    EpiLib/Clock.cpp

    EpiLib/Hash.h
    EpiLib/Hash.cpp

    EpiLib/Expression.h
    EpiLib/Expression.cpp

    EpiLib/Singleton.h
    EpiLib/Pool.h
    EpiLib/RotatingBuffer.h

	EpiLib/Containers/Array.h
	EpiLib/Containers/HashMap.h

    EpiLib/ObjectModel/Object.h
    EpiLib/ObjectModel/Object.cpp
	EpiLib/ObjectModel/MetaObject.h
	EpiLib/ObjectModel/MetaObject.cpp
    EpiLib/ObjectModel/ClassRegistry.h
	EpiLib/ObjectModel/ClassRegistry.cpp
    EpiLib/ObjectModel/PropertyPath.h
	EpiLib/ObjectModel/PropertyPath.cpp
	EpiLib/ObjectModel/Handle.h
)

add_library(EpiLib ${EpiLib_SRCS})
add_precompiled_header(EpiLib EpiLib/pch.h SOURCE_CXX EpiLib/pch.cpp)

if(MSVC)
	# needed for exprtk.hpp (probably?)
	# https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/fatal-error-c1128?view=vs-2019
	set_target_properties(EpiLib PROPERTIES COMPILE_FLAGS "/bigobj" )
endif()

target_include_directories(EpiLib
    PUBLIC
        ${RapidJSON_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

fbl_pack_sources(${EpiLib_SRCS})

target_link_libraries(EpiLib
    PUBLIC
        glm
		exprtk
)

target_compile_definitions(EpiLib
    PUBLIC
        _USE_MATH_DEFINES
)

fbl_set_default_target_properties(EpiLib)
