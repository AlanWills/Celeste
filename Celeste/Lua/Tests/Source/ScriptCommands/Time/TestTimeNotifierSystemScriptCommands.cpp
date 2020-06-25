#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Time/TimeNotifierSystemScriptCommands.h"
#include "Lua/LuaState.h"

#include "Time/TimeNotifierSystem.h"

using LuaState = Celeste::Lua::LuaState;
using TimeNotifierSystem = Celeste::Time::TimeNotifierSystem;

using namespace Celeste;


namespace TestCeleste::LuaTimeNotifierSystemScriptCommands
{
  CELESTE_TEST_CLASS(TestTimeNotifierSystemScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystemScriptCommands_Initialize_Adds_getTimeNotifierSystem_ToSystemTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["System"]["getTimeNotifierSystem"].valid());

    Celeste::Lua::Time::TimeNotifierSystemScriptCommands::initialize(state);

    Assert::IsTrue(state["System"]["getTimeNotifierSystem"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystemScriptCommands_Initialize_Adds_TimeNotifierSystemTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["TimeNotifierSystem"].valid());

    Celeste::Lua::Time::TimeNotifierSystemScriptCommands::initialize(state);

    Assert::IsTrue(state["TimeNotifierSystem"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystemScriptCommands_Initialize_Adds_subscribe_ToTimeNotifierSystemTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["TimeNotifierSystem"]["subscribe"].valid());

    Celeste::Lua::Time::TimeNotifierSystemScriptCommands::initialize(state);

    Assert::IsTrue(state["TimeNotifierSystem"]["subscribe"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystemScriptCommands_Initialize_Adds_unsubscribe_ToTimeNotifierSystemTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["TimeNotifierSystem"]["unsubscribe"].valid());

    Celeste::Lua::Time::TimeNotifierSystemScriptCommands::initialize(state);

    Assert::IsTrue(state["TimeNotifierSystem"]["unsubscribe"].valid());
  }

#pragma endregion

#pragma region Subscribe Tests

  void function(float) {}

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystemScriptCommands_subscribe_AddsCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Time::TimeNotifierSystemScriptCommands::initialize(state);

    sol::function function = state["TimeNotifierSystem"]["subscribe"];
    TimeNotifierSystem notifierSystem;

    Assert::AreEqual(static_cast<size_t>(0), notifierSystem.getSubscriberCount());

    auto result = state["TimeNotifierSystem"]["subscribe"].get<sol::protected_function>().call(notifierSystem, function, sol::object());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());
  }

#pragma endregion

#pragma region Unsubscribe Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystemScriptCommands_unsubscribe_InputtingInvalidHandle_DoesNothing)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Time::TimeNotifierSystemScriptCommands::initialize(state);

    TimeNotifierSystem notifierSystem;
    StringId validHandle = notifierSystem.subscribe([](float) {});

    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());

    auto result = state["TimeNotifierSystem"]["unsubscribe"].get<sol::protected_function>().call(notifierSystem, validHandle + 1);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeNotifierSystemScriptCommands_subscribe_InputtingValidHandle_RemovesSubscribedCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Time::TimeNotifierSystemScriptCommands::initialize(state);

    TimeNotifierSystem notifierSystem;
    StringId validHandle = notifierSystem.subscribe([](float) {});

    Assert::AreEqual(static_cast<size_t>(1), notifierSystem.getSubscriberCount());

    auto result = state["TimeNotifierSystem"]["unsubscribe"].get<sol::protected_function>().call(notifierSystem, validHandle);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), notifierSystem.getSubscriberCount());
  }

#pragma endregion

  };
}