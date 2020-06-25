#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Time/TimeNotifierSystem.h"

using namespace Celeste::Time;


namespace TestCeleste::Time
{
  CELESTE_TEST_CLASS(TestTimeNotifierSystem)

#pragma region Subscribe Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystem_Subscribe_AddsNewCallback)
  {
    TimeNotifierSystem notifierSystem;

    Assert::AreEqual(static_cast<size_t>(0), notifierSystem.getSubscriberCount());

    notifierSystem.subscribe([](float) {});

    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());
  }

#pragma endregion

#pragma region Unsubscribe Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystem_Unsubscribe_InputtingInvalidHandle_DoesNothing)
  {
    TimeNotifierSystem notifierSystem;
    Celeste::StringId validHandle = notifierSystem.subscribe([](float) {});

    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());

    notifierSystem.unsubscribe(validHandle + 1);
  
    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystem_Unsubscribe_InputtingValidHandle_RemovesCorrespondingCallback)
  {
    TimeNotifierSystem notifierSystem;
    Celeste::StringId validHandle = notifierSystem.subscribe([](float) {});

    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());

    notifierSystem.unsubscribe(validHandle);
  
    Assert::AreEqual(static_cast<size_t>(0), notifierSystem.getSubscriberCount());
  }

#pragma endregion

  };
}