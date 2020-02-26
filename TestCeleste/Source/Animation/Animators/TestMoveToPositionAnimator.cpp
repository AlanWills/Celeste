#include "Animation/Animators/MoveToPositionAnimator.h"
#include "UtilityHeaders/UnitTestHeaders.h"
#include "Registries/ComponentRegistry.h"
#include "Mocks/Physics/MockRigidBody2D.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Animators;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestMoveToPositionAnimator)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MoveToPositionAnimator_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<MoveToPositionAnimator>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MoveToPositionAnimator_IsAllocatableFromComponentRegistry)
  {
    GAMEOBJECT(gameObject);

    AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(MoveToPositionAnimator::type_name(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<MoveToPositionAnimator*>(component.get()));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Constructor_SetsAllValuesToDefault)
    {
      MoveToPositionAnimator animator;

      Assert::AreEqual(0.0f, animator.getTime());
      Assert::AreEqual(glm::vec3(), animator.getTargetPosition());
    }

#pragma endregion

#pragma region Set Target Position Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_SetTargetPosition_NullGameObject_DoesNotThrow)
    {
      MoveToPositionAnimator animator;

      Assert::IsNull(animator.getGameObject());

      animator.setTargetPosition(glm::vec3(100, 200, 300));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_SetTargetPosition_SetsTargetPositionToInputtedValue)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<MoveToPositionAnimator> animator = gameObject.addComponent<MoveToPositionAnimator>();

      Assert::IsTrue(&gameObject == animator->getGameObject());
      Assert::AreEqual(glm::vec3(), animator->getTargetPosition());

      animator->setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(100, 200, 300), animator->getTargetPosition());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_NullGameObject_DoesNotThrow)
    {
      MoveToPositionAnimator animator;

      Assert::IsNull(animator.getGameObject());

      animator.update(1);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_TimeIsZero_SetsGameObjectToTargetPosition)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<MoveToPositionAnimator> animator = gameObject.addComponent<MoveToPositionAnimator>();
      animator->setTime(0);
      animator->setTargetPosition(glm::vec3(100, 200, 300));
      
      Assert::AreEqual(glm::vec3(), gameObject.getTransform()->getTranslation());

      animator->update(0);

      Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_TimeNonZero_LerpsBetweenStartAndTarget_UsingElapsedTime)
    {
      GAMEOBJECT(gameObject);
      gameObject.getTransform()->setTranslation(1, 1, 1);
      AutoDeallocator<MoveToPositionAnimator> animator = gameObject.addComponent<MoveToPositionAnimator>();
      animator->setTime(0.5f);
      animator->setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(1), gameObject.getTransform()->getTranslation());

      animator->update(0.25f);

      Assert::AreEqual(glm::vec3(50.5f, 100.5f, 150.5f), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeEqualToTime_SetsGameObjectToTargetPosition)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<MoveToPositionAnimator> animator = gameObject.addComponent<MoveToPositionAnimator>();
      animator->setTime(0.5f);
      animator->setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(), gameObject.getTransform()->getTranslation());

      animator->update(0.5f);

      Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeEqualToTime_DeactivatesScript)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<MoveToPositionAnimator> animator = gameObject.addComponent<MoveToPositionAnimator>();
      animator->setTime(0.5f);

      AssertCel::IsActive(animator.get());

      animator->update(0.5f);

      AssertCel::IsNotActive(animator.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeGreaterThanTime_SetsGameObjectToTargetPosition)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<MoveToPositionAnimator> animator = gameObject.addComponent<MoveToPositionAnimator>();
      animator->setTime(0.5f);
      animator->setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(), gameObject.getTransform()->getTranslation());

      animator->update(1);

      Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeGreaterThanTime_DeactivatesScript)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<MoveToPositionAnimator> animator = gameObject.addComponent<MoveToPositionAnimator>();
      animator->setTime(0.5f);

      AssertCel::IsActive(animator.get());

      animator->update(1);

      AssertCel::IsNotActive(animator.get());
    }

#pragma endregion

#pragma region Die Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Die_ResetsValuesToDefault)
    {
      MoveToPositionAnimator animator;
      animator.setTime(0.5f);
      animator.setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(0.5f, animator.getTime());
      Assert::AreEqual(glm::vec3(100, 200, 300), animator.getTargetPosition());

      animator.die();

      Assert::AreEqual(0.0f, animator.getTime());
      Assert::AreEqual(glm::vec3(), animator.getTargetPosition());
    }

#pragma endregion
  };
}