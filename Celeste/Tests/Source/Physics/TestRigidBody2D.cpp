#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Objects/GameObject.h"
#include "Physics/RigidBody2D.h"
#include "TestUtils/Assert/AssertExt.h"
#include "TestUtils/Assert/AssertCel.h"
#include "Registries/ComponentRegistry.h"

using namespace Celeste;


namespace TestCeleste
{
  using namespace Celeste::Physics;

  CELESTE_TEST_CLASS(TestRigidBody2D)

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<RigidBody2D>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IsAllocatableFromComponentRegistry)
    {
      GameObject gameObject;

      observer_ptr<Component> component = ComponentRegistry::createComponent(RigidBody2D::type_name(), gameObject);

      Assert::IsNotNull(component);
      Assert::IsNotNull(dynamic_cast<RigidBody2D*>(component));
      Assert::AreEqual(&gameObject, component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_Constructor_SetsValuesToDefault)
    {
      GameObject gameObject;
      RigidBody2D rigidBody2D(gameObject);
      
      Assert::AreEqual(glm::vec2(), rigidBody2D.getLinearVelocity());
      Assert::AreEqual(glm::vec2(-FLT_MAX, -FLT_MAX), rigidBody2D.getMinLinearVelocity());
      Assert::AreEqual(glm::vec2(FLT_MAX, FLT_MAX), rigidBody2D.getMaxLinearVelocity());
      Assert::AreEqual(0.0f, rigidBody2D.getAngularVelocity());
      Assert::AreEqual(-FLT_MAX, rigidBody2D.getMinAngularVelocity());
      Assert::AreEqual(FLT_MAX, rigidBody2D.getMaxAngularVelocity());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_Update_WithNoParent_DoesNotThrow)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);
      
      rigidBody.update(1);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_Update_WithParentAndNonZeroLinearVelocity_UpdatesTransformTranslation)
    {
      GameObject gameObject;
      observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();

      rigidBody->setLinearVelocity(glm::vec2(100, 100));
      rigidBody->update(0.5f);

      Assert::AreEqual(glm::vec3(50, 50, 0), gameObject.getTransform()->getTranslation());
      Assert::AreEqual(0.0f, gameObject.getTransform()->getRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_Update_WithParentAndNonZeroAngularVelocity_UpdatesTransformRotation)
    {
      GameObject gameObject;
      observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();

      rigidBody->setAngularVelocity(1);
      rigidBody->update(0.5f);

      Assert::AreEqual(glm::vec3(), gameObject.getTransform()->getTranslation());
      Assert::AreEqual(0.5f, gameObject.getTransform()->getRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_Update_WithParentAndNonZeroVelocities_UpdatesTransformTranslationAndRotation)
    {
      GameObject gameObject;
      observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();

      rigidBody->setLinearVelocity(glm::vec2(100, 100));
      rigidBody->setAngularVelocity(glm::pi<float>());
      rigidBody->update(0.5f);

      Assert::AreEqual(glm::vec3(50, 50, 0), gameObject.getTransform()->getTranslation());
      Assert::AreEqual(glm::pi<float>() * 0.5f, gameObject.getTransform()->getRotation());

      rigidBody->update(0.5f);

      AssertExt::AreAlmostEqual(glm::vec3(100, 100, 0), gameObject.getTransform()->getTranslation());
      Assert::AreEqual(glm::pi<float>(), gameObject.getTransform()->getRotation());
    }

#pragma endregion

#pragma region Set Linear Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_SetLinearVelocity_IsClampedMyMinAndMax)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);
      rigidBody.setMinLinearVelocity(glm::vec2(-0.4f, 0.5f));
      rigidBody.setMaxLinearVelocity(glm::vec2(2, 0.6f));
      rigidBody.setLinearVelocity(glm::vec2(-0.9f, 0.4f));
      
      Assert::AreEqual(glm::vec2(-0.4f, 0.5f), rigidBody.getLinearVelocity());

      rigidBody.setLinearVelocity(glm::vec2(1.1f, 0.7f));

      Assert::AreEqual(glm::vec2(1.1f, 0.6f), rigidBody.getLinearVelocity());

      rigidBody.setLinearVelocity(glm::vec2(2.6f, 0.55f));

      Assert::AreEqual(glm::vec2(2, 0.55f), rigidBody.getLinearVelocity());
    }

#pragma endregion

#pragma region Set Min Linear Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_SetMinLinearVelocity_UpdatesMinLinearVelocity)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);

      Assert::AreEqual(glm::vec2(-FLT_MAX, -FLT_MAX), rigidBody.getMinLinearVelocity());

      rigidBody.setMinLinearVelocity(glm::vec2(-1, -2));

      Assert::AreEqual(glm::vec2(-1, -2), rigidBody.getMinLinearVelocity());

      rigidBody.setMinLinearVelocity(glm::vec2(1, 2.2f));

      Assert::AreEqual(glm::vec2(1, 2.2f), rigidBody.getMinLinearVelocity());
    }

#pragma endregion

#pragma region Set Max Linear Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_SetMaxLinearVelocity_UpdatesMinLinearVelocity)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);

      Assert::AreEqual(glm::vec2(FLT_MAX, FLT_MAX), rigidBody.getMaxLinearVelocity());

      rigidBody.setMaxLinearVelocity(glm::vec2(-1, -2));

      Assert::AreEqual(glm::vec2(-1, -2), rigidBody.getMaxLinearVelocity());

      rigidBody.setMaxLinearVelocity(glm::vec2(1, 2.2f));

      Assert::AreEqual(glm::vec2(1, 2.2f), rigidBody.getMaxLinearVelocity());
    }

#pragma endregion

#pragma region Set Angular Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_SetAngularVelocity_IsClampedByMinAndMax)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);
      rigidBody.setMinAngularVelocity(-0.4f);
      rigidBody.setMaxAngularVelocity(2);
      rigidBody.setAngularVelocity(-0.9f);

      Assert::AreEqual(-0.4f, rigidBody.getAngularVelocity());

      rigidBody.setAngularVelocity(1.1f);

      Assert::AreEqual(1.1f, rigidBody.getAngularVelocity());

      rigidBody.setAngularVelocity(2.6f);

      Assert::AreEqual(2.0f, rigidBody.getAngularVelocity());
    }

#pragma endregion

#pragma region Set Min Angular Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_SetMinAngularVelocity_UpdatesMinAngularVelocity)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);

      Assert::AreEqual(-FLT_MAX, rigidBody.getMinAngularVelocity());

      rigidBody.setMinAngularVelocity(-1);

      Assert::AreEqual(-1.0f, rigidBody.getMinAngularVelocity());

      rigidBody.setMinAngularVelocity(1);

      Assert::AreEqual(1.0f, rigidBody.getMinAngularVelocity());
    }

#pragma endregion

#pragma region Set Max Angular Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_SetMaxAngularVelocity_UpdatesMaxAngularVelocity)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);

      Assert::AreEqual(FLT_MAX, rigidBody.getMaxAngularVelocity());

      rigidBody.setMaxAngularVelocity(-1);

      Assert::AreEqual(-1.0f, rigidBody.getMaxAngularVelocity());

      rigidBody.setMaxAngularVelocity(1);

      Assert::AreEqual(1.0f, rigidBody.getMaxAngularVelocity());
    }

#pragma endregion

#pragma region Increment Linear Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IncrementLinearVelocity_Vec2Input_AppliesLinearVelocityDelta)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);
      
      Assert::AreEqual(glm::vec2(), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(glm::vec2(1, -1));

      Assert::AreEqual(glm::vec2(1, -1), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(glm::vec2(0.1f, 2));

      Assert::AreEqual(glm::vec2(1.1f, 1), rigidBody.getLinearVelocity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IncrementLinearVelocity_Vec2Input_IsClampedByMinAndMaxLinearVelocities)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);
      rigidBody.setMinLinearVelocity(glm::vec2(-1, -0.5f));
      rigidBody.setMaxLinearVelocity(glm::vec2(1.1f, 2));

      Assert::AreEqual(glm::vec2(), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(glm::vec2(2, -1));

      Assert::AreEqual(glm::vec2(1.1f, -0.5f), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(glm::vec2(0.1f, -2));

      Assert::AreEqual(glm::vec2(1.1f, -0.5f), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(glm::vec2(-3, 3));

      Assert::AreEqual(glm::vec2(-1, 2), rigidBody.getLinearVelocity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IncrementLinearVelocity_DoubleFloatInput_AppliesLinearVelocityDelta)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);

      Assert::AreEqual(glm::vec2(), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(1, -1);

      Assert::AreEqual(glm::vec2(1, -1), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(0.1f, 2);

      Assert::AreEqual(glm::vec2(1.1f, 1), rigidBody.getLinearVelocity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IncrementLinearVelocity_DoubleFloatInput_IsClampedByMinAndMaxLinearVelocities)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);
      rigidBody.setMinLinearVelocity(glm::vec2(-1, -0.5f));
      rigidBody.setMaxLinearVelocity(glm::vec2(1.1f, 2));

      Assert::AreEqual(glm::vec2(), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(2, -1);

      Assert::AreEqual(glm::vec2(1.1f, -0.5f), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(0.1f, -2);

      Assert::AreEqual(glm::vec2(1.1f, -0.5f), rigidBody.getLinearVelocity());

      rigidBody.incrementLinearVelocity(-3, 3);

      Assert::AreEqual(glm::vec2(-1, 2), rigidBody.getLinearVelocity());
    }

#pragma endregion

#pragma region Increment Angular Velocity Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IncrementAngularVelocity_AppliesLinearVelocityDelta)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);

      Assert::AreEqual(0.0f, rigidBody.getAngularVelocity());

      rigidBody.incrementAngularVelocity(1);

      Assert::AreEqual(1.0f, rigidBody.getAngularVelocity());

      rigidBody.incrementAngularVelocity(-0.1f);

      Assert::AreEqual(0.9f, rigidBody.getAngularVelocity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RigidBody2D_IncrementAngularVelocity_IsClampedByMinAndMaxAngularVelocities)
    {
      GameObject gameObject;
      RigidBody2D rigidBody(gameObject);
      rigidBody.setMinAngularVelocity(-1);
      rigidBody.setMaxAngularVelocity(2.1f);

      Assert::AreEqual(0.0f, rigidBody.getAngularVelocity());

      rigidBody.incrementAngularVelocity(1);

      Assert::AreEqual(1.0f, rigidBody.getAngularVelocity());

      rigidBody.incrementAngularVelocity(-3);

      Assert::AreEqual(-1.0f, rigidBody.getAngularVelocity());

      rigidBody.incrementAngularVelocity(5);

      Assert::AreEqual(2.1f, rigidBody.getAngularVelocity());
    }

#pragma endregion
  };
}