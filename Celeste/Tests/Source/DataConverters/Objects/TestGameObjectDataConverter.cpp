#include "UtilityHeaders/UnitTestHeaders.h"

#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "Resources/Objects/GameObjectLoadingResources.h"
#include "Resources/Resources/Data/PrefabLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Rendering/SpriteRenderer.h"
#include "DataConverters/Rendering/SpriteRendererDataConverter.h"
#include "DataConverters/Resources/PrefabDataConverter.h"
#include "Utils/GameObjectXMLUtils.h"
#include "AssertCel.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/Components/LuaComponent.h"

using namespace Celeste::Lua;
using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestGameObjectDataConverter)

  class AutoDestroyer
  {
    public:
      AutoDestroyer(GameObject* gameObject) :
        m_gameObject(gameObject)
      {
      }

      std::unique_ptr<GameObject> m_gameObject;
  };

  //------------------------------------------------------------------------------------------------
  void TestGameObjectDataConverter::testInitialize()
  {
    GameObjectLoadingResources::unloadAllResources();
    LuaComponentManifestRegistry::deregisterComponent("Test");
  }

  //------------------------------------------------------------------------------------------------
  void TestGameObjectDataConverter::testCleanup()
  {
    GameObjectLoadingResources::unloadAllResources();
    LuaComponentManifestRegistry::deregisterComponent("Test");
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsElementName_ToInput)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::AreEqual("GameObject", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsNameToEmptyString)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::IsTrue(converter.getName().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsTagToEmptyString)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::IsTrue(converter.getTag().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsPositionToZero)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::AreEqual(glm::vec3(), converter.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsIsActiveToTrue)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsComponentsListToEmptyList)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::IsTrue(converter.getComponents().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsChildGameObjectsListToEmptyList)
  {
    GameObjectDataConverter converter("GameObject");

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_AddsNameAttribute)
  {
    const GameObjectDataConverter converter("GameObject");

    Assert::IsNotNull(converter.findAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsNameAttributeToRequired)
  {
    const GameObjectDataConverter converter("GameObject");

    Assert::IsTrue(converter.findAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_AddsTagAttribute)
  {
    const GameObjectDataConverter converter("GameObject");

    Assert::IsNotNull(converter.findAttribute(converter.TAG_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsTagAttributeToNotRequired)
  {
    const GameObjectDataConverter converter("GameObject");

    Assert::IsFalse(converter.findAttribute(converter.TAG_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_AddsPositionAttribute)
  {
    const GameObjectDataConverter converter("GameObject");

    Assert::IsNotNull(converter.findAttribute(converter.POSITION_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_AddsComponentsElement)
  {
    const GameObjectDataConverter converter("GameObject");
    
    Assert::IsNotNull(converter.findElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_AddsChildGameObjectsElement)
  {
    const GameObjectDataConverter converter("GameObject");

    Assert::IsNotNull(converter.findElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Constructor_SetsChildGameObjects_To_kNotRequired)
  {
    const GameObjectDataConverter converter("GameObject");

    Assert::IsFalse(converter.findElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    
    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    GameObjectDataConverter converter("GameObject");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    observer_ptr<Data> data = getResourceManager().load<Data>(GameObjectLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    GameObjectDataConverter converter("GameObject");
    converter.convertFromXML(getResourceManager().load<Data>(GameObjectLoadingResources::getInvalidFullPath())->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    observer_ptr<Data> data = getResourceManager().load<Data>(GameObjectLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    GameObjectDataConverter converter("GameObject");
    converter.convertFromXML(getResourceManager().load<Data>(GameObjectLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoNameAttribute_DoesNothing_AndReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getName().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NameAttribute_SetsNameToText_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("WubbaLubbaDubDub", converter.getName().c_str());
  }

#pragma endregion

#pragma region Convert Tag Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoTagAttribute_DoesNothing_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Test");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(converter.TAG_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getTag().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_TagAttribute_SetsTagToText_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Test");
    element->SetAttribute(converter.TAG_ATTRIBUTE_NAME, "Foreground");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(converter.TAG_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("Foreground", converter.getTag().c_str());
  }

#pragma endregion

#pragma region Convert Position Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoPositionAttribute_DoesNothing_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(converter.POSITION_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(), converter.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_PositionAttribute_InvalidText_DoesNothing_AndReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(converter.POSITION_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(converter.POSITION_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(), converter.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_PositionAttribute_AbsoluteValues_SetsValueTypeAndValuesCorrectly_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(converter.POSITION_ATTRIBUTE_NAME, "30,40,0.5");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(converter.POSITION_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(30, 40, 0.5), converter.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_PositionAttribute_RelativeValues_SetsValueTypeAndValuesCorrectly_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(converter.POSITION_ATTRIBUTE_NAME, "3%,2%,0.1%");
    
    const glm::vec2& viewportDimensions = getViewportDimensions();

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(converter.POSITION_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(3 * viewportDimensions.x, 2 * viewportDimensions.y, 0.1), converter.getPosition());
  }

#pragma endregion

#pragma region Convert Is Active Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoIsActiveAttribute_DoesNothing_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    
    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(GameObjectDataConverter::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_IsActiveAttribute_InvalidText_SetsValueToTrue_AndReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(GameObjectDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(GameObjectDataConverter::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_IsActiveAttribute_ValidText_SetsValueToCorrectValue_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(GameObjectDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, "false");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(GameObjectDataConverter::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsActive());
  }

#pragma endregion

#pragma region Convert Components Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoComponentsElement_DoesNothing_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");

    Assert::IsNull(element->FirstChildElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME));
    Assert::IsTrue(converter.getComponents().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getComponents().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ComponentsElement_NoComponentElement_DoesNothing_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    XMLElement* componentsElement = document.NewElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME);
    element->InsertFirstChild(componentsElement);
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");

    Assert::IsNotNull(element->FirstChildElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME));
    Assert::IsNull(componentsElement->FirstChildElement(""));
    Assert::IsTrue(converter.getComponents().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getComponents().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ComponentsElement_WithComponentElements_LoadsCorrectConvertersAndData_AndReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    XMLElement* componentsElement = document.NewElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME);
    XMLElement* componentElement = document.NewElement(Rendering::SpriteRenderer::type_name());
    componentElement->SetAttribute("active", false);
    element->InsertFirstChild(componentsElement);
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    componentsElement->InsertFirstChild(componentElement);

    Assert::IsNotNull(element->FirstChildElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME));
    Assert::IsNotNull(componentsElement->FirstChildElement());
    Assert::IsTrue(converter.getComponents().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getComponents().size());
    Assert::IsNotNull(dynamic_cast<const SpriteRendererDataConverter*>(converter.getComponents()[0]));
    Assert::IsFalse(converter.getComponents()[0]->getIsActive());
  }

#pragma endregion

#pragma region Convert Child GameObjects Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoChildGameObjectsElement_DoesNothing)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");

    Assert::IsNull(element->FirstChildElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoChildGameObjectsElement_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");

    Assert::IsNull(element->FirstChildElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoChildElements_DoesNothing)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_NoChildElements_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);

    Assert::IsNull(gameObjects->FirstChildElement());
    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma region Game Object Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_InvalidChildGameObjectElement_DoesNothing)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, gameObjects);

    Assert::IsNull(gameObject->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_InvalidChildGameObjectElement_ReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, gameObjects);

    Assert::IsNull(gameObject->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ValidChildGameObjectElement_AddsChildGameObjectDataConverter)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getChildGameObjects().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ValidChildGameObjectElement_SetsChildGameObjectDataConverterDataCorrectly)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    gameObject->SetAttribute(converter.TAG_ATTRIBUTE_NAME, "UI");
    gameObject->SetAttribute(converter.POSITION_ATTRIBUTE_NAME, "1, 2, 3");

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getChildGameObjects().size());

    const GameObjectDataConverter& childConverter = *converter.getChildGameObjects()[0];

    Assert::AreEqual("Child", childConverter.getName().c_str());
    Assert::AreEqual("UI", childConverter.getTag().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), childConverter.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ValidChildGameObjectElement_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildGameObjectElements_AtLeastOneInvalid_DoesNotAddAnyChildGameObjectDataConverters)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, gameObjects);

    Assert::IsTrue(converter.getChildGameObjects().empty());
    
    converter.convertFromXML(element);

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildGameObjectElements_AtLeastOneInvalid_ReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, gameObjects);
    
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildGameObjectElements_AllValid_AddsChildGameObjectDataConverters)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildGameObjectElements_AllValid_SetsChildGameObjectDataConverterDataCorrectly)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child1", gameObjects);
    gameObject->SetAttribute(converter.TAG_ATTRIBUTE_NAME, "UI");
    gameObject->SetAttribute(converter.POSITION_ATTRIBUTE_NAME, "1, 2, 3");
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);
    gameObject2->SetAttribute(converter.TAG_ATTRIBUTE_NAME, "World");
    gameObject2->SetAttribute(converter.POSITION_ATTRIBUTE_NAME, "4, 5, 6");

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());

    const GameObjectDataConverter& childConverter1 = *converter.getChildGameObjects()[0];

    Assert::AreEqual("Child1", childConverter1.getName().c_str());
    Assert::AreEqual("UI", childConverter1.getTag().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), childConverter1.getPosition());

    const GameObjectDataConverter& childConverter2 = *converter.getChildGameObjects()[1];

    Assert::AreEqual("Child2", childConverter2.getName().c_str());
    Assert::AreEqual("World", childConverter2.getTag().c_str());
    Assert::AreEqual(glm::vec3(4, 5, 6), childConverter2.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildGameObjectElements_AllValid_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

#pragma region Prefab Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_InvalidChildPrefabElement_DoesNothing)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, gameObjects);

    Assert::IsNull(prefab->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_InvalidChildPrefabElement_ReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, gameObjects);

    Assert::IsNull(prefab->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ValidChildPrefabElement_AddsChildPrefabDataConverter)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getChildGameObjects().size());
    Assert::IsNotNull(dynamic_cast<PrefabDataConverter*>(converter.getChildGameObjects()[0]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ValidChildPrefabElement_SetsChildPrefabDataConverterDataCorrectly)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getChildGameObjects().size());

    const PrefabDataConverter& childConverter = static_cast<const PrefabDataConverter&>(*converter.getChildGameObjects()[0]);

    Assert::AreEqual("Child", childConverter.getName().c_str());
    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_ValidChildPrefabElement_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildPrefabElements_AtLeastOneInvalid_DoesNotAddAnyChildPrefabDataConverters)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, gameObjects);

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildPrefabElements_AtLeastOneInvalid_ReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, gameObjects);

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildPrefabElements_AllValid_AddsChildPrefabDataConverters)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getChildGameObjects()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getChildGameObjects()[1]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildPrefabElements_AllValid_SetsChildPrefabDataConverterDataCorrectly)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());

    const PrefabDataConverter& childConverter1 = static_cast<const PrefabDataConverter&>(*converter.getChildGameObjects()[0]);

    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter1.getPath().c_str());

    const PrefabDataConverter& childConverter2 = static_cast<const PrefabDataConverter&>(*converter.getChildGameObjects()[1]);

    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter2.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MultipleChildPrefabElements_AllValid_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MixOfPrefabAndGameObjects_OneInvalid_DoesNotAddAnyChildConverters)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getChildGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MixOfPrefabAndGameObjects_OneInvalid_ReturnsFalse)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_AddsChildConverters)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::IsNotNull(static_cast<GameObjectDataConverter*>(converter.getChildGameObjects()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getChildGameObjects()[1]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_ReturnsTrue)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_SetsChildConverterDataCorrectly)
  {
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    gameObject->SetAttribute(converter.TAG_ATTRIBUTE_NAME, "UI");
    gameObject->SetAttribute(converter.POSITION_ATTRIBUTE_NAME, "1, 2, 3");
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getChildGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::IsNotNull(static_cast<GameObjectDataConverter*>(converter.getChildGameObjects()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getChildGameObjects()[1]));

    const GameObjectDataConverter& gameObjectConverter = *converter.getChildGameObjects()[0];

    Assert::AreEqual("Child", gameObjectConverter.getName().c_str());
    Assert::AreEqual("UI", gameObjectConverter.getTag().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), gameObjectConverter.getPosition());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    gameObject.setName("Test");
    GameObjectDataConverter converter("GameObject");
    observer_ptr<Data> data = getResourceManager().load<Data>(GameObjectLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
    Assert::IsFalse(gameObject.isActive());
    Assert::AreEqual(internString("Test"), gameObject.getName());

    converter.setValues(gameObject);

    Assert::IsFalse(gameObject.isActive());
    Assert::AreEqual(internString("Test"), gameObject.getName());
  }

  // <GameObject active="false" should_render="false" position="10" name="TestName"/>

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_DataLoadedCorrectly_ReturnsGameObject_WithDataSetToLoadedData)
  {
    GameObject gameObject;
    gameObject.setName("Test");
    GameObjectDataConverter converter("GameObject");
    observer_ptr<Data> data = getResourceManager().load<Data>(GameObjectLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
    Assert::IsTrue(gameObject.isActive());
    Assert::AreEqual(internString("Test"), gameObject.getName());

    converter.setValues(gameObject);

    Assert::IsFalse(gameObject.isActive());
    Assert::AreEqual(internString("TestName"), gameObject.getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_TagSetToEmptyString_DoesNotChangeTag)
  {
    GameObject gameObject;
    gameObject.setTag("Test");
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Test");

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(internString("Test"), gameObject.getTag());

    converter.setValues(gameObject);

    Assert::AreEqual(internString("Test"), gameObject.getTag());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_TagNotSetToEmptyString_SetsGameObjectTagToCorrectValue)
  {
    GameObject gameObject;
    gameObject.setTag("Test");
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Test");
    element->SetAttribute(converter.TAG_ATTRIBUTE_NAME, "Foreground");

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(internString("Test"), gameObject.getTag());

    converter.setValues(gameObject);

    Assert::AreEqual(internString("Foreground"), gameObject.getTag());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_AddsComponentsToGameObject)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    XMLElement* componentsElement = document.NewElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME);
    XMLElement* componentElement = document.NewElement(Rendering::SpriteRenderer::type_name());
    componentElement->SetAttribute("active", false);
    element->InsertFirstChild(componentsElement);
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    componentsElement->InsertFirstChild(componentElement);

    AssertCel::DoesNotHaveComponent<Rendering::SpriteRenderer>(gameObject);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getComponents().size());
    Assert::IsNotNull(dynamic_cast<const SpriteRendererDataConverter*>(converter.getComponents()[0]));

    converter.setValues(gameObject);

    AssertCel::HasComponent<Rendering::SpriteRenderer>(gameObject);
    AssertCel::IsNotActive(gameObject.findComponent<Rendering::SpriteRenderer>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_AddsLuaComponentsToGameObject)
  {
    LuaComponentManifestRegistry::registerComponent("Test", LuaState::instance().create_table());

    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    XMLElement* componentsElement = document.NewElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME);
    XMLElement* componentElement = document.NewElement("Test");
    element->InsertFirstChild(componentsElement);
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    componentsElement->InsertFirstChild(componentElement);

    AssertCel::DoesNotHaveComponent<LuaComponent>(gameObject);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getComponents().size());

    converter.setValues(gameObject);

    AssertCel::HasComponent<LuaComponent>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_SetsActiveComponentsToBeInactive_IfGameObjectIsInactive)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("GameObject");
    XMLElement* componentsElement = document.NewElement(GameObjectDataConverter::COMPONENTS_ELEMENT_NAME);
    XMLElement* componentElement = document.NewElement(Rendering::SpriteRenderer::type_name());
    element->InsertFirstChild(componentsElement);
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(GameObjectDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, false);
    componentsElement->InsertFirstChild(componentElement);

    AssertCel::DoesNotHaveComponent<Rendering::SpriteRenderer>(gameObject);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getComponents().size());
    Assert::IsNotNull(dynamic_cast<const SpriteRendererDataConverter*>(converter.getComponents()[0]));
    Assert::IsFalse(converter.getIsActive());

    converter.setValues(gameObject);

    AssertCel::HasComponent<Rendering::SpriteRenderer>(gameObject);
    AssertCel::IsNotActive(gameObject.findComponent<Rendering::SpriteRenderer>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_NoChildElements_DoesNotAddChildren)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(gameObject);

    Assert::IsTrue(converter.getChildGameObjects().empty());
    Assert::AreEqual(static_cast<size_t>(0), gameObject.getChildCount());
  }

#pragma region GameObject Instantiation

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_ChildGameObjects_InstantiatesChildrenCorrectly)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObject1 = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(gameObject);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::AreEqual(internString("Child1"), gameObject.getChild(0)->getName());
    Assert::AreEqual(internString("Child2"), gameObject.getChild(1)->getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_ChildGameObjects_ParentedToInputtedGameObject)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObject1 = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(gameObject);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::IsTrue(&gameObject == gameObject.getChild(0)->getParent());
    Assert::IsTrue(&gameObject == gameObject.getChild(1)->getParent());
  }

#pragma endregion

#pragma region Prefab Instantiation

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_ChildPrefabs_InstantiatesPrefabsCorrectly)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(gameObject);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::AreEqual(internString("GameObject1"), gameObject.getChild(0)->getName());
    Assert::AreEqual(internString("GameObject1"), gameObject.getChild(1)->getName());
    Assert::AreNotEqual(gameObject.getChild(0), gameObject.getChild(1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_ChildPrefabs_ParentedToInputtedGameObject)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(gameObject);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::AreEqual(&gameObject, gameObject.getChild(0)->getParent());
    Assert::AreEqual(&gameObject, gameObject.getChild(1)->getParent());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_ChildGameObjectsAndPrefabs_InstantiatesCorrectly)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObjectElement = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(gameObject);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::AreEqual(internString("Child1"), gameObject.getChild(0)->getName());
    Assert::AreEqual(internString("GameObject1"), gameObject.getChild(1)->getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_SetValues_ChildGameObjectsAndPrefabs_ParentedToInputtedGameObject)
  {
    GameObject gameObject;
    GameObjectDataConverter converter("GameObject");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObjectElement = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(gameObject);

    Assert::AreEqual(static_cast<size_t>(2), converter.getChildGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), gameObject.getChildCount());
    Assert::AreEqual(&gameObject, gameObject.getChild(0)->getParent());
    Assert::AreEqual(&gameObject, gameObject.getChild(1)->getParent());
  }

#pragma endregion

#pragma region Instantiate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_Instantiate_DataNotLoadedCorrectly_ReturnsNullptr)
  {
    GameObjectDataConverter converter("GameObject");
    observer_ptr<Data> data = getResourceManager().load<Data>(GameObjectLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));

    AutoDestroyer result = converter.instantiate();

    Assert::IsNull(result.m_gameObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObjectDataConverter_AllocateGameObject_DataLoadedCorrectly_ReturnsGameObject_WithDataSetToLoadedData)
  {
    GameObjectDataConverter converter("GameObject");
    observer_ptr<Data> data = getResourceManager().load<Data>(GameObjectLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));

    AutoDestroyer result = converter.instantiate();

    Assert::IsNotNull(result.m_gameObject.get());
    Assert::AreEqual(internString("TestName"), result.m_gameObject->getName());
    Assert::AreEqual(internString("Foreground"), result.m_gameObject->getTag());
    Assert::IsFalse(result.m_gameObject->isActive());
    Assert::AreEqual(glm::vec3(10, 0, 0), result.m_gameObject->getTransform()->getTranslation());
  }

#pragma endregion

  };
}

//----------------------------------------------------------------------------------------------------------
namespace Microsoft {
  namespace VisualStudio {
    namespace CppUnitTestFramework {

      template<>
      static std::wstring ToString<tinyxml2::XMLElement>(tinyxml2::XMLElement* element)
      {
        return std::to_wstring(reinterpret_cast<size_t>(element));
      }
    }
  }
}