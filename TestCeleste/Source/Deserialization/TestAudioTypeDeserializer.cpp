#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/AudioDeserializers.h"

using namespace Celeste;
using namespace Celeste::Audio;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestAudioTypeDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingMusic_ReturnsTrue)
    {
      AudioType audio = Audio::AudioType::kSFX;

      Assert::IsTrue(deserialize("Music", audio));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingMusic_SetsOutputTokWorld)
    {
      AudioType audio = Audio::AudioType::kSFX;
      deserialize("Music", audio);

      Assert::IsTrue(audio == AudioType::kMusic);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingSFX_ReturnsTrue)
    {
      AudioType audio = Audio::AudioType::kMusic;

      Assert::IsTrue(deserialize("SFX", audio));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingSFX_SetsOutputTokGUI)
    {
      AudioType audio = Audio::AudioType::kMusic;
      deserialize("SFX", audio);

      Assert::IsTrue(audio == AudioType::kSFX);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingInvalidText_ReturnsFalse)
    {
      AudioType audio = Audio::AudioType::kMusic;

      Assert::IsFalse(deserialize("", audio));
      Assert::IsFalse(deserialize("adhiasd", audio));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingInvalidText_DoesNotChangeOutput)
    {
      AudioType audio = Audio::AudioType::kMusic;
      deserialize("", audio);

      Assert::IsTrue(audio == AudioType::kMusic);

      deserialize("wjdankjds", audio);

      Assert::IsTrue(audio == AudioType::kMusic);
    }

#pragma endregion
    };
  }
}