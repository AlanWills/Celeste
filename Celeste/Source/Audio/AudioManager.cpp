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
  AudioManager::~AudioManager()
  {
    AudioSource::m_allocator.deallocateAll();

    // Terminate the OpenAL state
    OpenALState::terminate();
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::handleInput()
  {
    Inherited::handleInput();

    AudioSource::m_allocator.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    AudioSource::m_allocator.update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void AudioManager::setMasterVolume(float volume)
  {
    m_masterVolume = glm::clamp<float>(volume, 0, 1);

    // Iterate through all allocated audio sources
    for (AudioSource& audio : AudioSource::m_allocator)
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
    for (AudioSource& audio : AudioSource::m_allocator)
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
    for (AudioSource& audio : AudioSource::m_allocator)
    {
      if (audio.getAudioType() == AudioType::kSFX)
      {
        ASSERT(alIsSource(audio.m_sourceHandle));
        alSourcef(audio.m_sourceHandle, AL_GAIN, m_masterVolume * m_sfxVolume * audio.getVolume());
      }
    }
  }
}