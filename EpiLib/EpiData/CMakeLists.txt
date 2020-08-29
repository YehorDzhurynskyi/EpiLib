project(EpiData)

add_library(EpiData
    Sources/EpiData/dCollection.epi
    Sources/EpiData/dCollection.h
    Sources/EpiData/dCollection.cpp
)
get_target_property(EpiData_SOURCES EpiData SOURCES)
epi_pack_sources(${EpiData_SOURCES})

target_precompile_headers(EpiData REUSE_FROM EpiCore)

target_include_directories(EpiData
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiData
    PUBLIC
        EpiCore
)

epi_module_register(EpiData
    FOLDER "EpiLib"
)
