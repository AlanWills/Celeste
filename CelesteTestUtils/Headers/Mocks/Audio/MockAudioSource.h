#pragma once

#include "Audio/AudioSource.h"


namespace CelesteTestUtils
{

class MockAudioSource : public Celeste::Audio::AudioSource
{
  public:
    ~MockAudioSource()
    {
      ALuint sourceHandle = getSourceHandle();

      if (alIsSource(sourceHandle))
      {
        alDeleteSources(1, &sourceHandle);
      }
    }

    ALuint getSourceHandle_Public() const { return getSourceHandle(); }
    
    ALint getSourceBufferHandle() const
    {
      ALint handle = 0;
      alGetSourcei(getSourceHandle(), AL_BUFFER, &handle);
      return handle;
    }
};

}