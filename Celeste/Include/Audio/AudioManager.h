#pragma once

#include "System/ISystem.h"
#include "Audio/AudioUtils.h"


namespace Celeste::Audio
{
  class AudioManager : public System::ISystem
  {
    public:
      CelesteDllExport AudioManager();
      CelesteDllExport ~AudioManager() override;

      AudioManager(const AudioManager&) = delete;
      AudioManager& operator=(const AudioManager&) = delete;

      float getMasterVolume() const { return m_masterVolume; }
      CelesteDllExport void setMasterVolume(float volume);

      float getMusicVolume() const { return m_musicVolume; }
      CelesteDllExport void setMusicVolume(float volume);

      float getSFXVolume() const { return m_sfxVolume; }
      CelesteDllExport void setSFXVolume(float volume);

      void update(float elapsedGameTime) override;

    private:
      using Inherited = System::ISystem;

      float m_masterVolume;
      float m_musicVolume;
      float m_sfxVolume;
  };
}