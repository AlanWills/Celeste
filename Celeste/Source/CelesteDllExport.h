#pragma once

#include "Platform/Platform.h"

#ifdef BUILDING_CELESTE_DLL
#define CelesteDllExport __declspec(dllexport)
#else
#define CelesteDllExport __declspec(dllimport)
#endif
