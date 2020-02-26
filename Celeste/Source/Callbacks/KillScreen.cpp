#include "Callbacks/KillScreen.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"


namespace Celeste
{
  REGISTER_CALLBACK(KillScreen)

  //------------------------------------------------------------------------------------------------
  void KillScreen::operator()(GameObject&, const std::string& arg)
  {
    observer_ptr<Screen> namedScreen = getScreenManager().findScreen(arg);
    if (namedScreen == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    namedScreen->die();
  }
}