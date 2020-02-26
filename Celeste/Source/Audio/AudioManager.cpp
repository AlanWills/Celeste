#include "Audio/AudioManager.h"
#include "Audio/AudioSource.h"
#include "OpenAL/OpenALState.h"
#include "glm/glm.hpp"


namespace Celeste::Audio
{
  //------------------------------------------------------------------------------------------------
  AudioManager::AudioManager() :
    m_masterVolume(1),
    m_musicVolume(1),
    m_sfxVolume(1)
  {
    // Initialize the OpenAL state
    if (!OpenALState::initialize())
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::onHandleInput()
  {
    Inherited::onHandleInput();

    AudioSource::m_componentAllocator.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::onUpdate(float elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    AudioSource::m_componentAllocator.update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::onDeath()
  {
    Inherited::onDeath();

    AudioSource::m_componentAllocator.die();

    // Terminate the OpenAL state
    OpenALState::terminate();
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::setMasterVolume(float volume)
  {
    m_masterVolume = glm::clamp<float>(volume, 0, 1);

    // Iterate through all allocated audio sources
    for (AudioSource& audio : AudioSource::m_componentAllocator)
    {
      ASSERT(alIsSource(audio.m_sourceHandle));
      alSourcef(audio.m_sourceHandle, AL_GAIN, m_masterVolume * (audio.getAudioType() == AudioType::kMusic ? m_musicVolume : m_sfxVolume) * audio.getVolume());
    }
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::setMusicVolume(float volume)
  {
    m_musicVolume = glm::clamp<float>(volume, 0, 1);

    // Iterate through all allocated music sources
    for (AudioSource& audio : AudioSource::m_componentAllocator)
    {
      if (audio.getAudioType() == AudioType::kMusic)
      {
        ASSERT(alIsSource(audio.m_sourceHandle));
        alSourcef(audio.m_sourceHandle, AL_GAIN, m_masterVolume * m_musicVolume * audio.getVolume());
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::setSFXVolume(float volume)
  {
    m_sfxVolume = glm::clamp<float>(volume, 0, 1);

    // Iterate through all allocated sfx sources
    for (AudioSource& audio : AudioSource::m_componentAllocator)
    {
      if (audio.getAudioType() == AudioType::kSFX)
      {
        ASSERT(alIsSource(audio.m_sourceHandle));
        alSourcef(audio.m_sourceHandle, AL_GAIN, m_masterVolume * m_sfxVolume * audio.getVolume());
      }
    }
  }
}