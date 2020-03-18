#pragma once

#include "CelesteDllExport.h"
#include "Lua/LuaState.h"


namespace Celeste
{
  class GameObject;

  namespace Lua::GameObjectScriptCommands
  {
    CelesteDllExport void initialize();
  }
}


namespace sol
{
  template <>
  struct is_container<Celeste::GameObject> : std::false_type { };
}