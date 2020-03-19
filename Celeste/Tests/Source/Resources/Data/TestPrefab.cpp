#include "UtilityHeaders/UnitTestHeaders.h"

#include "Resources/Data/Prefab.h"
#include "Resources/Resources/Data/PrefabLoadingResources.h"
#include "Rendering/TextRenderer.h"
#include "Rendering/SpriteRenderer.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "FileAssert.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestPrefab)

#pragma region Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_Constructor_SetsGameObjectsToEmptyList)
  {
    Prefab prefab;

    Assert::IsTrue(prefab.getGameObjects().empty());
  }

#pragma endregion

#pragma region Load From File Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_LoadFromFile_InputtingNonExistentPrefabFile_ReturnsFalse)
  {
    Prefab prefab;
    Path path("WubbaLubbaDubDub");

    FileAssert::FileDoesNotExist(path.as_string());
    Assert::IsFalse(prefab.loadFromFile(path));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_LoadFromFile_InputtingNonExistentPrefabFile_LeavesPrefabDataUnchanged)
  {
    Prefab prefab;
    Path path("WubbaLubbaDubDub");

    FileAssert::FileDoesNotExist(path.as_string());
    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.loadFromFile(path);

    Assert::IsTrue(prefab.getGameObjects().empty());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_LoadFromFile_InputtingExistentNonPrefabFile_IsFalse)
  {
    Prefab prefab;
    Path path(TestResources::getArialTtfFullPath());

    FileAssert::FileExists(path.as_string());
    Assert::IsFalse(prefab.loadFromFile(path));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_LoadFromFile_InputtingExistentNonPrefabFile_LeavesPrefabDataUnchanged)
  {
    Prefab prefab;
    Path path(TestResources::getArialTtfFullPath());

    FileAssert::FileExists(path.as_string());
    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.loadFromFile(path);

    Assert::IsTrue(prefab.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_EmptyFile_ReturnsFalse)
  {
    Prefab prefab;
    Path path(PrefabLoadingResources::getEmptyFullPath());

    FileAssert::FileExists(path.as_string());
    Assert::IsFalse(prefab.loadFromFile(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_EmptyFile_LeavesPrefabDataUnchanged)
  {
    Prefab prefab;
    Path path(PrefabLoadingResources::getEmptyFullPath());

    FileAssert::FileExists(path.as_string());
    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.loadFromFile(path);

    Assert::IsTrue(prefab.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_NoGameObjectsElement_ReturnsFalse)
  {
    Prefab prefab;
    Path path(PrefabLoadingResources::getNoGameObjectsElementFullPath());

    FileAssert::FileExists(path.as_string());
    Assert::IsFalse(prefab.loadFromFile(path));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_NoGameObjectsElement_LeavesPrefabDataUnchanged)
  {
    Prefab prefab;
    Path path(PrefabLoadingResources::getNoGameObjectsElementFullPath());

    FileAssert::FileExists(path.as_string());
    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.loadFromFile(path);

    Assert::IsTrue(prefab.getGameObjects().empty());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_LoadFromFile_InputtingExistentPrefabFile_ValidFile_ReturnsTrue)
  {
    Prefab prefab;

    Assert::IsTrue(prefab.loadFromFile(PrefabLoadingResources::getValidSingleGameObjectFullPath()));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_LoadFromFile_InputtingExistentPrefabFile_ValidFile_LoadsPrefabData)
  {
    Prefab prefab;
    Path path(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    FileAssert::FileExists(path.as_string());
    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.loadFromFile(path);

    Assert::IsFalse(prefab.getGameObjects().empty());
  }

#pragma endregion

#pragma region Unload Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_UnloadFromFile_PrefabsNotLoaded_ClearsAllGameObjects)
  {
    Prefab prefab;

    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.loadFromFile(Path("WubbaLubbaDubDub"));

    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.unload();

    Assert::IsTrue(prefab.getGameObjects().empty());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_UnloadFromFile_PrefabsLoaded_ClearsAllGameObjects)
  {
    Prefab prefab;

    Assert::IsTrue(prefab.getGameObjects().empty());

    prefab.loadFromFile(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::IsFalse(prefab.getGameObjects().empty());

    prefab.unload();

    Assert::IsTrue(prefab.getGameObjects().empty());
  }

#pragma endregion

#pragma region Instantiate Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_Instantiate_DataNotLoaded_ReturnsNullptr)
  {
    Prefab prefab;

    Assert::AreEqual(static_cast<StringId>(0), prefab.getResourceId());
    Assert::IsNull(prefab.instantiate());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_Instantiate_MultipleParentGameObjects_ReturnsNullptr)
  {
    Prefab prefab;
    prefab.loadFromFile(PrefabLoadingResources::getTwoParentGameObjectsFullPath());

    Assert::AreNotEqual(static_cast<StringId>(0), prefab.getResourceId());
    Assert::IsFalse(prefab.getGameObjects().empty());
    Assert::AreEqual(static_cast<size_t>(2), prefab.getGameObjects().size());
    Assert::IsNull(prefab.instantiate());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_Instantiate_ReturnsParentGameObject)
  {
    Prefab prefab;
    prefab.loadFromFile(PrefabLoadingResources::getValidSingleGameObjectFullPath());

    Assert::AreNotEqual(static_cast<StringId>(0), prefab.getResourceId());
    Assert::IsFalse(prefab.getGameObjects().empty());
    Assert::AreEqual(static_cast<size_t>(1), prefab.getGameObjects().size());

    std::unique_ptr<GameObject> gameObject(prefab.instantiate());

    Assert::IsNotNull(gameObject.get());

    Assert::AreEqual(gameObject->getName(), internString(prefab.getGameObjects()[0]->getName()));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_Instantiate_SetsUpTransformHierarchyCorrectly)
  {
    Prefab prefab;
    prefab.loadFromFile(PrefabLoadingResources::getValidMultipleGameObjectsFullPath());

    Assert::AreNotEqual(static_cast<StringId>(0), prefab.getResourceId());
    Assert::IsFalse(prefab.getGameObjects().empty());
    Assert::AreEqual(static_cast<size_t>(1), prefab.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(1), prefab.getGameObjects()[0]->getChildGameObjects().size());

    std::unique_ptr<GameObject> gameObject(prefab.instantiate());

    Assert::IsNotNull(gameObject.get());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_Instantiate_MultipleChildrenForSingleParent_SetsUpTransformHierarchyCorrectly)
  {
    // This test is for a bug I found once with prefab transform resolution
    // Multiple children referencing the same parent caused problems

    Prefab prefab;
    prefab.loadFromFile(PrefabLoadingResources::getValidMultipleChildrenForSingleParentFullPath());

    Assert::AreNotEqual(static_cast<StringId>(0), prefab.getResourceId());
    Assert::IsFalse(prefab.getGameObjects().empty());
    Assert::AreEqual(static_cast<size_t>(1), prefab.getGameObjects().size());

    std::unique_ptr<GameObject> gameObject(prefab.instantiate());

    Assert::IsNotNull(gameObject.get());
    Assert::AreEqual(static_cast<size_t>(2), gameObject->getChildCount());
    Assert::AreEqual(internString("Child1"), gameObject->getChild(0)->getName());
    Assert::AreEqual(internString("Child2"), gameObject->getChild(1)->getName());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Prefab_Instantiate_SetsGameObjectsDataCorrectly)
  {
    Prefab prefab;
    prefab.loadFromFile(PrefabLoadingResources::getValidMultipleGameObjectsFullPath());

    Assert::AreNotEqual(static_cast<StringId>(0), prefab.getResourceId());
    Assert::IsFalse(prefab.getGameObjects().empty());
    Assert::AreEqual(static_cast<size_t>(1), prefab.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(1), prefab.getGameObjects()[0]->getChildGameObjects().size());

    std::unique_ptr<GameObject> gameObject(prefab.instantiate());

    Assert::IsNotNull(gameObject.get());
    AssertCel::HasComponent<Rendering::SpriteRenderer>(gameObject.get());
  }

#pragma endregion
  
  };
}