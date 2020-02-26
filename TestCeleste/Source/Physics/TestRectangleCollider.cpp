#include "UtilityHeaders/UnitTestHeaders.h"

#include "Physics/RectangleCollider.h"
#include "Maths/Ray.h"
#include "Mocks/Physics/MockCollider.h"
#include "Utils/ObjectUtils.h"
#include "Registries/ComponentRegistry.h"
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

    AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(RectangleCollider::type_name(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<RectangleCollider*>(component.get()));
    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleCollider_Constructor_CreatesEmptyRectangle)
  {
    RectangleCollider collider;
      
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
    RectangleCollider collider;

    Assert::AreEqual(glm::vec2(0, 0), collider.getDimensions());
  }

#pragma endregion

#pragma region Set Game Object Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleCollider_SetGameObject_SynchronizesPosition)
  {
    GAMEOBJECT(gameObject);
    gameObject.getTransform()->setTranslation(50, -30);

    AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

    Assert::AreEqual(glm::vec2(50, -30), collider->getCentre());
  }

#pragma endregion

#pragma region Set Offset Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_SetOffset_FromZero_ToNonZero_UpdatesRectangle)
    {
      RectangleCollider collider;

      Assert::AreEqual(glm::vec2(), collider.getCentre());

      collider.setOffset(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), collider.getCentre());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_SetOffset_FromNonZero_ToAnotherZero_UpdatesRectangleWithDelta)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

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
      RectangleCollider collider;

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
    TEST_METHOD(RectangleCollider_Update_WithNoTransformSet_DoesNotThrow)
    {
      RectangleCollider collider;
      collider.update(0);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Update_WithTransformSet_NoOffset_SetsColliderCentreToTransformWorldPosition)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(parent);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      
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
      GAMEOBJECT(gameObject);
      GAMEOBJECT(parent);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

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
      GAMEOBJECT(gameObject);
      GAMEOBJECT(parent);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

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

#pragma region Die Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Die_SesRectangleToEmpty)
    {
      GAMEOBJECT(gameObject);
      gameObject.getTransform()->setTranslation(50, -30);
      gameObject.getTransform()->setScale(5, 2);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      collider->setDimensions(50, 40);

      Assert::AreEqual(glm::vec2(50, -30), collider->getCentre());
      Assert::AreEqual(250.0f, collider->getWidth());
      Assert::AreEqual(80.0f, collider->getHeight());

      collider->die();

      Assert::AreEqual(glm::vec2(), collider->getCentre());
      Assert::AreEqual(0.0f, collider->getWidth());
      Assert::AreEqual(0.0f, collider->getHeight());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Die_SetsDimensionsToZero)
    {
      RectangleCollider collider;
      collider.setDimensions(50, 40);

      Assert::AreEqual(glm::vec2(50, 40), collider.getDimensions());

      collider.die();

      Assert::AreEqual(glm::vec2(), collider.getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Die_SetsColliderTypeTo_kCollider)
    {
      RectangleCollider collider;
      collider.setColliderType(ColliderType::kTrigger);

      Assert::IsTrue(collider.getColliderType() == ColliderType::kTrigger);

      collider.die();

      Assert::IsTrue(collider.getColliderType() == ColliderType::kCollider);
    }

#pragma endregion

#pragma region Sync Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Sync_NullGameObject_DoesNothing)
    {
      RectangleCollider collider;
      collider.setDimensions(20, 30);

      Assert::IsNull(collider.getGameObject());

      collider.sync();

      Assert::AreEqual(glm::vec2(), collider.getCentre());
      Assert::AreEqual(glm::vec2(20, 30), collider.getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_Sync_SynchronizesPositionAndScale)
    {
      GAMEOBJECT(gameObject);

      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
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
    TEST_METHOD(RectangleCollider_IntersectsRayWithNoTransform_ShouldReturnFalse)
    {
      RectangleCollider collider;
      collider.setDimensions(10, 10);

      Ray ray(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1));

      // False if no transform
      Assert::IsFalse(collider.intersects(ray));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRay_NoOffset_ShouldReturnTrue)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
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
      RectangleCollider collider;
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
      RectangleCollider collider;

      Assert::AreEqual(glm::vec2(), collider.getDimensions());

      Ray ray(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1));

      Assert::IsFalse(collider.intersects(ray));
    }

#pragma endregion

#pragma region Intersects Point Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_NoOffset_ShouldReturnTrue)
    {
      RectangleCollider collider;
      collider.setDimensions(10, 10);

      Assert::IsTrue(collider.intersects(glm::vec2(0, 0)));
      Assert::IsTrue(collider.intersects(glm::vec2(1, 1)));
      Assert::IsTrue(collider.intersects(glm::vec2(-4, 4)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_NoOffset_ShouldReturnFalse)
    {
      RectangleCollider collider;
      collider.setDimensions(10, 10);

      Assert::IsFalse(collider.intersects(glm::vec2(10, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(5, 10)));
      Assert::IsFalse(collider.intersects(glm::vec2(5.1f, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(100, 100)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_WithOffset_ShouldReturnTrue)
    {
      RectangleCollider collider;
      collider.setDimensions(10, 10);
      collider.setOffset(-20, 5);

      Assert::IsTrue(collider.intersects(glm::vec2(-16, 4)));
      Assert::IsTrue(collider.intersects(glm::vec2(-22, 7)));
      Assert::IsTrue(collider.intersects(glm::vec2(-18.75f, 1)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_WithOffset_ShouldReturnFalse)
    {
      RectangleCollider collider;
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
      RectangleCollider collider;
      collider.setDimensions(10, 10);

      Assert::IsFalse(collider.intersects(glm::vec2(5, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(-5, 0)));
      Assert::IsFalse(collider.intersects(glm::vec2(0, 5)));
      Assert::IsFalse(collider.intersects(glm::vec2(0, -5)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsPoint_DegenerateRectangle_ShouldReturnFalse)
    {
      RectangleCollider collider;

      Assert::AreEqual(glm::vec2(), collider.getDimensions());
      Assert::IsFalse(collider.intersects(glm::vec2(0, 0)));
    }

#pragma endregion

#pragma region Intersects Rectangle Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_NoOffset_ShouldReturnTrue)
    {
      RectangleCollider collider;
      collider.setDimensions(10, 10);

      Assert::IsTrue(collider.intersects(Rectangle(1, 1, 1, 1)));
      Assert::IsTrue(collider.intersects(Rectangle(5, 0, 1, 0)));
      Assert::IsTrue(collider.intersects(Rectangle(0, 0, 20, 20)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_NoOffset_ShouldReturnFalse)
    {
      RectangleCollider collider;
      collider.setDimensions(10, 10);

      Assert::IsFalse(collider.intersects(Rectangle(10, 0, 3, 0)));
      Assert::IsFalse(collider.intersects(Rectangle(5, 10, 5, 1)));
      Assert::IsFalse(collider.intersects(Rectangle(5.1f, 0, 0.1f, 1)));
      Assert::IsFalse(collider.intersects(Rectangle(100, 100, 100, 100)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_WithOffset_ShouldReturnTrue)
    {
      RectangleCollider collider;
      collider.setDimensions(10, 10);
      collider.setOffset(-10, 1);

      Assert::IsTrue(collider.intersects(Rectangle(-10, 0.5f, 1, 1)));
      Assert::IsTrue(collider.intersects(Rectangle(-15, 1, 1, 0)));
      Assert::IsTrue(collider.intersects(Rectangle(0, 0, 30, 20)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangle_WithOffset_ShouldReturnFalse)
    {
      RectangleCollider collider;
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
      RectangleCollider rectangleCollider;
      RectangleCollider other;

      Assert::AreEqual(glm::vec2(), rectangleCollider.getDimensions());
      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(other));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangleCollider_OneIsDegenerate_ShouldReturnFalse)
    {
      RectangleCollider rectangleCollider;
      RectangleCollider other;

      rectangleCollider.setDimensions(10, 5);

      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(other));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangleCollider_ShouldReturnTrue)
    {
      RectangleCollider rectangleCollider;
      RectangleCollider other;

      rectangleCollider.setDimensions(10, 20);
      other.setDimensions(5, 5);

      Assert::IsTrue(rectangleCollider.intersects(other));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsRectangleCollider_ShouldReturnFalse)
    {
      RectangleCollider rectangleCollider;
      RectangleCollider other;

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
      RectangleCollider rectangleCollider;
      RectangleCollider other;

      Assert::AreEqual(glm::vec2(), rectangleCollider.getDimensions());
      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsConstRectangleCollider_OneIsDegenerate_ShouldReturnFalse)
    {
      RectangleCollider rectangleCollider;
      RectangleCollider other;

      rectangleCollider.setDimensions(10, 5);

      Assert::AreEqual(glm::vec2(), other.getDimensions());
      Assert::IsFalse(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsConstRectangleCollider_ShouldReturnTrue)
    {
      RectangleCollider rectangleCollider;
      RectangleCollider other;

      rectangleCollider.setDimensions(10, 20);
      other.setDimensions(5, 5);

      Assert::IsTrue(rectangleCollider.intersects(static_cast<const RectangleCollider&>(other)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RectangleCollider_IntersectsConstRectangleCollider_ShouldReturnFalse)
    {
      RectangleCollider rectangleCollider;
      RectangleCollider other;

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
      RectangleCollider collider;
      MockCollider unhandledCollider;

      Assert::IsFalse(collider.intersects(unhandledCollider));
    }

#pragma endregion

#pragma endregion

  };
}