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
      AudioType audioSource = Audio::AudioType::kSFX;

      Assert::IsTrue(deserialize("Music", audioSource));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingMusic_SetsOutputTokWorld)
    {
      AudioType audioSource = Audio::AudioType::kSFX;
      deserialize("Music", audioSource);

      Assert::IsTrue(audioSource == AudioType::kMusic);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingSFX_ReturnsTrue)
    {
      AudioType audioSource = Audio::AudioType::kMusic;

      Assert::IsTrue(deserialize("SFX", audioSource));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingSFX_SetsOutputTokGUI)
    {
      AudioType audioSource = Audio::AudioType::kMusic;
      deserialize("SFX", audioSource);

      Assert::IsTrue(audioSource == AudioType::kSFX);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingInvalidText_ReturnsFalse)
    {
      AudioType audioSource = Audio::AudioType::kMusic;

      Assert::IsFalse(deserialize("", audioSource));
      Assert::IsFalse(deserialize("adhiasd", audioSource));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDeserializer_InputtingInvalidText_DoesNotChangeOutput)
    {
      AudioType audioSource = Audio::AudioType::kMusic;
      deserialize("", audioSource);

      Assert::IsTrue(audioSource == AudioType::kMusic);

      deserialize("wjdankjds", audioSource);

      Assert::IsTrue(audioSource == AudioType::kMusic);
    }

#pragma endregion
    };
  }
}