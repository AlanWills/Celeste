#include "Animation/Animators/ChangeScaleAnimator.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;
using namespace Celeste::Animators;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestChangeScaleAnimator)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<ChangeScaleAnimator>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(ChangeScaleAnimator::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<ChangeScaleAnimator*>(component));
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Constructor_SetsAllValuesToDefault)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);

    Assert::AreEqual(0.0f, animator.getTime());
    Assert::AreEqual(glm::vec3(1), animator.getTargetScale());
  }

#pragma endregion

#pragma region Set Target Scale Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_SetTargetScale_SetsTargetScaleToInputtedValue)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);

    Assert::AreSame(gameObject, animator.getGameObject());
    Assert::AreEqual(glm::vec3(1), animator.getTargetScale());

    animator.setTargetScale(glm::vec3(100, 200, 300));

    Assert::AreEqual(glm::vec3(100, 200, 300), animator.getTargetScale());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_TimeIsZero_SetsGameObjectToTargetScale)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0);
    animator.setTargetScale(glm::vec3(100, 200, 300));

    Assert::AreEqual(glm::vec3(1), gameObject.getTransform()->getScale());

    animator.update(0);

    Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_TimeNonZero_LerpsBetweenStartAndTarget_UsingElapsedTime)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0.5f);
    animator.setTargetScale(glm::vec3(100, 200, 300));

    Assert::AreEqual(glm::vec3(1), gameObject.getTransform()->getScale());

    animator.update(0.25f);

    Assert::AreEqual(glm::vec3(50.5f, 100.5f, 150.5f), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_ElapsedTimeEqualToTime_SetsGameObjectToScale)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0.5f);
    animator.setTargetScale(glm::vec3(100, 200, 300));

    Assert::AreEqual(glm::vec3(1), gameObject.getTransform()->getScale());

    animator.update(0.5f);

    Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_ElapsedTimeEqualToTime_DeactivatesScript)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0.5f);

    AssertCel::IsActive(animator);

    animator.update(0.5f);

    AssertCel::IsNotActive(animator);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_ElapsedTimeGreaterThanTime_SetsGameObjectToTargetScale)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0.5f);
    animator.setTargetScale(glm::vec3(100, 200, 300));

    Assert::AreEqual(glm::vec3(1), gameObject.getTransform()->getScale());

    animator.update(1);

    Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_ElapsedTimeGreaterThanTime_DeactivatesScript)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0.5f);

    AssertCel::IsActive(animator);

    animator.update(1);

    AssertCel::IsNotActive(animator);
  }

#pragma endregion

  };
}