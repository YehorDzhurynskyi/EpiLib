#[=======================================================================[.rst:
Findshaderc
----------

IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines :prop_tgt:`IMPORTED` target ``shaderc``, if
shaderc has been found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables::

  shaderc_FOUND             - "True" if shaderc was found
  shaderc_INCLUDE_DIRS      - include directories for shaderc
  shaderc_LIBRARIES         - link against this library to use shaderc
  shaderc_LIBRARIES_DEBUG   - link against this library to use shaderc DEBUG

#]=======================================================================]

include(FindPackageHandleStandardArgs)
include(FindVulkanLibrary)

find_path(shaderc_INCLUDE_DIR
    NAMES
        "shaderc/shaderc.h"
    PATHS
        "$ENV{VULKAN_SDK}/Include"
        "$ENV{VK_SDK_PATH}/Include"
)

set(shaderc_LIBRARIES)
set(shaderc_LIBRARIES_DEBUG)
set(shaderc_INCLUDE_DIRS ${shaderc_INCLUDE_DIR})

find_package(SPIRV-Tools)
find_package(SPIRV-Headers)
find_package(glslang)

if (TARGET SPIRV-Tools AND TARGET SPIRV-Headers AND TARGET glslang)
    find_vulkan_library(shaderc)
    find_vulkan_library(shaderc_util)

    if (shaderc_LIBRARY AND shaderc_util_LIBRARY)
        list(APPEND shaderc_LIBRARIES ${shaderc_LIBRARY} ${shaderc_util_LIBRARY})
        list(APPEND shaderc_LIBRARIES_DEBUG ${shadercd_LIBRARY} ${shaderc_utild_LIBRARY})

        mark_as_advanced(shaderc_LIBRARY shadercd_LIBRARY shaderc_util_LIBRARY shaderc_utild_LIBRARY)
    endif()
endif()

if (NOT shaderc_LIBRARIES OR NOT shaderc_LIBRARIES_DEBUG)
    find_vulkan_library(shaderc_combined)

    list(APPEND shaderc_LIBRARIES ${shaderc_combined_LIBRARY})
    list(APPEND shaderc_LIBRARIES_DEBUG ${shaderc_combinedd_LIBRARY})

    mark_as_advanced(shaderc_combined_LIBRARY shaderc_combinedd_LIBRARY)
endif()

mark_as_advanced(shaderc_INCLUDE_DIR)

find_package_handle_standard_args(shaderc DEFAULT_MSG shaderc_LIBRARIES shaderc_LIBRARIES_DEBUG shaderc_INCLUDE_DIRS)

if(shaderc_FOUND AND NOT TARGET shaderc)
    add_library(shaderc INTERFACE IMPORTED)

    target_link_libraries(shaderc
        INTERFACE
            $<$<NOT:$<CONFIG:Debug>>:${shaderc_LIBRARIES}>$<$<CONFIG:Debug>:${shaderc_LIBRARIES_DEBUG}>
    )

    if (TARGET SPIRV-Tools AND TARGET SPIRV-Headers AND TARGET glslang)
        target_link_libraries(shaderc
            INTERFACE
                SPIRV-Tools
                SPIRV-Headers
                glslang
        )
    endif()

    target_include_directories(shaderc
        INTERFACE
            ${shaderc_INCLUDE_DIRS}
    )
endif()
