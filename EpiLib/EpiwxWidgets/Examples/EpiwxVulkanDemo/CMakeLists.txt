project(EpiwxVulkanDemo)

add_executable(EpiwxVulkanDemo demo.cpp)

get_target_property(EpiwxVulkanDemo_SOURCES EpiwxVulkanDemo SOURCES)
epi_pack_sources(${EpiwxVulkanDemo_SOURCES})

epi_extern_add(tinyobjloader)

target_link_libraries(EpiwxVulkanDemo
    PUBLIC
        EpiwxWidgets
        tinyobjloader
)

epi_module_register(EpiwxVulkanDemo
    FOLDER "EpiLib/Examples"
)

configure_file("texture.jpg" . COPYONLY)
configure_file("viking_room.obj" . COPYONLY)
configure_file("viking_room.png" . COPYONLY)
