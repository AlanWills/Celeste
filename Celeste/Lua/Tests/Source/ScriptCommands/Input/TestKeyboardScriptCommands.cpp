#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/KeyboardScriptCommands.h"
#include "Lua/LuaState.h"

#include "Input/Keyboard.h"
#include "Input/InputUtils.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestKeyboardScriptCommands)

  //------------------------------------------------------------------------------------------------
  void testInitialize() override
  {
    Celeste::Input::getKeyboard().getKeyPressedEvent().unsubscribeAll();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup() override
  {
    Celeste::Input::getKeyboard().getKeyPressedEvent().unsubscribeAll();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardScriptCommands_Initialize_AddsKeyboardTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Keyboard"].valid());

    Celeste::Lua::Input::KeyboardScriptCommands::initialize(state);

    Assert::IsTrue(state["Keyboard"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardScriptCommands_Initialize_Adds_subscribeOnKeyPressedCallback_ToKeyboardTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Keyboard"]["subscribeOnKeyPressedCallback"].valid());

    Celeste::Lua::Input::KeyboardScriptCommands::initialize(state);

    Assert::IsTrue(state["Keyboard"]["subscribeOnKeyPressedCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardScriptCommands_Initialize_Adds_unsubscribeOnKeyPressedCallback_ToKeyboardTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Keyboard"]["unsubscribeOnKeyPressedCallback"].valid());

    Celeste::Lua::Input::KeyboardScriptCommands::initialize(state);

    Assert::IsTrue(state["Keyboard"]["unsubscribeOnKeyPressedCallback"].valid());
  }

#pragma endregion

#pragma region Subscribe On Key Pressed Callback

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardScriptCommands_subscribeOnKeyPressedCallback_SubscribesToKeyPressedEvent)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), getKeyboard().getKeyPressedEvent().getSubscriberCount());

    auto result = state["Keyboard"]["subscribeOnKeyPressedCallback"].get<sol::protected_function>().call(
      state["Keyboard"]["subscribeOnKeyPressedCallback"].get<sol::protected_function>());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), getKeyboard().getKeyPressedEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region Unsubscribe On Key Pressed Callback

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardScriptCommands_unsubscribeOnKeyPressedCallback_InputtingInvalidStringId_DoesNothing)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardScriptCommands::initialize(state);

    getKeyboard().getKeyPressedEvent().subscribe([](int) {});

    Assert::AreEqual(static_cast<size_t>(1), getKeyboard().getKeyPressedEvent().getSubscriberCount());

    auto result = state["Keyboard"]["unsubscribeOnKeyPressedCallback"].get<sol::protected_function>().call(EventHandle());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), getKeyboard().getKeyPressedEvent().getSubscriberCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardScriptCommands_unsubscribeOnKeyPressedCallback_InputtingValidStringId_RemovesCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardScriptCommands::initialize(state);

    EventHandle id = getKeyboard().getKeyPressedEvent().subscribe([](int) {});

    Assert::AreEqual(static_cast<size_t>(1), getKeyboard().getKeyPressedEvent().getSubscriberCount());

    auto result = state["Keyboard"]["unsubscribeOnKeyPressedCallback"].get<sol::protected_function>().call(id);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), getKeyboard().getKeyPressedEvent().getSubscriberCount());
  }

#pragma endregion

  };
}