#pragma once

#include "UtilityHeaders/PlatformHeaders.h"

#if defined(CETESTUTILS_STATIC_LIB)
#define CelesteTestUtilsDllExport
#elif defined(BUILDING_CELESTE_TESTUTILS_DLL)
#define CelesteTestUtilsDllExport __declspec(dllexport)
#else
#define CelesteTestUtilsDllExport __declspec(dllimport)
#endif