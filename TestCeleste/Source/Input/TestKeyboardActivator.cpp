#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/KeyboardActivator.h"
#include "Input/InputManager.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Objects/Component.h"
#include "Utils/ObjectUtils.h"
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
      GAMEOBJECT(gameObject);

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(KeyboardActivator::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<KeyboardActivator*>(component.get()));
      Assert::IsTrue(&gameObject == component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Constructor_SetsActivationKeyTo_GLFW_KEY_UNKNOWN)
    {
      KeyboardActivator kvScript;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, kvScript.getActivationKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Constructor_SetsDeactivationKeyTo_GLFW_KEY_UNKNOWN)
    {
      KeyboardActivator kvScript;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, kvScript.getDeactivationKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Constructor_SetsInputModeToToggle)
    {
      KeyboardActivator kvScript;

      Assert::IsTrue(kvScript.getInputMode() == InputMode::kToggle);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Constructor_SetsTargetToNull)
    {
      KeyboardActivator kvScript;

      Assert::IsNull(kvScript.getTarget());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_NullTarget_DoesNothing)
    {
      KeyboardActivator activation;
      activation.setActivationKey(GLFW_KEY_A);
      activation.setDeactivationKey(GLFW_KEY_D);

      Assert::IsTrue(activation.getActivationKey() > -1);
      Assert::IsTrue(activation.getDeactivationKey() > -1);
      Assert::IsNull(activation.getTarget());

      activation.handleInput();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_ActivationKeyAndDeactivationKeyLessThanZero_DoesNothing)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      Assert::IsTrue(activation->getActivationKey() < 0);
      Assert::IsTrue(activation->getDeactivationKey() < 0);
      AssertCel::IsActive(target);

      activation->handleInput();

      AssertCel::IsActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_Toggle_ActivationKeyLessThanZero_DoesNothing)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(false);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setDeactivationKey(GLFW_KEY_D);
      activation->setInputMode(InputMode::kToggle);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      Assert::IsTrue(activation->getActivationKey() < 0);
      Assert::AreEqual(GLFW_KEY_D, activation->getDeactivationKey());
      Assert::IsTrue(activation->getInputMode() == InputMode::kToggle);
      AssertCel::IsNotActive(target);

      activation->handleInput();

      AssertCel::IsNotActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_Toggle_ActivationKeySet_ActivatesTarget)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(false);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setActivationKey(GLFW_KEY_D);
      activation->setInputMode(InputMode::kToggle);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      Assert::AreEqual(GLFW_KEY_D, activation->getActivationKey());
      Assert::IsTrue(activation->getInputMode() == InputMode::kToggle);
      AssertCel::IsNotActive(target);

      simulateKeyTapped(GLFW_KEY_D);

      Assert::IsTrue(isKeyTapped(GLFW_KEY_D));

      activation->handleInput();

      AssertCel::IsActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_Toggle_DeactivationKeyLessThanZero_DoesNotDeactivateTarget)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(true);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setActivationKey(GLFW_KEY_D);
      activation->setInputMode(InputMode::kToggle);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      Assert::IsTrue(activation->getDeactivationKey() < 0);
      Assert::AreEqual(GLFW_KEY_D, activation->getActivationKey());
      Assert::IsTrue(activation->getInputMode() == InputMode::kToggle);
      AssertCel::IsActive(target);

      activation->handleInput();

      AssertCel::IsActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_Toggle_DeactivationKeySet_DeactivatesTarget)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(true);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setDeactivationKey(GLFW_KEY_D);
      activation->setInputMode(InputMode::kToggle);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      Assert::AreEqual(GLFW_KEY_D, activation->getDeactivationKey());
      Assert::IsTrue(activation->getInputMode() == InputMode::kToggle);
      AssertCel::IsActive(target);

      simulateKeyTapped(GLFW_KEY_D);

      Assert::IsTrue(isKeyTapped(GLFW_KEY_D));

      activation->handleInput();

      AssertCel::IsNotActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_ToggleMode_ActivationAndDeactivationKeysSet_InvertsTargetsActiveFlagWhenKeysPressed)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(false);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setActivationKey(GLFW_KEY_D);
      activation->setDeactivationKey(GLFW_KEY_A);
      activation->setInputMode(InputMode::kToggle);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      Assert::AreEqual(GLFW_KEY_D, activation->getActivationKey());
      Assert::AreEqual(GLFW_KEY_A, activation->getDeactivationKey());
      Assert::IsTrue(activation->getInputMode() == InputMode::kToggle);
      AssertCel::IsNotActive(target);

      simulateKeyTapped(GLFW_KEY_D);

      Assert::IsTrue(isKeyTapped(GLFW_KEY_D));

      activation->handleInput();

      AssertCel::IsActive(target);

      simulateKeyTapped(GLFW_KEY_A);

      Assert::IsTrue(isKeyTapped(GLFW_KEY_A));

      activation->handleInput();

      AssertCel::IsNotActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_Continuous_ActivationKeyNotSet_DoesNotActivateTarget)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(false);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setInputMode(InputMode::kContinuous);
      activation->setDeactivationKey(GLFW_KEY_A);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      AssertCel::IsNotActive(target);
      Assert::IsTrue(activation->getActivationKey() < 0);
      Assert::AreEqual(GLFW_KEY_A, activation->getDeactivationKey());

      activation->handleInput();

      AssertCel::IsNotActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_Continuous_ActivationKeySetAndDown_ActivatesTarget)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(false);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setInputMode(InputMode::kContinuous);
      activation->setActivationKey(GLFW_KEY_A);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      AssertCel::IsNotActive(target);
      Assert::AreEqual(GLFW_KEY_A, activation->getActivationKey());
      Assert::IsTrue(activation->getInputMode() == InputMode::kContinuous);

      simulateKeyPressed(GLFW_KEY_A);

      Assert::IsTrue(isKeyPressed(GLFW_KEY_A));

      activation->handleInput();

      AssertCel::IsActive(target);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_HandleInput_Continuous_ActivationKeySetAndNotDown_DeactivatesTarget)
    {
      GAMEOBJECT(gameObject);
      GAMEOBJECT(target);
      target.setActive(true);
      AutoDeallocator<KeyboardActivator> activation = gameObject.addComponent<KeyboardActivator>();
      activation->setInputMode(InputMode::kContinuous);
      activation->setActivationKey(GLFW_KEY_A);
      activation->setTarget(&target);

      Assert::IsTrue(&target == activation->getTarget());
      AssertCel::IsActive(target);
      Assert::AreEqual(GLFW_KEY_A, activation->getActivationKey());
      Assert::IsTrue(activation->getInputMode() == InputMode::kContinuous);
      Assert::IsFalse(isKeyPressed(GLFW_KEY_A));

      activation->handleInput();

      AssertCel::IsNotActive(target);
    }

#pragma endregion

#pragma region Die Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Die_SetsActivationKeyTo_GLFW_KEY_UNKNOWN)
    {
      KeyboardActivator activation;
      activation.setActivationKey(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, activation.getActivationKey());

      activation.die();

      Assert::AreEqual(GLFW_KEY_UNKNOWN, activation.getActivationKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Die_SetsDeactivationKeyTo_GLFW_KEY_UNKNOWN)
    {
      KeyboardActivator activation;
      activation.setDeactivationKey(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, activation.getDeactivationKey());

      activation.die();

      Assert::AreEqual(GLFW_KEY_UNKNOWN, activation.getDeactivationKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Die_SetsInputModeToToggle)
    {
      KeyboardActivator activation;
      activation.setInputMode(InputMode::kContinuous);

      Assert::IsTrue(InputMode::kContinuous == activation.getInputMode());

      activation.die();

      Assert::IsTrue(InputMode::kToggle == activation.getInputMode());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_Die_SetsTargetToNull)
    {
      KeyboardActivator activation;
      GAMEOBJECT(target);
      activation.setInputMode(InputMode::kContinuous);
      activation.setTarget(&target);

      Assert::IsNotNull(activation.getTarget());

      activation.die();

      Assert::IsNull(activation.getTarget());
    }

#pragma endregion

#pragma region Set Target Tests

#pragma region Game Object Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_SetTarget_SetsTargetToInputtedGameObject)
    {
      GAMEOBJECT(target1);
      GAMEOBJECT(target2);

      KeyboardActivator activator;

      Assert::IsNull(activator.getTarget());

      activator.setTarget(&target1);

      Assert::IsTrue(&target1 == activator.getTarget());

      activator.setTarget(&target2);

      Assert::IsTrue(&target2 == activator.getTarget());

      activator.setTarget(nullptr);

      Assert::IsNull(activator.getTarget());
    }

#pragma endregion

#pragma region String Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_SetTarget_EmptyString_SetsTargetToNull)
    {
      Screen screen;
      GAMEOBJECT(target1);
      
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardActivator> activator = gameObject->addComponent<KeyboardActivator>();
      activator->setTarget(&target1);

      Assert::IsTrue(&target1 == activator->getTarget());

      activator->setTarget("");

      Assert::IsNull(activator->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_SetTarget_NonExistentGameObjectStringName_SetsTargetToNull)
    {
      Screen screen;
      GAMEOBJECT(target1);

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardActivator> activator = gameObject->addComponent<KeyboardActivator>();
      activator->setTarget(&target1);

      Assert::IsTrue(&target1 == activator->getTarget());
      Assert::IsNull(screen.findGameObject("WubbaLubbaDubDub"));

      activator->setTarget("WubbaLubbaDubDub");

      Assert::IsNull(activator->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_SetTarget_ExistentGameObjectStringName_SetsTargetToCorrectGameObject)
    {
      Screen screen;
      GAMEOBJECT(target1);

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardActivator> activator = gameObject->addComponent<KeyboardActivator>();
      activator->setTarget(&target1);
      AutoDeallocator<GameObject> newTarget = screen.allocateGameObject();
      newTarget->setName("NewTarget");

      Assert::IsTrue(&target1 == activator->getTarget());
      Assert::IsTrue(newTarget.get() == screen.findGameObject("NewTarget"));

      activator->setTarget("NewTarget");

      Assert::IsTrue(newTarget.get() == activator->getTarget());
    }

#pragma endregion

#pragma region StringId Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_SetTarget_ZeroStringId_SetsTargetToNull)
    {
      Screen screen;
      GAMEOBJECT(target1);

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardActivator> activator = gameObject->addComponent<KeyboardActivator>();
      activator->setTarget(&target1);

      Assert::IsTrue(&target1 == activator->getTarget());

      activator->setTarget(StringId(0));

      Assert::IsNull(activator->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_SetTarget_NonExistentGameObjectStringIdName_SetsTargetToNull)
    {
      Screen screen;
      GAMEOBJECT(target1);

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardActivator> activator = gameObject->addComponent<KeyboardActivator>();
      activator->setTarget(&target1);

      Assert::IsTrue(&target1 == activator->getTarget());
      Assert::IsNull(screen.findGameObject(internString("WubbaLubbaDubDub")));

      activator->setTarget(internString("WubbaLubbaDubDub"));

      Assert::IsNull(activator->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardActivator_SetTarget_ExistentGameObjectStringIdName_SetsTargetToCorrectGameObject)
    {
      Screen screen;
      GAMEOBJECT(target1);

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardActivator> activator = gameObject->addComponent<KeyboardActivator>();
      activator->setTarget(&target1);
      AutoDeallocator<GameObject> newTarget = screen.allocateGameObject();
      newTarget->setName("NewTarget");

      Assert::IsTrue(&target1 == activator->getTarget());
      Assert::AreEqual(newTarget.get(), screen.findGameObject(internString("NewTarget")));

      activator->setTarget(internString("NewTarget"));

      Assert::AreEqual(newTarget.get(), activator->getTarget());
    }

#pragma endregion

#pragma endregion

  };
}