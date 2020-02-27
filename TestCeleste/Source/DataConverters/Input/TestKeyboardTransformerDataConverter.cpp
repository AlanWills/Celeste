#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Input/MockKeyboardTransformerDataConverter.h"
#include "Resources/Input/KeyboardTransformerLoadingResources.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Resources/ResourceManager.h"
#include "Input/KeyboardTransformer.h"
#include "AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKeyboardTransformerDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestKeyboardTransformerDataConverter::testInitialize()
  {
    KeyboardTransformerLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<KeyboardTransformerDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardTransformerLoadingResources::getValidFullPath());
    AutoDeallocator<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<KeyboardTransformer*>(component.get()));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Instantiate_SetsInputtedPointer_ToNewKeyboardTransformerDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    KeyboardTransformerDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<KeyboardTransformerDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    KeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    KeyboardTransformerDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateLeftKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateLeftKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateRightKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateRightKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateUpKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateUpKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateDownKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateDownKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsRotateLeftKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateLeftKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsRotateRightKey_To_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateRightKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslationSpeed_ToOne)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(1.0f, converter.getTranslationSpeed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsRotationSpeed_ToZeroPointZeroOne)
  {
    KeyboardTransformerDataConverter converter;

    Assert::AreEqual(0.01f, converter.getRotationSpeed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsTranslateLeftKeyAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;
    
    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsTranslateRightKeyAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsTranslateUpKeyAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsTranslateDownKeyAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsRotateLeftKeyAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsRotateRightKeyAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsTranslationSpeedAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_AddsRotationSpeedAttribute)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateLeftKeyAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateRightKeyAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateUpKeyAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslateDownKeyAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsRotateLeftKeyAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsRotateRightKeyAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsTranslationSpeedAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_Constructor_SetsRotationSpeedAttribute_ToNotRequired)
  {
    const MockKeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.findAttribute(KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    KeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    KeyboardTransformerDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    KeyboardTransformerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardTransformerLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    KeyboardTransformerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardTransformerLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    KeyboardTransformerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardTransformerLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    KeyboardTransformerDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(KeyboardTransformerLoadingResources::getValidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Translate Left Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoTranslateLeftKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateLeftKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateLeftKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslateLeftKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateLeftKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateLeftKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslateLeftKeyAttribute_WithValidText_ReturnsTrue_SetsTranslateLeftKeyToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateLeftKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getTranslateLeftKey());
  }

#pragma endregion

#pragma region Convert Translate Right Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoTranslateRightKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateRightKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateRightKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslateRightKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateRightKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateRightKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslateRightKeyAttribute_WithValidText_ReturnsTrue_SetsTranslateRightKeyToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateRightKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getTranslateRightKey());
  }

#pragma endregion

#pragma region Convert Translate Up Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoTranslateUpKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateUpKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateUpKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslateUpKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateUpKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateUpKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslateUpKeyAttribute_WithValidText_ReturnsTrue_SetsTranslateUpKeyToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateUpKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getTranslateUpKey());
  }

#pragma endregion

#pragma region Convert Translate Down Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoTranslateDownKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateDownKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateDownKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslateDownKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateDownKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateDownKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_MoveDownAttribute_WithValidText_ReturnsTrue_SetsTranslateDownKeyToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTranslateDownKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getTranslateDownKey());
  }

#pragma endregion

#pragma region Convert Rotate Left Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoRotateLeftKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateLeftKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateLeftKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_RotateLeftKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateLeftKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateLeftKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_RotateLeftAttribute_WithValidText_ReturnsTrue_SetsRotateLeftKeyToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateLeftKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getRotateLeftKey());
  }

#pragma endregion

#pragma region Convert RotateRight Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoRotateRightKeyAttribute_ReturnsTrue_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateRightKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateRightKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_RotateRightKeyAttribute_WithInvalidText_ReturnsFalse_SetsKeyTo_GLFW_KEY_UNKNOWN)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateRightKey());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateRightKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_RotateRightAttribute_WithValidText_ReturnsTrue_SetsRotateRightKeyToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME, "A");

    Assert::AreEqual("A", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getRotateRightKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getRotateRightKey());
  }

#pragma endregion

#pragma region Convert Translation Speed Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoTranslationSpeedAttribute_ReturnsTrue_SetsTranslationSpeedToOne)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getTranslationSpeed());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getTranslationSpeed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslationSpeedAttribute_WithInvalidText_ReturnsFalse_SetsTranslationSpeedToOne)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getTranslationSpeed());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getTranslationSpeed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_TranslationSpeedAttribute_WithValidText_ReturnsTrue_SetsTranslationSpeedToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME, "-0.123");

    Assert::AreEqual("-0.123", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getTranslationSpeed());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(-0.123f, converter.getTranslationSpeed());
  }

#pragma endregion

#pragma region Convert Rotation Speed Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_NoRotationSpeedAttribute_ReturnsTrue_SetsRotationSpeedToZeroPointZeroOne)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");

    Assert::IsNull(static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME));
    Assert::AreEqual(0.01f, converter.getRotationSpeed());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.01f, converter.getRotationSpeed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_RotationSpeedAttribute_WithInvalidText_ReturnsFalse_SetsRotationSpeedToZeroPointZeroOne)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME));
    Assert::AreEqual(0.01f, converter.getRotationSpeed());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.01f, converter.getRotationSpeed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_ConvertFromXML_RotationSpeedAttribute_WithValidText_ReturnsTrue_SetsRotationSpeedToCorrectValue)
  {
    KeyboardTransformerDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("KeyboardTransformer");
    element->SetAttribute(KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME, "-0.123");

    Assert::AreEqual("-0.123", static_cast<const XMLElement*>(element)->Attribute(KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME));
    Assert::AreEqual(0.01f, converter.getRotationSpeed());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(-0.123f, converter.getRotationSpeed());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_SetValues_InputtingNullKeyboardTransformer_DoesNothing)
  {
    KeyboardTransformerDataConverter converter;
    converter.setValues(KeyboardTransformer());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_SetValues_InputtingKeyboardTransformer_DataNotLoadedCorrectly_DoesNothing)
  {
    KeyboardTransformer translator;
    translator.setTranslateLeftKey(GLFW_KEY_A);
    translator.setTranslationSpeed(0.3f);

    KeyboardTransformerDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(translator);

    Assert::AreEqual(GLFW_KEY_A, translator.getTranslateLeftKey());
    Assert::AreEqual(0.3f, translator.getTranslationSpeed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardTransformerDataConverter_SetValues_InputtingKeyboardTransformer_DataLoadedCorrectly_ChangesKeyboardTransformerToMatchData)
  {
    KeyboardTransformer translator;
    translator.setTranslateLeftKey(GLFW_KEY_A);
    translator.setTranslationSpeed(0.3f);

    KeyboardTransformerDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(KeyboardTransformerLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(translator);

    Assert::AreEqual(GLFW_KEY_A, translator.getTranslateLeftKey());
    Assert::AreEqual(GLFW_KEY_B, translator.getTranslateRightKey());
    Assert::AreEqual(GLFW_KEY_C, translator.getTranslateUpKey());
    Assert::AreEqual(GLFW_KEY_D, translator.getTranslateDownKey());
    Assert::AreEqual(GLFW_KEY_E, translator.getRotateLeftKey());
    Assert::AreEqual(GLFW_KEY_F, translator.getRotateRightKey());
    Assert::AreEqual(4.0f, translator.getTranslationSpeed());
    Assert::AreEqual(0.5f, translator.getRotationSpeed());
  }

#pragma endregion

  };
}