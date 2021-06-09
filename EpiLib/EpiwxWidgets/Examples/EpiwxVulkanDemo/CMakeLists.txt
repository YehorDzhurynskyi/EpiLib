project(EpiwxVulkanDemo)

add_executable(EpiwxVulkanDemo demo.cpp)

get_target_property(EpiwxVulkanDemo_SOURCES EpiwxVulkanDemo SOURCES)
epi_pack_sources(${EpiwxVulkanDemo_SOURCES})

target_link_libraries(EpiwxVulkanDemo PUBLIC EpiwxWidgets)

epi_module_register(EpiwxVulkanDemo
    FOLDER "EpiLib/Examples"
)

configure_file("texture.jpg" . COPYONLY)
