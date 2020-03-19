#include "Resources/Rendering/TextRendererLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestUtils
{
  REGISTER_TEST_RESOURCE_CLASS(TextRendererLoadingResources)

  //------------------------------------------------------------------------------------------------
  void TextRendererLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();
    ADD_RESOURCE_TO_LUA(resources, Invalid);
    ADD_RESOURCE_TO_LUA(resources, ValidNoLines);
    ADD_RESOURCE_TO_LUA(resources, ValidWithLines);
  }

  //------------------------------------------------------------------------------------------------
  void TextRendererLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(Invalid);
    UNLOAD_DATA(ValidNoLines);
    UNLOAD_DATA(ValidWithLines);
  }
}