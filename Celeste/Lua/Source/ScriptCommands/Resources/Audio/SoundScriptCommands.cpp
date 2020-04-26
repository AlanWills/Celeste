#include "ScriptCommands/Resources/Audio/SoundScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Audio/Sound.h"

using Sound = Celeste::Resources::Sound;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::Sound> : std::false_type {};
}

namespace Celeste::Lua::Resources::Audio::SoundScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Sound>(
      state,
      "Sound",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}