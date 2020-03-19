#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_AUDIO_SOURCE_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, AudioSourceData, ResourceRelativePath)

  class AudioSourceLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(AudioSourceLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(AudioSourceData, "AudioSource Data")

    TEST_AUDIO_SOURCE_DATA(Invalid, "Invalid.xml");
    TEST_AUDIO_SOURCE_DATA(Valid, "Valid.xml");
  };
}