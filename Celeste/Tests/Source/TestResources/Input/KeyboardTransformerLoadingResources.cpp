#include "Resources/Input/KeyboardTransformerLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestUtils
{
  REGISTER_TEST_RESOURCE_CLASS(KeyboardTransformerLoadingResources)

  //------------------------------------------------------------------------------------------------
  void KeyboardTransformerLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Valid);
    ADD_RESOURCE_TO_LUA(resources, Invalid);
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardTransformerLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Valid);
    UNLOAD_DATA(Invalid);
  }
}