#pragma once

#include "DataConverters/Audio/AudioSourceDataConverter.h"


namespace CelesteTestUtils
{
  class MockAudioSourceDataConverter : public Celeste::AudioSourceDataConverter
  {
    public:
      MockAudioSourceDataConverter() = default;
  };
}