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

epi_extern_add(wxWidgets
    COMPONENTS
        wx::net
        wx::core
        wx::gl
        wx::base
        wx::aui
        wx::propgrid
        wx::jpeg
        wx::png
        wx::regex
        wx::tiff
        wx::zlib
)

target_include_directories(EpiwxWidgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiwxWidgets
    PUBLIC
        EpiCore
        EpiDataVisualization
        wxWidgets
)

epi_module_register(EpiwxWidgets)
