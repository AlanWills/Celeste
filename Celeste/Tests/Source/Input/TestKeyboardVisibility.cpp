#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Input/KeyboardVisibility.h"
#include "Input/InputManager.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "TestUtils/Utils/InputUtils.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKeyboardVisibility)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    // Flush the keyboard to avoid carrying over any changes we make in tests
    getKeyboard().flush();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    // Flush the keyboard to avoid carrying over any changes we make in tests
    getKeyboard().flush();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibility_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<KeyboardVisibility>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibility_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(KeyboardVisibility::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<KeyboardVisibility*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Constructor_SetsVisibilityKeyTo_GLFW_KEY_UNKNOWN)
    {
      GameObject gameObject;
      KeyboardVisibility keyboardVisibility(gameObject);

      Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardVisibility.getVisibilityKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Constructor_SetsInvisibilityKeyTo_GLFW_KEY_UNKNOWN)
    {
      GameObject gameObject;
      KeyboardVisibility keyboardVisibility(gameObject);

      Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardVisibility.getInvisibilityKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Constructor_SetsInputModeToToggle)
    {
      GameObject gameObject;
      KeyboardVisibility keyboardVisibility(gameObject);

      Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_TargetHasNoRenderer_DoesNothing)
    {
      GameObject gameObject;
      KeyboardVisibility keyboardVisibility(gameObject);
      
      AssertCel::DoesNotHaveComponent<Rendering::Renderer>(gameObject);

      keyboardVisibility.setInputMode(InputMode::kToggle);
      keyboardVisibility.setVisibilityKey(GLFW_KEY_A);
      keyboardVisibility.setInvisibilityKey(GLFW_KEY_D);
      keyboardVisibility.update(0);  // Check this doesn't throw
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_WithNeitherVisibilityOrInvisibilityKeySet_DoesNothing)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      renderer->setActive(false);
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();

      Assert::IsTrue(keyboardVisibility->getVisibilityKey() < 0);
      Assert::IsTrue(keyboardVisibility->getInvisibilityKey() < 0);
      AssertCel::IsNotActive(*renderer);

      keyboardVisibility->setInputMode(InputMode::kToggle);
      keyboardVisibility->update(0);

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_ToggleMode_VisibilityKeyNotSet_DoesNotMakeTargetVisible)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      renderer->setActive(false);
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();
      keyboardVisibility->setInvisibilityKey(GLFW_KEY_D);
      keyboardVisibility->setInputMode(InputMode::kToggle);

      AssertCel::IsNotActive(*renderer);
      Assert::IsTrue(keyboardVisibility->getVisibilityKey() < 0);
      Assert::AreEqual(GLFW_KEY_D, keyboardVisibility->getInvisibilityKey());
      Assert::IsTrue(keyboardVisibility->getInputMode() == InputMode::kToggle);

      keyboardVisibility->update(0);

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_ToggleMode_VisibilityKeySet_MakesTargetVisible)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      renderer->setActive(false);
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();
      keyboardVisibility->setVisibilityKey(GLFW_KEY_A);
      keyboardVisibility->setInvisibilityKey(GLFW_KEY_D);
      keyboardVisibility->setInputMode(InputMode::kToggle);

      AssertCel::IsNotActive(*renderer);
      Assert::AreEqual(GLFW_KEY_A, keyboardVisibility->getVisibilityKey());
      Assert::AreEqual(GLFW_KEY_D, keyboardVisibility->getInvisibilityKey());
      Assert::IsTrue(keyboardVisibility->getInputMode() == InputMode::kToggle);

      simulateKeyTapped(GLFW_KEY_A);
      keyboardVisibility->update(0);

      AssertCel::IsActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_ToggleMode_InvisibilityKeyNotSet_DoesNotMakeTargetInvisible)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();
      keyboardVisibility->setVisibilityKey(GLFW_KEY_D);
      keyboardVisibility->setInputMode(InputMode::kToggle);

      AssertCel::IsActive(*renderer);
      Assert::IsTrue(keyboardVisibility->getInvisibilityKey() < 0);
      Assert::AreEqual(GLFW_KEY_D, keyboardVisibility->getVisibilityKey());
      Assert::IsTrue(keyboardVisibility->getInputMode() == InputMode::kToggle);

      keyboardVisibility->update(0);

      AssertCel::IsActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_ToggleMode_InvisibilityKeySet_MakesTargetInvisible)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();
      keyboardVisibility->setInvisibilityKey(GLFW_KEY_A);
      keyboardVisibility->setVisibilityKey(GLFW_KEY_D);
      keyboardVisibility->setInputMode(InputMode::kToggle);

      AssertCel::IsActive(*renderer);
      Assert::AreEqual(GLFW_KEY_A, keyboardVisibility->getInvisibilityKey());
      Assert::AreEqual(GLFW_KEY_D, keyboardVisibility->getVisibilityKey());
      Assert::IsTrue(keyboardVisibility->getInputMode() == InputMode::kToggle);

      simulateKeyTapped(GLFW_KEY_A);
      keyboardVisibility->update(0);

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_ToggleMode_VisibilityAndInvisibilityKeysSet_InvertsTargetShouldRenderFlagWhenKeysPressed)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      renderer->setActive(false);
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();
      keyboardVisibility->setInputMode(InputMode::kToggle);
      keyboardVisibility->setVisibilityKey(GLFW_KEY_A);
      keyboardVisibility->setInvisibilityKey(GLFW_KEY_D);
      
      Assert::IsTrue(keyboardVisibility->getInputMode() == InputMode::kToggle);
      AssertCel::IsNotActive(*renderer);

      // Toggle once
      {
        simulateKeyTapped(GLFW_KEY_A);

        Assert::IsTrue(getKeyboard().isKeyTapped(keyboardVisibility->getVisibilityKey()));

        keyboardVisibility->update(0);

        AssertCel::IsActive(*renderer);
      }

      // Flush keyboard
      getKeyboard().flush();

      // Toggle again the other way back to the original setting
      {
        simulateKeyTapped(GLFW_KEY_D);

        Assert::IsTrue(getKeyboard().isKeyTapped(keyboardVisibility->getInvisibilityKey()));

        keyboardVisibility->update(0);

        AssertCel::IsNotActive(*renderer);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_ContinuousMode_VisibilityKeyNotSet_DoesNotChangeTargetShouldRenderFlag)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      renderer->setActive(false);
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();
      keyboardVisibility->setInputMode(InputMode::kContinuous);
      keyboardVisibility->setInvisibilityKey(GLFW_KEY_A);

      AssertCel::IsNotActive(*renderer);
      Assert::IsTrue(keyboardVisibility->getInputMode() == InputMode::kContinuous);
      Assert::AreEqual(GLFW_KEY_A, keyboardVisibility->getInvisibilityKey());
      Assert::IsTrue(0 > keyboardVisibility->getVisibilityKey());

      keyboardVisibility->update(0);

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Update_ContinuousMode_VisibilityKeySet_TargetShouldRenderFlag_EqualsWhetherKeyPressed)
    {
      GameObject gameObject;
      observer_ptr<MockRenderer> renderer = gameObject.addComponent<MockRenderer>();
      renderer->setActive(false);
      observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject.addComponent<KeyboardVisibility>();
      keyboardVisibility->setInputMode(InputMode::kContinuous);
      keyboardVisibility->setVisibilityKey(GLFW_KEY_A);

      Assert::IsTrue(keyboardVisibility->getInputMode() == InputMode::kContinuous);
      AssertCel::IsNotActive(*renderer);

      // Toggle once
      {
        simulateKeyPressed(keyboardVisibility->getVisibilityKey());

        Assert::IsTrue(getKeyboard().isKeyPressed(keyboardVisibility->getVisibilityKey()));

        keyboardVisibility->update(0);

        AssertCel::IsActive(*renderer);
      }

      // Flush keyboard
      getKeyboard().flush();

      // Toggle again the other way back to the original setting
      {
        simulateKeyReleased(keyboardVisibility->getVisibilityKey());

        Assert::IsFalse(getKeyboard().isKeyPressed(keyboardVisibility->getVisibilityKey()));

        keyboardVisibility->update(0);

        AssertCel::IsNotActive(*renderer);
      }
    }

#pragma endregion

  };
}