#pragma once

#include "Objects/Entity.h"
#include "Audio/AudioUtils.h"


namespace Celeste::Audio
{
  class AudioManager : public Entity
  {
    public:
      CelesteDllExport AudioManager();

      AudioManager(const AudioManager&) = delete;
      AudioManager& operator=(const AudioManager&) = delete;

      float getMasterVolume() const { return m_masterVolume; }
      CelesteDllExport void setMasterVolume(float volume);

      float getMusicVolume() const { return m_musicVolume; }
      CelesteDllExport void setMusicVolume(float volume);

      float getSFXVolume() const { return m_sfxVolume; }
      CelesteDllExport void setSFXVolume(float volume);

    protected:
      void onHandleInput() override;
      void onUpdate(float elapsedGameTime) override;
      void onDeath() override;

    private:
      using Inherited = Entity;

      float m_masterVolume;
      float m_musicVolume;
      float m_sfxVolume;
  };
}