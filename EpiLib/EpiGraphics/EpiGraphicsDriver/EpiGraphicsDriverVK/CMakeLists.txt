project(EpiGraphicsDriverVK)

add_library(EpiGraphicsDriverVK
    Sources/EpiGraphicsDriverVK/gfxDriverImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDriverImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxDeviceMemoryImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDeviceMemoryImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxBufferImplVK.h
    Sources/EpiGraphicsDriverVK/gfxBufferImplVK.cpp
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
    Sources/EpiGraphicsDriverVK/gfxPipelineLayoutImplVK.h
    Sources/EpiGraphicsDriverVK/gfxPipelineLayoutImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxPipelineImplVK.h
    Sources/EpiGraphicsDriverVK/gfxPipelineImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxRenderPassImplVK.h
    Sources/EpiGraphicsDriverVK/gfxRenderPassImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxFrameBufferImplVK.h
    Sources/EpiGraphicsDriverVK/gfxFrameBufferImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxCommandPoolImplVK.h
    Sources/EpiGraphicsDriverVK/gfxCommandPoolImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxCommandBufferImplVK.h
    Sources/EpiGraphicsDriverVK/gfxCommandBufferImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxDescriptorPoolImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDescriptorPoolImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxDescriptorSetImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDescriptorSetImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxDescriptorSetLayoutImplVK.h
    Sources/EpiGraphicsDriverVK/gfxDescriptorSetLayoutImplVK.cpp
    Sources/EpiGraphicsDriverVK/gfxSamplerImplVK.h
    Sources/EpiGraphicsDriverVK/gfxSamplerImplVK.cpp

    Sources/EpiGraphicsDriverVK/Synchronization/gfxFenceImplVK.h
    Sources/EpiGraphicsDriverVK/Synchronization/gfxFenceImplVK.cpp
    Sources/EpiGraphicsDriverVK/Synchronization/gfxSemaphoreImplVK.h
    Sources/EpiGraphicsDriverVK/Synchronization/gfxSemaphoreImplVK.cpp
)

target_sources(EpiGraphicsDriverVK
    PRIVATE
        Sources/EpiGraphicsDriverVK/gfxEnumVK.h
        Sources/EpiGraphicsDriverVK/gfxEnumVK.cpp
        Sources/EpiGraphicsDriverVK/gfxErrorVK.h
        Sources/EpiGraphicsDriverVK/gfxErrorVK.cpp
)

get_target_property(EpiGraphicsDriverVK_SOURCES EpiGraphicsDriverVK SOURCES)
epi_pack_sources(${EpiGraphicsDriverVK_SOURCES})

target_include_directories(EpiGraphicsDriverVK
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

find_package(shaderc REQUIRED FATAL_ERROR)
find_package(Vulkan REQUIRED FATAL_ERROR)

target_link_libraries(EpiGraphicsDriverVK
    PRIVATE
        EpiGraphicsDriverCommon
        Vulkan::Vulkan
        shaderc
)

epi_module_register(EpiGraphicsDriverVK
    FOLDER "EpiLib"
)

