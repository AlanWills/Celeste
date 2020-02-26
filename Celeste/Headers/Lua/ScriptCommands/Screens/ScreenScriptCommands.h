#pragma once

#include "CelesteDllExport.h"
#include "Lua/LuaState.h"


namespace Celeste
{
  class Screen;

  namespace Lua::ScreenScriptCommands
  {
    CelesteDllExport void initialize();
  }
}


namespace sol::detail
{
  template <>
  struct is_container<Celeste::Screen> : std::false_type { };
}