#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "UtilityMacros/Unused.h"

#include "XML/Elements/DataConverterListElement.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "DataConverters/Resources/PrefabDataConverter.h"
#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "CelesteTestUtils/Utils/GameObjectXMLUtils.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste::XML;


namespace TestCeleste::XML
{
  CELESTE_TEST_CLASS(TestGameObjectDataConverterListElement)

  using GameObjectDataConverterListElement = std::unique_ptr<DataConverterListElement<GameObjectDataConverter>>;

  //------------------------------------------------------------------------------------------------
  GameObjectDataConverterListElement createListElement(
    const std::string& name = "Test",
    DeserializationRequirement requirement = DeserializationRequirement::kNotRequired)
  {
    return GameObjectDataConverterListElement(
      XMLObjectFactory::create<DataConverterListElement, GameObjectDataConverter>(name, requirement));
  }

#pragma region IsReference Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_IsReference_ReturnsFalse)
  {
    GameObjectDataConverterListElement element = createListElement();

    Assert::IsFalse(element->isReference());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    GameObjectDataConverterListElement element = createListElement();

    Assert::IsFalse(element->convertFromXML(nullptr));
    Assert::IsTrue(element->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_NoChildElements_DoesNothing)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_NoChildElements_ElementNotRequired_ReturnsTrue)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);

    Assert::IsFalse(ele->isRequired());
    Assert::IsNull(element->FirstChildElement());
    Assert::IsTrue(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_NoChildElements_ElementRequired_ReturnsFalse)
  {
    GameObjectDataConverterListElement ele = createListElement("Test", DeserializationRequirement::kRequired);
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);

    Assert::IsTrue(ele->isRequired());
    Assert::IsNull(element->FirstChildElement());
    Assert::IsFalse(ele->convertFromXML(element));
  }

#pragma region Game Object Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_InvalidChildGameObjectElement_DoesNothing)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, element);

    Assert::IsNull(gameObject->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_InvalidChildGameObjectElement_ReturnsFalse)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, element);

    Assert::IsNull(gameObject->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_ValidChildGameObjectElement_AddsChildGameObjectDataConverter)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_ValidChildGameObjectElement_SetsChildGameObjectDataConverterDataCorrectly)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", element);
    gameObject->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "1, 2, 3");

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());

    const GameObjectDataConverter& childConverter = *ele->getItems()[0];

    Assert::AreEqual("Child", childConverter.getName().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), childConverter.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_ValidChildGameObjectElement_ReturnsTrue)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);

    Assert::IsTrue(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildGameObjectElements_AtLeastOneInvalid_DoesNotAddAnyChildGameObjectDataConverters)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    createGameObjectElement(document, element);

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildGameObjectElements_AtLeastOneInvalid_ReturnsFalse)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    createGameObjectElement(document, element);

    Assert::IsFalse(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildGameObjectElements_AllValid_AddsChildGameObjectDataConverters)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    createGameObjectElement(document, "Child2", element);

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildGameObjectElements_AllValid_SetsChildGameObjectDataConverterDataCorrectly)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child1", element);
    gameObject->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "1, 2, 3");
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, "Child2", element);
    gameObject2->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "4, 5, 6");

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());

    const GameObjectDataConverter& childConverter1 = *ele->getItems()[0];

    Assert::AreEqual("Child1", childConverter1.getName().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), childConverter1.getPosition());

    const GameObjectDataConverter& childConverter2 = *ele->getItems()[1];

    Assert::AreEqual("Child2", childConverter2.getName().c_str());
    Assert::AreEqual(glm::vec3(4, 5, 6), childConverter2.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildGameObjectElements_AllValid_ReturnsTrue)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    createGameObjectElement(document, "Child2", element);

    Assert::IsTrue(ele->convertFromXML(element));
  }

#pragma endregion

#pragma region Prefab Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_InvalidChildPrefabElement_DoesNothing)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, element);

    Assert::IsNull(prefab->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_InvalidChildPrefabElement_ReturnsFalse)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, element);

    Assert::IsNull(prefab->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_ValidChildPrefabElement_AddsChildPrefabDataConverter)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());
    Assert::IsNotNull(dynamic_cast<PrefabDataConverter*>(ele->getItems()[0]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_ValidChildPrefabElement_SetsChildPrefabDataConverterDataCorrectly)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());

    const PrefabDataConverter& childConverter = static_cast<const PrefabDataConverter&>(*ele->getItems()[0]);

    Assert::AreEqual("Child", childConverter.getName().c_str());
    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_ValidChildPrefabElement_ReturnsTrue)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildPrefabElements_AtLeastOneInvalid_DoesNotAddAnyChildPrefabDataConverters)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createPrefabElement(document, "Child", element);
    createPrefabElement(document, element);

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildPrefabElements_AtLeastOneInvalid_ReturnsFalse)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createPrefabElement(document, "Child", element);
    createPrefabElement(document, element);

    Assert::IsFalse(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildPrefabElements_AllValid_AddsChildPrefabDataConverters)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", element);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(ele->getItems()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(ele->getItems()[1]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildPrefabElements_AllValid_SetsChildPrefabDataConverterDataCorrectly)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child1", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", element);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());

    const PrefabDataConverter& childConverter1 = static_cast<const PrefabDataConverter&>(*ele->getItems()[0]);

    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter1.getPath().c_str());

    const PrefabDataConverter& childConverter2 = static_cast<const PrefabDataConverter&>(*ele->getItems()[1]);

    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter2.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MultipleChildPrefabElements_AllValid_ReturnsTrue)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", element);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->convertFromXML(element));
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MixOfPrefabAndGameObjects_OneInvalid_DoesNotAddAnyChildConverters)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    createPrefabElement(document, "Child2", element);

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MixOfPrefabAndGameObjects_OneInvalid_ReturnsFalse)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    createPrefabElement(document, "Child2", element);

    Assert::IsFalse(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MixOfPrefabAndGameObjects_AllValid_AddsChildConverters)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());
    Assert::IsNotNull(static_cast<GameObjectDataConverter*>(ele->getItems()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(ele->getItems()[1]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MixOfPrefabAndGameObjects_AllValid_ReturnsTrue)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ConvertFromXML_MixOfPrefabAndGameObjects_AllValid_SetsChildConverterDataCorrectly)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectsElement(document);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", element);
    gameObject->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "1, 2, 3");
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", element);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(ele->getItems().empty());

    ele->convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());
    Assert::IsNotNull(static_cast<GameObjectDataConverter*>(ele->getItems()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(ele->getItems()[1]));

    const GameObjectDataConverter& gameObjectConverter = *ele->getItems()[0];

    Assert::AreEqual("Child", gameObjectConverter.getName().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), gameObjectConverter.getPosition());
  }

#pragma endregion

#pragma region Foreach Iteration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ForeachIteration_EmptyList_DoesNothing)
  {
    GameObjectDataConverterListElement ele = createListElement();

    size_t index = 0;
    for (GameObjectDataConverter* converter : *ele)
    {
      UNUSED(converter);
      ++index;
    }

    Assert::AreEqual(static_cast<size_t>(0), index);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_ForeachIteration_NonEmptyList_IteratesOverCorrectElements)
  {
    GameObjectDataConverterListElement ele = createListElement();
    const_cast<std::vector<GameObjectDataConverter*>&>(ele->getItems()).push_back(new GameObjectDataConverter("GameObject"));
    const_cast<std::vector<GameObjectDataConverter*>&>(ele->getItems()).push_back(new GameObjectDataConverter("GameObject"));

    size_t index = 0;
    for (GameObjectDataConverter* converter : *ele)
    {
      UNUSED(converter);
      ++index;
    }

    Assert::AreEqual(static_cast<size_t>(2), index);
  }

#pragma endregion

#pragma region Clear Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_Clear_ClearsAllElementsFromList)
  {
    GameObjectDataConverterListElement ele = createListElement();
    const_cast<std::vector<GameObjectDataConverter*>&>(ele->getItems()).push_back(new GameObjectDataConverter("GameObject"));
    const_cast<std::vector<GameObjectDataConverter*>&>(ele->getItems()).push_back(new GameObjectDataConverter("GameObject"));

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());

    ele->clear();

    Assert::IsTrue(ele->getItems().empty());
  }

#pragma endregion

#pragma region Clone Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_Clone_ReturnsNewInstanceOfDataConverterListElement)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Test");

    Assert::IsTrue(ele->convertFromXML(element));

    GameObjectDataConverterListElement ele2(ele->clone());

    AssertExt::IsNotNull(ele2);
    Assert::IsFalse(ele == ele2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_Clone_SetsInstanceElementNameToSameName)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Test");

    Assert::IsTrue(ele->convertFromXML(element));

    GameObjectDataConverterListElement ele2(ele->clone());

    Assert::AreEqual(ele->getElementName(), ele2->getElementName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_Clone_SetsInstanceDeserializationRequirementToSameRequirement)
  {
    GameObjectDataConverterListElement ele = createListElement("Test", DeserializationRequirement::kRequired);
    XMLDocument document;
    XMLElement* element = createGameObjectsElement(document);
    createGameObjectElement(document, "Child", element);

    Assert::IsTrue(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));

    GameObjectDataConverterListElement ele2(ele->clone());

    Assert::IsTrue(ele2->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverterListElement_Clone_DoesNotCloneChildren)
  {
    GameObjectDataConverterListElement ele = createListElement();
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Test");

    Assert::IsTrue(ele->convertFromXML(element));

    const_cast<std::vector<GameObjectDataConverter*>&>(ele->getItems()).push_back(new GameObjectDataConverter("GameObject"));
    const_cast<std::vector<GameObjectDataConverter*>&>(ele->getItems()).push_back(new GameObjectDataConverter("GameObject"));

    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());

    GameObjectDataConverterListElement ele2(ele->clone());

    Assert::IsTrue(ele2->getItems().empty());
  }

#pragma endregion

  };
}