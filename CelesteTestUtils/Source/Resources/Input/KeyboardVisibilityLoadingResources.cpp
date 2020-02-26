#include "Resources/Input/KeyboardVisibilityLoadingResources.h"
#include "Resources/ResourceManager.h"

#include "Lua/LuaState.h"


namespace CelesteTestUtils
{
  REGISTER_TEST_RESOURCE_CLASS(KeyboardVisibilityLoadingResources)

  //------------------------------------------------------------------------------------------------
  void KeyboardVisibilityLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Invalid);
    ADD_RESOURCE_TO_LUA(resources, Valid);
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardVisibilityLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Invalid);
    UNLOAD_DATA(Valid);
  }
}