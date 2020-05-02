#pragma once

#include "Platform/Platform.h"

#ifdef BUILDING_ASSERT_DLL
#define AssertDllExport __declspec(dllexport)
#else
#define AssertDllExport __declspec(dllimport)
#endif
