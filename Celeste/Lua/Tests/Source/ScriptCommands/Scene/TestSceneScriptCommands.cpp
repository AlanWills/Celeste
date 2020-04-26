#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Scene/SceneScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "TestResources/Scene/SceneLoadingResources.h"
#include "AssertCel.h"
#include "FileAssert.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestSceneScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneScriptCommands_Initialize_Adds_SceneTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Scene::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Scene"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneScriptCommands_Initialize_Adds_load_ToSceneTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Scene::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Scene"]["load"].valid());
  }

#pragma endregion

  };
}
