#include "UtilityHeaders/UnitTestHeaders.h"

#include "Utils/GameObjectXMLUtils.h"
#include "XML/Elements/DataConverterListElement.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "DataConverters/Resources/PrefabDataConverter.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestGameObjectXMLUtils)

#pragma region Create GameObjects Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectsElement_ReturnsNewElementInstance)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);

    Assert::IsNotNull(element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectsElement_AddsElementToEndOfDocument)
  {
    XMLDocument document;
    document.InsertFirstChild(document.NewElement("FirstChild"));
    tinyxml2::XMLElement* element = createGameObjectsElement(document);

    Assert::IsTrue(document.LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectsElement_InputtingParent_AddsElementToEndOfInputtedParent)
  {
    XMLDocument document;
    tinyxml2::XMLElement* parent = document.NewElement("FirstChild");
    document.InsertFirstChild(parent);
    tinyxml2::XMLElement* sibling = document.NewElement("Sibling");
    parent->InsertFirstChild(sibling);
    tinyxml2::XMLElement* element = createGameObjectsElement(document, parent);

    Assert::IsTrue(parent->LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TesGameObjecttXMLUtils_CreateGameObjectsElement_SetsNameToCorrectValue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);

    Assert::AreEqual(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME, element->Name());
  }

#pragma endregion

#pragma region Create Game Object Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectElement_ReturnsNewElementInstance)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document);

    Assert::IsNotNull(element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectElement_SetsElementName_ToCorrectValue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document);

    Assert::AreEqual(DataConverterListElement<GameObjectDataConverter>::GAME_OBJECT_ELEMENT_NAME, element->Name());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectElement_AddsElementToEndOfDocument)
  {
    XMLDocument document;
    document.InsertFirstChild(document.NewElement("FirstChild"));
    tinyxml2::XMLElement* element = createGameObjectElement(document);

    Assert::IsTrue(document.LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectElement_InputtingParent_AddsElementToEndOfInputtedParent)
  {
    XMLDocument document;
    tinyxml2::XMLElement* parent = document.NewElement("FirstChild");
    document.InsertFirstChild(parent);
    tinyxml2::XMLElement* sibling = document.NewElement("Sibling");
    parent->InsertFirstChild(sibling);
    tinyxml2::XMLElement* element = createGameObjectElement(document, parent);

    Assert::IsTrue(parent->LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectElement_NotInputtingName_SetsNameAttribute_ToNull)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document);

    Assert::IsNull(element->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreateGameObjectElement_InputtingName_SetsNameAttribute_ToInputtedValue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");

    Assert::AreEqual("Test", element->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Create Prefab Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreatePrefabElement_ReturnsNewElementInstance)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createPrefabElement(document);

    Assert::IsNotNull(element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreatePrefabElement_SetsElementName_ToCorrectValue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createPrefabElement(document);

    Assert::AreEqual(DataConverterListElement<GameObjectDataConverter>::PREFAB_ELEMENT_NAME, element->Name());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreatePrefabElement_AddsElementToEndOfDocument)
  {
    XMLDocument document;
    document.InsertFirstChild(document.NewElement("FirstChild"));
    tinyxml2::XMLElement* element = createPrefabElement(document);

    Assert::IsTrue(document.LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreatePrefabElement_InputtingParent_AddsElementToEndOfInputtedParent)
  {
    XMLDocument document;
    tinyxml2::XMLElement* parent = document.NewElement("FirstChild");
    document.InsertFirstChild(parent);
    tinyxml2::XMLElement* sibling = document.NewElement("Sibling");
    parent->InsertFirstChild(sibling);
    tinyxml2::XMLElement* element = createPrefabElement(document, parent);

    Assert::IsTrue(parent->LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreatePrefabElement_NotInputtingName_SetsNameAttribute_ToNull)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createPrefabElement(document);

    Assert::IsNull(element->Attribute(PrefabDataConverter::NAME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestGameObjectXMLUtils_CreatePrefabElement_InputtingName_SetsNameAttribute_ToInputtedValue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");

    Assert::AreEqual("Test", element->Attribute(PrefabDataConverter::NAME_ATTRIBUTE_NAME));
  }

#pragma endregion

  };
}