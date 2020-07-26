#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/MockResource.h"
#include "TestResources/TestResources.h"


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestResource)

#pragma region Load From File Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Resource_LoadFromFile_PathThatDoesntExist_ReturnsFalse)
  {
    MockResource resource;
    Assert::IsFalse(resource.loadFromFile(Path("ThisPathDoesntExist")));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_LoadFromFile_PathThatDoesntExist_DoesNotSetResourceId)
  {
    MockResource resource;
    resource.loadFromFile(Path("ThisPathDoesntExist"));

    Assert::AreEqual(string_id(), resource.getResourceId());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_LoadFromFile_PathThatDoesntExist_DoesNotSetFilePath)
  {
    MockResource resource;
    resource.loadFromFile(Path("ThisPathDoesntExist"));

    Assert::AreEqual("", resource.getFilePath().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_LoadFromFile_PathThatDoesExist_ReturnsTrue)
  {
    MockResource resource;
    Assert::IsTrue(resource.loadFromFile(Path(TestResources::getSpriteVertexShaderFullPath())));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_LoadFromFile_PathThatDoesExist_SetsResourceIdToFilePath)
  {
    MockResource resource;
    resource.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

    Assert::AreEqual(string_id(TestResources::getSpriteVertexShaderFullPath().as_string()), resource.getResourceId());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_LoadFromFile_PathThatDoesExist_SetFilePath)
  {
    MockResource resource;
    resource.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

    Assert::AreEqual(TestResources::getSpriteVertexShaderFullPath(), resource.getFilePath());
  }

#pragma endregion

#pragma region Unload Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_UnloadFromFile_NotLoadedResource_SetsResourceIdToEmptyStringId)
  {
    MockResource resource;

    Assert::AreEqual(string_id(), resource.getResourceId());

    resource.unload();

    Assert::AreEqual(string_id(), resource.getResourceId());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_UnloadFromFile_NotLoadedResource_SetsFilePathToEmptyPath)
  {
    MockResource resource;

    Assert::AreEqual("", resource.getFilePath().c_str());

    resource.unload();

    Assert::AreEqual("", resource.getFilePath().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_UnloadFromFile_LoadedResource_SetsResourceIdToEmptyStringId)
  {
    MockResource resource;
    resource.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

    Assert::AreEqual(string_id(TestResources::getSpriteVertexShaderFullPath().as_string()), resource.getResourceId());

    resource.unload();

    Assert::AreEqual(string_id(), resource.getResourceId());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Resource_UnloadFromFile_LoadedResource_SetsFilePathToEmptyPath)
  {
    MockResource resource;
    resource.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

    Assert::AreEqual(TestResources::getSpriteVertexShaderFullPath(), resource.getFilePath());

    resource.unload();

    Assert::AreEqual("", resource.getFilePath().c_str());
  }

#pragma endregion

  };
}