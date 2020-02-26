#include "UtilityHeaders/UnitTestHeaders.h"

#include "Callbacks/ExecuteLuaScript.h"
#include "Resources/TestResources.h"
#include "Lua/LuaState.h"
#include "FileAssert.h"
#include "Objects/GameObject.h"


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestExecuteLuaScript);

  //------------------------------------------------------------------------------------------------
  void TestExecuteLuaScript::testInitialize()
  {
    Celeste::Lua::LuaState::instance()["var = nil"];
  }

  //------------------------------------------------------------------------------------------------
  void TestExecuteLuaScript::testCleanup()
  {
    Celeste::Lua::LuaState::instance()["var = nil"];
  }

#pragma region Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ExecuteLuaScript_FunctionOperator_InputtingFullPathToScriptFile_ExecutesScript)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Path path(TestResources::getTempDirectory(), "Test.lua");
    File file(path);
    file.create(true);
    file.append("var = 5");

    FileAssert::FileExists(path.as_string());
    Assert::IsFalse(state["var"].valid());

    ExecuteLuaScript callback;
    GameObject gameObject;
    callback(gameObject, path.as_string());

    Assert::IsTrue(state["var"].valid());
    Assert::AreEqual(5, state["var"].get<sol::object>().as<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ExecuteLuaScript_FunctionOperator_InputtingRelativePathToScriptFile_ExecutesScript)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Path path(TestResources::getTempDirectory(), "Test.lua");
    File file(path);
    file.create(true);
    file.append("var = 5");

    FileAssert::FileExists(path.as_string());
    Assert::IsFalse(state["var"].valid());

    ExecuteLuaScript callback;
    GameObject gameObject;
    callback(gameObject, Path(TestResources::getTempDirectoryRelativePath(), "Test.lua").as_string());

    Assert::IsTrue(state["var"].valid());
    Assert::AreEqual(5, state["var"].get<sol::object>().as<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ExecuteLuaScript_FunctionOperator_InputtingNonExistentFullPathToScriptFile_ExecutesScript)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Path path(TestResources::getTempDirectory(), "WubbaLubbaDubDub.lua");

    FileAssert::FileDoesNotExist(path.as_string());
    Assert::IsFalse(state["var"].valid());

    ExecuteLuaScript callback;
    GameObject gameObject;
    callback(gameObject, path.as_string());

    Assert::IsFalse(state["var"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ExecuteLuaScript_FunctionOperator_InputtingNonExistentRelativePathToScriptFile_ExecutesScript)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Path path(TestResources::getTempDirectory(), "WubbaLubbaDubDub.lua");

    FileAssert::FileDoesNotExist(path.as_string());
    Assert::IsFalse(state["var"].valid());

    ExecuteLuaScript callback;
    GameObject gameObject;
    callback(gameObject, Path(TestResources::getTempDirectoryRelativePath(), "WubbaLubbaDubDub.lua").as_string());

    Assert::IsFalse(state["var"].valid());
  }

#pragma endregion

  };
}