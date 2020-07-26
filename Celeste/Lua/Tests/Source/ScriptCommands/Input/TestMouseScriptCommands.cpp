#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/MouseScriptCommands.h"
#include "Lua/LuaState.h"
#include "Input/Mouse.h"
#include "Input/InputUtils.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestMouseScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseScriptCommands_Initialize_Adds_getPosition_ToMouseTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Mouse"]["getPosition"].valid());

    Celeste::Lua::Input::MouseScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Mouse"]["getPosition"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseScriptCommands_Initialize_Adds_setCursor_ToMouseTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Mouse"]["setCursor"].valid());

    Celeste::Lua::Input::MouseScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Mouse"]["setCursor"].valid());
  }

#pragma endregion

#pragma region Get Position Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseScriptCommands_getPosition_ReturnsMousePosition)
  {
    getMouse().getTransform().setTranslation(glm::vec3(100, 200, 300));

    Assert::AreEqual(glm::vec3(100, 200, 300), getMouse().getTransform().getTranslation());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseScriptCommands::initialize(state);
    auto result = state.globals()["Mouse"]["getPosition"].get<sol::protected_function>().call();

    Assert::AreEqual(glm::vec2(100, 200), result.get<glm::vec2>());
  }

#pragma endregion

  };
}