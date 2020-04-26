#include "ScriptCommands/Resources/Fonts/FontScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Fonts/Font.h"

using Font = Celeste::Resources::Font;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::Font> : std::false_type {};
}

namespace Celeste::Lua::Resources::FontScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Font>(
      state,
      "Font",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}