#include "Loading/LoadResourcesAsyncScript.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Screens/ScreenManager.h"


namespace Celeste
{
  REGISTER_SCRIPT(LoadResourcesAsyncScript, 1)

  //------------------------------------------------------------------------------------------------
  LoadResourcesAsyncScript::LoadResourcesAsyncScript()
    /*m_loadingThread(nullptr)*/
  {
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::onUpdate(float secondsPerUpdate)
  {
    Inherited::onUpdate(secondsPerUpdate);

    /*if (m_loadingThread->joinable())*/
    {
      m_loadComplete.invoke();
      m_loadComplete.unsubscribeAll();

      setActive(false);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::onDeath()
  {
    Inherited::onDeath();

    m_loadComplete.unsubscribeAll();

    //if (m_loadingThread)
    {
      // Delete our allocated thread
      //delete m_loadingThread;
    }
  }
}