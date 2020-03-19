#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/MockResource.h"
#include "Resources/TestResources.h"


namespace TestCeleste
{
  namespace Resources
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

      Assert::AreEqual(static_cast<StringId>(0), resource.getResourceId());
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
      resource.loadFromFile(Path(TestResources::getSpriteVertexShaderFullPath()));

      Assert::AreEqual(internString(TestResources::getSpriteVertexShaderFullPath().as_string()), resource.getResourceId());
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Resource_UnloadFromFile_NotLoadedResource_SetsResourceIdToZero)
    {
      MockResource resource;

      Assert::AreEqual(static_cast<StringId>(0), resource.getResourceId());

      resource.unload();

      Assert::AreEqual(static_cast<StringId>(0), resource.getResourceId());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Resource_UnloadFromFile_LoadedResource_SetsResourceIdToZero)
    {
      MockResource resource;
      resource.loadFromFile(Path(TestResources::getSpriteVertexShaderFullPath()));

      Assert::AreEqual(internString(TestResources::getSpriteVertexShaderFullPath().as_string()), resource.getResourceId());

      resource.unload();

      Assert::AreEqual(static_cast<StringId>(0), resource.getResourceId());
    }

#pragma endregion

    };
  }
}