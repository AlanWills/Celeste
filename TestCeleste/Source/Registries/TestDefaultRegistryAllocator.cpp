#include "UtilityHeaders/UnitTestHeaders.h"

#include "Registries/DefaultRegistryAllocator.h"
#include "Mocks/Objects/MockComponent.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste::Registries
{
  CELESTE_TEST_CLASS(TestDefaultRegistryAllocator)

#pragma region Allocate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DefaultRegistryAllocator_Allocate_ReturnsAllocatedComponentOfCorrectType)
  {
    DefaultRegistryAllocator<MockComponent> mockComponent;
    GameObject gameObject;

    observer_ptr<Component> component = mockComponent.allocate("", gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<MockComponent*>(component));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DefaultRegistryAllocator_Allocate_SetsComponentGameObject_ToInputtedGameObject)
  {
    DefaultRegistryAllocator<MockComponent> mockComponent;
    GameObject gameObject;

    observer_ptr<Component> component = mockComponent.allocate("", gameObject);

    Assert::IsNotNull(component);
    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

  };
}