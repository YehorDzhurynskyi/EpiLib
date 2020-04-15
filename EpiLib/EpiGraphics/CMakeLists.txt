project(EpiGraphics)

add_library(EpiGraphics
    EpiGraphics/pch.h
    EpiGraphics/pch.cpp

    EpiGraphics/Drawer.epi
    EpiGraphics/Drawer.h
    EpiGraphics/Drawer.cpp
)
get_target_property(EpiGraphics_SRCs EpiGraphics SOURCES) 
epi_add_precompiled_header(EpiGraphics EpiGraphics/pch.h SOURCE_CXX EpiGraphics/pch.cpp)
epi_pack_sources(${EpiGraphics_SRCs})

add_subdirectory(Extern/glad)
epi_extern_register(glad)

target_include_directories(EpiGraphics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiGraphics
    PUBLIC
        EpiCore
        glad
)

epi_module_register(EpiGraphics)
