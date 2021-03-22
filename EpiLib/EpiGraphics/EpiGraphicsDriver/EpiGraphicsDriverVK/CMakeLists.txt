project(EpiGraphicsDriverVK)

add_library(EpiGraphicsDriverVK
    Sources/EpiGraphicsDriverVK/gfxEnumVK.h
    Sources/EpiGraphicsDriverVK/gfxEnumVK.cpp
    Sources/EpiGraphicsDriverVK/gfxDriverImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDriverImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxVertexArrayImplVK.h
    Sources/EpiGraphicsDriverVK/gfxVertexArrayImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxVertexBufferImplVK.h
    Sources/EpiGraphicsDriverVK/gfxVertexBufferImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxTextureImplVK.h
    Sources/EpiGraphicsDriverVK/gfxTextureImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxTextureViewImplVK.h
    Sources/EpiGraphicsDriverVK/gfxTextureViewImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxShaderProgramImplVK.h
    Sources/EpiGraphicsDriverVK/gfxShaderProgramImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h
    Sources/EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxDeviceImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDeviceImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxQueueImplVK.h
    Sources/EpiGraphicsDriverVK/gfxQueueImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h
    Sources/EpiGraphicsDriverVK/gfxQueueFamilyImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxSurfaceImplVK.h
    Sources/EpiGraphicsDriverVK/gfxSurfaceImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxSwapChainImplVK.h
    Sources/EpiGraphicsDriverVK/gfxSwapChainImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxPipelineImplVK.h
    Sources/EpiGraphicsDriverVK/gfxPipelineImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxAttachmentImplVK.h
    Sources/EpiGraphicsDriverVK/gfxAttachmentImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxRenderPassImplVK.h
    Sources/EpiGraphicsDriverVK/gfxRenderPassImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxRenderSubPassVK.h
    Sources/EpiGraphicsDriverVK/gfxRenderSubPassVK.cpp
    Sources/EpiGraphicsDriverVK/gfxFrameBufferImplVK.h
    Sources/EpiGraphicsDriverVK/gfxFrameBufferImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxCommandPoolImplVK.h
    Sources/EpiGraphicsDriverVK/gfxCommandPoolImplVK.cpp
)
get_target_property(EpiGraphicsDriverVK_SOURCES EpiGraphicsDriverVK SOURCES)
epi_pack_sources(${EpiGraphicsDriverVK_SOURCES})

target_include_directories(EpiGraphicsDriverVK
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

find_package(Vulkan REQUIRED FATAL_ERROR)

target_link_libraries(EpiGraphicsDriverVK
    PRIVATE
        EpiGraphicsDriverCommon
        Vulkan::Vulkan
        #Vulkan::glslc
)

epi_module_register(EpiGraphicsDriverVK
    FOLDER "EpiLib"
)

