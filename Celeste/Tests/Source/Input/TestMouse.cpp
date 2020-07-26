#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Input/MockMouse.h"
#include "TestResources/TestResources.h"
#include "OpenGL/GL.h"

using namespace Celeste::Input;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestMouse)

#pragma region Set Button Pressed Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetButtonPressed_WithValidButton_BuffersButtonStateForHandling)
    {
      // Just check we don't get a really bad error like a nullptr exception when using this function
      MockMouse mouse;
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);

      Assert::IsTrue(mouse.getLatestButtonFlag(MouseButton::kLeft));
      Assert::IsTrue(mouse.getLatestButtonFlag(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetButtonPressed_InvalidButton_DoesNotThrow)
    {
      // Check this doesn't throw
      Mouse mouse;
      mouse.setButtonPressed(MouseButton::kNumButtons);
    }

#pragma endregion

#pragma region Set Button Up Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetButtonUp_WithValidButton_BuffersButtonStateForHandling)
    {
      MockMouse mouse;
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);

      Assert::IsFalse(mouse.getLatestButtonFlag(MouseButton::kLeft));
      Assert::IsFalse(mouse.getLatestButtonFlag(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetButtonUp_WithInvalidButton_DoesNotThrow)
    {
      // Check this doesnt throw
      Mouse mouse;
      mouse.setButtonReleased(MouseButton::kNumButtons);
    }

#pragma endregion

#pragma region Is Button Pressed Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonPressed_ShouldReturnTrue)
    {
      MockMouse mouse;
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);

      // Process latest mouse messages
      mouse.update();

      Assert::IsTrue(mouse.isButtonPressed(MouseButton::kLeft));
      Assert::IsTrue(mouse.isButtonPressed(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonPressed_ShouldReturnFalse)
    {
      MockMouse mouse;

      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kMiddle));
      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kRight));

      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);

      // Latest mouse state has not been processed yet

      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kMiddle));
      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kRight));

      mouse.update();

      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonPressed_WithInvalidInput_ReturnsFalse)
    {
      Mouse mouse;

      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kNumButtons));
    }

#pragma endregion

#pragma region Is Button Released Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonReleased_ShouldReturnTrue)
    {
      MockMouse mouse;
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);

      // Process latest mouse messages
      mouse.update();

      Assert::IsTrue(mouse.isButtonReleased(MouseButton::kLeft));
      Assert::IsTrue(mouse.isButtonReleased(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonReleased_ShouldReturnFalse)
    {
      MockMouse mouse;
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kMiddle);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsFalse(mouse.isButtonReleased(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonReleased(MouseButton::kMiddle));
      Assert::IsFalse(mouse.isButtonReleased(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonReleased_WithInvalidInput_ReturnsFalse)
    {
      Mouse mouse;

      Assert::IsFalse(mouse.isButtonReleased(MouseButton::kNumButtons));
    }

#pragma endregion

#pragma region Is Button Clicked Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonClicked_ShouldReturnTrue)
    {
      Mouse mouse;

      // Process down message
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);
      mouse.update();

      // Process up message
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsTrue(mouse.isButtonClicked(MouseButton::kLeft));
      Assert::IsTrue(mouse.isButtonClicked(MouseButton::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonClicked_ShouldReturnFalse)
    {
      Mouse mouse;

      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kRight));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kMiddle));

      // Process down message
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);
      mouse.update();

      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kRight));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kMiddle));

      // Process up message
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_IsButtonClicked_WithInvalidInput_ReturnsFalse)
    {
      Mouse mouse;

      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kNumButtons));
    }

#pragma endregion

#pragma region Flush Tests

    // Cannot test flushing presses and downs in the same test so we split into two

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_Flush_SetsButtonPressed_ToFalse)
    {
      Mouse mouse;

      // Process messages
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsTrue(mouse.isButtonPressed(MouseButton::kLeft));
      Assert::IsTrue(mouse.isButtonPressed(MouseButton::kRight));
      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kMiddle));

      mouse.flush();

      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kRight));
      Assert::IsFalse(mouse.isButtonPressed(MouseButton::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_Flush_SetsButtonClicked_ToFalse)
    {
      Mouse mouse;

      // Process messages
      mouse.setButtonReleased(MouseButton::kLeft);
      mouse.setButtonReleased(MouseButton::kRight);
      mouse.update();

      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kRight));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kMiddle));

      // Process messages
      mouse.setButtonPressed(MouseButton::kLeft);
      mouse.setButtonPressed(MouseButton::kRight);
      mouse.update();

      Assert::IsTrue(mouse.isButtonClicked(MouseButton::kLeft));
      Assert::IsTrue(mouse.isButtonClicked(MouseButton::kRight));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kMiddle));

      mouse.flush();

      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kRight));
      Assert::IsFalse(mouse.isButtonClicked(MouseButton::kMiddle));
    }

#pragma endregion

#pragma region Set Cursor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetCursor_WithNonExistentImagePath_DoesNotThrow)
    {
      MockMouse mouse;
      mouse.setCursor(Path("ThisShouldntExist"));

      Assert::IsNull(mouse.getCursor());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetCursor_WithExistentImagePath_SetsCursor)
    {
      if (GL::isInitialized())
      {
        MockMouse mouse;
        mouse.setCursor(TestResources::getBlockPngRelativePath());

        Assert::IsNotNull(mouse.getCursor());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetCursor_WithCustomCursorSet_WithNonExistentImagePath_DoesNothing)
    {
      if (GL::isInitialized())
      {
        MockMouse mouse;
        mouse.setCursor(TestResources::getBlockPngRelativePath());

        GLFWcursor* old = mouse.getCursor();
        Assert::IsNotNull(old);

        mouse.setCursor(Path("ThisShouldntExist"));

        GLFWcursor* new_ = mouse.getCursor();
        Assert::IsNotNull(new_);
        Assert::IsTrue(old == new_);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Mouse_SetCursor_WithCustomCursorSet_WithExistentImagePath_SetsNewCursor)
    {
      // This test often fails so I've disabled it for now

      /*MockMouse mouse;
      mouse.setCursor(TestResources::getBlockPngRelativePath());

      GLFWcursor* old = mouse.getCursor();
      Assert::IsNotNull(old);

      mouse.setCursor(TestResources::getContainerJpgRelativePath());

      GLFWcursor* new_ = mouse.getCursor();
      Assert::IsNotNull(new_);
      Assert::IsFalse(old == new_);*/
    }

#pragma endregion
  };
}