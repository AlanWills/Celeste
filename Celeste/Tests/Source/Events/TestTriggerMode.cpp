#include "UtilityHeaders/UnitTestHeaders.h"

#include "Events/TriggerMode.h"

using namespace Celeste::Events;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestTriggerMode)

#pragma region To String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_ToString_InputtingkOnce_ReturnsCorrectString)
  {
    Assert::AreEqual("Once", Celeste::to_string(TriggerMode::kOnce).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_ToString_InputtingkUnlimited_ReturnsCorrectString)
  {
    Assert::AreEqual("Unlimited", Celeste::to_string(TriggerMode::kUnlimited).c_str());
  }

#pragma endregion

#pragma region From String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_FromString_InputtingOnce_ReturnskOnce)
  {
    TriggerMode triggerMode = TriggerMode::kUnlimited;
    Celeste::from_string("Once", triggerMode);

    Assert::IsTrue(TriggerMode::kOnce == triggerMode);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_FromString_InputtingOnce_ReturnsTrue)
  {
    TriggerMode triggerMode = TriggerMode::kOnce;

    Assert::IsTrue(Celeste::from_string("Once", triggerMode));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_FromString_InputtingUnlimited_ReturnskUnlimited)
  {
    TriggerMode triggerMode = TriggerMode::kOnce;
    Celeste::from_string("Unlimited", triggerMode);

    Assert::IsTrue(TriggerMode::kUnlimited == triggerMode);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_FromString_InputtingUnlimited_ReturnsTrue)
  {
    TriggerMode triggerMode = TriggerMode::kUnlimited;

    Assert::IsTrue(Celeste::from_string("Unlimited", triggerMode));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_FromString_InputtingInvalidString_ReturnsDoesNotChangeInputtedTriggerMode)
  {
    TriggerMode triggerMode = TriggerMode::kOnce;
    Celeste::from_string("WubbaLubbaDubDub", triggerMode);

    Assert::IsTrue(TriggerMode::kOnce == triggerMode);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TriggerMode_FromString_InputtingInvalidString_ReturnsFalse)
  {
    TriggerMode triggerMode = TriggerMode::kUnlimited;

    Assert::IsFalse(Celeste::from_string("", triggerMode));
    Assert::IsFalse(Celeste::from_string("WubbaLubbaDubDub", triggerMode));
  }

#pragma endregion

  };
}