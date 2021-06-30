set(FFMPEG_EXTRA_CFLAGS "/MDd")
set(FFMPEG_EXTRA_LDFLAGS "")
set(FFMPEG_ENABLE_ZLIB "")
set(FFMPEG_EXTRA_PKG_CONFIG_PATH "")

if (TARGET epiimported::zlib)
    set(FFMPEG_ENABLE_ZLIB "--enable-zlib")

    get_target_property(EPIIMPORTED_ZLIB_INTERFACE_INCLUDE_DIRECTORIES epiimported::zlib INTERFACE_INCLUDE_DIRECTORIES)

    foreach(INCLUDE_DIR ${EPIIMPORTED_ZLIB_INTERFACE_INCLUDE_DIRECTORIES})
        if (WIN32) # TODO: move to a proper place
            execute_process(COMMAND bash -c "wslpath -a ${INCLUDE_DIR}"
                RESULT_VARIABLE COMMAND_STATUS
                OUTPUT_VARIABLE INCLUDE_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )

            if (COMMAND_STATUS)
                message(FATAL_ERROR "`wslpath` command has failed: ${COMMAND_STATUS}")
            endif ()
        endif()

        list(APPEND FFMPEG_EXTRA_CFLAGS "/I ${INCLUDE_DIR}")
    endforeach()

    get_target_property(EPIIMPORTED_ZLIB_INTERFACE_LINK_DIRECTORIES epiimported::zlib INTERFACE_LINK_DIRECTORIES)
    foreach(LINK_DIR ${EPIIMPORTED_ZLIB_INTERFACE_LINK_DIRECTORIES})
        if (WIN32) # TODO: move to a proper place
            execute_process(COMMAND bash -c "wslpath -a ${LINK_DIR}"
                RESULT_VARIABLE COMMAND_STATUS
                OUTPUT_VARIABLE LINK_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )

            if (COMMAND_STATUS)
                message(FATAL_ERROR "`wslpath` command has failed: ${COMMAND_STATUS}")
            endif ()
        endif()

        list(APPEND FFMPEG_EXTRA_LDFLAGS "/LIBPATH:${LINK_DIR}")
    endforeach()

    get_target_property(EPIIMPORTED_ZLIB_INTERFACE_SHARE_DIRECTORIES epiimported::zlib INTERFACE_SHARE_DIRECTORIES)
    foreach(SHARE_DIR ${EPIIMPORTED_ZLIB_INTERFACE_SHARE_DIRECTORIES})
        find_file(PKG_CONFIG_DIR
            NAMES pkgconfig
            PATHS ${SHARE_DIR}
        )

        if (WIN32) # TODO: move to a proper place
            execute_process(COMMAND bash -c "wslpath -a ${PKG_CONFIG_DIR}"
                RESULT_VARIABLE COMMAND_STATUS
                OUTPUT_VARIABLE PKG_CONFIG_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )

            if (COMMAND_STATUS)
                message(FATAL_ERROR "`wslpath` command has failed: ${COMMAND_STATUS}")
            endif ()
        endif()

        list(APPEND FFMPEG_EXTRA_PKG_CONFIG_PATH ${PKG_CONFIG_DIR})
    endforeach()
endif()

set(FFMPEG_EXTRA_CXXFLAGS "${FFMPEG_EXTRA_CFLAGS}")

string(JOIN " " FFMPEG_EXTRA_CFLAGS ${FFMPEG_EXTRA_CFLAGS})
string(JOIN " " FFMPEG_EXTRA_CXXFLAGS ${FFMPEG_EXTRA_CXXFLAGS})
string(JOIN " " FFMPEG_EXTRA_LDFLAGS ${FFMPEG_EXTRA_LDFLAGS})
string(JOIN ":" FFMPEG_EXTRA_PKG_CONFIG_PATH ${FFMPEG_EXTRA_PKG_CONFIG_PATH})
