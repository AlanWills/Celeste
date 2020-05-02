#pragma once

#include "Platform/Platform.h"

#ifdef BUILDING_LOG_DLL
#define LogDllExport __declspec(dllexport)
#else
#define LogDllExport __declspec(dllimport)
#endif
