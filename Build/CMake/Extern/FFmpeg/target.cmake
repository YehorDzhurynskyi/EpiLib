set(FFMPEG_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/FFmpeg/FFmpeg/build")

set(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll" ".a")

find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h PATHS "${FFMPEG_BUILD_DIR}/include") 
find_library(AVCODEC_LIBRARY avcodec PATHS "${FFMPEG_BUILD_DIR}/lib" REQUIRED)

find_path(AVDEVICE_INCLUDE_DIR libavdevice/avdevice.h PATHS "${FFMPEG_BUILD_DIR}/include")
find_library(AVDEVICE_LIBRARY avdevice PATHS "${FFMPEG_BUILD_DIR}/lib" REQUIRED)

find_path(AVFILTER_INCLUDE_DIR libavfilter/avfilter.h PATHS "${FFMPEG_BUILD_DIR}/include")
find_library(AVFILTER_LIBRARY avfilter PATHS "${FFMPEG_BUILD_DIR}/lib" REQUIRED)

find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h PATHS "${FFMPEG_BUILD_DIR}/include") 
find_library(AVFORMAT_LIBRARY avformat PATHS "${FFMPEG_BUILD_DIR}/lib" REQUIRED)

find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h PATHS "${FFMPEG_BUILD_DIR}/include")
find_library(AVUTIL_LIBRARY avutil PATHS "${FFMPEG_BUILD_DIR}/lib" REQUIRED)

find_path(SWRESAMPLE_INCLUDE_DIR libswresample/swresample.h PATHS "${FFMPEG_BUILD_DIR}/include")
find_library(SWRESAMPLE_LIBRARY swresample PATHS "${FFMPEG_BUILD_DIR}/lib" REQUIRED)

find_path(SWSCALE_INCLUDE_DIR libswscale/swscale.h PATHS "${FFMPEG_BUILD_DIR}/include")
find_library(SWSCALE_LIBRARY swscale PATHS "${FFMPEG_BUILD_DIR}/lib" REQUIRED)

add_library(FFmpeg INTERFACE IMPORTED GLOBAL)

target_link_libraries(FFmpeg
    INTERFACE
        ${AVCODEC_LIBRARY}
        ${AVDEVICE_LIBRARY}
        ${AVFILTER_LIBRARY}
        ${AVFORMAT_LIBRARY}
        ${AVUTIL_LIBRARY}
        ${SWRESAMPLE_LIBRARY}
        ${SWSCALE_LIBRARY}
)

target_include_directories(FFmpeg
    INTERFACE
        ${AVCODEC_INCLUDE_DIR}
        ${AVDEVICE_INCLUDE_DIR}
        ${AVFILTER_INCLUDE_DIR}
        ${AVFORMAT_INCLUDE_DIR}
        ${AVUTIL_INCLUDE_DIR}
        ${SWRESAMPLE_INCLUDE_DIR}
        ${SWSCALE_INCLUDE_DIR}
)
