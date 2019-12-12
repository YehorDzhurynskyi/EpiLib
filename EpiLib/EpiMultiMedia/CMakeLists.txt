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
        PATHS "${EPI_BUILD_DIR}/Scripts/"
    )
endif()

set(FFMPEG_ARGS
    --arch=x86_64
    --target-os=win64
    --toolchain=msvc

    --enable-shared
    --disable-static

    --enable-asm
    --enable-yasm

    --disable-ffserver
    --disable-avdevice
    --disable-swscale
    --disable-doc
    --disable-ffplay
    --disable-ffprobe
    --disable-ffmpeg
    --disable-bzlib
    --disable-libopenjpeg
    --disable-iconv
    --disable-zlib
)

set(FFMPEG_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Extern/FFmpeg)

ExternalProject_Add(FFmpeg
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Extern/FFmpeg
    BINARY_DIR ${FFMPEG_BINARY_DIR}
    TMP_DIR ${FFMPEG_BINARY_DIR}/tmp
    STAMP_DIR ${FFMPEG_BINARY_DIR}/stamp
    DOWNLOAD_DIR ${FFMPEG_BINARY_DIR}/download
    INSTALL_DIR ${FFMPEG_BINARY_DIR}/install
    LOG_DIR ${FFMPEG_BINARY_DIR}/log

    GIT_REPOSITORY "https://github.com/FFmpeg/FFmpeg.git"
    GIT_TAG "n4.2.1"

    GIT_SHALLOW 1
    GIT_PROGRESS 1

    # replace with a epi_wsl_path_convert function so "C:/..." become "/mnt/c/..."
    CONFIGURE_COMMAND C:/Windows/sysnative/bash.exe -c /mnt/c/Users/yadzh/Projects/BloodSystem/Extern/EpiLib/EpiLib/EpiMultiMedia/Extern/FFmpeg/configure ${FFMPEG_ARGS} --prefix=/mnt/c/Users/yadzh/Projects/BloodSystem/_projects/Visual Studio 16 2019 x64/Extern/EpiLib/EpiLib/EpiMultiMedia/Extern/FFmpeg/install/
    BUILD_COMMAND C:/Windows/sysnative/bash.exe -c make
    INSTALL_COMMAND C:/Windows/sysnative/bash.exe -c make install
)

epi_register_extern_target(FFmpeg)

target_include_directories(EpiMultiMedia
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

epi_set_common_target_properties(EpiMultiMedia)
