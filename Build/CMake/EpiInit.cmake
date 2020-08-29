include(CTest)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

function(epi_include_script)
    foreach (SCRIPT IN ITEMS ${ARGN})
        include("${EPI_DIR}/Build/CMake/${SCRIPT}.cmake")
    endforeach ()
endfunction()

epi_include_script(EpiOptions)
epi_include_script(EpiModule)
epi_include_script(EpiExtern)
epi_include_script(EpiGen)
epi_include_script(EpiPath)
epi_include_script(EpiDebug)
