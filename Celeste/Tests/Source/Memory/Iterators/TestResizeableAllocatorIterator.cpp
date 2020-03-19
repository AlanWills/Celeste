#include "UtilityHeaders/UnitTestHeaders.h"

#include "Memory/Allocators/ResizeableAllocator.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "Memory/Iterators/ResizeableAllocatorIterator.h"
#include "Mocks/Objects/MockComponent.h"

#include <array>

using namespace Celeste;


ARE_PTRS_EQUAL(MockComponent);

namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestResizeableAllocatorIterator)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_Constructor_InputtingEndIterators_KeepsIteratorToEndElement)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    allocator->allocate();
    allocator->allocate();
    observer_ptr<MockComponent> component3 = allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it(allocators.begin(), allocators.back()->end());

    Assert::AreEqual(component3 + 1, it.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_Constructor_MovesIteratorToFirstAllocatedElement)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> a = std::make_unique<PoolAllocator<MockComponent>>(3);
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(a));
    const auto& allocator = allocators.back();

    observer_ptr<MockComponent> component1 = allocator->allocate();
    observer_ptr<MockComponent> component2 = allocator->allocate();
    observer_ptr<MockComponent> component3 = allocator->allocate();

    ResizeableAllocatorIterator<MockComponent> it(allocators.begin(), allocators.end());

    Assert::AreSame(*component1, *it);

    Assert::IsTrue(allocator->isAllocated(*component1));

    allocator->deallocate(*component1);

    Assert::IsFalse(allocator->isAllocated(*component1));

    it = ResizeableAllocatorIterator<MockComponent>(allocators.begin(), allocators.end());

    Assert::AreSame(*component2, *it);

    allocator->deallocate(*component2);
    it = ResizeableAllocatorIterator<MockComponent>(allocators.begin(), allocators.end());

    Assert::AreSame(*component3, *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_Constructor_WithAllDeallocatedObjects_MovesIteratorToEnd)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it(allocators.begin(), allocators.end());

    Assert::AreEqual(allocators.back()->end().get(), it.get());
  }

#pragma endregion

#pragma region ++ Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_IncrementOperator)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    observer_ptr<MockComponent> component1 = allocator->allocate();
    observer_ptr<MockComponent> component2 = allocator->allocate();
    observer_ptr<MockComponent> component3 = allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it(allocators.begin(), allocators.end());
      
    Assert::AreSame(*component1, *it);

    ++it;

    Assert::AreSame(*component2, *it);

    ++it;

    Assert::AreSame(*component3, *it);

    // Should just stay at end now
    ++it;

    Assert::AreEqual(component3 + 1, it.get());

    ++it;

    Assert::AreEqual(component3 + 2, it.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_ShouldOnlyIterateOverAllocatedComponents)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    observer_ptr<MockComponent> component1 = allocator->allocate();
    observer_ptr<MockComponent> component2 = allocator->allocate();
    observer_ptr<MockComponent> component3 = allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    // Iterator over 3 allocated objects
    {
      ResizeableAllocatorIterator<MockComponent> it(allocators.begin(), allocators.end());

      Assert::AreSame(*component1, *it);

      ++it;

      Assert::AreSame(*component2, *it);

      ++it;

      Assert::AreSame(*component3, *it);
    }

    // Deallocate an object
    {
      allocators.back()->deallocate(*component2);
      ResizeableAllocatorIterator<MockComponent> it(allocators.begin(), allocators.end());

      Assert::AreSame(*component1, *it);

      ++it;

      Assert::AreSame(*component3, *it);
    }

    // Deallocate another object
    {
      allocators.back()->deallocate(*component3);
      ResizeableAllocatorIterator<MockComponent> it(allocators.begin(), allocators.end());

      Assert::AreSame(*component1, *it);

      ++it;

      Assert::AreEqual(component3 + 1, it.get());
    }
  }

#pragma endregion

#pragma region Equality Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_EqualityOperator_ShouldReturnTrue)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());
    ResizeableAllocatorIterator<MockComponent> it2(allocators.begin(), allocators.end());

    Assert::IsTrue(it1 == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_EqualityOperator_ShouldReturnFalse)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    allocator->allocate();
    allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());
    ResizeableAllocatorIterator<MockComponent> it2(allocators.begin(), allocators.end());
    ++it2;

    Assert::IsFalse(it1 == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_EqualityOperator_Reflexivity_ShouldReturnTrue)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());

    Assert::IsTrue(it1 == it1);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_EqualityOperator_IsSymmetric)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());
    ResizeableAllocatorIterator<MockComponent> it2(allocators.begin(), allocators.end());

    Assert::IsTrue(it1 == it2);
    Assert::IsTrue(it2 == it1);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_EqualityOperator_IsTransitive)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());
    ResizeableAllocatorIterator<MockComponent> it2(allocators.begin(), allocators.end());
    ResizeableAllocatorIterator<MockComponent> it3(allocators.begin(), allocators.end());

    Assert::IsTrue(it1 == it2);
    Assert::IsTrue(it2 == it3);
    Assert::IsTrue(it1 == it3);
  }

#pragma endregion

#pragma region Inequality Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_InequalityOperator_ShouldReturnTrue)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    allocator->allocate();
    allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());
    ResizeableAllocatorIterator<MockComponent> it2(allocators.begin(), allocators.end());
    ++it2;

    Assert::IsTrue(it1 != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_InequalityOperator_ShouldReturnFalse)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    allocator->allocate();
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());
    ResizeableAllocatorIterator<MockComponent> it2(allocators.begin(), allocators.end());

    Assert::IsFalse(it1 != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_InequalityOperator_Reflexivity_ShouldReturnFalse)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());

    Assert::IsFalse(it1 != it1);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocatorIterator_InequalityOperator_IsSymmetric)
  {
    std::unique_ptr<PoolAllocator<MockComponent>> allocator = std::make_unique<PoolAllocator<MockComponent>>(3);
    std::list<std::unique_ptr<PoolAllocator<MockComponent>>> allocators;
    allocators.emplace_back(std::move(allocator));

    ResizeableAllocatorIterator<MockComponent> it1(allocators.begin(), allocators.end());

    allocators.back()->allocate();
      
    ResizeableAllocatorIterator<MockComponent> it2(allocators.begin(), allocators.end());

    Assert::IsTrue(it1 != it2);
    Assert::IsTrue(it2 != it1);
  }

  // Inequality operator cannot be transitive

#pragma endregion

  };
}