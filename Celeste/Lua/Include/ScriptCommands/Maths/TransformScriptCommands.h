#pragma once

#include "Lua/LuaHeaders.h"


namespace sol
{
  class state;
}

namespace Celeste
{
  class Transform;

  namespace Lua::Maths::TransformScriptCommands
  {
    void initialize(sol::state& state);
  }
}

namespace sol
{
  template <>
  struct is_container<Celeste::Transform> : std::false_type { };
}