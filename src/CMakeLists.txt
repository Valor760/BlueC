cmake_minimum_required(VERSION 3.16)

set(LIBRARY "BlueC")
project(${LIBRARY})


# ----- Compiler options -----
set(CMAKE_CXX_STANDARD 17) # TODO: Upgrade to C++20?
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall") # TODO: Provide different flags based on DEBUG/RELEASE build
# Remove full path from filename
# TODO: Check if other compilers are compatible with this
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffile-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}/=")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")


# ----- Includes -----
message(DEBUG "[BlueC] Lib include path: ${_LIBBLUEC_INCLUDE_PATH}")
message(DEBUG "[BlueC] glib include path: ${_LIBBLUEC_GLIB_INC_PATH}")
message(DEBUG "[BlueC] glibmm include path: ${_LIBBLUEC_GLIBMM_INC_PATH}")
message(DEBUG "[BlueC] sigc include path: ${_LIBBLUEC_SIGC_INC_PATH}")
message(DEBUG "[BlueC] giomm include path: ${_LIBBLUEC_GIOMM_INC_PATH}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${_LIBBLUEC_INCLUDE_PATH})
include_directories(${_LIBBLUEC_GLIB_INC_PATH})
include_directories(${_LIBBLUEC_GLIBMM_INC_PATH})
include_directories(${_LIBBLUEC_SIGC_INC_PATH})
include_directories(${_LIBBLUEC_GIOMM_INC_PATH})


# ----- Linker options -----
link_libraries(glib-2.0)
link_libraries(glibmm-2.68)
link_libraries(sigc-3.0)
link_libraries(giomm-2.68)


# ----- Library itself -----
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
if(LIBBLUEC_SHARED_LIB)
	add_library(${LIBRARY} SHARED ${SRC})
else()
	add_library(${LIBRARY} STATIC ${SRC})
endif()
