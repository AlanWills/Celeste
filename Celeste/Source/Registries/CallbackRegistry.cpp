#include "Registries/CallbackRegistry.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  CallbackRegistry::CallbackMap& CallbackRegistry::getCallbacks()
  {
    static CallbackRegistry::CallbackMap callbacks;
    return callbacks;
  }

  //------------------------------------------------------------------------------------------------
  void CallbackRegistry::removeCallback(const std::string& callbackName)
  {
    if (!hasCallback(callbackName))
    {
      ASSERT_FAIL();
      return;
    }

    getCallbacks().erase(callbackName);
  }

  //------------------------------------------------------------------------------------------------
  void CallbackRegistry::invokeCallback(
    const std::string& callbackName, 
    GameObject& gameObject, 
    const std::string& arg)
  {
    if (!hasCallback(callbackName))
    {
      ASSERT_FAIL();
      return;
    }

    getCallbacks()[callbackName](gameObject, arg);
  }
}