#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Objects/GameObject.h"
#include "Mocks/Objects/MockEntity.h"
#include "CelesteTestUtils/Assert/AssertCel.h"


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

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Entity_Update_CallsOnUpdate)
  {
    MockEntity entity;

    Assert::IsFalse(entity.isUpdateCalled());

    entity.update();

    Assert::IsTrue(entity.isUpdateCalled());
  }

#pragma endregion

  };
}