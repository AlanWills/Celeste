#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_SCREEN_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, ScreenData, ResourceRelativePath)

  class ScreenLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(ScreenLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(ScreenData, "Screen Data")

    TEST_SCREEN_DATA(EmptyFile, "EmptyFile.screen");
    TEST_SCREEN_DATA(EmptyScreen, "EmptyScreen.screen");
    TEST_SCREEN_DATA(NoResourcesElement, "NoResourcesElement.screen");

    // Name
    TEST_SCREEN_DATA(NoNameAttribute, "Name\\NoNameAttribute.screen");
    TEST_SCREEN_DATA(NameAttribute, "Name\\NameAttribute.screen");

    // Fonts
    TEST_SCREEN_DATA(NoFontsElement, "Fonts\\NoFontsElement.screen");
    TEST_SCREEN_DATA(FontsElement, "Fonts\\FontsElement.screen");
    TEST_SCREEN_DATA(FontsElementWithBadElements, "Fonts\\FontsElementWithBadElements.screen");

    // Vertex Shaders
    TEST_SCREEN_DATA(NoVertexShadersElement, "VertexShaders\\NoVertexShadersElement.screen");
    TEST_SCREEN_DATA(VertexShadersElement, "VertexShaders\\VertexShadersElement.screen");
    TEST_SCREEN_DATA(VertexShadersElementWithBadElements, "VertexShaders\\VertexShadersElementWithBadElements.screen");

    // Fragment Shaders
    TEST_SCREEN_DATA(NoFragmentShadersElement, "FragmentShaders\\NoFragmentShadersElement.screen");
    TEST_SCREEN_DATA(FragmentShadersElement, "FragmentShaders\\FragmentShadersElement.screen");
    TEST_SCREEN_DATA(FragmentShadersElementWithBadElements, "FragmentShaders\\FragmentShadersElementWithBadElements.screen");

    // Data
    TEST_SCREEN_DATA(NoDataElement, "Data\\NoDataElement.screen");
    TEST_SCREEN_DATA(DataElement, "Data\\DataElement.screen");
    TEST_SCREEN_DATA(DataElementWithBadElements, "Data\\DataElementWithBadElements.screen");

    // Sound
    TEST_SCREEN_DATA(NoSoundsElement, "Sounds\\NoSoundsElement.screen");
    TEST_SCREEN_DATA(SoundsElement, "Sounds\\SoundsElement.screen");
    TEST_SCREEN_DATA(SoundsElementWithBadElements, "Sounds\\SoundsElementWithBadElements.screen");

    // Texture
    TEST_SCREEN_DATA(NoTexturesElement, "Textures\\NoTexturesElement.screen");
    TEST_SCREEN_DATA(TexturesElement, "Textures\\TexturesElement.screen");
    TEST_SCREEN_DATA(TexturesElementWithBadElements, "Textures\\TexturesElementWithBadElements.screen");

    // GameObjects
    TEST_SCREEN_DATA(NoGameObjectsElement, "GameObjects\\NoGameObjectsElement.screen");
    TEST_SCREEN_DATA(GameObjectsElement, "GameObjects\\GameObjectsElement.screen");
    TEST_SCREEN_DATA(GameObjectsElementWithBadElements, "GameObjects\\GameObjectsElementWithBadElements.screen");

    // Prefabs
    TEST_SCREEN_DATA(PrefabWithParent, "Prefabs\\PrefabWithParent.screen");
  };
}