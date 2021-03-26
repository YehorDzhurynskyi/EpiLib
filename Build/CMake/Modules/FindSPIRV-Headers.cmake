#[=======================================================================[.rst:
FindSPIRV-Headers
----------

IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines :prop_tgt:`IMPORTED` target ``SPIRV-Headers``, if
SPIRV-Headers has been found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables::

  SPIRV_Headers_FOUND          - "True" if SPIRV-Headers was found
  SPIRV_Headers_INCLUDE_DIRS   - include directories for SPIRV-Headers

#]=======================================================================]

include(FindPackageHandleStandardArgs)

find_path(SPIRV_Headers_INCLUDE_DIR
    NAMES
        "spirv-headers/spirv.h"
    PATHS
        "$ENV{VULKAN_SDK}/Include"
        "$ENV{VK_SDK_PATH}/Include"
)

set(SPIRV_Headers_INCLUDE_DIRS ${SPIRV_Headers_INCLUDE_DIR})

find_package_handle_standard_args(SPIRV_Headers DEFAULT_MSG SPIRV_Headers_INCLUDE_DIRS)

mark_as_advanced(SPIRV_Headers_INCLUDE_DIR)

if(SPIRV_Headers_FOUND AND NOT TARGET SPIRV-Headers)
    add_library(SPIRV-Headers INTERFACE IMPORTED)

    target_include_directories(SPIRV-Headers
        INTERFACE
            ${SPIRV_Headers_INCLUDE_DIRS}
    )
endif()
