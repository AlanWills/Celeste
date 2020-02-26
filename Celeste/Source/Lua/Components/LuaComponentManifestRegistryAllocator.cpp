#include "Lua/Components/LuaComponentManifestRegistryAllocator.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/Components/LuaComponent.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  observer_ptr<Component> LuaComponentManifestRegistryAllocator::allocate(
    const std::string& componentName, 
    GameObject& gameObject) const
  {
    return Lua::LuaComponentManifestRegistry::allocateComponent(componentName, gameObject);
  }
}