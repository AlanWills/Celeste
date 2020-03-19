#pragma once

#include "DataConverters/Audio/AudioSourceDataConverter.h"


namespace CelesteMocks
{
  class MockAudioSourceDataConverter : public Celeste::AudioSourceDataConverter
  {
    public:
      MockAudioSourceDataConverter() = default;
  };
}