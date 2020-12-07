project(EpiMultimedia)

add_library(EpiMultimedia
    Sources/EpiMultimedia/mmMediaBase.epi
    Sources/EpiMultimedia/mmMediaBase.h
    Sources/EpiMultimedia/mmMediaBase.cpp
    Sources/EpiMultimedia/mmAudio.epi
    Sources/EpiMultimedia/mmAudio.h
    Sources/EpiMultimedia/mmAudio.cpp
    Sources/EpiMultimedia/mmFrame.epi
    Sources/EpiMultimedia/mmFrame.h
    Sources/EpiMultimedia/mmFrame.cpp
    Sources/EpiMultimedia/mmVideo.epi
    Sources/EpiMultimedia/mmVideo.h
    Sources/EpiMultimedia/mmVideo.cpp

    Sources/EpiMultimedia/Image/mmImage.epi
    Sources/EpiMultimedia/Image/mmImage.h
    Sources/EpiMultimedia/Image/mmImage.cpp
    Sources/EpiMultimedia/Image/mmJobImage.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageBase.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageBase.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageBase.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageContrast.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageContrast.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageContrast.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageHSB.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageHSB.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageHSB.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageGamma.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageGamma.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageGamma.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageThreshold.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageThreshold.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageThreshold.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageSpatialDenoising.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageSpatialDenoising.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageSpatialDenoising.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageMedian.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageMedian.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageMedian.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageSharpening.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageSharpening.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageSharpening.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageHomomorphic.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageHomomorphic.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageHomomorphic.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageNoiseNormal.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageNoiseNormal.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageNoiseNormal.cpp
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageNoiseSaltAndPepper.epi
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageNoiseSaltAndPepper.h
    Sources/EpiMultimedia/Image/ViewModel/mmVMImageNoiseSaltAndPepper.cpp

    Sources/EpiMultimedia/Image/Provider/mmImageProviderBase.epi
    Sources/EpiMultimedia/Image/Provider/mmImageProviderBase.h
    Sources/EpiMultimedia/Image/Provider/mmImageProviderBase.cpp
    Sources/EpiMultimedia/Image/Provider/mmImageProviderInMemory.epi
    Sources/EpiMultimedia/Image/Provider/mmImageProviderInMemory.h
    Sources/EpiMultimedia/Image/Provider/mmImageProviderInMemory.cpp

    Sources/EpiMultimedia/Resource/mmResourceManager.h
    Sources/EpiMultimedia/Resource/mmResourceManager.cpp
    Sources/EpiMultimedia/Resource/mmJobResourceLoad.epi
    Sources/EpiMultimedia/Resource/mmJobResourceLoad.h
    Sources/EpiMultimedia/Resource/mmJobResourceLoad.cpp
    Sources/EpiMultimedia/Resource/mmJobResourceLoadDeep.epi
    Sources/EpiMultimedia/Resource/mmJobResourceLoadDeep.h
    Sources/EpiMultimedia/Resource/mmJobResourceLoadDeep.cpp
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
