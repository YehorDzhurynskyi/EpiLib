include(ExternalProject)

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif (POLICY CMP0077)

function(epi_extern_add EXTERN)
    cmake_parse_arguments(EXTERN
        "DONT_ADD_SUBDIRECTORY"
        ""
        "COMPONENTS"
        ${ARGN}
    )

    # TODO: check whether the dependency is already installed before compiling it from scratch

    set(EXTERN_DIR "${EPI_DIR}/Build/CMake/Extern/${EXTERN}")

    if (NOT EXISTS ${EXTERN_DIR})
        message(FATAL_ERROR "No directory exists for `${EXTERN}` target! `${EXTERN_DIR}` path is expected!")
    endif ()

    if (NOT EXISTS "${EXTERN_DIR}/CMakeLists.txt.in")
        message(FATAL_ERROR "No `CMakeLists.txt.in` file exists for `${EXTERN}` target! `${EXTERN_DIR}/CMakeLists.txt.in` path is expected!")
    endif ()

    configure_file("${EXTERN_DIR}/CMakeLists.txt.in" "${EXTERN}/CMakeLists.txt" @ONLY)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE COMMAND_STATUS
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}"
    )

    if (COMMAND_STATUS)
        message(FATAL_ERROR "CMake step for `${EXTERN}` has failed: ${COMMAND_STATUS}")
    endif ()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE COMMAND_STATUS
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}"
    )

    if (COMMAND_STATUS)
        message(FATAL_ERROR "Build step for `${EXTERN}` has failed: ${COMMAND_STATUS}")
    endif ()

    if (EXISTS "${EXTERN_DIR}/configure.cmake")
        include("${EXTERN_DIR}/configure.cmake")
    endif ()

    if (NOT EXTERN_DONT_ADD_SUBDIRECTORY)
        add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}/${EXTERN}/src"
                         "${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}/${EXTERN}/build"
                         EXCLUDE_FROM_ALL)
    endif ()

    if (EXISTS "${EXTERN_DIR}/target.cmake")
        include("${EXTERN_DIR}/target.cmake")
    endif ()

    list(LENGTH EXTERN_COMPONENTS EXTERN_COMPONENTS_LENGTH)
    if (NOT EXTERN_COMPONENTS_LENGTH EQUAL 0)
        if (TARGET ${EXTERN})
            message(FATAL_ERROR "`${EXTERN}` is already defined, but it's implied to be an interface library!")
        endif ()

        foreach (COMPONENT ${EXTERN_COMPONENTS})
            if (NOT TARGET ${COMPONENT})
                message(FATAL_ERROR "`${COMPONENT}` such component of `${EXTERN}` doesn't exists!")
            endif ()

            epi_module_register(${COMPONENT} EXTERN
                FOLDER "EpiLib/Extern"
            )
        endforeach ()

        add_library(${EXTERN} INTERFACE)
        target_link_libraries(${EXTERN}
            INTERFACE
                ${EXTERN_COMPONENTS}
        )
    endif ()

    epi_module_register(${EXTERN} EXTERN
        FOLDER "EpiLib/Extern"
    )
endfunction()
