project(EpiData)

add_library(EpiData
    Sources/EpiData/Series/dSeriesBase.epi
    Sources/EpiData/Series/dSeriesBase.h
    Sources/EpiData/Series/dSeriesBase.cpp

    Sources/EpiData/Series/dSeriesY.epi
    Sources/EpiData/Series/dSeriesY.h
    Sources/EpiData/Series/dSeriesY.cpp

    Sources/EpiData/Series/dSeriesXY.epi
    Sources/EpiData/Series/dSeriesXY.h
    Sources/EpiData/Series/dSeriesXY.cpp

    Sources/EpiData/Series/dSeriesYComplex.epi
    Sources/EpiData/Series/dSeriesYComplex.h
    Sources/EpiData/Series/dSeriesYComplex.cpp
)
get_target_property(EpiData_SOURCES EpiData SOURCES)
epi_pack_sources(${EpiData_SOURCES})

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
