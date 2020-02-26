#include "Lua/ScriptCommands/Resources/Fonts/FontScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Fonts/Font.h"

using Font = Celeste::Resources::Font;


namespace Celeste::Lua::Resources::FontScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Font>("Font");
  }
}