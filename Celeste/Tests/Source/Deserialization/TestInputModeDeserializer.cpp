#include "Deserialization/InputDeserializers.h"
#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestInputModeDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeDeserializer_InputtingToggle_ReturnsTrue)
    {
      InputMode incrementMode = InputMode::kToggle;

      Assert::IsTrue(deserialize("Toggle", incrementMode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeDeserializer_InputtingToggle_SetsOutputTokToggle)
    {
      InputMode incrementMode = InputMode::kContinuous;
      deserialize("Toggle", incrementMode);

      Assert::IsTrue(incrementMode == InputMode::kToggle);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeDeserializer_InputtingContinuous_ReturnsTrue)
    {
      InputMode incrementMode = InputMode::kToggle;

      Assert::IsTrue(deserialize("Continuous", incrementMode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeDeserializer_InputtingContinuous_SetsOutputTokContinuous)
    {
      InputMode incrementMode = InputMode::kToggle;
      deserialize("Continuous", incrementMode);

      Assert::IsTrue(incrementMode == InputMode::kContinuous);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeDeserializer_InputtingInvalidText_ReturnsFalse)
    {
      InputMode incrementMode = InputMode::kToggle;

      Assert::IsFalse(deserialize("", incrementMode));
      Assert::IsFalse(deserialize("adhiasd", incrementMode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeDeserializer_InputtingInvalidText_DoesNotChangeOutput)
    {
      InputMode incrementMode = InputMode::kToggle;
      deserialize("", incrementMode);

      Assert::IsTrue(incrementMode == InputMode::kToggle);

      deserialize("wjdankjds", incrementMode);

      Assert::IsTrue(incrementMode == InputMode::kToggle);
    }

#pragma endregion

    };
  }
}