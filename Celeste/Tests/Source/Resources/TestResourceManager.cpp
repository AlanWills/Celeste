#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/MockResourceManager.h"
#include "TestResources/Animation/AnimatorLoadingResources.h"
#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "TestResources/Resources/Models/ModelLoadingResources.h"
#include "OpenAL/OpenALState.h"
#include "AssertCel.h"
#include "AssertSpecialization/FileSystem.h"

using namespace Celeste::Resources;


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestResourceManager)

  //------------------------------------------------------------------------------------------------
  void TestResourceManager::testInitialize()
  {
    // Recreate the alut state
    OpenALState::terminate();
    OpenALState::initialize();
  }

  //------------------------------------------------------------------------------------------------
  void TestResourceManager::testCleanup()
  {
    // Recreate the alut state
    OpenALState::terminate();
    OpenALState::initialize();
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_ConstructorSetsResourcesDirectoryPath)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::AreEqual(TestResources::getResourcesDirectory(), resourceManager.getResourcesDirectory());
  }

#pragma endregion

#pragma region Set Resources Directory Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getResourcesDirectory().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getResourcesDirectory().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesVertexShaderLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getVertexShaderLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getVertexShaderLoader().getResourceDirectoryPath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesFragmentShaderLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getFragmentShaderLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getFragmentShaderLoader().getResourceDirectoryPath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesTexture2DLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getTexture2DLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getTexture2DLoader().getResourceDirectoryPath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesFontLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getFontLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getFontLoader().getResourceDirectoryPath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesSoundLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getSoundLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getSoundLoader().getResourceDirectoryPath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesDataLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getDataLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getDataLoader().getResourceDirectoryPath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesPrefabLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getPrefabLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getPrefabLoader().getResourceDirectoryPath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_SetResourcesDirectory_UpdatesModelLoaderResourcesDirectoryToInputtedValue)
  {
    MockResourceManager resources;
    resources.setResourcesDirectory(Path("Test", "Path"));

    Assert::AreEqual(Path("Test", "Path").as_string(), resources.getModelLoader().getResourceDirectoryPath().as_string());

    resources.setResourcesDirectory(Path("Another", "Path"));

    Assert::AreEqual(Path("Another", "Path").as_string(), resources.getModelLoader().getResourceDirectoryPath().as_string());
  }

#pragma endregion

#pragma region Unload All Tests

#pragma region Vertex Shader

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_VertexShaders_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());

    resources.unloadAll<VertexShader>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_VertexShaders_UnloadsAndDeallocatesAllVertexShaders)
  {
    MockResourceManager resources;
    observer_ptr<VertexShader> shader = resources.load<VertexShader>(TestResources::getSpriteVertexShaderFullPath());

    Assert::IsNotNull(shader);
    Assert::AreNotEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getVertexShaderLoader().size());

    resources.unloadAll<VertexShader>();

    Assert::AreEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());
  }

#pragma endregion

#pragma region Fragment Shader

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_FragmentShaders_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());

    resources.unloadAll<FragmentShader>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_FragmentShaders_UnloadsAndDeallocatesAllFragmentShaders)
  {
    MockResourceManager resources;
    observer_ptr<FragmentShader> shader = resources.load<FragmentShader>(TestResources::getSpriteFragmentShaderFullPath());

    Assert::IsNotNull(shader);
    Assert::AreNotEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getFragmentShaderLoader().size());

    resources.unloadAll<FragmentShader>();

    Assert::AreEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());
  }

#pragma endregion

#pragma region Fonts

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Fonts_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());

    resources.unloadAll<Font>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Fonts_UnloadsAndDeallocatesAllFonts)
  {
    MockResourceManager resources;
    observer_ptr<Font> font = resources.load<Font>(TestResources::getArialTtfFullPath());

    Assert::IsNotNull(font);
    Assert::AreNotEqual(static_cast<StringId>(0), font->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getFontLoader().size());

    resources.unloadAll<Font>();

    Assert::AreEqual(static_cast<StringId>(0), font->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());
  }

#pragma endregion

#pragma region Data

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Data_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());

    resources.unloadAll<Data>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Data_UnloadsAndDeallocatesAllData)
  {
    MockResourceManager resources;
    observer_ptr<Data> data = resources.load<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::IsNotNull(data);
    Assert::AreNotEqual(static_cast<StringId>(0), data->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getDataLoader().size());

    resources.unloadAll<Data>();

    Assert::AreEqual(static_cast<StringId>(0), data->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());
  }

#pragma endregion

#pragma region Sounds

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Sounds_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());

    resources.unloadAll<Sound>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Sounds_UnloadsAndDeallocatesAllSounds)
  {
    MockResourceManager resources;
    observer_ptr<Sound> sound = resources.load<Sound>(TestResources::getButtonHoverWavFullPath());

    Assert::IsNotNull(sound);
    Assert::AreNotEqual(static_cast<StringId>(0), sound->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getSoundLoader().size());

    resources.unloadAll<Sound>();

    Assert::AreEqual(static_cast<StringId>(0), sound->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());
  }

#pragma endregion

#pragma region Textures

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Textures_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());

    resources.unloadAll<Texture2D>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Textures_UnloadsAndDeallocatesAllTextures)
  {
    MockResourceManager resources;
    observer_ptr<Texture2D> texture = resources.load<Texture2D>(TestResources::getContainerJpgFullPath());

    Assert::IsNotNull(texture);
    Assert::AreNotEqual(static_cast<StringId>(0), texture->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getTexture2DLoader().size());

    resources.unloadAll<Texture2D>();

    Assert::AreEqual(static_cast<StringId>(0), texture->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());
  }

#pragma endregion

#pragma region Prefabs

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Prefabs_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());

    resources.unloadAll<Prefab>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Prefabs_UnloadsAndDeallocatesAllPrefabs)
  {
    MockResourceManager resources;
    observer_ptr<Prefab> prefab = resources.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::IsNotNull(prefab);
    Assert::AreNotEqual(static_cast<StringId>(0), prefab->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getPrefabLoader().size());

    resources.unloadAll<Prefab>();

    Assert::AreEqual(static_cast<StringId>(0), prefab->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());
  }

#pragma endregion

#pragma region Models

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Models_NoneLoaded_DoesNothing)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());

    resources.unloadAll<Model>();

    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAll_Models_UnloadsAndDeallocatesAllModel)
  {
    MockResourceManager resources;
    observer_ptr<Model> model = resources.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::IsNotNull(model);
    Assert::AreNotEqual(static_cast<StringId>(0), model->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getModelLoader().size());

    resources.unloadAll<Model>();

    Assert::AreEqual(static_cast<StringId>(0), model->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());
  }

#pragma endregion

#pragma endregion

#pragma region Unload All Resources Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadAllResources_UnloadsResourcesFromLoaders)
  {
    MockResourceManager resourceManager;
    resourceManager.load<VertexShader>(TestResources::getSpriteVertexShaderFullPath());
    resourceManager.load<FragmentShader>(TestResources::getSpriteFragmentShaderFullPath());
    resourceManager.load<Font>(TestResources::getArialTtfFullPath());
    resourceManager.load<Data>(AnimatorLoadingResources::getValidFullPath());
    resourceManager.load<Sound>(TestResources::getButtonHoverWavFullPath());
    resourceManager.load<Texture2D>(TestResources::getBlockPngFullPath());
    resourceManager.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());
    resourceManager.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::AreEqual((size_t)1, resourceManager.getVertexShaderLoader().size());
    Assert::AreEqual((size_t)1, resourceManager.getFragmentShaderLoader().size());
    Assert::AreEqual((size_t)1, resourceManager.getTexture2DLoader().size());
    Assert::AreEqual((size_t)1, resourceManager.getFontLoader().size());
    Assert::AreEqual((size_t)1, resourceManager.getSoundLoader().size());
    Assert::AreEqual((size_t)1, resourceManager.getDataLoader().size());
    Assert::AreEqual((size_t)1, resourceManager.getPrefabLoader().size());
    Assert::AreEqual((size_t)1, resourceManager.getModelLoader().size());

    resourceManager.unloadAllResources();

    Assert::AreEqual((size_t)0, resourceManager.getVertexShaderLoader().size());
    Assert::AreEqual((size_t)0, resourceManager.getFragmentShaderLoader().size());
    Assert::AreEqual((size_t)0, resourceManager.getTexture2DLoader().size());
    Assert::AreEqual((size_t)0, resourceManager.getFontLoader().size());
    Assert::AreEqual((size_t)0, resourceManager.getSoundLoader().size());
    Assert::AreEqual((size_t)0, resourceManager.getDataLoader().size());
    Assert::AreEqual((size_t)0, resourceManager.getPrefabLoader().size());
    Assert::AreEqual((size_t)0, resourceManager.getModelLoader().size());
  }

#pragma endregion

#pragma region Is Vertex Shader Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsVertexShaderLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<VertexShader>("ThisShouldntExist.vert"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsVertexShaderLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<VertexShader> shader = resourceManager.load<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::IsNotNull(shader);
    Assert::IsTrue(resourceManager.isLoaded<VertexShader>(TestResources::getSpriteVertexShaderRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsVertexShaderLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.vert");

    Assert::IsFalse(resourceManager.isLoaded<VertexShader>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsVertexShaderLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<VertexShader> shader = resourceManager.load<VertexShader>(TestResources::getSpriteVertexShaderFullPath());

    Assert::IsNotNull(shader);
    Assert::IsTrue(resourceManager.isLoaded<VertexShader>(TestResources::getSpriteVertexShaderFullPath()));
  }

#pragma endregion

#pragma region Is Fragment Shader Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFragmentShaderLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<FragmentShader>("ThisShouldntExist.frag"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFragmentShaderLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<FragmentShader> shader = resourceManager.load<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::IsNotNull(shader);
    Assert::IsTrue(resourceManager.isLoaded<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFragmentShaderLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.frag");

    Assert::IsFalse(resourceManager.isLoaded<FragmentShader>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFragmentShaderLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<FragmentShader> shader = resourceManager.load<FragmentShader>(TestResources::getSpriteFragmentShaderFullPath());

    Assert::IsNotNull(shader);
    Assert::IsTrue(resourceManager.isLoaded<FragmentShader>(TestResources::getSpriteFragmentShaderFullPath()));
  }

#pragma endregion

#pragma region Is Texture2D Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsTexture2DLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<Texture2D>("ThisShouldntExist.png"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsTexture2DLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Texture2D> texture = resourceManager.load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(texture);
    Assert::IsTrue(resourceManager.isLoaded<Texture2D>(TestResources::getBlockPngRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsTexture2DLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.png");

    Assert::IsFalse(resourceManager.isLoaded<Texture2D>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsTexture2DLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Texture2D> texture = resourceManager.load<Texture2D>(TestResources::getBlockPngFullPath());

    Assert::IsNotNull(texture);
    Assert::IsTrue(resourceManager.isLoaded<Texture2D>(TestResources::getBlockPngFullPath()));
  }

#pragma endregion

#pragma region Is Font Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFontLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<Font>("ThisShouldntExist.ttf"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFontLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Font> font = resourceManager.load<Font>(TestResources::getArialTtfRelativePath());

    Assert::IsNotNull(font);
    Assert::IsTrue(resourceManager.isLoaded<Font>(TestResources::getArialTtfRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFontLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.ttf");

    Assert::IsFalse(resourceManager.isLoaded<Font>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsFontLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Font> font = resourceManager.load<Font>(TestResources::getArialTtfFullPath());

    Assert::IsNotNull(font);
    Assert::IsTrue(resourceManager.isLoaded<Font>(TestResources::getArialTtfFullPath()));
  }

#pragma endregion

#pragma region Is Sound Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsSoundLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<Sound>("ThisShouldntExist.wav"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsSoundLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Sound> sound = resourceManager.load<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(sound);
    Assert::IsTrue(resourceManager.isLoaded<Sound>(TestResources::getButtonHoverWavRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsSoundLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.wav");

    Assert::IsFalse(resourceManager.isLoaded<Sound>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsSoundLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Sound> sound = resourceManager.load<Sound>(TestResources::getButtonHoverWavFullPath());

    Assert::IsNotNull(sound);
    Assert::IsTrue(resourceManager.isLoaded<Sound>(TestResources::getButtonHoverWavFullPath()));
  }

#pragma endregion

#pragma region Is Data Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsDataLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<Data>("ThisShouldntExist.xml"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsDataLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Data> data = resourceManager.load<Data>(TestResources::getDataXmlRelativePath());

    Assert::IsNotNull(data);
    Assert::IsTrue(resourceManager.isLoaded<Data>(TestResources::getDataXmlRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsDataLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.xml");

    Assert::IsFalse(resourceManager.isLoaded<Data>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsDataLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Data> data = resourceManager.load<Data>(TestResources::getDataXmlFullPath());

    Assert::IsNotNull(data);
    Assert::IsTrue(resourceManager.isLoaded<Data>(TestResources::getDataXmlFullPath()));
  }

#pragma endregion

#pragma region Is Prefab Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsPrefabLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<Prefab>("ThisShouldntExist.prefab"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsPrefabLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Prefab> prefab = resourceManager.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectRelativePath());

    Assert::IsNotNull(prefab);
    Assert::IsTrue(resourceManager.isLoaded<Prefab>(PrefabLoadingResources::getValidSingleGameObjectRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsPrefabLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.prefab");

    Assert::IsFalse(resourceManager.isLoaded<Prefab>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsPrefabLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Prefab> prefab = resourceManager.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::IsNotNull(prefab);
    Assert::IsTrue(resourceManager.isLoaded<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath()));
  }

#pragma endregion

#pragma region Is Model Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsModelLoaded_WithNonLoadedRelativeFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());

    Assert::IsFalse(resourceManager.isLoaded<Model>("ThisShouldntExist.obj"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsModelLoaded_WithLoadedRelativeFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Model> model = resourceManager.load<Model>(ModelLoadingResources::getBoxRelativePath());

    Assert::IsNotNull(model);
    Assert::IsTrue(resourceManager.isLoaded<Model>(ModelLoadingResources::getBoxRelativePath()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsModelLoaded_WithNonLoadedFullFilePath_ReturnsFalse)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    Path path(resourceManager.getResourcesDirectory(), "ThisShouldntExist.obj");

    Assert::IsFalse(resourceManager.isLoaded<Model>(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_IsModelLoaded_WithLoadedFullFilePath_ReturnsTrue)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Model> model = resourceManager.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::IsNotNull(model);
    Assert::IsTrue(resourceManager.isLoaded<Model>(ModelLoadingResources::getBoxFullPath()));
  }

#pragma endregion

#pragma region Load Vertex Shader Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadVertexShader_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<VertexShader> shader = resourceManager.load<VertexShader>("ThisShouldntExist.vert");

    Assert::IsNull(shader);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadVertexShader_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<VertexShader> shader = resourceManager.load<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::IsNotNull(shader);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadVertexShader_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getVertexShaderLoader().size());

    resourceManager.load<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getVertexShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadVertexShader_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getVertexShaderLoader().size());

    resourceManager.load<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getVertexShaderLoader().size());

    resourceManager.load<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getVertexShaderLoader().size());
  }

#pragma endregion

#pragma region Load Fragment Shader Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFragmentShader_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<FragmentShader> shader = resourceManager.load<FragmentShader>("ThisShouldntExist.frag");

    Assert::IsNull(shader);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFragmentShader_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<FragmentShader> shader = resourceManager.load<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::IsNotNull(shader);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFragmentShader_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getFragmentShaderLoader().size());

    resourceManager.load<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getFragmentShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFragmentShader_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getFragmentShaderLoader().size());

    resourceManager.load<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getFragmentShaderLoader().size());

    resourceManager.load<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getFragmentShaderLoader().size());
  }

#pragma endregion

#pragma region Load Texture2D Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadTexture2D_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Texture2D> texture = resourceManager.load<Texture2D>("ThisShouldntExist.png");

    Assert::IsNull(texture);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadTexture2D_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Texture2D> texture = resourceManager.load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(texture);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadTexture2D_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getTexture2DLoader().size());

    resourceManager.load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getTexture2DLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadTexture2D_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getTexture2DLoader().size());

    resourceManager.load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getTexture2DLoader().size());

    resourceManager.load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getTexture2DLoader().size());
  }

#pragma endregion

#pragma region Load Font Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFont_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Font> font = resourceManager.load<Font>("ThisShouldntExist.ttf");

    Assert::IsNull(font);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFont_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Font> font = resourceManager.load<Font>(TestResources::getArialTtfRelativePath());

    Assert::IsNotNull(font);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFont_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getFontLoader().size());

    resourceManager.load<Font>(TestResources::getArialTtfRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getFontLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadFont_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getFontLoader().size());

    resourceManager.load<Font>(TestResources::getArialTtfRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getFontLoader().size());

    resourceManager.load<Font>(TestResources::getArialTtfRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getFontLoader().size());
  }

#pragma endregion

#pragma region Load Sound Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadSound_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Sound> audioSource = resourceManager.load<Sound>("ThisShouldntExist.wav");

    Assert::IsNull(audioSource);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadSound_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Sound> audioSource = resourceManager.load<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(audioSource);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadSound_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getSoundLoader().size());

    resourceManager.load<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getSoundLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadSound_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getSoundLoader().size());

    resourceManager.load<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getSoundLoader().size());

    resourceManager.load<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getSoundLoader().size());
  }

#pragma endregion

#pragma region Load Data Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadData_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Data> data = resourceManager.load<Data>("ThisShouldntExist.wav");

    Assert::IsNull(data);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadData_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Data> data = resourceManager.load<Data>(TestResources::getDataXmlRelativePath());

    Assert::IsNotNull(data);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadData_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getDataLoader().size());

    resourceManager.load<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getDataLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadData_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getDataLoader().size());

    resourceManager.load<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getDataLoader().size());

    resourceManager.load<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getDataLoader().size());
  }

#pragma endregion

#pragma region Load Prefab Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadPrefab_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Prefab> prefab = resourceManager.load<Prefab>("ThisShouldntExist.xml");

    Assert::IsNull(prefab);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadPrefab_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Prefab> prefab = resourceManager.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::IsNotNull(prefab);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadPrefab_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getPrefabLoader().size());

    resourceManager.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getPrefabLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadPrefab_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getPrefabLoader().size());

    resourceManager.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getPrefabLoader().size());

    resourceManager.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getPrefabLoader().size());
  }

#pragma endregion

#pragma region Load Model Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadModel_WithNonExistentFilePath_ReturnsNullHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Model> model = resourceManager.load<Model>("ThisShouldntExist.obj");

    Assert::IsNull(model);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadModel_WithExistentFilePath_ReturnsResourceHandle)
  {
    ResourceManager resourceManager(TestResources::getResourcesDirectory());
    observer_ptr<Model> model = resourceManager.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::IsNotNull(model);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadModel_WithExistentFilePath_ForFirstTime_AddsToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getModelLoader().size());

    resourceManager.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getModelLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_LoadModel_WithExistentFilePath_NotForFirstTime_DoesNotAddDuplicateToResourceManager)
  {
    MockResourceManager resourceManager;

    Assert::AreEqual(static_cast<size_t>(0), resourceManager.getModelLoader().size());

    resourceManager.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getModelLoader().size());

    resourceManager.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resourceManager.getModelLoader().size());
  }

#pragma endregion

#pragma region Unload Vertex Shader Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadVertexShader_WithNonLoadedVertexShader_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());

    resources.unload<VertexShader>("ThisShouldntExist.vert");

    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadVertexShader_WithLoadedVertexShader_UnloadsVertexShader)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());

    observer_ptr<VertexShader> shader = resources.load<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::IsNotNull(shader);
    Assert::AreNotEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getVertexShaderLoader().size());

    resources.unload<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::AreEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadVertexShader_WithLoadedVertexShader_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());

    resources.load<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getVertexShaderLoader().size());

    resources.unload<VertexShader>(TestResources::getSpriteVertexShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getVertexShaderLoader().size());
  }

#pragma endregion

#pragma region Unload Fragment Shader Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadFragmentShader_WithNonLoadedFragmentShader_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());

    resources.unload<FragmentShader>("ThisShouldntExist.frag");

    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadFragmentShader_WithLoadedFragmentShader_UnloadsFragmentShader)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());

    observer_ptr<FragmentShader> shader = resources.load<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::IsNotNull(shader);
    Assert::AreNotEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getFragmentShaderLoader().size());

    resources.unload<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::AreEqual(static_cast<StringId>(0), shader->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadFragmentShader_WithLoadedFragmentShader_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());

    resources.load<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getFragmentShaderLoader().size());

    resources.unload<FragmentShader>(TestResources::getSpriteFragmentShaderRelativePath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getFragmentShaderLoader().size());
  }

#pragma endregion

#pragma region Unload Texture2D Shader Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadTexture2D_WithNonLoadedTexture2D_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());

    resources.unload<Texture2D>("ThisShouldntExist.png");

    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadTexture2D_WithLoadedTexture2D_UnloadsTexture2D)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());

    observer_ptr<Texture2D> texture = resources.load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(texture);
    Assert::AreNotEqual(static_cast<StringId>(0), texture->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getTexture2DLoader().size());

    resources.unload<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(static_cast<StringId>(0), texture->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadTexture2D_WithLoadedTexture2D_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());

    resources.load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getTexture2DLoader().size());

    resources.unload<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getTexture2DLoader().size());
  }

#pragma endregion

#pragma region Unload Font Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadFont_WithNonLoadedFont_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());

    resources.unload<Font>("ThisShouldntExist.ttf");

    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadFont_WithLoadedFont_UnloadsFont)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());

    observer_ptr<Font> font = resources.load<Font>(TestResources::getArialTtfRelativePath());

    Assert::IsNotNull(font);
    Assert::AreNotEqual(static_cast<StringId>(0), font->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getFontLoader().size());

    resources.unload<Font>(TestResources::getArialTtfRelativePath());

    Assert::AreEqual(static_cast<StringId>(0), font->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadFont_WithLoadedFont_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());

    resources.load<Font>(TestResources::getArialTtfRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getFontLoader().size());

    resources.unload<Font>(TestResources::getArialTtfRelativePath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getFontLoader().size());
  }

#pragma endregion

#pragma region Unload Sound Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadSound_WithNonLoadedSound_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());

    resources.unload<Sound>("ThisShouldntExist.wav");

    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadSound_WithLoadedSound_UnloadsSound)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());

    observer_ptr<Sound> sound = resources.load<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(sound);
    Assert::AreNotEqual(static_cast<StringId>(0), sound->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getSoundLoader().size());

    resources.unload<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::AreEqual(static_cast<StringId>(0), sound->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadSound_WithLoadedSound_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());

    resources.load<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getSoundLoader().size());

    resources.unload<Sound>(TestResources::getButtonHoverWavRelativePath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getSoundLoader().size());
  }

#pragma endregion

#pragma region Unload Data Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadData_WithNonLoadedData_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());

    resources.unload<Data>("ThisShouldntExist.xml");

    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadData_WithLoadedData_UnloadsData)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());

    observer_ptr<Data> data = resources.load<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::IsNotNull(data);
    Assert::AreNotEqual(static_cast<StringId>(0), data->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getDataLoader().size());

    resources.unload<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::AreEqual(static_cast<StringId>(0), data->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadData_WithLoadedData_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());

    resources.load<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getDataLoader().size());

    resources.unload<Data>(AnimatorLoadingResources::getValidFullPath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getDataLoader().size());
  }

#pragma endregion

#pragma region Unload Prefab Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadPrefab_WithNonLoadedPrefab_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());

    resources.unload<Prefab>("ThisShouldntExist.xml");

    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadPrefab_WithLoadedPrefab_UnloadsPrefab)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());

    observer_ptr<Prefab> prefab = resources.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::IsNotNull(prefab);
    Assert::AreNotEqual(static_cast<StringId>(0), prefab->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getPrefabLoader().size());

    resources.unload<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::AreEqual(static_cast<StringId>(0), prefab->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadPrefab_WithLoadedPrefab_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());

    resources.load<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getPrefabLoader().size());

    resources.unload<Prefab>(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getPrefabLoader().size());
  }

#pragma endregion

#pragma region Unload Model Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadModel_WithNonLoadedModel_DoesNotThrow)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());

    resources.unload<Model>("ThisShouldntExist.obj");

    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadModel_WithLoadedModel_UnloadsModel)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());

    observer_ptr<Model> model = resources.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::IsNotNull(model);
    Assert::AreNotEqual(static_cast<StringId>(0), model->getResourceId());
    Assert::AreEqual(static_cast<size_t>(1), resources.getModelLoader().size());

    resources.unload<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::AreEqual(static_cast<StringId>(0), model->getResourceId());
    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceManager_UnloadModel_WithLoadedModel_RemovesFromResourceManager)
  {
    MockResourceManager resources;

    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());

    resources.load<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::AreEqual(static_cast<size_t>(1), resources.getModelLoader().size());

    resources.unload<Model>(ModelLoadingResources::getBoxFullPath());

    Assert::AreEqual(static_cast<size_t>(0), resources.getModelLoader().size());
  }

#pragma endregion

  };
}