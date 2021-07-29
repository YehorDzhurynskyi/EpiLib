project(EpiGraphicsDriverCommon)

add_library(EpiGraphicsDriverCommon
    Sources/EpiGraphicsDriverCommon/gfxDriverInternal.h
    Sources/EpiGraphicsDriverCommon/gfxInstance.epi
    Sources/EpiGraphicsDriverCommon/gfxInstance.h
    Sources/EpiGraphicsDriverCommon/gfxInstance.cpp
    Sources/EpiGraphicsDriverCommon/gfxPhysicalDevice.epi
    Sources/EpiGraphicsDriverCommon/gfxPhysicalDevice.h
    Sources/EpiGraphicsDriverCommon/gfxPhysicalDevice.cpp
    Sources/EpiGraphicsDriverCommon/gfxDevice.epi
    Sources/EpiGraphicsDriverCommon/gfxDevice.h
    Sources/EpiGraphicsDriverCommon/gfxDevice.cpp
    Sources/EpiGraphicsDriverCommon/gfxEnum.epi
    Sources/EpiGraphicsDriverCommon/gfxEnum.h
    Sources/EpiGraphicsDriverCommon/gfxEnum.cpp
    Sources/EpiGraphicsDriverCommon/gfxQueueFamily.epi
    Sources/EpiGraphicsDriverCommon/gfxQueueFamily.h
    Sources/EpiGraphicsDriverCommon/gfxQueueFamily.cpp
    Sources/EpiGraphicsDriverCommon/gfxQueue.epi
    Sources/EpiGraphicsDriverCommon/gfxQueue.h
    Sources/EpiGraphicsDriverCommon/gfxQueue.cpp
    Sources/EpiGraphicsDriverCommon/gfxQueueDescriptor.epi
    Sources/EpiGraphicsDriverCommon/gfxQueueDescriptor.h
    Sources/EpiGraphicsDriverCommon/gfxQueueDescriptor.cpp
    Sources/EpiGraphicsDriverCommon/gfxSurface.epi
    Sources/EpiGraphicsDriverCommon/gfxSurface.h
    Sources/EpiGraphicsDriverCommon/gfxSurface.cpp
    Sources/EpiGraphicsDriverCommon/gfxWindow.epi
    Sources/EpiGraphicsDriverCommon/gfxWindow.h
    Sources/EpiGraphicsDriverCommon/gfxWindow.cpp
    Sources/EpiGraphicsDriverCommon/gfxSwapChain.epi
    Sources/EpiGraphicsDriverCommon/gfxSwapChain.h
    Sources/EpiGraphicsDriverCommon/gfxSwapChain.cpp
    Sources/EpiGraphicsDriverCommon/gfxRenderPass.epi
    Sources/EpiGraphicsDriverCommon/gfxRenderPass.h
    Sources/EpiGraphicsDriverCommon/gfxRenderPass.cpp
    Sources/EpiGraphicsDriverCommon/gfxPipelineLayout.epi
    Sources/EpiGraphicsDriverCommon/gfxPipelineLayout.h
    Sources/EpiGraphicsDriverCommon/gfxPipelineLayout.cpp
    Sources/EpiGraphicsDriverCommon/gfxPipeline.epi
    Sources/EpiGraphicsDriverCommon/gfxPipeline.h
    Sources/EpiGraphicsDriverCommon/gfxPipeline.cpp
    Sources/EpiGraphicsDriverCommon/gfxDeviceMemory.epi
    Sources/EpiGraphicsDriverCommon/gfxDeviceMemory.h
    Sources/EpiGraphicsDriverCommon/gfxDeviceMemory.cpp
    Sources/EpiGraphicsDriverCommon/gfxBuffer.epi
    Sources/EpiGraphicsDriverCommon/gfxBuffer.h
    Sources/EpiGraphicsDriverCommon/gfxBuffer.cpp
    Sources/EpiGraphicsDriverCommon/gfxImage.epi
    Sources/EpiGraphicsDriverCommon/gfxImage.h
    Sources/EpiGraphicsDriverCommon/gfxImage.cpp
    Sources/EpiGraphicsDriverCommon/gfxImageView.epi
    Sources/EpiGraphicsDriverCommon/gfxImageView.h
    Sources/EpiGraphicsDriverCommon/gfxImageView.cpp
    Sources/EpiGraphicsDriverCommon/gfxShaderProgram.epi
    Sources/EpiGraphicsDriverCommon/gfxShaderProgram.h
    Sources/EpiGraphicsDriverCommon/gfxShaderProgram.cpp
    Sources/EpiGraphicsDriverCommon/gfxFrameBuffer.epi
    Sources/EpiGraphicsDriverCommon/gfxFrameBuffer.h
    Sources/EpiGraphicsDriverCommon/gfxFrameBuffer.cpp
    Sources/EpiGraphicsDriverCommon/gfxCommandPool.epi
    Sources/EpiGraphicsDriverCommon/gfxCommandPool.h
    Sources/EpiGraphicsDriverCommon/gfxCommandPool.cpp
    Sources/EpiGraphicsDriverCommon/gfxCommandBuffer.epi
    Sources/EpiGraphicsDriverCommon/gfxCommandBuffer.h
    Sources/EpiGraphicsDriverCommon/gfxCommandBuffer.cpp
    Sources/EpiGraphicsDriverCommon/gfxDescriptorPool.epi
    Sources/EpiGraphicsDriverCommon/gfxDescriptorPool.h
    Sources/EpiGraphicsDriverCommon/gfxDescriptorPool.cpp
    Sources/EpiGraphicsDriverCommon/gfxDescriptorSet.epi
    Sources/EpiGraphicsDriverCommon/gfxDescriptorSet.h
    Sources/EpiGraphicsDriverCommon/gfxDescriptorSet.cpp
    Sources/EpiGraphicsDriverCommon/gfxDescriptorSetLayout.epi
    Sources/EpiGraphicsDriverCommon/gfxDescriptorSetLayout.h
    Sources/EpiGraphicsDriverCommon/gfxDescriptorSetLayout.cpp
    Sources/EpiGraphicsDriverCommon/gfxSampler.epi
    Sources/EpiGraphicsDriverCommon/gfxSampler.h
    Sources/EpiGraphicsDriverCommon/gfxSampler.cpp

    Sources/EpiGraphicsDriverCommon/Synchronization/gfxFence.epi
    Sources/EpiGraphicsDriverCommon/Synchronization/gfxFence.h
    Sources/EpiGraphicsDriverCommon/Synchronization/gfxFence.cpp
    Sources/EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.epi
    Sources/EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.h
    Sources/EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.cpp
)
get_target_property(EpiGraphicsDriverCommon_SOURCES EpiGraphicsDriverCommon SOURCES)
epi_pack_sources(${EpiGraphicsDriverCommon_SOURCES})

target_include_directories(EpiGraphicsDriverCommon
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiGraphicsDriverCommon
    PUBLIC
        EpiCore
)

find_package(NsightAftermath)

if (NsightAftermath_FOUND)
    target_link_libraries(EpiGraphicsDriverCommon
        PUBLIC
            NsightAftermath::NsightAftermath
    )

    target_compile_definitions(EpiGraphicsDriverCommon
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

epi_module_register(EpiGraphicsDriverCommon
    FOLDER "EpiLib"
)
