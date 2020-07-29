# https://blog.kangz.net/posts/2016/05/26/integrating-a-code-generator-with-cmake/

function(epi_run_epigen)

    find_package(Python3 COMPONENTS Interpreter)

    file(RELATIVE_PATH BINARY_DIR ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

    list(APPEND EPIGEN_IGNORE_LIST "*/${BINARY_DIR}/*")
    list(APPEND EPIGEN_IGNORE_LIST "*/EpiCodeGenerator/tests/*")
    list(APPEND EPIGEN_IGNORE_LIST "*.git*")

    if (NOT Python3_EXECUTABLE)
        message(FATAL_ERROR "[EPIGEN] Python3 interpreter hasn't found")
        return()
    endif()

    message(STATUS "[EPIGEN] Python version is ${Python3_VERSION}")

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -m pip install ${EPI_DIR}/Tools/EpiCodeGenerator
        RESULT_VARIABLE RETURN_VALUE
    )

    if (NOT RETURN_VALUE EQUAL 0)
        message(FATAL_ERROR "[EPIGEN] Failed to setup EpiCodeGenerator")
        return()
    endif()

    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun.py -i ${CMAKE_SOURCE_DIR}/BloodSystem --print-dependencies --ignore-list ${EPIGEN_IGNORE_LIST}
        OUTPUT_VARIABLE DEPENDENCIES
        RESULT_VARIABLE RETURN_VALUE
    )

    if (NOT RETURN_VALUE EQUAL 0)
        message(FATAL_ERROR "[EPIGEN] Failed to get dependencies")
        return()
    endif()

#    execute_process(
#        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun.py -i ${CMAKE_SOURCE_DIR}/BloodSystem --print-outputs --ignore-list ${EPIGEN_IGNORE_LIST}
#        OUTPUT_VARIABLE OUTPUTS
#        RESULT_VARIABLE RETURN_VALUE
#    )

#    if (NOT RETURN_VALUE EQUAL 0)
#        message(FATAL_ERROR "[EPIGEN] Failed to get outputs")
#        return()
#    endif()

    set(EPIGEN_MANIFEST_NAME "epigen-manifest.json")
    get_property(EPIGEN_MANIFEST_MODULES GLOBAL PROPERTY EPIGEN_MANIFEST_MODULES)

    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun-generate-manifest.py -o ${CMAKE_BINARY_DIR}/BloodSystem --modules ${EPIGEN_MANIFEST_MODULES} --name ${EPIGEN_MANIFEST_NAME}
        RESULT_VARIABLE RETURN_VALUE
    )

    if (NOT RETURN_VALUE EQUAL 0)
        message(FATAL_ERROR "[EPIGEN] Failed to generate the manifest")
        return()
    endif()

    add_custom_target(epigen
        ALL
        DEPENDS ${DEPENDENCIES}
        COMMENT "[EPIGEN] Generation done"
        #SOURCES ${OUTPUTS} ${DEPENDENCIES}
    )

    add_custom_command(TARGET epigen
        PRE_BUILD
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun.py -i ${CMAKE_SOURCE_DIR}/BloodSystem -m ${CMAKE_BINARY_DIR}/BloodSystem/${EPIGEN_MANIFEST_NAME} --dir-output-build ${CMAKE_BINARY_DIR}/BloodSystem --debug --ignore-list ${EPIGEN_IGNORE_LIST}
    )

endfunction()
