#include "TestResources/Physics/RigidBody2DLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestResources
{
  REGISTER_TEST_RESOURCE_CLASS(RigidBody2DLoadingResources)

  //------------------------------------------------------------------------------------------------
  void RigidBody2DLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Invalid);
    ADD_RESOURCE_TO_LUA(resources, Valid);
  }

  //------------------------------------------------------------------------------------------------
  void RigidBody2DLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Invalid);
    UNLOAD_DATA(Valid);
  }
}