#include "UtilityHeaders/UnitTestHeaders.h"
#include "UtilityMacros/Unused.h"

#include "Memory/Allocators/ResizeableAllocator.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "Mocks/Objects/MockComponent.h"
#include "Objects/GameObject.h"

using namespace Celeste;

ARE_PTRS_EQUAL(MockComponent);

namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestResizeableAllocator)

#pragma region Is Allocated Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_IsAllocated_InputtingAllocatedObject_ShouldReturnTrue)
  {
    ResizeableAllocator<MockComponent> allocator(10);
    observer_ptr<MockComponent> object = allocator.allocate();

    Assert::AreEqual((size_t)1, allocator.size());
    Assert::IsTrue(allocator.isAllocated(*object));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Allocate_InputtingUnAllocatedObject_ShouldReturnFalse)
  {
    ResizeableAllocator<MockComponent> allocator(10);
    MockComponent& object = *allocator.allocate();

    Assert::AreEqual((size_t)1, allocator.size());

    allocator.deallocate(object);

    Assert::AreEqual((size_t)0, allocator.size());
    Assert::IsFalse(allocator.deallocate(object));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Allocate_InputtingObjectNotFromAllocator_ShouldReturnFalse)
  {
    GameObject gameObject;
    MockComponent object(gameObject);
    ResizeableAllocator<MockComponent> allocator(10);

    Assert::AreEqual((size_t)0, allocator.size());
    Assert::IsFalse(allocator.deallocate(object));
  }

#pragma endregion

#pragma region Allocate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Allocate_WithSpaceInAllocator_ReturnsAllocatedPtr)
  {
    ResizeableAllocator<MockComponent> allocator(10);
    observer_ptr<MockComponent> handle = allocator.allocate();

    Assert::IsNotNull(handle);
    Assert::AreEqual((size_t)1, allocator.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Allocate_WithNotEnoughSpaceInAllocator_IncreasesSize)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    allocator.allocate();

    Assert::AreEqual((size_t)1, allocator.size());

    observer_ptr<MockComponent> handle = allocator.allocate();

    Assert::IsNotNull(handle);
    Assert::AreEqual((size_t)2, allocator.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Allocate_Resizing_PreservesPtrs)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    observer_ptr<MockComponent> handle3 = allocator.allocate();

    Assert::IsNotNull(handle);
    Assert::IsNotNull(handle2);
    Assert::IsNotNull(handle3);
    Assert::IsFalse(handle == handle2);
    Assert::AreEqual((size_t)3, allocator.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Allocate_PreviouslyDeallocatedObject_ObjectReallocated)
  {
    ResizeableAllocator<MockComponent> allocator(10);
    observer_ptr<MockComponent> handle = allocator.allocate();

    allocator.deallocate(*handle);

    Assert::IsFalse(allocator.isAllocated(*handle));
    Assert::AreEqual((size_t)0, allocator.size());

    observer_ptr<MockComponent> handle2 = allocator.allocate();

    Assert::AreEqual((size_t)1, allocator.size());
    Assert::IsNotNull(handle2);
    Assert::IsTrue(handle == handle2);
    Assert::IsTrue(allocator.isAllocated(*handle));
  }

#pragma endregion

#pragma region Deallocate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Deallocate_ObjectNotFromAllocator_DoesNothingAndReturnsFalse)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    GameObject gameObject;
    MockComponent component(gameObject);

    Assert::IsTrue(component.isActive());
    Assert::IsFalse(allocator.contains(component));
    Assert::IsFalse(allocator.deallocate(component));
    Assert::IsTrue(component.isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Deallocate_ObjectFromAllocator_DeallocatesObject_ResetsFlags_AndReturnsTrue)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle = allocator.allocate();

    Assert::IsTrue(handle->isActive());
    Assert::AreEqual((size_t)1, allocator.size());
    Assert::IsTrue(allocator.isAllocated(*handle));

    Assert::IsTrue(allocator.deallocate(*handle));

    Assert::AreEqual((size_t)0, allocator.size());
    Assert::IsFalse(allocator.isAllocated(*handle));
  }

#pragma endregion

#pragma region Size Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Size_EqualsNumberOfAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
      
    Assert::AreEqual((size_t)0, allocator.size());

    observer_ptr<MockComponent> handle = allocator.allocate();

    Assert::AreEqual((size_t)1, allocator.size());

    allocator.allocate();
    allocator.allocate();

    Assert::AreEqual((size_t)3, allocator.size());

    allocator.allocate();

    Assert::AreEqual((size_t)4, allocator.size());

    allocator.deallocate(*handle);

    Assert::AreEqual((size_t)3, allocator.size());
  }

#pragma endregion

#pragma region Begin Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Begin_ReturnsFirstAllocatedObject)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();
    ResizeableAllocatorIterator<MockComponent> it = allocator.begin();

    Assert::AreSame(*handle1, *it);

    // Deallocate an object
    allocator.deallocate(*handle1);
    it = allocator.begin();

    Assert::AreSame(*handle2, *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_BeginOnConst_ReturnsConstFirstAllocatedObject)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();
    ResizeableAllocatorIterator<const MockComponent> it = (static_cast<const ResizeableAllocator<MockComponent>&>(allocator).begin());

    Assert::AreSame(*handle1, *it);

    // Deallocate an object
    allocator.deallocate(*handle1);
    it = (static_cast<const ResizeableAllocator<MockComponent>&>(allocator).begin());

    Assert::AreSame(*handle2, *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_CBegin_ReturnsConstFirstAllocatedObject)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    ResizeableAllocatorIterator<const MockComponent> it = allocator.cbegin();
    Assert::AreSame(*handle1, *it);

    // Deallocate an object
    allocator.deallocate(*handle1);
    it = allocator.cbegin();

    Assert::AreSame(*handle2, *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_begin_WithNoAllocatedObjects_Equals_end)
  {
    ResizeableAllocator<MockComponent> allocator(3);

    Assert::IsTrue(allocator.begin() == allocator.end());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_cbegin_WithNoAllocatedObjects_Equals_cend)
  {
    ResizeableAllocator<MockComponent> allocator(3);

    Assert::IsTrue(allocator.cbegin() == allocator.cend());
  }

#pragma endregion

#pragma region Foreach Iteration

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ForeachIteration_AllPoolAllocated_IteratesOverAllocatedObjectsOnly)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    // 3 allocated objects
    {
      int count = 0;
      for (const MockComponent& component : allocator)
      {
        UNUSED(component);
        count++;
      }

      Assert::AreEqual(3, count);
    }

    // Now deallocate 1 object
    {
      allocator.deallocate(*handle1);

      int count = 0;
      for (const MockComponent& component : allocator)
      {
        UNUSED(component);
        count++;
      }

      Assert::AreEqual(2, count);
    }

    // Now deallocate another object
    {
      allocator.deallocate(*handle2);

      int count = 0;
      for (const MockComponent& component : allocator)
      {
        UNUSED(component);
        count++;
      }

      Assert::AreEqual(1, count);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ForeachIteration_PoolShrinkOccurred_IteratesOverAllocatedObjectsOnly)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    // 3 allocated objects
    {
      int count = 0;
      for (const MockComponent& component : allocator)
      {
        UNUSED(component);
        count++;
      }

      Assert::AreEqual(3, count);
    }

    // Now deallocate 1 object
    {
      allocator.deallocate(*handle1);

      int count = 0;
      for (const MockComponent& component : allocator)
      {
        UNUSED(component);
        count++;
      }

      Assert::AreEqual(2, count);
    }

    // Now deallocate another object
    {
      allocator.deallocate(*handle2);

      int count = 0;
      for (const MockComponent& component : allocator)
      {
        UNUSED(component);
        count++;
      }

      Assert::AreEqual(1, count);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ForeachIteration_PoolExpandOccurs_IteratesOverInitiallyAllocatedObjectsOnly)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    allocator.allocate();

    {
      int count = 0;
      for (const MockComponent& component : allocator)
      {
        if (count == 0)
        {
          for (size_t i = 0; i < 2 * allocator.capacity(); ++i)
          {
            allocator.allocate();
          }
        }

        UNUSED(component);
        count++;
      }

      Assert::AreEqual(1, count);
    }
  }

#pragma endregion

#pragma region Find Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Find_NoResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    observer_ptr<MockComponent> handle3 = allocator.allocate();

    Assert::IsTrue(allocator.isAllocated(*handle1));
    Assert::IsTrue(allocator.isAllocated(*handle2));
    Assert::IsTrue(allocator.isAllocated(*handle3));

    // All three objects allocated
    {
      observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(handle1, foundObject);
    }

    // 2 allocated objects
    {
      allocator.deallocate(*handle1);

      observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(handle2, foundObject);
    }

    // 1 allocated object
    {
      // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
      allocator.deallocate(*handle2);

      observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(handle3, foundObject);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Find_ResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(2);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    observer_ptr<MockComponent> handle3 = allocator.allocate();

    Assert::IsTrue(allocator.isAllocated(*handle1));
    Assert::IsTrue(allocator.isAllocated(*handle2));
    Assert::IsTrue(allocator.isAllocated(*handle3));

    // All three objects allocated
    {
      observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(handle1, foundObject);
    }

    // 2 allocated objects
    {
      allocator.deallocate(*handle1);

      observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(handle2, foundObject);
    }

    // 1 allocated object
    {
      // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
      allocator.deallocate(*handle2);

      observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(handle3, foundObject);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Find_NoResizeOccurred_ShouldNotFindAnything)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    Assert::IsNull(allocator.find([](const MockComponent&) -> bool { return false; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Find_ResizeOccurred_ShouldNotFindAnything)
  {
    ResizeableAllocator<MockComponent> allocator(2);
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    Assert::IsNull(allocator.find([](const MockComponent&) -> bool { return false; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Find_NoResizeOccurred_ReturnsFirstMatchingObject)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    Assert::AreEqual(handle2, allocator.find([handle1](const MockComponent& component) -> bool { return &component != handle1; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Find_ResizeOccurred_ReturnsFirstMatchingObject)
  {
    ResizeableAllocator<MockComponent> allocator(2);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    Assert::AreEqual(handle2, allocator.find([handle1](const MockComponent& component) -> bool { return &component != handle1; }));
    Assert::IsNull(allocator.find([](const MockComponent&) -> bool { return false; }));
  }

#pragma endregion

#pragma region Const Find Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFind_NoResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    observer_ptr<MockComponent> handle3 = allocator.allocate();

    Assert::IsTrue(allocator.isAllocated(*handle1));
    Assert::IsTrue(allocator.isAllocated(*handle2));
    Assert::IsTrue(allocator.isAllocated(*handle3));

    // Need const reference to call const functions
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    // All three objects allocated
    {
      observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(static_cast<const MockComponent*>(handle1), foundObject);
    }

    // 2 allocated objects
    {
      allocator.deallocate(*handle1);

      observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(static_cast<const MockComponent*>(handle2), foundObject);
    }

    // 1 allocated object
    {
      // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
      allocator.deallocate(*handle2);

      observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(static_cast<const MockComponent*>(handle3), foundObject);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFind_ResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(2);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    observer_ptr<MockComponent> handle3 = allocator.allocate();

    Assert::IsTrue(allocator.isAllocated(*handle1));
    Assert::IsTrue(allocator.isAllocated(*handle2));
    Assert::IsTrue(allocator.isAllocated(*handle3));

    // Need a const reference to call const functions
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    // All three objects allocated
    {
      observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(static_cast<const MockComponent*>(handle1), foundObject);
    }

    // 2 allocated objects
    {
      allocator.deallocate(*handle1);

      Assert::IsFalse(allocator.isAllocated(*handle1));

      observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(static_cast<const MockComponent*>(handle2), foundObject);
    }

    // 1 allocated object
    {
      // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
      allocator.deallocate(*handle2);

      observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent&) -> bool { return true; });

      Assert::IsNotNull(foundObject);
      Assert::AreEqual(static_cast<const MockComponent*>(handle3), foundObject);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFind_NoResizeOccurred_ShouldNotFindAnything)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    // Need a const reference to call const functions
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    Assert::IsNull(allocatorRef.find([](const MockComponent&) -> bool { return false; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFind_ResizeOccurred_ShouldNotFindAnything)
  {
    ResizeableAllocator<MockComponent> allocator(2);
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    // Need a const reference to call const functions
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    Assert::IsNull(allocatorRef.find([](const MockComponent&) -> bool { return false; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFind_NoResizeOccurred_ReturnsFirstMatchingObject)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    // Need a const reference to call const functions
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    Assert::AreEqual(static_cast<const MockComponent*>(handle2), allocatorRef.find([&handle1](const MockComponent& component) -> bool { return &component != handle1; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFind_ResizeOccurred_ReturnsFirstMatchingObject)
  {
    ResizeableAllocator<MockComponent> allocator(2);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    // Need a const reference to call const functions
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    Assert::AreEqual(static_cast<const MockComponent*>(handle2), allocatorRef.find([&handle1](const MockComponent& component) -> bool { return &component != handle1; }));
  }

#pragma endregion

#pragma region Find All Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_FindAll_NoResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();
      
    // Three allocated objects
    {
      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent&) { return true; }, foundObjects);

      Assert::AreEqual((size_t)3, foundObjects.size());
    }

    // Now deallocate one object
    {
      allocator.deallocate(*handle1);
        
      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent&) { return true; }, foundObjects);

      Assert::AreEqual((size_t)2, foundObjects.size());
    }

    // Now deallocator another
    {
      allocator.deallocate(*handle2);

      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)1, foundObjects.size());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_FindAll_ResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    // Three allocated objects
    {
      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)3, foundObjects.size());
    }

    // Now deallocate one object
    {
      allocator.deallocate(*handle1);

      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent&) { return true; }, foundObjects);

      Assert::AreEqual((size_t)2, foundObjects.size());
    }

    // Now deallocate another another
    {
      allocator.deallocate(*handle2);

      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)1, foundObjects.size());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_FindAll_NoResizeOccurred_ShouldNotFindAnything)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    std::vector<std::reference_wrapper<MockComponent>> foundObjects;
    allocator.findAll([](const MockComponent&) { return false; }, foundObjects);

    Assert::AreEqual((size_t)0, foundObjects.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_FindAll_ResizeOccurred_ShouldNotFindAnything)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    std::vector<std::reference_wrapper<MockComponent>> foundObjects;
    allocator.findAll([](const MockComponent&) { return false; }, foundObjects);

    Assert::AreEqual((size_t)0, foundObjects.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_FindAll_OnlyPoolAllocatorObjects_ShouldFindObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    std::vector<std::reference_wrapper<MockComponent>> foundObjects;
    allocator.findAll([&handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

    Assert::AreEqual((size_t)1, foundObjects.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_FindAll_PoolAndOverflowAllocatorObjects_ShouldFindObjects)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    std::vector<std::reference_wrapper<MockComponent>> foundObjects;
    allocator.findAll([&handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

    Assert::AreEqual((size_t)1, foundObjects.size());
  }

#pragma endregion

#pragma region Const Find All Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFindAll_NoResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    // Used so we can force the const version of find
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    // Three allocated objects
    {
      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)3, foundObjects.size());
    }

    // Now deallocate one object
    {
      allocator.deallocate(*handle1);

      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)2, foundObjects.size());
    }

    // Now deallocate another
    {
      allocator.deallocate(*handle2);

      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)1, foundObjects.size());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFindAll_ResizeOccurred_OnlySearchesThroughAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    observer_ptr<MockComponent> handle2 = allocator.allocate();
    allocator.allocate();

    // Used so we can force the const version of find
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    // Three allocated objects
    {
      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)3, foundObjects.size());
    }

    // Now deallocate one object
    {
      allocator.deallocate(*handle1);

      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)2, foundObjects.size());
    }

    // Now deallocate another
    {
      allocator.deallocate(*handle2);

      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
      Assert::AreEqual((size_t)1, foundObjects.size());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFindAll_ShouldNotFindAnything)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    // Used so we can force the const version of find
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
    allocatorRef.findAll([](const MockComponent&) { return false; }, foundObjects);

    Assert::AreEqual((size_t)0, foundObjects.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFindAll_NoResizeOccurred_ShouldFindObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    // Used so we can force the const version of find
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
    allocatorRef.findAll([&handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

    Assert::AreEqual((size_t)1, foundObjects.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_ConstFindAll_ResizeOccurred_ShouldFindObjects)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    allocator.allocate();
    allocator.allocate();

    // Used so we can force the const version of find
    const ResizeableAllocator<MockComponent>& allocatorRef = allocator;

    std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
    allocatorRef.findAll([&handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

    Assert::AreEqual((size_t)1, foundObjects.size());
  }
    
#pragma endregion

#pragma region Contains Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Contains_InputtingObjectFromAllocator_ReturnsTrue)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> component = allocator.allocate();

    Assert::IsTrue(allocator.contains(*component));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_Contains_InputtingObjectNotFromResizeableAllocator_ReturnsFalse)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    GameObject gameObject;
    MockComponent component(gameObject);

    Assert::IsFalse(allocator.contains(component));
  }

#pragma endregion

#pragma region Deallocate All Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_DeallocateAll_DeallocatesAllPoolAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(3);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    const MockComponent* ptr1 = handle1;

    observer_ptr<MockComponent> handle2 = allocator.allocate();
    const MockComponent* ptr2 = handle2;

    allocator.deallocateAll();

    Assert::AreEqual((size_t)0, allocator.size());
    Assert::IsFalse(allocator.isAllocated(*ptr1));
    Assert::IsFalse(allocator.isAllocated(*ptr2));

    observer_ptr<MockComponent> handle3 = allocator.allocate();
    const MockComponent* ptr3 = handle3;

    Assert::IsTrue(allocator.isAllocated(*handle3));

    allocator.deallocateAll();

    Assert::AreEqual((size_t)0, allocator.size());
    Assert::IsFalse(allocator.isAllocated(*ptr3));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResizeableAllocator_DeallocateAll_ResizeOccurred_DeallocatesAllPoolAllocatedObjects)
  {
    ResizeableAllocator<MockComponent> allocator(1);
    observer_ptr<MockComponent> handle1 = allocator.allocate();
    const MockComponent* ptr1 = handle1;

    observer_ptr<MockComponent> handle2 = allocator.allocate();
    const MockComponent* ptr2 = handle2;

    allocator.deallocateAll();

    Assert::AreEqual((size_t)0, allocator.size());
    Assert::IsFalse(allocator.isAllocated(*ptr1));
    Assert::IsFalse(allocator.isAllocated(*ptr2));

    observer_ptr<MockComponent> handle3 = allocator.allocate();
    const MockComponent* ptr3 = handle3;

    Assert::IsTrue(allocator.isAllocated(*handle3));

    allocator.deallocateAll();

    Assert::AreEqual((size_t)0, allocator.size());
    Assert::IsFalse(allocator.isAllocated(*ptr3));
  }

#pragma endregion

  };
}