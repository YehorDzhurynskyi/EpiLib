project(EpiTests)

if (EPI_BUILD_TESTS)
    epi_extern_add(googletest
        COMPONENTS
            gtest
            gtest_main
    )

    add_library(EpiTests INTERFACE)
    set_target_properties(EpiTests
        PROPERTIES
            INTERFACE_LINK_LIBRARIES googletest
    )
endif ()
