cmake_minimum_required(VERSION 3.1)

project(EpiLib VERSION 1.0.0)

set(Epi_USE_QT ON CACHE BOOL "")
set(Epi_USE_METAPROPERTY_NAME ON CACHE BOOL "")

set(CMAKE_AUTOMOC ON CACHE BOOL "" FORCE)
set(CMAKE_AUTORCC ON CACHE BOOL "" FORCE)
set(CMAKE_AUTOUIC ON CACHE BOOL "" FORCE)

mark_as_advanced(CMAKE_AUTOMOC)
mark_as_advanced(CMAKE_AUTORCC)
mark_as_advanced(CMAKE_AUTOUIC)

if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_library(EpiLib STATIC
    EpiLib/pch.h
    EpiLib/pch.cpp

    EpiLib/types.h
    EpiLib/env.h
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

    EpiLib/Debug/FiniteFloating.h

    EpiLib/Containers/Array.h
    EpiLib/Containers/HashMap.h

    EpiLib/ObjectModel/Serialization.h
    EpiLib/ObjectModel/Object.h
    EpiLib/ObjectModel/Object.cpp
    EpiLib/ObjectModel/MetaObject.h
    EpiLib/ObjectModel/MetaObject.cpp
    EpiLib/ObjectModel/ClassRegistry.h
    EpiLib/ObjectModel/ClassRegistry.cpp
    EpiLib/ObjectModel/PropertyPath.h
    EpiLib/ObjectModel/PropertyPath.cpp
    EpiLib/ObjectModel/Handle.h

    EpiLib/ObjectModel/QtAdaptors/QtObjectModel.h
    EpiLib/ObjectModel/QtAdaptors/QtObjectModel.cpp
    EpiLib/ObjectModel/QtAdaptors/QtObjectDelegate.h
    EpiLib/ObjectModel/QtAdaptors/QtObjectDelegate.cpp
    EpiLib/ObjectModel/QtAdaptors/QtObjectModelItem.h
    EpiLib/ObjectModel/QtAdaptors/QtObjectModelItem.cpp
    EpiLib/ObjectModel/QtAdaptors/QtEpiPropertyBrowser.h
    EpiLib/ObjectModel/QtAdaptors/QtEpiPropertyBrowser.cpp
    EpiLib/ObjectModel/QtAdaptors/QtEpiPropertyManager.h
    EpiLib/ObjectModel/QtAdaptors/QtEpiPropertyManager.cpp
)
get_target_property(EpiLib_SRCs EpiLib SOURCES)
epi_add_precompiled_header(EpiLib EpiLib/pch.h SOURCE_CXX EpiLib/pch.cpp)
epi_pack_sources(${EpiLib_SRCs})

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

target_compile_definitions(EpiLib
    PUBLIC
        _USE_MATH_DEFINES
)

if (Epi_USE_QT)
    find_package(Qt5 COMPONENTS Core REQUIRED)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    target_compile_definitions(EpiLib
        PUBLIC
            epiUSE_QT
    )
endif()

add_subdirectory(Extern/nlohmann)
add_subdirectory(Extern/glm)
add_subdirectory(Extern/exprtk)
add_subdirectory(Extern/QtPropertyBrowser)

target_link_libraries(EpiLib
    PUBLIC
        glm
        exprtk
        nlohmann
        QtPropertyBrowser
        Qt5::Core
        Qt5::Widgets
)

set_target_properties(
    glm
    QtPropertyBrowser

    PROPERTIES
        FOLDER Extern
)

if (Epi_USE_METAPROPERTY_NAME)
    target_compile_definitions(EpiLib
        PUBLIC
            epiUSE_METAPROPERTY_NAME
    )
endif()

set_target_properties(EpiLib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
