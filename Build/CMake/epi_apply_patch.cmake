function(epi_apply_patch)
    cmake_parse_arguments(ARG
        ""
        "WORKING_DIRECTORY"
        "PATCHES"
        ${ARGN}
    )

    if(DEFINED ARG_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "epi_apply_patch was passed extra arguments: ${ARG_UNPARSED_ARGUMENTS}")
    endif()

    find_package(Git REQUIRED)
    if(DEFINED ENV{GIT_CONFIG_NOSYSTEM})
        set(GIT_CONFIG_NOSYSTEM_BACKUP "$ENV{GIT_CONFIG_NOSYSTEM}")
    else()
        unset(GIT_CONFIG_NOSYSTEM_BACKUP)
    endif()

    set(ENV{GIT_CONFIG_NOSYSTEM} 1)
    foreach(PATCH IN LISTS ARG_PATCHES)
        message(STATUS "Applying patch `${PATCH}`")

        execute_process(COMMAND "${GIT_EXECUTABLE}" -c core.longpaths=true -c core.autocrlf=false --work-tree=. --git-dir=.git apply "${PATCH}" --ignore-whitespace --whitespace=nowarn --verbose
            RESULT_VARIABLE COMMAND_STATUS
            WORKING_DIRECTORY ${ARG_WORKING_DIRECTORY}
        )

        if (COMMAND_STATUS)
            message(FATAL_ERROR "Applying patch `${PATCH}` has failed: ${COMMAND_STATUS}")
        endif()
    endforeach()

    if(DEFINED GIT_CONFIG_NOSYSTEM_BACKUP)
        set(ENV{GIT_CONFIG_NOSYSTEM} "${GIT_CONFIG_NOSYSTEM_BACKUP}")
    else()
        unset(ENV{GIT_CONFIG_NOSYSTEM})
    endif()
endfunction()
