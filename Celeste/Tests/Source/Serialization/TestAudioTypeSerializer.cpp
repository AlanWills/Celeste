#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"
#include "Audio/AudioEnums.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestAudioTypeSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeSerializer_Serialize_InputtingkMusic_SetsOutputStringToMusic)
    {
      std::string output;
      serialize(Audio::AudioType::kMusic, output);

      Assert::AreEqual("Music", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeSerializer_Serialize_InputtingkSFX_SetsOutputStringToSFX)
    {
      std::string output;
      serialize(Audio::AudioType::kSFX, output);

      Assert::AreEqual("SFX", output.c_str());
    }

#pragma endregion

    };
  }
}