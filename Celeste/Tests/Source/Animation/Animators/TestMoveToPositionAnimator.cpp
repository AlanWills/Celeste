#include "Animation/Animators/MoveToPositionAnimator.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "Physics/RigidBody2D.h"
#include "TestUtils/Assert/AssertCel.h"

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
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(MoveToPositionAnimator::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<MoveToPositionAnimator*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Constructor_SetsAllValuesToDefault)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);

      Assert::AreEqual(0.0f, animator.getTime());
      Assert::AreEqual(glm::vec3(), animator.getTargetPosition());
    }

#pragma endregion

#pragma region Set Target Position Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_SetTargetPosition_SetsTargetPositionToInputtedValue)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);

      Assert::IsTrue(&gameObject == animator.getGameObject());
      Assert::AreEqual(glm::vec3(), animator.getTargetPosition());

      animator.setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(100, 200, 300), animator.getTargetPosition());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_TimeIsZero_SetsGameObjectToTargetPosition)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);
      animator.setTime(0);
      animator.setTargetPosition(glm::vec3(100, 200, 300));
      
      Assert::AreEqual(glm::vec3(), gameObject.getTransform()->getTranslation());

      animator.update(0);

      Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_TimeNonZero_LerpsBetweenStartAndTarget_UsingElapsedTime)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);
      gameObject.getTransform()->setTranslation(1, 1, 1);
      animator.setTime(0.5f);
      animator.setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(1), gameObject.getTransform()->getTranslation());

      animator.update(0.25f);

      Assert::AreEqual(glm::vec3(50.5f, 100.5f, 150.5f), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeEqualToTime_SetsGameObjectToTargetPosition)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);
      animator.setTime(0.5f);
      animator.setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(), gameObject.getTransform()->getTranslation());

      animator.update(0.5f);

      Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeEqualToTime_DeactivatesScript)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);
      animator.setTime(0.5f);

      AssertCel::IsActive(animator);

      animator.update(0.5f);

      AssertCel::IsNotActive(animator);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeGreaterThanTime_SetsGameObjectToTargetPosition)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);
      animator.setTime(0.5f);
      animator.setTargetPosition(glm::vec3(100, 200, 300));

      Assert::AreEqual(glm::vec3(), gameObject.getTransform()->getTranslation());

      animator.update(1);

      Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MoveToPositionAnimator_Update_ElapsedTimeGreaterThanTime_DeactivatesScript)
    {
      GameObject gameObject;
      MoveToPositionAnimator animator(gameObject);
      animator.setTime(0.5f);

      AssertCel::IsActive(animator);

      animator.update(1);

      AssertCel::IsNotActive(animator);
    }

#pragma endregion

  };
}