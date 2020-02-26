#include "UtilityHeaders/UnitTestHeaders.h"

#include "Memory/Allocators/EntityAllocator.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "Mocks/Objects/MockComponent.h"
#include "AssertCel.h"
#include "Utils/ObjectUtils.h"

using namespace Celeste;


ARE_PTRS_EQUAL(MockComponent);

namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestEntityAllocator)

#pragma region Allocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Allocate_WithSpaceInAllocator_ReturnsAlivePtr)
    {
      EntityAllocator<MockComponent> allocator(10);
      observer_ptr<MockComponent> handle = allocator.allocate();

      Assert::IsNotNull(handle);
      Assert::IsTrue(handle->isAlive());
      Assert::AreEqual((size_t)1, allocator.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Allocate_WithNotEnoughSpaceInAllocator_IncreasesSize)
    {
      EntityAllocator<MockComponent> allocator(1);
      allocator.allocate();

      Assert::AreEqual((size_t)1, allocator.size());

      observer_ptr<MockComponent> handle = allocator.allocate();

      Assert::IsNotNull(handle);
      Assert::AreEqual((size_t)2, allocator.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Allocate_Resizing_PreservesPtrs)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsNotNull(handle);
      Assert::IsTrue(handle->isAlive());

      Assert::IsNotNull(handle2);
      Assert::IsTrue(handle2->isAlive());

      Assert::IsNotNull(handle3);
      Assert::IsTrue(handle3->isAlive());

      Assert::IsFalse(handle == handle2);
      Assert::AreEqual((size_t)3, allocator.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Allocate_PreviouslyDeallocatedObject_ObjectNowAlive)
    {
      EntityAllocator<MockComponent> allocator(10);
      observer_ptr<MockComponent> handle = allocator.allocate();

      allocator.deallocate(*handle);

      Assert::IsFalse(handle->isAlive());
      Assert::AreEqual((size_t)0, allocator.size());

      observer_ptr<MockComponent> handle2 = allocator.allocate();

      Assert::AreEqual((size_t)1, allocator.size());
      Assert::IsNotNull(handle2);
      Assert::IsTrue(handle == handle2);
      Assert::IsTrue(handle->isAlive());
    }

#pragma endregion

#pragma region Deallocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Deallocate_ObjectNotFromAllocator_DoesNothingAndReturnsFalse)
    {
      EntityAllocator<MockComponent> allocator(1);
      MockComponent component;

      Assert::IsTrue(component.isAlive());
      Assert::IsFalse(allocator.contains(component));
      Assert::IsFalse(allocator.deallocate(component));
      Assert::IsTrue(component.isAlive());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Deallocate_AllocatedObject_DeallocatesObject_ResetsFlags_AndReturnsTrue)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle = allocator.allocate();

      Assert::IsTrue(handle->isAlive());
      Assert::IsTrue(handle->isActive());
      Assert::AreEqual((size_t)1, allocator.size());

      Assert::IsTrue(allocator.deallocate(*handle));

      Assert::IsFalse(handle->isAlive());
      Assert::IsFalse(handle->isActive());
      Assert::AreEqual((size_t)0, allocator.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Deallocate_AllocatedObject_CallsDieIfNecessary)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle = allocator.allocate();

      Assert::IsTrue(handle->isAlive());
      Assert::IsFalse(handle->onDeathCalled());
      Assert::IsTrue(allocator.deallocate(*handle));
      Assert::IsFalse(handle->isAlive());
      Assert::IsTrue(handle->onDeathCalled());
    }

#pragma endregion

#pragma region Size Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Size_EqualsNumberOfAllocatedObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      
      Assert::AreEqual((size_t)0, allocator.size());

      observer_ptr<MockComponent> handle = allocator.allocate();

      Assert::AreEqual((size_t)1, allocator.size());

      allocator.allocate();
      allocator.allocate();

      Assert::AreEqual((size_t)3, allocator.size());

      handle->die();

      Assert::AreEqual((size_t)3, allocator.size());

      allocator.allocate();

      Assert::AreEqual((size_t)4, allocator.size());

      allocator.deallocate(*handle);

      Assert::AreEqual((size_t)3, allocator.size());
    }

#pragma endregion

#pragma region Begin Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Begin_ReturnsFirstAllocatedAndAliveObject)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();
      EntityAllocatorIterator<MockComponent> it = allocator.begin();

      Assert::AreSame(*handle1, *it);

      // Deallocate an object
      allocator.deallocate(*handle1);
      it = allocator.begin();

      Assert::AreSame(*handle2, *it);

      // Kill an object, but keep it allocated
      handle2->die();
      it = allocator.begin();

      Assert::AreSame(*handle3, *it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_BeginOnConst_ReturnsConstFirstAllocatedAndAliveObject)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();
      EntityAllocatorIterator<const MockComponent> it = (static_cast<const EntityAllocator<MockComponent>&>(allocator).begin());

      Assert::AreSame(*handle1, *it);

      // Deallocate an object
      allocator.deallocate(*handle1);
      it = (static_cast<const EntityAllocator<MockComponent>&>(allocator).begin());

      Assert::AreSame(*handle2, *it);

      // Kill an object, but keep it allocated
      handle2->die();
      it = (static_cast<const EntityAllocator<MockComponent>&>(allocator).begin());

      Assert::AreSame(*handle3, *it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_CBegin_ReturnsConstFirstAllocatedAndAliveObject)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      EntityAllocatorIterator<const MockComponent> it = allocator.cbegin();
      Assert::AreSame(*handle1, *it);

      // Deallocate an object
      allocator.deallocate(*handle1);
      it = allocator.cbegin();

      Assert::AreSame(*handle2, *it);

      // Kill an object, but keep it allocated
      handle2->die();
      it = allocator.cbegin();

      Assert::AreSame(*handle3, *it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_begin_WithNoAllocatedObjects_Equals_end)
    {
      EntityAllocator<MockComponent> allocator(3);

      Assert::IsTrue(allocator.begin() == allocator.end());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_cbegin_WithNoAllocatedObjects_Equals_cend)
    {
      EntityAllocator<MockComponent> allocator(3);

      Assert::IsTrue(allocator.cbegin() == allocator.cend());
    }

#pragma endregion

#pragma region Foreach Iteration

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ForeachIteration_AllPoolAllocated_IteratesOverAllocatedAliveObjectsOnly)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // 3 alive objects
      {
        int count = 0;
        for (const MockComponent& component : allocator)
        {
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
          count++;
        }

        Assert::AreEqual(2, count);
      }

      // Now kill another object
      {
        handle2->die();

        int count = 0;
        for (const MockComponent& component : allocator)
        {
          count++;
        }

        Assert::AreEqual(1, count);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ForeachIteration_PoolResizeOccurred_IteratesOverAllocatedAliveObjectsOnly)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // 3 alive objects
      {
        int count = 0;
        for (const MockComponent& component : allocator)
        {
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
          count++;
        }

        Assert::AreEqual(2, count);
      }

      // Now kill another object
      {
        handle2->die();

        int count = 0;
        for (const MockComponent& component : allocator)
        {
          count++;
        }

        Assert::AreEqual(1, count);
      }
    }

#pragma endregion

#pragma region Find Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Find_NoResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsTrue(handle1->isAlive());
      Assert::IsTrue(handle2->isAlive());
      Assert::IsTrue(handle3->isAlive());

      // All three objects alive and allocated
      {
        observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(handle1, foundObject);
      }

      // 2 alive objects
      {
        handle1->die();

        observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(handle2, foundObject);
      }

      // 1 alive object
      {
        // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
        allocator.deallocate(*handle2);

        observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(handle3, foundObject);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Find_ResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(2);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsTrue(handle1->isAlive());
      Assert::IsTrue(handle2->isAlive());
      Assert::IsTrue(handle3->isAlive());

      // All three objects alive and allocated
      {
        observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(handle1, foundObject);
      }

      // 2 alive objects
      {
        handle1->die();

        observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(handle2, foundObject);
      }

      // 1 alive object
      {
        // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
        allocator.deallocate(*handle2);

        observer_ptr<MockComponent> foundObject = allocator.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(handle3, foundObject);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Find_NoResizeOccurred_ShouldNotFindAnything)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsNull(allocator.find([](const MockComponent& component) -> bool { return false; }));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Find_ResizeOccurred_ShouldNotFindAnything)
    {
      EntityAllocator<MockComponent> allocator(2);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();
      observer_ptr<MockComponent> handle4 = allocator.allocate();

      Assert::IsNull(allocator.find([](const MockComponent& component) -> bool { return false; }));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Find_NoResizeOccurred_ReturnsFirstMatchingObject)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      handle2->setActive(false);
      handle3->setActive(false);

      AssertCel::IsActive(handle1);
      AssertCel::IsNotActive(handle2);
      AssertCel::IsNotActive(handle3);
      Assert::AreEqual(handle2, allocator.find([](const MockComponent& component) -> bool { return !component.isActive(); }));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Find_ResizeOccurred_ReturnsFirstMatchingObject)
    {
      EntityAllocator<MockComponent> allocator(2);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();
      observer_ptr<MockComponent> handle4 = allocator.allocate();

      handle2->setActive(false);
      handle4->setActive(false);

      AssertCel::IsActive(handle1);
      AssertCel::IsNotActive(handle2);
      AssertCel::IsActive(handle3);
      AssertCel::IsNotActive(handle4);
      Assert::AreEqual(handle2, allocator.find([](const MockComponent& component) -> bool { return !component.isActive(); }));

      Assert::IsNull(allocator.find([](const MockComponent& component) -> bool { return false; }));
    }

#pragma endregion

#pragma region Const Find Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFind_NoResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsTrue(handle1->isAlive());
      Assert::IsTrue(handle2->isAlive());
      Assert::IsTrue(handle3->isAlive());

      // Need const reference to call const functions
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      // All three objects alive and allocated
      {
        observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(static_cast<const MockComponent*>(handle1), foundObject);
      }

      // 2 alive objects
      {
        handle1->die();

        observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(static_cast<const MockComponent*>(handle2), foundObject);
      }

      // 1 alive object
      {
        // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
        allocator.deallocate(*handle2);

        observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(static_cast<const MockComponent*>(handle3), foundObject);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFind_ResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(2);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      AssertCel::IsAlive(handle1);
      AssertCel::IsAlive(handle2);
      AssertCel::IsAlive(handle3);

      // Need a const reference to call const functions
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      // All three objects alive and allocated
      {
        observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(static_cast<const MockComponent*>(handle1), foundObject);
      }

      // 2 alive objects
      {
        handle1->die();

        AssertCel::IsNotAlive(handle1);

        observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(static_cast<const MockComponent*>(handle2), foundObject);
      }

      // 1 alive object
      {
        // Have to get the allocator to deallocate, since this component is not from the static MockComponent allocator
        allocator.deallocate(*handle2);

        observer_ptr<const MockComponent> foundObject = allocatorRef.find([](const MockComponent& component) -> bool { return true; });

        Assert::IsNotNull(foundObject);
        Assert::AreEqual(static_cast<const MockComponent*>(handle3), foundObject);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFind_NoResizeOccurred_ShouldNotFindAnything)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // Need a const reference to call const functions
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      Assert::IsNull(allocatorRef.find([](const MockComponent& component) -> bool { return false; }));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFind_ResizeOccurred_ShouldNotFindAnything)
    {
      EntityAllocator<MockComponent> allocator(2);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();
      observer_ptr<MockComponent> handle4 = allocator.allocate();

      // Need a const reference to call const functions
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      Assert::IsNull(allocatorRef.find([](const MockComponent& component) -> bool { return false; }));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFind_NoResizeOccurred_ReturnsFirstMatchingObject)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      handle2->setActive(false);
      handle3->setActive(false);

      // Need a const reference to call const functions
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      AssertCel::IsActive(handle1);
      AssertCel::IsNotActive(handle2);
      AssertCel::IsNotActive(handle3);
      Assert::AreEqual(static_cast<const MockComponent*>(handle2), allocatorRef.find([](const MockComponent& component) -> bool { return !component.isActive(); }));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFind_ResizeOccurred_ReturnsFirstMatchingObject)
    {
      EntityAllocator<MockComponent> allocator(2);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();
      observer_ptr<MockComponent> handle4 = allocator.allocate();

      handle2->setActive(false);
      handle4->setActive(false);

      // Need a const reference to call const functions
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      AssertCel::IsActive(handle1);
      AssertCel::IsNotActive(handle2);
      AssertCel::IsActive(handle3);
      AssertCel::IsNotActive(handle4);
      Assert::AreEqual(static_cast<const MockComponent*>(handle2), allocatorRef.find([](const MockComponent& component) -> bool { return !component.isActive(); }));
    }

#pragma endregion

#pragma region Find All Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_FindAll_NoResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();
      
      // Two allocated and alive objects
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

      // Now kill the other
      {
        handle2->die();

        std::vector<std::reference_wrapper<MockComponent>> foundObjects;
        allocator.findAll([](const MockComponent&) { return true; }, foundObjects);
        
        Assert::AreEqual((size_t)1, foundObjects.size());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_FindAll_ResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // Two allocated and alive objects
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

      // Now kill the other
      {
        handle2->die();

        std::vector<std::reference_wrapper<MockComponent>> foundObjects;
        allocator.findAll([](const MockComponent&) { return true; }, foundObjects);
        
        Assert::AreEqual((size_t)1, foundObjects.size());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_FindAll_NoResizeOccurred_ShouldNotFindAnything)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent& c) { return false; }, foundObjects);

      Assert::AreEqual((size_t)0, foundObjects.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_FindAll_ResizeOccurred_ShouldNotFindAnything)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([](const MockComponent& c) { return false; }, foundObjects);

      Assert::AreEqual((size_t)0, foundObjects.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_FindAll_OnlyPoolAllocatorObjects_ShouldFindObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

      Assert::AreEqual((size_t)1, foundObjects.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_FindAll_PoolAndOverflowAllocatorObjects_ShouldFindObjects)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      std::vector<std::reference_wrapper<MockComponent>> foundObjects;
      allocator.findAll([handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

      Assert::AreEqual((size_t)1, foundObjects.size());
    }

#pragma endregion

#pragma region Const Find All Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFindAll_NoResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // Used so we can force the const version of find
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      // Two allocated and alive objects
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

      // Now kill the other
      {
        handle2->die();

        std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
        allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
        Assert::AreEqual((size_t)1, foundObjects.size());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFindAll_ResizeOccurred_OnlySearchesThroughAllocatedAndAliveObjects)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // Used so we can force the const version of find
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      // Two allocated and alive objects
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

      // Now kill the other
      {
        handle2->die();

        std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
        allocatorRef.findAll([](const MockComponent&) { return true; }, foundObjects);
        
        Assert::AreEqual((size_t)1, foundObjects.size());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFindAll_ShouldNotFindAnything)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // Used so we can force the const version of find
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([](const MockComponent& c) { return false; }, foundObjects);

      Assert::AreEqual((size_t)0, foundObjects.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFindAll_NoResizeOccurred_ShouldFindObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // Used so we can force the const version of find
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

      Assert::AreEqual((size_t)1, foundObjects.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_ConstFindAll_ResizeOccurred_ShouldFindObjects)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();
      observer_ptr<MockComponent> handle3 = allocator.allocate();

      // Used so we can force the const version of find
      const EntityAllocator<MockComponent>& allocatorRef = allocator;

      std::vector<std::reference_wrapper<const MockComponent>> foundObjects;
      allocatorRef.findAll([handle1](const MockComponent& c) { return &c == handle1; }, foundObjects);

      Assert::AreEqual((size_t)1, foundObjects.size());
    }
    
#pragma endregion

#pragma region Contains Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Contains_InputtingObjectFromAllocator_ReturnsTrue)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> component = allocator.allocate();

      Assert::IsTrue(allocator.contains(*component));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Contains_InputtingObjectNotFromEntityAllocator_ReturnsFalse)
    {
      EntityAllocator<MockComponent> allocator(3);
      MockComponent component;

      Assert::IsFalse(allocator.contains(component));
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_HandleInput_NoResizeOccurred_CallsHandleInputOnAllAllocatedObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();

      allocator.handleInput();

      Assert::IsTrue(handle1->handleInputCalled());
      Assert::IsTrue(handle2->handleInputCalled());

      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsFalse(handle3->handleInputCalled());

      allocator.handleInput();

      Assert::IsTrue(handle3->handleInputCalled());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_HandleInput_ResizeOccurred_CallsHandleInputOnAllAllocatedObjects)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();

      allocator.handleInput();

      Assert::IsTrue(handle1->handleInputCalled());
      Assert::IsTrue(handle2->handleInputCalled());

      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsFalse(handle3->handleInputCalled());

      allocator.handleInput();

      Assert::IsTrue(handle3->handleInputCalled());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Update_NoResizeOccurred_CallsUpdateOnAllAllocatedObjects)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();

      allocator.update(0);

      Assert::IsTrue(handle1->updateCalled());
      Assert::IsTrue(handle2->updateCalled());

      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsFalse(handle3->updateCalled());

      allocator.update(0);

      Assert::IsTrue(handle3->updateCalled());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Update_ResizeOccurred_CallsUpdateOnAllAllocatedObjects)
    {
      EntityAllocator<MockComponent> allocator(1);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();

      allocator.update(0);

      Assert::IsTrue(handle1->updateCalled());
      Assert::IsTrue(handle2->updateCalled());

      observer_ptr<MockComponent> handle3 = allocator.allocate();

      Assert::IsFalse(handle3->updateCalled());

      allocator.update(0);

      Assert::IsTrue(handle3->updateCalled());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Update_DeallocatesAllOverflowAllocatedDeadObjects)
    {
      EntityAllocator<MockComponent> allocator(1);
      allocator.allocate();
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      observer_ptr<MockComponent> handle2 = allocator.allocate();

      Assert::AreEqual((size_t)3, allocator.size());

      handle1->die();
      handle2->die();

      Assert::IsFalse(handle1->isAlive());
      Assert::IsFalse(handle2->isAlive());

      allocator.update(0);

      // Cannot directly test allocated handles as they will have been deallocated by shared ptr
      Assert::AreEqual((size_t)1, allocator.size());
    }

#pragma endregion

#pragma region Die Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Die_CallsDieOnAllPoolAllocatedObjects_AndDeallocatesThem)
    {
      EntityAllocator<MockComponent> allocator(3);
      observer_ptr<MockComponent> handle1 = allocator.allocate();
      const MockComponent* ptr1 = handle1;

      observer_ptr<MockComponent> handle2 = allocator.allocate();
      const MockComponent* ptr2 = handle2;

      allocator.die();

      Assert::AreEqual((size_t)0, allocator.size());
      Assert::IsFalse(ptr1->isAlive());
      Assert::IsNull(ptr1->getGameObject());
      Assert::IsFalse(ptr2->isAlive());
      Assert::IsNull(ptr2->getGameObject());

      observer_ptr<MockComponent> handle3 = allocator.allocate();
      const MockComponent* ptr3 = handle3;

      Assert::IsTrue(handle3->isAlive());

      allocator.die();

      Assert::AreEqual((size_t)0, allocator.size());
      Assert::IsFalse(ptr3->isAlive());
      Assert::IsNull(ptr3->getGameObject());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(EntityAllocator_Die_ClearsOverflowVector)
    {
      EntityAllocator<MockComponent> allocator(1);
      allocator.allocate();
      allocator.allocate();
      allocator.allocate();
      
      Assert::AreEqual((size_t)3, allocator.size());

      allocator.die();

      // Since the objects are deallocated, we will not be able to access the overflow elements

      Assert::AreEqual((size_t)0, allocator.size());
    }

#pragma endregion

  };
}