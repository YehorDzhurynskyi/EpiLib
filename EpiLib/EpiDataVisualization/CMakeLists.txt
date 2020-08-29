project(EpiDataVisualization)

add_library(EpiDataVisualization
    Sources/EpiDataVisualization/Plot/dvPlot.epi
    Sources/EpiDataVisualization/Plot/dvPlot.h
    Sources/EpiDataVisualization/Plot/dvPlot.cpp

    Sources/EpiDataVisualization/ViewModel/dvViewModelPlot.epi
    Sources/EpiDataVisualization/ViewModel/dvViewModelPlot.h
    Sources/EpiDataVisualization/ViewModel/dvViewModelPlot.cpp
    Sources/EpiDataVisualization/ViewModel/dvViewModelSeriesBase.epi
    Sources/EpiDataVisualization/ViewModel/dvViewModelSeriesBase.h
    Sources/EpiDataVisualization/ViewModel/dvViewModelSeriesBase.cpp

    Sources/EpiDataVisualization/Drawer/dvDrawerPlotDrawArea.epi
    Sources/EpiDataVisualization/Drawer/dvDrawerPlotDrawArea.h
    Sources/EpiDataVisualization/Drawer/dvDrawerPlotDrawArea.cpp
    Sources/EpiDataVisualization/Drawer/dvDrawerPlotTimeline.epi
    Sources/EpiDataVisualization/Drawer/dvDrawerPlotTimeline.h
    Sources/EpiDataVisualization/Drawer/dvDrawerPlotTimeline.cpp
    Sources/EpiDataVisualization/Drawer/dvDrawerSeriesBase.epi
    Sources/EpiDataVisualization/Drawer/dvDrawerSeriesBase.h
    Sources/EpiDataVisualization/Drawer/dvDrawerSeriesBase.cpp
    Sources/EpiDataVisualization/Drawer/dvDrawerSeriesY.epi
    Sources/EpiDataVisualization/Drawer/dvDrawerSeriesY.h
    Sources/EpiDataVisualization/Drawer/dvDrawerSeriesY.cpp
)
get_target_property(EpiDataVisualization_SOURCES EpiDataVisualization SOURCES)
epi_pack_sources(${EpiDataVisualization_SOURCES})

target_include_directories(EpiDataVisualization
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiDataVisualization
    PUBLIC
        EpiCore
        EpiData
        EpiGraphics
)

epi_module_register(EpiDataVisualization
    FOLDER "EpiLib"
)
