project(EpiUI)

add_library(EpiUI
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

    Sources/EpiUI/Plot/uiPlot.epi
    Sources/EpiUI/Plot/uiPlot.h
    Sources/EpiUI/Plot/uiPlot.cpp
    Sources/EpiUI/Plot/uiPlotDrawArea.epi
    Sources/EpiUI/Plot/uiPlotDrawArea.h
    Sources/EpiUI/Plot/uiPlotDrawArea.cpp
)
get_target_property(EpiUI_SOURCES EpiUI SOURCES)
epi_pack_sources(${EpiUI_SOURCES})

target_include_directories(EpiUI
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiUI
    PUBLIC
        EpiCore
        EpiGraphics
        EpiDataVisualization
)

epi_module_register(EpiUI
    FOLDER "EpiLib"
)

