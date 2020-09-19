project(EpiDataVisualization)

add_library(EpiDataVisualization
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMPlot.epi
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMPlot.h
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMPlot.cpp
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.epi
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.h
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.cpp
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMSeries1Df.epi
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMSeries1Df.h
    Sources/EpiDataVisualization/Plot/ViewModel/dvVMSeries1Df.cpp

    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.epi
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.h
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerPlotDrawArea.cpp
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerSeriesBase.epi
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerSeriesBase.h
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerSeriesBase.cpp
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.epi
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.h
    Sources/EpiDataVisualization/Plot/Drawer/dvDrawerSeries1Df.cpp
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
