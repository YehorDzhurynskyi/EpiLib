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
    
    set(EPIGEN_INPUT_DIR "${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}")
    set(EPIGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}")
    set(EPIGEN_MANIFEST_NAME "epigen-manifest.json")
    get_property(EPIGEN_MANIFEST_MODULES GLOBAL PROPERTY EPIGEN_MANIFEST_MODULES)

    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun.py -i ${EPIGEN_INPUT_DIR} --print-dependencies --ignore-list ${EPIGEN_IGNORE_LIST}
        OUTPUT_VARIABLE EPIGEN_DEPENDENCIES
        RESULT_VARIABLE RETURN_VALUE
    )

    if (NOT RETURN_VALUE EQUAL 0)
        message(FATAL_ERROR "[EPIGEN] Failed to get dependencies")
        return()
    endif()

#    execute_process(
#        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun.py -i ${EPIGEN_INPUT_DIR} --print-outputs --ignore-list ${EPIGEN_IGNORE_LIST}
#        OUTPUT_VARIABLE OUTPUTS
#        RESULT_VARIABLE RETURN_VALUE
#    )

#    if (NOT RETURN_VALUE EQUAL 0)
#        message(FATAL_ERROR "[EPIGEN] Failed to get outputs")
#        return()
#    endif()

    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun-generate-manifest.py -o ${EPIGEN_OUTPUT_DIR} --modules ${EPIGEN_MANIFEST_MODULES} --name ${EPIGEN_MANIFEST_NAME}
        RESULT_VARIABLE RETURN_VALUE
    )

    if (NOT RETURN_VALUE EQUAL 0)
        message(FATAL_ERROR "[EPIGEN] Failed to generate the manifest")
        return()
    endif()

    add_custom_target(epigen
        ALL
        DEPENDS ${EPIGEN_DEPENDENCIES}
        COMMENT "[EPIGEN] Generation done"
        #SOURCES ${OUTPUTS} ${EPIGEN_DEPENDENCIES}
    )

    add_custom_command(TARGET epigen
        PRE_BUILD
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigenrun.py -i ${EPIGEN_INPUT_DIR} -m ${EPIGEN_OUTPUT_DIR}/${EPIGEN_MANIFEST_NAME} --dir-output-build ${EPIGEN_OUTPUT_DIR} --debug --ignore-list ${EPIGEN_IGNORE_LIST}
    )

endfunction()
