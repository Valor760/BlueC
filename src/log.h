#pragma once

#include <stdio.h>

// TODO: Move it to function in source file and use dedicated FDs
#define LOG_ERROR(fmt, ...) do { printf("[BlueC|ERROR] (%s:%d) %s: " fmt "\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__); } while(false)
#define LOG_INFO(fmt, ...) do { printf("[BlueC|INFO] (%s:%d) %s: " fmt "\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__); } while(false)
#define LOG_DEBUG(fmt, ...) do { printf("[BlueC|DEBUG] (%s:%d) %s: " fmt "\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__); } while(false)
