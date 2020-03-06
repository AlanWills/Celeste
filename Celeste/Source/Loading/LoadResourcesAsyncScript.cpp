#include "Loading/LoadResourcesAsyncScript.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Screens/ScreenManager.h"


namespace Celeste
{
  REGISTER_UNMANAGED_COMPONENT(LoadResourcesAsyncScript, 1)

  //------------------------------------------------------------------------------------------------
  LoadResourcesAsyncScript::LoadResourcesAsyncScript(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::update(float secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    {
      m_loadComplete.invoke();
      m_loadComplete.unsubscribeAll();

      setActive(false);
    }
  }
}