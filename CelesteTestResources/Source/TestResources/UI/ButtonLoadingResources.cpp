#include "TestResources/UI/ButtonLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestResources
{
  REGISTER_TEST_RESOURCE_CLASS(ButtonLoadingResources)

  //------------------------------------------------------------------------------------------------
  void ButtonLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, ValidWithCallbacks);
    ADD_RESOURCE_TO_LUA(resources, ValidNoCallbacks);
    ADD_RESOURCE_TO_LUA(resources, Invalid);
  }

  //------------------------------------------------------------------------------------------------
  void ButtonLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(ValidWithCallbacks);
    UNLOAD_DATA(ValidNoCallbacks);
    UNLOAD_DATA(Invalid);
  }
}