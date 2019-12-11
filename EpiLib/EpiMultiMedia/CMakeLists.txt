project(EpiMultiMedia)

add_library(EpiMultiMedia
    EpiMultiMedia/pch.h
    EpiMultiMedia/pch.cpp

    EpiMultiMedia/test.cpp
)
get_target_property(EpiMultiMedia_SRCs EpiMultiMedia SOURCES)
epi_add_precompiled_header(EpiMultiMedia EpiMultiMedia/pch.h SOURCE_CXX EpiMultiMedia/pch.cpp)
epi_pack_sources(${EpiMultiMedia_SRCs})

include(ExternalProject)

if (NOT GIT_EXECUTABLE)
    find_program(GIT_EXECUTABLE
        NAMES "bash-git.bat"
        PATHS "${EPI_BUILD_DIR}/WSL/"
    )
endif()

set( proj ffmpeg )
set( SHARED_FFMPEG )

set(BASIC
        --extra-ldflags=-L/usr/local/lib
        --extra-cflags=-I/usr/local/include
        --enable-gpl
        --enable-libx264)

ExternalProject_Add(FFmpeg
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Extern/FFmpeg
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Extern/FFmpeg

    GIT_REPOSITORY "https://github.com/FFmpeg/FFmpeg.git"
    GIT_TAG "n4.2.1"

    GIT_SHALLOW 1
    GIT_PROGRESS 1

    # replace with a epi_wsl_path_convert function so "C:/..." become "/mnt/c/..."
    CONFIGURE_COMMAND C:/Windows/sysnative/bash.exe -c /mnt/c/Users/yadzh/Projects/BloodSystem/Extern/EpiLib/EpiLib/EpiMultiMedia/Extern/FFmpeg/configure --prefix=./INSTALL ${SHARED_FFMPEG} ${FFMPEG_GPL_FLAG} ${BASIC}
    BUILD_COMMAND C:/Windows/sysnative/bash.exe -c make
)

epi_register_extern_target(FFmpeg)

target_include_directories(EpiMultiMedia
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

epi_set_common_target_properties(EpiMultiMedia)
