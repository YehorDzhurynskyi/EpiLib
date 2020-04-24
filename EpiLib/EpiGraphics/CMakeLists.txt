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
    EpiGraphics/gfxVertexBuffer.epi
    EpiGraphics/gfxVertexBuffer.h
    EpiGraphics/gfxVertexBuffer.cpp

    EpiGraphics/gfxTexture.epi
    EpiGraphics/gfxTexture.h
    EpiGraphics/gfxTexture.cpp

    EpiGraphics/gfxShaderProgram.epi
    EpiGraphics/gfxShaderProgram.h
    EpiGraphics/gfxShaderProgram.cpp

    EpiGraphics/gfxDrawer.epi
    EpiGraphics/gfxDrawer.h
    EpiGraphics/gfxDrawer.cpp
    EpiGraphics/gfxDrawerPrimitive.epi
    EpiGraphics/gfxDrawerPrimitive.h
    EpiGraphics/gfxDrawerPrimitive.cpp
    EpiGraphics/gfxDrawerText.epi
    EpiGraphics/gfxDrawerText.h
    EpiGraphics/gfxDrawerText.cpp

    EpiGraphics/Camera/gfxCamera.epi
    EpiGraphics/Camera/gfxCamera.h
    EpiGraphics/Camera/gfxCamera.cpp
    EpiGraphics/Camera/gfxCameraOrtho.epi
    EpiGraphics/Camera/gfxCameraOrtho.h
    EpiGraphics/Camera/gfxCameraOrtho.cpp
    EpiGraphics/Camera/gfxCameraPersp.epi
    EpiGraphics/Camera/gfxCameraPersp.h
    EpiGraphics/Camera/gfxCameraPersp.cpp

    EpiGraphics/Text/gfxTextManager.epi
    EpiGraphics/Text/gfxTextManager.h
    EpiGraphics/Text/gfxTextManager.cpp
    EpiGraphics/Text/gfxTextFace.epi
    EpiGraphics/Text/gfxTextFace.h
    EpiGraphics/Text/gfxTextFace.cpp
    EpiGraphics/Text/gfxTextRendered.epi
    EpiGraphics/Text/gfxTextRendered.h
    EpiGraphics/Text/gfxTextRendered.cpp
    EpiGraphics/Text/gfxTextRenderedAtlas.epi
    EpiGraphics/Text/gfxTextRenderedAtlas.h
    EpiGraphics/Text/gfxTextRenderedAtlas.cpp
    EpiGraphics/Text/gfxTextRenderedGlyph.epi
    EpiGraphics/Text/gfxTextRenderedGlyph.h
    EpiGraphics/Text/gfxTextRenderedGlyph.cpp
)
get_target_property(EpiGraphics_SRCs EpiGraphics SOURCES) 
epi_add_precompiled_header(EpiGraphics EpiGraphics/pch.h SOURCE_CXX EpiGraphics/pch.cpp)
epi_pack_sources(${EpiGraphics_SRCs})

epi_extern_add(freetype)

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
        freetype
)

epi_module_register(EpiGraphics)
