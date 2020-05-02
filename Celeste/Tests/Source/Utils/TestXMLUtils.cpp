#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "TestUtils/Utils/XMLUtils.h"

using namespace tinyxml2;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestXMLUtils)

#pragma region Create Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestXMLUtils_CreateElement_ReturnsNewElementInstance)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createElement(document, "Test");

    Assert::IsNotNull(element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestXMLUtils_CreateElement_AddsElementToEndOfDocument)
  {
    XMLDocument document;
    document.InsertFirstChild(document.NewElement("FirstChild"));
    tinyxml2::XMLElement* element = createElement(document, "Test");

    Assert::IsTrue(document.LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestXMLUtils_CreateElement_InputtingParent_AddsElementToEndOfInputtedParent)
  {
    XMLDocument document;
    tinyxml2::XMLElement* parent = document.NewElement("FirstChild");
    document.InsertFirstChild(parent);
    tinyxml2::XMLElement* sibling = document.NewElement("Sibling");
    parent->InsertFirstChild(sibling);
    tinyxml2::XMLElement* element = createElement(document, "Test", parent);

    Assert::IsTrue(parent->LastChildElement() == element);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestXMLUtils_CreateElement_SetsNameToInputtedName)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createElement(document, "Test");

    Assert::AreEqual("Test", element->Name());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TestXMLUtils_CreateElement_InputtingEmptyName_SetsNameToEmptyString)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = createElement(document, "");

    Assert::AreEqual("", element->Name());
  }

#pragma endregion

  };
}