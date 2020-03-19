#define NOMINMAX  // Disable windows.h min/max macros

#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Physics/MockRigidBody2DDataConverter.h"
#include "TestResources/Physics/RigidBody2DLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Physics/RigidBody2D.h"
#include "AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::Physics;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestRigidBody2DDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestRigidBody2DDataConverter::testInitialize()
  {
    RigidBody2DLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<RigidBody2DDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(RigidBody2DLoadingResources::getValidFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<RigidBody2D*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Instantiate_SetsInputtedPointer_ToNewRigidBody2DDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    RigidBody2DDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<RigidBody2DDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    RigidBody2DDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    RigidBody2DDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsLinearVelocity_ToZeroVector)
  {
    RigidBody2DDataConverter converter;

    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsMinLinearVelocity_ToNegativeFloatMaxVector)
  {
    RigidBody2DDataConverter converter;

    Assert::AreEqual(glm::vec2(-std::numeric_limits<float>::max()), converter.getMinLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsMaxLinearVelocity_ToFloatMaxVector)
  {
    RigidBody2DDataConverter converter;

    Assert::AreEqual(glm::vec2(std::numeric_limits<float>::max()), converter.getMaxLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsAngularVelocity_ToZero)
  {
    RigidBody2DDataConverter converter;

    Assert::AreEqual(0.0f, converter.getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsMinAngularVelocity_ToNegativeFloatMax)
  {
    RigidBody2DDataConverter converter;

    Assert::AreEqual(-std::numeric_limits<float>::max(), converter.getMinAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_SetsMaxAngularVelocity_ToFloatMax)
  {
    RigidBody2DDataConverter converter;

    Assert::AreEqual(std::numeric_limits<float>::max(), converter.getMaxAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_AddsLinearVelocityAttribute)
  {
    const MockRigidBody2DDataConverter converter;
    
    Assert::IsNotNull(converter.findAttribute(RigidBody2DDataConverter::LINEAR_VELOCITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_AddsMinLinearVelocityAttribute)
  {
    const MockRigidBody2DDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RigidBody2DDataConverter::MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_AddsMaxLinearVelocityAttribute)
  {
    const MockRigidBody2DDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RigidBody2DDataConverter::MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_AddsAngularVelocityAttribute)
  {
    const MockRigidBody2DDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RigidBody2DDataConverter::ANGULAR_VELOCITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_AddsMinAngularVelocityAttribute)
  {
    const MockRigidBody2DDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RigidBody2DDataConverter::MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_Constructor_AddsOffsetAttribute)
  {
    const MockRigidBody2DDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(RigidBody2DDataConverter::MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    RigidBody2DDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    RigidBody2DDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    RigidBody2DDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RigidBody2DLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    RigidBody2DDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RigidBody2DLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    RigidBody2DDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RigidBody2DLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    RigidBody2DDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(RigidBody2DLoadingResources::getValidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Linear Velocity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_NoLinearVelocityAttribute_ReturnsTrue_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_LinearVelocityAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::LINEAR_VELOCITY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_LinearVelocityAttribute_WithValidText_ReturnsTrue_SetsLinearVelocityToCorrectValue)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::LINEAR_VELOCITY_ATTRIBUTE_NAME, "1, -2");

    Assert::AreEqual("1, -2", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(1, -2), converter.getLinearVelocity());
  }

#pragma endregion

#pragma region Convert Min Linear Velocity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_NoMinLinearVelocityAttribute_ReturnsTrue_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::vec2(-FLT_MAX), converter.getMinLinearVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(-FLT_MAX), converter.getMinLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MinLinearVelocityAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::vec2(-FLT_MAX), converter.getMinLinearVelocity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(-FLT_MAX), converter.getMinLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MinLinearVelocityAttribute_WithValidText_ReturnsTrue_SetsMinLinearVelocityToCorrectValue)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME, "1, -2");

    Assert::AreEqual("1, -2", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::vec2(-FLT_MAX), converter.getMinLinearVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(1, -2), converter.getMinLinearVelocity());
  }

#pragma endregion

#pragma region Convert Max Linear Velocity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_NoMaxLinearVelocityAttribute_ReturnsTrue_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::vec2(FLT_MAX), converter.getMaxLinearVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(FLT_MAX), converter.getMaxLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MaxLinearVelocityAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::vec2(FLT_MAX), converter.getMaxLinearVelocity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(FLT_MAX), converter.getMaxLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MaxLinearVelocityAttribute_WithValidText_ReturnsTrue_SetsMaxLinearVelocityToCorrectValue)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME, "1, -2");

    Assert::AreEqual("1, -2", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::vec2(FLT_MAX), converter.getMaxLinearVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(1, -2), converter.getMaxLinearVelocity());
  }

#pragma endregion

#pragma region Convert Angular Velocity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_NoAngularVelocityAttribute_ReturnsTrue_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getAngularVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_AngularVelocityAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::ANGULAR_VELOCITY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getAngularVelocity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_AngularVelocityAttribute_WithValidText_ReturnsTrue_SetsAngularVelocityToCorrectValue)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::ANGULAR_VELOCITY_ATTRIBUTE_NAME, "1.2");

    Assert::AreEqual("1.2", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getAngularVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.2f, converter.getAngularVelocity());
  }

#pragma endregion

#pragma region Convert Min Angular Velocity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_NoMinAngularVelocityAttribute_ReturnsTrue_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(-FLT_MAX, converter.getMinAngularVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(-FLT_MAX, converter.getMinAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MinAngularVelocityAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(-FLT_MAX, converter.getMinAngularVelocity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(-FLT_MAX, converter.getMinAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MinAngularVelocityAttribute_WithValidText_ReturnsTrue_SetsMinAngularVelocityToCorrectValue)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME, "1.2");

    Assert::AreEqual("1.2", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(-FLT_MAX, converter.getMinAngularVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.2f, converter.getMinAngularVelocity());
  }

#pragma endregion

#pragma region Convert Max Angular Velocity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_NoMaxAngularVelocityAttribute_ReturnsTrue_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(FLT_MAX, converter.getMaxAngularVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(FLT_MAX, converter.getMaxAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MaxAngularVelocityAttribute_WithInvalidText_ReturnsFalse_DoesNothing)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(FLT_MAX, converter.getMaxAngularVelocity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(FLT_MAX, converter.getMaxAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_ConvertFromXML_MaxAngularVelocityAttribute_WithValidText_ReturnsTrue_SetsMaxAngularVelocityToCorrectValue)
  {
    RigidBody2DDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("RigidBody2D");
    element->SetAttribute(RigidBody2DDataConverter::MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME, "1.2");

    Assert::AreEqual("1.2", static_cast<const XMLElement*>(element)->Attribute(RigidBody2DDataConverter::MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME));
    Assert::AreEqual(FLT_MAX, converter.getMaxAngularVelocity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.2f, converter.getMaxAngularVelocity());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_SetValues_InputtingRigidBody2D_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    RigidBody2D rigidBody(gameObject);
    rigidBody.setLinearVelocity(1, 2);
    rigidBody.setAngularVelocity(0.3f);

    RigidBody2DDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(rigidBody);

    Assert::AreEqual(glm::vec2(1, 2), rigidBody.getLinearVelocity());
    Assert::AreEqual(0.3f, rigidBody.getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RigidBody2DDataConverter_SetValues_InputtingRigidBody2D_DataLoadedCorrectly_ChangesRigidBody2DToMatchData)
  {
    GameObject gameObject;
    RigidBody2D rigidBody(gameObject);
    rigidBody.setLinearVelocity(1, 2);
    rigidBody.setAngularVelocity(0.3f);

    RigidBody2DDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(RigidBody2DLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(rigidBody);

    Assert::AreEqual(glm::vec2(120, 4), rigidBody.getLinearVelocity());
    Assert::AreEqual(glm::vec2(1, -1), rigidBody.getMinLinearVelocity());
    Assert::AreEqual(glm::vec2(1000, 1000), rigidBody.getMaxLinearVelocity());
    Assert::AreEqual(0.25f, rigidBody.getAngularVelocity());
    Assert::AreEqual(0.0f, rigidBody.getMinAngularVelocity());
    Assert::AreEqual(2.2f, rigidBody.getMaxAngularVelocity());
  }

#pragma endregion

  };
}