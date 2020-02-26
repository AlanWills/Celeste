#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/LuaState.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/Components/LuaComponent.h"
#include "Registries/ComponentRegistry.h"

#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste
{
  namespace Lua
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

#pragma region Allocate Component Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AllocateComponent_InputtingNonRegisteredComponentName_DoesNotAddComponent)
    {
      GAMEOBJECT(gameObject);

      Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
      AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

      AutoDeallocator<LuaComponent> luaComponent = LuaComponentManifestRegistry::allocateComponent("Test", gameObject);

      AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AllocateComponent_InputtingNonRegisteredComponentName_ReturnsNullHandle)
    {
      GAMEOBJECT(gameObject);

      Assert::AreEqual(static_cast<size_t>(0), LuaComponentManifestRegistry::registeredComponentsSize());
      AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

      AutoDeallocator<LuaComponent> luaComponent = LuaComponentManifestRegistry::allocateComponent("Test", gameObject);

      Assert::IsNull(luaComponent.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AllocateComponent_InputtingRegisteredComponentName_AddsComponent)
    {
      GAMEOBJECT(gameObject);

      LuaComponentManifestRegistry::registerComponent("Test", LuaState::instance().globals());

      Assert::AreEqual(static_cast<size_t>(1), LuaComponentManifestRegistry::registeredComponentsSize());
      AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

      AutoDeallocator<LuaComponent> luaComponent = LuaComponentManifestRegistry::allocateComponent("Test", gameObject);

      AssertCel::HasComponent<LuaComponent>(gameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AllocateComponent_InputtingRegisteredComponentName_ReturnsCreatedComponentHandle)
    {
      GAMEOBJECT(gameObject);

      LuaComponentManifestRegistry::registerComponent("Test", LuaState::instance().globals());

      Assert::AreEqual(static_cast<size_t>(1), LuaComponentManifestRegistry::registeredComponentsSize());
      AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);

      AutoDeallocator<LuaComponent> luaComponent = LuaComponentManifestRegistry::allocateComponent("Test", gameObject);

      Assert::IsNotNull(luaComponent.get());
    }

#pragma endregion

    };
  }
}