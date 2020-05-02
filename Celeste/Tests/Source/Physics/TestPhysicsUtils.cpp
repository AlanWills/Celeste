#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Game/Game.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsUtils.h"
#include "Physics/RectangleCollider.h"
#include "Physics/RigidBody2D.h"

using namespace Celeste;
using namespace Celeste::Physics;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestPhysicsUtils)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    Game::current().getSystem<Physics::PhysicsManager>()->clearSimulatedBodies();
  }

#pragma region Get Physics Manager Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_GetPhysicsManager_EqualsGamePhysicsManager)
  {
    Assert::IsTrue(&getPhysicsManager() == Game::current().getSystem<Physics::PhysicsManager>());
  }

#pragma endregion

#pragma region Add Simulated Body Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_AddSimulatedBody_Collider_AddsSimulatedBodyToPhysicsManager)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(collider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_AddSimulatedBody_RigidBody_AddsSimulatedBodyToPhysicsManager)
  {
    GameObject gameObject;
    RigidBody2D rigidBody2D(gameObject);

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(rigidBody2D);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_AddSimulatedBody_ColliderAndRigidBody_AddsSimulatedBodyToPhysicsManager)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);
    RigidBody2D rigidBody2D(gameObject);

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(collider, rigidBody2D);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
  }

#pragma endregion

#pragma region Clear Simulated Bodies Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_ClearSimulatedBodies_RemovesAllSimulatedBodies_FromPhysicsManager)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);
    RigidBody2D rigidBody2D(gameObject);

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(collider, rigidBody2D);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());

    clearSimulatedBodies();

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());
  }

#pragma endregion

  };
}