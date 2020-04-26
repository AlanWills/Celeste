#pragma once


namespace sol
{
  class state;
}

namespace Celeste
{
  namespace Audio
  {
    class AudioManager;
  }

  namespace Lua::Audio::ScriptCommands
  {
    void initialize(sol::state& state);

    float getMasterVolume();
    void setMasterVolume(float masterVolume);

    float getMusicVolume();
    void setMusicVolume(float musicVolume);

    float getSFXVolume();
    void setSFXVolume(float sfxVolume);
  }
}