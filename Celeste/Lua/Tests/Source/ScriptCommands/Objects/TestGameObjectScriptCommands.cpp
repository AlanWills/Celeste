#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Registries/ComponentRegistry.h"
#include "Mocks/Objects/MockComponent.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestGameObjectScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestGameObjectScriptCommands::testInitialize()
  {
    ComponentRegistry::deregisterComponent<MockComponent>();
  }

  //------------------------------------------------------------------------------------------------
  void TestGameObjectScriptCommands::testCleanup()
  {
    ComponentRegistry::deregisterComponent<MockComponent>();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_GameObjectUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getName_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getName"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["getName"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_setName_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["setName"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["setName"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getParent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getParent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["getParent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_setParent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["setParent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["setParent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getTransform_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getTransform"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["getTransform"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getComponentCount_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getComponentCount"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["getComponentCount"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getComponent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getComponent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["getComponent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_addComponent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["addComponent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["addComponent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getChildCount_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getChildCount"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["getChildCount"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getChildGameObject_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getChild"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["getChild"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_findChildGameObject_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["findChild"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["findChild"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_as_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["as"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["GameObject"]["as"].valid());
  }

#pragma endregion

#pragma region Get Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getName_NameIsEmptyString_ReturnsEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;
    gameObject.setName("");

    Assert::AreEqual(internString(""), gameObject.getName());

    auto functionResult = state.globals()["GameObject"]["getName"].get<sol::protected_function>().call(
      gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("", functionResult.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getName_NameIsNonEmptyString_ReturnsCorrectString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;
    gameObject.setName("Test");

    Assert::AreEqual(internString("Test"), gameObject.getName());

    auto functionResult = state.globals()["GameObject"]["getName"].get<sol::protected_function>().call(
      gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("Test", functionResult.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setName_InputtingEmptyString_SetsNameToEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;
    gameObject.setName("Test");

    Assert::AreEqual(internString("Test"), gameObject.getName());

    auto functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      gameObject, "");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString(""), gameObject.getName());

    functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      gameObject, "");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString(""), gameObject.getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setName_InputtingNonEmptyString_SetsNameToInputtingString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;

    Assert::AreEqual(internString(""), gameObject.getName());

    auto functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      gameObject, "Test");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString("Test"), gameObject.getName());

    functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      gameObject, "Test2");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString("Test2"), gameObject.getName());
  }

#pragma endregion

#pragma region Get Parent Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getParent_ParentNull_ReturnsNullHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;

    Assert::IsNull(gameObject.getParent());

    auto functionResult = state.globals()["GameObject"]["getParent"].get<sol::protected_function>().call(
      gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(functionResult.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getParent_ParentNotNull_ReturnsCorrectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject parent;
    GameObject gameObject;
    gameObject.setParent(&parent);

    Assert::IsTrue(&parent == gameObject.getParent());

    auto functionResult = state.globals()["GameObject"]["getParent"].get<sol::protected_function>().call(
      gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&parent == functionResult.get<GameObject*>());
  }

#pragma endregion

#pragma region Set Parent Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNull_InputtingNullHandle_SetsParentToNull)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;

    Assert::IsNull(gameObject.getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      gameObject, nullptr);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(gameObject.getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNotNull_InputtingNullHandle_SetsParentToNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject parent, gameObject;
    gameObject.setParent(&parent);

    Assert::AreEqual(&parent, gameObject.getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      gameObject, nullptr);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(gameObject.getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNull_InputtingNonNullHandle_SetsParentToInputtedHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject, newParent;

    Assert::IsNull(gameObject.getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      gameObject, &newParent);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(&newParent, gameObject.getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNotNull_InputtingNonNullHandle_SwitchesParentToInputtedHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject, oldParent, newParent;
    gameObject.setParent(&oldParent);

    Assert::AreEqual(&oldParent, gameObject.getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      gameObject, newParent);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(&newParent, gameObject.getParent());
  }

#pragma endregion

#pragma region Get Transform Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getTransform_TransformNotNull_ReturnsCorrectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());

    auto functionResult = state.globals()["GameObject"]["getTransform"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(gameObject.getTransform(), functionResult.get<Transform*>());
  }

#pragma endregion

#pragma region Add Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingUnregisteredComponentName_ReturnsNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;

    Assert::IsFalse(ComponentRegistry::hasComponent<MockComponent>());

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(functionResult.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingRegisteredTypeComponentName_ReturnsCorrectTypePtr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);
    Celeste::Lua::registerUserType<MockComponent>(state, "MockComponent");

    GameObject gameObject;
    ComponentRegistry::registerComponent<MockComponent>();

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());
    Assert::IsTrue(state.globals()["MockComponent"]);

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    Assert::IsNotNull(functionResult.get<MockComponent*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingNonRegisteredTypeComponentName_ReturnsComponentPtr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;
    ComponentRegistry::registerComponent<MockComponent>();

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());
    Assert::IsFalse(state.globals()["MockComponentHandle"]);

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    Assert::IsNotNull(functionResult.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingRegisteredComponentName_AddsComponentToGameObject)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;
    ComponentRegistry::registerComponent<MockComponent>();

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    AssertCel::HasComponent<MockComponent>(gameObject);
  }

#pragma endregion

#pragma region Get Component Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getComponentCount_NoComponents_ReturnsZero)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["getComponentCount"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), result.get<size_t>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getComponentCount_WithComponents_ReturnsCorrectComponentCount)
  {
    GameObject gameObject;

    gameObject.addComponent<MockComponent>();
    gameObject.addComponent<MockComponent>();

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["getComponentCount"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(2), result.get<size_t>());
  }

#pragma endregion

#pragma region Get Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getComponent_InputtingInvalidComponentIndex_ReturnsNullComponentHandle)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Component*>());

    gameObject.addComponent<MockComponent>();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

    result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 1);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getComponent_InputtingValidComponentIndex_ReturnsCorrectComponentHandle)
  {
    GameObject gameObject;

    observer_ptr<MockComponent> component = gameObject.addComponent<MockComponent>();
    observer_ptr<MockComponent> component2 = gameObject.addComponent<MockComponent>();

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(component == result.get<Component*>());

    result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 1);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(component2 == result.get<Component*>());
  }

#pragma endregion

#pragma region Add Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingNonExistentComponentName_DoesNotAddComponent)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsFalse(ComponentRegistry::hasComponent("WubbaLubbaDubDub"));

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingNonExistentComponentName_ReturnsNullHandle)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, MockComponent::type_name());

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingValid_UnRegisteredComponentName_AddsComponent)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);
    ComponentRegistry::registerComponent<MockComponent>();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsFalse(state[MockComponent::type_name()].valid());

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, MockComponent::type_name());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());
    AssertCel::HasComponent<MockComponent>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingValid_UnregisteredComponentName_ReturnsComponentHandle)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);
    ComponentRegistry::registerComponent<MockComponent>();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsFalse(state[MockComponent::type_name()].valid());

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, MockComponent::type_name());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(gameObject.getComponent(0), result.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingValidComponentName_AddsComponentToGameObject)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);
    ComponentRegistry::registerComponent<MockComponent>();
    Celeste::Lua::registerUserType<MockComponent>(state, MockComponent::type_name());

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsTrue(state[MockComponent::type_name()].valid());

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, MockComponent::type_name());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());
    AssertCel::HasComponent<MockComponent>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingValidComponentName_ReturnsComponentHandle)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);
    ComponentRegistry::registerComponent<MockComponent>();
    Celeste::Lua::registerUserType<MockComponent>(state, MockComponent::type_name());

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsTrue(state[MockComponent::type_name()].valid());

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, MockComponent::type_name());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(gameObject.getComponent(0), result.get<Component*>());
  }

#pragma endregion

#pragma region Get Child Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildCount_NoChildren_ReturnsZero)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildCount"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), result.get<size_t>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildCount_WithChildren_ReturnsCorrectChildCount)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;
    child1.setParent(&gameObject);
    child2.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildCount"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(2), result.get<size_t>());
  }

#pragma endregion

#pragma region Get Child Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildGameObject_NoChildren_ReturnsNullHandle)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChild"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildGameObject_InputtingInvalidIndex_ReturnsNullHandle)
  {
    GameObject gameObject;
    GameObject child1;
    child1.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChild"].get<sol::protected_function>().call(gameObject, 1);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildGameObject_InputtingValidIndex_ReturnsCorrectGameObjectHandle)
  {
    GameObject gameObject;
    GameObject child1;
    child1.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChild"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(&child1 == result.get<GameObject*>());
  }

#pragma endregion

#pragma region Find Child Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_NoChildren_ReturnsNullHandle)
  {
    GameObject gameObject;

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["findChild"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_NoChildWithMatchingName_ReturnsNullHandle)
  {
    GameObject gameObject;
    GameObject child;
    child.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());
    Assert::IsNull(gameObject.findChild("Child"));

    auto result = state.globals()["GameObject"]["findChild"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_OneChildWithMatchingName_ReturnsCorrectHandle)
  {
    GameObject gameObject;
    GameObject child;
    child.setParent(&gameObject);
    child.setName("Child");

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());
    Assert::IsTrue(&child == gameObject.findChild("Child"));

    auto result = state.globals()["GameObject"]["findChild"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(&child == result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_MultipleChildrenWithMatchingName_ReturnsFirstMatchingCorrectHandle)
  {
    GameObject gameObject;
    GameObject child;
    GameObject child2;
    child.setParent(&gameObject);
    child.setName("Child");
    child2.setParent(&gameObject);
    child2.setName("Child");

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::IsTrue(&child == gameObject.findChild("Child"));

    auto result = state.globals()["GameObject"]["findChild"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(&child == result.get<GameObject*>());
  }

#pragma endregion

#pragma region GameObject As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToGameObjectType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "GameObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "GameObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObjectHandle_as_InputtingNullGameObjectHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&gameObject == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToGameObjectType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "GameObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&gameObject == functionResult.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    class DerivedType : public GameObject {};
    state.new_usertype<DerivedType>("DerivedType");
    
    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "DerivedType");
    
    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::GameObjectScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}