#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockScriptableObject.h"

#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "TestResources/Objects/MockScriptableObjectLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "AssertExt.h"
#include "AssertCel.h"
#include "FileAssert.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestScriptCommandUtils)

  //------------------------------------------------------------------------------------------------
  void TestScriptCommandUtils::testInitialize()
  {
    LuaState::instance()[MockScriptableObject::type_name()] = sol::nil;
  }

  //------------------------------------------------------------------------------------------------
  void TestScriptCommandUtils::testCleanup()
  {
    LuaState::instance()[MockScriptableObject::type_name()] = sol::nil;
  }

#pragma region Register Scriptable Object User Type Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_AddsUserTypeToGlobalState)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state[MockScriptableObject::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_AddsCreate_ToScriptableObjectTypeTable)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state[MockScriptableObject::type_name()]["create"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_AddsLoad_ToScriptableObjectTypeTable)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state[MockScriptableObject::type_name()]["load"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_AddsSave_ToScriptableObjectTypeTable)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state[MockScriptableObject::type_name()]["save"].valid());
  }

#pragma region Create Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_Create_CreatesNewScriptableObjectInstance)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["create"].get<sol::protected_function>().call("Test");

    Assert::IsTrue(result.valid());
    Assert::IsNotNull(result.get<MockScriptableObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_Create_SetsScriptableObjectInstanceName_ToInputtedValue)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["create"].get<sol::protected_function>().call("Test");

    Assert::IsTrue(result.valid());
    Assert::AreEqual("Test", result.get<MockScriptableObject*>()->getName().c_str());
  }

#pragma endregion

#pragma region Load Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_Load_InputtingNonExistentPath_ReturnsNullptr)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["load"].get<sol::protected_function>().call("WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<MockScriptableObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_Load_InputtingExistentPath_ToInvalidData_ReturnsNullptr)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["load"].get<sol::protected_function>().call(MockScriptableObjectLoadingResources::getInvalidRelativePath());

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<MockScriptableObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_RegisterScriptableObjectUserType_Load_InputtingExistentPath_ToValidData_ReturnsNewScriptableObjectInstance)
  {
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["load"].get<sol::protected_function>().call(MockScriptableObjectLoadingResources::getValidRelativePath());

    Assert::IsTrue(result.valid());

    auto obj = result.get<MockScriptableObject*>();

    Assert::AreEqual("Valid", obj->getName().c_str());
    Assert::AreEqual("34b0d489-8485-4391-b3b9-b3f062e90c4a", obj->getGuid().str().c_str());
  }

#pragma endregion

#pragma region Save Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_save_InputtingNonExistentFullPath_CreatesFile)
  {
    Path path(TestResources::getTempDirectory(), "Test.asset");

    FileAssert::FileDoesNotExist(path.as_string());

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("Test");
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["save"].get<sol::protected_function>().call(*scriptableObject, path.as_string());

    Assert::IsTrue(result.valid());
    FileAssert::FileExists(path.as_string());
    Assert::IsNotNull(getResourceManager().load<Data>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_save_InputtingNonExistentRelativePath_CreatesFile)
  {
    Path path(TestResources::getTempDirectoryRelativePath(), "Test.asset");
    Path fullPath(TestResources::getResourcesDirectory(), path);

    FileAssert::FileDoesNotExist(fullPath.as_string());

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("Test");
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["save"].get<sol::protected_function>().call(*scriptableObject, path.as_string());

    Assert::IsTrue(result.valid());
    FileAssert::FileExists(fullPath.as_string());
    Assert::IsNotNull(getResourceManager().load<Data>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_save_InputtingExistentFullPath_OverwritesFile)
  {
    Path path(TestResources::getTempDirectory(), "Test.asset");
    File file(path);
    file.create();
    file.append("Test");

    FileAssert::FileContentsEqual(path.as_string(), "Test");

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("Test");
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["save"].get<sol::protected_function>().call(*scriptableObject, path.as_string());

    Assert::IsTrue(result.valid());
    FileAssert::FileContentsNotEqual(path.as_string(), "Test");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptCommandUtils_save_InputtingExistentRelativePath_OverwritesFile)
  {
    Path path(TestResources::getTempDirectoryRelativePath(), "Test.asset");
    Path fullPath(TestResources::getResourcesDirectory(), path);
    File file(fullPath);
    file.create();
    file.append("Test");

    FileAssert::FileContentsEqual(fullPath.as_string(), "Test");

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("Test");
    Celeste::Lua::registerScriptableObjectUserType<MockScriptableObject>("MockScriptableObject");
    auto result = LuaState::instance()[MockScriptableObject::type_name()]["save"].get<sol::protected_function>().call(*scriptableObject, path.as_string());

    Assert::IsTrue(result.valid());
    FileAssert::FileContentsNotEqual(fullPath.as_string(), "Test");
  }

#pragma endregion

#pragma endregion

  };
}