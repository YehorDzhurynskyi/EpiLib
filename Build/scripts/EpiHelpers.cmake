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
        include("${EPI_BUILD_DIR}/scripts/${_script}")
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
