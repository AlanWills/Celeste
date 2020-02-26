#include "Callbacks/TransitionToScreen.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Screens/Loading/ScreenLoader.h"
#include "Resources/ResourceManager.h"


namespace Celeste
{
  REGISTER_CALLBACK(TransitionToScreen)

  //------------------------------------------------------------------------------------------------
  void TransitionToScreen::operator()(GameObject& gameObject, const std::string& arg)
  {
#if _DEBUG
    if (gameObject.getScreen() == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    if (arg.empty())
    {
      ASSERT_FAIL();
      return;
    }

    Path screenFile(Resources::getResourcesDirectory(), arg);
    if (!File::exists(screenFile))
    {
      ASSERT_FAIL();
      return;
    }

    gameObject.getScreen()->die();
    ScreenLoader::load(screenFile);
  }
}