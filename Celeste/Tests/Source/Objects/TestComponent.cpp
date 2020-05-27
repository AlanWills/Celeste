#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockComponent.h"
#include "Objects/GameObject.h"
#include "Rendering/SpriteRenderer.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;
using namespace Celeste::Rendering;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestComponent)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_Constructor_SetsAllInitialValuesCorrectly)
  {
    GameObject gameObject;
    MockComponent component(gameObject);

    Assert::AreSame(gameObject, component.getGameObject());
    Assert::AreEqual(gameObject.getTransform(), component.getTransform());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_Constructor_Sets_ActiveToTrue)
  {
    GameObject gameObject;
    MockComponent component(gameObject);

    Assert::IsTrue(component.isActive());
  }

#pragma endregion

#pragma region Destructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_Destructor_RemovesComponentFromGameObject)
  {
    GameObject gameObject;
    
    {
      std::unique_ptr<MockComponent> component(gameObject.addComponent<MockComponent>());

      AssertCel::HasComponent<MockComponent>(gameObject);
    }

    AssertCel::DoesNotHaveComponent<MockComponent>(gameObject);
  }

#pragma endregion

#pragma region Get Transform Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_GetTransform_WithParentSet_ReturnsParentsTransform)
  {
    GameObject gameObject;
    observer_ptr<MockComponent> component = gameObject.addComponent<MockComponent>();

    Assert::IsTrue(component->getTransform() == gameObject.getTransform());
  }

#pragma endregion

#pragma region Get Const Transform Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_GetConstTransform_WithGameObjectSet_ReturnsGameObjectsTransform)
  {
    GameObject gameObject;
    observer_ptr<MockComponent> component = gameObject.addComponent<MockComponent>();

    const MockComponent& constComponent = *component;
    const Transform* constTransform = constComponent.getTransform();

    Assert::IsTrue(constTransform == gameObject.getTransform());
  }

#pragma endregion
  };
}