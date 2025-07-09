cmake_minimum_required(VERSION 3.16)

set(EXECUTABLE "test-BlueC")
project(${EXECUTABLE})


# ----- CppUTest -----
include(ExternalProject)
ExternalProject_Add(
	CppUTest
	PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../external
	GIT_REPOSITORY "https://github.com/cpputest/cpputest.git"
	GIT_TAG "e332d88164090beba1060bd3159aea5ded3f5bba"
	GIT_SUBMODULES_RECURSE TRUE
	GIT_SHALLOW TRUE
	LOG_DOWNLOAD ON
	UPDATE_COMMAND ""
	INSTALL_COMMAND ""
	CMAKE_ARGS "-DCPPUTEST_EXTENSIONS=OFF" "-DCPPUTEST_BUILD_TESTING=OFF" "-DCPPUTEST_EXAMPLES=OFF"
)


# ----- Compiler options -----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -g") # TODO: Provide different flags based on DEBUG/RELEASE build
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


# ----- Includes -----
include_directories(${_LIBBLUEC_INCLUDE_PATH})


# ----- Linker options -----
link_libraries(BlueC)
link_libraries(CppUTest)


# ----- Test executable -----
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${EXECUTABLE} ${SRC})

add_dependencies(${EXECUTABLE} BlueC)
add_dependencies(${EXECUTABLE} CppUTest)
