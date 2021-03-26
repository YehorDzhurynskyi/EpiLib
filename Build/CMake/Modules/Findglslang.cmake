#[=======================================================================[.rst:
Findglslang
----------

IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines :prop_tgt:`IMPORTED` target ``glslang``, if
glslang has been found.

Result Variables
^^^^^^^^^^^^^^^^

This module defines the following variables::

  glslang_FOUND             - "True" if glslang was found
  glslang_INCLUDE_DIRS      - include directories for glslang
  glslang_LIBRARIES         - link against this library to use glslang
  glslang_LIBRARIES_DEBUG   - link against this library to use glslang DEBUG

#]=======================================================================]

include(FindPackageHandleStandardArgs)
include(FindVulkanLibrary)

find_path(glslang_INCLUDE_DIR
    NAMES
        "glslang/Public/ShaderLang.h"
    PATHS
        "$ENV{VULKAN_SDK}/Include"
        "$ENV{VK_SDK_PATH}/Include"
)

find_path(SPIRV_INCLUDE_DIR
    NAMES
        "SPIRV/GlslangToSpv.h"
    PATHS
        "$ENV{VULKAN_SDK}/Include/glslang"
        "$ENV{VK_SDK_PATH}/Include/glslang"
)

find_vulkan_library(glslang)
find_vulkan_library(SPIRV)
find_vulkan_library(GenericCodeGen)
find_vulkan_library(MachineIndependent)
find_vulkan_library(OGLCompiler)
find_vulkan_library(OSDependent)

set(glslang_LIBRARIES)
set(glslang_LIBRARIES_DEBUG)
set(glslang_INCLUDE_DIRS)

list(APPEND glslang_LIBRARIES ${glslang_LIBRARY} ${SPIRV_LIBRARY} ${GenericCodeGen_LIBRARY} ${MachineIndependent_LIBRARY} ${OGLCompiler_LIBRARY} ${OSDependent_LIBRARY})
list(APPEND glslang_LIBRARIES_DEBUG ${glslangd_LIBRARY} ${SPIRVd_LIBRARY} ${GenericCodeGend_LIBRARY} ${MachineIndependentd_LIBRARY} ${OGLCompilerd_LIBRARY} ${OSDependentd_LIBRARY})
list(APPEND glslang_INCLUDE_DIRS ${glslang_INCLUDE_DIR} ${SPIRV_INCLUDE_DIR})

mark_as_advanced(
    glslang_LIBRARY
    glslangd_LIBRARY
    SPIRV_LIBRARY
    SPIRVd_LIBRARY
    GenericCodeGen_LIBRARY
    GenericCodeGend_LIBRARY
    MachineIndependent_LIBRARY
    MachineIndependentd_LIBRARY
    OGLCompiler_LIBRARY
    OGLCompilerd_LIBRARY
    OSDependent_LIBRARY
    OSDependentd_LIBRARY
    glslang_INCLUDE_DIR
    SPIRV_INCLUDE_DIR
)

find_package_handle_standard_args(glslang DEFAULT_MSG glslang_LIBRARIES glslang_LIBRARIES_DEBUG glslang_INCLUDE_DIRS)

if(glslang_FOUND AND NOT TARGET glslang)
    add_library(glslang INTERFACE IMPORTED)

    target_link_libraries(glslang
        INTERFACE
            $<$<NOT:$<CONFIG:Debug>>:${glslang_LIBRARIES}>$<$<CONFIG:Debug>:${glslang_LIBRARIES_DEBUG}>
    )

    target_include_directories(glslang
        INTERFACE
            ${glslang_INCLUDE_DIRS}
    )
endif()
