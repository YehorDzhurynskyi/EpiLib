include(ExternalProject)

# if (NOT GIT_EXECUTABLE)
#     find_program(GIT_EXECUTABLE
#         NAMES "bash-git.bat"
#         PATHS "${EPI_BUILD_DIR}/"
#     )
# endif()

function(epi_extern_register _extern)

    get_target_property(TargetType ${_extern} TYPE)
    
    if (NOT ${TargetType} STREQUAL "INTERFACE_LIBRARY")
        set_target_properties(${_extern}
            PROPERTIES
                FOLDER Extern
        )
    endif()

endfunction()

function(epi_extern_add _extern)

    configure_file("${EPI_BUILD_DIR}/Extern/${_extern}_Extern.txt.in" "${_extern}-download/CMakeLists.txt")

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
      RESULT_VARIABLE result WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${_extern}-download")
    if(result)
      message(FATAL_ERROR "CMake step for ${_extern} failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${_extern}-download )

    if(result)
      message(FATAL_ERROR "Build step for ${_extern} failed: ${result}")
    endif()

    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/${_extern}-src
                     ${CMAKE_CURRENT_BINARY_DIR}/${_extern}-build
                     EXCLUDE_FROM_ALL)

    epi_extern_register(${_extern})

endfunction()