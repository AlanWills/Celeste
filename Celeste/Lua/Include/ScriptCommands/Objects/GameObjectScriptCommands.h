#pragma once

#include "sol/sol.hpp"


namespace Celeste
{
  class GameObject;

  namespace Lua::GameObjectScriptCommands
  {
    void initialize(sol::state& state);
  }
}

namespace sol
{
  template <>
  struct is_container<Celeste::GameObject> : std::false_type { };
}