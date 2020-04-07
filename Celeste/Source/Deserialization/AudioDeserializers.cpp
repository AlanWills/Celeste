#include "Deserialization/AudioDeserializers.h"
#include "Assert/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<Audio::AudioType>(const std::string& text, Audio::AudioType& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    if (text == "Music")
    {
      output = Audio::AudioType::kMusic;
      return true;
    }
    else if (text == "SFX")
    {
      output = Audio::AudioType::kSFX;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}