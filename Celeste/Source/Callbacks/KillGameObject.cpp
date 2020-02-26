#include "Callbacks/KillGameObject.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Screens/Screen.h"


namespace Celeste
{
  REGISTER_CALLBACK(KillGameObject)

  //------------------------------------------------------------------------------------------------
  void KillGameObject::operator()(GameObject& gameObject, const std::string& arg)
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

    if (gameObject.getName() == arg)
    {
      // We want to kill the game object this callback has been called from
      if (gameObject.isAlive())
      {
        // But only kill it if it is alive
        gameObject.die();
      }
    }
    else
    {
      observer_ptr<GameObject> namedGameObject = gameObject.getScreen()->findGameObject(arg);
      if (namedGameObject == nullptr)
      {
        ASSERT_FAIL();
        return;
      }

      // The find function in the screen should only go through alive objects
      ASSERT(namedGameObject->isAlive());
      namedGameObject->die();
    }
  }
}