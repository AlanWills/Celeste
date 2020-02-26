#pragma once

#ifdef BUILDING_BINDINGS_GENERATOR_DLL
#define BindingsGeneratorDllExport __declspec(dllexport)
#else
#define BindingsGeneratorDllExport __declspec(dllimport)
#endif
