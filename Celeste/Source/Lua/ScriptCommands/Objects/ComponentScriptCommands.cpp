#include "Lua/ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/ScriptCommands/Animation/AnimatorScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Registries/ComponentRegistry.h"
#include "Objects/Component.h"


namespace Celeste::Lua::ComponentScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Component>(
      "Component",
      sol::base_classes, sol::bases<Entity, Object>());

    // Animation
    Animation::AnimatorScriptCommands::initialize();
  }
}