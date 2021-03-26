macro(find_vulkan_library name)
    string(REPLACE "-" "_" namevar ${name})

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        find_library(${namevar}_LIBRARY
            NAMES
                ${name}
            PATHS
                "$ENV{VULKAN_SDK}/Lib"
                "$ENV{VK_SDK_PATH}/Lib"
                "$ENV{VULKAN_SDK}/Bin"
                "$ENV{VK_SDK_PATH}/Bin"
                NO_SYSTEM_ENVIRONMENT_PATH
        )

        find_library(${namevar}d_LIBRARY
            NAMES
                ${name}d
            PATHS
                "$ENV{VULKAN_SDK}/Lib"
                "$ENV{VK_SDK_PATH}/Lib"
                "$ENV{VULKAN_SDK}/Bin"
                "$ENV{VK_SDK_PATH}/Bin"
                NO_SYSTEM_ENVIRONMENT_PATH
        )
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        find_library(${namevar}_LIBRARY
            NAMES
                ${name}
            PATHS
                "$ENV{VULKAN_SDK}/Lib32"
                "$ENV{VK_SDK_PATH}/Lib32"
                "$ENV{VULKAN_SDK}/Bin32"
                "$ENV{VK_SDK_PATH}/Bin32"
                NO_SYSTEM_ENVIRONMENT_PATH
        )

        find_library(${namevar}d_LIBRARY
            NAMES
                ${name}d
            PATHS
                "$ENV{VULKAN_SDK}/Lib32"
                "$ENV{VK_SDK_PATH}/Lib32"
                "$ENV{VULKAN_SDK}/Bin32"
                "$ENV{VK_SDK_PATH}/Bin32"
                NO_SYSTEM_ENVIRONMENT_PATH
        )
    endif()
endmacro()