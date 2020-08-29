project(EpiwxWidgets)

add_library(EpiwxWidgets
    Sources/EpiwxWidgets/epiWXPropertyGrid.h
    Sources/EpiwxWidgets/epiWXPropertyGrid.cpp
    Sources/EpiwxWidgets/epiWXPlot.h
    Sources/EpiwxWidgets/epiWXPlot.cpp
)
get_target_property(EpiwxWidgets_SOURCES EpiwxWidgets SOURCES)
epi_pack_sources(${EpiwxWidgets_SOURCES})

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiwxWidgets
    PUBLIC
        EpiCore
        EpiDataVisualization
        EpiUI
        wxWidgets
)

epi_module_register(EpiwxWidgets
    FOLDER "EpiLib"
)
