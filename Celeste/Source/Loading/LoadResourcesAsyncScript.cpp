#include "Loading/LoadResourcesAsyncScript.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Screens/ScreenManager.h"


namespace Celeste
{
  REGISTER_SCRIPT(LoadResourcesAsyncScript, 1)

  //------------------------------------------------------------------------------------------------
  LoadResourcesAsyncScript::LoadResourcesAsyncScript()
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