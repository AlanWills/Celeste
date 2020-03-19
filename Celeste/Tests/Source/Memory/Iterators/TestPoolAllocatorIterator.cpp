#include "UtilityHeaders/UnitTestHeaders.h"

#include "Memory/Allocators/PoolAllocator.h"
#include "Memory/Iterators/PoolAllocatorIterator.h"

#include <array>

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestPoolAllocatorIterator)

#pragma region ++ Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PoolAllocatorIterator_SkipsDeallocatedObjects)
  {
    std::array<int, 3> objects;
    std::array<bool, 3> allocated{ true, false, true };

    PoolAllocatorIterator<const int> it(objects.data(), allocated.data(), 3);
      
    Assert::AreSame(*it, objects[0]);

    ++it;

    Assert::AreSame(*it, objects[2]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PoolAllocatorIterator_IteratesOverObjects)
  {
    std::array<int, 3> objects;
    std::array<bool, 3> allocated{ true, true, true };

    PoolAllocatorIterator<const int> it(objects.data(), allocated.data(), 3);

    // Iterate with 3 allocated objects should stop at the last one
    {
      Assert::AreSame(*it, objects[0]);

      ++it;

      Assert::AreSame(*it, objects[1]);

      ++it;

      Assert::AreSame(*it, objects[2]);

      ++it;

      Assert::IsTrue(it.get() == objects.data() + 3);
    }
  }

#pragma endregion

#pragma region Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_EqualityOperator_ShouldReturnTrue)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it2(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it3(objects.data(), allocated.data(), 3);
      ++it3;

      Assert::IsTrue(it == it2);
      Assert::IsTrue(it == it3);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_EqualityOperator_ShouldReturnFalse)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data(), allocated.data(), 3);
      PoolAllocatorIterator<const int> it2(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it3(objects.data(), allocated.data(), 3);
      ++it3;

      Assert::IsFalse(it == it2);
      Assert::IsFalse(it == it3);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_EqualityOperator_Reflexivity_ShouldReturnTrue)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data(), allocated.data(), 3);

      Assert::IsTrue(it == it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_EqualityOperator_IsSymmetric)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data(), allocated.data(), 3);
      PoolAllocatorIterator<const int> it2(objects.data(), allocated.data(), 3);

      Assert::IsTrue(it == it2);
      Assert::IsTrue(it2 == it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_EqualityOperator_IsTransitive)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it2(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it3(objects.data(), allocated.data(), 3);
      ++it3;

      // a == b
      Assert::IsTrue(it == it2);

      // a == c
      Assert::IsTrue(it == it3);

      // => b == c
      Assert::IsTrue(it2 == it3);
    }

#pragma endregion

#pragma region Inequality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_InequalityOperator_ShouldReturnTrue)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data(), allocated.data(), 3);
      PoolAllocatorIterator<const int> it2(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it3(objects.data(), allocated.data(), 3);
      ++it3;

      Assert::IsTrue(it != it2);
      Assert::IsTrue(it != it3);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_InequalityOperator_ShouldReturnFalse)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it2(objects.data() + 1, allocated.data(), 3);
      PoolAllocatorIterator<const int> it3(objects.data(), allocated.data(), 3);
      ++it3;

      Assert::IsFalse(it != it2);
      Assert::IsFalse(it != it3);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_InequalityOperator_Reflexivity_ShouldReturnFalse)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data() + 1, allocated.data(), 3);
      
      Assert::IsFalse(it != it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PoolAllocatorIterator_InequalityOperator_IsSymmetric)
    {
      std::array<int, 3> objects;
      std::array<bool, 3> allocated{ true, true, true };

      PoolAllocatorIterator<const int> it(objects.data(), allocated.data(), 3);
      PoolAllocatorIterator<const int> it2(objects.data() + 1, allocated.data(), 3);
      
      Assert::IsTrue(it != it2);
      Assert::IsTrue(it2 != it);
    }

    // Inequality operator is not transitive

#pragma endregion

  };
}