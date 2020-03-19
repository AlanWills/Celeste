#include "UtilityHeaders/UnitTestHeaders.h"

#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
#include "Mocks/Objects/MockComponent.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{

  class NonRegisteredComponent : public Component 
  { 
    public: 
      static std::string type_name() { return "NonRegistered"; }
      static constexpr bool isManaged() { return false; }

      NonRegisteredComponent(GameObject& gameObject) : Component(gameObject) {}
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
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject& gameObject) { return nullptr; });

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
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject& gameObject) { return nullptr; });

    Assert::IsTrue(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));
  }

#pragma endregion

#pragma region Add Component Tests

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentNameThatDoesExist_DoesNothing_ReturnsFalse)
  {
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject&) { return nullptr; });

    Assert::IsTrue(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));
    Assert::IsFalse(ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject&) { return nullptr; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_AddComponent_InputtingComponentNameThatDoesntExist_AddsComponent_ReturnsTrue)
  {
    Assert::IsFalse(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));
    Assert::IsTrue(ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject&) { return nullptr; }));
    Assert::IsTrue(ComponentRegistry::hasComponent(NonRegisteredComponent::type_name()));
  }

#pragma endregion

#pragma endregion

#pragma region Template Overload

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
    ComponentRegistry::registerComponent(MockComponent::type_name(), [](GameObject&) { return nullptr; });

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
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject&) { return nullptr; });
    
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
    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject&) { return nullptr; });

    Assert::IsTrue(ComponentRegistry::hasComponent<NonRegisteredComponent>());

    ComponentRegistry::deregisterComponent(NonRegisteredComponent::type_name());

    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
  }

#pragma endregion

#pragma region Create Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_CreateComponent_InputtingEmptyComponentName_ReturnsNullptr)
  {
    GameObject gameObject;

    Assert::IsNull(ComponentRegistry::createComponent("", gameObject));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_CreateComponent_InputtingNonExistentComponentName_ReturnsNullptr)
  {
    GameObject gameObject;

    Assert::IsFalse(ComponentRegistry::hasComponent<NonRegisteredComponent>());
    Assert::IsNull(ComponentRegistry::createComponent(NonRegisteredComponent::type_name(), gameObject));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_CreateComponent_ReturnsCorrectlyAllocatedComponentType)
  {
    GameObject gameObject;

    ComponentRegistry::registerComponent(NonRegisteredComponent::type_name(), [](GameObject& gameObject) { return gameObject.addComponent<NonRegisteredComponent>(); });

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());
    
    observer_ptr<Component> component = ComponentRegistry::createComponent(MockComponent::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<MockComponent*>(component));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentRegistry_CreateComponent_ReturnsComponentWithGameObjectSetToInputtedGameObject)
  {
    GameObject gameObject;

    ComponentRegistry::registerComponent(MockComponent::type_name(), [](GameObject& gameObject) { return gameObject.addComponent<NonRegisteredComponent>(); });

    Assert::IsTrue(ComponentRegistry::hasComponent<MockComponent>());

    observer_ptr<Component> component = ComponentRegistry::createComponent(MockComponent::type_name(), gameObject);

    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

  };
}