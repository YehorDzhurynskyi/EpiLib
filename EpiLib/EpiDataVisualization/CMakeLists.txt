project(EpiDataVisualization)

add_library(EpiDataVisualization
    EpiDataVisualization/pch.h
    EpiDataVisualization/pch.cpp

    EpiDataVisualization/Data/DataCollection.epi
    EpiDataVisualization/Data/DataCollection.h
    EpiDataVisualization/Data/DataCollection.cpp

    EpiDataVisualization/Plot/PlotBase.epi
    EpiDataVisualization/Plot/PlotBase.h
    EpiDataVisualization/Plot/PlotBase.cpp
    EpiDataVisualization/Plot/PlotLine.epi
    EpiDataVisualization/Plot/PlotLine.h
    EpiDataVisualization/Plot/PlotLine.cpp

    EpiDataVisualization/Plot/Series/SeriesBase.epi
    EpiDataVisualization/Plot/Series/SeriesBase.h
    EpiDataVisualization/Plot/Series/SeriesBase.cpp
    EpiDataVisualization/Plot/Series/SeriesY.epi
    EpiDataVisualization/Plot/Series/SeriesY.h
    EpiDataVisualization/Plot/Series/SeriesY.cpp
    EpiDataVisualization/Plot/Series/SeriesXY.epi
    EpiDataVisualization/Plot/Series/SeriesXY.h
    EpiDataVisualization/Plot/Series/SeriesXY.cpp

    EpiDataVisualization/Drawer/DrawerPlotBase.epi
    EpiDataVisualization/Drawer/DrawerPlotBase.h
    EpiDataVisualization/Drawer/DrawerPlotBase.cpp
    EpiDataVisualization/Drawer/DrawerPlotLine.epi
    EpiDataVisualization/Drawer/DrawerPlotLine.h
    EpiDataVisualization/Drawer/DrawerPlotLine.cpp
)
get_target_property(EpiDataVisualization_SRCs EpiDataVisualization SOURCES) 
epi_add_precompiled_header(EpiDataVisualization EpiDataVisualization/pch.h SOURCE_CXX EpiDataVisualization/pch.cpp)
epi_pack_sources(${EpiDataVisualization_SRCs})

target_include_directories(EpiDataVisualization
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiDataVisualization
    PUBLIC
        EpiCore
        EpiGraphics
)

epi_module_register(EpiDataVisualization)
