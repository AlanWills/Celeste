#pragma once

#include "CelesteDllExport.h"


namespace Celeste
{
  namespace Audio
  {
    class AudioManager;
  }

  namespace Lua::Audio::ScriptCommands
  {
    CelesteDllExport void initialize();

    CelesteDllExport float getMasterVolume();
    CelesteDllExport void setMasterVolume(float masterVolume);

    CelesteDllExport float getMusicVolume();
    CelesteDllExport void setMusicVolume(float musicVolume);

    CelesteDllExport float getSFXVolume();
    CelesteDllExport void setSFXVolume(float sfxVolume);
  }
}