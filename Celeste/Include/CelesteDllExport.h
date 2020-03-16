#pragma once

#include "UtilityHeaders/PlatformHeaders.h"

#ifdef STATIC_LIB
#define CelesteDllExport
#elif BUILDING_CELESTE_ENGINE_DLL
#define CelesteDllExport __declspec(dllexport)
#else
#define CelesteDllExport __declspec(dllimport)
#endif
