#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockEntity.h"


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestEntity)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Constructor_Sets_AliveAndActive_ToFalse)
  {
    MockEntity entity;

    Assert::IsFalse(entity.isAlive());
    Assert::IsFalse(entity.isActive());
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

#pragma region Die Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Die_Sets_AliveAndActive_ToFalse)
  {
    MockEntity entity;
    entity.setActive(true);

    Assert::IsTrue(entity.isAlive());
    Assert::IsTrue(entity.isActive());

    entity.die();

    Assert::IsFalse(entity.isAlive());
    Assert::IsFalse(entity.isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Die_CallsOnDeath)
  {
    MockEntity entity;

    Assert::IsFalse(entity.isOnDeathCalled());

    entity.die();

    Assert::IsTrue(entity.isOnDeathCalled());
  }

#pragma endregion
};
}