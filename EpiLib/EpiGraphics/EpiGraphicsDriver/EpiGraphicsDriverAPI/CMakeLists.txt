project(EpiGraphicsDriverAPI)

add_library(EpiGraphicsDriverAPI INTERFACE)

target_sources(EpiGraphicsDriverAPI
    INTERFACE
        "Sources/EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"
)

target_link_libraries(EpiGraphicsDriverAPI
    INTERFACE
        EpiCore
)

get_target_property(EpiGraphicsDriverAPI_SOURCES EpiGraphicsDriverAPI INTERFACE_SOURCES)
epi_pack_sources(${EpiGraphicsDriverAPI_SOURCES})

target_include_directories(EpiGraphicsDriverAPI
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

epi_module_register(EpiGraphicsDriverAPI
    FOLDER "EpiLib"
)
