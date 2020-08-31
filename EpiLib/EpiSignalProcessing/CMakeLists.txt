project(EpiSignalProcessing)

add_library(EpiSignalProcessing
    Sources/EpiSignalProcessing/spMath.epi
    Sources/EpiSignalProcessing/spMath.h
    Sources/EpiSignalProcessing/spMath.cpp
)
get_target_property(EpiSignalProcessing_SOURCES EpiSignalProcessing SOURCES)
epi_pack_sources(${EpiSignalProcessing_SOURCES})

target_include_directories(EpiSignalProcessing
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiSignalProcessing
    PUBLIC
        EpiCore
        EpiData
)

epi_module_register(EpiSignalProcessing
    FOLDER "EpiLib"
)
