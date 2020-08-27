include(ExternalProject)

function(epi_extern_add EXTERN)
    cmake_parse_arguments(EXTERN
        ""
        ""
        "COMPONENTS"
        ${ARGN}
    )

    set(EXTERN_DIR "${EPI_DIR}/Build/CMake/Extern/${EXTERN}")

    if (NOT EXISTS ${EXTERN_DIR})
        message(FATAL_ERROR "No directory exists for `${EXTERN}` target! `${EXTERN_DIR}` path is expected!")
    endif ()

    if (NOT EXISTS "${EXTERN_DIR}/CMakeLists.txt.in")
        message(FATAL_ERROR "No `CMakeLists.txt.in` file exists for `${EXTERN}` target! `${EXTERN_DIR}/CMakeLists.txt.in` path is expected!")
    endif ()

    configure_file("${EXTERN_DIR}/CMakeLists.txt.in" "${EXTERN}/CMakeLists.txt")

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE COMMAND_STATUS
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}"
    )

    if(COMMAND_STATUS)
        message(FATAL_ERROR "CMake step for `${EXTERN}` has failed: ${COMMAND_STATUS}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE COMMAND_STATUS
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}"
    )

    if(COMMAND_STATUS)
        message(FATAL_ERROR "Build step for `${EXTERN}` has failed: ${COMMAND_STATUS}")
    endif()

    if (EXISTS "${EXTERN_DIR}/config.cmake")
        include("${EXTERN_DIR}/config.cmake")
    endif ()

    add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}/src"
                     "${CMAKE_CURRENT_BINARY_DIR}/${EXTERN}/build"
                     EXCLUDE_FROM_ALL)
 
    list(LENGTH EXTERN_COMPONENTS EXTERN_COMPONENTS_LENGTH)
    if (NOT EXTERN_COMPONENTS_LENGTH EQUAL 0)
        if (TARGET ${EXTERN})
            message(FATAL_ERROR "`${EXTERN}` is already defined, but it's implied to be an interface library!")
        endif ()

        foreach (COMPONENT ${EXTERN_COMPONENTS})
            if (NOT TARGET ${COMPONENT})
                message(FATAL_ERROR "`${COMPONENT}` such component of `${EXTERN}` doesn't exists!")
            endif ()

            epi_module_register(${COMPONENT}
                FOLDER "EpiLib/Extern"
            )
        endforeach ()

        add_library(${EXTERN} INTERFACE)
        target_link_libraries(${EXTERN}
            INTERFACE
                ${EXTERN_COMPONENTS}
        )
    endif ()

    epi_module_register(${EXTERN}
        FOLDER "EpiLib/Extern"
    )
endfunction()
