#[=======================================================================[.rst:
FindSPIRV-Tools
----------

IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines :prop_tgt:`IMPORTED` target ``SPIRV-Tools``, if
SPIRV-Tools has been found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables::

  SPIRV_Tools_FOUND             - "True" if SPIRV-Tools was found
  SPIRV_Tools_INCLUDE_DIRS      - include directories for SPIRV-Tools
  SPIRV_Tools_LIBRARIES         - link against this library to use SPIRV-Tools
  SPIRV_Tools_LIBRARIES_DEBUG   - link against this library to use SPIRV-Tools DEBUG

#]=======================================================================]

include(FindPackageHandleStandardArgs)
include(FindVulkanLibrary)

find_path(SPIRV_Tools_INCLUDE_DIR
    NAMES
        "spirv-tools/libspirv.h"
    PATHS
        "$ENV{VULKAN_SDK}/Include"
        "$ENV{VK_SDK_PATH}/Include"
)

find_vulkan_library(SPIRV-Tools)
find_vulkan_library(SPIRV-Tools-opt)
find_vulkan_library(SPIRV-Tools-link)

set(SPIRV_Tools_LIBRARIES)
set(SPIRV_Tools_LIBRARIES_DEBUG)
set(SPIRV_Tools_INCLUDE_DIRS ${SPIRV_Tools_INCLUDE_DIR})

list(APPEND SPIRV_Tools_LIBRARIES ${SPIRV_Tools_LIBRARY} ${SPIRV_Tools_opt_LIBRARY} ${SPIRV_Tools_link_LIBRARY})
list(APPEND SPIRV_Tools_LIBRARIES_DEBUG ${SPIRV_Toolsd_LIBRARY} ${SPIRV_Tools_optd_LIBRARY} ${SPIRV_Tools_linkd_LIBRARY})

mark_as_advanced(SPIRV_Tools_LIBRARY SPIRV_Toolsd_LIBRARY SPIRV_Tools_opt_LIBRARY SPIRV_Tools_optd_LIBRARY SPIRV_Tools_link_LIBRARY SPIRV_Tools_linkd_LIBRARY SPIRV_Tools_INCLUDE_DIR)

find_package_handle_standard_args(SPIRV_Tools DEFAULT_MSG SPIRV_Tools_LIBRARIES SPIRV_Tools_LIBRARIES_DEBUG SPIRV_Tools_INCLUDE_DIRS)

if(SPIRV_Tools_FOUND AND NOT TARGET SPIRV-Tools)
    add_library(SPIRV-Tools INTERFACE IMPORTED)

    target_link_libraries(SPIRV-Tools
        INTERFACE
            $<$<NOT:$<CONFIG:Debug>>:${SPIRV_Tools_LIBRARIES}>$<$<CONFIG:Debug>:${SPIRV_Tools_LIBRARIES_DEBUG}>
    )

    target_include_directories(SPIRV-Tools
        INTERFACE
            ${SPIRV_Tools_INCLUDE_DIRS}
    )
endif()
