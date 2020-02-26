#include "Callbacks/ActivateGameObject.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"


namespace Celeste
{
  REGISTER_CALLBACK(ActivateGameObject)

  //------------------------------------------------------------------------------------------------
  void ActivateGameObject::operator()(GameObject& gameObject, const std::string& arg)
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
      gameObject.setActive(true);
    }
    else
    {
      observer_ptr<GameObject> namedGameObject = gameObject.getScreen()->findGameObject(arg);
      if (namedGameObject == nullptr)
      {
        ASSERT_FAIL();
        return;
      }

      namedGameObject->setActive(true);
    }
  }
}