#include "TestResources/Input/KeyboardActivatorLoadingResources.h"
#include "Resources/ResourceManager.h"

#include "Lua/LuaState.h"


namespace CelesteTestResources
{
  REGISTER_TEST_RESOURCE_CLASS(KeyboardActivatorLoadingResources)

  //------------------------------------------------------------------------------------------------
  void KeyboardActivatorLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Invalid);
    ADD_RESOURCE_TO_LUA(resources, Valid);
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardActivatorLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Invalid);
    UNLOAD_DATA(Valid);
  }
}