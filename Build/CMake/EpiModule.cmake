function(epi_pack_sources)
    if(NOT MSVC OR NOT WIN32)
        message(WARNING "This function doesn't support selected platform, it's necessary replace slashes by back-slashes only on WIN platform")
        return ()
    endif()

    foreach (SOURCE IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${SOURCE}")
            file(RELATIVE_PATH SOURCE_REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${SOURCE}")
        else ()
            set(SOURCE_REL_PATH "${SOURCE}")
        endif ()
        get_filename_component(SOURCE_PATH "${SOURCE_REL_PATH}" PATH)
        string(REPLACE "/" "\\" SOURCE_PATH_MSVC "${SOURCE_PATH}")
        source_group("${SOURCE_PATH_MSVC}" FILES "${SOURCE}")
    endforeach ()
endfunction()

function(epi_module_register EPIMODULE)
    cmake_parse_arguments(EPIMODULE
        "EXTERN"
        "FOLDER"
        ""
        ${ARGN}
    )

    if (NOT TARGET ${EPIMODULE})
        message(FATAL_ERROR "`${EPIMODULE}` is not defined!")
    endif ()

    get_target_property(EPIMODULE_ALIASED_TARGET ${EPIMODULE} ALIASED_TARGET)
    if (EPIMODULE_ALIASED_TARGET)
        set(EPIMODULE ${EPIMODULE_ALIASED_TARGET})
    endif ()

    get_target_property(EPIMODULE_TYPE ${EPIMODULE} TYPE)

    # TODO: finish recursive extern registering
    # if (NOT ${EPIMODULE_TYPE} STREQUAL "INTERFACE_LIBRARY")
    #     get_target_property(EPIMODULE_LINK_LIBRARIES ${EPIMODULE} LINK_LIBRARIES)
    #     message(STATUS "EPIMODULE_LINK_LIBRARIES=${EPIMODULE_LINK_LIBRARIES}")
    # else ()
    #     get_target_property(EPIMODULE_LINK_LIBRARIES ${EPIMODULE} INTERFACE_LINK_LIBRARIES)
    #     message(STATUS "EPIMODULE_LINK_LIBRARIES=${EPIMODULE_LINK_LIBRARIES}")
    # endif ()

    if (NOT ${EPIMODULE_TYPE} STREQUAL "INTERFACE_LIBRARY")
        get_target_property(EPIMODULE_SOURCE_DIR ${EPIMODULE} SOURCE_DIR)
        get_target_property(EPIMODULE_BINARY_DIR ${EPIMODULE} BINARY_DIR)

        set_target_properties(${EPIMODULE}
            PROPERTIES
                CXX_STANDARD 17
                CXX_STANDARD_REQUIRED YES
                CXX_EXTENSIONS NO
        )

        if (EPIMODULE_FOLDER)
            set_target_properties(${EPIMODULE}
                PROPERTIES
                    FOLDER ${EPIMODULE_FOLDER}
            )
        endif ()

        if (NOT EPIMODULE_EXTERN)
            set_property(GLOBAL APPEND PROPERTY EPIGEN_MANIFEST_MODULES "${EPIMODULE_SOURCE_DIR}/Sources/${EPIMODULE}")
        endif ()


        set(EPIMODULE_TEST_DIR "${EPIMODULE_SOURCE_DIR}/Tests")
        if (EPI_BUILD_TESTS AND NOT EPIMODULE_EXTERN AND IS_DIRECTORY ${EPIMODULE_TEST_DIR})
            file(GLOB EPIMODULE_TESTS_GLOB
                RELATIVE ${EPIMODULE_TEST_DIR}
                LIST_DIRECTORIES ON
                "${EPIMODULE_TEST_DIR}/Tests*"
            )

            foreach (EPIMODULE_TESTS_ITEM ${EPIMODULE_TESTS_GLOB})
                set(EPIMODULE_TESTS_ITEM_DIR "${EPIMODULE_TEST_DIR}/${EPIMODULE_TESTS_ITEM}")
                if (NOT IS_DIRECTORY ${EPIMODULE_TESTS_ITEM_DIR})
                    continue ()
                endif ()

                file(GLOB EPIMODULE_TESTS_ITEM_SOURCES
                    ${EPIMODULE_TESTS_ITEM_DIR}/*.epi
                    ${EPIMODULE_TESTS_ITEM_DIR}/*.h
                    ${EPIMODULE_TESTS_ITEM_DIR}/*.cpp
                )

                set(EPIMODULE_TEST "${EPIMODULE}-${EPIMODULE_TESTS_ITEM}")

                add_executable(${EPIMODULE_TEST}
                    ${EPIMODULE_TESTS_ITEM_SOURCES}
                )

                get_target_property(EPIMODULE_TEST_SOURCES ${EPIMODULE_TEST} SOURCES)
                epi_pack_sources(${EPIMODULE_TEST_SOURCES})

                target_include_directories(${EPIMODULE_TEST}
                    PRIVATE
                        $<BUILD_INTERFACE:${EPIMODULE_SOURCE_DIR}/Tests>
                        $<BUILD_INTERFACE:${EPIMODULE_BINARY_DIR}/Tests>
                )

                target_link_libraries(${EPIMODULE_TEST}
                    PRIVATE
                        ${EPIMODULE}
                        EpiTests
                )

                add_test(NAME ${EPIMODULE_TEST} COMMAND ${EPIMODULE_TEST})

                if (EPIMODULE_FOLDER)
                    set(EPIMODULE_TESTS_FOLDER "${EPIMODULE_FOLDER}/Tests")
                else ()
                    set(EPIMODULE_TESTS_FOLDER "Tests")
                endif ()

                set_property(GLOBAL APPEND PROPERTY EPIGEN_MANIFEST_MODULES "${EPIMODULE_TESTS_ITEM_DIR}")

                set_target_properties(${EPIMODULE_TEST}
                    PROPERTIES
                        CXX_STANDARD 17
                        CXX_STANDARD_REQUIRED YES
                        CXX_EXTENSIONS NO
                        FOLDER ${EPIMODULE_TESTS_FOLDER}
                )
            endforeach ()
        endif ()
    endif()
endfunction()
