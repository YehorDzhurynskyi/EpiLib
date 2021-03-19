project(EpiGraphics)

add_library(EpiGraphics
    Sources/EpiGraphics/gfxContext.epi
    Sources/EpiGraphics/gfxContext.h
    Sources/EpiGraphics/gfxContext.cpp

    Sources/EpiGraphics/gfxBindable.epi
    Sources/EpiGraphics/gfxBindable.h
    Sources/EpiGraphics/gfxBindable.cpp

    Sources/EpiGraphics/gfxDrawer.epi
    Sources/EpiGraphics/gfxDrawer.h
    Sources/EpiGraphics/gfxDrawer.cpp
    Sources/EpiGraphics/gfxDrawerPrimitive.epi
    Sources/EpiGraphics/gfxDrawerPrimitive.h
    Sources/EpiGraphics/gfxDrawerPrimitive.cpp
    Sources/EpiGraphics/gfxDrawerText.epi
    Sources/EpiGraphics/gfxDrawerText.h
    Sources/EpiGraphics/gfxDrawerText.cpp

    Sources/EpiGraphics/Camera/gfxCamera.epi
    Sources/EpiGraphics/Camera/gfxCamera.h
    Sources/EpiGraphics/Camera/gfxCamera.cpp
    Sources/EpiGraphics/Camera/gfxCameraOrtho.epi
    Sources/EpiGraphics/Camera/gfxCameraOrtho.h
    Sources/EpiGraphics/Camera/gfxCameraOrtho.cpp
    Sources/EpiGraphics/Camera/gfxCameraPersp.epi
    Sources/EpiGraphics/Camera/gfxCameraPersp.h
    Sources/EpiGraphics/Camera/gfxCameraPersp.cpp

    Sources/EpiGraphics/Text/gfxTextManager.epi
    Sources/EpiGraphics/Text/gfxTextManager.h
    Sources/EpiGraphics/Text/gfxTextManager.cpp
    Sources/EpiGraphics/Text/gfxTextFace.epi
    Sources/EpiGraphics/Text/gfxTextFace.h
    Sources/EpiGraphics/Text/gfxTextFace.cpp
    Sources/EpiGraphics/Text/gfxTextRendered.epi
    Sources/EpiGraphics/Text/gfxTextRendered.h
    Sources/EpiGraphics/Text/gfxTextRendered.cpp
    Sources/EpiGraphics/Text/gfxTextRenderedAtlas.epi
    Sources/EpiGraphics/Text/gfxTextRenderedAtlas.h
    Sources/EpiGraphics/Text/gfxTextRenderedAtlas.cpp
    Sources/EpiGraphics/Text/gfxTextRenderedGlyph.epi
    Sources/EpiGraphics/Text/gfxTextRenderedGlyph.h
    Sources/EpiGraphics/Text/gfxTextRenderedGlyph.cpp
)
get_target_property(EpiGraphics_SOURCES EpiGraphics SOURCES)
epi_pack_sources(${EpiGraphics_SOURCES})

epi_extern_add(freetype)

target_include_directories(EpiGraphics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiGraphics
    PUBLIC
        EpiCore
        EpiGraphicsDriver
        freetype
)

epi_module_register(EpiGraphics
    FOLDER "EpiLib"
)
