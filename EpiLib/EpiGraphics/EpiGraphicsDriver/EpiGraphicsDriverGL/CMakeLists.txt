project(EpiGraphicsDriverGL)

add_library(EpiGraphicsDriverGL
    Sources/EpiGraphicsDriverGL/gfxDriverGL.h
    Sources/EpiGraphicsDriverGL/gfxDriverGL.cpp
)
get_target_property(EpiGraphicsDriverGL_SOURCES EpiGraphicsDriverGL SOURCES)
epi_pack_sources(${EpiGraphicsDriverGL_SOURCES})

add_subdirectory(Extern/glad)
epi_module_register(glad EXTERN
    FOLDER "EpiLib/Extern"
)

target_include_directories(EpiGraphicsDriverGL
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

target_link_libraries(EpiGraphicsDriverGL
    PRIVATE
        EpiGraphicsDriverAPI
        glad
)

epi_module_register(EpiGraphicsDriverGL
    FOLDER "EpiLib"
)
