#include "UtilityHeaders/UnitTestHeaders.h"

#include "Rendering/Canvas.h"
#include "Rendering/RenderManager.h"
#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Physics/RectangleCollider.h"
#include "Physics/PhysicsManager.h"
#include "OpenGL/GL.h"
#include "Scene/SceneUtils.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
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
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(Canvas::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<Canvas*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Constructor_SetsProjectionMode_ToPerspective)
  {
    GameObject gameObject;
    Canvas canvas(gameObject);

    Assert::IsTrue(canvas.getProjectionMode() == ProjectionMode::kPerspective);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Constructor_SetsDimensions_ToViewportDimensions)
  {
    GameObject gameObject;
    Canvas canvas(gameObject);

    Assert::AreEqual(getViewportDimensions(), canvas.getDimensions());
  }

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_GameObjectActive_WithCollider_RaycastsCollider)
  {
    GameObject gameObject;

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsTrue(gameObject.isActive());

    canvas->handleInput();

    Assert::IsTrue(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_GameObjectNotActive_WithCollider_DoesNotRaycastCollider)
  {
    GameObject gameObject;
    gameObject.setActive(false);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = gameObject.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);

    Assert::IsFalse(rectangleCollider->isHitByRay());
    Assert::IsFalse(gameObject.isActive());

    canvas->handleInput();

    Assert::IsFalse(rectangleCollider->isHitByRay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_HandleInput_GameObjectNotActive_DoesNotRaycastChildren)
  {
    GameObject gameObject;
    GameObject child;
    GameObject grandChild;
    gameObject.setActive(false);
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
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
    GameObject gameObject;
    GameObject child;
    child.setParent(&gameObject);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = child.addComponent<RectangleCollider>();
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
    GameObject gameObject;
    GameObject child;
    child.setParent(&gameObject);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = child.addComponent<RectangleCollider>();
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
    GameObject gameObject;
    GameObject child;
    child.setParent(&gameObject);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = child.addComponent<RectangleCollider>();
    rectangleCollider->setDimensions(100, 100);
    observer_ptr<Canvas> childCanvas = child.addComponent<Canvas>();

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
    GameObject gameObject;
    GameObject child;
    GameObject grandChild;
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
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
    GameObject gameObject;
    GameObject child;
    GameObject grandChild;
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<Canvas> childCanvas = child.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
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
    GameObject gameObject;
    GameObject child;
    GameObject grandChild;
    child.setActive(false);
    child.setParent(&gameObject);
    grandChild.setParent(&child);

    observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
    observer_ptr<RectangleCollider> rectangleCollider = grandChild.addComponent<RectangleCollider>();
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
      GameObject gameObject;

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();

      AssertCel::IsActive(gameObject);
      
      canvas->render(0);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Canvas_Render_GameObjectActiveAndHasActiveRenderer_Renders)
  {
    if (Celeste::GL::isInitialized())
    {
      GameObject gameObject;

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = gameObject.addComponent<MockSpriteRenderer>();

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
      GameObject gameObject;
      gameObject.setActive(false);

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = gameObject.addComponent<MockSpriteRenderer>();

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
      GameObject gameObject;

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = gameObject.addComponent<MockSpriteRenderer>();
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
      GameObject gameObject;
      GameObject child;
      gameObject.setActive(false);
      child.setParent(&gameObject);

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = child.addComponent<MockSpriteRenderer>();

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
      GameObject gameObject;
      GameObject child;
      child.setParent(&gameObject);

      Assert::IsTrue(&gameObject == child.getParent());

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = child.addComponent<MockSpriteRenderer>();

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
      GameObject gameObject;
      GameObject child;
      GameObject grandChild;
      child.setParent(&gameObject);
      grandChild.setParent(&child);

      Assert::IsTrue(&gameObject == child.getParent());
      Assert::IsTrue(&child == grandChild.getParent());

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = grandChild.addComponent<MockSpriteRenderer>();

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
      GameObject gameObject;
      GameObject child;
      child.setParent(&gameObject);

      Assert::IsTrue(&gameObject == child.getParent());

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<Canvas> childCanvas = child.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = child.addComponent<MockSpriteRenderer>();

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
      GameObject gameObject;
      GameObject child;
      GameObject grandChild;
      child.setParent(&gameObject);
      grandChild.setParent(&child);

      Assert::IsTrue(&gameObject == child.getParent());
      Assert::IsTrue(&child == grandChild.getParent());

      observer_ptr<Canvas> canvas = gameObject.addComponent<Canvas>();
      observer_ptr<Canvas> childCanvas = child.addComponent<Canvas>();
      observer_ptr<MockSpriteRenderer> renderer = grandChild.addComponent<MockSpriteRenderer>();

      AssertCel::IsActive(gameObject);
      AssertCel::HasComponent<Canvas>(child);
      AssertCel::HasComponent<Renderer>(grandChild);
      Assert::IsFalse(renderer->isRenderCalled());

      canvas->render(0);

      Assert::IsFalse(renderer->isRenderCalled());
    }
  }

#pragma endregion

  };
}