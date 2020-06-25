#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Time/TimeScriptCommands.h"
#include "Lua/LuaState.h"

#include "Time/TimeUtils.h"
#include "Time/Clock.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;


namespace TestCeleste::LuaScriptCommands
{
  CELESTE_TEST_CLASS(TestTimeScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeScriptCommands_Initialize_CreatesTimeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Time"].valid());

    Celeste::Lua::Time::ScriptCommands::initialize(state);

    Assert::IsTrue(state["Time"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeScriptCommands_Initialize_Adds_getDeltaTime_ToTimeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Time"]["getDeltaTime"].valid());

    Celeste::Lua::Time::ScriptCommands::initialize(state);

    Assert::IsTrue(state["Time"]["getDeltaTime"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeScriptCommands_Initialize_InitializesTimeNotifierSystemScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["TimeNotifierSystem"].valid());

    Celeste::Lua::Time::ScriptCommands::initialize(state);

    Assert::IsTrue(state["TimeNotifierSystem"].valid());
  }

#pragma endregion

#pragma region Get Delta Time Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TimeScriptCommands_getDeltaTime_ReturnsGameClockElapsedDeltaTime)
  {
    sol::state& state = LuaState::instance();
    Clock& clock = Time::getClock();

    Celeste::Lua::Time::ScriptCommands::initialize(state);

    clock.update(50.1f);
    auto result = state["Time"]["getDeltaTime"].get<sol::protected_function>().call();

    Assert::IsTrue(result.valid());
    Assert::AreEqual(50.1f, clock.getElapsedDeltaTime());
    Assert::AreEqual(clock.getElapsedDeltaTime(), result.get<float>());
  }

#pragma endregion

  };
}