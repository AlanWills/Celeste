#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Registries/ComponentRegistry.h"
#include "Registries/DefaultRegistryAllocator.h"
#include "Screens/Screen.h"
#include "Mocks/Objects/MockComponent.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "Mocks/Objects/MockGameObject.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  class MockComponentRegistryAllocator : public RegistryAllocator 
  { 
    public: 
      observer_ptr<Component> allocate(const std::string& componentName, GameObject& gameObject) const override 
      {
        return gameObject.addComponent<MockComponent>();
      } 
  };

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

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getName_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getName"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getName"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_setName_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["setName"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["setName"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_shouldRender_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["shouldRender"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["shouldRender"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_setShouldRender_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["setShouldRender"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["setShouldRender"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getScreen_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getScreen"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getScreen"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getParent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getParent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getParent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_setParent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["setParent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["setParent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getTransform_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getTransform"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getTransform"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getComponentCount_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getComponentCount"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getComponentCount"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getComponent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getComponent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getComponent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_addComponent_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["addComponent"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["addComponent"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getChildCount_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getChildCount"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getChildCount"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getChildTransform_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getChildTransform"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getChildTransform"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_getChildGameObject_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["getChildGameObject"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["getChildGameObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_findChildGameObject_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["findChildGameObject"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["findChildGameObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_Initialize_Adds_as_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"]["as"].valid());

    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"]["as"].valid());
  }

#pragma endregion

#pragma region Get Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getName_NameIsEmptyString_ReturnsEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setName("");

    Assert::AreEqual(internString(""), gameObject->getName());

    auto functionResult = state.globals()["GameObject"]["getName"].get<sol::protected_function>().call(
      *gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("", functionResult.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getName_NameIsNonEmptyString_ReturnsCorrectString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setName("Test");

    Assert::AreEqual(internString("Test"), gameObject->getName());

    auto functionResult = state.globals()["GameObject"]["getName"].get<sol::protected_function>().call(
      *gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("Test", functionResult.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setName_InputtingEmptyString_SetsNameToEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setName("Test");

    Assert::AreEqual(internString("Test"), gameObject->getName());

    auto functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      *gameObject, "");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString(""), gameObject->getName());

    functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      *gameObject, "");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString(""), gameObject->getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setName_InputtingNonEmptyString_SetsNameToInputtingString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

    Assert::AreEqual(internString(""), gameObject->getName());

    auto functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      *gameObject, "Test");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString("Test"), gameObject->getName());

    functionResult = state.globals()["GameObject"]["setName"].get<sol::protected_function>().call(
      *gameObject, "Test2");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(internString("Test2"), gameObject->getName());
  }

#pragma endregion

#pragma region Should Render Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_shouldRender_ReturnsObjectRenderState)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<MockRenderer> renderer = gameObject->addComponent<MockRenderer>();
    renderer->setActive(false);

    AssertCel::IsNotActive(*renderer);

    auto functionResult = state["GameObject"]["shouldRender"].get<sol::protected_function>().call(*gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsFalse(functionResult.get<bool>());

    renderer->setActive(true);

    AssertCel::IsActive(*renderer);

    functionResult = state["GameObject"]["shouldRender"].get<sol::protected_function>().call(*gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(functionResult.get<bool>());
  }

#pragma endregion

#pragma region Set Should Render Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setShouldRender_UpdatesShouldRenderFlagCorrectly)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<MockRenderer> renderer = gameObject->addComponent<MockRenderer>();
    renderer->setActive(false);

    AssertCel::IsNotActive(*renderer);

    auto functionResult = state.globals()["GameObject"]["setShouldRender"].get<sol::protected_function>().call(
      *gameObject, true);

    Assert::IsTrue(functionResult.valid());
    AssertCel::IsActive(*renderer);

    functionResult = state.globals()["GameObject"]["setShouldRender"].get<sol::protected_function>().call(
      *gameObject, false);

    Assert::IsTrue(functionResult.valid());
    AssertCel::IsNotActive(*renderer);
  }

#pragma endregion

#pragma region Get Screen Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getScreen_ScreenNull_ReturnsNullHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    GameObject gameObject;

    Assert::IsNull(gameObject.getScreen());

    auto functionResult = state.globals()["GameObject"]["getScreen"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(functionResult.get<Screen*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getScreen_ScreenNotNull_ReturnsCorrectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

    Assert::IsTrue(&screen == gameObject->getScreen());

    auto functionResult = state.globals()["GameObject"]["getScreen"].get<sol::protected_function>().call(
      *gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&screen == functionResult.get<Screen*>());
  }

#pragma endregion

#pragma region Get Parent Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getParent_ParentNull_ReturnsNullHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

    Assert::IsNull(gameObject->getParent());

    auto functionResult = state.globals()["GameObject"]["getParent"].get<sol::protected_function>().call(
      *gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(functionResult.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getParent_ParentNotNull_ReturnsCorrectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    GAMEOBJECT(parent);
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setParent(&parent);

    Assert::IsTrue(&parent == gameObject->getParent());

    auto functionResult = state.globals()["GameObject"]["getParent"].get<sol::protected_function>().call(
      *gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&parent == functionResult.get<GameObject*>());
  }

#pragma endregion

#pragma region Set Parent Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNull_InputtingNullHandle_SetsParentToNull)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

    Assert::IsNull(gameObject->getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      *gameObject, nullptr);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(gameObject->getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNotNull_InputtingNullHandle_DoesNotChangeParent)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> parent = screen.allocateGameObject();
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setParent(parent.get());

    Assert::AreEqual(parent.get(), gameObject->getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      *gameObject, nullptr);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(parent.get(), gameObject->getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNull_InputtingNonNullHandle_SetsParentToInputtedHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<GameObject> newParent = screen.allocateGameObject();

    Assert::IsNull(gameObject->getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      *gameObject, newParent.get());

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(newParent.get(), gameObject->getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_setParent_ParentNotNull_InputtingNonNullHandle_SwitchesParentToInputtedHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<GameObject> oldParent = screen.allocateGameObject();
    AutoDeallocator<GameObject> newParent = screen.allocateGameObject();
    gameObject->setParent(oldParent.get());

    Assert::AreEqual(oldParent.get(), gameObject->getParent());

    auto functionResult = state.globals()["GameObject"]["setParent"].get<sol::protected_function>().call(
      *gameObject, newParent.get());

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(newParent.get(), gameObject->getParent());
  }

#pragma endregion

#pragma region Get Transform Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getTransform_TransformNull_ReturnsNullHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    GameObject gameObject;

    Assert::IsNull(gameObject.getTransform());

    auto functionResult = state.globals()["GameObject"]["getTransform"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(functionResult.get<Transform*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getTransform_TransformNotNull_ReturnsCorrectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

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
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

    Assert::IsFalse(ComponentRegistry::hasComponent<MockComponent>());

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      *gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(functionResult.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingRegisteredTypeComponentName_ReturnsCorrectTypePtr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();
    Celeste::Lua::registerUserType<MockComponent>("MockComponent");

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    ComponentRegistry::registerComponent(MockComponent::type_name(), std::unique_ptr<RegistryAllocator>(new MockComponentRegistryAllocator()));

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());
    Assert::IsTrue(state.globals()["MockComponent"]);

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      *gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    Assert::IsNotNull(functionResult.get<MockComponent*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingNonRegisteredTypeComponentName_ReturnsComponentPtr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    ComponentRegistry::registerComponent(MockComponent::type_name(), std::unique_ptr<RegistryAllocator>(new MockComponentRegistryAllocator()));

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());
    Assert::IsFalse(state.globals()["MockComponentHandle"]);

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      *gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    Assert::IsNotNull(functionResult.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingRegisteredComponentName_AddsComponentToGameObject)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    ComponentRegistry::registerComponent(MockComponent::type_name(), std::unique_ptr<RegistryAllocator>(new MockComponentRegistryAllocator()));

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());

    auto functionResult = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(
      *gameObject, MockComponent::type_name());

    Assert::IsTrue(functionResult.valid());
    AssertCel::HasComponent<MockComponent>(gameObject.get());
  }

#pragma endregion

#pragma region Get Component Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getComponentCount_NoComponents_ReturnsZero)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["getComponentCount"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), result.get<size_t>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getComponentCount_WithComponents_ReturnsCorrectComponentCount)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
    AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

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
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Component*>());

    AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

    result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 1);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getComponent_InputtingValidComponentIndex_ReturnsCorrectComponentHandle)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
    AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(component.get() == result.get<Component*>());

    result = state.globals()["GameObject"]["getComponent"].get<sol::protected_function>().call(gameObject, 1);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(component2.get() == result.get<Component*>());
  }

#pragma endregion

#pragma region Add Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingNonExistentComponentName_DoesNotAddComponent)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsFalse(ComponentRegistry::hasComponent("WubbaLubbaDubDub"));

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingNonExistentComponentName_ReturnsNullHandle)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());

    auto result = state.globals()["GameObject"]["addComponent"].get<sol::protected_function>().call(gameObject, MockComponent::type_name());

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_addComponent_InputtingValid_UnRegisteredComponentName_AddsComponent)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();
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
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();
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
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();
    ComponentRegistry::registerComponent<MockComponent>();
    Celeste::Lua::registerUserType<MockComponent>(MockComponent::type_name());

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
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();
    ComponentRegistry::registerComponent<MockComponent>();
    Celeste::Lua::registerUserType<MockComponent>(MockComponent::type_name());

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
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildCount"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), result.get<size_t>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildCount_WithChildren_ReturnsCorrectChildCount)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child1);
    GAMEOBJECT(child2);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child1.setParent(&gameObject);
    child2.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildCount"].get<sol::protected_function>().call(gameObject);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(2), result.get<size_t>());
  }

#pragma endregion

#pragma region Get Child Transform Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildTransform_NoChildren_ReturnsNullHandle)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildTransform"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Transform*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildTransform_InputtingInvalidIndex_ReturnsNullHandle)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child1);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child1.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildTransform"].get<sol::protected_function>().call(gameObject, 1);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Transform*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildTransform_InputtingValidIndex_ReturnsCorrectTransformHandle)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child1);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child1.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildTransform"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(child1.getTransform(), result.get<Transform*>());
  }

#pragma endregion

#pragma region Get Child GameObject Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildGameObject_NoChildren_ReturnsNullHandle)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildGameObject"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildGameObject_InputtingInvalidIndex_ReturnsNullHandle)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child1);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child1.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildGameObject"].get<sol::protected_function>().call(gameObject, 1);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_getChildGameObject_InputtingValidIndex_ReturnsCorrectGameObjectHandle)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child1);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child1.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["getChildGameObject"].get<sol::protected_function>().call(gameObject, 0);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(&child1 == result.get<GameObject*>());
  }

#pragma endregion

#pragma region Find Child GameObject Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_NoChildren_ReturnsNullHandle)
  {
    GAMEOBJECT(mockGameObject);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());

    auto result = state.globals()["GameObject"]["findChildGameObject"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_NoChildWithMatchingName_ReturnsNullHandle)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child.setParent(&gameObject);

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());
    Assert::IsNull(gameObject.findChildGameObject("Child"));

    auto result = state.globals()["GameObject"]["findChildGameObject"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_OneChildWithMatchingName_ReturnsCorrectHandle)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child.setParent(&gameObject);
    child.setName("Child");

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getChildCount());
    Assert::IsTrue(&child == gameObject.findChildGameObject("Child"));

    auto result = state.globals()["GameObject"]["findChildGameObject"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(&child == result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_findChildGameObject_MultipleChildrenWithMatchingName_ReturnsFirstMatchingCorrectHandle)
  {
    GAMEOBJECT(mockGameObject);
    GAMEOBJECT(child);
    GAMEOBJECT(child2);
    GameObject& gameObject = static_cast<GameObject&>(mockGameObject);
    child.setParent(&gameObject);
    child.setName("Child");
    child2.setParent(&gameObject);
    child2.setName("Child");

    sol::state& state = LuaState::instance();
    Celeste::Lua::GameObjectScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::IsTrue(&child == gameObject.findChildGameObject("Child"));

    auto result = state.globals()["GameObject"]["findChildGameObject"].get<sol::protected_function>().call(gameObject, "Child");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(&child == result.get<GameObject*>());
  }

#pragma endregion

#pragma region GameObject As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToGameObjectType_ReturnsNil)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "GameObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();
    state.new_usertype<MockGameObject>("MockGameObject");

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "MockGameObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObjectHandle_as_InputtingNullGameObjectHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&gameObject == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToGameObjectType_ReturnsCorrectPtr)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "GameObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&gameObject == functionResult.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();
    state.new_usertype<MockGameObject>("MockGameObject");
    
    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "MockGameObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(&gameObject, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectScriptCommands_GameObject_as_InputtingNonNullGameObject_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::GameObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["GameObject"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}