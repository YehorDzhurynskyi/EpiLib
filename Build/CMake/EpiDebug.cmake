function(epi_print_target_properties TGT)
    if(NOT TARGET ${TGT})
        message("There is no target named '${TGT}'")
        return()
    endif()

    execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)

    STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
    STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")

    foreach (PROP ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" PROP ${PROP})

        if(PROP STREQUAL "LOCATION" OR PROP MATCHES "^LOCATION_" OR PROP MATCHES "_LOCATION$")
            continue()
        endif()

        get_property(PROPVAL TARGET ${TGT} PROPERTY ${PROP} SET)

        if (PROPVAL)
            get_target_property(PROPVAL ${TGT} ${PROP})
            message ("${TGT} ${PROP} = ${PROPVAL}")
        endif()
    endforeach(PROP)
endfunction(epi_print_target_properties)
