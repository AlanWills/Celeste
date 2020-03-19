#include "Resources/UI/SliderLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestUtils
{
  REGISTER_TEST_RESOURCE_CLASS(SliderLoadingResources)

  //------------------------------------------------------------------------------------------------
  void SliderLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, ValidWithCallbacks);
    ADD_RESOURCE_TO_LUA(resources, ValidNoCallbacks);
    ADD_RESOURCE_TO_LUA(resources, Invalid);
  }

  //------------------------------------------------------------------------------------------------
  void SliderLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(ValidWithCallbacks);
    UNLOAD_DATA(ValidNoCallbacks);
    UNLOAD_DATA(Invalid);
  }
}