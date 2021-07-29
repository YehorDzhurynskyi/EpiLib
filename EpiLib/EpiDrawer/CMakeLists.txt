project(EpiDrawer)

add_library(EpiDrawer
    Sources/EpiDrawer/drwContext.epi
    Sources/EpiDrawer/drwContext.h
    Sources/EpiDrawer/drwContext.cpp

    Sources/EpiDrawer/drwDrawer.epi
    Sources/EpiDrawer/drwDrawer.h
    Sources/EpiDrawer/drwDrawer.cpp
    Sources/EpiDrawer/drwDrawerPrimitive.epi
    Sources/EpiDrawer/drwDrawerPrimitive.h
    Sources/EpiDrawer/drwDrawerPrimitive.cpp
    Sources/EpiDrawer/drwDrawerText.epi
    Sources/EpiDrawer/drwDrawerText.h
    Sources/EpiDrawer/drwDrawerText.cpp

    Sources/EpiDrawer/Camera/drwCamera.epi
    Sources/EpiDrawer/Camera/drwCamera.h
    Sources/EpiDrawer/Camera/drwCamera.cpp
    Sources/EpiDrawer/Camera/drwCameraOrtho.epi
    Sources/EpiDrawer/Camera/drwCameraOrtho.h
    Sources/EpiDrawer/Camera/drwCameraOrtho.cpp
    Sources/EpiDrawer/Camera/drwCameraPersp.epi
    Sources/EpiDrawer/Camera/drwCameraPersp.h
    Sources/EpiDrawer/Camera/drwCameraPersp.cpp

    Sources/EpiDrawer/Text/drwTextManager.epi
    Sources/EpiDrawer/Text/drwTextManager.h
    Sources/EpiDrawer/Text/drwTextManager.cpp
    Sources/EpiDrawer/Text/drwTextFace.epi
    Sources/EpiDrawer/Text/drwTextFace.h
    Sources/EpiDrawer/Text/drwTextFace.cpp
    Sources/EpiDrawer/Text/drwTextRendered.epi
    Sources/EpiDrawer/Text/drwTextRendered.h
    Sources/EpiDrawer/Text/drwTextRendered.cpp
    Sources/EpiDrawer/Text/drwTextRenderedAtlas.epi
    Sources/EpiDrawer/Text/drwTextRenderedAtlas.h
    Sources/EpiDrawer/Text/drwTextRenderedAtlas.cpp
    Sources/EpiDrawer/Text/drwTextRenderedGlyph.epi
    Sources/EpiDrawer/Text/drwTextRenderedGlyph.h
    Sources/EpiDrawer/Text/drwTextRenderedGlyph.cpp
)
get_target_property(EpiDrawer_SOURCES EpiDrawer SOURCES)
epi_pack_sources(${EpiDrawer_SOURCES})

epi_extern_add(freetype)

target_include_directories(EpiDrawer
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiDrawer
    PUBLIC
        EpiCore
        EpiGraphicsDriver
        freetype
)

epi_module_register(EpiDrawer
    FOLDER "EpiLib"
)
