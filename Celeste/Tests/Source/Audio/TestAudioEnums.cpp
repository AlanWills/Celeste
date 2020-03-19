#include "Audio/AudioEnums.h"
#include "UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Audio;


namespace TestCeleste
{
  namespace Audio
  {
    CELESTE_TEST_CLASS(TestAudioEnums)

#pragma region AudioType To String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioType_ToString_InputtingkMusic_ReturnsCorrectString)
    {
      Assert::AreEqual("Music", to_string(AudioType::kMusic).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioType_ToString_InputtingkSFX_ReturnsCorrectString)
    {
      Assert::AreEqual("SFX", to_string(AudioType::kSFX).c_str());
    }

#pragma endregion

    };
  }
}