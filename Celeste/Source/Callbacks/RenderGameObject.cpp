#include "Callbacks/RenderGameObject.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Rendering/Renderer.h"


namespace Celeste
{
  REGISTER_CALLBACK(RenderGameObject)

  //------------------------------------------------------------------------------------------------
  void RenderGameObject::operator()(GameObject& gameObject, const std::string& arg)
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

    observer_ptr<GameObject> namedGameObject = gameObject.getName() == arg ? &gameObject : gameObject.getScreen()->findGameObject(arg);
    if (namedGameObject == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    if (observer_ptr<Celeste::Rendering::Renderer> renderer = namedGameObject->findComponent<Celeste::Rendering::Renderer>(); renderer != nullptr)
    {
      renderer->setActive(true);
    }
  }
}