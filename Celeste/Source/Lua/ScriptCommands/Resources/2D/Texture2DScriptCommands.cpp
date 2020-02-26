#include "Lua/ScriptCommands/Resources/2D/Texture2DScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/2D/Texture2D.h"

using Texture2D = Celeste::Resources::Texture2D;


namespace Celeste::Lua::Resources::Texture2DScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Texture2D>(
      "Texture2D",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}