#include "UtilityHeaders/UnitTestHeaders.h"

#include "Utils/ScreenXMLUtils.h"
#include "DataConverters/Screens/ScreenDataConverter.h"
#include "Screens/Screen.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestScreenXMLUtils)

#pragma region Create Screen Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestScreenXMLUtils_CreateScreenElement_ReturnsNewElementInstance)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document);

    Assert::IsNotNull(element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestScreenXMLUtils_CreateScreenElement_AddsElementToEndOfDocument)
  {
    XMLDocument document;
    document.InsertFirstChild(document.NewElement("FirstChild"));
    tinyxml2::XMLElement* element = createScreenElement(document);

    Assert::IsTrue(document.LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestScreenXMLUtils_CreateScreenElement_SetsElementNameToCorrectValue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document);

    Assert::AreEqual(ScreenDataConverter::SCREEN_ELEMENT_NAME, element->Name());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestScreenXMLUtils_CreateScreenElement_NotInputtingName_SetsNameAttributeToNull)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document);

    Assert::IsNull(element->Attribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestScreenXMLUtils_CreateScreenElement_InputtingName_SetsNameAttributeToInputtedValue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");

    Assert::AreEqual("Test", element->Attribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
  }

#pragma endregion

  };
}