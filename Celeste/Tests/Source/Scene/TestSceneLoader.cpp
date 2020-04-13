#include "UtilityHeaders/UnitTestHeaders.h"

#include "Scene/SceneLoader.h"
#include "TestResources/Scene/SceneLoadingResources.h"
#include "Objects/GameObject.h"
#include "tinyxml2.h"

#include "AssertCel.h"
#include "FileAssert.h"

using namespace tinyxml2;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSceneLoader)

  class AutoDestroyer
  {
  public:
    AutoDestroyer(const std::tuple<bool, std::vector<GameObject*>>& resultGameObjects) :
      m_result(std::get<0>(resultGameObjects)),
      m_gameObjects()
    {
      for (GameObject* gameObject : std::get<1>(resultGameObjects))
      {
        m_gameObjects.emplace_back(gameObject);
      }
    }

    bool m_result;
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
  };

#pragma region Load Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingNonExistentFilePath_ReturnsFalseAndEmptyGameObjects)
  {
    AutoDestroyer result = SceneLoader::load("WubbaLubba");

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentFullFilePath_ToInvalidXMLFile_ReturnsFalseAndEmptyGameObjects)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    File file(path);
    file.append("");

    FileAssert::FileExists(path.as_string());

    AutoDestroyer result = SceneLoader::load(path);

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentRelativeFilePath_ToInvalidXMLFile_ReturnsFalseAndEmptyGameObjects)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    File file(path);
    file.append("");

    FileAssert::FileExists(path.as_string());

    AutoDestroyer result = SceneLoader::load(Path("Temp", "Text.xml"));

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentFullFilePath_NoDocumentRoot_ReturnsFalseAndEmptyGameObjects)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    XMLDocument document;
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDestroyer result = SceneLoader::load(path);

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentRelativeFilePath_NoDocumentRoot_ReturnsFalseAndEmptyGameObjects)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    XMLDocument document;
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDestroyer result = SceneLoader::load(Path("Temp", "Text.xml"));

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentFullFilePath_DocumentRootHasNoChildElement_ReturnsFalseAndEmptyGameObjects)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    XMLDocument document;
    document.NewElement("Root");
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDestroyer result = SceneLoader::load(path);

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentRelativeFilePath_DocumentRootHasNoChildElement_ReturnsFalseAndEmptyGameObjects)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    XMLDocument document;
    document.NewElement("Root");
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDestroyer result = SceneLoader::load(Path("Temp", "Text.xml"));

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentFullFilePath_InvalidScreenData_ReturnsFalseAndEmptyGameObjects)
  {
    AutoDestroyer result = SceneLoader::load(SceneLoadingResources::getEmptyFileFullPath());

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentRelativeFilePath_InvalidScreenData_ReturnsFalseAndEmptyGameObjects)
  {
    AutoDestroyer result = SceneLoader::load(SceneLoadingResources::getEmptyFileRelativePath());

    Assert::IsFalse(result.m_result);
    Assert::IsTrue(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentFullFilePath_ValidScreenData_ReturnsTrue)
  {
    AutoDestroyer result = SceneLoader::load(SceneLoadingResources::getGameObjectsElementFullPath());
    
    Assert::IsTrue(result.m_result);
    Assert::IsFalse(result.m_gameObjects.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneLoader_Load_InputtingExistentRelativeFilePath_ValidScreenData_ReturnsTrue)
  {
    AutoDestroyer result = SceneLoader::load(SceneLoadingResources::getGameObjectsElementRelativePath());

    Assert::IsTrue(result.m_result);
    Assert::IsFalse(result.m_gameObjects.empty());
  }

#pragma endregion

  };
}