project(EpiGraphicsDriver)

option(EPI_GRAPHICS_DRIVER_GL "Enable OpenGL Graphics API support" ON)
option(EPI_GRAPHICS_DRIVER_VK "Enable Vulkan Graphics API support" ON)

add_subdirectory(EpiGraphicsDriverImpl)

add_library(EpiGraphicsDriver
    Sources/EpiGraphicsDriver/gfxDriver.h
    Sources/EpiGraphicsDriver/gfxDriver.cpp
)
get_target_property(EpiGraphicsDriver_SOURCES EpiGraphicsDriver SOURCES)
epi_pack_sources(${EpiGraphicsDriver_SOURCES})

target_include_directories(EpiGraphicsDriver
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiGraphicsDriver
    PUBLIC
        EpiGraphicsEnum

    PRIVATE
        EpiGraphicsDriverImpl
)

if (EPI_GRAPHICS_DRIVER_GL)
    find_package(OpenGL)

    if (OpenGL_FOUND)
        message(STATUS "OpenGL libraries are found: ${OPENGL_LIBRARIES}")
        add_subdirectory(EpiGraphicsDriverGL)
        target_link_libraries(EpiGraphicsDriver PRIVATE EpiGraphicsDriverGL)
    else()
        message(WARNING "Failed to find OpenGL, skipping OpenGL Graphics Driver compilation...")
    endif()
endif()

if (EPI_GRAPHICS_DRIVER_VK)
    find_package(Vulkan)

    if (Vulkan_FOUND)
        message(STATUS "Vulkan libraries are found: ${Vulkan_LIBRARIES}")
        add_subdirectory(EpiGraphicsDriverVK)
        target_link_libraries(EpiGraphicsDriver PRIVATE EpiGraphicsDriverVK)
    else()
        message(WARNING "Failed to find Vulkan, skipping Vulkan Graphics Driver compilation...")
        if (NOT $ENV{VK_SDK_PATH})
            message(WARNING "VK_SDK_PATH environment variable isn't set, try to install Vulkan SDK then reboot your device")
        endif()
    endif()
endif()

epi_module_register(EpiGraphicsDriver
    FOLDER "EpiLib"
)
