#include "Lua/LuaState.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/Components/LuaComponent.h"
#include "Registries/ComponentRegistry.h"

#include "Objects/GameObject.h"


namespace Celeste::Lua
{
  //------------------------------------------------------------------------------------------------
  LuaComponentManifestRegistry::LuaComponentManifestRegistry() :
    m_manifests()
  {
  }

  //------------------------------------------------------------------------------------------------
  LuaComponentManifestRegistry& LuaComponentManifestRegistry::getInstance()
  {
    static LuaComponentManifestRegistry instance;
    return instance;
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentManifestRegistry::registerComponent(const std::string& componentName, sol::table componentTable)
  {
    if (hasComponent(componentName))
    {
      ASSERT_FAIL();
      return;
    }

    // Process manifest and add it to our registry
    if (!componentTable.valid())
    {
      ASSERT_FAIL();
      return;
    }

    getInstance().m_manifests.insert(std::make_pair(componentName, LuaComponentManifest(componentTable)));
    ComponentRegistry::registerComponent(componentName, [componentName](GameObject& gameObject) { return LuaComponentManifestRegistry::createComponent(componentName, gameObject); });
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentManifestRegistry::deregisterComponent(const std::string& componentName)
  {
    if (hasComponent(componentName))
    {
      getInstance().m_manifests.erase(componentName);
      ComponentRegistry::deregisterComponent(componentName);
    }
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<LuaComponent> LuaComponentManifestRegistry::createComponent(const std::string& componentName, GameObject& gameObject)
  {
    if (!hasComponent(componentName))
    {
      return observer_ptr<LuaComponent>();
    }

    observer_ptr<LuaComponent> luaComponent = gameObject.addComponent<LuaComponent>();
    getInstance().m_manifests.find(componentName)->second.initializeComponent(*luaComponent);

    return luaComponent;
  }
}