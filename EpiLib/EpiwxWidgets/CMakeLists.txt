project(EpiwxWidgets)

add_library(EpiwxWidgets
    EpiwxWidgets/pch.h
    EpiwxWidgets/pch.cpp

    EpiwxWidgets/epiWXPropertyGrid.h
    EpiwxWidgets/epiWXPropertyGrid.cpp
    EpiwxWidgets/epiWXPlot.h
    EpiwxWidgets/epiWXPlot.cpp
)
get_target_property(EpiwxWidgets_SRCs EpiwxWidgets SOURCES) 
epi_add_precompiled_header(EpiwxWidgets EpiwxWidgets/pch.h SOURCE_CXX EpiwxWidgets/pch.cpp)
epi_pack_sources(${EpiwxWidgets_SRCs})

epi_extern_add(wxWidgets net core gl base aui propgrid)

epi_extern_register(wxjpeg)
epi_extern_register(wxpng)
epi_extern_register(wxregex)
epi_extern_register(wxtiff)
epi_extern_register(wxzlib)

target_include_directories(EpiwxWidgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiwxWidgets
    PUBLIC
        EpiCore
        EpiDataVisualization
        net
        core
        gl
        base
        aui
        propgrid
)

epi_module_register(EpiwxWidgets)
