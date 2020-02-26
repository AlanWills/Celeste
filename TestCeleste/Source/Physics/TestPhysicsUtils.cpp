#include "UtilityHeaders/UnitTestHeaders.h"

#include "Physics/PhysicsUtils.h"
#include "Game/Game.h"
#include "Physics/RectangleCollider.h"
#include "Physics/RigidBody2D.h"
#include "Utils/ObjectUtils.h"

using namespace Celeste;
using namespace Celeste::Physics;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestPhysicsUtils)

  //------------------------------------------------------------------------------------------------
  void TestPhysicsUtils::testInitialize()
  {
    Game::getPhysicsManager().clearSimulatedBodies();
  }

#pragma region Get Physics Manager Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_GetPhysicsManager_EqualsGamePhysicsManager)
  {
    Assert::IsTrue(&getPhysicsManager() == &Game::getPhysicsManager());
  }

#pragma endregion

#pragma region Add Simulated Body Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_AddSimulatedBody_Collider_AddsSimulatedBodyToPhysicsManager)
  {
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(RectangleCollider());

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_AddSimulatedBody_RigidBody_AddsSimulatedBodyToPhysicsManager)
  {
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(RigidBody2D());

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_AddSimulatedBody_ColliderAndRigidBody_AddsSimulatedBodyToPhysicsManager)
  {
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(RectangleCollider(), RigidBody2D());

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
  }

#pragma endregion

#pragma region Clear Simulated Bodies Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsUtils_ClearSimulatedBodies_RemovesAllSimulatedBodies_FromPhysicsManager)
  {
    RectangleCollider collider;

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    addSimulatedBody(collider, RigidBody2D());

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());

    clearSimulatedBodies();

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());
  }

#pragma endregion

  };
}