project(EpiDataVisualization)

add_library(EpiDataVisualization
    EpiDataVisualization/pch.h
    EpiDataVisualization/pch.cpp

    EpiDataVisualization/DataCollection.epi
    EpiDataVisualization/DataCollection.h
    EpiDataVisualization/DataCollection.cpp

    EpiDataVisualization/SeriesY.epi
    EpiDataVisualization/SeriesY.h
    EpiDataVisualization/SeriesY.cpp
    EpiDataVisualization/SeriesXY.epi
    EpiDataVisualization/SeriesXY.h
    EpiDataVisualization/SeriesXY.cpp

    EpiDataVisualization/PlotBase.epi
    EpiDataVisualization/PlotBase.h
    EpiDataVisualization/PlotBase.cpp
    EpiDataVisualization/PlotLine.epi
    EpiDataVisualization/PlotLine.h
    EpiDataVisualization/PlotLine.cpp

    EpiDataVisualization/DrawerPlotBase.epi
    EpiDataVisualization/DrawerPlotBase.h
    EpiDataVisualization/DrawerPlotBase.cpp
    EpiDataVisualization/DrawerPlotLine.epi
    EpiDataVisualization/DrawerPlotLine.h
    EpiDataVisualization/DrawerPlotLine.cpp
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
