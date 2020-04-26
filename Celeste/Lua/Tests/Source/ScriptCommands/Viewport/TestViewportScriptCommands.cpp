#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "Lua/LuaState.h"

#include "Scene/SceneUtils.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestViewportScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_Initialize_CreatesViewportTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Viewport"].valid());

    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Viewport"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_Initialize_Adds_getDimensions_ToViewportTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Viewport"]["getDimensions"].valid());

    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Viewport"]["getDimensions"].valid());
  }

#pragma endregion

#pragma region Get Viewport Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_getDimensions_ReturnsCorrectViewportDimensions)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    auto result = state.globals()["Viewport"]["getDimensions"].get<sol::protected_function>().call();

    Assert::IsTrue(result.valid());
    Assert::AreEqual(getViewportDimensions(), result.get<glm::vec2>());
  }

#pragma endregion

  };
}