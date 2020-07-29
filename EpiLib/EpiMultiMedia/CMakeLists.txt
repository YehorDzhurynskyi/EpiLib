project(EpiMultiMedia)

add_library(EpiMultiMedia
    EpiMultiMedia/pch.h
    EpiMultiMedia/pch.cpp

    EpiMultiMedia/test.cpp
)
get_target_property(EpiMultiMedia_SRCs EpiMultiMedia SOURCES)
epi_add_precompiled_header(EpiMultiMedia EpiMultiMedia/pch.h SOURCE_CXX EpiMultiMedia/pch.cpp)
epi_pack_sources(${EpiMultiMedia_SRCs})

set(FFMPEG_ARGS
    --arch=x86_64
    --target-os=win64
    --toolchain=msvc

    --enable-shared
    --disable-static

    --enable-asm
    --enable-yasm

    --disable-programs
    --disable-doc
)
string(JOIN " " FFMPEG_ARGS ${FFMPEG_ARGS})

set(FFMPEG_DIR ${CMAKE_CURRENT_BINARY_DIR}/Extern/FFmpeg)
epi_win_to_wsl_unix_path("${FFMPEG_DIR}/src" FFMPEG_SOURCE_WSL_DIR)
epi_win_to_wsl_unix_path("${FFMPEG_DIR}/install" FFMPEG_ISNTALL_WSL_DIR)

if (NOT GIT_EXECUTABLE)
    find_program(GIT_EXECUTABLE
        NAMES "bash-git.bat"
        PATHS "${EPI_BUILD_DIR}/Scripts/"
    )
endif()

ExternalProject_Add(FFmpeg
    SOURCE_DIR ${FFMPEG_DIR}/src
    BINARY_DIR ${FFMPEG_DIR}
    TMP_DIR ${FFMPEG_DIR}/tmp
    STAMP_DIR ${FFMPEG_DIR}/stamp
    DOWNLOAD_DIR ${FFMPEG_DIR}/download
    INSTALL_DIR ${FFMPEG_DIR}/install
    LOG_DIR ${FFMPEG_DIR}/log

    GIT_REPOSITORY "https://github.com/FFmpeg/FFmpeg.git"
    GIT_TAG "n4.2.1"

    GIT_SHALLOW 1
    GIT_PROGRESS 1

    CONFIGURE_COMMAND C:/Windows/sysnative/bash.exe -c "cd \"${FFMPEG_SOURCE_WSL_DIR}\" && ./configure ${FFMPEG_ARGS} --prefix=\"${FFMPEG_ISNTALL_WSL_DIR}\""
    BUILD_COMMAND C:/Windows/sysnative/bash.exe -c "cd \"${FFMPEG_SOURCE_WSL_DIR}\" && make && find . -name *.d -type f -delete"
    INSTALL_COMMAND C:/Windows/sysnative/bash.exe -c "cd \"${FFMPEG_SOURCE_WSL_DIR}\" && make install"
)
epi_register_extern_target(FFmpeg)

ExternalProject_Get_Property(FFmpeg INSTALL_DIR)

target_include_directories(EpiMultiMedia
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        ${INSTALL_DIR}/include
)

macro(add_ffmpeglib lib libversion)
    epi_get_libname(${lib} staticlibname dynamiclibname ${libversion})

    target_link_libraries(EpiMultiMedia
        PUBLIC
            ${INSTALL_DIR}/bin/${staticlibname}
    )

    set_property(
        TARGET EpiMultiMedia
        APPEND PROPERTY
            EPI_DLL_LIBS ${INSTALL_DIR}/bin/${dynamiclibname}
    )
endmacro()

add_ffmpeglib("avcodec" "58")
add_ffmpeglib("avdevice" "58")
add_ffmpeglib("avfilter" "7")
add_ffmpeglib("avformat" "58")
add_ffmpeglib("avutil" "56")
add_ffmpeglib("swresample" "3")
add_ffmpeglib("swscale" "5")

add_dependencies(EpiMultiMedia FFmpeg)
target_link_libraries(EpiMultiMedia
    PUBLIC
        EpiCore
)

epi_module_register(EpiMultiMedia)
