project(EpiUI)

add_library(EpiUI
    EpiUI/pch.h
    EpiUI/pch.cpp

    EpiUI/uiViewModel.epi
    EpiUI/uiViewModel.h
    EpiUI/uiViewModel.cpp

    EpiUI/uiAction.epi
    EpiUI/uiAction.h
    EpiUI/uiAction.cpp

    EpiUI/uiCamera.epi
    EpiUI/uiCamera.h
    EpiUI/uiCamera.cpp

    EpiUI/uiContext.epi
    EpiUI/uiContext.h
    EpiUI/uiContext.cpp

    EpiUI/uiWidget.epi
    EpiUI/uiWidget.h
    EpiUI/uiWidget.cpp

    EpiUI/uiPage.epi
    EpiUI/uiPage.h
    EpiUI/uiPage.cpp

    EpiUI/Layout/uiLayout.epi
    EpiUI/Layout/uiLayout.h
    EpiUI/Layout/uiLayout.cpp
    EpiUI/Layout/uiLayoutBox.epi
    EpiUI/Layout/uiLayoutBox.h
    EpiUI/Layout/uiLayoutBox.cpp
)
get_target_property(EpiUI_SRCs EpiUI SOURCES) 
epi_add_precompiled_header(EpiUI EpiUI/pch.h SOURCE_CXX EpiUI/pch.cpp)
epi_pack_sources(${EpiUI_SRCs})

target_include_directories(EpiUI
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiUI
    PUBLIC
        EpiCore
        EpiGraphics
)

epi_module_register(EpiUI)
