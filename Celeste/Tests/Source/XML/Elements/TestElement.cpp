#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/XML/Elements/MockElement.h"

using namespace Celeste;
using namespace tinyxml2;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestElement)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_Constructor_SetsElementNameToInput)
  {
    MockElement element("Test");

    Assert::AreEqual("Test", element.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_Constructor_SetsRequiredToInput)
  {
    MockElement element("Test", DeserializationRequirement::kRequired);

    Assert::IsTrue(element.isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_Constructor_SetsIsUsingDefaultValue_ToTrue)
  {
    MockElement element("Test", DeserializationRequirement::kRequired);

    Assert::IsTrue(element.isUsingDefaultValue());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    MockElement element("");

    Assert::IsFalse(element.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_ConvertFromXML_InputtingNullptr_SetsIsUsingDefaultValue_ToTrue)
  {
    MockElement element("");
    element.convertFromXML(nullptr);

    Assert::IsTrue(element.isUsingDefaultValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_ConvertFromXML_InputtingNullptr_DoesNotCallDoConvertFromXML)
  {
    MockElement element("");

    Assert::IsFalse(element.isDoConvertFromXMLCalled());

    element.convertFromXML(nullptr);

    Assert::IsFalse(element.isDoConvertFromXMLCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_ConvertFromXML_InputtingNonNullElement_ReturnsResultOfDoConvertFromXML)
  {
    MockElement element("");
    XMLDocument document;
    XMLElement* ele = document.NewElement("Test");
    element.setDoConvertResult(true);

    Assert::IsTrue(element.convertFromXML(ele));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_ConvertFromXML_InputtingNonNullElement_SetsIsUsingDefaultValue_ToCorrectValue)
  {
    MockElement element("");
    XMLDocument document;
    XMLElement* ele = document.NewElement("Test");

    element.setDoConvertResult(true);
    element.convertFromXML(ele);

    Assert::IsFalse(element.isUsingDefaultValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Element_ConvertFromXML_InputtingNonNullElement_CallsDoConvertFromXML)
  {
    MockElement ele("Test");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsFalse(ele.isDoConvertFromXMLCalled());

    ele.convertFromXML(element);

    Assert::IsTrue(ele.isDoConvertFromXMLCalled());
  }

#pragma endregion

  };
}