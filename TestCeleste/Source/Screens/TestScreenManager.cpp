#include "UtilityHeaders/UnitTestHeaders.h"

#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestScreenManager)

    //------------------------------------------------------------------------------------------------
    void TestScreenManager::testInitialize()
    {
      glfwMakeContextCurrent(nullptr);
    }

    //------------------------------------------------------------------------------------------------
    void TestScreenManager::testCleanup()
    {
      glfwMakeContextCurrent(getWindow()->getGLWindow());
    }

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScreenManager_Constructor_SetsValuesToDefault)
    {
      ScreenManager screenManager;

      Assert::IsNull(screenManager.getWindow());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScreenManager_Constructor_CreatesWindow)
    {
      ScreenManager screenManager;

      Assert::IsNotNull(screenManager.getWindow());
    }

#pragma endregion

#pragma region Find Screen Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScreenManager_FindScreen_InputtingNonExistentStringId_ReturnsNullHandle)
    {
      Assert::IsNull(getScreenManager().findScreen(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScreenManager_FindScreen_InputtingNonExistentString_ReturnsNullHandle)
    {
      Assert::IsNull(getScreenManager().findScreen("ThisNameShouldntExist"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScreenManager_FindScreen_InputtingExistentName_StringId_ReturnsScreenPtr)
    {
      // Have to use screens here rather than mock screens
      StringId name = internString("Test");
      AutoDeallocator<Screen> screen = Screen::allocate();
      screen->setName(name);

      Assert::AreEqual(screen.get(), getScreenManager().findScreen(name));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScreenManager_FindScreen_InputtingExistentName_String_ReturnsScreenPtr)
    {
      // Have to use screens here rather than mock screens
      AutoDeallocator<Screen> screen = Screen::allocate();
      screen->setName("Test");

      Assert::AreEqual(screen.get(), getScreenManager().findScreen("Test"));
    }

#pragma endregion
  };
}