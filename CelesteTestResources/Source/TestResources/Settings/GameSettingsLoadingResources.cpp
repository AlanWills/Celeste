#include "TestResources/Settings/GameSettingsLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestResources
{
  REGISTER_TEST_RESOURCE_CLASS(GameSettingsLoadingResources)

  //------------------------------------------------------------------------------------------------
  void GameSettingsLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Valid);
    ADD_RESOURCE_TO_LUA(resources, Invalid);
  }

  //------------------------------------------------------------------------------------------------
  void GameSettingsLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Valid);
    UNLOAD_DATA(Invalid);
  }
}