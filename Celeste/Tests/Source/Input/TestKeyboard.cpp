#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Input/MockKeyboard.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{		
  CELESTE_TEST_CLASS(TestKeyboard)

#pragma region Set Key Pressed Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_SetKeyPressed_WithValidKey_BuffersKeyStateForHandling)
		{
      MockKeyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_A < KEYBOARD_KEY_COUNT);
      
      keyboard.setKeyPressed(GLFW_KEY_A);
      
      Assert::IsTrue(keyboard.getLatestKeyState(GLFW_KEY_A));
		}

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_SetKeyPressed_WithInvalidKey_DoesNotThrow)
    {
      // Check this does not throw
      Keyboard keyboard;
      keyboard.setKeyPressed(-1);
      keyboard.setKeyPressed(KEYBOARD_KEY_COUNT + 2);
    }

#pragma endregion

#pragma region Set Key Released Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_SetKeyReleased_WithValidKey_BuffersKeyStateForHandling)
    {
      MockKeyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_A < KEYBOARD_KEY_COUNT);

      keyboard.setKeyReleased(GLFW_KEY_A);

      Assert::IsFalse(keyboard.getLatestKeyState(GLFW_KEY_A));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_SetKeyReleased_WithInvalidKey_DoesNotThrow)
    {
      // Check this does not throw
      Keyboard keyboard;
      keyboard.setKeyReleased(-1);
      keyboard.setKeyReleased(KEYBOARD_KEY_COUNT + 2);
    }

#pragma endregion

#pragma region Is Key Pressed Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyPressed_ShouldReturnTrue)
    {
      Keyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      // Process key down events
      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);
      keyboard.handleInput();

      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_SPACE));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyPressed_ShouldReturnFalse)
    {
      Keyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_SPACE));

      keyboard.handleInput();

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_C));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyPressed_WithInvalidKey_ReturnsFalse)
    {
      // Check this does not throw
      Keyboard keyboard;

      Assert::IsFalse(keyboard.isKeyPressed(-1));
      Assert::IsFalse(keyboard.isKeyPressed(KEYBOARD_KEY_COUNT + 2));
    }

#pragma endregion

#pragma region Is Key Released Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyReleased_ShouldReturnTrue)
    {
      Keyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      // Process key down events
      keyboard.setKeyReleased(GLFW_KEY_A);
      keyboard.setKeyReleased(GLFW_KEY_SPACE);
      keyboard.handleInput();

      Assert::IsTrue(keyboard.isKeyReleased(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyReleased(GLFW_KEY_SPACE));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyReleased_ShouldReturnFalse)
    {
      Keyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);
      keyboard.handleInput();

      Assert::IsFalse(keyboard.isKeyReleased(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyReleased(GLFW_KEY_SPACE));
      Assert::IsTrue(keyboard.isKeyReleased(GLFW_KEY_B));
      Assert::IsTrue(keyboard.isKeyReleased(GLFW_KEY_C));

      keyboard.setKeyReleased(GLFW_KEY_A);
      keyboard.setKeyReleased(GLFW_KEY_SPACE);
      // Haven't called handleInput() so release calls won't be processed

      Assert::IsFalse(keyboard.isKeyReleased(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyReleased(GLFW_KEY_SPACE));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyReleased_WithInvalidKey_ReturnsFalse)
    {
      // Check this does not throw
      Keyboard keyboard;

      Assert::IsFalse(keyboard.isKeyReleased(-1));
      Assert::IsFalse(keyboard.isKeyReleased(KEYBOARD_KEY_COUNT + 2));
    }

#pragma endregion

#pragma region Is Key Tapped Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyTapped_WithValidKey_ShouldReturnTrue)
    {
      Keyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      // Process key down events
      keyboard.setKeyReleased(GLFW_KEY_A);
      keyboard.setKeyReleased(GLFW_KEY_SPACE);
      keyboard.handleInput();

      // Process key up events
      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);
      keyboard.handleInput();

      Assert::IsTrue(keyboard.isKeyTapped(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyTapped(GLFW_KEY_SPACE));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyTapped_WithValidKey_ShouldReturnFalse)
    {
      Keyboard keyboard;

      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);
      Assert::IsTrue(GLFW_KEY_A >= 0);
      Assert::IsTrue(GLFW_KEY_SPACE < KEYBOARD_KEY_COUNT);

      // Process key down events
      keyboard.setKeyReleased(GLFW_KEY_A);
      keyboard.setKeyReleased(GLFW_KEY_SPACE);
      keyboard.handleInput();

      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_SPACE));
      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_C));

      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);

      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_SPACE));

      keyboard.handleInput();

      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_C));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_IsKeyTapped_WithInvalidKey_ReturnsFalse)
    {
      // Check this does not throw
      Keyboard keyboard;

      Assert::IsFalse(keyboard.isKeyTapped(-1));
      Assert::IsFalse(keyboard.isKeyTapped(KEYBOARD_KEY_COUNT + 2));
    }

#pragma endregion

#pragma region Flush Tests

    // We cannot test flushing presses and key downs in the same test, so we do it separately

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_Flush_IsKeyPressed_ShouldReturnFalse)
    {
      Keyboard keyboard;

      // Process key down messages
      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);
      keyboard.handleInput();

      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_SPACE));

      // Flush now so that all the above calls should now fail
      keyboard.flush();

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_C));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_Flush_IsKeyTapped_ShouldReturnFalse)
    {
      Keyboard keyboard;

      // Process key down messages
      keyboard.setKeyReleased(GLFW_KEY_A);
      keyboard.setKeyReleased(GLFW_KEY_SPACE);
      keyboard.handleInput();

      // Process key up messages
      keyboard.setKeyPressed(GLFW_KEY_A);
      keyboard.setKeyPressed(GLFW_KEY_SPACE);
      keyboard.handleInput();

      Assert::IsTrue(keyboard.isKeyTapped(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyTapped(GLFW_KEY_SPACE));

      // Flush now so that all the above calls should now fail
      keyboard.flush();
      
      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyTapped(GLFW_KEY_SPACE));
    }

#pragma endregion

#pragma region On Text Inputted Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_OnTextInputted_NoSubscribers_DoesNothing)
    {
      Keyboard keyboard;

      keyboard.onTextInputted('c');
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_OnTextInputted_WithSubscribers_TriggersEvent_AndPassesCorrectCharacter)
    {
      Keyboard keyboard;

      char character = '\0';
      auto f = [&character](char c) -> void { character = c; };

      keyboard.getTextInputtedEvent().subscribe(f);
      keyboard.onTextInputted('c');

      Assert::AreEqual('c', character);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_SubscribeToOnTextInputted_SubscribesToEvent)
    {
      Keyboard keyboard;

      bool called = false;
      auto f = [&called](char) -> void { called = true; };

      keyboard.getTextInputtedEvent().subscribe(f);
      keyboard.onTextInputted('c');

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_UnsubscribeToOnTextInputted_InputtingSubscribedEvent_UnsubscribesFromEvent)
    {
      Keyboard keyboard;

      bool called = false;
      auto f = [&called](char) -> void { called = true; };

      keyboard.getTextInputtedEvent().subscribe(f, "Test");
      keyboard.onTextInputted('c');

      Assert::IsTrue(called);

      called = false;
      keyboard.getTextInputtedEvent().unsubscribe("Test");
      keyboard.onTextInputted('c');

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_UnsubscribeToOnTextInputted_InputtingUnsubscribedEvent_DoesNothing)
    {
      Keyboard keyboard;
      keyboard.getTextInputtedEvent().unsubscribe("Wubba Lubba Dub Dub");
    }

#pragma endregion

#pragma region Key Pressed Event Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_KeyPressed_NoSubscribers_DoesNothing)
    {
      Keyboard keyboard;

      keyboard.setKeyPressed(GLFW_KEY_A);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_KeyPressed_WithSubscribers_TriggersEvent_AndPassesCorrectValue)
    {
      Keyboard keyboard;

      int key = -1;

      Assert::AreNotEqual(-1, GLFW_KEY_A);

      auto f = [&key](int keyPressed) -> void { key = keyPressed; };
      keyboard.getKeyPressedEvent().subscribe(f);
      keyboard.setKeyPressed(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_KeyPressed_MultipleTimes_WithSubscribers_TriggersEventForEachTime_AndPassesCorrectValue)
    {
      Keyboard keyboard;

      int key = -1;

      Assert::AreNotEqual(-1, GLFW_KEY_A);

      auto f = [&key](int keyPressed) -> void { key = keyPressed; };
      keyboard.getKeyPressedEvent().subscribe(f);
      keyboard.setKeyPressed(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key);

      key = -1;
      keyboard.setKeyPressed(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_SubscribeToKeyPressed_SubscribesToEvent)
    {
      Keyboard keyboard;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      keyboard.getKeyPressedEvent().subscribe(f);
      keyboard.setKeyPressed(GLFW_KEY_A);

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_UnsubscribeToKeyPressed_InputtingSubscribedEvent_UnsubscribesFromEvent)
    {
      Keyboard keyboard;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      keyboard.getKeyPressedEvent().subscribe(f, "Test");
      keyboard.setKeyPressed(GLFW_KEY_A);

      Assert::IsTrue(called);

      called = false;
      keyboard.getKeyPressedEvent().unsubscribe("Test");
      keyboard.setKeyPressed(GLFW_KEY_A);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_UnsubscribeToKeyPressed_InputtingUnSubscribedEvent_DoesNothing)
    {
      Keyboard keyboard;
      keyboard.getKeyPressedEvent().unsubscribe("Wubba Lubba Dub Dub");
    }

#pragma endregion

#pragma region Key Released Event Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_KeyReleased_NoSubscribers_DoesNothing)
    {
      Keyboard keyboard;

      keyboard.setKeyReleased(GLFW_KEY_A);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_KeyReleased_WithSubscribers_TriggersEvent_AndPassesCorrectValue)
    {
      Keyboard keyboard;

      int key = -1;

      Assert::AreNotEqual(-1, GLFW_KEY_A);

      auto f = [&key](int keyReleased) -> void { key = keyReleased; };
      keyboard.getKeyReleasedEvent().subscribe(f);
      keyboard.setKeyReleased(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_KeyReleased_MultipleCalls_WithSubscribers_TriggersEventForEachTime_AndPassesCorrectValue)
    {
      Keyboard keyboard;

      int key = -1;

      Assert::AreNotEqual(-1, GLFW_KEY_A);

      auto f = [&key](int keyReleased) -> void { key = keyReleased; };
      keyboard.getKeyReleasedEvent().subscribe(f);
      keyboard.setKeyReleased(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key);

      key = -1;
      keyboard.setKeyReleased(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_SubscribeToKeyReleased_SubscribesToEvent)
    {
      Keyboard keyboard;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      keyboard.getKeyReleasedEvent().subscribe(f);
      keyboard.setKeyReleased(GLFW_KEY_A);

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_UnsubscribeToKeyReleased_InputtingSubscribedEvent_UnsubscribesFromEvent)
    {
      Keyboard keyboard;

      bool called = false;
      auto f = [&called](int) -> void { called = true; };

      keyboard.getKeyReleasedEvent().subscribe(f, "Test");
      keyboard.setKeyReleased(GLFW_KEY_A);

      Assert::IsTrue(called);

      called = false;

      keyboard.getKeyReleasedEvent().unsubscribe("Test");
      keyboard.setKeyReleased(GLFW_KEY_A);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Keyboard_UnsubscribeToKeyReleased_InputtingUnSubscribedEvent_DoesNothing)
    {
      Keyboard keyboard;
      keyboard.getKeyReleasedEvent().unsubscribe("Wubba Lubba Dub Dub");
    }

#pragma endregion

	};
}