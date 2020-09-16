project(EpiMultimedia)

add_library(EpiMultimedia
    Sources/EpiMultimedia/mmMediaBase.epi
    Sources/EpiMultimedia/mmMediaBase.h
    Sources/EpiMultimedia/mmMediaBase.cpp
    Sources/EpiMultimedia/mmAudio.epi
    Sources/EpiMultimedia/mmAudio.h
    Sources/EpiMultimedia/mmAudio.cpp

    Sources/EpiMultimedia/Resource/mmResourceManager.h
    Sources/EpiMultimedia/Resource/mmResourceManager.cpp
    Sources/EpiMultimedia/Resource/mmResource.epi
    Sources/EpiMultimedia/Resource/mmResource.h
    Sources/EpiMultimedia/Resource/mmResource.cpp
)
get_target_property(EpiMultimedia_SOURCES EpiMultimedia SOURCES)
epi_pack_sources(${EpiMultimedia_SOURCES})

target_include_directories(EpiMultimedia
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

epi_extern_add(FFmpeg DONT_ADD_SUBDIRECTORY)

target_link_libraries(EpiMultimedia
    PUBLIC
        EpiCore
        EpiData
        FFmpeg
)

epi_module_register(EpiMultimedia
    FOLDER "EpiLib"
)
