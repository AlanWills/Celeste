#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/KeyboardActivator.h"
#include "Input/InputManager.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
#include "Objects/Component.h"
#include "Utils/InputUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKeyboardActivator)

  //------------------------------------------------------------------------------------------------
  void TestKeyboardActivator::testInitialize()
  {
    // Flush the keyboard to avoid carrying over any changes we make in tests
    getKeyboard().flush();
  }

  //------------------------------------------------------------------------------------------------
  void TestKeyboardActivator::testCleanup()
  {
    // Flush the keyboard to avoid carrying over any changes we make in tests
    getKeyboard().flush();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<KeyboardActivator>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(KeyboardActivator::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<KeyboardActivator*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_Constructor_SetsActivationKeyTo_GLFW_KEY_UNKNOWN)
  {
    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);

    Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardActivator.getActivationKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_Constructor_SetsDeactivationKeyTo_GLFW_KEY_UNKNOWN)
  {
    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);

    Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardActivator.getDeactivationKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_Constructor_SetsInputModeToToggle)
  {
    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);

    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kToggle);
  }

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_ActivationKeyAndDeactivationKeyLessThanZero_DoesNothing)
  {
    GameObject gameObject;
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();

    Assert::IsTrue(keyboardActivator->getActivationKey() < 0);
    Assert::IsTrue(keyboardActivator->getDeactivationKey() < 0);
    AssertCel::IsActive(gameObject);

    keyboardActivator->handleInput();

    AssertCel::IsActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_Toggle_ActivationKeyLessThanZero_DoesNothing)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setDeactivationKey(GLFW_KEY_D);
    keyboardActivator->setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardActivator->getActivationKey() < 0);
    Assert::AreEqual(GLFW_KEY_D, keyboardActivator->getDeactivationKey());
    Assert::IsTrue(keyboardActivator->getInputMode() == InputMode::kToggle);
    AssertCel::IsNotActive(gameObject);

    keyboardActivator->handleInput();

    AssertCel::IsNotActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_Toggle_ActivationKeySet_ActivatesGameObject)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setActivationKey(GLFW_KEY_D);
    keyboardActivator->setInputMode(InputMode::kToggle);

    Assert::AreEqual(GLFW_KEY_D, keyboardActivator->getActivationKey());
    Assert::IsTrue(keyboardActivator->getInputMode() == InputMode::kToggle);
    AssertCel::IsNotActive(gameObject);

    simulateKeyTapped(GLFW_KEY_D);

    Assert::IsTrue(isKeyTapped(GLFW_KEY_D));

    keyboardActivator->handleInput();

    AssertCel::IsActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_Toggle_DeactivationKeyLessThanZero_DoesNotDeactivateGameObject)
  {
    GameObject gameObject;
    gameObject.setActive(true);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setActivationKey(GLFW_KEY_D);
    keyboardActivator->setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardActivator->getDeactivationKey() < 0);
    Assert::AreEqual(GLFW_KEY_D, keyboardActivator->getActivationKey());
    Assert::IsTrue(keyboardActivator->getInputMode() == InputMode::kToggle);
    AssertCel::IsActive(gameObject);

    keyboardActivator->handleInput();

    AssertCel::IsActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_Toggle_DeactivationKeySet_DeactivatesGameObject)
  {
    GameObject gameObject;
    gameObject.setActive(true);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setDeactivationKey(GLFW_KEY_D);
    keyboardActivator->setInputMode(InputMode::kToggle);

    Assert::AreEqual(GLFW_KEY_D, keyboardActivator->getDeactivationKey());
    Assert::IsTrue(keyboardActivator->getInputMode() == InputMode::kToggle);
    AssertCel::IsActive(gameObject);

    simulateKeyTapped(GLFW_KEY_D);

    Assert::IsTrue(isKeyTapped(GLFW_KEY_D));

    keyboardActivator->handleInput();

    AssertCel::IsNotActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_ToggleMode_ActivationAndDeactivationKeysSet_InvertsGameObjectsActiveFlagWhenKeysPressed)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setActivationKey(GLFW_KEY_D);
    keyboardActivator->setDeactivationKey(GLFW_KEY_A);
    keyboardActivator->setInputMode(InputMode::kToggle);

    Assert::AreEqual(GLFW_KEY_D, keyboardActivator->getActivationKey());
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator->getDeactivationKey());
    Assert::IsTrue(keyboardActivator->getInputMode() == InputMode::kToggle);
    AssertCel::IsNotActive(gameObject);

    simulateKeyTapped(GLFW_KEY_D);

    Assert::IsTrue(isKeyTapped(GLFW_KEY_D));

    keyboardActivator->handleInput();

    AssertCel::IsActive(gameObject);

    simulateKeyTapped(GLFW_KEY_A);

    Assert::IsTrue(isKeyTapped(GLFW_KEY_A));

    keyboardActivator->handleInput();

    AssertCel::IsNotActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_Continuous_ActivationKeyNotSet_DoesNotActivateGameObject)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setInputMode(InputMode::kContinuous);
    keyboardActivator->setDeactivationKey(GLFW_KEY_A);

    AssertCel::IsNotActive(gameObject);
    Assert::IsTrue(keyboardActivator->getActivationKey() < 0);
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator->getDeactivationKey());

    keyboardActivator->handleInput();

    AssertCel::IsNotActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_Continuous_ActivationKeySetAndDown_ActivatesGameObject)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setInputMode(InputMode::kContinuous);
    keyboardActivator->setActivationKey(GLFW_KEY_A);

    AssertCel::IsNotActive(gameObject);
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator->getActivationKey());
    Assert::IsTrue(keyboardActivator->getInputMode() == InputMode::kContinuous);

    simulateKeyPressed(GLFW_KEY_A);

    Assert::IsTrue(isKeyPressed(GLFW_KEY_A));

    keyboardActivator->handleInput();

    AssertCel::IsActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivator_HandleInput_Continuous_ActivationKeySetAndNotDown_DeactivatesGameObject)
  {
    GameObject gameObject;
    gameObject.setActive(true);
    observer_ptr<KeyboardActivator> keyboardActivator = gameObject.addComponent<KeyboardActivator>();
    keyboardActivator->setInputMode(InputMode::kContinuous);
    keyboardActivator->setActivationKey(GLFW_KEY_A);

    AssertCel::IsActive(gameObject);
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator->getActivationKey());
    Assert::IsTrue(keyboardActivator->getInputMode() == InputMode::kContinuous);
    Assert::IsFalse(isKeyPressed(GLFW_KEY_A));

    keyboardActivator->handleInput();

    AssertCel::IsNotActive(gameObject);
  }

#pragma endregion

  };
}