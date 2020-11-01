project(EpiData)

add_library(EpiData
    Sources/EpiData/Series/dSeriesBase.epi
    Sources/EpiData/Series/dSeriesBase.h
    Sources/EpiData/Series/dSeriesBase.cpp

    Sources/EpiData/Series/dSeriesf.epi
    Sources/EpiData/Series/dSeriesf.h
    Sources/EpiData/Series/dSeriesf.cpp
    Sources/EpiData/Series/dSeries1Df.epi
    Sources/EpiData/Series/dSeries1Df.h
    Sources/EpiData/Series/dSeries1Df.cpp
    Sources/EpiData/Series/dSeries2Df.epi
    Sources/EpiData/Series/dSeries2Df.h
    Sources/EpiData/Series/dSeries2Df.cpp

    Sources/EpiData/Series/dSeriesc.epi
    Sources/EpiData/Series/dSeriesc.h
    Sources/EpiData/Series/dSeriesc.cpp
    Sources/EpiData/Series/dSeries1Dc.epi
    Sources/EpiData/Series/dSeries1Dc.h
    Sources/EpiData/Series/dSeries1Dc.cpp
    Sources/EpiData/Series/dSeries2Dc.epi
    Sources/EpiData/Series/dSeries2Dc.h
    Sources/EpiData/Series/dSeries2Dc.cpp

    Sources/EpiData/Series/dSeriesY.epi
    Sources/EpiData/Series/dSeriesY.h
    Sources/EpiData/Series/dSeriesY.cpp

    Sources/EpiData/Series/dSeriesXY.epi
    Sources/EpiData/Series/dSeriesXY.h
    Sources/EpiData/Series/dSeriesXY.cpp
)
get_target_property(EpiData_SOURCES EpiData SOURCES)
epi_pack_sources(${EpiData_SOURCES})

epi_extern_add(fftw3f)

# TODO: fix
get_target_property(FFTW3F_SOURCE_DIR fftw3f SOURCE_DIR)

target_include_directories(EpiData
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
        ${FFTW3F_SOURCE_DIR}/api
)

target_link_libraries(EpiData
    PUBLIC
        EpiCore
        fftw3f
)

epi_module_register(EpiData
    FOLDER "EpiLib"
)
