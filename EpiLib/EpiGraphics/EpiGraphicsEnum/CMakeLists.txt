project(EpiGraphicsEnum)

add_library(EpiGraphicsEnum
    Sources/EpiGraphicsEnum/EpiGraphicsEnum.epi
    Sources/EpiGraphicsEnum/EpiGraphicsEnum.h
    Sources/EpiGraphicsEnum/EpiGraphicsEnum.cpp
)

target_link_libraries(EpiGraphicsEnum
    PUBLIC
        EpiCore
)

get_target_property(EpiGraphicsEnum_SOURCES EpiGraphicsEnum SOURCES)
epi_pack_sources(${EpiGraphicsEnum_SOURCES})

target_include_directories(EpiGraphicsEnum
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

epi_module_register(EpiGraphicsEnum
    FOLDER "EpiLib"
)
