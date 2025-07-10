cmake_minimum_required(VERSION 3.16)

set(EXECUTABLE "test-BlueC")
project(${EXECUTABLE})


# ----- CppUTest -----
include(ExternalProject)
ExternalProject_Add(
	CppUTest_PROJ
	PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../external
	GIT_REPOSITORY "https://github.com/cpputest/cpputest.git"
	#GIT_TAG "e332d88164090beba1060bd3159aea5ded3f5bba"
	GIT_SUBMODULES_RECURSE TRUE
	GIT_SHALLOW FALSE
	LOG_DOWNLOAD ON
	UPDATE_COMMAND ""
	BUILD_BYPRODUCTS <INSTALL_DIR>/lib/libCppUTest.a
	CMAKE_ARGS -DCPPUTEST_EXTENSIONS=OFF -DCPPUTEST_BUILD_TESTING=OFF -DCPPUTEST_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)

ExternalProject_Get_Property(CppUTest_PROJ INSTALL_DIR)
add_library(CppUTest STATIC IMPORTED)
set_property(TARGET CppUTest PROPERTY IMPORTED_LOCATION ${INSTALL_DIR}/lib/libCppUTest.a)
add_dependencies(CppUTest CppUTest_PROJ)


# ----- Compiler options -----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -g") # TODO: Provide different flags based on DEBUG/RELEASE build
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


# ----- Includes -----
include_directories(${_LIBBLUEC_INCLUDE_PATH})


# ----- Test executable -----
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${EXECUTABLE} ${SRC})

add_dependencies(${EXECUTABLE} BlueC)
add_dependencies(${EXECUTABLE} CppUTest)

# ----- Linker options -----
target_link_libraries(${EXECUTABLE} BlueC)
target_link_libraries(${EXECUTABLE} CppUTest)