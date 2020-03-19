#include "Resources/Input/KeyboardRigidBody2DControllerLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestUtils
{
  REGISTER_TEST_RESOURCE_CLASS(KeyboardRigidBody2DControllerLoadingResources)

  //------------------------------------------------------------------------------------------------
  void KeyboardRigidBody2DControllerLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Valid);
    ADD_RESOURCE_TO_LUA(resources, Invalid);
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardRigidBody2DControllerLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Valid);
    UNLOAD_DATA(Invalid);
  }
}