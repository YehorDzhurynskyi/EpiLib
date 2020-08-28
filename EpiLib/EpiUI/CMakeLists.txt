project(EpiUI)

add_library(EpiUI
    Sources/EpiUI/uiViewModel.epi
    Sources/EpiUI/uiViewModel.h
    Sources/EpiUI/uiViewModel.cpp

    Sources/EpiUI/uiAction.epi
    Sources/EpiUI/uiAction.h
    Sources/EpiUI/uiAction.cpp

    Sources/EpiUI/uiCamera.epi
    Sources/EpiUI/uiCamera.h
    Sources/EpiUI/uiCamera.cpp

    Sources/EpiUI/uiContext.epi
    Sources/EpiUI/uiContext.h
    Sources/EpiUI/uiContext.cpp

    Sources/EpiUI/uiWidget.epi
    Sources/EpiUI/uiWidget.h
    Sources/EpiUI/uiWidget.cpp

    Sources/EpiUI/uiPage.epi
    Sources/EpiUI/uiPage.h
    Sources/EpiUI/uiPage.cpp

    Sources/EpiUI/Layout/uiLayout.epi
    Sources/EpiUI/Layout/uiLayout.h
    Sources/EpiUI/Layout/uiLayout.cpp
    Sources/EpiUI/Layout/uiLayoutBox.epi
    Sources/EpiUI/Layout/uiLayoutBox.h
    Sources/EpiUI/Layout/uiLayoutBox.cpp
)
get_target_property(EpiUI_SOURCES EpiUI SOURCES)
epi_pack_sources(${EpiUI_SOURCES})

target_precompile_headers(EpiUI REUSE_FROM EpiCore)

target_include_directories(EpiUI
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiUI
    PUBLIC
        EpiCore
        EpiGraphics
)

epi_module_register(EpiUI
    FOLDER "EpiLib"
)

