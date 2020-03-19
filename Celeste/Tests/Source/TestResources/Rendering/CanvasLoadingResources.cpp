#include "Resources/Rendering/CanvasLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestUtils
{
  REGISTER_TEST_RESOURCE_CLASS(CanvasLoadingResources)

  //------------------------------------------------------------------------------------------------
  void CanvasLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Invalid);
    ADD_RESOURCE_TO_LUA(resources, Valid);
  }

  //------------------------------------------------------------------------------------------------
  void CanvasLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Invalid);
    UNLOAD_DATA(Valid);
  }
}