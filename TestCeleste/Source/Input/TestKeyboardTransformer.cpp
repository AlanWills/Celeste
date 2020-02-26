#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Input/MockKeyboardTransformer.h"
#include "Input/InputManager.h"
#include "Registries/ComponentRegistry.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKeyboardTransformer)

    //------------------------------------------------------------------------------------------------
    void TestKeyboardTransformer::testInitialize()
    {
      // Make sure we clean up keyboard state
      getKeyboard().flush();
    }

    //------------------------------------------------------------------------------------------------
    void TestKeyboardTransformer::testCleanup()
    {
      // Make sure we clean up keyboard state
      getKeyboard().flush();
    }

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<KeyboardTransformer>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_IsAllocatableFromComponentRegistry)
    {
      GAMEOBJECT(gameObject);

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(KeyboardTransformer::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<KeyboardTransformer*>(component.get()));
      Assert::IsTrue(&gameObject == component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_Constructor_SetsDefaultValues)
    {
      MockKeyboardTransformer kmScript;
      
      Assert::AreEqual(GLFW_KEY_A, kmScript.getTranslateLeftKey());
      Assert::AreEqual(GLFW_KEY_D, kmScript.getTranslateRightKey());
      Assert::AreEqual(GLFW_KEY_W, kmScript.getTranslateUpKey());
      Assert::AreEqual(GLFW_KEY_S, kmScript.getTranslateDownKey());
      Assert::AreEqual(GLFW_KEY_Q, kmScript.getRotateLeftKey());
      Assert::AreEqual(GLFW_KEY_E, kmScript.getRotateRightKey());
      Assert::AreEqual(1.0f, kmScript.getTranslationSpeed());
      Assert::AreEqual(0.01f, kmScript.getRotationSpeed());
      Assert::IsNull(kmScript.getTransform());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_ResetsDirectionVector)
    {
      MockKeyboardTransformer kmScript;

      kmScript.setDirectionVector_Public(glm::vec2(1, -1));
      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateLeftKeyPressed_ShouldRaiseLeftMovement)
    {
      MockKeyboardTransformer kmScript;

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getTranslateLeftKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(-1, 0), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateLeftKeyPressed_ShouldRaiseLeftMovement)
    {
      MockKeyboardTransformer kmScript;
      kmScript.setTranslateLeftKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getTranslateLeftKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(-1, 0), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateUpKeyPressed_ShouldRaiseUpMovement)
    {
      MockKeyboardTransformer kmScript;

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getTranslateUpKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(0, 1), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateUpKeyPressed_ShouldRaiseUpMovement)
    {
      MockKeyboardTransformer kmScript;
      kmScript.setTranslateUpKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getTranslateUpKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(0, 1), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateRightKeyPressed_ShouldRaiseRightMovement)
    {
      MockKeyboardTransformer kmScript;

      // Simulate a key down
      getKeyboard().setKeyPressed(kmScript.getTranslateRightKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(1, 0), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateRightKeyPressed_ShouldRaiseRightMovement)
    {
      MockKeyboardTransformer kmScript;
      kmScript.setTranslateRightKey(GLFW_KEY_U);

      // Simulate a key down
      getKeyboard().setKeyPressed(kmScript.getTranslateRightKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(1, 0), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateDownKeyPressed_ShouldRaiseDownMovement)
    {
      MockKeyboardTransformer kmScript;

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getTranslateDownKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(0, -1), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateDownKeyPressed_ShouldRaiseDownMovement)
    {
      MockKeyboardTransformer kmScript;
      kmScript.setTranslateDownKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getTranslateDownKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(0, -1), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultRotateLeftKeyPressed_ShouldCauseLeftRotation)
    {
      MockKeyboardTransformer kmScript;

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getRotateLeftKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(-1.0f, kmScript.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomRotateLeftKeyPressed_ShouldCauseLeftRotation)
    {
      MockKeyboardTransformer kmScript;
      kmScript.setRotateLeftKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getRotateLeftKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(-1.0f, kmScript.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultRotateRightKeyPressed_ShouldCauseRightRotation)
    {
      MockKeyboardTransformer kmScript;

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getRotateRightKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(1.0f, kmScript.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomRotateRightKeyPressed_ShouldCauseRightRotation)
    {
      MockKeyboardTransformer kmScript;
      kmScript.setRotateRightKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(kmScript.getRotateRightKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(1.0f, kmScript.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithMultipleTranslationKeysDownInSameAxis_Sum)
    {
      MockKeyboardTransformer kmScript;

      // Simulate keys down
      getKeyboard().setKeyPressed(kmScript.getTranslateDownKey());
      getKeyboard().setKeyPressed(kmScript.getTranslateUpKey());
      getKeyboard().setKeyPressed(kmScript.getTranslateLeftKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(glm::vec2(-1, 0), kmScript.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithMultipleRotationKeysDown_Sum)
    {
      MockKeyboardTransformer kmScript;

      // Simulate keys down
      getKeyboard().setKeyPressed(kmScript.getRotateLeftKey());
      getKeyboard().setKeyPressed(kmScript.getRotateRightKey());
      getKeyboard().handleInput();

      kmScript.handleInput();

      Assert::AreEqual(0.0f, kmScript.getRotationDelta_Public());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_Update_WithNullTransform_DoesNotThrow)
    {
      MockKeyboardTransformer kmScript;

      Assert::IsNull(kmScript.getTransform());

      kmScript.update(0);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_Update_WithTransform_AppliesRotationScaledWithTime)
    {
      GAMEOBJECT(gameObject);

      AutoDeallocator<MockKeyboardTransformer> kmScript = gameObject.addComponent<MockKeyboardTransformer>();
      kmScript->setRotationSpeed(2);

      Assert::IsNotNull(kmScript->getTransform());

      kmScript->setRotationDelta_Public(1);
      kmScript->update(2);

      Assert::AreEqual(4.0f, gameObject.getTransform()->getRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_Update_WithTransform_AppliesDirectionVectorScaledWithTime)
    {
      GAMEOBJECT(gameObject);
      gameObject.getTransform()->setRotation(glm::half_pi<float>());  // Rotate the transform local space to show that the movement is locally

      AutoDeallocator<MockKeyboardTransformer> kmScript = gameObject.addComponent<MockKeyboardTransformer>();
      kmScript->setTranslationSpeed(2);

      Assert::IsNotNull(kmScript->getTransform());

      kmScript->setDirectionVector_Public(glm::vec2(0.5f, -1));
      kmScript->update(2);

      AssertExt::AreAlmostEqual(glm::vec3(-4, -2, 0), gameObject.getTransform()->getTranslation(), 0.0001f);
    }

#pragma endregion

  };
}