#include "Lua/Components/LuaComponentManifestRegistryAllocator.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/LuaState.h"
#include "UtilityHeaders/UnitTestHeaders.h"
#include "Objects/GameObject.h"

#include "Mocks/Objects/MockComponent.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestLuaComponentManifestRegistryAllocator)

  //------------------------------------------------------------------------------------------------
  void TestLuaComponentManifestRegistryAllocator::testInitialize()
  {
    LuaComponentManifestRegistry::deregisterComponent(MockComponent::type_name());
  }

  //------------------------------------------------------------------------------------------------
  void TestLuaComponentManifestRegistryAllocator::testCleanup()
  {
    LuaComponentManifestRegistry::deregisterComponent(MockComponent::type_name());
  }

#pragma region Allocate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentManifestRegistryAllocator_allocate_InputtingNonExistentComponentName_ReturnsNullHandle)
  {
    GameObject gameObject;

    Assert::IsFalse(LuaComponentManifestRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsNull(LuaComponentManifestRegistryAllocator().allocate(MockComponent::type_name(), gameObject));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentManifestRegistryAllocator_allocate_InputtingNullGameObjectHandle_ReturnsNullHandle)
  {
    Assert::IsFalse(LuaComponentManifestRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsNull(LuaComponentManifestRegistryAllocator().allocate(MockComponent::type_name(), GameObject()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentManifestRegistryAllocator_allocate_InputtingExistentComponentName_ReturnsHandleToLuaComponent)
  {
    GameObject gameObject;
    LuaComponentManifestRegistry::registerComponent(MockComponent::type_name(), LuaState::instance().create_table());

    Assert::IsTrue(LuaComponentManifestRegistry::hasComponent(MockComponent::type_name()));

    auto component = LuaComponentManifestRegistryAllocator().allocate(MockComponent::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<LuaComponent*>(component));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentManifestRegistryAllocator_allocate_InputtingExistentComponentName_ComponentIsAssignedToInputtedGameObject)
  {
    GameObject gameObject;
    LuaComponentManifestRegistry::registerComponent(MockComponent::type_name(), LuaState::instance().create_table());

    Assert::IsTrue(LuaComponentManifestRegistry::hasComponent(MockComponent::type_name()));
    
    auto component = LuaComponentManifestRegistryAllocator().allocate(MockComponent::type_name(), gameObject);

    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

  };
}