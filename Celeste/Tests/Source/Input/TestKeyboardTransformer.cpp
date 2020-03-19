#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Input/MockKeyboardTransformer.h"
#include "Input/InputManager.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
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
      GameObject gameObject;

      observer_ptr<Component> component = ComponentRegistry::createComponent(KeyboardTransformer::type_name(), gameObject);

      Assert::IsNotNull(component);
      Assert::IsNotNull(dynamic_cast<KeyboardTransformer*>(component));
      Assert::IsTrue(&gameObject == component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_Constructor_SetsDefaultValues)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);
      
      Assert::AreEqual(GLFW_KEY_A, keyboardTransformer.getTranslateLeftKey());
      Assert::AreEqual(GLFW_KEY_D, keyboardTransformer.getTranslateRightKey());
      Assert::AreEqual(GLFW_KEY_W, keyboardTransformer.getTranslateUpKey());
      Assert::AreEqual(GLFW_KEY_S, keyboardTransformer.getTranslateDownKey());
      Assert::AreEqual(GLFW_KEY_Q, keyboardTransformer.getRotateLeftKey());
      Assert::AreEqual(GLFW_KEY_E, keyboardTransformer.getRotateRightKey());
      Assert::AreEqual(1.0f, keyboardTransformer.getTranslationSpeed());
      Assert::AreEqual(0.01f, keyboardTransformer.getRotationSpeed());
      Assert::AreEqual(gameObject.getTransform(), keyboardTransformer.getTransform());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_ResetsDirectionVector)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      keyboardTransformer.setDirectionVector_Public(glm::vec2(1, -1));
      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateLeftKeyPressed_ShouldRaiseLeftMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateLeftKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(-1, 0), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateLeftKeyPressed_ShouldRaiseLeftMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);
      keyboardTransformer.setTranslateLeftKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateLeftKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(-1, 0), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateUpKeyPressed_ShouldRaiseUpMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateUpKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(0, 1), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateUpKeyPressed_ShouldRaiseUpMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);
      keyboardTransformer.setTranslateUpKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateUpKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(0, 1), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateRightKeyPressed_ShouldRaiseRightMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate a key down
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateRightKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(1, 0), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateRightKeyPressed_ShouldRaiseRightMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);
      keyboardTransformer.setTranslateRightKey(GLFW_KEY_U);

      // Simulate a key down
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateRightKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(1, 0), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultTranslateDownKeyPressed_ShouldRaiseDownMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateDownKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(0, -1), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomTranslateDownKeyPressed_ShouldRaiseDownMovement)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);
      keyboardTransformer.setTranslateDownKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateDownKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(0, -1), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultRotateLeftKeyPressed_ShouldCauseLeftRotation)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getRotateLeftKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(-1.0f, keyboardTransformer.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomRotateLeftKeyPressed_ShouldCauseLeftRotation)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);
      keyboardTransformer.setRotateLeftKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getRotateLeftKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(-1.0f, keyboardTransformer.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithDefaultRotateRightKeyPressed_ShouldCauseRightRotation)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getRotateRightKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(1.0f, keyboardTransformer.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithCustomRotateRightKeyPressed_ShouldCauseRightRotation)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);
      keyboardTransformer.setRotateRightKey(GLFW_KEY_U);

      // Simulate a key down event
      getKeyboard().setKeyPressed(keyboardTransformer.getRotateRightKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(1.0f, keyboardTransformer.getRotationDelta_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithMultipleTranslationKeysDownInSameAxis_Sum)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate keys down
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateDownKey());
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateUpKey());
      getKeyboard().setKeyPressed(keyboardTransformer.getTranslateLeftKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(glm::vec2(-1, 0), keyboardTransformer.getDirectionVector_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_HandleInput_WithMultipleRotationKeysDown_Sum)
    {
      GameObject gameObject;
      MockKeyboardTransformer keyboardTransformer(gameObject);

      // Simulate keys down
      getKeyboard().setKeyPressed(keyboardTransformer.getRotateLeftKey());
      getKeyboard().setKeyPressed(keyboardTransformer.getRotateRightKey());
      getKeyboard().handleInput();

      keyboardTransformer.handleInput();

      Assert::AreEqual(0.0f, keyboardTransformer.getRotationDelta_Public());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_Update_WithTransform_AppliesRotationScaledWithTime)
    {
      GameObject gameObject;

      observer_ptr<MockKeyboardTransformer> keyboardTransformer = gameObject.addComponent<MockKeyboardTransformer>();
      keyboardTransformer->setRotationSpeed(2);

      Assert::IsNotNull(keyboardTransformer->getTransform());

      keyboardTransformer->setRotationDelta_Public(1);
      keyboardTransformer->update(2);

      Assert::AreEqual(4.0f, gameObject.getTransform()->getRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardTransformer_Update_WithTransform_AppliesDirectionVectorScaledWithTime)
    {
      GameObject gameObject;
      gameObject.getTransform()->setRotation(glm::half_pi<float>());  // Rotate the transform local space to show that the movement is locally

      observer_ptr<MockKeyboardTransformer> keyboardTransformer = gameObject.addComponent<MockKeyboardTransformer>();
      keyboardTransformer->setTranslationSpeed(2);

      Assert::IsNotNull(keyboardTransformer->getTransform());

      keyboardTransformer->setDirectionVector_Public(glm::vec2(0.5f, -1));
      keyboardTransformer->update(2);

      AssertExt::AreAlmostEqual(glm::vec3(-4, -2, 0), gameObject.getTransform()->getTranslation(), 0.0001f);
    }

#pragma endregion

  };
}