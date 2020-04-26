#include "ScriptCommands/Resources/2D/Texture2DScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Resources/2D/Texture2D.h"
#include "sol/sol.hpp"

using Texture2D = Celeste::Resources::Texture2D;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::Texture2D> : std::false_type {};
}

namespace Celeste::Lua::Resources::Texture2DScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Texture2D>(
      state,
      "Texture2D",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}