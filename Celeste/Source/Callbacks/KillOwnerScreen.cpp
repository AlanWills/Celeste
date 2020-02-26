#include "Callbacks/KillOwnerScreen.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"


namespace Celeste
{
  REGISTER_CALLBACK(KillOwnerScreen)

  //------------------------------------------------------------------------------------------------
  void KillOwnerScreen::operator()(GameObject& gameObject, const std::string& arg)
  {
#if _DEBUG
    if (gameObject.getScreen() == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    gameObject.getScreen()->die();
  }
}