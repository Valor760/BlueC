# TODO: Maybe switch to cmake later

CXX ?= g++
BUILD_DIR ?= build
OBJ_DIR ?= $(BUILD_DIR)/obj


# Lib part
TARGET_LIB_NAME ?= libsimple-bluez
LIB_SRC = $(shell find lib/ -name '*.cpp')
LIB_OBJ = $(LIB_SRC:%.cpp=$(OBJ_DIR)/%.o)
LIB_DEFINES =
LIB_INCLUDES = -Iinclude/ -I/usr/include/glib-2.0/ -I/usr/lib/glib-2.0/include/ \
	-I/usr/include/dbus-1.0/
LIB_CXXFLAGS = -O3 -std=c++20 $(LIB_DEFINES) $(LIB_INCLUDES) -fPIC
LIB_LDFLAGS = -shared -lglib-2.0 -lgobject-2.0 -lgio-2.0


# Test part
TARGET_TEST_NAME ?= test-libsimple-bluez
TEST_SRC = $(shell find test/ -name '*.cpp')
TEST_OBJ = $(TEST_SRC:%.cpp=$(OBJ_DIR)/%.o)
TEST_DEFINES =
TEST_INCLUDES = -Iinclude/
TEST_CXXFLAGS = -O3 -std=c++20 $(TEST_DEFINES) $(TEST_INCLUDES)
TEST_LDFLAGS = -lsimple-bluez -L$(BUILD_DIR)


all: lib


build_dir:
	mkdir -p $(OBJ_DIR)


lib: build_dir $(LIB_OBJ)
	$(CXX) $(LIB_OBJ) -o $(BUILD_DIR)/$(TARGET_LIB_NAME).so $(LIB_LDFLAGS)


test: build_dir lib $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o $(BUILD_DIR)/$(TARGET_TEST_NAME) $(TEST_LDFLAGS)


$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(LIB_CXXFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR)
	rm -rf external/
