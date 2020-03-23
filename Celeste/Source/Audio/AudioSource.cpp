#include "Audio/AudioSource.h"
#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Audio/AudioUtils.h"
#include "Audio/AudioManager.h"

using namespace Celeste::Resources;


namespace Celeste::Audio
{
  REGISTER_COMPONENT(AudioSource, 10)

  //------------------------------------------------------------------------------------------------
  AudioSource::AudioSource(GameObject& gameObject) :
    Inherited(gameObject)
  {
    // Clear the error state
    alGetError();

    // Generate a source
    alGenSources(1, &m_sourceHandle);

    if (alGetError() == AL_NO_ERROR)
    {
      alSourcef(m_sourceHandle, AL_PITCH, 1);
      alSource3f(m_sourceHandle, AL_POSITION, 0, 0, 0);
      alSource3f(m_sourceHandle, AL_VELOCITY, 0, 0, 0);
    }

    setVolume(m_volume);
    setLooping(false);
  }

  //------------------------------------------------------------------------------------------------
  AudioSource::~AudioSource()
  {
    stop();

    if (alIsSource(m_sourceHandle))
    {
      alDeleteSources(1, &m_sourceHandle);
    }
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::setSound(const Path& wavFilePath)
  {
    setSound(getResourceManager().load<Sound>(wavFilePath));
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::setSound(observer_ptr<Sound> sound)
  {
    if (sound != nullptr)
    {
      m_sound = sound;
      alSourcei(m_sourceHandle, AL_BUFFER, m_sound->getAudioHandle());
    }
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::setVolume(float volume)
  {
    m_volume = glm::clamp<float>(volume, 0, 1);

    if (alIsSource(m_sourceHandle))
    {
      AudioManager& manager = getAudioManager();
      float v = m_volume * manager.getMasterVolume() * (m_audioType == AudioType::kSFX ? manager.getSFXVolume() : manager.getMusicVolume());
      alSourcef(m_sourceHandle, AL_GAIN, v);
    }
  }

  //------------------------------------------------------------------------------------------------
  bool AudioSource::isLooping() const
  {
    if (alIsSource(m_sourceHandle))
    {
      int looping[1];
      alGetSourcei(m_sourceHandle, AL_LOOPING, looping);
      return looping[0] == AL_TRUE;
    }

    return false;
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::setLooping(bool isLooping)
  {
    if (alIsSource(m_sourceHandle))
    {
      alSourcei(m_sourceHandle, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE);
    }
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::play()
  {
    if (m_sound != nullptr)
    {
      m_isPlaying = true;
      alSourcePlay(m_sourceHandle);
    }
  }

  //------------------------------------------------------------------------------------------------
  void AudioSource::stop()
  {
    m_isPlaying = false;

    if (alIsSource(m_sourceHandle))
    {
      alSourceStop(m_sourceHandle);
    }
  }
}