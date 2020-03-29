#include "Lua/ScriptCommands/Resources/Fonts/FontScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

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
  void initialize()
  {
    registerUserType<Font>(
      "Font",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}