#pragma once

#include "Platform/Platform.h"

#ifdef BUILDING_CELESTE_ENGINE_DLL
#define CelesteDllExport __declspec(dllexport)
#else
#define CelesteDllExport __declspec(dllimport)
#endif
