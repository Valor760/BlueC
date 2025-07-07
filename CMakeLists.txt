cmake_minimum_required(VERSION 3.16)

project(BlueC VERSION 0.01)


# ----- Options -----
option(LIBBLUEC_SHARED_LIB "Build library as SHARED or STATIC (Default: ON)" ON)
option(LIBBLUEC_BUILD_TESTS "Build libbluez tests" ON)
option(LIBBLUEC_INSTALL "Install built binaries to system" OFF)


# ----- Requirements -----
function(find_includes_for_package _PACKAGE_NAME _VAR_NAME _REQUIRED)
	execute_process(
		COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/scripts/get_includes.sh" ${_PACKAGE_NAME}
		OUTPUT_VARIABLE _LOCAL_OUT
		RESULT_VARIABLE _RETURN_CODE
	)

	if(NOT _RETURN_CODE EQUAL "0")
		if(_REQUIRED)
			message(FATAL_ERROR "[BlueC] Couldn't find includes for mandatory package '${_PACKAGE_NAME}'")
		else()
			message(NOTICE "[BlueC] Couldn't find includes for '${_PACKAGE_NAME}' package. Not mandatory -- continue...")
		endif()
	else()
		# Replace spaces with separators, so all includes are properly feeded to "include_directories" function
		string(REPLACE " " ";" _LOCAL_LIST ${_LOCAL_OUT})
		set(${_VAR_NAME} ${_LOCAL_LIST} PARENT_SCOPE)
	endif()
endfunction()


find_includes_for_package("glib-2.0"    _LIBBLUEC_GLIB_INC_PATH   TRUE)
find_includes_for_package("glibmm-2.68" _LIBBLUEC_GLIBMM_INC_PATH TRUE)
find_includes_for_package("sigc++-3.0"  _LIBBLUEC_SIGC_INC_PATH   TRUE)
find_includes_for_package("giomm-2.68"  _LIBBLUEC_GIOMM_INC_PATH  TRUE)


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
