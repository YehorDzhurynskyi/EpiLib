project(EpiMultimedia)

add_library(EpiMultimedia
    Sources/EpiMultimedia/mmMediaBase.epi
    Sources/EpiMultimedia/mmMediaBase.h
    Sources/EpiMultimedia/mmMediaBase.cpp
    Sources/EpiMultimedia/mmAudio.epi
    Sources/EpiMultimedia/mmAudio.h
    Sources/EpiMultimedia/mmAudio.cpp
    Sources/EpiMultimedia/mmImage.epi
    Sources/EpiMultimedia/mmImage.h
    Sources/EpiMultimedia/mmImage.cpp
    Sources/EpiMultimedia/mmFrame.epi
    Sources/EpiMultimedia/mmFrame.h
    Sources/EpiMultimedia/mmFrame.cpp
    Sources/EpiMultimedia/mmVideo.epi
    Sources/EpiMultimedia/mmVideo.h
    Sources/EpiMultimedia/mmVideo.cpp

    Sources/EpiMultimedia/Resource/mmResourceManager.h
    Sources/EpiMultimedia/Resource/mmResourceManager.cpp
    Sources/EpiMultimedia/Resource/mmResource.epi
    Sources/EpiMultimedia/Resource/mmResource.h
    Sources/EpiMultimedia/Resource/mmResource.cpp
)
get_target_property(EpiMultimedia_SOURCES EpiMultimedia SOURCES)
epi_pack_sources(${EpiMultimedia_SOURCES})

target_include_directories(EpiMultimedia
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sources>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Sources>
)

epi_extern_add(FFmpeg DONT_ADD_SUBDIRECTORY)
epi_extern_add(opencv
    COMPONENTS
        opencv_core
        opencv_highgui
        opencv_calib3d
        opencv_dnn
        opencv_features2d
        opencv_flann
        opencv_gapi
        opencv_imgcodecs
        opencv_imgproc
        opencv_ml
        opencv_objdetect
        opencv_photo
        opencv_stitching
        opencv_ts
        opencv_video
        opencv_videoio
)

target_link_libraries(EpiMultimedia
    PUBLIC
        EpiCore
        EpiData
        FFmpeg
        opencv
)

epi_module_register(EpiMultimedia
    FOLDER "EpiLib"
)
