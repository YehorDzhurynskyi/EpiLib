project(EpiGraphics)

add_library(EpiGraphics
    EpiGraphics/pch.h
    EpiGraphics/pch.cpp

    EpiGraphics/gfxContext.epi
    EpiGraphics/gfxContext.h
    EpiGraphics/gfxContext.cpp

    EpiGraphics/gfxBindable.epi
    EpiGraphics/gfxBindable.h
    EpiGraphics/gfxBindable.cpp

    EpiGraphics/gfxVertexArray.epi
    EpiGraphics/gfxVertexArray.h
    EpiGraphics/gfxVertexArray.cpp

    EpiGraphics/gfxShaderProgram.epi
    EpiGraphics/gfxShaderProgram.h
    EpiGraphics/gfxShaderProgram.cpp

    EpiGraphics/gfxDrawer.epi
    EpiGraphics/gfxDrawer.h
    EpiGraphics/gfxDrawer.cpp

    EpiGraphics/Camera/gfxCamera.epi
    EpiGraphics/Camera/gfxCamera.h
    EpiGraphics/Camera/gfxCamera.cpp
    EpiGraphics/Camera/gfxCameraOrtho.epi
    EpiGraphics/Camera/gfxCameraOrtho.h
    EpiGraphics/Camera/gfxCameraOrtho.cpp
    EpiGraphics/Camera/gfxCameraPersp.epi
    EpiGraphics/Camera/gfxCameraPersp.h
    EpiGraphics/Camera/gfxCameraPersp.cpp
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
