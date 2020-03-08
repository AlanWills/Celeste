#pragma once

#include "Objects/Component.h"
#include "Resources/Audio/Sound.h"
#include "FileSystem/Path.h"
#include "AudioEnums.h"


namespace Celeste::Audio
{
  class AudioSource : public Component
  {
    DECLARE_MANAGED_COMPONENT(AudioSource, AudioManager, CelesteDllExport)

    public:
      CelesteDllExport ~AudioSource() override;

      inline observer_ptr<const Resources::Sound> getSound() const { return m_sound; }
      CelesteDllExport void setSound(const Path& wavFilePath);
      CelesteDllExport void setSound(Resources::Sound* sound);

      inline AudioType getAudioType() const { return m_audioType; }
      inline void setAudioType(AudioType audioType) { m_audioType = audioType; }

      inline float getVolume() const { return m_volume; }
      CelesteDllExport void setVolume(float volume);

      CelesteDllExport bool isLooping() const;
      CelesteDllExport void setLooping(bool isLooping);

      inline bool isPlaying() const { return m_isPlaying; }

      CelesteDllExport void play();
      CelesteDllExport void stop();

    protected:
      ALuint getSourceHandle() const { return m_sourceHandle; }

    private:
      using Inherited = Component;

      observer_ptr<Resources::Sound> m_sound = nullptr;
      ALuint m_sourceHandle = AL_NONE;
      bool m_isPlaying = false;
      float m_volume = 1.0f;
      AudioType m_audioType = AudioType::kSFX;
  };
}