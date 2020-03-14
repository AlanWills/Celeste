#include "Lua/ScriptCommands/Animation/AnimationScriptCommands.h"
#include "Lua/ScriptCommands/Animation/AnimatorScriptCommands.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::Animation::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    Animation::AnimatorScriptCommands::initialize();
  }
}