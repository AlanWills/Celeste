#include "UtilityHeaders/UnitTestHeaders.h"

#include "Physics/PhysicsManager.h"
#include "Game/Game.h"
#include "Physics/RectangleCollider.h"
#include "Physics/RigidBody2D.h"
#include "Mocks/Physics/CollisionDetector.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Physics;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestPhysicsManager)

  //------------------------------------------------------------------------------------------------
  void TestPhysicsManager::testInitialize()
  {
    Game::getPhysicsManager().clearSimulatedBodies();
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Constructor_HasNoSimulatedBodies)
  {
    PhysicsManager manager;

    Assert::AreEqual((size_t)0, manager.getSimulatedBodiesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Constructor_SetsGravityScale_ToDefaultEarthGravity)
  {
    PhysicsManager manager;

    Assert::AreEqual(9.81f, manager.getGravityScale());
  }

#pragma endregion

#pragma region Set Gravity Scale Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_SetsGravityScale_ToInputtedValue)
  {
    PhysicsManager manager;
    manager.setGravityScale(100.01f);

    Assert::AreEqual(100.01f, manager.getGravityScale());

    manager.setGravityScale(-6);

    Assert::AreEqual(-6.0f, manager.getGravityScale());
  }

#pragma endregion

#pragma region Add Simulated Body Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_AddSimulatedBody_Collider_AddsSimulatedBodyToPhysicsManager)
  {
    PhysicsManager manager;

    Assert::AreEqual((size_t)0, manager.getSimulatedBodiesSize());

    GameObject gameObject;
    RectangleCollider rectangleCollider(gameObject);
    manager.addSimulatedBody(rectangleCollider);

    Assert::AreEqual((size_t)1, manager.getSimulatedBodiesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_AddSimulatedBody_RigidBody_AddsSimulatedBodyToPhysicsManager)
  {
    PhysicsManager manager;

    Assert::AreEqual((size_t)0, manager.getSimulatedBodiesSize());
    
    GameObject gameObject;
    RigidBody2D rigidBody2D(gameObject);
    manager.addSimulatedBody(rigidBody2D);

    Assert::AreEqual((size_t)1, manager.getSimulatedBodiesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_AddSimulatedBody_ColliderAndRigidBody_AddsSimulatedBodyToPhysicsManager)
  {
    PhysicsManager manager;

    Assert::AreEqual((size_t)0, manager.getSimulatedBodiesSize());

    GameObject gameObject;
    RectangleCollider rectangleCollider(gameObject);
    RigidBody2D rigidBody2D(gameObject);
    manager.addSimulatedBody(rectangleCollider, rigidBody2D);

    Assert::AreEqual((size_t)1, manager.getSimulatedBodiesSize());
  }

#pragma endregion

#pragma region Clear Simulated Bodies Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_ClearSimulatedBodies_RemovesAllSimulatedBodies_FromPhysicsManager)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);
    PhysicsManager manager;

    Assert::AreEqual((size_t)0, manager.getSimulatedBodiesSize());

    manager.addSimulatedBody(collider);

    Assert::AreEqual((size_t)1, manager.getSimulatedBodiesSize());

    manager.clearSimulatedBodies();

    Assert::AreEqual((size_t)0, manager.getSimulatedBodiesSize());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyWithInactiveRigidBody_DoesNotSimulateGravity)
  {
    GameObject gameObject;
    RigidBody2D rigidBody(gameObject);
    rigidBody.setActive(false);

    AssertCel::IsNotActive(rigidBody);
    Assert::AreEqual(0.0f, rigidBody.getLinearVelocity().y);

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(rigidBody);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().update(0.01f);

    Assert::AreEqual(0.0f, rigidBody.getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyWithActiveRigidBody_UpdatesLinearVelocityToSimulateGravity)
  {
    GameObject gameObject;
    RigidBody2D rigidBody(gameObject);

    AssertCel::IsActive(rigidBody);
    Assert::AreEqual(0.0f, rigidBody.getLinearVelocity().y);

    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(rigidBody);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().update(0.01f);

    Assert::AreNotEqual(0.0f, rigidBody.getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyWithInactiveCollider_DoesNotPerformCollisions)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setActive(false);
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    
    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    AssertCel::IsNotActive(rectangleCollider);
    Assert::AreEqual(glm::vec2(100, 200), rectangleCollider->getDimensions());
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsFalse(detector->collisionCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyDoesNotPerformCollisionsWithInactiveColliders)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    otherCollider->setActive(false);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    AssertCel::IsActive(rectangleCollider);
    AssertCel::IsNotActive(otherCollider);
    Assert::AreEqual(glm::vec2(100, 200), rectangleCollider->getDimensions());
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsFalse(detector->collisionCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyDoesNotPerformCollisionsWithItself)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    Assert::IsTrue(rectangleCollider->intersects(*rectangleCollider));
    AssertCel::IsActive(rectangleCollider);
    Assert::AreEqual(glm::vec2(100, 200), rectangleCollider->getDimensions());
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsFalse(detector->collisionCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithTriggerForFirstTime_CallsTriggerEnter)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);
    
    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    otherCollider->setColliderType(Physics::ColliderType::kTrigger);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->triggerEnterCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->triggerEnterCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithTriggerNotForFirstTime_DoesNotCallTriggerEnter)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    otherCollider->setColliderType(Physics::ColliderType::kTrigger);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->triggerEnterCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->triggerEnterCalled());

    detector->reset();

    Assert::IsFalse(detector->triggerEnterCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsFalse(detector->triggerEnterCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithTrigger_CallsTrigger)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    otherCollider->setColliderType(Physics::ColliderType::kTrigger);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->triggerCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->triggerCalled());

    detector->reset();

    Assert::IsFalse(detector->triggerCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->triggerCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithMultipleTriggers_CallsTriggerForEveryTriggerItCollidesWith)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    otherCollider->setColliderType(Physics::ColliderType::kTrigger);

    GameObject other2;
    observer_ptr<RectangleCollider> otherCollider2 = other2.addComponent<RectangleCollider>();
    otherCollider2->setDimensions(50, 50);
    otherCollider2->setColliderType(Physics::ColliderType::kTrigger);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(rectangleCollider->intersects(*otherCollider2));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::IsTrue(otherCollider2->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->triggerCalled());
    Assert::AreEqual((size_t)0, detector->triggerCount());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->triggerCalled());
    Assert::AreEqual((size_t)2, detector->triggerCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithCollider_NoRigidBody_DoesNotThrow)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionEnterCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->collisionEnterCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithColliderForFirstTime_CallsCollisionEnter)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionEnterCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->collisionEnterCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithColliderNotForFirstTime_DoesNotCallCollisionEnter)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionEnterCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->collisionEnterCalled());

    detector->reset();

    Assert::IsFalse(detector->collisionEnterCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsFalse(detector->collisionEnterCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithCollider_CallsCollision)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->collisionCalled());

    detector->reset();

    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->collisionCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithMultipleColliders_CallsCollisionForEveryColliderItCollidesWith)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    GameObject other2;
    observer_ptr<RectangleCollider> otherCollider2 = other2.addComponent<RectangleCollider>();
    otherCollider2->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(rectangleCollider->intersects(*otherCollider2));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    Assert::AreEqual(static_cast<size_t>(2), detector->collisionCount());

    detector->reset();

    Assert::AreEqual(static_cast<size_t>(0), detector->collisionCount());

    getPhysicsManager().update(0.1f);

    Assert::AreEqual(static_cast<size_t>(2), detector->collisionCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithCollider_BodyIsTrigger_DoesNotAffectRigidBody)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    rigidBody->setLinearVelocity(10, 20);
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);
    rectangleCollider->setColliderType(Physics::ColliderType::kTrigger);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(rectangleCollider->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::AreEqual(glm::vec2(10, 20), rigidBody->getLinearVelocity());
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider, *rigidBody);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    // Do  not apply gravity
    getPhysicsManager().update(0);

    Assert::IsTrue(detector->collisionCalled());
    Assert::AreEqual(glm::vec2(10, 20), rigidBody->getLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithCollider_BodyIsCollider_Left_SetsLeftVelocityToZero)
  {
    GameObject gameObject;
    gameObject.getTransform()->setTranslation(50, 0);
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    rigidBody->setLinearVelocity(-10, 0);
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(rectangleCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual(-10.0f, rigidBody->getLinearVelocity().x);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider, *rigidBody);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    // Do  not apply gravity
    getPhysicsManager().update(0);

    Assert::IsTrue(detector->collisionCalled());
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithCollider_BodyIsCollider_Up_SetsUpVelocityToZero)
  {
    GameObject gameObject;
    gameObject.getTransform()->setTranslation(0, -50);
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    rigidBody->setLinearVelocity(0, 10);
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(rectangleCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual(10.0f, rigidBody->getLinearVelocity().y);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider, *rigidBody);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    // Do  not apply gravity
    getPhysicsManager().update(0);

    Assert::IsTrue(detector->collisionCalled());
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithCollider_BodyIsCollider_Right_SetsRightVelocityToZero)
  {
    GameObject gameObject;
    gameObject.getTransform()->setTranslation(-50, 0);
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    rigidBody->setLinearVelocity(10, 0);
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(rectangleCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual(10.0f, rigidBody->getLinearVelocity().x);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider, *rigidBody);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    // Do  not apply gravity
    getPhysicsManager().update(0);

    Assert::IsTrue(detector->collisionCalled());
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyCollidesWithCollider_BodyIsCollider_Down_SetsDownVelocityToZero)
  {
    GameObject gameObject;
    gameObject.getTransform()->setTranslation(0, 50);
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    rigidBody->setLinearVelocity(0, -10);
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(rectangleCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual(-10.0f, rigidBody->getLinearVelocity().y);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider, *rigidBody);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    // Do  not apply gravity
    getPhysicsManager().update(0);

    Assert::IsTrue(detector->collisionCalled());
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyDoesNotCollideWithTrigger_ButDidLastFrame_CallsTriggerExit)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    otherCollider->setColliderType(Physics::ColliderType::kTrigger);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->triggerCalled());

    getPhysicsManager().update(0.1f);

    // Check collision occurred
    Assert::IsTrue(detector->triggerCalled());

    detector->reset();

    Assert::IsFalse(detector->triggerExitCalled());

    // Move collider and see that a collision will now not occur
    gameObject.getTransform()->setTranslation(500, 500);
    rectangleCollider->sync(); // Sync with gameobject's position

    Assert::IsFalse(rectangleCollider->intersects(*otherCollider));

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->triggerExitCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyDoesNotCollideWithTrigger_AndDidNotLastFrame_DoesNotCallTriggerExit)
  {
    GameObject gameObject;
    gameObject.getTransform()->setTranslation(500, 500);
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);
    otherCollider->setColliderType(Physics::ColliderType::kTrigger);

    Assert::IsFalse(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kTrigger);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->triggerCalled());

    getPhysicsManager().update(0.1f);

    // Check collision did not occur
    Assert::IsFalse(detector->triggerCalled());

    detector->reset();

    Assert::IsFalse(detector->triggerExitCalled());
    Assert::IsFalse(rectangleCollider->intersects(*otherCollider));

    getPhysicsManager().update(0.1f);

    Assert::IsFalse(detector->triggerExitCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyDoesNotCollideWithCollider_ButDidLastFrame_CallsCollisionExit)
  {
    GameObject gameObject;
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsTrue(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    // Check collision occurred
    Assert::IsTrue(detector->collisionCalled());

    detector->reset();

    Assert::IsFalse(detector->collisionExitCalled());

    // Move collider and see that a collision will now not occur
    gameObject.getTransform()->setTranslation(500, 500);
    rectangleCollider->sync(); // Sync with gameobject's position

    Assert::IsFalse(rectangleCollider->intersects(*otherCollider));

    getPhysicsManager().update(0.1f);

    Assert::IsTrue(detector->collisionExitCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsManager_Update_SimulatedBodyDoesNotCollideWithTrigger_AndDidNotLastFrame_DoesNotCallCollisionExit)
  {
    GameObject gameObject;
    gameObject.getTransform()->setTranslation(500, 500);
    observer_ptr<CollisionDetector> detector = gameObject.addComponent<CollisionDetector>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 200);

    // Add scripts & components
    gameObject.update(0);

    GameObject other;
    observer_ptr<RectangleCollider> otherCollider = other.addComponent<RectangleCollider>();
    otherCollider->setDimensions(50, 50);

    Assert::IsFalse(rectangleCollider->intersects(*otherCollider));
    Assert::IsTrue(otherCollider->getColliderType() == Physics::ColliderType::kCollider);
    Assert::AreEqual((size_t)0, getPhysicsManager().getSimulatedBodiesSize());

    getPhysicsManager().addSimulatedBody(*rectangleCollider);

    Assert::AreEqual((size_t)1, getPhysicsManager().getSimulatedBodiesSize());
    Assert::IsFalse(detector->collisionCalled());

    getPhysicsManager().update(0.1f);

    // Check collision occurred
    Assert::IsFalse(detector->collisionCalled());

    detector->reset();

    Assert::IsFalse(detector->collisionExitCalled());
    Assert::IsFalse(rectangleCollider->intersects(*otherCollider));

    getPhysicsManager().update(0.1f);

    Assert::IsFalse(detector->collisionExitCalled());
  }

#pragma endregion

  };
}