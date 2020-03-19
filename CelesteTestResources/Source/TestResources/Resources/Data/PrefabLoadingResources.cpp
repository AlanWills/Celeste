#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestResources
{
  REGISTER_TEST_RESOURCE_CLASS(PrefabLoadingResources)

  //------------------------------------------------------------------------------------------------
  void PrefabLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();

    ADD_RESOURCE_TO_LUA(resources, Empty);
    ADD_RESOURCE_TO_LUA(resources, NoGameObjectsElement);
    ADD_RESOURCE_TO_LUA(resources, Invalid);
    ADD_RESOURCE_TO_LUA(resources, ValidSingleGameObject);
    ADD_RESOURCE_TO_LUA(resources, ValidMultipleGameObjects);
    ADD_RESOURCE_TO_LUA(resources, ValidMultipleChildrenForSingleParent);
  }

  //------------------------------------------------------------------------------------------------
  void PrefabLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Empty);
    UNLOAD_DATA(NoGameObjectsElement);
    UNLOAD_DATA(Invalid);
    UNLOAD_DATA(ValidSingleGameObject);
    UNLOAD_DATA(ValidMultipleGameObjects);
    UNLOAD_DATA(ValidMultipleChildrenForSingleParent);
  }
}