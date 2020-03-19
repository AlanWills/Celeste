#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/LuaState.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/Components/LuaComponent.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"

#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste::Lua
{
  CELESTE_TEST_CLASS(TestLuaComponentManifestRegistry)

  //------------------------------------------------------------------------------------------------
  void TestLuaComponentManifestRegistry::testInitialize()
  {
    LuaComponentManifestRegistry::deregisterComponent("Test");
    ComponentRegistry::deregisterComponent("Test");
  }

  //------------------------------------------------------------------------------------------------
  void TestLuaComponentManifestRegistry::testCleanup()
  {
    LuaComponentManifestRegistry::deregisterComponent("Test");
    ComponentRegistry::deregisterComponent("Test");
  }

#pragma region Register Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RegisterComponent_InputtingInvalidComponentTable_DoesNotAddToManifest)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());

    sol::table table;

    Assert::IsFalse(table.valid());

    LuaComponentManifestRegistry::registerComponent("Test", table);

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RegisterComponent_InputtingValidComponentTable_AddsToManifest)
  {
    sol::state& state = LuaState::instance();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
    Assert::IsTrue(state.globals().valid());

    LuaComponentManifestRegistry::registerComponent("Test", state.globals());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentManifestRegistry::registeredComponentsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RegisterComponent_InputtingValidComponentTable_AddsToComponentManifest)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(ComponentRegistry::hasComponent("Test"));

    LuaComponentManifestRegistry::registerComponent("Test", state.globals());

    Assert::IsTrue(ComponentRegistry::hasComponent("Test"));
  }

#pragma endregion

#pragma region Has Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HasComponent_InputtingComponentNameNotInManifest_ReturnsFalse)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
    Assert::IsFalse(LuaComponentManifestRegistry::hasComponent("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HasComponent_InputtingComponentNameInManifest_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();

    LuaComponentManifestRegistry::registerComponent("Test", state.globals());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentManifestRegistry::registeredComponentsSize());
    Assert::IsTrue(LuaComponentManifestRegistry::hasComponent("Test"));
  }

#pragma endregion

#pragma region Deregister Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DeregisterComponent_InputtingComponentNameNotInManifest_DoesNothing)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());

    LuaComponentManifestRegistry::deregisterComponent("Test");

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DeregisterComponent_InputtingComponentNameInManifest_RemovesFromManifest)
  {
    sol::state& state = LuaState::instance();

    LuaComponentManifestRegistry::registerComponent("Test", state.globals());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentManifestRegistry::registeredComponentsSize());

    LuaComponentManifestRegistry::deregisterComponent("Test");

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DeregisterComponent_InputtingComponentNameInManifest_RemovesFromComponentManifest)
  {
    sol::state& state = LuaState::instance();

    LuaComponentManifestRegistry::registerComponent("Test", state.globals());

    Assert::IsTrue(ComponentRegistry::hasComponent("Test"));

    LuaComponentManifestRegistry::deregisterComponent("Test");

    Assert::IsFalse(ComponentRegistry::hasComponent("Test"));
  }

#pragma endregion

#pragma region Create Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CreateComponent_InputtingNonRegisteredComponentName_DoesNotAddComponent)
  {
    GameObject gameObject;

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
    AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

    LuaComponentManifestRegistry::createComponent("Test", gameObject);

    AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CreateComponent_InputtingNonRegisteredComponentName_ReturnsNullptr)
  {
    GameObject gameObject;

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
    AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

    observer_ptr<LuaComponent> luaComponent = LuaComponentManifestRegistry::createComponent("Test", gameObject);

    Assert::IsNull(luaComponent);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CreateComponent_InputtingRegisteredComponentName_AddsComponent)
  {
    GameObject gameObject;

    LuaComponentManifestRegistry::registerComponent("Test", LuaState::instance().globals());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentManifestRegistry::registeredComponentsSize());
    AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

    LuaComponentManifestRegistry::createComponent("Test", gameObject);

    AssertCel::HasComponent<LuaComponent>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CreateComponent_InputtingRegisteredComponentName_ReturnsCreatedComponent)
  {
    GameObject gameObject;

    LuaComponentManifestRegistry::registerComponent("Test", LuaState::instance().globals());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentManifestRegistry::registeredComponentsSize());
    AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

    observer_ptr<LuaComponent> luaComponent = LuaComponentManifestRegistry::createComponent("Test", gameObject);

    Assert::IsNotNull(luaComponent);
  }

#pragma endregion

  };
}