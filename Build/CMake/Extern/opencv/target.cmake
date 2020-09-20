# TODO: opencv use a PRIVATE access modifier for its targets
# so `include` can't be linked normally
foreach (COMPONENT ${EXTERN_COMPONENTS})
    if (NOT TARGET ${COMPONENT})
        message(FATAL_ERROR "`${COMPONENT}` such component of `${EXTERN}` doesn't exists!")
    endif ()

    get_target_property(COMPONENT_INTERFACE_INCLUDE_DIRECTORIES ${COMPONENT} INTERFACE_INCLUDE_DIRECTORIES)

    get_target_property(COMPONENT_SOURCE_DIR ${COMPONENT} SOURCE_DIR)
    if (EXISTS "${COMPONENT_SOURCE_DIR}/include" AND IS_DIRECTORY "${COMPONENT_SOURCE_DIR}/include")
        get_target_property(COMPONENT_BINARY_DIR ${COMPONENT} BINARY_DIR)
        target_include_directories(${COMPONENT}
            PUBLIC
                $<BUILD_INTERFACE:${COMPONENT_SOURCE_DIR}/include>
                $<BUILD_INTERFACE:${COMPONENT_BINARY_DIR}/include>
                $<BUILD_INTERFACE:${COMPONENT_BINARY_DIR}>
                $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        )
    endif ()
endforeach ()

# TODO: check function exists
# `libtiff` does this check by itself, but in some reason it doesn't work properly
target_compile_definitions(libtiff
    PUBLIC
        HAVE_SNPRINTF=1
)
