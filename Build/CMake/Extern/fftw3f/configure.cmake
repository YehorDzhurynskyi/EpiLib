if (EPI_CPU_X86_FEATURE_SSE)
    set(ENABLE_SSE ON)
endif()

if (EPI_CPU_X86_FEATURE_SSE2)
    set(ENABLE_SSE2 ON)
endif()

if (EPI_CPU_X86_FEATURE_AVX)
    set(ENABLE_AVX ON)
endif()

if (EPI_CPU_X86_FEATURE_AVX2)
    set(ENABLE_AVX2 ON)
endif()

set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTS OFF)
set(ENABLE_FLOAT ON)
set(ENABLE_THREADS ON)
set(WITH_COMBINED_THREADS ON)
set(DISABLE_FORTRAN ON)
