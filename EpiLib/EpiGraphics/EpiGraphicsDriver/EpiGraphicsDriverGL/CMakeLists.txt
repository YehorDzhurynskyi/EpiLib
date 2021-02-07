project(EpiGraphicsDriverGL)

add_library(EpiGraphicsDriverGL
    Sources/EpiGraphicsDriverGL/gfxDriverGL.h
    Sources/EpiGraphicsDriverGL/gfxDriverGL.cpp
    Sources/EpiGraphicsDriverGL/gfxVertexArrayImplGL.h
    Sources/EpiGraphicsDriverGL/gfxVertexArrayImplGL.cpp
    Sources/EpiGraphicsDriverGL/gfxVertexBufferImplGL.h
    Sources/EpiGraphicsDriverGL/gfxVertexBufferImplGL.cpp
    Sources/EpiGraphicsDriverGL/gfxTextureImplGL.h
    Sources/EpiGraphicsDriverGL/gfxTextureImplGL.cpp
    Sources/EpiGraphicsDriverGL/gfxShaderProgramImplGL.h
    Sources/EpiGraphicsDriverGL/gfxShaderProgramImplGL.cpp
    Sources/EpiGraphicsDriverGL/gfxPhysicalDeviceImplGL.h
    Sources/EpiGraphicsDriverGL/gfxPhysicalDeviceImplGL.cpp
    Sources/EpiGraphicsDriverGL/gfxDeviceImplGL.h
    Sources/EpiGraphicsDriverGL/gfxDeviceImplGL.cpp
    Sources/EpiGraphicsDriverGL/gfxQueueImplGL.h
    Sources/EpiGraphicsDriverGL/gfxQueueImplGL.cpp
    Sources/EpiGraphicsDriverGL/gfxSurfaceImplGL.h
    Sources/EpiGraphicsDriverGL/gfxSurfaceImplGL.cpp
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
