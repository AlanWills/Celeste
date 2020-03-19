#include "UtilityHeaders/UnitTestHeaders.h"

#include "Physics/RectangleCollider.h"
#include "Maths/Ray.h"
#include "Mocks/Physics/MockCollider.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"


namespace TestCeleste
{
  using namespace Celeste;
  using namespace Celeste::Physics;
  using namespace Celeste::Maths;

  using Rectangle = Celeste::Maths::Rectangle;

  CELESTE_TEST_CLASS(TestRectangleCollider)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleCollider_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<RectangleCollider>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleCollider_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(RectangleCollider::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<RectangleCollider*>(component));
    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleCollider_Constructor_CreatesEmptyRectangle)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);
      
    Assert::AreEqual(glm::vec2(0, 0), collider.getLeft());
    Assert::AreEqual(glm::vec2(0, 0), collider.getTop());
    Assert::AreEqual(glm::vec2(0, 0), collider.getRight());
    Assert::AreEqual(glm::vec2(0, 0), collider.getBottom());
    Assert::AreEqual(glm::vec2(0, 0), collider.getCentre());
    Assert::AreEqual(0.0f, collider.getWidth());
    Assert::AreEqual(0.0f, collider.getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleCollider_Constructor_SetsDimensionsToZero)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);

    Assert::AreEqual(glm::vec2(0, 0), collider.getDimensions());
  }

#pragma endregion

#pragma region Set Offset Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_SetOffset_FromZero_ToNonZero_UpdatesRectangle)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);

      Assert::AreEqual(glm::vec2(), collider.getCentre());

      collider.setOffset(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), collider.getCentre());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_SetOffset_FromNonZero_ToAnotherZero_UpdatesRectangleWithDelta)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

      Assert::AreEqual(glm::vec2(), collider->getCentre());

      collider->setOffset(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), collider->getCentre());

      collider->setOffset(glm::vec2(200, 100));

      Assert::AreEqual(glm::vec2(200, 100), collider->getCentre());

      // Check with a game object to make sure it's a delta that is applied rather than a fixed value
      gameObject.getTransform()->setTranslation(50, -50);
      collider->update(0);

      Assert::AreEqual(glm::vec2(250, 50), collider->getCentre());

      collider->setOffset(-100, -5);

      Assert::AreEqual(glm::vec2(-50, -55), collider->getCentre());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_SetOffset_FromNonZero_ToSameOffset_DoesNothing)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);

      Assert::AreEqual(glm::vec2(), collider.getCentre());

      collider.setOffset(0, 0);

      Assert::AreEqual(glm::vec2(), collider.getCentre());

      collider.setOffset(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), collider.getCentre());
      
      collider.setOffset(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), collider.getCentre());

    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Update_WithTransformSet_NoOffset_SetsColliderCentreToTransformWorldPosition)
    {
      GameObject gameObject;
      GameObject parent;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      
      collider->setDimensions(10, 10);
      gameObject.getTransform()->setTranslation(10, 10);
      collider->update(0);
      
      Assert::AreEqual(glm::vec2(5, 10), collider->getLeft());
      Assert::AreEqual(glm::vec2(10, 15), collider->getTop());
      Assert::AreEqual(glm::vec2(15, 10), collider->getRight());
      Assert::AreEqual(glm::vec2(10, 5), collider->getBottom());

      parent.getTransform()->setTranslation(-20, 20);
      gameObject.getTransform()->setParent(parent.getTransform());

      collider->update(0);

      Assert::AreEqual(glm::vec2(-15, 30), collider->getLeft());
      Assert::AreEqual(glm::vec2(-10, 35), collider->getTop());
      Assert::AreEqual(glm::vec2(-5, 30), collider->getRight());
      Assert::AreEqual(glm::vec2(-10, 25), collider->getBottom());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Update_WithTransformSet_AndOffset_SetsColliderCentreToTransformWorldPosition_PlusOffset)
    {
      GameObject gameObject;
      GameObject parent;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

      collider->setDimensions(10, 10);
      collider->setOffset(15, 5);
      gameObject.getTransform()->setTranslation(10, 10);
      collider->update(0);

      Assert::AreEqual(glm::vec2(20, 15), collider->getLeft());
      Assert::AreEqual(glm::vec2(25, 20), collider->getTop());
      Assert::AreEqual(glm::vec2(30, 15), collider->getRight());
      Assert::AreEqual(glm::vec2(25, 10), collider->getBottom());

      collider->setOffset(-10, -10);
      gameObject.getTransform()->setParent(parent.getTransform());

      collider->update(0);

      Assert::AreEqual(glm::vec2(-5, 0), collider->getLeft());
      Assert::AreEqual(glm::vec2(0, 5), collider->getTop());
      Assert::AreEqual(glm::vec2(5, 0), collider->getRight());
      Assert::AreEqual(glm::vec2(0, -5), collider->getBottom());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Update_WithTransformSet_SetsColliderDimensionsToWorldScaledDimensions)
    {
      GameObject gameObject;
      GameObject parent;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

      collider->setDimensions(10, 10);
      collider->update(0);

      Assert::AreEqual(glm::vec2(10, 10), collider->getDimensions());

      parent.getTransform()->setScale(0.2f, 0.5f);
      gameObject.getTransform()->setParent(parent.getTransform());
      collider->update(0);

      Assert::AreEqual(glm::vec2(2, 5), collider->getDimensions());

      gameObject.getTransform()->setScale(2, 0.5f);
      collider->update(0);

      Assert::AreEqual(glm::vec2(4, 2.5f), collider->getDimensions());
    }

#pragma endregion

#pragma region Sync Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Sync_SynchronizesPositionAndScale)
    {
      GameObject gameObject;

      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      collider->setDimensions(20, 30);

      Assert::AreEqual(glm::vec2(), collider->getCentre());
      Assert::AreEqual(glm::vec2(20, 30), collider->getDimensions());
      
      gameObject.getTransform()->setTranslation(50, -30);
      gameObject.getTransform()->setScale(2, 0.5f);
      collider->sync();

      Assert::AreEqual(glm::vec2(50, -30), collider->getCentre());
      Assert::AreEqual(glm::vec2(40, 15), collider->getDimensions());
    }

#pragma endregion

#pragma region Intersects Ray Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRay_NoOffset_ShouldReturnTrue)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

      collider->setDimensions(10, 10);

      Ray ray(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1));
      
      Assert::IsTrue(collider->intersects(ray));

      ray.m_origin = glm::vec3(0, 0, 0.1f);
      ray.m_direction = glm::vec3(1, 1, -1);

      Assert::IsTrue(collider->intersects(ray));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRay_NoOffset_ShouldReturnFalse)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      collider->setDimensions(10, 10);

      Ray ray(glm::vec3(11, 0, 1), glm::vec3(0, 0, -1));

      Assert::IsFalse(collider->intersects(ray));

      ray.m_origin = glm::vec3(0, 0, 10);
      ray.m_direction = glm::vec3(1, 1, -1);

      Assert::IsFalse(collider->intersects(ray));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRay_WithOffset_ShouldReturnTrue)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

      collider->setDimensions(10, 10);
      collider->setOffset(-3, 3);

      Ray ray(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1));

      Assert::IsTrue(collider->intersects(ray));

      ray.m_origin = glm::vec3(1.99f, 3.9f, 1);

      Assert::IsTrue(collider->intersects(ray));

      ray.m_origin = glm::vec3(0, 0, 0.1f);
      ray.m_direction = glm::vec3(1, 1, -1);

      Assert::IsTrue(collider->intersects(ray));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRay_WithOffset_ShouldReturnFalse)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      collider->setDimensions(10, 10);
      collider->setOffset(-10, 5);

      Ray ray(glm::vec3(11, 0, 1), glm::vec3(0, 0, -1));

      Assert::IsFalse(collider->intersects(ray));

      ray.m_origin = glm::vec3(0, 0, 10);
      ray.m_direction = glm::vec3(1, 1, -1);

      Assert::IsFalse(collider->intersects(ray));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRay_OnEdge_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(6, 8);

      Ray ray(glm::vec3(3, 0, 1), glm::vec3(0, 0, -1));

      Assert::IsFalse(collider.intersects(ray));

      ray.m_origin = glm::vec3(0, 4, 1);

      Assert::IsFalse(collider.intersects(ray));

      ray.m_origin = glm::vec3(-3, 0, 1);

      Assert::IsFalse(collider.intersects(ray));

      ray.m_origin = glm::vec3(0, -4, 1);

      Assert::IsFalse(collider.intersects(ray));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRay_DegenerateRectangle_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);

      Assert::AreEqual(glm::vec2(), collider.getDimensions());

      Ray ray(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1));

      Assert::IsFalse(collider.intersects(ray));
    }

#pragma endregion

#pragma region Intersects Point Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_NoOffset_ShouldReturnTrue)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);

      Assert::IsTrue(collider.intersects(glm::vec2(0, 0)));
      Assert::IsTrue(collider.intersects(glm::vec2(1, 1)));
      Assert::IsTrue(collider.intersects(glm::vec2(-4, 4)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_NoOffset_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);

      Assert::IsFalse(collider.intersects(glm::vec2(10, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(5, 10)));
      Assert::IsFalse(collider.intersects(glm::vec2(5.1f, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(100, 100)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_WithOffset_ShouldReturnTrue)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);
      collider.setOffset(-20, 5);

      Assert::IsTrue(collider.intersects(glm::vec2(-16, 4)));
      Assert::IsTrue(collider.intersects(glm::vec2(-22, 7)));
      Assert::IsTrue(collider.intersects(glm::vec2(-18.75f, 1)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_WithOffset_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);
      collider.setOffset(-5, 15);

      Assert::IsFalse(collider.intersects(glm::vec2(0, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(-11, 15)));
      Assert::IsFalse(collider.intersects(glm::vec2(21, -5)));
      Assert::IsFalse(collider.intersects(glm::vec2(100, 100)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_OnEdge_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);

      Assert::IsFalse(collider.intersects(glm::vec2(5, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(-5, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(0, 5)));
      Assert::IsFalse(collider.intersects(glm::vec2(0, -5)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_DegenerateRectangle_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);

      Assert::AreEqual(glm::vec2(), collider.getDimensions());
      Assert::IsFalse(collider.intersects(glm::vec2(0, 0)));
    }

#pragma endregion

#pragma region Intersects Rectangle Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_NoOffset_ShouldReturnTrue)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);

      Assert::IsTrue(collider.intersects(Rectangle(1, 1, 1, 1)));
      Assert::IsTrue(collider.intersects(Rectangle(5, 0, 1, 0)));
      Assert::IsTrue(collider.intersects(Rectangle(0, 0, 20, 20)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_NoOffset_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);

      Assert::IsFalse(collider.intersects(Rectangle(10, 0, 3, 0)));
      Assert::IsFalse(collider.intersects(Rectangle(5, 10, 5, 1)));
      Assert::IsFalse(collider.intersects(Rectangle(5.1f, 0, 0.1f, 1)));
      Assert::IsFalse(collider.intersects(Rectangle(100, 100, 100, 100)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_WithOffset_ShouldReturnTrue)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);
      collider.setOffset(-10, 1);

      Assert::IsTrue(collider.intersects(Rectangle(-10, 0.5f, 1, 1)));
      Assert::IsTrue(collider.intersects(Rectangle(-15, 1, 1, 0)));
      Assert::IsTrue(collider.intersects(Rectangle(0, 0, 30, 20)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_WithOffset_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      collider.setDimensions(10, 10);
      collider.setOffset(-3, 2);

      Assert::IsFalse(collider.intersects(Rectangle(10, 0, 3, 0)));
      Assert::IsFalse(collider.intersects(Rectangle(5, 10, 5, 1)));
      Assert::IsFalse(collider.intersects(Rectangle(5.1f, 0, 0.1f, 1)));
      Assert::IsFalse(collider.intersects(Rectangle(100, 100, 100, 100)));
    }

#pragma endregion

#pragma region Intersects Collider Tests

#pragma region Rectangle Collider

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangleCollider_BothDegenerateAtSamePosition_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      Assert::AreEqual(glm::vec2(), rectangleCollider.getDimensions());
      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(other));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangleCollider_OneIsDegenerate_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      rectangleCollider.setDimensions(10, 5);

      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(other));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangleCollider_ShouldReturnTrue)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      rectangleCollider.setDimensions(10, 20);
      other.setDimensions(5, 5);

      Assert::IsTrue(rectangleCollider.intersects(other));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangleCollider_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      rectangleCollider.setDimensions(10, 20);
      rectangleCollider.setOffset(100, 100);
      other.setDimensions(5, 5);

      Assert::IsFalse(rectangleCollider.intersects(other));

      other.setDimensions(50, 50);

      Assert::IsFalse(rectangleCollider.intersects(other));
    }

#pragma endregion

#pragma region Const Rectangle Collider

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsConstRectangleCollider_BothDegenerateAtSamePosition_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      Assert::AreEqual(glm::vec2(), rectangleCollider.getDimensions());
      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsConstRectangleCollider_OneIsDegenerate_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      rectangleCollider.setDimensions(10, 5);

      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsConstRectangleCollider_ShouldReturnTrue)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      rectangleCollider.setDimensions(10, 20);
      other.setDimensions(5, 5);

      Assert::IsTrue(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsConstRectangleCollider_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider rectangleCollider(gameObject);
      RectangleCollider other(gameObject);

      rectangleCollider.setDimensions(10, 20);
      rectangleCollider.setOffset(100, 100);
      other.setDimensions(5, 5);

      Assert::IsFalse(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));

      other.setDimensions(50, 50);

      Assert::IsFalse(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));
    }

#pragma endregion

#pragma region Unhandled Collider

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsUnhandledCollider_ShouldReturnFalse)
    {
      GameObject gameObject;
      RectangleCollider collider(gameObject);
      MockCollider unhandledCollider(gameObject);

      Assert::IsFalse(collider.intersects(unhandledCollider));
    }

#pragma endregion

#pragma endregion

  };
}