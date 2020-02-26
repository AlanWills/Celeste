#include "UtilityHeaders/UnitTestHeaders.h"

#include "Rendering/Canvas.h"
#include "Rendering/RenderManager.h"
#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Physics/RectangleCollider.h"
#include "Physics/PhysicsManager.h"
#include "OpenGL/GL.h"
#include "Screens/ScreenUtils.h"
#include "Registries/ComponentRegistry.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using RectangleCollider = Celeste::Physics::RectangleCollider;

using namespace Celeste;
using namespace Celeste::Rendering;


namespace TestCeleste::Rendering
{
  CELESTE_TEST_CLASS(TestCanvas)

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Canvas_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<Canvas>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_IsAllocatableFromComponentRegistry)
  {
    GAMEOBJECT(gameObject);

    AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(Canvas::type_name(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<Canvas*>(component.get()));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Constructor_SetsProjectionMode_ToPerspective)
  {
    Canvas canvas;

    Assert::IsTrue(canvas.getProjectionMode() == ProjectionMode::kPerspective);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Constructor_SetsDimensions_ToOneVector)
  {
    Canvas canvas;

    Assert::AreEqual(glm::vec2(1), canvas.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Constructor_SetsDimensions_ToViewportDimensions)
  {
    Canvas canvas;

    Assert::AreEqual(getViewportDimensions(), canvas.getDimensions());
  }

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_GameObjectActive_WithCollider_RaycastsCollider)
  {
    GAMEOBJECT(gameObject);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());

    canvas->handleInput();

    Assert::IsTrue(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_GameObjectNotActive_WithCollider_DoesNotRaycastCollider)
  {
    GAMEOBJECT(gameObject);
    gameObject.setActive(false);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsFalse(gameObject.isActive());

    canvas->handleInput();

    Assert::IsFalse(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_GameObjectNotActive_DoesNotRaycastChildren)
  {
    GAMEOBJECT(gameObject);
    GAMEOBJECT(child);
    GAMEOBJECT(grandChild);
    gameObject.setActive(false);
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsFalse(gameObject.isActive());
    Assert::IsTrue(child.isActive());
    Assert::IsTrue(grandChild.isActive());
    AssertCel::DoesNotHaveComponent<Canvas>(child);
    Assert::IsTrue(&gameObject == child.getParent());
    Assert::IsTrue(&child == grandChild.getParent());

    canvas->handleInput();

    Assert::IsFalse(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_ChildWithCollider_ColliderIsActive_RaycastsCollider)
  {
    GAMEOBJECT(gameObject);
    GAMEOBJECT(child);
    child.setParent(&gameObject);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = child.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());
    Assert::IsTrue(child.isActive());
    Assert::IsTrue(&gameObject == child.getParent());

    canvas->handleInput();

    Assert::IsTrue(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_ChildWithCollider_ColliderIsNotActive_DoesNotRaycastCollider)
  {
    GAMEOBJECT(gameObject);
    GAMEOBJECT(child);
    child.setParent(&gameObject);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = child.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);
    rectangleCollider->setActive(false);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());
    Assert::IsTrue(child.isActive());
    Assert::IsFalse(rectangleCollider->isActive());
    Assert::IsTrue(&gameObject == child.getParent());

    canvas->handleInput();

    Assert::IsFalse(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_ChildHasCanvasAndCollider_DoesNotRaycastCollider)
  {
    GAMEOBJECT(gameObject);
    GAMEOBJECT(child);
    child.setParent(&gameObject);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = child.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);
    AutoDeallocator<Canvas> childCanvas = child.addComponent<Canvas>();

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());
    Assert::IsTrue(child.isActive());
    AssertCel::HasComponent<Canvas>(child);
    Assert::IsTrue(&gameObject == child.getParent());

    canvas->handleInput();

    Assert::IsFalse(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_RaycastsGrandChildren)
  {
    GAMEOBJECT(gameObject);
    GAMEOBJECT(child);
    GAMEOBJECT(grandChild);
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());
    Assert::IsTrue(child.isActive());
    Assert::IsTrue(grandChild.isActive());
    AssertCel::DoesNotHaveComponent<Canvas>(child);
    Assert::IsTrue(&gameObject == child.getParent());
    Assert::IsTrue(&child == grandChild.getParent());

    canvas->handleInput();

    Assert::IsTrue(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_ChildHasCanvas_DoesNotRaycastAnyGrandChildColliders)
  {
    GAMEOBJECT(gameObject);
    GAMEOBJECT(child);
    GAMEOBJECT(grandChild);
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<Canvas> childCanvas = child.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());
    Assert::IsTrue(child.isActive());
    Assert::IsTrue(grandChild.isActive());
    AssertCel::HasComponent<Canvas>(child);
    Assert::IsTrue(&gameObject == child.getParent());
    Assert::IsTrue(&child == grandChild.getParent());

    canvas->handleInput();

    Assert::IsFalse(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_ChildIsNotActive_DoesNotRaycastAnyGrandChildColliders)
  {
    GAMEOBJECT(gameObject);
    GAMEOBJECT(child);
    GAMEOBJECT(grandChild);
    child.setActive(false);
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    AutoDeallocator<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());
    Assert::IsFalse(child.isActive());
    Assert::IsTrue(grandChild.isActive());
    AssertCel::DoesNotHaveComponent<Canvas>(child);
    Assert::IsTrue(&gameObject == child.getParent());
    Assert::IsTrue(&child == grandChild.getParent());

    canvas->handleInput();

    Assert::IsFalse(rectangleCollider->isHitByRay());
  }

#pragma endregion

#pragma region Render Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActiveAndHasNoRenderer_DoesNothing)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();

      AssertCel::IsActive(gameObject);
      
      canvas->render(0);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActiveAndHasActiveRenderer_Renders)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = gameObject.addComponent<MockSpriteRenderer>();

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(*renderer);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsTrue(renderer->isRenderCalled());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectNotActiveAndHasActiveRenderer_DoesNotRender)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);
      gameObject.setActive(false);

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = gameObject.addComponent<MockSpriteRenderer>();

      AssertCel::IsNotActive(gameObject);
      AssertCel::IsActive(*renderer);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsFalse(renderer->isRenderCalled());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActiveAndHasNonActiveRenderer_DoesNotRender)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = gameObject.addComponent<MockSpriteRenderer>();
      renderer->setActive(false);

      AssertCel::IsActive(*canvas);
      AssertCel::IsNotActive(*renderer);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsFalse(renderer->isRenderCalled());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectNotActive_DoesNotRenderChildren)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(child);
      gameObject.setActive(false);
      child.setParent(&gameObject);

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = child.addComponent<MockSpriteRenderer>();

      AssertCel::IsNotActive(gameObject);
      AssertCel::HasComponent<Renderer>(child);
      AssertCel::DoesNotHaveComponent<Canvas>(child);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsFalse(renderer->isRenderCalled());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActive_ChildWithoutCanvas_RendersChild)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(child);
      child.setParent(&gameObject);

      Assert::IsTrue(&gameObject == child.getParent());

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = child.addComponent<MockSpriteRenderer>();

      AssertCel::IsActive(gameObject);
      AssertCel::HasComponent<Renderer>(child);
      AssertCel::DoesNotHaveComponent<Canvas>(child);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsTrue(renderer->isRenderCalled());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActive_ChildWithoutCanvas_RendersGrandChildren)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(child);
      GAMEOBJECT(grandChild);
      child.setParent(&gameObject);
      grandChild.setParent(&child);

      Assert::IsTrue(&gameObject == child.getParent());
      Assert::IsTrue(&child == grandChild.getParent());

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = grandChild.addComponent<MockSpriteRenderer>();

      AssertCel::IsActive(gameObject);
      AssertCel::DoesNotHaveComponent<Canvas>(child);
      AssertCel::HasComponent<Renderer>(grandChild);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsTrue(renderer->isRenderCalled());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActive_ChildWithCanvas_DoesNotRenderChild)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(child);
      child.setParent(&gameObject);

      Assert::IsTrue(&gameObject == child.getParent());

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<Canvas> childCanvas = child.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = child.addComponent<MockSpriteRenderer>();

      AssertCel::IsActive(gameObject);
      AssertCel::HasComponent<Canvas>(child);
      AssertCel::HasComponent<Renderer>(child);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsFalse(renderer->isRenderCalled());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActive_ChildWithCanvas_DoesNotRenderGrandChildren)
  {
    if (Celeste::GL::isInitialized())
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(child);
      GAMEOBJECT(grandChild);
      child.setParent(&gameObject);
      grandChild.setParent(&child);

      Assert::IsTrue(&gameObject == child.getParent());
      Assert::IsTrue(&child == grandChild.getParent());

      AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
      AutoDeallocator<Canvas> childCanvas = child.addComponent<Canvas>();
      AutoDeallocator<MockSpriteRenderer> renderer = grandChild.addComponent<MockSpriteRenderer>();

      AssertCel::IsActive(gameObject);
      AssertCel::HasComponent<Canvas>(child);
      AssertCel::HasComponent<Renderer>(grandChild);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsFalse(renderer->isRenderCalled());
    }
  }

#pragma endregion

#pragma region Die Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Die_SetsProjectionMode_ToPerspective)
  {
    Canvas canvas;
    canvas.setProjectionMode(ProjectionMode::kOrthographic);

    Assert::IsTrue(canvas.getProjectionMode() == ProjectionMode::kOrthographic);

    canvas.die();

    Assert::IsTrue(canvas.getProjectionMode() == ProjectionMode::kPerspective);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Die_SetsDimensions_ToOneVector)
  {
    Canvas canvas;
    canvas.setDimensions(glm::vec2(200, 300));

    Assert::AreEqual(glm::vec2(200, 300), canvas.getDimensions());

    canvas.die();

    Assert::AreEqual(glm::vec2(1), canvas.getDimensions());
  }

#pragma endregion

  };
}