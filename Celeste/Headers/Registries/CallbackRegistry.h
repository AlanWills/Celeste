#pragma once

#include "CelesteDllExport.h"

#include <unordered_map>
#include <functional>


namespace Celeste
{
  class GameObject;
  
  class CallbackRegistry
  {
    public:
      CallbackRegistry() = delete;
      ~CallbackRegistry() = delete;
      CallbackRegistry(const CallbackRegistry&) = delete;
      CallbackRegistry& operator=(const CallbackRegistry&) = delete;

      static bool hasCallback(const std::string& callbackName) { return getCallbacks().find(callbackName) != getCallbacks().end(); }
      CelesteDllExport static void removeCallback(const std::string& callbackName);
      CelesteDllExport static void invokeCallback(const std::string& callbackName, GameObject& gameObject, const std::string& arg);

      template <typename T>
      static bool addCallback();

      template <typename T>
      static bool hasCallback() { return hasCallback(T::name()); }

      template <typename T>
      static void removeCallback() { removeCallback(T::name()); }

    private:
      using FactoryFunction = std::function<void(GameObject&, const std::string&)>;
      using CallbackMap = std::unordered_map<std::string, FactoryFunction>;

      CelesteDllExport static CallbackMap& getCallbacks();
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool CallbackRegistry::addCallback()
  {
    const std::string& name = T::name();
    if (getCallbacks().find(name) != getCallbacks().end())
    {
      return false;
    }

    getCallbacks().emplace(name, [](GameObject& gameObject, const std::string& arg) -> void
    { 
      T()(gameObject, arg); 
    });
    return true;
  }
}