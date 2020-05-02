#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Input/MockKeyboardRigidBody2DControllerDataConverter.h"
#include "TestResources/Input/KeyboardRigidBody2DControllerLoadingResources.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Deserialization/InputDeserializers.h"
#include "Resources/ResourceManager.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKeyboardRigidBody2DControllerDataConverter)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    KeyboardRigidBody2DControllerLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<KeyboardRigidBody2DControllerDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardRigidBody2DControllerLoadingResources::getValidFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsTrue(dynamic_cast<KeyboardRigidBody2DController*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Instantiate_SetsInputtedPointer_ToNewKeyboardRigidBody2DControllerDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    KeyboardRigidBody2DControllerDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<KeyboardRigidBody2DControllerDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsDecreaseXLinearVelocityKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseXLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncreaseXLinearVelocityKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseXLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsDecreaseYLinearVelocityKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseYLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncreaseYLinearVelocityKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseYLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsDecreaseAngularVelocityKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseAngularVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncreaseAngularVelocityKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseAngularVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsLinearVelocityDelta_ToZeroVector)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocityDelta());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsAngularVelocityDelta_ToZeroVector)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::AreEqual(0.0f, converter.getAngularVelocityDelta());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsSpace_To_kLocal)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsTrue(Maths::Space::kLocal == converter.getSpace());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncrementMode_To_kContinuous)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsTrue(Input::IncrementMode::kContinuous == converter.getIncrementMode());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsDecreaseXLinearVelocityKeyAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;
    
    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsIncreaseXLinearVelocityKeyAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsDecreaseYLinearVelocityKeyAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsIncreaseYLinearVelocityKeyAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsDecreaseAngularVelocityKeyAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsIncreaseAngularVelocityKeyAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsLinearVelocityDeltaAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsAngularVelocityDeltaAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsSpaceAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_AddsIncrementModeAttribute)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsDecreaseXLinearVelocityKeyAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncreaseXLinearVelocityKeyAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsDecreaseYLinearVelocityKeyAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncreaseYLinearVelocityKeyAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsDecreaseAngularVelocityKeyAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncreaseAngularVelocityKeyAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsSpaceAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_Constructor_SetsIncrementModeAttribute_ToNotRequired)
  {
    const MockKeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardRigidBody2DControllerLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardRigidBody2DControllerLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardRigidBody2DControllerLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardRigidBody2DControllerLoadingResources::getValidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Decrease X Linear Velocity Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoDecreaseXLinearVelocityKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseXLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseXLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_DecreaseXLinearVelocityKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseXLinearVelocityKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseXLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_DecreaseXLinearVelocityKeyAttribute_WithValidText_ReturnsTrue_SetsDecreaseXLinearVelocityToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseXLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getDecreaseXLinearVelocityKey());
  }

#pragma endregion

#pragma region Convert Increase X Linear Velocity Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoIncreaseXLinearVelocityKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseXLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseXLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncreaseXLinearVelocityKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseXLinearVelocityKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseXLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncreaseXLinearVelocityKeyAttribute_WithValidText_ReturnsTrue_SetsIncreaseXLinearVelocityToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseXLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getIncreaseXLinearVelocityKey());
  }

#pragma endregion

#pragma region Convert Decrease Y Linear Velocity Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoDecreaseYLinearVelocityKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseYLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseYLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_DecreaseYLinearVelocityKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseYLinearVelocityKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseYLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_DecreaseXLinearVelocityKeyAttribute_WithValidText_ReturnsTrue_SetsDecreaseYLinearVelocityToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseYLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getDecreaseYLinearVelocityKey());
  }

#pragma endregion

#pragma region Convert Increase Y Linear Velocity Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoIncreaseYLinearVelocityKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseYLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseYLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncreaseYLinearVelocityKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseYLinearVelocityKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseYLinearVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncreaseYLinearVelocityKeyAttribute_WithValidText_ReturnsTrue_SetsIncreaseYLinearVelocityToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseYLinearVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getIncreaseYLinearVelocityKey());
  }

#pragma endregion

#pragma region Convert Decrease Angular Velocity Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoDecreaseAngularVelocityKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseAngularVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseAngularVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_DecreaseAngularVelocityKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseAngularVelocityKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseAngularVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_DecreaseAngularVelocityKeyAttribute_WithValidText_ReturnsTrue_SetsDecreaseAngularVelocityToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getDecreaseAngularVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getDecreaseAngularVelocityKey());
  }

#pragma endregion

#pragma region Convert Increase Angular Velocity Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoIncreaseAngularVelocityKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseAngularVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseAngularVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncreaseAngularVelocityKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseAngularVelocityKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseAngularVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncreaseAngularVelocityKeyAttribute_WithValidText_ReturnsTrue_SetsIncreaseAngularVelocityToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getIncreaseAngularVelocityKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getIncreaseAngularVelocityKey());
  }

#pragma endregion

#pragma region Convert Linear Velocity Delta Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoLinearVelocityDeltaAttribute_ReturnsTrue_SetsDeltaToZeroVector)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocityDelta());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocityDelta());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_LinearVelocityDeltaAttribute_WithInvalidText_ReturnsFalse_SetsDeltaToZeroVector)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocityDelta());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocityDelta());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_LinearVelocityDeltaAttribute_WithValidText_ReturnsTrue_SetsLinearVelocityDeltaToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME, "2, 3");

    Assert::AreEqual("2, 3", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
    Assert::AreEqual(glm::zero<glm::vec2>(), converter.getLinearVelocityDelta());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(2, 3), converter.getLinearVelocityDelta());
  }

#pragma endregion

#pragma region Convert Angular Velocity Delta Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoAngularVelocityDeltaAttribute_ReturnsTrue_SetsDeltaToZero)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getAngularVelocityDelta());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getAngularVelocityDelta());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_AngularVelocityDeltaAttribute_WithInvalidText_ReturnsFalse_SetsDeltaToZero)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getAngularVelocityDelta());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getAngularVelocityDelta());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_AngularVelocityDeltaAttribute_WithValidText_ReturnsTrue_SetsAngularVelocityDeltaToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME, "-0.123");

    Assert::AreEqual("-0.123", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getAngularVelocityDelta());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(-0.123f, converter.getAngularVelocityDelta());
  }

#pragma endregion

#pragma region Convert Space Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoSpaceAttribute_ReturnsTrue_SetsSpaceTo_kLocal)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getSpace() == Maths::Space::kLocal);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getSpace() == Maths::Space::kLocal);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_SpaceAttribute_WithInvalidText_ReturnsFalse_SetsSpaceTo_kLocal)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getSpace() == Maths::Space::kLocal);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getSpace() == Maths::Space::kLocal);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_SpaceAttribute_WithValidText_ReturnsTrue_SetsSpaceToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME, "World");

    Assert::AreEqual("World", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getSpace() == Maths::Space::kLocal);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getSpace() == Maths::Space::kWorld);
  }

#pragma endregion

#pragma region Increment Mode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_NoIncrementModeAttribute_ReturnsTrue_SetsIncrementModeTo_kContinuous)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIncrementMode() == Input::IncrementMode::kContinuous);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIncrementMode() == Input::IncrementMode::kContinuous);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncrementModeAttribute_WithInvalidText_ReturnsFalse_SetsIncrementModeTo_kContinuous)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIncrementMode() == Input::IncrementMode::kContinuous);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIncrementMode() == Input::IncrementMode::kContinuous);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_ConvertFromXML_IncrementModeAttribute_WithValidText_ReturnsTrue_SetsIncrementModeToCorrectValue)
  {
    KeyboardRigidBody2DControllerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardRigidBody2DController");
    element->SetAttribute(KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME, "Toggle");

    Assert::AreEqual("Toggle", static_cast<const XMLElement*>(element)->Attribute(KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIncrementMode() == Input::IncrementMode::kContinuous);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIncrementMode() == Input::IncrementMode::kToggle);
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_SetValues_InputtingKeyboardRigidBody2DController_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    KeyboardRigidBody2DController rigidBodyController(gameObject);
    rigidBodyController.setDecreaseAngularVelocityKey(GLFW_KEY_A);
    rigidBodyController.setLinearVelocityDelta(0.3f, 2);

    KeyboardRigidBody2DControllerDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(rigidBodyController);

    Assert::AreEqual(glm::vec2(0.3f, 2), rigidBodyController.getLinearVelocityDelta());
    Assert::AreEqual(GLFW_KEY_A, rigidBodyController.getDecreaseAngularVelocityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DControllerDataConverter_SetValues_InputtingKeyboardRigidBody2DController_DataLoadedCorrectly_ChangesKeyboardRigidBody2DControllerToMatchData)
  {
    GameObject gameObject;
    KeyboardRigidBody2DController rigidBodyController(gameObject);
    rigidBodyController.setDecreaseAngularVelocityKey(GLFW_KEY_J);
    rigidBodyController.setLinearVelocityDelta(0.3f, 2);

    KeyboardRigidBody2DControllerDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(KeyboardRigidBody2DControllerLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(rigidBodyController);

    Assert::AreEqual(GLFW_KEY_A, rigidBodyController.getDecreaseXLinearVelocityKey());
    Assert::AreEqual(GLFW_KEY_B, rigidBodyController.getIncreaseXLinearVelocityKey());
    Assert::AreEqual(GLFW_KEY_C, rigidBodyController.getDecreaseYLinearVelocityKey());
    Assert::AreEqual(GLFW_KEY_D, rigidBodyController.getIncreaseYLinearVelocityKey());
    Assert::AreEqual(GLFW_KEY_E, rigidBodyController.getDecreaseAngularVelocityKey());
    Assert::AreEqual(GLFW_KEY_F, rigidBodyController.getIncreaseAngularVelocityKey());
    Assert::AreEqual(glm::vec2(1, 2), rigidBodyController.getLinearVelocityDelta());
    Assert::AreEqual(4.0f, rigidBodyController.getAngularVelocityDelta());
    Assert::IsTrue(rigidBodyController.getSpace() == Maths::Space::kWorld);
    Assert::IsTrue(rigidBodyController.getIncrementMode() == Input::IncrementMode::kToggle);
  }

#pragma endregion

  };
}