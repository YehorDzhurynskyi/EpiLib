function(epi_pack_sources)
    if(NOT MSVC OR NOT WIN32)
        message(FATAL_ERROR "This function doesn't support selected platform, it's necessary replace slashes by back-slashes only on WIN platform")
    endif()
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction()

function(epi_include_script)
    foreach(_script IN ITEMS ${ARGN})
        include("${EPI_BUILD_DIR}/Scripts/CMake/${_script}")
    endforeach()
endfunction()

function(epi_status_message _message)
    message(STATUS "**********************[EPI][STATUS] ${_message}")
endfunction()

function(epi_fatal_message _message)
    message(FATAL_ERROR "**********************[EPI][FATAL ERROR] ${_message}")
endfunction()

epi_include_script(PrecompiledHeader.cmake)

function(epi_add_precompiled_header)
    add_precompiled_header(${ARGV})
endfunction()

function(epi_set_common_target_properties _target)
    set_target_properties(${_target}
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            FOLDER EpiLib
    )
endfunction()

function(epi_register_extern_target _target)
    get_target_property(TargetType ${_target} TYPE)
    
    if (NOT ${TargetType} STREQUAL "INTERFACE_LIBRARY")
        set_target_properties(${_target}
            PROPERTIES
                FOLDER Extern
        )
    endif()
endfunction()

include(ExternalProject)

if (NOT GIT_EXECUTABLE)
    find_program(EPI_GIT_EXECUTABLE
        NAMES "bash-git.bat"
        PATHS "${EPI_BUILD_DIR}/Scripts/"
    )
else()
    set(EPI_GIT_EXECUTABLE ${GIT_EXECUTABLE})
endif()

macro(epi_win_to_unix_path winpath unixpath)
    string(REGEX REPLACE "^([a-zA-Z]):/" "/\\1/" temp ${winpath})
    string(TOLOWER ${temp} ${unixpath})
endmacro()

macro(epi_win_to_wsl_unix_path winpath wslunixpath)
    epi_win_to_unix_path(${winpath} unixpath)
    set(${wslunixpath} "/mnt${unixpath}")
endmacro()

function(epi_print_target_properties tgt)
    if(NOT TARGET ${tgt})
        message("There is no target named '${tgt}'")
        return()
    endif()

    execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)

    STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
    STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")

    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})

        if(prop STREQUAL "LOCATION" OR prop MATCHES "^LOCATION_" OR prop MATCHES "_LOCATION$")
            continue()
        endif()

        get_property(propval TARGET ${tgt} PROPERTY ${prop} SET)

        if (propval)
            get_target_property(propval ${tgt} ${prop})
            message ("${tgt} ${prop} = ${propval}")
        endif()
    endforeach(prop)
endfunction(epi_print_target_properties)

macro(epi_get_libname libname out_static_libname out_dynamic_libname libversion)
    if(APPLE)
        set(${out_static_libname} "lib${libname}.a")
        if (NOT ${libversion})
            set(${out_dynamic_libname} "lib${libname}.dylib")
        else()
            set(${out_dynamic_libname} "lib${libname}.${libversion}.dylib")
        endif()
    elseif(UNIX)
        set(${out_static_libname} "lib${libname}.a")
        if (NOT ${libversion})
            set(${out_dynamic_libname} "lib${libname}.so")
        else()
            set(${out_dynamic_libname} "lib${libname}.so.${libversion}")
        endif()
    elseif(WIN32)
        set(${out_static_libname} "${libname}.lib")
        if (NOT ${libversion})
            set(${out_dynamic_libname} "${libname}.dll")
        else()
            set(${out_dynamic_libname} "${libname}-${libversion}.dll")
        endif()
    else()
        message(FATAL_ERROR "EpiHelpers.cmake: Unsupported platform, couldn't get lib name")
    endif()
endmacro()
