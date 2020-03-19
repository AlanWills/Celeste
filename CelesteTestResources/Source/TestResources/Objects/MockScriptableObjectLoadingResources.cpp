#include "TestResources/Objects/MockScriptableObjectLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestResources
{
  REGISTER_TEST_RESOURCE_CLASS(MockScriptableObjectLoadingResources)

  //------------------------------------------------------------------------------------------------
  void MockScriptableObjectLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Invalid);
    ADD_RESOURCE_TO_LUA(resources, Valid);
  }

  //------------------------------------------------------------------------------------------------
  void MockScriptableObjectLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Valid);
    UNLOAD_DATA(Invalid);
  }
}