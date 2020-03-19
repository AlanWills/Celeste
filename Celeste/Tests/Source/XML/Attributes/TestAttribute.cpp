#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/XML/Attributes/MockAttribute.h"

using namespace tinyxml2;
using namespace Celeste;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestAttribute)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_Constructor_SetsNameToInput)
  {
    MockAttribute attr("Test");

    Assert::AreEqual("Test", attr.getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_Constructor_SetsRequiredToInput)
  {
    MockAttribute attr("Test", DeserializationRequirement::kRequired);

    Assert::IsTrue(attr.isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_Constructor_SetsIsUsingDefaultValue_ToTrue)
  {
    MockAttribute attr("Test", DeserializationRequirement::kRequired);

    Assert::IsTrue(attr.isUsingDefaultValue());
  }

#pragma endregion

#pragma region ConvertFromXML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    MockAttribute attr("");

    Assert::IsFalse(attr.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_ConvertFromXML_SetsIsUsingDefaultValue_ToTrue)
  {
    MockAttribute attr("Test", DeserializationRequirement::kRequired);
    attr.convertFromXML(nullptr);

    Assert::IsTrue(attr.isUsingDefaultValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_ConvertFromXML_InputtingNullptr_DoesNotCallDoConvertFromXML)
  {
    MockAttribute attr("");

    Assert::IsFalse(attr.isDoConvertFromXMLCalled());

    attr.convertFromXML(nullptr);

    Assert::IsFalse(attr.isDoConvertFromXMLCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_ConvertFromXML_InputtingNonNullAttribute_NonNullText_ReturnsResultOfDoConvertFromXML)
  {
    MockAttribute attr("Test");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute("Test", "Value");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("Test"));
    Assert::IsFalse(attr.isDoConvertFromXMLCalled());

    attr.setDoConvertResult(true);

    Assert::IsTrue(attr.convertFromXML(static_cast<const XMLElement*>(element)->FindAttribute("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_ConvertFromXML_InputtingNonNullAttribute_NonNullText_SetsIsUsingDefaultValueToCorrectValue)
  {
    MockAttribute attr("Test", DeserializationRequirement::kRequired);
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute("Test", "Value");

    attr.setDoConvertResult(false);
    attr.convertFromXML(static_cast<const XMLElement*>(element)->FindAttribute("Test"));

    Assert::IsTrue(attr.isUsingDefaultValue());

    attr.setDoConvertResult(true);
    attr.convertFromXML(static_cast<const XMLElement*>(element)->FindAttribute("Test"));

    Assert::IsFalse(attr.isUsingDefaultValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Attribute_ConvertFromXML_InputtingNonNullAttribute_NonNullText_CallsDoConvertFromXML)
  {
    MockAttribute attr("Test");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute("Test", "Value");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("Test"));
    Assert::IsFalse(attr.isDoConvertFromXMLCalled());

    attr.convertFromXML(static_cast<const XMLElement*>(element)->FindAttribute("Test"));

    Assert::IsTrue(attr.isDoConvertFromXMLCalled());
  }

#pragma endregion

  };

}