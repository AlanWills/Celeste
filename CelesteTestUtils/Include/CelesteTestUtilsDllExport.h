#pragma once

#include "UtilityHeaders/PlatformHeaders.h"

#if defined(CELESTE_TEST_UTILS_STATIC_LIB)
#define CelesteTestUtilsDllExport
#elif defined(BUILDING_CELESTE_TEST_UTILS_DLL)
#define CelesteTestUtilsDllExport __declspec(dllexport)
#else
#define CelesteTestUtilsDllExport __declspec(dllimport)
#endif