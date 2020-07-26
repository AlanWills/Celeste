#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Memory/Allocators/ResizeableAllocator.h"
#include "Algorithm/Entity.h"

#include "Mocks/Objects/MockEntity.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestAlgorithmEntity)

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AlgorithmEntity_Update_InputtingResizeableAllocator_CallsUpdateOnAllocatedObjects)
  {
    ResizeableAllocator<MockEntity> allocator(5);
    MockEntity* entity = new (allocator.allocate()) MockEntity();
    MockEntity* entity2 = new (allocator.allocate()) MockEntity();

    Assert::IsFalse(entity->isUpdateCalled());
    Assert::IsFalse(entity2->isUpdateCalled());

    Algorithm::update(allocator);

    Assert::IsTrue(entity->isUpdateCalled());
    Assert::IsTrue(entity2->isUpdateCalled());
  }

#pragma endregion

  };
}