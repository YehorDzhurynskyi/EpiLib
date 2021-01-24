project(glad)

# TODO: change directory based on the $<CONFIG>
add_library(glad STATIC
    OpenGL4.0-debug/src/glad.c
    OpenGL4.0-debug/include/glad/glad.h
    OpenGL4.0-debug/include/KHR/khrplatform.h
)

target_include_directories(glad
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/$<$<CONFIG:Debug>:OpenGL4.0-debug>$<$<OR:$<CONFIG:Release>,$<CONFIG:Profile>>:OpenGL4.0>>/include
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/$<$<CONFIG:Debug>:OpenGL4.0-debug>$<$<OR:$<CONFIG:Release>,$<CONFIG:Profile>>:OpenGL4.0>>/include
)
