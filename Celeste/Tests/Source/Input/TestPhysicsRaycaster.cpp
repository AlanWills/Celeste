#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/PhysicsRaycaster.h"
#include "Input/InputUtils.h"
#include "Input/Mouse.h"
#include "Rendering/Canvas.h"
#include "Mocks/Physics/MockCollider.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;
using namespace Celeste::Rendering;
using namespace Celeste::Physics;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestPhysicsRaycaster)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<PhysicsRaycaster>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(PhysicsRaycaster::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<PhysicsRaycaster*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Raycast Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectNotActive_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    gameObject.setActive(false);

    AssertCel::IsNotActive(gameObject);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_NoCollider_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);

    AssertCel::IsActive(gameObject);
    AssertCel::DoesNotHaveComponent<Collider>(gameObject);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_NoActiveCollider_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsNotActive(collider);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_ActiveColliderNotHitByRay_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(collider);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_ActiveColliderHitByRay_NoChildren_ReturnsCorrectList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectNotActive_WithChildrenWhichShouldBeRaycasted_ReturnsEmptyList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    gameObject.setActive(false);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    childCollider->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsNotActive(gameObject);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_NoCollider_WithChildrenWhichShouldBeRaycasted_ReturnsEmptyList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    childCollider->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::DoesNotHaveComponent<Collider>(gameObject);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&child, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_NoActiveCollider_WithChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setActive(false);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    childCollider->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsNotActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&child, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_ActiveColliderNotHitByRay_WithNoChildrenWhichShouldBeRaycasted_ReturnsEmptyList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();

    GameObject child;
    child.setParent(&gameObject);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsActive(collider);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_ActiveColliderNotHitByRay_WithChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    childCollider->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&child, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_ActiveColliderHitByRay_WithNoChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setIntersectsRayResult(true);

    GameObject child;
    child.setParent(&gameObject);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActive_ActiveColliderHitByRay_WithChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setIntersectsRayResult(true);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    childCollider->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(2), result.size());
    Assert::AreEqual(&gameObject, result[0]);
    Assert::AreEqual(&child, result[1]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActiveInRaycast_IgnoresInactiveChildren)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setIntersectsRayResult(true);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    childCollider->setIntersectsRayResult(true);
    child.setActive(false);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActiveInRaycast_IgnoresChildrenWithCanvasComponents)
  {
    GameObject gameObject;
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setIntersectsRayResult(true);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    child.addComponent<Canvas>();
    childCollider->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsRaycaster_Raycast_GameObjectActiveInRaycast_SortsHitGameObjectsIntoNearestToFurthest)
  {
    GameObject gameObject;
    gameObject.getTransform()->translate(0, 0, 4);
    PhysicsRaycaster raycaster(gameObject);
    observer_ptr<MockCollider> collider = gameObject.addComponent<MockCollider>();
    collider->setIntersectsRayResult(true);

    GameObject child;
    child.setParent(&gameObject);
    child.getTransform()->translate(0, 0, 5);
    observer_ptr<MockCollider> childCollider = child.addComponent<MockCollider>();
    childCollider->setIntersectsRayResult(true);

    GameObject child2;
    child2.setParent(&gameObject);
    child2.getTransform()->translate(0, 0, -6);
    observer_ptr<MockCollider> childCollider2 = child2.addComponent<MockCollider>();
    childCollider2->setIntersectsRayResult(true);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Collider>(gameObject);
    AssertCel::IsActive(collider);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(3), result.size());
    Assert::AreEqual(&child, result[0]);
    Assert::AreEqual(&gameObject, result[1]);
    Assert::AreEqual(&child2, result[2]);
  }

#pragma endregion

  };
}