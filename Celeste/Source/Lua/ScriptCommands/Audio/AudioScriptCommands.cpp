#include "Lua/ScriptCommands/Audio/AudioScriptCommands.h"
#include "Lua/ScriptCommands/Audio/AudioSourceScriptCommands.h"
#include "Lua/LuaState.h"

#include "Audio/AudioUtils.h"
#include "Audio/AudioManager.h"


namespace Celeste::Lua::Audio::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = LuaState::instance();
    sol::table audioTable = state.create_named_table("Audio");

    // Set up script commands
    audioTable.set_function("getMasterVolume", &getMasterVolume);
    audioTable.set_function("setMasterVolume", &setMasterVolume);

    audioTable.set_function("getMusicVolume", &getMusicVolume);
    audioTable.set_function("setMusicVolume", &setMusicVolume);

    audioTable.set_function("getSFXVolume", &getSFXVolume);
    audioTable.set_function("setSFXVolume", &setSFXVolume);

    AudioSourceScriptCommands::initialize();
  }

  //------------------------------------------------------------------------------------------------
  float getMasterVolume()
  {
    return Celeste::Audio::getAudioManager().getMasterVolume();
  }

  //------------------------------------------------------------------------------------------------
  void setMasterVolume(float masterVolume)
  {
    Celeste::Audio::getAudioManager().setMasterVolume(masterVolume);
  }

  //------------------------------------------------------------------------------------------------
  float getMusicVolume()
  {
    return Celeste::Audio::getAudioManager().getMusicVolume();
  }

  //------------------------------------------------------------------------------------------------
  void setMusicVolume(float musicVolume)
  {
    Celeste::Audio::getAudioManager().setMusicVolume(musicVolume);
  }

  //------------------------------------------------------------------------------------------------
  float getSFXVolume()
  {
    return Celeste::Audio::getAudioManager().getSFXVolume();
  }

  //------------------------------------------------------------------------------------------------
  void setSFXVolume(float sfxVolume)
  {
    Celeste::Audio::getAudioManager().setSFXVolume(sfxVolume);
  }
}