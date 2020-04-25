project(EpiDataVisualization)

add_library(EpiDataVisualization
    EpiDataVisualization/pch.h
    EpiDataVisualization/pch.cpp

    EpiDataVisualization/Data/dvDataCollection.epi
    EpiDataVisualization/Data/dvDataCollection.h
    EpiDataVisualization/Data/dvDataCollection.cpp

    EpiDataVisualization/Plot/dvPlotBase.epi
    EpiDataVisualization/Plot/dvPlotBase.h
    EpiDataVisualization/Plot/dvPlotBase.cpp
    EpiDataVisualization/Plot/dvPlotLine.epi
    EpiDataVisualization/Plot/dvPlotLine.h
    EpiDataVisualization/Plot/dvPlotLine.cpp

    EpiDataVisualization/Plot/Series/dvSeriesBase.epi
    EpiDataVisualization/Plot/Series/dvSeriesBase.h
    EpiDataVisualization/Plot/Series/dvSeriesBase.cpp
    EpiDataVisualization/Plot/Series/dvSeriesY.epi
    EpiDataVisualization/Plot/Series/dvSeriesY.h
    EpiDataVisualization/Plot/Series/dvSeriesY.cpp
    EpiDataVisualization/Plot/Series/dvSeriesXY.epi
    EpiDataVisualization/Plot/Series/dvSeriesXY.h
    EpiDataVisualization/Plot/Series/dvSeriesXY.cpp

    EpiDataVisualization/ViewModel/dvViewModelPlotBase.epi
    EpiDataVisualization/ViewModel/dvViewModelPlotBase.h
    EpiDataVisualization/ViewModel/dvViewModelPlotBase.cpp
    EpiDataVisualization/ViewModel/dvViewModelSeriesBase.epi
    EpiDataVisualization/ViewModel/dvViewModelSeriesBase.h
    EpiDataVisualization/ViewModel/dvViewModelSeriesBase.cpp

    EpiDataVisualization/View/dvViewPlotBase.epi
    EpiDataVisualization/View/dvViewPlotBase.h
    EpiDataVisualization/View/dvViewPlotBase.cpp

    EpiDataVisualization/Drawer/dvDrawerPlotBase.epi
    EpiDataVisualization/Drawer/dvDrawerPlotBase.h
    EpiDataVisualization/Drawer/dvDrawerPlotBase.cpp
    EpiDataVisualization/Drawer/dvDrawerPlotLine.epi
    EpiDataVisualization/Drawer/dvDrawerPlotLine.h
    EpiDataVisualization/Drawer/dvDrawerPlotLine.cpp
    EpiDataVisualization/Drawer/dvDrawerSeriesBase.epi
    EpiDataVisualization/Drawer/dvDrawerSeriesBase.h
    EpiDataVisualization/Drawer/dvDrawerSeriesBase.cpp
    EpiDataVisualization/Drawer/dvDrawerSeriesY.epi
    EpiDataVisualization/Drawer/dvDrawerSeriesY.h
    EpiDataVisualization/Drawer/dvDrawerSeriesY.cpp
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
        EpiUI
        EpiGraphics
)

epi_module_register(EpiDataVisualization)
