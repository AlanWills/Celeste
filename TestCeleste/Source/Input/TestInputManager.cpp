#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Input/MockKeyboard.h"
#include "Input/KeyboardActivator.h"
#include "Input/InputManager.h"
#include "AssertCel.h"
#include "KeyboardTextInputtedEventUnsubscriber.h"
#include "Objects/GameObject.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestInputManager)

    //------------------------------------------------------------------------------------------------
    void TestInputManager::testInitialize()
    {
      getInputManager().getKeyboard().flush();
      getInputManager().getMouse().flush();
    }

#pragma region Key Callback Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_KeyCallback_Pressed_SetsKeyPressed)
    {
      Assert::IsFalse(getInputManager().getKeyboard().isKeyPressed(GLFW_KEY_A));

      keyCallback(nullptr, GLFW_KEY_A, 0, GLFW_PRESS, 0);
      getInputManager().getKeyboard().handleInput();

      Assert::IsTrue(getInputManager().getKeyboard().isKeyPressed(GLFW_KEY_A));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_KeyCallback_Repeat_SetsKeyPressed)
    {
      Assert::IsFalse(getInputManager().getKeyboard().isKeyPressed(GLFW_KEY_A));

      keyCallback(nullptr, GLFW_KEY_A, 0, GLFW_REPEAT, 0);
      getInputManager().getKeyboard().handleInput();

      Assert::IsTrue(getInputManager().getKeyboard().isKeyPressed(GLFW_KEY_A));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_KeyCallback_Released_SetsKeyReleased)
    {
      getInputManager().getKeyboard().setKeyPressed(GLFW_KEY_A);
      getInputManager().getKeyboard().handleInput();

      Assert::IsTrue(getInputManager().getKeyboard().isKeyPressed(GLFW_KEY_A));

      keyCallback(nullptr, GLFW_KEY_A, 0, GLFW_RELEASE, 0);
      getInputManager().getKeyboard().handleInput();

      Assert::IsFalse(getInputManager().getKeyboard().isKeyPressed(GLFW_KEY_A));
    }

#pragma endregion

#pragma region Char Callback Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_CharCallback_CallsKeyboardOnTextInputted)
    {
      char c = '\0';
      auto f = [&c](char character) -> void { c = character; };
      KeyboardTextInputtedEventUnsubscriber unsub = getInputManager().getKeyboard().getTextInputtedEvent().subscribe(f);
      
      charCallback(nullptr, static_cast<unsigned int>('a'));

      Assert::AreEqual('a', c);
    }

#pragma endregion

#pragma region Mouse Button Callback Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Pressed_LeftMouseButton_SetsLeftMouseButtonPressed)
    {
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kLeft));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kLeft));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Pressed_MiddleMouseButton_SetsMiddleMouseButtonPressed)
    {
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kMiddle));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_MIDDLE, GLFW_PRESS, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kMiddle));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Pressed_RightMouseButton_SetsRightMouseButtonPressed)
    {
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kRight));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kRight));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Released_LeftMouseButton_SetsLeftMouseButtonReleased)
    {
      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kLeft));

      getMouse().setButtonPressed(MouseButton::kLeft);
      getMouse().handleInput();

      Assert::IsFalse(getMouse().isButtonReleased(MouseButton::kLeft));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonReleased(MouseButton::kLeft));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kLeft));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kLeft));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Released_MiddleMouseButton_SetsMiddleMouseButtonReleased)
    {
      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kMiddle));

      getMouse().setButtonPressed(MouseButton::kMiddle);
      getMouse().handleInput();

      Assert::IsFalse(getMouse().isButtonReleased(MouseButton::kMiddle));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_MIDDLE, GLFW_RELEASE, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonReleased(MouseButton::kMiddle));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kMiddle));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Released_RightMouseButton_SetsRightMouseButtonReleased)
    {
      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kRight));

      getMouse().setButtonPressed(MouseButton::kRight);
      getMouse().handleInput();

      Assert::IsFalse(getMouse().isButtonReleased(MouseButton::kRight));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_RIGHT, GLFW_RELEASE, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonReleased(MouseButton::kRight));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kRight));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonReleased(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Pressed_LeftMouseButton_SetsLeftMouseButtonClicked)
    {
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kLeft));
      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kLeft));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kLeft));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

      getMouse().handleInput();

      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kLeft));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Pressed_MiddleMouseButton_SetsMiddleMouseButtonClicked)
    {
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kMiddle));
      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kMiddle));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_MIDDLE, GLFW_PRESS, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kMiddle));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kMiddle));

      getMouse().handleInput();

      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputManager_MouseButtonCallback_Pressed_RightMouseButton_SetsRightMouseButtonClicked)
    {
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kRight));
      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kRight));

      mouseButtonCallback(nullptr, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, 0);

      // Handle input not called
      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kRight));

      getMouse().handleInput();

      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kRight));

      getMouse().handleInput();

      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kRight));
    }

#pragma endregion
  };
}