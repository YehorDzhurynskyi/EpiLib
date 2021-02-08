project(EpiGraphicsDriverImpl)

add_library(EpiGraphicsDriverImpl INTERFACE)

target_sources(EpiGraphicsDriverImpl
    INTERFACE
        Sources/EpiGraphicsDriverImpl/EpiGraphicsDriverImpl.h
)

target_link_libraries(EpiGraphicsDriverImpl
    INTERFACE
        EpiCore
        EpiGraphicsEnum
)

get_target_property(EpiGraphicsDriverImpl_SOURCES EpiGraphicsDriverImpl INTERFACE_SOURCES)
epi_pack_sources(${EpiGraphicsDriverImpl_SOURCES})

target_include_directories(EpiGraphicsDriverImpl
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

epi_module_register(EpiGraphicsDriverImpl
    FOLDER "EpiLib"
)
