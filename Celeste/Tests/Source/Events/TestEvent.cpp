#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Events/Event.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestEvent)

    int call_count = 0;
    void input_void()
    {
      call_count++;
    }

    void input_int(int input)
    {
      call_count += input;
    }

    //------------------------------------------------------------------------------------------------
    void testInitialize()
    {
      call_count = 0;
    }

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Constructor_SetsSubscriberCount_ToZero)
    {
      Event<> event;

      Assert::AreEqual(static_cast<size_t>(0), event.getSubscriberCount());

      Event<int> event2;

      Assert::AreEqual(static_cast<size_t>(0), event2.getSubscriberCount());
    }

#pragma endregion

#pragma region Get Subscriber Count Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_GetSubscriberCount_WithSubscribedEvents_ReturnsCorrectNumberOfSubscribers)
    {
      Event<> event;

      auto f = []() -> void { };
      auto f2 = []() -> void { };
      event.subscribe(f);
      event.subscribe(f2);

      Assert::AreEqual(static_cast<size_t>(2), event.getSubscriberCount());
    }

#pragma endregion

#pragma region Void Input Template Specialization

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Invoke_WithNoSubscribers_VoidTemplateSpecialization)
    {
      Event<> event;
      event.invoke();

      Assert::AreEqual(0, call_count);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Invoke_WithSingleSubscriber_VoidTemplateSpecialization)
    {
      Event<> event;
      event.subscribe(std::bind(&TestEvent::input_void, this));
      event.invoke();

      Assert::AreEqual(1, call_count);

      event.invoke();

      Assert::AreEqual(2, call_count);
    }

#pragma endregion

#pragma region Single Parameter Event Tests

#pragma region Subscribe Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Subscribe_InputtingStringId_NotInMap_AddsFunctionToSubscriberList_AndReturnsStringId)
    {
      Event<int> event;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };
      StringId id = event.subscribe(f, 0);
      event.invoke(5);

      Assert::AreEqual((StringId)0, id);
      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Subscribe_InputtingStringId_InMap_ChangesCallbackForSubscriber_AndReturnsStringId)
    {
      Event<int> event;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };
      auto f2 = [&called](int) -> void { called = false; };
      StringId id = event.subscribe(f, 0);
      event.invoke(5);

      Assert::IsTrue(called);

      event.subscribe(f2, id);
      event.invoke(5);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Subscribe_InputtingString_UsesAndReturnsStringId)
    {
      Event<int> event;

      auto f = [](int) -> void { };
      StringId id = event.subscribe(f, "Test");

      Assert::AreEqual(internString("Test"), id);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Subscribe_InputtingNoKey_CalculatesKeyNotInUse)
    {
      Event<int> event;

      auto f = [](int) -> void {};
      StringId id = event.subscribe(f, "Test");

      Assert::AreNotEqual((StringId)0, id);
    }

#pragma endregion

#pragma region Invoke Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Invoke_WithNoSubscribers)
    {
      Event<int> event;
      event.invoke(5);

      Assert::AreEqual(0, call_count);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Invoke_WithSingleSubscriber)
    {
      Event<int> event;
      event.subscribe(std::bind(&TestEvent::input_int, this, std::placeholders::_1));
      event.invoke(5);

      Assert::AreEqual(5, call_count);

      event.invoke(-1);

      Assert::AreEqual(4, call_count);
    }

#pragma endregion

#pragma region Unsubscribe Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Unsubscribe_InputtingExistentStringId_RemovesEvent)
    {
      Event<int> event;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      StringId id = event.subscribe(f);
      event.invoke(5);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe(id);
      event.invoke(5);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Unsubscribe_InputtingNonExistentStringId_DoesNothing)
    {
      Event<int> event;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      StringId id = event.subscribe(f);
      event.invoke(5);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe(id + 1);
      event.invoke(5);

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Unsubscribe_InputtingExistentString_RemovesEvent)
    {
      Event<int> event;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      event.subscribe(f, "Test");
      event.invoke(5);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe("Test");
      event.invoke(5);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_Unsubscribe_InputtingNonExistentString_DoesNothing)
    {
      Event<int> event;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      event.subscribe(f, "Test");
      event.invoke(5);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe("Test2");
      event.invoke(5);

      Assert::IsTrue(called);
    }

#pragma endregion

#pragma region Unsubscribe All Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_UnsubscribeAll_WithNoSubscribers_DoesNotThrow)
    {
      Event<int> event;
      event.invoke(5);

      Assert::AreEqual(0, call_count);

      event.unsubscribeAll();
      event.invoke(0);

      Assert::AreEqual(0, call_count);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_UnsubscribeAll_WithSubscribers_RemovesAllCallbacks)
    {
      Event<int> event;
      event.subscribe(std::bind(&TestEvent::input_int, this, std::placeholders::_1));
      event.invoke(5);

      Assert::AreEqual(5, call_count);

      event.unsubscribeAll();
      event.invoke(5);

      Assert::AreEqual(5, call_count);
    }

#pragma endregion

#pragma endregion

#pragma region Multiple Parameter Event Tests

#pragma region Subscribe Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Subscribe_InputtingStringId_NotInMap_AddsFunctionToSubscriberList_AndReturnsStringId)
    {
      Event<int, float> event;

      bool called = false;
      auto f = [&called](int, float) -> void { called = true; };
      StringId id = event.subscribe(f, 0);
      event.invoke(5, 0.1f);

      Assert::AreEqual((StringId)0, id);
      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Subscribe_InputtingStringId_InMap_ChangesCallbackForSubscriber_AndReturnsStringId)
    {
      Event<int, float> event;

      bool called = false;
      auto f = [&called](int, float) -> void { called = true; };
      auto f2 = [&called](int, float) -> void { called = false; };
      StringId id = event.subscribe(f, 0);
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);

      event.subscribe(f2, id);
      event.invoke(5, 0.1f);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Subscribe_InputtingString_UsesAndReturnsStringId)
    {
      Event<int, float> event;

      auto f = [](int, float) -> void {};
      StringId id = event.subscribe(f, "Test");

      Assert::AreEqual(internString("Test"), id);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Subscribe_InputtingNoKey_CalculatesKeyNotInUse)
    {
      Event<int, float> event;

      auto f = [](int, float) -> void {};
      StringId id = event.subscribe(f, "Test");

      Assert::AreNotEqual((StringId)0, id);
    }

#pragma endregion

#pragma region Invoke Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Invoke_WithNoSubscribers)
    {
      Event<int, float> event;
      event.invoke(5, 0.1f);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Invoke_WithSingleSubscriber)
    {
      std::pair<int, float> p;
      Event<int, float> event;
      event.subscribe([&p](int i, float f) -> void
      {
        p.first = i;
        p.second = f;
      });
      event.invoke(5, 0.1f);

      Assert::AreEqual(5, p.first);
      Assert::AreEqual(0.1f, p.second);
    }

#pragma endregion

#pragma region Unsubscribe Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Unsubscribe_InputtingExistentStringId_RemovesEvent)
    {
      Event<int, float> event;

      bool called = false;
      auto f = [&called](int, float) -> void { called = true; };

      StringId id = event.subscribe(f);
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe(id);
      event.invoke(5, 0.1f);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Unsubscribe_InputtingNonExistentStringId_DoesNothing)
    {
      Event<int, float> event;

      bool called = false;
      auto f = [&called](int, float) -> void { called = true; };

      StringId id = event.subscribe(f);
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe(id + 1);
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Unsubscribe_InputtingExistentString_RemovesEvent)
    {
      Event<int, float> event;

      bool called = false;
      auto f = [&called](int, float) -> void { called = true; };

      event.subscribe(f, "Test");
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe("Test");
      event.invoke(5, 0.1f);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_Unsubscribe_InputtingNonExistentString_DoesNothing)
    {
      Event<int, float> event;

      bool called = false;
      auto f = [&called](int, float) -> void { called = true; };

      event.subscribe(f, "Test");
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribe("Test2");
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);
    }

#pragma endregion

#pragma region Unsubscribe All Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_UnsubscribeAll_WithNoSubscribers_DoesNotThrow)
    {
      Event<int, float> event;
      event.invoke(5, 0.1f);

      Assert::AreEqual(0, call_count);

      event.unsubscribeAll();
      event.invoke(0, 0.0f);

      Assert::AreEqual(0, call_count);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Event_MultiParam_UnsubscribeAll_WithSubscribers_RemovesAllCallbacks)
    {
      bool called = false;
      Event<int, float> event;
      auto f = [&called](int, float) -> void { called = true; };
      event.subscribe(f);
      event.invoke(5, 0.1f);

      Assert::IsTrue(called);

      called = false;
      event.unsubscribeAll();
      event.invoke(5, 0.1f);

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma endregion

  };
}