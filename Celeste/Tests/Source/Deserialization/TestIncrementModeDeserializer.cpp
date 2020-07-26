#include "Deserialization/InputDeserializers.h"
#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestIncrementModeDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDeserializer_InputtingToggle_ReturnsTrue)
    {
      IncrementMode incrementMode = IncrementMode::kToggle;

      Assert::IsTrue(deserialize("Toggle", incrementMode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDeserializer_InputtingToggle_SetsOutputTokToggle)
    {
      IncrementMode incrementMode = IncrementMode::kContinuous;
      deserialize("Toggle", incrementMode);

      Assert::IsTrue(incrementMode == IncrementMode::kToggle);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDeserializer_InputtingContinuous_ReturnsTrue)
    {
      IncrementMode incrementMode = IncrementMode::kToggle;

      Assert::IsTrue(deserialize("Continuous", incrementMode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDeserializer_InputtingContinuous_SetsOutputTokContinuous)
    {
      IncrementMode incrementMode = IncrementMode::kToggle;
      deserialize("Continuous", incrementMode);

      Assert::IsTrue(incrementMode == IncrementMode::kContinuous);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDeserializer_InputtingInvalidText_ReturnsFalse)
    {
      IncrementMode incrementMode = IncrementMode::kToggle;

      Assert::IsFalse(deserialize("", incrementMode));
      Assert::IsFalse(deserialize("adhiasd", incrementMode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDeserializer_InputtingInvalidText_DoesNotChangeOutput)
    {
      IncrementMode incrementMode = IncrementMode::kToggle;
      deserialize("", incrementMode);

      Assert::IsTrue(incrementMode == IncrementMode::kToggle);

      deserialize("wjdankjds", incrementMode);

      Assert::IsTrue(incrementMode == IncrementMode::kToggle);
    }

#pragma endregion

    };
  }
}