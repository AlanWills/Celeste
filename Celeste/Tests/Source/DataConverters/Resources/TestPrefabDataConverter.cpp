#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Resources/MockPrefabDataConverter.h"
#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "Resources/Data/Prefab.h"
#include "Utils/GameObjectXMLUtils.h"
#include "AssertCel.h"


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestPrefabDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestPrefabDataConverter::testInitialize()
  {
    PrefabLoadingResources::unloadAllResources();
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    PrefabDataConverter converter("Prefab");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_Constructor_SetsElementName_ToInput)
  {
    PrefabDataConverter converter("Prefab");

    Assert::AreEqual("Prefab", converter.getElementName().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_Constructor_SetsPrefab_ToNull)
  {
    PrefabDataConverter converter("Prefab");

    Assert::IsNull(converter.getPrefab());
  }

#pragma region Relative Path

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_Constructor_SetsRelativePath_ToEmptyString)
  {
    PrefabDataConverter converter("Prefab");

    Assert::AreEqual("", converter.getPath().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_Constructor_AddsRelativePathAttribute)
  {
    const MockPrefabDataConverter converter("Prefab");

    Assert::IsNotNull(converter.findAttribute(converter.PATH_ATTRIBUTE_NAME));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_Constructor_SetsRelativePathAttribute_TokRequired)
  {
    const MockPrefabDataConverter converter("Prefab");

    Assert::IsTrue(converter.findAttribute(converter.PATH_ATTRIBUTE_NAME)->isRequired());
  }

#pragma endregion

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    PrefabDataConverter converter("Prefab");

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    PrefabDataConverter converter("Prefab");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = document.NewElement("Prefab");

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = document.NewElement("Prefab");
    converter.convertFromXML(element);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectFullPath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectFullPath().c_str());
    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Relative Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingElementWithNoPathElement_ReturnsFalse_DoesNothing)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    
    Assert::IsNull(element->Attribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getPath().c_str());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual("", converter.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingElementWithPathElement_EmptyText_ReturnsFalse_SetsPathToEmptyString)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, "");

    Assert::AreEqual("", element->Attribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getPath().c_str());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual("", converter.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingElementWithPathElement_InvalidPath_ReturnsFalse_SetsPathToSameString)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", element->Attribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getPath().c_str());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InputtingElementWithPathElement_ValidPath_ReturnsTrue_SetsPathToSameString)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectFullPath().c_str());

    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectFullPath().c_str(), element->Attribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getPath().c_str());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectFullPath().c_str(), converter.getPath().c_str());
  }

#pragma endregion

#pragma region Convert Prefab Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_InvalidPath_SetsPrefabToNull_ReturnsFalse)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::IsNull(converter.getPrefab());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsNull(converter.getPrefab());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_EmptyFile_SetsPrefabToNull_ReturnsFalse)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getEmptyFullPath().c_str());

    Assert::IsNull(converter.getPrefab());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsNull(converter.getPrefab());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_NoGameObjectsElement_SetsPrefabToNull_ReturnsFalse)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getNoGameObjectsElementFullPath().c_str());

    Assert::IsNull(converter.getPrefab());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsNull(converter.getPrefab());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_SingleGameObject_LoadsOneGameObject_ReturnsTrue)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectFullPath().c_str());

    Assert::IsNull(converter.getPrefab());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsNotNull(converter.getPrefab());
    Assert::AreEqual(static_cast<size_t>(1), converter.getPrefab()->getGameObjects().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PrefabDataConverter_ConvertFromXML_ValidPath_MultipleGameObjects_LoadsMultipleGameObjects_ReturnsTrue)
  {
    PrefabDataConverter converter("Prefab");
    XMLDocument document;
    XMLElement* element = createPrefabElement(document, "Test");
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidMultipleChildrenForSingleParentFullPath().c_str());

    Assert::IsNull(converter.getPrefab());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsNotNull(converter.getPrefab());
    Assert::AreEqual(static_cast<size_t>(1), converter.getPrefab()->getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), converter.getPrefab()->getGameObjects()[0]->getChildGameObjects().size());
  }

#pragma endregion

  };
}