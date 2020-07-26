#include "Animation/Animators/ChangeScaleAnimator.h"
#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "CelesteTestUtils/Assert/AssertCel.h"
#include "Time/TimeUtils.h"
#include "Time/Clock.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::Animators;
using namespace Celeste::Time;


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

    getClock().update(0);

    Assert::AreEqual(0.0f, getElapsedDeltaTime());

    animator.update();

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

    getClock().update(0.25f);

    AssertExt::AreAlmostEqual(0.25f, getElapsedDeltaTime());

    animator.update();

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

    getClock().update(0.5f);

    Assert::AreEqual(0.5f, getElapsedDeltaTime());

    animator.update();

    Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_ElapsedTimeEqualToTime_DeactivatesScript)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0.5f);

    AssertCel::IsActive(animator);

    getClock().update(0.5f);

    Assert::AreEqual(0.5f, getElapsedDeltaTime());

    animator.update();

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

    getClock().update(1);

    Assert::AreEqual(1.0f, getElapsedDeltaTime());

    animator.update();

    Assert::AreEqual(glm::vec3(100, 200, 300), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChangeScaleAnimator_Update_ElapsedTimeGreaterThanTime_DeactivatesScript)
  {
    GameObject gameObject;
    ChangeScaleAnimator animator(gameObject);
    animator.setTime(0.5f);

    AssertCel::IsActive(animator);

    getClock().update(1);

    Assert::AreEqual(1.0f, getElapsedDeltaTime());

    animator.update();

    AssertCel::IsNotActive(animator);
  }

#pragma endregion

  };
}