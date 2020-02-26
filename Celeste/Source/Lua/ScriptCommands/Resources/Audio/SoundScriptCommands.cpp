#include "Lua/ScriptCommands/Resources/Audio/SoundScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Audio/Sound.h"

using Sound = Celeste::Resources::Sound;


namespace Celeste::Lua::Resources::Audio::SoundScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Sound>("Sound");
  }
}