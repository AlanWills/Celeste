#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Resources/ResourceLoader.h"
#include "TestResources/TestResources.h"
#include "Resources/Audio/Sound.h"
#include "Mocks/Resources/MockResourceLoader.h"
#include "Mocks/Resources/MockResource.h"
#include "Objects/GameObject.h"
#include "CelesteTestUtils/Assert/AssertCel.h"

using namespace Celeste::Resources;


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestResourceLoader)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_Constructor_CreatesEmptyLoader)
  {
    MockResourceLoader<MockResource> loader(10);

    Assert::AreEqual((size_t)0, loader.size());
    Assert::AreEqual((size_t)0, loader.getMemory().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_Constructor_InputtingLength_SetsResourceDirectoryAsEmptyString)
  {
    // Do not use mock resource loader here - it behaves differently in it's constructor
    ResourceLoader<MockResource> loader(10);

    Assert::AreEqual("", loader.getResourceDirectoryPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_Constructor_InputtingLengthAndFullPathString_SetsDirectoryPathAsInputtedString)
  {
    ResourceLoader<MockResource> loader(10, "Test\\Path");

    Assert::AreEqual("Test\\Path", loader.getResourceDirectoryPath().c_str());
    Assert::AreEqual((size_t)0, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_Constructor_InputtingLengthAndPath_SetsDirectoryPathAsInputtedPath)
  {
    ResourceLoader<MockResource> loader(10, Path("Test", "Path"));

    Assert::AreEqual("Test\\Path", loader.getResourceDirectoryPath().c_str());
    Assert::AreEqual((size_t)0, loader.size());
  }

#pragma endregion

#pragma region Is Resource Loaded Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_IsResourceLoaded_ResourceNotLoaded_RelativePath_ReturnsFalse)
  {
    MockResourceLoader<MockResource> loader(10);
    Path path("ThisResourceDoesntExist");

    Assert::AreEqual(static_cast<size_t>(0), loader.size());
    Assert::IsFalse(loader.isResourceLoaded(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_IsResourceLoaded_ResourceLoaded_RelativePath_ReturnsTrue)
  {
    MockResourceLoader<MockResource> loader(10);
    Path path("Mock1.txt");
    loader.loadResource(path);

    Assert::IsTrue(loader.inMapRelative(path));
    Assert::AreEqual((size_t)1, loader.size());
    Assert::IsTrue(loader.isResourceLoaded(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_IsResourceLoaded_ResourceNotLoaded_FullPath_ReturnsFalse)
  {
    MockResourceLoader<MockResource> loader(10);
    Path path(TestResources::getResourcesDirectory(), "ThisResourceDoesntExist");

    Assert::AreEqual(static_cast<size_t>(0), loader.size());
    Assert::IsFalse(loader.isResourceLoaded(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_IsResourceLoaded_ResourceLoaded_FullPath_ReturnsTrue)
  {
    MockResourceLoader<MockResource> loader(10);
    Path path(loader.getResourceDirectoryPath().as_string(), "Mock1.txt");
    loader.loadResource(path);

    Assert::IsTrue(loader.inMapFull(path));
    Assert::AreEqual((size_t)1, loader.size());
    Assert::IsTrue(loader.isResourceLoaded(path));
  }

#pragma endregion

#pragma region Load Resource Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithRelativeStringForNonExistentResource_DoesNotThrow_AndDoesNotAddNameToMap)
  {
    MockResourceLoader<MockResource> loader(10);
    observer_ptr<MockResource> resource = loader.loadResource("ThisResourceDoesntExist.txt");

    // Check the full path is not in the map
    Assert::IsFalse(loader.inMapRelative("ThisResourceDoestExist"));
    Assert::IsNull(resource);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithFullStringForNonExistentResource_DoesNotThrow_AndDoesNotAddNameToMap)
  {
    MockResourceLoader<MockResource> loader(10);
    std::string fullPath = Path(loader.getResourceDirectoryPath().as_string(), "ThisResourceDoesntExist.txt").as_string();
    observer_ptr<MockResource> resource = loader.loadResource(fullPath);

    // Check the full path is not in the map
    Assert::IsFalse(loader.inMapFull(fullPath));
    Assert::IsNull(resource);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithRelativeStringForInvalidExistentResource_DoesNotAddNameToMap_AndReturnsNullHandle)
  {
    MockResourceLoader<Sound> loader(10);
    observer_ptr<Sound> resource = loader.loadResource(TestResources::getArialTtfRelativePath());

    // Check the path is not in the map
    Assert::IsFalse(loader.inMapRelative(TestResources::getArialTtfRelativePath()));
    Assert::IsNull(resource);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithFullStringForInvalidExistentResource_DoesNotAddNameToMap_AndReturnsNullHandle)
  {
    MockResourceLoader<Sound> loader(10);
    observer_ptr<Sound> resource = loader.loadResource(TestResources::getArialTtfFullPath());

    // Check the full path is not in the map
    Assert::IsFalse(loader.inMapFull(TestResources::getArialTtfFullPath()));
    Assert::IsNull(resource);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithRelativeStringForExistentResource_LoadsAndReturnsResource)
  {
    MockResourceLoader<MockResource> loader(10);

    // Check the text is not in the map
    Assert::IsFalse(loader.inMapRelative("Mock1.txt"));
    Assert::AreEqual((size_t)0, loader.size());

    observer_ptr<MockResource> resource = loader.loadResource("Mock1.txt");

    Assert::IsNotNull(resource);
    Assert::IsTrue(resource->getLoaded());

    // Check the text is added to the map
    Assert::IsTrue(loader.inMapRelative("Mock1.txt"));
    Assert::AreEqual((size_t)1, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithFullStringForExistentResource_LoadsAndReturnsResource)
  {
    MockResourceLoader<MockResource> loader(10);
    std::string fullPath = Path(loader.getResourceDirectoryPath().as_string(), "Mock1.txt").as_string();

    // Check the text is not in the map
    Assert::IsFalse(loader.inMapFull(fullPath));
    Assert::AreEqual((size_t)0, loader.size());

    observer_ptr<MockResource> resource = loader.loadResource(fullPath);

    Assert::IsNotNull(resource);
    Assert::IsTrue(resource->getLoaded());

    // Check the text is added to the map
    Assert::IsTrue(loader.inMapFull(fullPath));
    Assert::AreEqual((size_t)1, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_ForLoadedResourceRelativeString_DoesNotLoadResourceButJustReturnsHandleInMap)
  {
    MockResourceLoader<MockResource> loader(10);
    observer_ptr<MockResource> resource = loader.loadResource("Mock1.txt");

    // Check the text is added to the map
    Assert::IsTrue(loader.inMapRelative("Mock1.txt"));
    Assert::AreEqual((size_t)1, loader.size());

    // Reset the internal load flag - we can use this to test if load has been called again
    resource->unload();
    Assert::IsFalse(resource->getLoaded());

    observer_ptr<MockResource> resourceAgain = loader.loadResource("Mock1.txt");

    // The handle pointers should be the same & it should not have been loaded again
    Assert::IsTrue(resource == resourceAgain);
    Assert::IsFalse(resource->getLoaded());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_ForLoadedResourceFullString_DoesNotLoadResourceButJustReturnsHandleInMap)
  {
    MockResourceLoader<MockResource> loader(10);
    std::string fullPath = Path(loader.getResourceDirectoryPath().as_string(), "Mock1.txt").as_string();
    observer_ptr<MockResource> resource = loader.loadResource(fullPath);

    // Check the text is added to the map
    Assert::IsTrue(loader.inMapFull(fullPath));
    Assert::AreEqual((size_t)1, loader.size());

    // Reset the internal load flag - we can use this to test if load has been called again
    resource->unload();
    Assert::IsFalse(resource->getLoaded());

    observer_ptr<MockResource> resourceAgain = loader.loadResource(fullPath);

    // The handle pointers should be the same & it should not have been loaded again
    Assert::IsTrue(resource == resourceAgain);
    Assert::IsFalse(resource->getLoaded());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithRelativePathForNonExistentResource_DoesNotThrow_AndDoesNotAddNameToMap)
  {
    MockResourceLoader<MockResource> loader(10);
    observer_ptr<MockResource> resource = loader.loadResource(Path("ThisResourceDoesntExist.txt"));

    // Check the text is not added to the map
    Assert::IsFalse(loader.inMapRelative("ThisResourceDoesntExist.txt"));
    Assert::IsNull(resource);
    Assert::AreEqual((size_t)0, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithFullPathForNonExistentResource_DoesNotThrow_AndDoesNotAddNameToMap)
  {
    MockResourceLoader<MockResource> loader(10);
    Path fullPath(loader.getResourceDirectoryPath().as_string(), "ThisResourceDoesntExist.txt");
    observer_ptr<MockResource> resource = loader.loadResource(fullPath);

    // Check the text is not added to the map
    Assert::IsFalse(loader.inMapFull(fullPath));
    Assert::IsNull(resource);
    Assert::AreEqual((size_t)0, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithRelativePathForExistentResource_LoadsAndReturnsResource)
  {
    MockResourceLoader<MockResource> loader(10);

    // Check the text is not in the map
    Assert::AreEqual((size_t)0, loader.size());
    Assert::IsFalse(loader.inMapRelative("Mock1.txt"));

    observer_ptr<MockResource> resource = loader.loadResource(Path("Mock1.txt"));

    Assert::IsNotNull(resource);
    Assert::IsTrue(resource->getLoaded());

    // Check the text is added to the map
    Assert::IsTrue(loader.inMapRelative("Mock1.txt"));
    Assert::AreEqual((size_t)1, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_WithFullPathForExistentResource_LoadsAndReturnsResource)
  {
    MockResourceLoader<MockResource> loader(10);
    Path fullPath(loader.getResourceDirectoryPath().as_string(), "Mock1.txt");

    // Check the text is not in the map
    Assert::AreEqual((size_t)0, loader.size());
    Assert::IsFalse(loader.inMapFull(fullPath));

    observer_ptr<MockResource> resource = loader.loadResource(fullPath);

    Assert::IsNotNull(resource);
    Assert::IsTrue(resource->getLoaded());

    // Check the text is added to the map
    Assert::IsTrue(loader.inMapFull(fullPath));
    Assert::AreEqual((size_t)1, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_ForLoadedResourceRelativePath_DoesNotLoadResourceButJustReturnsHandleInMap)
  {
    MockResourceLoader<MockResource> loader(10);
    observer_ptr<MockResource> resource = loader.loadResource(Path("Mock1.txt"));

    // Check the text is added to the map
    Assert::AreEqual((size_t)1, loader.size());
    Assert::IsTrue(loader.inMapRelative("Mock1.txt"));

    // Reset the internal load flag - we can use this to test if load has been called again
    resource->unload();
    Assert::IsFalse(resource->getLoaded());

    observer_ptr<MockResource> resourceAgain = loader.loadResource(Path("Mock1.txt"));

    // The handle pointers should be the same & it should not have been loaded again
    Assert::IsTrue(resource == resourceAgain);
    Assert::IsFalse(resource->getLoaded());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadResource_ForLoadedResourceFullPath_DoesNotLoadResourceButJustReturnsHandleInMap)
  {
    MockResourceLoader<MockResource> loader(10);
    Path fullPath(loader.getResourceDirectoryPath().as_string(), "Mock1.txt");
    observer_ptr<MockResource> resource = loader.loadResource(fullPath);

    // Check the text is added to the map
    Assert::AreEqual((size_t)1, loader.size());
    Assert::IsTrue(loader.inMapFull(fullPath));

    // Reset the internal load flag - we can use this to test if load has been called again
    resource->unload();
    Assert::IsFalse(resource->getLoaded());

    observer_ptr<MockResource> resourceAgain = loader.loadResource(fullPath);

    // The handle pointers should be the same & it should not have been loaded again
    Assert::IsTrue(resource == resourceAgain);
    Assert::IsFalse(resource->getLoaded());
  }

#pragma endregion

#pragma region Load All Resources

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadAllResourcesInNonExistentDirectory_DoesNotThrow)
  {
    MockResourceLoader<MockResource> loader(10, Path("ThisDirectoryShouldntExist"));
    loader.loadAllResources(".txt");

    Assert::IsTrue(loader.getMap().empty());
    Assert::AreEqual((size_t)0, loader.getMemory().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_LoadAllResourcesInExistentDirectory_LoadsAllFilesThatMatchInputtedExtension)
  {
    MockResourceLoader<MockResource> loader(10);
    loader.loadAllResources(".txt");

    Assert::AreEqual((size_t)2, loader.getMap().size());
    Assert::AreEqual((size_t)2, loader.getMemory().size());
  }

#pragma endregion

#pragma region Unload Resource Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadResource_WithLoadedResource_DoesNotThrow)
  {
    ResourceLoader<MockResource> loader(10, TestResources::getMockResourcesDirectory());
    std::unique_ptr<MockResource> resource(new MockResource());
    MockResource* ptr = resource.get();

    // We call load on the resource, but we do not load it with the loader
    // This is so we can tell if it is still loaded, but not do any state changing of loader
    resource->loadFromFile(Path("Mock"));

    // Check this does not throw
    loader.unloadResource(*ptr);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadResource_WithLoadedResource_Unloads_AndRemovesNameFromMap)
  {
    MockResourceLoader<MockResource> loader(10);
    Path path("Mock1.txt");
    observer_ptr<MockResource> resource = loader.loadResource(path);

    loader.unloadResource(*resource);

    Assert::IsFalse(loader.isResourceLoaded(path));
    Assert::IsFalse(resource->getLoaded());
    Assert::IsFalse(loader.inMapRelative("Mock1.txt"));
    Assert::AreEqual((size_t)0, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadResource_WithRelativeStringForResourceFileNotInMap_DoesNotThrow)
  {
    MockResourceLoader<MockResource> loader(10);
    loader.unloadResource("ThisShouldntExist.txt");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadResource_WithFullStringForResourceFileNotInMap_DoesNotThrow)
  {
    MockResourceLoader<MockResource> loader(10);
    std::string fullPath = Path(loader.getResourceDirectoryPath().as_string(), "ThisShouldntExist.txt").as_string();
    loader.unloadResource(fullPath);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadResource_WithRelativeStringForResourceFileInMap_Unloads_Deallocates_AndRemovesFromMap)
  {
    MockResourceLoader<MockResource> loader(10);
    std::string string = "Mock1.txt";
    observer_ptr<MockResource> resource = loader.loadResource(string);

    loader.unloadResource("Mock1.txt");

    Assert::IsFalse(loader.isResourceLoaded(string));
    Assert::IsFalse(resource->getLoaded());
    Assert::IsFalse(loader.inMapRelative("Mock1.txt"));
    Assert::AreEqual((size_t)0, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadResource_WithFullStringForResourceFileInMap_Unloads_AndRemovesFromMap)
  {
    MockResourceLoader<MockResource> loader(10);
    Path fullPath(loader.getResourceDirectoryPath().as_string(), "Mock1.txt");
    observer_ptr<MockResource> resource = loader.loadResource(fullPath);

    loader.unloadResource(fullPath);

    Assert::IsFalse(loader.isResourceLoaded(fullPath));
    Assert::IsFalse(resource->getLoaded());
    Assert::IsFalse(loader.inMapFull(fullPath));
    Assert::AreEqual((size_t)0, loader.size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadingBug)
  {
    // Need to test that after changing the resource directory unloading an original resource still works
    // If we path in the relative path to it's location relative to new directory
    // This is to confirm we use full paths in the resource loader
    MockResourceLoader<MockResource> loader(10);
    loader.loadAllResources(".txt");

    Assert::AreEqual((size_t)2, loader.size());
    Assert::AreEqual((size_t)2, loader.getMemory().size());

    loader.setResourceDirectoryPath(TestResources::getMoreMockResourcesDirectory());

    // Check unloading old resources still work too
    loader.unloadResource(Path(UPDIR_STRING, "Mock Resources", "Mock1.txt"));
    loader.unloadResource(Path(UPDIR_STRING, "Mock Resources", "Nested", "Mock2.txt"));

    Assert::AreEqual((size_t)0, loader.size());
    Assert::AreEqual((size_t)0, loader.getMemory().size());
  }

#pragma endregion

#pragma region Unload All Resources Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadAllResources_WhenNoneLoaded)
  {
    MockResourceLoader<MockResource> loader(10);
    loader.unloadAllResources();

    Assert::IsTrue(loader.getMap().empty());
    Assert::AreEqual((size_t)0, loader.getMemory().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_UnloadAllResources_WhenResourcesLoaded_ClearsMap_AndDeallocatesAll)
  {
    MockResourceLoader<MockResource> loader(10);
    loader.loadAllResources(".txt");

    Assert::AreNotEqual((size_t)0, loader.size());
    Assert::AreNotEqual((size_t)0, loader.getMemory().size());

    loader.unloadAllResources();

    Assert::AreEqual((size_t)0, loader.size());
    Assert::AreEqual((size_t)0, loader.getMemory().size());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceLoader_SettingResourceDirectoryToAnotherDirectory_WithAllSameRelativeFilePaths_DoesNotCauseNamingCollisions)
  {
    // We need to make sure that setting the resource directory to another directory that
    // includes all the same relative file paths does not cause problems
    // We should be using the full path of the file in the ResourceLoader
    MockResourceLoader<MockResource> loader(10);
    loader.loadAllResources(".txt");

    Assert::AreEqual((size_t)2, loader.size());
    Assert::AreEqual((size_t)2, loader.getMemory().size());

    loader.setResourceDirectoryPath(TestResources::getMoreMockResourcesDirectory());
    loader.loadAllResources(".txt");

    Assert::AreEqual((size_t)4, loader.size());
    Assert::AreEqual((size_t)4, loader.getMemory().size());

    // New resources
    Assert::IsTrue(loader.inMapRelative("Mock1.txt"));
    Assert::IsTrue(loader.inMapRelative(Path("Nested", "Mock2.txt").as_string()));

    // Check old resources still work too
    Assert::IsTrue(loader.inMapRelative(Path(UPDIR_STRING, "Mock Resources", "Mock1.txt")));
    Assert::IsTrue(loader.inMapRelative(Path(UPDIR_STRING, "Mock Resources", "Nested", "Mock2.txt")));
  }

  };
}