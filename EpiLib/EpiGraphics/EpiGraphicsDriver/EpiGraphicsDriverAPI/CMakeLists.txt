project(EpiGraphicsDriverAPI)

add_library(EpiGraphicsDriverAPI
    Sources/EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h
    Sources/EpiGraphicsDriverAPI/EpiGraphicsDriverAPIEnum.epi
    Sources/EpiGraphicsDriverAPI/EpiGraphicsDriverAPIEnum.h
    Sources/EpiGraphicsDriverAPI/EpiGraphicsDriverAPIEnum.cpp
)

target_link_libraries(EpiGraphicsDriverAPI
    PUBLIC
        EpiCore
)

get_target_property(EpiGraphicsDriverAPI_SOURCES EpiGraphicsDriverAPI SOURCES)
epi_pack_sources(${EpiGraphicsDriverAPI_SOURCES})

target_include_directories(EpiGraphicsDriverAPI
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

epi_module_register(EpiGraphicsDriverAPI
    FOLDER "EpiLib"
)
