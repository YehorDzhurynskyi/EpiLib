project(EpiGraphics)

add_library(EpiGraphics
    Sources/EpiGraphics/gfxInstance.epi
    Sources/EpiGraphics/gfxInstance.h
    Sources/EpiGraphics/gfxInstance.cpp
    Sources/EpiGraphics/gfxPhysicalDevice.epi
    Sources/EpiGraphics/gfxPhysicalDevice.h
    Sources/EpiGraphics/gfxPhysicalDevice.cpp
    Sources/EpiGraphics/gfxDevice.epi
    Sources/EpiGraphics/gfxDevice.h
    Sources/EpiGraphics/gfxDevice.cpp
    Sources/EpiGraphics/gfxEnum.epi
    Sources/EpiGraphics/gfxEnum.h
    Sources/EpiGraphics/gfxEnum.cpp
    Sources/EpiGraphics/gfxQueueFamily.epi
    Sources/EpiGraphics/gfxQueueFamily.h
    Sources/EpiGraphics/gfxQueueFamily.cpp
    Sources/EpiGraphics/gfxQueue.epi
    Sources/EpiGraphics/gfxQueue.h
    Sources/EpiGraphics/gfxQueue.cpp
    Sources/EpiGraphics/gfxQueueDescriptor.epi
    Sources/EpiGraphics/gfxQueueDescriptor.h
    Sources/EpiGraphics/gfxQueueDescriptor.cpp
    Sources/EpiGraphics/gfxSurface.epi
    Sources/EpiGraphics/gfxSurface.h
    Sources/EpiGraphics/gfxSurface.cpp
    Sources/EpiGraphics/gfxWindow.epi
    Sources/EpiGraphics/gfxWindow.h
    Sources/EpiGraphics/gfxWindow.cpp
    Sources/EpiGraphics/gfxSwapChain.epi
    Sources/EpiGraphics/gfxSwapChain.h
    Sources/EpiGraphics/gfxSwapChain.cpp
    Sources/EpiGraphics/gfxRenderPass.epi
    Sources/EpiGraphics/gfxRenderPass.h
    Sources/EpiGraphics/gfxRenderPass.cpp
    Sources/EpiGraphics/gfxPipelineLayout.epi
    Sources/EpiGraphics/gfxPipelineLayout.h
    Sources/EpiGraphics/gfxPipelineLayout.cpp
    Sources/EpiGraphics/gfxPipeline.epi
    Sources/EpiGraphics/gfxPipeline.h
    Sources/EpiGraphics/gfxPipeline.cpp
    Sources/EpiGraphics/gfxDeviceMemory.epi
    Sources/EpiGraphics/gfxDeviceMemory.h
    Sources/EpiGraphics/gfxDeviceMemory.cpp
    Sources/EpiGraphics/gfxBuffer.epi
    Sources/EpiGraphics/gfxBuffer.h
    Sources/EpiGraphics/gfxBuffer.cpp
    Sources/EpiGraphics/gfxImage.epi
    Sources/EpiGraphics/gfxImage.h
    Sources/EpiGraphics/gfxImage.cpp
    Sources/EpiGraphics/gfxImageView.epi
    Sources/EpiGraphics/gfxImageView.h
    Sources/EpiGraphics/gfxImageView.cpp
    Sources/EpiGraphics/gfxShaderModule.epi
    Sources/EpiGraphics/gfxShaderModule.h
    Sources/EpiGraphics/gfxShaderModule.cpp
    Sources/EpiGraphics/gfxFrameBuffer.epi
    Sources/EpiGraphics/gfxFrameBuffer.h
    Sources/EpiGraphics/gfxFrameBuffer.cpp
    Sources/EpiGraphics/gfxCommandPool.epi
    Sources/EpiGraphics/gfxCommandPool.h
    Sources/EpiGraphics/gfxCommandPool.cpp
    Sources/EpiGraphics/gfxCommandBuffer.epi
    Sources/EpiGraphics/gfxCommandBuffer.h
    Sources/EpiGraphics/gfxCommandBuffer.cpp
    Sources/EpiGraphics/gfxDescriptorPool.epi
    Sources/EpiGraphics/gfxDescriptorPool.h
    Sources/EpiGraphics/gfxDescriptorPool.cpp
    Sources/EpiGraphics/gfxDescriptorSet.epi
    Sources/EpiGraphics/gfxDescriptorSet.h
    Sources/EpiGraphics/gfxDescriptorSet.cpp
    Sources/EpiGraphics/gfxDescriptorSetLayout.epi
    Sources/EpiGraphics/gfxDescriptorSetLayout.h
    Sources/EpiGraphics/gfxDescriptorSetLayout.cpp
    Sources/EpiGraphics/gfxSampler.epi
    Sources/EpiGraphics/gfxSampler.h
    Sources/EpiGraphics/gfxSampler.cpp

    Sources/EpiGraphics/Synchronization/gfxFence.epi
    Sources/EpiGraphics/Synchronization/gfxFence.h
    Sources/EpiGraphics/Synchronization/gfxFence.cpp
    Sources/EpiGraphics/Synchronization/gfxSemaphore.epi
    Sources/EpiGraphics/Synchronization/gfxSemaphore.h
    Sources/EpiGraphics/Synchronization/gfxSemaphore.cpp
)
get_target_property(EpiGraphics_SOURCES EpiGraphics SOURCES)
epi_pack_sources(${EpiGraphics_SOURCES})

target_include_directories(EpiGraphics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiGraphics
    PUBLIC
        EpiCore

    PRIVATE
        EpiGraphicsImpl
)

find_package(NsightAftermath)

if (NsightAftermath_FOUND)
    target_link_libraries(EpiGraphics
        PUBLIC
            NsightAftermath::NsightAftermath
    )

    target_compile_definitions(EpiGraphics
        PUBLIC
            EPI_NVIDIA_NSIGHT_AFTERMATH
    )
else()
    set(NsightAftermath_NOTFOUND_MESSAGE "Couldn't find NsightAftermath package!")
    if (NOT $ENV{SIGHT_AFTERMATH_SDK})
        set(NsightAftermath_NOTFOUND_MESSAGE "${NsightAftermath_NOTFOUND_MESSAGE} NSIGHT_AFTERMATH_SDK environment variable isn't set!")
    endif()

    message(WARNING ${NsightAftermath_NOTFOUND_MESSAGE})
endif()

epi_module_register(EpiGraphics
    FOLDER "EpiLib"
)
