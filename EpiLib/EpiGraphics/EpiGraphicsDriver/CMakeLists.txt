project(EpiGraphicsDriver)

add_library(EpiGraphicsDriver
    Sources/EpiGraphicsDriver/gfxDriver.epi
    Sources/EpiGraphicsDriver/gfxDriver.h
    Sources/EpiGraphicsDriver/gfxDriver.cpp

    Sources/EpiGraphicsDriver/gfxGPUCrashTracker.epi
    Sources/EpiGraphicsDriver/gfxGPUCrashTracker.h
    Sources/EpiGraphicsDriver/gfxGPUCrashTracker.cpp
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
        EpiGraphics
)

epi_module_register(EpiGraphicsDriver
    FOLDER "EpiLib"
)
