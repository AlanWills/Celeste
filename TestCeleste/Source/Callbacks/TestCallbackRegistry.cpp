#include "UtilityHeaders/UnitTestHeaders.h"

#include "Registries/CallbackRegistry.h"
#include "Utils/ObjectUtils.h"

using namespace Celeste;


namespace TestCeleste
{
  struct TestCallback
  {
    static std::string name() { return "Test"; }

    void operator()(GameObject& gameObject, const std::string& arg) { m_called = true; }

    static bool m_called;
  };

  bool TestCallback::m_called = false;

  CELESTE_TEST_CLASS(TestCallbackRegistry)

  //------------------------------------------------------------------------------------------------
  void TestCallbackRegistry::testInitialize()
  {
    CallbackRegistry::removeCallback<TestCallback>();
    TestCallback::m_called = false;
  }

  //------------------------------------------------------------------------------------------------
  void TestCallbackRegistry::testCleanup()
  {
    CallbackRegistry::removeCallback<TestCallback>();
    TestCallback::m_called = false;
  }

#pragma region Add Callback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_AddCallback_InputtingNonExistentName_AddsCallback_AndReturnsTrue)
  {
    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());
    Assert::IsTrue(CallbackRegistry::addCallback<TestCallback>());
    Assert::IsTrue(CallbackRegistry::hasCallback<TestCallback>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_AddCallback_InputtingExistentName_DoesNothing_AndReturnsFalse)
  {
    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());
    Assert::IsTrue(CallbackRegistry::addCallback<TestCallback>());
    Assert::IsTrue(CallbackRegistry::hasCallback<TestCallback>());
    Assert::IsFalse(CallbackRegistry::addCallback<TestCallback>());
  }

#pragma endregion

#pragma region Has Callback (Template Overload) Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_HasCallback_InputtingNonExistentType_ReturnsFalse)
  {
    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_HasCallback_InputtingExistentType_ReturnsTrue)
  {
    CallbackRegistry::addCallback<TestCallback>();

    Assert::IsTrue(CallbackRegistry::hasCallback<TestCallback>());
  }

#pragma endregion

#pragma region Has Callback (String Overload) Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_HasCallback_InputtingNonExistentName_ReturnsFalse)
  {
    Assert::IsFalse(CallbackRegistry::hasCallback(TestCallback::name()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_HasCallback_InputtingExistentName_ReturnsTrue)
  {
    CallbackRegistry::addCallback<TestCallback>();

    Assert::IsTrue(CallbackRegistry::hasCallback(TestCallback::name()));
  }

#pragma endregion

#pragma region Remove Callback (Template Overload) Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_RemoveCallback_InputtingNonExistentType_DoesNothing)
  {
    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());

    CallbackRegistry::removeCallback<TestCallback>();
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_RemoveCallback_InputtingExistentType_RemovesTypeFromRegistry)
  {
    CallbackRegistry::addCallback<TestCallback>();

    Assert::IsTrue(CallbackRegistry::hasCallback<TestCallback>());

    CallbackRegistry::removeCallback<TestCallback>();

    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());
  }

#pragma endregion

#pragma region Remove Callback (String Overload) Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_RemoveCallback_InputtingNonExistentString_DoesNothing)
  {
    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());

    CallbackRegistry::removeCallback(TestCallback::name());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_RemoveCallback_InputtingExistentName_RemovesTypeFromRegistry)
  {
    CallbackRegistry::addCallback<TestCallback>();

    Assert::IsTrue(CallbackRegistry::hasCallback<TestCallback>());

    CallbackRegistry::removeCallback(TestCallback::name());

    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());
  }

#pragma endregion

#pragma region Invoke Callback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_InvokeCallback_InputtingNonExistentCallbackName_DoesNotInvokeCallback)
  {
    GAMEOBJECT(gameObject);

    Assert::IsFalse(CallbackRegistry::hasCallback<TestCallback>());
    Assert::IsFalse(TestCallback::m_called);

    CallbackRegistry::invokeCallback(TestCallback::name(), gameObject, "Test");

    Assert::IsFalse(TestCallback::m_called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackRegistry_InvokeCallback_InputtingExistentCallbackName_AndNonNullGameObject_InvokesCallback)
  {
    GAMEOBJECT(gameObject);
    CallbackRegistry::addCallback<TestCallback>();

    Assert::IsTrue(CallbackRegistry::hasCallback<TestCallback>());
    Assert::IsFalse(TestCallback::m_called);

    CallbackRegistry::invokeCallback(TestCallback::name(), gameObject, "Test");

    Assert::IsTrue(TestCallback::m_called);
  }

#pragma endregion

  };

}