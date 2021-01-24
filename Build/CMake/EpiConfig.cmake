if (0)
    set(EPI_BUILD "Unknown" CACHE STRING "" FORCE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)
    if (CMAKE_BUILD_TYPE_TOLOWER STREQUAL debug)
        set(EPI_BUILD_DEBUG ON CACHE BOOL "" FORCE)
        set(EPI_BUILD "Debug" CACHE STRING "" FORCE)
    endif()

    if (CMAKE_BUILD_TYPE_TOLOWER STREQUAL release)
        set(EPI_BUILD_RELEASE ON CACHE BOOL "" FORCE)
        set(EPI_BUILD "Release" CACHE STRING "" FORCE)
    endif()

    if (CMAKE_BUILD_TYPE_TOLOWER STREQUAL profile)
        set(EPI_BUILD_PROFILE ON CACHE BOOL "" FORCE)
        set(EPI_BUILD "Profile" CACHE STRING "" FORCE)
    endif()

    if (EPI_BUILD STREQUAL Unknown)
        message(FATAL_ERROR "Couldn't determine a build configuration: ${EPI_BUILD}")
    else()
        message(STATUS "EPI_BUILD: ${EPI_BUILD}")
    endif()
endif()

set(CMAKE_CXX_FLAGS_PROFILE ${CMAKE_CXX_FLAGS_RELEASE})

set(EPI_PLATFORM "Unknown" CACHE STRING "" FORCE)
string(TOLOWER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME_TOLOWER)
if (CMAKE_SYSTEM_NAME_TOLOWER STREQUAL windows)
    set(EPI_PLATFORM_WINDOWS ON CACHE BOOL "" FORCE)
    set(EPI_PLATFORM "Windows" CACHE STRING "" FORCE)
endif()

if (EPI_PLATFORM STREQUAL Unknown)
    message(FATAL_ERROR "Couldn't determine a platform: ${EPI_PLATFORM}")
endif()

try_run(EPI_RUN_RESULT
        EPI_COMPILE_RESULT
        "${CMAKE_BINARY_DIR}"
        "${EPI_DIR}/Build/CMake/Check/cmake_check_cpu_arch.cpp"
        RUN_OUTPUT_VARIABLE EPI_CPU
        COMPILE_OUTPUT_VARIABLE EPI_COMPILE_OUTPUT
)

if (NOT EPI_COMPILE_RESULT)
    message(FATAL_ERROR "Failed to compile: ${EPI_COMPILE_OUTPUT}")
endif()

if (EPI_CPU STREQUAL Unknown)
    message(FATAL_ERROR "Failed to determine CPU architecture!")
elseif (EPI_CPU STREQUAL x86_64)
    set(EPI_CPU_X86 ON CACHE BOOL "" FORCE)
endif()

epi_extern_add(cpu_features IMPORTED)

message(STATUS "EPI_PLATFORM: ${EPI_PLATFORM}")
message(STATUS "EPI_CPU: ${EPI_CPU}")

if (EPI_CPU_X86)
    try_run(EPI_RUN_RESULT
            EPI_COMPILE_RESULT
            "${CMAKE_BINARY_DIR}"
            "${EPI_DIR}/Build/CMake/Check/cmake_check_cpu_x86_vendor.cpp"
            RUN_OUTPUT_VARIABLE EPI_CPU_X86_VENDOR
            COMPILE_OUTPUT_VARIABLE EPI_COMPILE_OUTPUT
            LINK_LIBRARIES epiimported::cpu_features
    )

    if (NOT EPI_COMPILE_RESULT)
        message(FATAL_ERROR "Failed to compile: ${EPI_COMPILE_OUTPUT}")
    endif()

    string(TOLOWER ${EPI_CPU_X86_VENDOR} EPI_CPU_X86_VENDOR_TOLOWER)
    string(FIND ${EPI_CPU_X86_VENDOR_TOLOWER} "intel" EPI_CPU_X86_VENDOR_TOLOWER_INTEL)
    string(FIND ${EPI_CPU_X86_VENDOR_TOLOWER} "amd" EPI_CPU_X86_VENDOR_TOLOWER_AMD)

    if (NOT EPI_CPU_X86_VENDOR_TOLOWER_INTEL EQUAL -1)
        set(EPI_CPU_X86_VENDOR_INTEL ON CACHE BOOL "" FORCE)
    elseif (NOT EPI_CPU_X86_VENDOR_TOLOWER_AMD EQUAL -1)
        set(EPI_CPU_X86_VENDOR_AMD ON CACHE BOOL "" FORCE)
    else()
        message(FATAL_ERROR "Unknown CPU vendor!")
    endif()

    message(STATUS "EPI_CPU_X86_VENDOR: ${EPI_CPU_X86_VENDOR}")

    try_run(EPI_RUN_RESULT
            EPI_COMPILE_RESULT
            "${CMAKE_BINARY_DIR}"
            "${EPI_DIR}/Build/CMake/Check/cmake_check_cpu_x86_uarch.cpp"
            RUN_OUTPUT_VARIABLE EPI_CPU_X86_UARCH
            COMPILE_OUTPUT_VARIABLE EPI_COMPILE_OUTPUT
            LINK_LIBRARIES epiimported::cpu_features
    )

    if (NOT EPI_COMPILE_RESULT)
        message(FATAL_ERROR "Failed to compile: ${EPI_COMPILE_OUTPUT}")
    endif()

    if (EPI_CPU_X86_UARCH STREQUAL Unknown)
        message(FATAL_ERROR "Failed to determine CPU microarchitecture!")
    else()
        set(EPI_CPU_X86_UARCH_${EPI_CPU_X86_UARCH} ON CACHE BOOL "" FORCE)
        message(STATUS "EPI_CPU_X86_UARCH: ${EPI_CPU_X86_UARCH}")
    endif()

    set(EPI_CPU_X86_FEATURE_LIST
        "FPU"
        "TSC"
        "CX8"
        "CLFSH"
        "MMX"
        "AES"
        "ERMS"
        "F16C"
        "FMA4"
        "FMA3"
        "VAES"
        "VPCLMULQDQ"
        "BMI1"
        "HLE"
        "BMI2"
        "RTM"
        "RDSEED"
        "CLFLUSHOPT"
        "CLWB"
        "SSE"
        "SSE2"
        "SSE3"
        "SSSE3"
        "SSE4_1"
        "SSE4_2"
        "SSE4A"
        "AVX"
        "AVX2"
        "AVX512F"
        "AVX512CD"
        "AVX512ER"
        "AVX512PF"
        "AVX512BW"
        "AVX512DQ"
        "AVX512VL"
        "AVX512IFMA"
        "AVX512VBMI"
        "AVX512VBMI2"
        "AVX512VNNI"
        "AVX512BITALG"
        "AVX512VPOPCNTDQ"
        "AVX512_4VNNIW"
        "AVX512_4VBMI2"
        "AVX512_SECOND_FMA"
        "AVX512_4FMAPS"
        "AVX512_BF16"
        "AVX512_VP2INTERSECT"
        "AMX_BF16"
        "AMX_TILE"
        "AMX_INT8"
        "PCLMULQDQ"
        "SMX"
        "SGX"
        "CX16"
        "SHA"
        "POPCNT"
        "MOVBE"
        "RDRND"
        "DCA"
        "SS"
    )

    foreach(EPI_CPU_X86_FEATURE ${EPI_CPU_X86_FEATURE_LIST})
        try_run(EPI_RUN_RESULT
                EPI_COMPILE_RESULT
                "${CMAKE_BINARY_DIR}"
                "${EPI_DIR}/Build/CMake/Check/cmake_check_cpu_x86_feature.cpp"
                COMPILE_DEFINITIONS -DEPI_CPU_X86_FEATURE=${EPI_CPU_X86_FEATURE}
                COMPILE_OUTPUT_VARIABLE EPI_COMPILE_OUTPUT
                LINK_LIBRARIES epiimported::cpu_features
        )

        if (NOT EPI_COMPILE_RESULT)
            message(FATAL_ERROR "Failed to compile: ${EPI_COMPILE_OUTPUT}")
        endif()

        if (NOT EPI_RUN_RESULT EQUAL 0)
            set(EPI_CPU_X86_FEATURE_${EPI_CPU_X86_FEATURE} ON CACHE BOOL "" FORCE)
            message(STATUS "EPI_CPU_X86_FEATURE `${EPI_CPU_X86_FEATURE}`: Enabled")
        else()
            message(STATUS "EPI_CPU_X86_FEATURE `${EPI_CPU_X86_FEATURE}`: Disabled")
        endif()
    endforeach()
endif()
