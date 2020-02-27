#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/KeyboardVisibility.h"
#include "Input/InputManager.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "Screens/Screen.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "Utils/InputUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKeyboardVisibility)

    //------------------------------------------------------------------------------------------------
    void TestKeyboardVisibility::testInitialize()
    {
      // Flush the keyboard to avoid carrying over any changes we make in tests
      getKeyboard().flush();
    }

    //------------------------------------------------------------------------------------------------
    void TestKeyboardVisibility::testCleanup()
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

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(KeyboardVisibility::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<KeyboardVisibility*>(component.get()));
      Assert::IsTrue(&gameObject == component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Constructor_SetsVisibilityKeyTo_GLFW_KEY_UNKNOWN)
    {
      KeyboardVisibility kvScript;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, kvScript.getVisibilityKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Constructor_SetsInvisibilityKeyTo_GLFW_KEY_UNKNOWN)
    {
      KeyboardVisibility kvScript;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, kvScript.getInvisibilityKey());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Constructor_SetsInputModeToToggle)
    {
      KeyboardVisibility kvScript;

      Assert::IsTrue(kvScript.getInputMode() == InputMode::kToggle);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_Constructor_SetsTargetToNull)
    {
      KeyboardVisibility kvScript;

      Assert::IsNull(kvScript.getTarget());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_WithNoTarget_DoesNothing)
    {
      KeyboardVisibility kvScript;

      Assert::IsNull(kvScript.getTarget());

      kvScript.setInputMode(InputMode::kToggle);
      kvScript.setVisibilityKey(GLFW_KEY_A);
      kvScript.setInvisibilityKey(GLFW_KEY_D);
      kvScript.handleInput();  // Check this doesn't throw
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_TargetHasNoRenderer_DoesNothing)
    {
      KeyboardVisibility kvScript;
      GameObject target;
      kvScript.setTarget(&target);

      Assert::IsNotNull(kvScript.getTarget());
      AssertCel::DoesNotHaveComponent<Rendering::Renderer>(target);

      kvScript.setInputMode(InputMode::kToggle);
      kvScript.setVisibilityKey(GLFW_KEY_A);
      kvScript.setInvisibilityKey(GLFW_KEY_D);
      kvScript.handleInput();  // Check this doesn't throw
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_WithNeitherVisibilityOrInvisibilityKeySet_DoesNothing)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      renderer->setActive(false);
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setTarget(&target);

      Assert::IsTrue(&target == kvScript->getTarget());
      Assert::IsTrue(kvScript->getVisibilityKey() < 0);
      Assert::IsTrue(kvScript->getInvisibilityKey() < 0);
      AssertCel::IsNotActive(*renderer);

      kvScript->setInputMode(InputMode::kToggle);
      kvScript->handleInput();

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_ToggleMode_VisibilityKeyNotSet_DoesNotMakeTargetVisible)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      renderer->setActive(false);
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setInvisibilityKey(GLFW_KEY_D);
      kvScript->setInputMode(InputMode::kToggle);
      kvScript->setTarget(&target);

      Assert::IsTrue(&target == kvScript->getTarget());
      AssertCel::IsNotActive(*renderer);
      Assert::IsTrue(kvScript->getVisibilityKey() < 0);
      Assert::AreEqual(GLFW_KEY_D, kvScript->getInvisibilityKey());
      Assert::IsTrue(kvScript->getInputMode() == InputMode::kToggle);

      kvScript->handleInput();

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_ToggleMode_VisibilityKeySet_MakesTargetVisible)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      renderer->setActive(false);
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setVisibilityKey(GLFW_KEY_A);
      kvScript->setInvisibilityKey(GLFW_KEY_D);
      kvScript->setInputMode(InputMode::kToggle);
      kvScript->setTarget(&target);

      Assert::IsTrue(&target == kvScript->getTarget());
      AssertCel::IsNotActive(*renderer);
      Assert::AreEqual(GLFW_KEY_A, kvScript->getVisibilityKey());
      Assert::AreEqual(GLFW_KEY_D, kvScript->getInvisibilityKey());
      Assert::IsTrue(kvScript->getInputMode() == InputMode::kToggle);

      simulateKeyTapped(GLFW_KEY_A);
      kvScript->handleInput();

      AssertCel::IsActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_ToggleMode_InvisibilityKeyNotSet_DoesNotMakeTargetInvisible)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setVisibilityKey(GLFW_KEY_D);
      kvScript->setInputMode(InputMode::kToggle);
      kvScript->setTarget(&target);

      Assert::IsTrue(&target == kvScript->getTarget());
      AssertCel::IsActive(*renderer);
      Assert::IsTrue(kvScript->getInvisibilityKey() < 0);
      Assert::AreEqual(GLFW_KEY_D, kvScript->getVisibilityKey());
      Assert::IsTrue(kvScript->getInputMode() == InputMode::kToggle);

      kvScript->handleInput();

      AssertCel::IsActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_ToggleMode_InvisibilityKeySet_MakesTargetInvisible)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setInvisibilityKey(GLFW_KEY_A);
      kvScript->setVisibilityKey(GLFW_KEY_D);
      kvScript->setInputMode(InputMode::kToggle);
      kvScript->setTarget(&target);

      Assert::IsTrue(&target == kvScript->getTarget());
      AssertCel::IsActive(*renderer);
      Assert::AreEqual(GLFW_KEY_A, kvScript->getInvisibilityKey());
      Assert::AreEqual(GLFW_KEY_D, kvScript->getVisibilityKey());
      Assert::IsTrue(kvScript->getInputMode() == InputMode::kToggle);

      simulateKeyTapped(GLFW_KEY_A);
      kvScript->handleInput();

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_ToggleMode_VisibilityAndInvisibilityKeysSet_InvertsTargetShouldRenderFlagWhenKeysPressed)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      renderer->setActive(false);
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setInputMode(InputMode::kToggle);
      kvScript->setVisibilityKey(GLFW_KEY_A);
      kvScript->setInvisibilityKey(GLFW_KEY_D);
      kvScript->setTarget(&target);
      
      Assert::IsTrue(&target == kvScript->getTarget());
      Assert::IsTrue(kvScript->getInputMode() == InputMode::kToggle);
      AssertCel::IsNotActive(*renderer);

      // Toggle once
      {
        simulateKeyTapped(GLFW_KEY_A);

        Assert::IsTrue(getKeyboard().isKeyTapped(kvScript->getVisibilityKey()));

        kvScript->handleInput();

        AssertCel::IsActive(*renderer);
      }

      // Flush keyboard
      getKeyboard().flush();

      // Toggle again the other way back to the original setting
      {
        simulateKeyTapped(GLFW_KEY_D);

        Assert::IsTrue(getKeyboard().isKeyTapped(kvScript->getInvisibilityKey()));

        kvScript->handleInput();

        AssertCel::IsNotActive(*renderer);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_ContinuousMode_VisibilityKeyNotSet_DoesNotChangeTargetShouldRenderFlag)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      renderer->setActive(false);
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setInputMode(InputMode::kContinuous);
      kvScript->setInvisibilityKey(GLFW_KEY_A);
      kvScript->setTarget(&target);

      Assert::IsTrue(&target == kvScript->getTarget());
      AssertCel::IsNotActive(*renderer);
      Assert::IsTrue(kvScript->getInputMode() == InputMode::kContinuous);
      Assert::AreEqual(GLFW_KEY_A, kvScript->getInvisibilityKey());
      Assert::IsTrue(0 > kvScript->getVisibilityKey());

      kvScript->handleInput();

      AssertCel::IsNotActive(*renderer);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_HandleInput_ContinuousMode_VisibilityKeySet_TargetShouldRenderFlag_EqualsWhetherKeyPressed)
    {
      GameObject gameObject;
      GameObject target;
      AutoDeallocator<MockRenderer> renderer = target.addComponent<MockRenderer>();
      renderer->setActive(false);
      AutoDeallocator<KeyboardVisibility> kvScript = gameObject.addComponent<KeyboardVisibility>();
      kvScript->setInputMode(InputMode::kContinuous);
      kvScript->setVisibilityKey(GLFW_KEY_A);
      kvScript->setTarget(&target);

      Assert::IsTrue(&target == kvScript->getTarget());
      Assert::IsTrue(kvScript->getInputMode() == InputMode::kContinuous);
      AssertCel::IsNotActive(*renderer);

      // Toggle once
      {
        simulateKeyPressed(kvScript->getVisibilityKey());

        Assert::IsTrue(getKeyboard().isKeyPressed(kvScript->getVisibilityKey()));

        kvScript->handleInput();

        AssertCel::IsActive(*renderer);
      }

      // Flush keyboard
      getKeyboard().flush();

      // Toggle again the other way back to the original setting
      {
        simulateKeyReleased(kvScript->getVisibilityKey());

        Assert::IsFalse(getKeyboard().isKeyPressed(kvScript->getVisibilityKey()));

        kvScript->handleInput();

        AssertCel::IsNotActive(*renderer);
      }
    }

#pragma endregion

#pragma region Set Target Tests

#pragma region Game Object Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_SetTarget_SetsTargetToInputtedGameObject)
    {
      GameObject target1;
      GameObject target2;

      KeyboardVisibility visibility;

      Assert::IsNull(visibility.getTarget());

      visibility.setTarget(&target1);

      Assert::IsTrue(&target1 == visibility.getTarget());

      visibility.setTarget(&target2);

      Assert::IsTrue(&target2 == visibility.getTarget());

      visibility.setTarget(nullptr);

      Assert::IsNull(visibility.getTarget());
    }

#pragma endregion

#pragma region String Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_SetTarget_EmptyString_SetsTargetToNull)
    {
      Screen screen;
      GameObject target1;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardVisibility> visibility = gameObject->addComponent<KeyboardVisibility>();
      visibility->setTarget(&target1);

      Assert::IsTrue(&target1 == visibility->getTarget());

      visibility->setTarget("");

      Assert::IsNull(visibility->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_SetTarget_NonExistentGameObjectStringName_SetsTargetToNull)
    {
      Screen screen;
      GameObject target1;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardVisibility> visibility = gameObject->addComponent<KeyboardVisibility>();
      visibility->setTarget(&target1);

      Assert::IsTrue(&target1 == visibility->getTarget());
      Assert::IsNull(screen.findGameObject("WubbaLubbaDubDub"));

      visibility->setTarget("WubbaLubbaDubDub");

      Assert::IsNull(visibility->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_SetTarget_ExistentGameObjectStringName_SetsTargetToCorrectGameObject)
    {
      Screen screen;
      GameObject target1;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardVisibility> visibility = gameObject->addComponent<KeyboardVisibility>();
      visibility->setTarget(&target1);
      AutoDeallocator<GameObject> newTarget = screen.allocateGameObject();
      newTarget->setName("NewTarget");

      Assert::IsTrue(&target1 == visibility->getTarget());
      Assert::IsTrue(newTarget.get() == screen.findGameObject("NewTarget"));

      visibility->setTarget("NewTarget");

      Assert::IsTrue(newTarget.get() == visibility->getTarget());
    }

#pragma endregion

#pragma region StringId Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_SetTarget_ZeroStringId_SetsTargetToNull)
    {
      Screen screen;
      GameObject target1;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardVisibility> visibility = gameObject->addComponent<KeyboardVisibility>();
      visibility->setTarget(&target1);

      Assert::IsTrue(&target1 == visibility->getTarget());

      visibility->setTarget(StringId(0));

      Assert::IsNull(visibility->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_SetTarget_NonExistentGameObjectStringIdName_SetsTargetToNull)
    {
      Screen screen;
      GameObject target1;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardVisibility> visibility = gameObject->addComponent<KeyboardVisibility>();
      visibility->setTarget(&target1);

      Assert::IsTrue(&target1 == visibility->getTarget());
      Assert::IsNull(screen.findGameObject(internString("WubbaLubbaDubDub")));

      visibility->setTarget(internString("WubbaLubbaDubDub"));

      Assert::IsNull(visibility->getTarget());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibility_SetTarget_ExistentGameObjectStringIdName_SetsTargetToCorrectGameObject)
    {
      Screen screen;
      GameObject target1;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<KeyboardVisibility> visibility = gameObject->addComponent<KeyboardVisibility>();
      visibility->setTarget(&target1);
      AutoDeallocator<GameObject> newTarget = screen.allocateGameObject();
      newTarget->setName("NewTarget");

      Assert::IsTrue(&target1 == visibility->getTarget());
      Assert::AreEqual(newTarget.get(), screen.findGameObject(internString("NewTarget")));

      visibility->setTarget(internString("NewTarget"));

      Assert::AreEqual(newTarget.get(), visibility->getTarget());
    }

#pragma endregion

#pragma endregion

  };
}