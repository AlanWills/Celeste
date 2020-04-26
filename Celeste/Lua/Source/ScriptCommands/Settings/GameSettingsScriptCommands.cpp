#include "ScriptCommands/Settings/GameSettingsScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Settings/GameSettings.h"

using namespace Celeste::Settings;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Settings::GameSettings> : std::false_type {};
}

namespace Celeste::Lua::Settings::GameSettingsScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void apply(const std::string& gameSettingsPath)
    {
      std::unique_ptr<GameSettings> settings = ScriptableObject::load<GameSettings>(gameSettingsPath);

      if (settings != nullptr)
      {
        settings->apply();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerScriptableObjectUserType<GameSettings>(
      state,
      "GameSettings",
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "apply", &Internals::apply,
      "getMasterVolume", &GameSettings::getMasterVolume,
      "setMasterVolume", &GameSettings::setMasterVolume,
      "getMusicVolume", &GameSettings::getMusicVolume,
      "setMusicVolume", &GameSettings::setMusicVolume,
      "getSFXVolume", &GameSettings::getSFXVolume,
      "setSFXVolume", &GameSettings::setSFXVolume);
  }
}