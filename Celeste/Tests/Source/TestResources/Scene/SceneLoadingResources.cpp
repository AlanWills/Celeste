#include "Resources/Scene/SceneLoadingResources.h"
#include "Resources/ResourceManager.h"


namespace CelesteTestUtils
{
  REGISTER_TEST_RESOURCE_CLASS(SceneLoadingResources)

  //------------------------------------------------------------------------------------------------
  void SceneLoadingResources::addAllResourcesToLua()
  {
    sol::table resources = createLuaResourcesTable();

    ADD_RESOURCE_TO_LUA(resources, EmptyFile);
    ADD_RESOURCE_TO_LUA(resources, EmptyScreen);
    ADD_RESOURCE_TO_LUA(resources, NoResourcesElement);

    // Fonts
    ADD_RESOURCE_TO_LUA(resources, NoFontsElement);
    ADD_RESOURCE_TO_LUA(resources, FontsElement);
    ADD_RESOURCE_TO_LUA(resources, FontsElementWithBadElements);

    // Vertex Shaders
    ADD_RESOURCE_TO_LUA(resources, NoVertexShadersElement);
    ADD_RESOURCE_TO_LUA(resources, VertexShadersElement);
    ADD_RESOURCE_TO_LUA(resources, VertexShadersElementWithBadElements);

    // Fragment Shaders
    ADD_RESOURCE_TO_LUA(resources, NoFragmentShadersElement);
    ADD_RESOURCE_TO_LUA(resources, FragmentShadersElement);
    ADD_RESOURCE_TO_LUA(resources, FragmentShadersElementWithBadElements);

    // Data
    ADD_RESOURCE_TO_LUA(resources, NoDataElement);
    ADD_RESOURCE_TO_LUA(resources, DataElement);
    ADD_RESOURCE_TO_LUA(resources, DataElementWithBadElements);

    // Sound
    ADD_RESOURCE_TO_LUA(resources, NoSoundsElement);
    ADD_RESOURCE_TO_LUA(resources, SoundsElement);
    ADD_RESOURCE_TO_LUA(resources, SoundsElementWithBadElements);

    // Texture
    ADD_RESOURCE_TO_LUA(resources, NoTexturesElement);
    ADD_RESOURCE_TO_LUA(resources, TexturesElement);
    ADD_RESOURCE_TO_LUA(resources, TexturesElementWithBadElements);

    // GameObjects
    ADD_RESOURCE_TO_LUA(resources, NoGameObjectsElement);
    ADD_RESOURCE_TO_LUA(resources, GameObjectsElement);
    ADD_RESOURCE_TO_LUA(resources, GameObjectsElementWithBadElements);

    // Prefabs
    ADD_RESOURCE_TO_LUA(resources, PrefabWithParent);
  }

  //----------------------------------------------------------------------------------------------------------
  void SceneLoadingResources::unloadAllResources()
  {
    UNLOAD_DATA(EmptyFile);
    UNLOAD_DATA(EmptyScreen);
    UNLOAD_DATA(NoResourcesElement);

    // Fonts
    UNLOAD_DATA(NoFontsElement);
    UNLOAD_DATA(FontsElement);
    UNLOAD_DATA(FontsElementWithBadElements);

    // Vertex Shaders
    UNLOAD_DATA(NoVertexShadersElement);
    UNLOAD_DATA(VertexShadersElement);
    UNLOAD_DATA(VertexShadersElementWithBadElements);

    // Fragment Shaders
    UNLOAD_DATA(NoFragmentShadersElement);
    UNLOAD_DATA(FragmentShadersElement);
    UNLOAD_DATA(FragmentShadersElementWithBadElements);

    // Data
    UNLOAD_DATA(NoDataElement);
    UNLOAD_DATA(DataElement);
    UNLOAD_DATA(DataElementWithBadElements);

    // Sound
    UNLOAD_DATA(NoSoundsElement);
    UNLOAD_DATA(SoundsElement);
    UNLOAD_DATA(SoundsElementWithBadElements);

    // Texture
    UNLOAD_DATA(NoTexturesElement);
    UNLOAD_DATA(TexturesElement);
    UNLOAD_DATA(TexturesElementWithBadElements);

    // GameObjects
    UNLOAD_DATA(NoGameObjectsElement);
    UNLOAD_DATA(GameObjectsElement);
    UNLOAD_DATA(GameObjectsElementWithBadElements);

    // Prefabs
    UNLOAD_DATA(PrefabWithParent);
  }
}