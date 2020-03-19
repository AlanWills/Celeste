#include "UtilityHeaders/UnitTestHeaders.h"

#include "Memory/Allocators/PoolAllocator.h"
#include "Mocks/Objects/MockComponent.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"
#include "UtilityMacros/Unused.h"

#include <vector>

using namespace Celeste;


ARE_PTRS_EQUAL(MockComponent);

namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestPoolAllocator)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PoolAllocator_Constructor_InputtingCapacity_SetsSizeToZero)
  {
    // Int pool
    {
      PoolAllocator<int> intPool( 10);
      Assert::AreEqual((size_t)0, intPool.size());
    }

    // Char pool
    {
      PoolAllocator<char> charPool(100);
      Assert::AreEqual((size_t)0, charPool.size());
    }

    // Pointer pool
    {
      PoolAllocator<float*> pointerPool(1);
      Assert::AreEqual((size_t)0, pointerPool.size());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PoolAllocator_Constructor_InputtingCapacity_SetsCapacityToInputtedValue)
  {
    // Int pool
    {
      PoolAllocator<int> intPool(10);
      Assert::AreEqual((size_t)10, intPool.capacity());
    }

    // Char pool
    {
      PoolAllocator<char> charPool(100);
      Assert::AreEqual((size_t)100, charPool.capacity());
    }

    // Pointer pool
    {
      PoolAllocator<float*> pointerPool(1);
      Assert::AreEqual((size_t)1, pointerPool.capacity());
    }
  }

#pragma endregion

#pragma region Can Allocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_CanAllocate_ShouldReturnTrue)
    {
      PoolAllocator<int> intPool(1024);
      std::vector<size_t> validAllocs { 0, 1, 1023, 1024 };

      for (size_t alloc : validAllocs)
      {
        Assert::IsTrue(intPool.canAllocate(alloc));
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_CanAllocate_ShouldReturnFalse)
    {
      PoolAllocator<int> intPool(1024);
      std::vector<size_t> invalidAllocs { 1025, 1111111111 };

      for (size_t alloc : invalidAllocs)
      {
        Assert::IsFalse(intPool.canAllocate(alloc));
      }
    }

#pragma endregion

#pragma region Is Allocated Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_IsAllocated_InputtingAllocatedObject_ShouldReturnTrue)
    {
      PoolAllocator<MockComponent> pool(1024);
      observer_ptr<MockComponent> object = pool.allocate();

      Assert::AreEqual((size_t)1, pool.size());
      Assert::IsTrue(pool.isAllocated(*object));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_Allocate_InputtingUnAllocatedObject_ShouldReturnFalse)
    {
      PoolAllocator<MockComponent> pool(1024);
      MockComponent& object = *pool.allocate();

      Assert::AreEqual((size_t)1, pool.size());

      pool.deallocate(object);

      Assert::AreEqual((size_t)0, pool.size());
      Assert::IsFalse(pool.deallocate(object));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_Allocate_InputtingObjectNotFromAllocator_ShouldReturnFalse)
    {
      GameObject gameObject;
      MockComponent object(gameObject);
      PoolAllocator<MockComponent> pool(1024);

      Assert::AreEqual((size_t)0, pool.size());
      Assert::IsFalse(pool.deallocate(object));
    }

#pragma endregion

#pragma region Allocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_Allocate_WithEnoughRoom_ReturnsAllocatedObject)
    {
      PoolAllocator<MockComponent> pool(1024);
      observer_ptr<MockComponent> object = pool.allocate();

      Assert::IsNotNull(object);
      Assert::AreEqual((size_t)1, pool.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_Allocate_WithNotEnoughRoom_ReturnsNullptrHandle)
    {
      PoolAllocator<MockComponent> pool(1);
      observer_ptr<MockComponent> object = pool.allocate();
      object = pool.allocate();

      Assert::IsNull(object);
      Assert::AreEqual((size_t)1, pool.size());
    }

#pragma endregion

#pragma region Deallocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_Deallocate_InputtingFirstElementOfPool_ReturnsTrue)
    {
      PoolAllocator<MockComponent> pool(1024);
      observer_ptr<MockComponent> object = pool.allocate();

      Assert::IsNotNull(object);
      Assert::AreEqual((size_t)1, pool.size());
      Assert::IsTrue(pool.deallocate(*object));
      Assert::AreEqual((size_t)0, pool.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_Deallocate_InputtingNonFirstElementOfPool_ReturnsTrue)
    {
      PoolAllocator<MockComponent> pool(1024);
      observer_ptr<MockComponent> first = pool.allocate();
      observer_ptr<MockComponent> object = pool.allocate();

      Assert::IsNotNull(object);
      Assert::AreEqual((size_t)2, pool.size());
      Assert::IsTrue(pool.deallocate(*object));
      Assert::IsNotNull(first);
      Assert::AreEqual((size_t)1, pool.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_Deallocate_InputtingAlreadyDeallocatedElement_ReturnsFalse)
    {
      PoolAllocator<MockComponent> pool(1024);
      observer_ptr<MockComponent> object = pool.allocate();

      Assert::IsNotNull(object);
      Assert::AreEqual((size_t)1, pool.size());
      Assert::IsTrue(pool.deallocate(*object));

      Assert::AreEqual((size_t)0, pool.size());
      Assert::IsFalse(pool.deallocate(*object));
      Assert::AreEqual((size_t)0, pool.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_DeallocateElementNotFromPool_DoesNothingAndReturnsFalse)
    {
      GameObject gameObject;
      MockComponent object(gameObject);
      PoolAllocator<MockComponent> pool(1024);
      
      Assert::IsFalse(pool.contains(object));
      Assert::IsFalse(pool.deallocate(object));
    }

#pragma endregion

#pragma region Deallocate All Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_DeallocateAll)
    {
      PoolAllocator<MockComponent> pool(1024);
      observer_ptr<MockComponent> object = pool.allocate();

      // Do some more allocation just to move the head
      pool.allocate();

      Assert::AreEqual((size_t)2, pool.size());

      // Free everything
      pool.deallocateAll();

      Assert::AreEqual((size_t)0, pool.size());
      Assert::AreEqual(object, pool.allocate());
    }

#pragma endregion

#pragma region Iteration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_ForeachIteration_WithNoAllocation_DoesNoIteration)
    {
      PoolAllocator<MockComponent> pool(1024);
      Assert::AreEqual((size_t)0, pool.size());

      int count = 0;
      for (MockComponent& item : pool)
      {
        UNUSED(item);
        count++;
      }

      Assert::AreEqual(0, count);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocator_ForeachIteration_WithAllocation_OnlyIteratesOverAllocatedItems)
    {
      PoolAllocator<MockComponent> pool(1024);
      observer_ptr<const MockComponent> expected = pool.allocate();

      for (int i = 0; i < 499; ++i)
      {
        pool.allocate();
      }

      Assert::AreEqual((size_t)500, pool.size());

      int count = 0;
      for (const MockComponent& item : pool)
      {
        count++;
        Assert::IsTrue(expected == &item);
        expected++;
      }

      Assert::AreEqual(500, count);
    }

#pragma endregion

  };
}