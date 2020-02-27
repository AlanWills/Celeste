#include "UtilityHeaders/UnitTestHeaders.h"

#include "Memory/Iterators/GameObjectIterator.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestGameObjectIterator)

#pragma region Deference Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_Dereference_ReturnsGameObjectHandleOfCurrentTransform)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      Assert::AreEqual(&gameObject1, *GameObjectIterator(transforms.begin()));
      Assert::AreEqual(&gameObject2, *GameObjectIterator(transforms.begin() + 1));
    }

#pragma endregion

#pragma region ++ Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_Increment_IncrementsUnderlyingVectorIterator)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      GameObjectIterator it(transforms.begin());

      Assert::AreEqual(&gameObject1, *it);

      ++it;

      Assert::AreEqual(&gameObject2, *it);
    }

#pragma endregion

#pragma region Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_EqualityOperator_ShouldReturnTrue)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      Assert::IsTrue(GameObjectIterator(transforms.begin()) == GameObjectIterator(transforms.begin()));
      Assert::IsTrue(GameObjectIterator(transforms.begin() + 1) == GameObjectIterator(transforms.begin() + 1));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_EqualityOperator_ShouldReturnFalse)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      Assert::IsFalse(GameObjectIterator(transforms.begin()) == GameObjectIterator(transforms.begin() + 1));
      Assert::IsFalse(GameObjectIterator(transforms.begin() + 1) == GameObjectIterator(transforms.begin()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_EqualityOperator_Reflexivity_ShouldReturnTrue)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      GameObjectIterator it(transforms.begin());

      Assert::IsTrue(it == it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_EqualityOperator_IsSymmetric)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      GameObjectIterator it(transforms.begin());
      GameObjectIterator it2(transforms.begin());

      Assert::IsTrue(it == it2);
      Assert::IsTrue(it2 == it);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_EqualityOperator_IsTransitive)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      GameObjectIterator it(transforms.begin());
      GameObjectIterator it2(transforms.begin());
      GameObjectIterator it3(transforms.begin());

      Assert::IsTrue(it == it2);
      Assert::IsTrue(it2 == it3);
      Assert::IsTrue(it3 == it);
    }

#pragma endregion

#pragma region Inequality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_InequalityOperator_ShouldReturnTrue)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      Assert::IsTrue(GameObjectIterator(transforms.begin()) != GameObjectIterator(transforms.begin() + 1));
      Assert::IsTrue(GameObjectIterator(transforms.begin() + 1) != GameObjectIterator(transforms.begin()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_InequalityOperator_ShouldReturnFalse)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      Assert::IsFalse(GameObjectIterator(transforms.begin()) != GameObjectIterator(transforms.begin()));
      Assert::IsFalse(GameObjectIterator(transforms.begin() + 1) != GameObjectIterator(transforms.begin() + 1));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_InequalityOperator_Reflexivity_ShouldReturnFalse)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      GameObjectIterator it(transforms.begin());
      GameObjectIterator it2(transforms.begin());

      Assert::IsFalse(it != it);
      Assert::IsFalse(it2 != it2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObjectIterator_InequalityOperator_IsSymmetric)
    {
      GameObject gameObject1;
      GameObject gameObject2;
      AutoDeallocator<Transform> transform1 = Transform::allocate(gameObject1);
      AutoDeallocator<Transform> transform2 = Transform::allocate(gameObject2);

      std::vector<Transform*> transforms
      {
        transform1.get(),
        transform2.get()
      };

      GameObjectIterator it(transforms.begin());
      GameObjectIterator it2(transforms.begin());

      Assert::IsFalse(it != it2);
      Assert::IsFalse(it2 != it);
    }

    // Inequality operator cannot be transitive

#pragma endregion

  };
}