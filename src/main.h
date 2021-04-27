#pragma once

#define ALT_SERVER_API

#ifdef _WIN32
static const char* preferred_separator = "\\";
#else
static const char* preferred_separator = "/";
#endif

// Standard C++ stuff
#include <iostream>
#include <string>

// AltV SDK
#include <SDK.h>

// Python API
#include <pybind11/embed.h>

extern alt::ICore* Core;