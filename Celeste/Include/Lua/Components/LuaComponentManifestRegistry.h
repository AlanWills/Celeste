#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/LuaHeaders.h"
#include "Lua/Components/LuaComponentManifest.h"
#include "Memory/ObserverPtr.h"

#include <unordered_map>


namespace Celeste
{
  class GameObject;

  namespace Lua
  {
    class LuaComponent;

    class LuaComponentManifestRegistry
    {
      public:
        CelesteDllExport static size_t registeredComponentsSize() { return getInstance().m_manifests.size(); }
        CelesteDllExport static void registerComponent(const std::string& componentName, sol::table componentTable);
        CelesteDllExport static void deregisterComponent(const std::string& componentName);
        CelesteDllExport static bool hasComponent(const std::string& componentName) { return getInstance().m_manifests.find(componentName) != getInstance().m_manifests.end(); }
        CelesteDllExport static observer_ptr<LuaComponent> createComponent(const std::string& componentName, GameObject& gameObject);

      private:
        using LuaComponentManifests = std::unordered_map<std::string, LuaComponentManifest>;

        static LuaComponentManifestRegistry& getInstance();

        LuaComponentManifestRegistry();
        ~LuaComponentManifestRegistry() = default;
        LuaComponentManifestRegistry(const LuaComponentManifestRegistry&) = delete;
        LuaComponentManifestRegistry& operator=(const LuaComponentManifestRegistry&) = delete;

        LuaComponentManifests m_manifests;
    };
  }
}