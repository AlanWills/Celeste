#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/GraphicsRaycaster.h"
#include "Input/InputUtils.h"
#include "Input/Mouse.h"
#include "Rendering/Canvas.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestGraphicsRaycaster)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<GraphicsRaycaster>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(GraphicsRaycaster::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<GraphicsRaycaster*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Raycast Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectNotActive_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    gameObject.setActive(false);

    AssertCel::IsNotActive(gameObject);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_NoRenderer_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);

    AssertCel::IsActive(gameObject);
    AssertCel::DoesNotHaveComponent<Renderer>(gameObject);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_NoActiveRenderer_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsNotActive(renderer);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_ActiveRendererNotHitByRay_NoChildren_ReturnsEmptyList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(renderer);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_ActiveRendererHitByRay_NoChildren_ReturnsCorrectList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectNotActive_WithChildrenWhichShouldBeRaycasted_ReturnsEmptyList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    gameObject.setActive(false);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    childRenderer->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsNotActive(gameObject);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_NoRenderer_WithChildrenWhichShouldBeRaycasted_ReturnsEmptyList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    childRenderer->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::DoesNotHaveComponent<Renderer>(gameObject);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&child, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_NoActiveRenderer_WithChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setActive(false);

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    childRenderer->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsNotActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&child, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_ActiveRendererNotHitByRay_WithNoChildrenWhichShouldBeRaycasted_ReturnsEmptyList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(0, 0));

    GameObject child;
    child.setParent(&gameObject);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsActive(renderer);
    Assert::IsTrue(raycaster.raycast().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_ActiveRendererNotHitByRay_WithChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(0, 0));

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    childRenderer->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&child, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_ActiveRendererHitByRay_WithNoChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(100, 100));

    GameObject child;
    child.setParent(&gameObject);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActive_ActiveRendererHitByRay_WithChildrenWhichShouldBeRaycasted_ReturnsCorrectList)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(100, 100));

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    childRenderer->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(2), result.size());
    Assert::AreEqual(&gameObject, result[0]);
    Assert::AreEqual(&child, result[1]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActiveInRaycast_IgnoresInactiveChildren)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(100, 100));

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    childRenderer->setDimensions(glm::vec2(100, 100));
    child.setActive(false);

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActiveInRaycast_IgnoresChildrenWithCanvasComponents)
  {
    GameObject gameObject;
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(100, 100));

    GameObject child;
    child.setParent(&gameObject);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    child.addComponent<Canvas>();
    childRenderer->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(1), result.size());
    Assert::AreEqual(&gameObject, result[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GraphicsRaycaster_Raycast_GameObjectActiveInRaycast_SortsHitGameObjectsIntoNearestToFurthest)
  {
    GameObject gameObject;
    gameObject.getTransform()->translate(0, 0, 4);
    GraphicsRaycaster raycaster(gameObject);
    observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(100, 100));

    GameObject child;
    child.setParent(&gameObject);
    child.getTransform()->translate(0, 0, 5);
    observer_ptr<MockRenderer> childRenderer = child.addComponent<MockRenderer>();
    childRenderer->setDimensions(glm::vec2(100, 100));

    GameObject child2;
    child2.setParent(&gameObject);
    child2.getTransform()->translate(0, 0, -6);
    observer_ptr<MockRenderer> childRenderer2 = child2.addComponent<MockRenderer>();
    childRenderer2->setDimensions(glm::vec2(100, 100));

    getMouse().getTransform().setTranslation(glm::zero<glm::vec2>());

    AssertCel::IsActive(gameObject);
    AssertCel::HasComponent<Renderer>(gameObject);
    AssertCel::IsActive(renderer);

    auto result = raycaster.raycast();

    Assert::AreEqual(static_cast<size_t>(3), result.size());
    Assert::AreEqual(&child, result[0]);
    Assert::AreEqual(&gameObject, result[1]);
    Assert::AreEqual(&child2, result[2]);
  }

#pragma endregion

  };
}