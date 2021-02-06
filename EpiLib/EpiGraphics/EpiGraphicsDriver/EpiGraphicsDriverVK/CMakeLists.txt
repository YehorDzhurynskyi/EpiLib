project(EpiGraphicsDriverVK)

add_library(EpiGraphicsDriverVK
    Sources/EpiGraphicsDriverVK/gfxDriverVK.h
    Sources/EpiGraphicsDriverVK/gfxDriverVK.cpp
)
get_target_property(EpiGraphicsDriverVK_SOURCES EpiGraphicsDriverVK SOURCES)
epi_pack_sources(${EpiGraphicsDriverVK_SOURCES})

target_include_directories(EpiGraphicsDriverVK
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

find_package(Vulkan REQUIRED FATAL_ERROR)

target_link_libraries(EpiGraphicsDriverVK
    PRIVATE
        EpiGraphicsDriverAPI
        Vulkan::Vulkan
)

epi_module_register(EpiGraphicsDriverVK
    FOLDER "EpiLib"
)

