project(EpiGraphicsDriverCommon)

add_library(EpiGraphicsDriverCommon
    Sources/EpiGraphicsDriverCommon/gfxDriverInternal.h
    Sources/EpiGraphicsDriverCommon/gfxPhysicalDevice.epi
    Sources/EpiGraphicsDriverCommon/gfxPhysicalDevice.h
    Sources/EpiGraphicsDriverCommon/gfxPhysicalDevice.cpp
    Sources/EpiGraphicsDriverCommon/gfxDevice.epi
    Sources/EpiGraphicsDriverCommon/gfxDevice.h
    Sources/EpiGraphicsDriverCommon/gfxDevice.cpp
    Sources/EpiGraphicsDriverCommon/gfxEnum.epi
    Sources/EpiGraphicsDriverCommon/gfxEnum.h
    Sources/EpiGraphicsDriverCommon/gfxEnum.cpp
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

epi_module_register(EpiGraphicsDriverCommon
    FOLDER "EpiLib"
)
