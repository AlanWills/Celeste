#pragma once

#include "UtilityHeaders/PlatformHeaders.h"

#if defined(CELESTE_MOCKS_STATIC_LIB)
#define CelesteMocksDllExport
#elif defined(BUILDING_CELESTE_MOCKS_DLL)
#define CelesteMocksDllExport __declspec(dllexport)
#else
#define CelesteMocksDllExport __declspec(dllimport)
#endif