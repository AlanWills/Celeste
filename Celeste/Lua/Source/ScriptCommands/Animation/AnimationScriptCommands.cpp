#include "ScriptCommands/Animation/AnimationScriptCommands.h"
#include "ScriptCommands/Animation/AnimatorScriptCommands.h"


namespace Celeste::Lua::Animation::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Animation::AnimatorScriptCommands::initialize(state);
  }
}