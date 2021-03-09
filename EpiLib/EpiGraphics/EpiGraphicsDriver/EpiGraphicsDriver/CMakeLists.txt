project(EpiGraphicsDriver)

add_library(EpiGraphicsDriver
    Sources/EpiGraphicsDriver/gfxDriver.epi
    Sources/EpiGraphicsDriver/gfxDriver.h
    Sources/EpiGraphicsDriver/gfxDriver.cpp
)
get_target_property(EpiGraphicsDriver_SOURCES EpiGraphicsDriver SOURCES)
epi_pack_sources(${EpiGraphicsDriver_SOURCES})

target_include_directories(EpiGraphicsDriver
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiGraphicsDriver
    PUBLIC
        EpiGraphicsDriverCommon
)

epi_module_register(EpiGraphicsDriver
    FOLDER "EpiLib"
)
