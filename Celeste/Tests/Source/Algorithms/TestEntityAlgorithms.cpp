#include "UtilityHeaders/UnitTestHeaders.h"
#include "Memory/Allocators/ResizeableAllocator.h"
#include "Algorithms/EntityAlgorithms.h"

#include "Mocks/Objects/MockEntity.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestEntityAlgorithms)

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityAlgorithms_HandleInput_InputtingResizeableAllocator_CallsHandleInputOnAllocatedObjects)
  {
    ResizeableAllocator<MockEntity> allocator(5);
    MockEntity* entity = new (allocator.allocate()) MockEntity();
    MockEntity* entity2 = new (allocator.allocate()) MockEntity();

    Assert::IsFalse(entity->isHandleInputCalled());
    Assert::IsFalse(entity2->isHandleInputCalled());

    Algorithms::handleInput(allocator);

    Assert::IsTrue(entity->isHandleInputCalled());
    Assert::IsTrue(entity2->isHandleInputCalled());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityAlgorithms_Update_InputtingResizeableAllocator_CallsUpdateOnAllocatedObjects)
  {
    ResizeableAllocator<MockEntity> allocator(5);
    MockEntity* entity = new (allocator.allocate()) MockEntity();
    MockEntity* entity2 = new (allocator.allocate()) MockEntity();

    Assert::IsFalse(entity->isHandleInputCalled());
    Assert::IsFalse(entity2->isHandleInputCalled());

    Algorithms::handleInput(allocator);

    Assert::IsTrue(entity->isHandleInputCalled());
    Assert::IsTrue(entity2->isHandleInputCalled());
  }

#pragma endregion

  };
}