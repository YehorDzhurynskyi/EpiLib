cmake_minimum_required(VERSION 3.1)

project(EpiLib)

set(Epi_USE_QT ON CACHE BOOL "")

add_subdirectory(EpiLib/EpiCore)
#add_subdirectory(EpiLib/EpiMultiMedia)

if (Epi_USE_QT)
    set(CMAKE_AUTOMOC ON CACHE BOOL "" FORCE)
    set(CMAKE_AUTORCC ON CACHE BOOL "" FORCE)
    set(CMAKE_AUTOUIC ON CACHE BOOL "" FORCE)

    mark_as_advanced(CMAKE_AUTOMOC)
    mark_as_advanced(CMAKE_AUTORCC)
    mark_as_advanced(CMAKE_AUTOUIC)

    if (CMAKE_VERSION VERSION_LESS "3.7.0")
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
    endif()

    add_subdirectory(EpiLib/EpiAdapterQt)
endif()
