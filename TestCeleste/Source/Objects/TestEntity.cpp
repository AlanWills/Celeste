#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockEntity.h"
#include "AssertCel.h"


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestEntity)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Constructor_Sets_Active_ToTrue)
  {
    MockEntity entity;

    AssertCel::IsActive(entity);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Constructor_CallsSetActive)
  {
    MockEntity entity;

    Assert::IsTrue(entity.isSetActiveCalled());
  }

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_HandleInput_CallsOnHandleInput)
  {
    MockEntity entity;

    Assert::IsFalse(entity.isOnHandleInputCalled());

    entity.handleInput();

    Assert::IsTrue(entity.isOnHandleInputCalled());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Update_CallsOnUpdate)
  {
    MockEntity entity;

    Assert::IsFalse(entity.isOnUpdateCalled());

    entity.update(0);

    Assert::IsTrue(entity.isOnUpdateCalled());
  }

#pragma endregion

  };
}