project(EpiAdapterQt)

add_library(EpiAdapterQt
    EpiAdapterQt/pch.h
    EpiAdapterQt/pch.cpp

    EpiAdapterQt/QtObjectModel.h
    EpiAdapterQt/QtObjectModel.cpp

    EpiAdapterQt/QtObjectDelegate.h
    EpiAdapterQt/QtObjectDelegate.cpp

    EpiAdapterQt/QtObjectModelItem.h
    EpiAdapterQt/QtObjectModelItem.cpp

#    EpiAdapterQt/QtEpiPropertyBrowser.h
#    EpiAdapterQt/QtEpiPropertyBrowser.cpp

#    EpiAdapterQt/QtEpiPropertyManager.h
#    EpiAdapterQt/QtEpiPropertyManager.cpp
)
get_target_property(EpiAdapterQt_SRCs EpiAdapterQt SOURCES) 
epi_add_precompiled_header(EpiAdapterQt EpiAdapterQt/pch.h SOURCE_CXX EpiAdapterQt/pch.cpp)
epi_pack_sources(${EpiAdapterQt_SRCs})

find_package(Qt5 COMPONENTS Core Widgets Gui PrintSupport REQUIRED)

add_subdirectory(Extern/QtPropertyBrowser)
epi_register_extern_target(QtPropertyBrowser)

target_include_directories(EpiAdapterQt
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(EpiAdapterQt
    PUBLIC
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::PrintSupport
        QtPropertyBrowser
        EpiCore
)

epi_set_common_target_properties(EpiAdapterQt)
