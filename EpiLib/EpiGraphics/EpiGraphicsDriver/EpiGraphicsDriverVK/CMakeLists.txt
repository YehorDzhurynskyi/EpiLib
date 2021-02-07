project(EpiGraphicsDriverVK)

add_library(EpiGraphicsDriverVK
    Sources/EpiGraphicsDriverVK/gfxDriverVK.h
    Sources/EpiGraphicsDriverVK/gfxDriverVK.cpp
    Sources/EpiGraphicsDriverVK/gfxVertexArrayImplVK.h
    Sources/EpiGraphicsDriverVK/gfxVertexArrayImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxVertexBufferImplVK.h
    Sources/EpiGraphicsDriverVK/gfxVertexBufferImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxTextureImplVK.h
    Sources/EpiGraphicsDriverVK/gfxTextureImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxShaderProgramImplVK.h
    Sources/EpiGraphicsDriverVK/gfxShaderProgramImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h
    Sources/EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxDeviceImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDeviceImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxQueueImplVK.h
    Sources/EpiGraphicsDriverVK/gfxQueueImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxSurfaceImplVK.h
    Sources/EpiGraphicsDriverVK/gfxSurfaceImplVK.cpp
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

