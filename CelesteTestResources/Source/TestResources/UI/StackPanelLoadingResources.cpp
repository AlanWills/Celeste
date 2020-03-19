#include "TestResources/UI/StackPanelLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestResources
{
  REGISTER_TEST_RESOURCE_CLASS(StackPanelLoadingResources)

  //------------------------------------------------------------------------------------------------
  void StackPanelLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Valid);
    ADD_RESOURCE_TO_LUA(resources, Invalid);
  }

  //------------------------------------------------------------------------------------------------
  void StackPanelLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Valid);
    UNLOAD_DATA(Invalid);
  }
}