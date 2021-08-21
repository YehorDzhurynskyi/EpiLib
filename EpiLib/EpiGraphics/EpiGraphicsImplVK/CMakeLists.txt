project(EpiGraphicsImplVK)

add_library(EpiGraphicsImplVK
    Sources/EpiGraphicsImplVK/gfxInstanceImplVK.h
    Sources/EpiGraphicsImplVK/gfxInstanceImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxDeviceMemoryImplVK.h
    Sources/EpiGraphicsImplVK/gfxDeviceMemoryImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxDeviceMemoryAllocatorImplVK.h
    Sources/EpiGraphicsImplVK/gfxDeviceMemoryAllocatorImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxBufferImplVK.h
    Sources/EpiGraphicsImplVK/gfxBufferImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxImageImplVK.h
    Sources/EpiGraphicsImplVK/gfxImageImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxImageViewImplVK.h
    Sources/EpiGraphicsImplVK/gfxImageViewImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxShaderModuleImplVK.h
    Sources/EpiGraphicsImplVK/gfxShaderModuleImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxPhysicalDeviceImplVK.h
    Sources/EpiGraphicsImplVK/gfxPhysicalDeviceImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxDeviceImplVK.h
    Sources/EpiGraphicsImplVK/gfxDeviceImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxQueueImplVK.h
    Sources/EpiGraphicsImplVK/gfxQueueImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxQueueFamilyImplVK.h
    Sources/EpiGraphicsImplVK/gfxQueueFamilyImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxSurfaceImplVK.h
    Sources/EpiGraphicsImplVK/gfxSurfaceImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxSwapChainImplVK.h
    Sources/EpiGraphicsImplVK/gfxSwapChainImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxPipelineLayoutImplVK.h
    Sources/EpiGraphicsImplVK/gfxPipelineLayoutImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxPipelineImplVK.h
    Sources/EpiGraphicsImplVK/gfxPipelineImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxRenderPassImplVK.h
    Sources/EpiGraphicsImplVK/gfxRenderPassImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxFrameBufferImplVK.h
    Sources/EpiGraphicsImplVK/gfxFrameBufferImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxCommandPoolImplVK.h
    Sources/EpiGraphicsImplVK/gfxCommandPoolImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxCommandBufferImplVK.h
    Sources/EpiGraphicsImplVK/gfxCommandBufferImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxDescriptorPoolImplVK.h
    Sources/EpiGraphicsImplVK/gfxDescriptorPoolImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxDescriptorSetImplVK.h
    Sources/EpiGraphicsImplVK/gfxDescriptorSetImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxDescriptorSetLayoutImplVK.h
    Sources/EpiGraphicsImplVK/gfxDescriptorSetLayoutImplVK.cpp
    Sources/EpiGraphicsImplVK/gfxSamplerImplVK.h
    Sources/EpiGraphicsImplVK/gfxSamplerImplVK.cpp

    Sources/EpiGraphicsImplVK/Synchronization/gfxFenceImplVK.h
    Sources/EpiGraphicsImplVK/Synchronization/gfxFenceImplVK.cpp
    Sources/EpiGraphicsImplVK/Synchronization/gfxSemaphoreImplVK.h
    Sources/EpiGraphicsImplVK/Synchronization/gfxSemaphoreImplVK.cpp
)

target_sources(EpiGraphicsImplVK
    PRIVATE
        Sources/EpiGraphicsImplVK/gfxEnumVK.h
        Sources/EpiGraphicsImplVK/gfxEnumVK.cpp
        Sources/EpiGraphicsImplVK/gfxErrorVK.h
        Sources/EpiGraphicsImplVK/gfxErrorVK.cpp
)

get_target_property(EpiGraphicsImplVK_SOURCES EpiGraphicsImplVK SOURCES)
epi_pack_sources(${EpiGraphicsImplVK_SOURCES})

target_include_directories(EpiGraphicsImplVK
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

epi_extern_add(VulkanMemoryAllocator)

find_package(shaderc REQUIRED FATAL_ERROR)
find_package(Vulkan REQUIRED FATAL_ERROR)

target_link_libraries(EpiGraphicsImplVK
    PRIVATE
        EpiGraphicsImpl
        Vulkan::Vulkan
        shaderc
        VulkanMemoryAllocator
)

epi_module_register(EpiGraphicsImplVK
    FOLDER "EpiLib"
)

