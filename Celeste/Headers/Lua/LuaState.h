#pragma once

#include "UtilityHeaders/LuaHeaders.h"
#include "FileSystem/Path.h"
#include "CelesteDllExport.h"


namespace Celeste::Lua
{
  class LuaState
  {
    public:
      CelesteDllExport static sol::state& instance();
      CelesteDllExport static sol::protected_function_result script(const std::string& code);
      CelesteDllExport static sol::protected_function_result scriptFile(const Path& path);
      CelesteDllExport static sol::protected_function_result requireModule(const std::string& moduleName);

      CelesteDllExport static void appendToLuaPackagePath(const Path& pathToAppend);
      CelesteDllExport static void appendToLuaPackagePath(const std::string& pathToAppend);

    private:
      LuaState();
      ~LuaState() = default;
      LuaState(const LuaState&) = delete;
      LuaState& operator=(const LuaState&) = delete;

      sol::state m_state;
  };
}