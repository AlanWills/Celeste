#include "UtilityHeaders/UnitTestHeaders.h"

#include "Registries/ComponentRegistry.h"
#include "Mocks/Objects/MockComponent.h"
#include "Registries/DefaultRegistryAllocator.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{

  class NonRegisteredComponent : public Component 
  { 
    public: 
      static std::string type_name() { return "NonRegistered"; } 
  };

  class DummyRegistryAllocator : public RegistryAllocator 
  { 
    public: observer_ptr<Component> allocate(const std::string& name, GameObject& gameObject) const override { return nullptr; } 
  };

  CELESTE_TEST_CLASS(TestComponentRegistry)

  //------------------------------------------------------------------------------------------------
  void TestComponentRegistry::testInitialize()
  {
    ComponentRegistry::deregisterComponent<NonRegisteredComponent>();
    ComponentRegistry::registerComponent<MockComponent>();
  }

  //------------------------------------------------------------------------------------------------
  void TestComponentRegistry::testCleanup()
  {
    ComponentRegistry::deregisterComponent<NonRegisteredComponent>();
    ComponentRegistry::registerComponent<MockComponent>();
  }

#pragma region Has Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_HasComponent_InputtingComponentTypeThatDoesntExist_ShouldReturnFalse)
  {
    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_HasComponent_InputtingComponentTypeThatDoesExist_ShouldReturnTrue)
  {
    std::unique_ptr<RegistryAllocator> allocator(new DummyRegistryAllocator());
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::move(allocator));

    Assert::IsTrue(ComponentRegistry::hasComponent<NonRegisteredComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_HasComponent_InputtingComponentNameThatDoesntExist_ShouldReturnFalse)
  {
    Assert::IsFalse(ComponentRegistry::hasComponent("WubbaLubbaDubDub"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_HasComponent_InputtingComponentNameThatDoesExist_ShouldReturnTrue)
  {
    std::unique_ptr<RegistryAllocator> allocator(new DummyRegistryAllocator());
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::move(allocator));

    Assert::IsTrue(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));
  }

#pragma endregion

#pragma region Add Component Tests

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentStringThatDoesntExist_NullAllocator_DoesNothing_ReturnsFalse_SetsAllocatorToNullptr)
  {
    std::unique_ptr<RegistryAllocator> allocator(nullptr);

    Assert::IsFalse(ComponentRegistry::hasComponent("WubbaLubbaDubDub"));
    Assert::IsFalse(ComponentRegistry::registerComponent("WubbaLubbaDubDub", std::move(allocator)));
    Assert::IsNull(allocator.get());
    Assert::IsFalse(ComponentRegistry::hasComponent("WubbaLubbaDubDub"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentNameThatDoesExist_NonNullAllocator_DoesNothing_ReturnFalse_SetsAllocatorToNullptr)
  {
    std::unique_ptr<RegistryAllocator> allocator(new DummyRegistryAllocator());
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::move((allocator)));

    Assert::IsTrue(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));

    // Adding the component above will set the allocator to nullptr as it is released to the registry
    allocator.reset(new DummyRegistryAllocator());

    Assert::IsNotNull(allocator.get());
    Assert::IsFalse(ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::move(allocator)));
    Assert::IsNull(allocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentNameThatDoesntExist_NonNullAllocator_AddsComponent_ReturnsTrue_SetsAllocatorToNullptr)
  {
    std::unique_ptr<RegistryAllocator> allocator(new DummyRegistryAllocator());

    Assert::IsFalse(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));
    Assert::IsTrue(ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::move(allocator)));
    Assert::IsNull(allocator.get());
    Assert::IsTrue(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));
  }

#pragma endregion

#pragma endregion

#pragma region Template Overload

  // Use MockComponent here because of templates and it will look for an allocate function

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentTypeThatDoesExist_DoesNothing)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
    
    ComponentRegistry::registerComponent<MockComponent>();

    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentTypeThatDoesExist_ReturnsFalse)
  {
    std::unique_ptr<RegistryAllocator> allocator(new DummyRegistryAllocator());
    ComponentRegistry::registerComponent(MockComponent::type_name(), std::move(allocator));

    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsFalse(ComponentRegistry::registerComponent<MockComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentTypeThatDoesntExist_AddsComponent)
  {
    ComponentRegistry::deregisterComponent<MockComponent>();

    Assert::IsFalse(ComponentRegistry::hasComponent(MockComponent::type_name()));
    
    ComponentRegistry::registerComponent<MockComponent>();

    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentTypeThatDoesntExist_ReturnsTrue)
  {
    ComponentRegistry::deregisterComponent<MockComponent>();

    Assert::IsFalse(ComponentRegistry::hasComponent(MockComponent::type_name()));
    Assert::IsTrue(ComponentRegistry::registerComponent<MockComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentTypeThatDoesntExist_CustomAllocatorType_AddsComponentWithCustomAllocator)
  {
    GameObject gameObject;

    ComponentRegistry::deregisterComponent<MockComponent>();

    Assert::IsFalse(ComponentRegistry::hasComponent(MockComponent::type_name()));
    
    ComponentRegistry::registerComponent<MockComponent, DummyRegistryAllocator>();

    Assert::IsTrue(ComponentRegistry::hasComponent(MockComponent::type_name()));
    
    observer_ptr<Component> component = ComponentRegistry::allocateComponent(MockComponent::type_name(), gameObject);

    // Dummy Registry Allocator will return null handle if it was called
    // This is how we tell the custom allocator was used
    Assert::IsNull(component);
  }

#pragma endregion

#pragma region Remove Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_RemoveComponent_InputtingComponentTypeThatDoesntExist_DoesNothing)
  {
    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());

    ComponentRegistry::deregisterComponent<NonRegisteredComponent>();

    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_RemoveComponent_InputtingComponentTypeThatDoesExist_RemovesComponentFromRegistry)
  {
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::unique_ptr<RegistryAllocator>(new DummyRegistryAllocator()));
    
    Assert::IsTrue(ComponentRegistry::hasComponent<NonRegisteredComponent>());

    ComponentRegistry::deregisterComponent<NonRegisteredComponent>();

    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_RemoveComponent_InputtingComponentNameThatDoesntExist_DoesNothing)
  {
    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());

    ComponentRegistry::deregisterComponent(NonRegisteredComponent::type_name());

    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_RemoveComponent_InputtingComponentNameThatDoesExist_RemovesComponentFromRegistry)
  {
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::unique_ptr<RegistryAllocator>(new DummyRegistryAllocator()));

    Assert::IsTrue(ComponentRegistry::hasComponent<NonRegisteredComponent>());

    ComponentRegistry::deregisterComponent(NonRegisteredComponent::type_name());

    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
  }

#pragma endregion

#pragma region Allocate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_Allocate_InputtingEmptyComponentName_ReturnsNullptr)
  {
    GameObject gameObject;

    Assert::IsNull(ComponentRegistry::allocateComponent("", gameObject));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_Allocate_InputtingNonExistentComponentName_ReturnsNullptr)
  {
    GameObject gameObject;

    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
    Assert::IsNull(ComponentRegistry::allocateComponent(NonRegisteredComponent::type_name(), gameObject));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_Allocate_ReturnsCorrectlyAllocatedComponentType)
  {
    GameObject gameObject;

    std::unique_ptr<RegistryAllocator> allocator(new DummyRegistryAllocator());
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), std::move(allocator));

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());
    
    AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(MockComponent::type_name(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<MockComponent*>(component.get()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_Allocate_ReturnsComponentWithGameObjectSetToInputtedGameObject)
  {
    GameObject gameObject;

    std::unique_ptr<RegistryAllocator> allocator(new DefaultRegistryAllocator<MockComponent>());
    ComponentRegistry::registerComponent(MockComponent::type_name(), std::move(allocator));

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());

    AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(MockComponent::type_name(), gameObject);

    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

  };
}