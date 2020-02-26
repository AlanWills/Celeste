#include "UtilityHeaders/UnitTestHeaders.h"

#include "Callbacks/KillScreen.h"
#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKillScreen);

#pragma region Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillScreen_Operator_InputtingNameForScreenWhichDoesntExist_DoesNothing)
  {
    Assert::IsNull(getScreenManager().findScreen("TestScreen"));

    // Check doesn't throw
    KillScreen()(GameObject(), "TestScreen");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillScreen_Operator_InputtingNameForScreenWhichDoesExist_KillsScreen)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    screen->setName("TestScreen");

    Assert::IsNotNull(getScreenManager().findScreen("TestScreen"));
    AssertCel::IsAlive(screen.get());

    KillScreen()(GameObject(), "TestScreen");

    AssertCel::IsNotAlive(screen.get());
  }

#pragma endregion
  };
}