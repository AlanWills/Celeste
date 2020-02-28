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

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_HandleInput_CallsOnHandleInput)
  {
    MockEntity entity;

    Assert::IsFalse(entity.isHandleInputCalled());

    entity.handleInput();

    Assert::IsTrue(entity.isHandleInputCalled());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Update_CallsOnUpdate)
  {
    MockEntity entity;

    Assert::IsFalse(entity.isUpdateCalled());

    entity.update(0);

    Assert::IsTrue(entity.isUpdateCalled());
  }

#pragma endregion

  };
}