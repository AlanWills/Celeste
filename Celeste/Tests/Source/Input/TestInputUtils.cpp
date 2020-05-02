#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Input/InputManager.h"
#include "Input/InputUtils.h"
#include "Game/Game.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestInputUtils)

    //------------------------------------------------------------------------------------------------
    void testInitialize()
    {
      getInputManager().getKeyboard().flush();
      getInputManager().getMouse().flush();
    }

#pragma region Get Input Manager Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_GetInputManager_ShouldReturnGameInputManager)
    {
      Assert::IsTrue(Game::current().getSystem<Input::InputManager>() == &getInputManager());
    }

#pragma endregion

#pragma region Get Keyboard Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_GetKeyboard_ShouldReturnInputManagerKeyboard)
    {
      Assert::IsTrue(&Game::current().getSystem<Input::InputManager>()->getKeyboard() == &getKeyboard());
    }

#pragma endregion

#pragma region Get Mouse Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_GetMouse_ShouldReturnInputManagerMouse)
    {
      Assert::IsTrue(&Game::current().getSystem<Input::InputManager>()->getMouse() == &getMouse());
    }

#pragma endregion

#pragma region Is Key Pressed Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyPressed_ShouldReturnTrue)
    {
      getInputManager().getKeyboard().setKeyPressed(GLFW_KEY_A);
      getInputManager().getKeyboard().update();

      Assert::IsTrue(isKeyPressed(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyReleased(GLFW_KEY_A);

      // Haven't handled input with keyboard yet so this should still return true
      Assert::IsTrue(isKeyPressed(GLFW_KEY_A));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyPressed_ShouldReturnFalse)
    {
      Assert::IsFalse(isKeyPressed(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyPressed(GLFW_KEY_A);

      // Haven't handled input yet
      Assert::IsFalse(isKeyPressed(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyReleased(GLFW_KEY_A);
      getInputManager().getKeyboard().update();

      // Haven't handled input yet
      Assert::IsFalse(isKeyPressed(GLFW_KEY_A));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyPressed_WithInvalidKey_ReturnsFalse)
    {
      Assert::IsFalse(isKeyPressed(KEYBOARD_KEY_COUNT + 2));
    }

#pragma endregion

#pragma region Is Key Released Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyReleased_ShouldReturnTrue)
    {
      Keyboard& keyboard = getKeyboard();

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      // Process key down events
      keyboard.setKeyReleased(GLFW_KEY_A);
      keyboard.setKeyReleased(GLFW_KEY_SPACE);
      keyboard.update();

      Assert::IsTrue(isKeyReleased(GLFW_KEY_A));
      Assert::IsTrue(isKeyReleased(GLFW_KEY_SPACE));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyReleased_ShouldReturnFalse)
    {
      Keyboard& keyboard = getKeyboard();

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);
      keyboard.update();

      Assert::IsFalse(isKeyReleased(GLFW_KEY_A));
      Assert::IsFalse(isKeyReleased(GLFW_KEY_SPACE));
      Assert::IsTrue(isKeyReleased(GLFW_KEY_B));
      Assert::IsTrue(isKeyReleased(GLFW_KEY_C));

      keyboard.setKeyReleased(GLFW_KEY_A);
      keyboard.setKeyReleased(GLFW_KEY_SPACE);
      // Haven't called handleInput() so release calls won't be processed

      Assert::IsFalse(isKeyReleased(GLFW_KEY_A));
      Assert::IsFalse(isKeyReleased(GLFW_KEY_SPACE));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyReleased_WithInvalidKey_ReturnsFalse)
    {
      // Check this does not throw
      Assert::IsFalse(isKeyReleased(-1));
      Assert::IsFalse(isKeyReleased(KEYBOARD_KEY_COUNT + 2));
    }

#pragma endregion

#pragma region Is Key Tapped Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyTapped_ShouldReturnTrue)
    {
      getInputManager().getKeyboard().setKeyReleased(GLFW_KEY_A);
      getInputManager().getKeyboard().update();
      getInputManager().getKeyboard().setKeyPressed(GLFW_KEY_A);

      // Haven't handled input yet
      Assert::IsFalse(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().update();

      Assert::IsTrue(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyPressed(GLFW_KEY_A);

      Assert::IsTrue(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyReleased(GLFW_KEY_A);

      // Haven't handled input yet
      Assert::IsTrue(isKeyTapped(GLFW_KEY_A));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyTapped_ShouldReturnFalse)
    {
      Assert::IsFalse(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyReleased(GLFW_KEY_A);

      Assert::IsFalse(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().update();

      Assert::IsFalse(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyPressed(GLFW_KEY_A);

      // Haven't handled input yet
      Assert::IsFalse(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().update();
      getInputManager().getKeyboard().update();

      Assert::IsFalse(isKeyTapped(GLFW_KEY_A));

      getInputManager().getKeyboard().setKeyReleased(GLFW_KEY_A);
      getInputManager().getKeyboard().update();

      Assert::IsFalse(isKeyTapped(GLFW_KEY_A));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsKeyTapped_WithInvalidKey_ReturnsFalse)
    {
      Assert::IsFalse(isKeyTapped(KEYBOARD_KEY_COUNT + 2));
    }

#pragma endregion

#pragma region Is Button Pressed Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonPressed_ShouldReturnTrue)
    {
      Mouse& mouse = getMouse();
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);

      // Process latest mouse messages
      mouse.update();

      Assert::IsTrue(isButtonPressed(MouseButton::kLeft));
      Assert::IsTrue(isButtonPressed(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonPressed_ShouldReturnFalse)
    {
      Mouse& mouse = getMouse();

      Assert::IsFalse(isButtonPressed(MouseButton::kLeft));
      Assert::IsFalse(isButtonPressed(MouseButton::kMiddle));
      Assert::IsFalse(isButtonPressed(MouseButton::kRight));

      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);

      // Latest mouse state has not been processed yet

      Assert::IsFalse(isButtonPressed(MouseButton::kLeft));
      Assert::IsFalse(isButtonPressed(MouseButton::kMiddle));
      Assert::IsFalse(isButtonPressed(MouseButton::kRight));

      mouse.update();

      Assert::IsFalse(isButtonPressed(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonPressed_WithInvalidInput_ReturnsFalse)
    {
      Assert::IsFalse(isButtonPressed(MouseButton::kNumButtons));
    }

#pragma endregion

#pragma region Is Button Released Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonReleased_ShouldReturnTrue)
    {
      Mouse& mouse = getMouse();
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);

      // Process latest mouse messages
      mouse.update();

      Assert::IsTrue(isButtonReleased(MouseButton::kLeft));
      Assert::IsTrue(isButtonReleased(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonReleased_ShouldReturnFalse)
    {
      Mouse& mouse = getMouse();
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kMiddle);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsFalse(isButtonReleased(MouseButton::kLeft));
      Assert::IsFalse(isButtonReleased(MouseButton::kMiddle));
      Assert::IsFalse(isButtonReleased(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonReleased_WithInvalidInput_ReturnsFalse)
    {
      Assert::IsFalse(isButtonReleased(MouseButton::kNumButtons));
    }

#pragma endregion

#pragma region Is Button Clicked Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonClicked_ShouldReturnTrue)
    {
      Mouse& mouse = getMouse();

      // Process down message
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);
      mouse.update();

      // Process up message
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsTrue(isButtonClicked(MouseButton::kLeft));
      Assert::IsTrue(isButtonClicked(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonClicked_ShouldReturnFalse)
    {
      Mouse& mouse = getMouse();

      Assert::IsFalse(isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(isButtonClicked(MouseButton::kRight));
      Assert::IsFalse(isButtonClicked(MouseButton::kMiddle));

      // Process down message
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);
      mouse.update();

      Assert::IsFalse(isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(isButtonClicked(MouseButton::kRight));
      Assert::IsFalse(isButtonClicked(MouseButton::kMiddle));

      // Process up message
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsFalse(isButtonClicked(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputUtils_IsButtonClicked_WithInvalidInput_ReturnsFalse)
    {
      Assert::IsFalse(isButtonClicked(MouseButton::kNumButtons));
    }

#pragma endregion

  };
}