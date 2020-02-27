#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockComponent.h"
#include "Objects/GameObject.h"
#include "Rendering/SpriteRenderer.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Rendering;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestComponent)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_Constructor_SetsAllInitialValuesCorrectly)
  {
    MockComponent component;

    Assert::IsNull(component.getGameObject());
    Assert::IsNull(component.getTransform());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_Constructor_Sets_ActiveToTrue)
  {
    MockComponent component;

    Assert::IsTrue(component.isActive());
  }

#pragma endregion

#pragma region Deallocate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_Deallocate_WithObjectFromAllocator_ReturnsTrue)
  {
    AutoDeallocator<MockComponent> component = MockComponent::allocate(GameObject());

    Assert::IsTrue(component->deallocate());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Component_Deallocate_WithObjectNotFromAllocator_ReturnsFalse)
  {
    MockComponent component;

    Assert::IsFalse(component.deallocate());
  }

#pragma endregion

#pragma region Set Game Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_SetGameObject_OnParentlessComponent_WithValidInputtedParent_SetsParent)
    {
      MockComponent component;
      GameObject parent;
      GameObject* pPtr = &parent;

      Assert::IsNull(component.getGameObject());
      
      component.setGameObject_Public(parent);

      Assert::IsTrue(pPtr == component.getGameObject());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_SetGameObject_OnComponentWithExistingParent_UpdatesParent)
    {
      MockComponent component;
      GameObject parent, parent2;
      GameObject* pPtr = &parent;
      GameObject* p2Ptr = &parent2;

      component.setGameObject_Public(parent);

      Assert::IsTrue(pPtr == component.getGameObject());

      component.setGameObject_Public(parent2);

      Assert::IsTrue(p2Ptr == component.getGameObject());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_SetGameObject_OnParentlessComponent_CallsOnSetParent)
    {
      MockComponent component;
      GameObject gameObject;

      Assert::IsFalse(component.onSetGameObjectCalled());
      Assert::IsNull(component.getGameObject());

      component.setGameObject_Public(gameObject);

      Assert::IsTrue(component.onSetGameObjectCalled());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_SetGameObject_OnComponentWithExistingParent_CallsOnSetParent)
    {
      MockComponent component;
      GameObject parent1;
      GameObject parent2;

      component.setGameObject_Public(parent1);

      Assert::IsTrue(component.onSetGameObjectCalled());
      
      component.reset();
     
      Assert::IsFalse(component.onSetGameObjectCalled());
      Assert::IsNotNull(component.getGameObject());

      component.setGameObject_Public(parent2);

      Assert::IsTrue(component.onSetGameObjectCalled());
    }

#pragma endregion

#pragma region Get Transform Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_GetTransform_WithNoParentSet_ReturnsNullHandle)
    {
      MockComponent component;

      Assert::IsNull(component.getGameObject());
      Assert::IsNull(component.getTransform());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_GetTransform_WithParentSet_ReturnsParentsTransformHandle)
    {
      GameObject gameObject;
      
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      Assert::IsNotNull(component->getGameObject());
      Assert::IsTrue(component->getTransform() == gameObject.getTransform());
    }

#pragma endregion

#pragma region Get Const Transform Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_GetConstTransform_WithNoParentSet_ReturnsNullHandle)
    {
      MockComponent component;

      const MockComponent& constComponent = static_cast<const MockComponent&>(component);
      const GameObject* constParent = constComponent.getGameObject();
      const Transform* constParentTransform = constComponent.getTransform();

      Assert::IsNull(constParent);
      Assert::IsNull(constParentTransform);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Component_GetConstTransform_WithParentSet_ReturnsParentsTransformHandle)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      const MockComponent& constComponent = *(component.get());
      const GameObject* constParent = constComponent.getGameObject();
      const Transform* constParentTransform = constComponent.getTransform();

      Assert::IsNotNull(constParent);
      Assert::IsTrue(constParentTransform == gameObject.getTransform());
    }

#pragma endregion
  };
}