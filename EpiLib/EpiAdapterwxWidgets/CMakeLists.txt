project(EpiAdapterwxWidgets)

add_library(EpiAdapterwxWidgets
    EpiAdapterwxWidgets/pch.h
    EpiAdapterwxWidgets/pch.cpp

    EpiAdapterwxWidgets/epiWXPropertyGrid.h
    EpiAdapterwxWidgets/epiWXPropertyGrid.cpp
    EpiAdapterwxWidgets/epiWXPlot.h
    EpiAdapterwxWidgets/epiWXPlot.cpp
)
get_target_property(EpiAdapterwxWidgets_SRCs EpiAdapterwxWidgets SOURCES) 
epi_add_precompiled_header(EpiAdapterwxWidgets EpiAdapterwxWidgets/pch.h SOURCE_CXX EpiAdapterwxWidgets/pch.cpp)
epi_pack_sources(${EpiAdapterwxWidgets_SRCs})

epi_extern_add(wxWidgets net core gl base aui propgrid)

epi_extern_register(wxjpeg)
epi_extern_register(wxpng)
epi_extern_register(wxregex)
epi_extern_register(wxtiff)
epi_extern_register(wxzlib)

target_include_directories(EpiAdapterwxWidgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiAdapterwxWidgets
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

epi_module_register(EpiAdapterwxWidgets)
