#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_SCENE_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, ScreenData, ResourceRelativePath)

  class SceneLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(SceneLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(ScreenData, "Scene Data")

    TEST_SCENE_DATA(EmptyFile, "EmptyFile.scene");
    TEST_SCENE_DATA(EmptyScreen, "EmptyScreen.scene");
    TEST_SCENE_DATA(NoResourcesElement, "NoResourcesElement.scene");

    // Name
    TEST_SCENE_DATA(NoNameAttribute, "Name\\NoNameAttribute.scene");
    TEST_SCENE_DATA(NameAttribute, "Name\\NameAttribute.scene");

    // Fonts
    TEST_SCENE_DATA(NoFontsElement, "Fonts\\NoFontsElement.scene");
    TEST_SCENE_DATA(FontsElement, "Fonts\\FontsElement.scene");
    TEST_SCENE_DATA(FontsElementWithBadElements, "Fonts\\FontsElementWithBadElements.scene");

    // Vertex Shaders
    TEST_SCENE_DATA(NoVertexShadersElement, "VertexShaders\\NoVertexShadersElement.scene");
    TEST_SCENE_DATA(VertexShadersElement, "VertexShaders\\VertexShadersElement.scene");
    TEST_SCENE_DATA(VertexShadersElementWithBadElements, "VertexShaders\\VertexShadersElementWithBadElements.scene");

    // Fragment Shaders
    TEST_SCENE_DATA(NoFragmentShadersElement, "FragmentShaders\\NoFragmentShadersElement.scene");
    TEST_SCENE_DATA(FragmentShadersElement, "FragmentShaders\\FragmentShadersElement.scene");
    TEST_SCENE_DATA(FragmentShadersElementWithBadElements, "FragmentShaders\\FragmentShadersElementWithBadElements.scene");

    // Data
    TEST_SCENE_DATA(NoDataElement, "Data\\NoDataElement.scene");
    TEST_SCENE_DATA(DataElement, "Data\\DataElement.scene");
    TEST_SCENE_DATA(DataElementWithBadElements, "Data\\DataElementWithBadElements.scene");

    // Sound
    TEST_SCENE_DATA(NoSoundsElement, "Sounds\\NoSoundsElement.scene");
    TEST_SCENE_DATA(SoundsElement, "Sounds\\SoundsElement.scene");
    TEST_SCENE_DATA(SoundsElementWithBadElements, "Sounds\\SoundsElementWithBadElements.scene");

    // Texture
    TEST_SCENE_DATA(NoTexturesElement, "Textures\\NoTexturesElement.scene");
    TEST_SCENE_DATA(TexturesElement, "Textures\\TexturesElement.scene");
    TEST_SCENE_DATA(TexturesElementWithBadElements, "Textures\\TexturesElementWithBadElements.scene");

    // GameObjects
    TEST_SCENE_DATA(NoGameObjectsElement, "GameObjects\\NoGameObjectsElement.scene");
    TEST_SCENE_DATA(GameObjectsElement, "GameObjects\\GameObjectsElement.scene");
    TEST_SCENE_DATA(GameObjectsElementWithBadElements, "GameObjects\\GameObjectsElementWithBadElements.scene");

    // Prefabs
    TEST_SCENE_DATA(PrefabWithParent, "Prefabs\\PrefabWithParent.scene");
  };
}