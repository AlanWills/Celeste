#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "Lua/LuaState.h"

#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestViewportScriptCommands)

  glm::vec2 resolution = glm::vec2();

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    resolution = getResolution();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    setResolution(resolution);
  }

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
  TEST_METHOD(ViewportScriptCommands_Initialize_Adds_getResolution_ToViewportTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Viewport"]["getResolution"].valid());

    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Viewport"]["getResolution"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_Initialize_Adds_setResolution_ToViewportTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Viewport"]["setResolution"].valid());

    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Viewport"]["setResolution"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_Initialize_Adds_getContentArea_ToViewportTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Viewport"]["getContentArea"].valid());

    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Viewport"]["getContentArea"].valid());
  }

#pragma endregion

#pragma region Get Resolution Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_getResolution_ReturnsCorrectResolution)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    auto result = state.globals()["Viewport"]["getResolution"].get<sol::protected_function>().call();

    Assert::IsTrue(result.valid());
    Assert::AreEqual(getResolution(), result.get<glm::vec2>());
  }

#pragma endregion

#pragma region Set Resolution Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_setResolution_ModifiesResolution)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    Assert::AreEqual(resolution, getResolution());

    auto result = state.globals()["Viewport"]["setResolution"].get<sol::protected_function>().call(glm::vec2(200, 400));

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec2(200, 400), getResolution());
  }

#pragma endregion

#pragma region Get Content Area Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ViewportScriptCommands_getContentArea_ReturnsViewportContentArea)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Viewport::ScriptCommands::initialize(state);

    auto result = state.globals()["Viewport"]["getContentArea"].get<sol::protected_function>().call();

    Assert::IsTrue(result.valid());
    Assert::AreEqual(getWindow().getContentArea(), result.get<glm::vec2>());
  }

#pragma endregion

  };
}