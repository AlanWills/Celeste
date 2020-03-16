#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/LuaHeaders.h"


namespace Celeste
{
  class Transform;

  namespace Lua::Maths::TransformScriptCommands
  {
    CelesteDllExport void initialize();
  }
}

namespace sol::detail
{
  template <>
  struct is_container<Celeste::Transform> : std::false_type { };
}