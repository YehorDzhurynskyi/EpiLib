project(EpiGraphicsImpl)

add_library(EpiGraphicsImpl
    Sources/EpiGraphicsImpl/common.h

    Sources/EpiGraphicsImpl/gfxInstanceImpl.h
    Sources/EpiGraphicsImpl/gfxInstanceImpl.cpp
    Sources/EpiGraphicsImpl/gfxDeviceMemoryImpl.h
    Sources/EpiGraphicsImpl/gfxDeviceMemoryImpl.cpp
    Sources/EpiGraphicsImpl/gfxBufferImpl.h
    Sources/EpiGraphicsImpl/gfxBufferImpl.cpp
    Sources/EpiGraphicsImpl/gfxImageImpl.h
    Sources/EpiGraphicsImpl/gfxImageImpl.cpp
    Sources/EpiGraphicsImpl/gfxImageViewImpl.h
    Sources/EpiGraphicsImpl/gfxImageViewImpl.cpp
    Sources/EpiGraphicsImpl/gfxShaderModuleImpl.h
    Sources/EpiGraphicsImpl/gfxShaderModuleImpl.cpp
    Sources/EpiGraphicsImpl/gfxPhysicalDeviceImpl.h
    Sources/EpiGraphicsImpl/gfxPhysicalDeviceImpl.cpp
    Sources/EpiGraphicsImpl/gfxDeviceImpl.h
    Sources/EpiGraphicsImpl/gfxDeviceImpl.cpp
    Sources/EpiGraphicsImpl/gfxQueueImpl.h
    Sources/EpiGraphicsImpl/gfxQueueImpl.cpp
    Sources/EpiGraphicsImpl/gfxQueueFamilyImpl.h
    Sources/EpiGraphicsImpl/gfxQueueFamilyImpl.cpp
    Sources/EpiGraphicsImpl/gfxSurfaceImpl.h
    Sources/EpiGraphicsImpl/gfxSurfaceImpl.cpp
    Sources/EpiGraphicsImpl/gfxSwapChainImpl.h
    Sources/EpiGraphicsImpl/gfxSwapChainImpl.cpp
    Sources/EpiGraphicsImpl/gfxPipelineLayoutImpl.h
    Sources/EpiGraphicsImpl/gfxPipelineLayoutImpl.cpp
    Sources/EpiGraphicsImpl/gfxPipelineImpl.h
    Sources/EpiGraphicsImpl/gfxPipelineImpl.cpp
    Sources/EpiGraphicsImpl/gfxRenderPassImpl.h
    Sources/EpiGraphicsImpl/gfxRenderPassImpl.cpp
    Sources/EpiGraphicsImpl/gfxFrameBufferImpl.h
    Sources/EpiGraphicsImpl/gfxFrameBufferImpl.cpp
    Sources/EpiGraphicsImpl/gfxCommandPoolImpl.h
    Sources/EpiGraphicsImpl/gfxCommandPoolImpl.cpp
    Sources/EpiGraphicsImpl/gfxCommandBufferImpl.h
    Sources/EpiGraphicsImpl/gfxCommandBufferImpl.cpp
    Sources/EpiGraphicsImpl/gfxDescriptorPoolImpl.h
    Sources/EpiGraphicsImpl/gfxDescriptorPoolImpl.cpp
    Sources/EpiGraphicsImpl/gfxDescriptorSetImpl.h
    Sources/EpiGraphicsImpl/gfxDescriptorSetImpl.cpp
    Sources/EpiGraphicsImpl/gfxDescriptorSetLayoutImpl.h
    Sources/EpiGraphicsImpl/gfxDescriptorSetLayoutImpl.cpp
    Sources/EpiGraphicsImpl/gfxSamplerImpl.h
    Sources/EpiGraphicsImpl/gfxSamplerImpl.cpp

    Sources/EpiGraphicsImpl/Synchronization/gfxFenceImpl.h
    Sources/EpiGraphicsImpl/Synchronization/gfxFenceImpl.cpp
    Sources/EpiGraphicsImpl/Synchronization/gfxSemaphoreImpl.h
    Sources/EpiGraphicsImpl/Synchronization/gfxSemaphoreImpl.cpp
)

target_precompile_headers(EpiGraphicsImpl
    PUBLIC
        [["EpiGraphicsImpl/common.h"]]
)

get_target_property(EpiGraphicsImpl_SOURCES EpiGraphicsImpl SOURCES)
epi_pack_sources(${EpiGraphicsImpl_SOURCES})

target_include_directories(EpiGraphicsImpl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiGraphicsImpl
    PUBLIC
        EpiGraphics
)

epi_module_register(EpiGraphicsImpl
    FOLDER "EpiLib"
)

