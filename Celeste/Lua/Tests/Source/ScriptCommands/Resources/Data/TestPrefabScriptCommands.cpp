#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Resources/Data/PrefabScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Rendering/TextRenderer.h"
#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "Resources/Data/Prefab.h"

#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestPrefabScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Initialize_Adds_PrefabUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Prefab"].valid());

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Prefab"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Initialize_Adds_instantiate_ToPrefabTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Prefab"]["instantiate"].valid());

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Prefab"]["instantiate"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Initialize_Adds_as_ToPrefabTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Prefab"]["as"].valid());

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Prefab"]["as"].valid());
  }

#pragma endregion

#pragma region Instantiate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_instantiate_PrefabNotLoaded_ReturnsNullGameObject)
  {
    Prefab prefab;

    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<StringId>(0), prefab.getResourceId());

    sol::protected_function_result result = state["Prefab"]["instantiate"].get<sol::protected_function>().call(prefab);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_instantiate_ReturnsNonNullGameObject)
  {
    Prefab prefab;
    prefab.loadFromFile(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::AreNotEqual(static_cast<StringId>(0), prefab.getResourceId());

    sol::protected_function_result result = state["Prefab"]["instantiate"].get<sol::protected_function>().call(prefab);

    Assert::IsTrue(result.valid());
    Assert::IsNotNull(result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_instantiate_InstantiatesGameObjectValuesCorrectly)
  {
    Prefab prefab;
    prefab.loadFromFile(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::AreNotEqual(static_cast<StringId>(0), prefab.getResourceId());

    sol::protected_function_result result = state["Prefab"]["instantiate"].get<sol::protected_function>().call(prefab);

    Assert::IsTrue(result.valid());

    observer_ptr<GameObject> gameObject = result.get<observer_ptr<GameObject>>();

    Assert::IsNotNull(gameObject);
    Assert::AreEqual(internString("GameObject1"), gameObject->getName());
    AssertCel::HasComponent<Rendering::TextRenderer>(gameObject);
  }

#pragma endregion

#pragma region Prefab As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNull_CastingToPrefabType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(nullptr, "Prefab");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    class MockPrefab : public Celeste::Resources::Prefab {};
    state.new_usertype<MockPrefab>("MockPrefab");

    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(nullptr, "MockPrefab");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_PrefabHandle_as_InputtingNullPrefabHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNonNullPrefab_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    Prefab prefab;
    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(&prefab, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&prefab == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNonNullPrefab_CastingToPrefabType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Prefab prefab;
    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(&prefab, "Prefab");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&prefab == functionResult.get<Prefab*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNonNullPrefab_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    class MockPrefab : public Celeste::Resources::Prefab {};
    state.new_usertype<MockPrefab>("MockPrefab");

    Prefab prefab;
    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(&prefab, "MockPrefab");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNonNullPrefab_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Prefab prefab;
    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(&prefab, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabScriptCommands_Prefab_as_InputtingNonNullPrefab_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::PrefabScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Prefab"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}