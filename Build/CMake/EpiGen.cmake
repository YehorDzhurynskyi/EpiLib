# https://blog.kangz.net/posts/2016/05/26/integrating-a-code-generator-with-cmake/

function(epi_run_epigen)

    find_package(Python3 COMPONENTS Interpreter)

    file(RELATIVE_PATH BINARY_DIR ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

    list(APPEND IGNORE_LIST "*/${BINARY_DIR}/*")
    list(APPEND IGNORE_LIST "*/EpiCodeGenerator/test/*")
    list(APPEND IGNORE_LIST "*.git*")

    if (NOT Python3_EXECUTABLE)
        message(FATAL_ERROR "[EPIGEN] Python3 interpreter not found")
        return()
    endif()

    execute_process(
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigen.py -i ${CMAKE_SOURCE_DIR}/BloodSystem --print-dependencies --ignore ${IGNORE_LIST}
        OUTPUT_VARIABLE DEPENDENCIES
        RESULT_VARIABLE RETURN_VALUE
    )

    if (NOT RETURN_VALUE EQUAL 0)
        message(FATAL_ERROR "[EPIGEN] Failed to get the dependencies on: ${CMD}")
        return()
    endif()

#    execute_process(
#        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigen.py -i ${CMAKE_SOURCE_DIR}/BloodSystem --print-outputs --ignore ${IGNORE_LIST}
#        OUTPUT_VARIABLE OUTPUTS
#        RESULT_VARIABLE RETURN_VALUE
#    )

#    if (NOT RETURN_VALUE EQUAL 0)
#        message(FATAL_ERROR "[EPIGEN] Failed to get the outputs on: ${CMD}")
#        return()
#    endif()

    add_custom_target(epigen
        ALL
        DEPENDS ${DEPENDENCIES}
        COMMENT "[EPIGEN] Generation done"
        #SOURCES ${OUTPUTS} ${DEPENDENCIES}
    )

    add_custom_command(TARGET epigen
        PRE_BUILD
        COMMAND ${Python3_EXECUTABLE} ${EPI_DIR}/Tools/EpiCodeGenerator/epigen.py -i ${CMAKE_SOURCE_DIR}/BloodSystem --output-dir-cxx-hxx ${CMAKE_BINARY_DIR}/BloodSystem --debug --nobackup --ignore ${IGNORE_LIST}
    )

endfunction()
