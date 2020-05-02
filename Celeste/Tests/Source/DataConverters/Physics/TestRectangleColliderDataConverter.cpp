#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Physics/MockRectangleColliderDataConverter.h"
#include "TestResources/Physics/RectangleColliderLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Physics/RectangleCollider.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::Physics;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestRectangleColliderDataConverter)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    RectangleColliderLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<RectangleColliderDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(RectangleColliderLoadingResources::getValidFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<RectangleCollider*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Instantiate_SetsInputtedPointer_ToNewRectangleColliderDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    RectangleColliderDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<RectangleColliderDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    RectangleColliderDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    RectangleColliderDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_SetsIsTrigger_ToFalse)
  {
    RectangleColliderDataConverter converter;

    Assert::IsFalse(converter.getIsTrigger());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_SetsDimensions_ToZeroVector)
  {
    RectangleColliderDataConverter converter;

    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_SetsOffset_ToZeroVector)
  {
    RectangleColliderDataConverter converter;

    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getOffset());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_AddsIsTriggerAttribute)
  {
    const MockRectangleColliderDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_AddsDimensionsAttribute)
  {
    const MockRectangleColliderDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_AddsOffsetAttribute)
  {
    const MockRectangleColliderDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RectangleColliderDataConverter::OFFSET_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_Constructor_SetsDimensionsAttribute_TokNotRequired)
  {
    const MockRectangleColliderDataConverter converter;

    Assert::IsFalse(converter.findAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    RectangleColliderDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    RectangleColliderDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    RectangleColliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RectangleColliderLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    RectangleColliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RectangleColliderLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    RectangleColliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RectangleColliderLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    RectangleColliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RectangleColliderLoadingResources::getValidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Is Trigger Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_NoTriggerAttribute_ReturnsTrue_DoesNothing)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RectangleCollider");
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "1,1");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsTrigger());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsTrigger());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_TriggerAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RectangleCollider");
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "1,1");
    element->SetAttribute(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsTrigger());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsTrigger());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_TriggerAttribute_WithValidText_ReturnsTrue_SetsIsTriggerToCorrectValue)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RectangleCollider");
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "1,1");
    element->SetAttribute(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME, "true");

    Assert::AreEqual("true", static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsTrigger());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsTrigger());
  }

#pragma endregion

#pragma region Convert Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_NoDimensionsAttribute_ReturnsTrue_SetsDimensionsToZeroVector)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RectangleCollider");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getDimensions());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_DimensionsAttribute_WithInvalidText_ReturnsFalse_SetsDimensionsToZeroVector)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME);
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getDimensions());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_DimensionsAttribute_WithValidText_ReturnsTrue_SetsDimensionsToCorrectValue)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RectangleCollider");
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "10,15");

    Assert::AreEqual("10,15", static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getDimensions());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(10, 15), converter.getDimensions());
  }

#pragma endregion

#pragma region Convert Offset Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_NoOffsetAttribute_ReturnsTrue_DoesNothing)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RectangleCollider");
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "1,1");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::OFFSET_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getOffset());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getOffset());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_OffsetAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement(RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME);
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "1,1");
    element->SetAttribute(RectangleColliderDataConverter::OFFSET_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::OFFSET_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getOffset());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getOffset());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_ConvertFromXML_OffsetAttribute_WithValidText_ReturnsTrue_SetsOffsetToCorrectValue)
  {
    RectangleColliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RectangleCollider");
    element->SetAttribute(RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME, "1,1");
    element->SetAttribute(RectangleColliderDataConverter::OFFSET_ATTRIBUTE_NAME, "10,15");

    Assert::AreEqual("10,15", static_cast<const XMLElement*>(element)->Attribute(RectangleColliderDataConverter::OFFSET_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getOffset());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(10, 15), converter.getOffset());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_SetValues_InputtingRectangleCollider_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);
    collider.setColliderType(Physics::ColliderType::kTrigger);
    collider.setOffset(0.1f, 0.2f);

    RectangleColliderDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(collider);

    Assert::IsTrue(collider.getColliderType() == ColliderType::kTrigger);
    Assert::AreEqual(glm::vec2(0.1f, 0.2f), collider.getOffset());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RectangleColliderDataConverter_SetValues_InputtingRectangleCollider_DataLoadedCorrectly_ChangesRectangleColliderToMatchData)
  {
    GameObject gameObject;
    RectangleCollider collider(gameObject);
    collider.setOffset(0.1f, 0.2f);

    Assert::IsTrue(collider.getColliderType() == ColliderType::kCollider);

    RectangleColliderDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(RectangleColliderLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(collider);

    Assert::AreEqual(50.0f, collider.getDimensions().x);
    Assert::AreEqual(70.0f, collider.getDimensions().y);
    Assert::AreEqual(glm::vec2(5.0f, 12.0f), collider.getOffset());
    Assert::IsTrue(collider.getColliderType() == ColliderType::kTrigger);
  }

#pragma endregion

};

}