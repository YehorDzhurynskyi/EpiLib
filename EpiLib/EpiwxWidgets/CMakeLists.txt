project(EpiwxWidgets)

add_library(EpiwxWidgets
    Sources/EpiwxWidgets/epiWXImagePanel.h
    Sources/EpiwxWidgets/epiWXImagePanel.cpp
    Sources/EpiwxWidgets/epiWXPropertyGrid.h
    Sources/EpiwxWidgets/epiWXPropertyGrid.cpp
    Sources/EpiwxWidgets/epiWXPlot.h
    Sources/EpiwxWidgets/epiWXPlot.cpp
    Sources/EpiwxWidgets/epiWXObjectConfigurationPanel.h
    Sources/EpiwxWidgets/epiWXObjectConfigurationPanel.cpp
    Sources/EpiwxWidgets/epiWXSliderBase.h
    Sources/EpiwxWidgets/epiWXSliderBase.cpp
    Sources/EpiwxWidgets/epiWXSlider.h
    Sources/EpiwxWidgets/epiWXSliderThumb.h
    Sources/EpiwxWidgets/epiWXSliderRange.h
    Sources/EpiwxWidgets/epiWXEventLoop.h
    Sources/EpiwxWidgets/epiWXEventLoop.cpp
)

if (EPI_GRAPHICS_DRIVER_VK)
    find_package(Vulkan REQUIRED FATAL_ERROR)
    
    target_link_libraries(EpiwxWidgets
        PRIVATE
            Vulkan::Vulkan
    )

    target_sources(EpiwxWidgets
        PUBLIC
            Sources/EpiwxWidgets/Vulkan/epiWXVulkanContext.h
            Sources/EpiwxWidgets/Vulkan/epiWXVulkanContext.cpp
            Sources/EpiwxWidgets/Vulkan/epiWXVulkanCanvas.h
            Sources/EpiwxWidgets/Vulkan/epiWXVulkanCanvas.cpp
    )
endif()

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
        EpiMultimedia
        EpiUI
        wxWidgets
)

epi_module_register(EpiwxWidgets
    FOLDER "EpiLib"
)

add_subdirectory(Examples)
