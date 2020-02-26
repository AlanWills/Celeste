#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Callbacks/MockCallbackDataConverter.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestCallbackDataConverter)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    CallbackDataConverter converter("Callback");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_Constructor_SetsElementName_ToInput)
  {
    CallbackDataConverter converter("Callback");

    Assert::AreEqual("Callback", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_Constructor_SetsName_ToEmptyString)
  {
    CallbackDataConverter converter("Callback");

    Assert::IsTrue(converter.getName().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_Constructor_SetsArg_ToEmptyString)
  {
    CallbackDataConverter converter("Callback");

    Assert::IsTrue(converter.getArg().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_Constructor_AddsNameAttribute)
  {
    const MockCallbackDataConverter converter("Callback");
    
    Assert::IsNotNull(converter.findAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_Constructor_NameAttributeIsRequired)
  {
    const MockCallbackDataConverter converter("Callback");

    Assert::IsTrue(converter.findAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_Constructor_AddsArgAttribute)
  {
    const MockCallbackDataConverter converter("Callback");

    Assert::IsNotNull(converter.findAttribute(CallbackDataConverter::ARG_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_ConvertFromXML_NoNameAttribute_DoesNothing_ReturnsFalse)
  {
    MockCallbackDataConverter converter("Callback");
    XMLDocument document;
    const XMLElement* element = document.NewElement("Element");

    Assert::IsNull(element->FindAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getName().c_str());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual("", converter.getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_ConvertFromXML_NameAttribute_EmptyText_ReturnsTrue)
  {
    MockCallbackDataConverter converter("Callback");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getName().c_str());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("", converter.getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_ConvertFromXML_NameAttribute_NonEmptyText_SetsAttributeToCorrectValue_ReturnsTrue)
  {
    MockCallbackDataConverter converter("Callback");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getName().c_str());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("WubbaLubbaDubDub", converter.getName().c_str());
  }

#pragma endregion

#pragma region Convert Arg Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_ConvertFromXML_NoArgAttribute_DoesNothing_ReturnsTrue)
  {
    MockCallbackDataConverter converter("Callback");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME, "Name");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(CallbackDataConverter::ARG_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getArg().c_str());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("", converter.getArg().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_ConvertFromXML_ArgAttribute_EmptyText_ReturnsTrue)
  {
    MockCallbackDataConverter converter("Callback");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(CallbackDataConverter::ARG_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(CallbackDataConverter::ARG_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getArg().c_str());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("", converter.getArg().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CallbackDataConverter_ConvertFromXML_ArgAttribute_NonEmptyText_SetsAttributeToCorrectValue_ReturnsTrue)
  {
    MockCallbackDataConverter converter("Callback");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute(CallbackDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->SetAttribute(CallbackDataConverter::ARG_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(CallbackDataConverter::ARG_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getArg().c_str());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("WubbaLubbaDubDub", converter.getArg().c_str());
  }

#pragma region

  };
}