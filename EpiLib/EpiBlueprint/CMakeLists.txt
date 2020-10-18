project(EpiBlueprint)

add_library(EpiBlueprint
    Sources/EpiBlueprint/bpBlueprint.epi
    Sources/EpiBlueprint/bpBlueprint.h
    Sources/EpiBlueprint/bpBlueprint.cpp

    Sources/EpiBlueprint/Node/bpNodeBase.epi
    Sources/EpiBlueprint/Node/bpNodeBase.h
    Sources/EpiBlueprint/Node/bpNodeBase.cpp
    Sources/EpiBlueprint/Node/bpNodeImageProvider.epi
    Sources/EpiBlueprint/Node/bpNodeImageProvider.h
    Sources/EpiBlueprint/Node/bpNodeImageProvider.cpp
    Sources/EpiBlueprint/Node/bpNodeOperator.epi
    Sources/EpiBlueprint/Node/bpNodeOperator.h
    Sources/EpiBlueprint/Node/bpNodeOperator.cpp

    Sources/EpiBlueprint/Drawer/bpNodeDrawerImageProvider.epi
    Sources/EpiBlueprint/Drawer/bpNodeDrawerImageProvider.h
    Sources/EpiBlueprint/Drawer/bpNodeDrawerImageProvider.cpp
)
get_target_property(EpiBlueprint_SOURCES EpiBlueprint SOURCES)
epi_pack_sources(${EpiBlueprint_SOURCES})

target_include_directories(EpiBlueprint
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiBlueprint
    PUBLIC
        EpiGraphics
        EpiMultimedia
)

epi_module_register(EpiBlueprint
    FOLDER "EpiLib"
)

