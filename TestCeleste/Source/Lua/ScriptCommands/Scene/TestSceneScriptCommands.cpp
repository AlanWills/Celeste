#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Scene/SceneScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Resources/Scene/SceneLoadingResources.h"
#include "AssertCel.h"
#include "FileAssert.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestSceneScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneScriptCommands_Initialize_Adds_SceneTable_ToGlobalTable)
  {
    Celeste::Lua::Scene::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Scene"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneScriptCommands_Initialize_Adds_load_ToSceneTable)
  {
    Celeste::Lua::Scene::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Scene"]["load"].valid());
  }

#pragma endregion

  };
}
