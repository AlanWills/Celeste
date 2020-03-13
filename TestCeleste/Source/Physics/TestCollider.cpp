#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Physics/MockCollider.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestCollider)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Collider_DefaultConstructor_SetsTransformToGameObjectTransform)
  {
    GameObject gameObject;
    MockCollider collider(gameObject);

    Assert::AreEqual(gameObject.getTransform(), collider.getTransform());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Collider_DefaultConstructor_SetsIsColliderTypeTo_kCollider)
  {
    GameObject gameObject;
    MockCollider collider(gameObject);

    Assert::IsTrue(collider.getColliderType() == Physics::ColliderType::kCollider);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Collider_DefaultConstructor_SetsIsHitByRayToFalse)
  {
    GameObject gameObject;
    MockCollider collider(gameObject);

    Assert::IsFalse(collider.isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Collider_DefaultConstructor_SetsOffsetToZero)
  {
    GameObject gameObject;
    MockCollider collider(gameObject);

    Assert::AreEqual(glm::vec2(), collider.getOffset());
  }

#pragma endregion

#pragma region Set Offset Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Collider_SetOffset_CallsOnSetOffset)
  {
    GameObject gameObject;
    MockCollider collider(gameObject);
    collider.setOffset(100, 200);

    Assert::IsTrue(collider.isOnSetOffsetCalled());

    collider.reset();

    Assert::IsFalse(collider.isOnSetOffsetCalled());

    collider.setOffset(glm::vec2(200, 100));

    Assert::IsTrue(collider.isOnSetOffsetCalled());
  }

#pragma endregion

  };
}