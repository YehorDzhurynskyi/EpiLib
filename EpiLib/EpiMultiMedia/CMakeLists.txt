project(EpiMultimedia)

add_library(EpiMultimedia
    Sources/EpiMultimedia/Resource/mmResourceManager.h
    Sources/EpiMultimedia/Resource/mmResourceManager.cpp
    Sources/EpiMultimedia/Resource/mmResource.epi
    Sources/EpiMultimedia/Resource/mmResource.h
    Sources/EpiMultimedia/Resource/mmResource.cpp
    Sources/EpiMultimedia/Resource/mmResourceAudio.epi
    Sources/EpiMultimedia/Resource/mmResourceAudio.h
    Sources/EpiMultimedia/Resource/mmResourceAudio.cpp
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
