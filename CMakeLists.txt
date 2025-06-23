cmake_minimum_required(VERSION 3.16)

project(BlueC VERSION 0.01)


# ----- Options -----
option(LIBBLUEC_SHARED_LIB "Build library as SHARED or STATIC (Default: ON)" ON)
option(LIBBLUEC_BUILD_TESTS "Build libbluez tests" ON)
option(LIBBLUEC_INSTALL "Install built binaries to system" OFF)


# ----- Requirements -----
function(include_dir_find_or_error _VAR_NAME _INC_PATH _REQUIRED)
	if(NOT EXISTS ${_INC_PATH})
		if(_REQUIRED)
			message(FATAL_ERROR "[BlueC] Couldn't find mandatory include directoty at ${_INC_PATH}")
		else()
			message(NOTICE "[BlueC] Couldn't find ${_INC_PATH} include directory. Not mandatory -- continue...")
		endif()
	else()
		set(${_VAR_NAME} ${_INC_PATH} PARENT_SCOPE)
	endif()
endfunction()

# TODO: Check if the following configs are always at the same path
include_dir_find_or_error(_LIBBLUEC_GLIB_INC_PATH          "/usr/include/glib-2.0"        TRUE)
include_dir_find_or_error(_LIBBLUEC_GLIB_INC_PATH_CONFIG   "/usr/lib/glib-2.0/include"    TRUE)
include_dir_find_or_error(_LIBBLUEC_GLIBMM_INC_PATH        "/usr/include/glibmm-2.68"     TRUE)
include_dir_find_or_error(_LIBBLUEC_GLIBMM_INC_PATH_CONFIG "/usr/lib/glibmm-2.68/include" TRUE)
include_dir_find_or_error(_LIBBLUEC_SIGC_INC_PATH          "/usr/include/sigc++-3.0"      TRUE)
include_dir_find_or_error(_LIBBLUEC_SIGC_INC_PATH_CONFIG   "/usr/lib/sigc++-3.0/include"  TRUE)
include_dir_find_or_error(_LIBBLUEC_GIOMM_INC_PATH         "/usr/include/giomm-2.68"      TRUE)
include_dir_find_or_error(_LIBBLUEC_GIOMM_INC_PATH_CONFIG  "/usr/lib/giomm-2.68/include"  TRUE)


# ----- Internal Variables ------
set(_LIBBLUEC_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)


# ----- Subdirectories -----
add_subdirectory(src)

if(LIBBLUEC_BUILD_TESTS)
	message(NOTICE "[BlueC] Tests are enabled")
	add_subdirectory(tests)
endif()


# ----- Installation ------
if(LIBBLUEC_INSTALL)
	message(NOTICE "[BlueC] BlueZ installation not yet done! TODO")
endif()
