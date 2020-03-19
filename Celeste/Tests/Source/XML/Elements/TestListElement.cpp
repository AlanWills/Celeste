 #include "UtilityHeaders/UnitTestHeaders.h"
#include "UtilityMacros/Unused.h"

#include "XML/Elements/ListElement.h"
#include "Mocks/DataConverters/MockDataConverter.h"
#include "AssertExt.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste::XML
{
  CELESTE_TEST_CLASS(TestListElement)

#pragma region IsReference Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_IsReference_ReturnsFalse)
  {
    std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
      "Test", DeserializationRequirement::kNotRequired));

    Assert::IsFalse(element->isReference());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
      "Test", DeserializationRequirement::kNotRequired));

    Assert::IsFalse(element->convertFromXML(nullptr));
    Assert::IsTrue(element->getChildren().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ConvertFromXML_InputtingNonNullElement_ButNoSubElements_ElementNotRequired_DoesNothing_ReturnsTrue)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsFalse(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::IsTrue(ele->getChildren().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ConvertFromXML_InputtingNonNullElement_ButNoSubElements_ElementRequired_DoesNothing_ReturnsFalse)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsTrue(ele->isRequired());
    Assert::IsFalse(ele->convertFromXML(element));
    Assert::IsTrue(ele->getChildren().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ConvertFromXML_InputtingNonNullElement_AndCorrectSubElements_ElementNotRequired_AddsReturnsTrue)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child");
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsFalse(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getChildren().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ConvertFromXML_InputtingNonNullElement_AndSubElements_OnlyConvertFromXMLsCorrectSubElements)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child_");
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child_"));
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::IsTrue(ele->getChildren().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ConvertFromXML_InputtingNonNullElement_AndSubElements_ChildElementNameIsEmpty_ConvertsAllSubElements)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child_");
    element->InsertFirstChild(subElement);
    XMLElement* subElement2 = document.NewElement("Child");
    element->InsertFirstChild(subElement2);

    Assert::AreEqual("", ele->getChildElementName().c_str());
    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child_"));
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(2), ele->getChildren().size());
  }

#pragma endregion

#pragma region Foreach Iteration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ForeachIteration_EmptyList_DoesNothing)
  {
    std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));

    size_t count = 0;
    for (const std::string& converter : *element)
    {
      UNUSED(converter);
      ++count;
    }

    Assert::AreEqual(static_cast<size_t>(0), count);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_ForeachIteration_NonEmptyList_IteratesOverCorrectElements)
  {
    std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    const_cast<std::vector<std::string>&>(element->getChildren()).push_back("Child1");
    const_cast<std::vector<std::string>&>(element->getChildren()).push_back("Child2");

    size_t index = 0;
    for (const std::string& converter : *element)
    {
      UNUSED(converter);
      ++index;
    }

    Assert::AreEqual(static_cast<size_t>(2), index);
  }

#pragma endregion

#pragma region Clear Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_Clear_ClearsAllElementsFromList)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child");
    subElement->SetText("Test");
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getChildren().size());

    ele->clear();

    Assert::IsTrue(ele->getChildren().empty());
  }

#pragma endregion

#pragma region Clone Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_Clone_ReturnsNewInstanceOfListElement)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));

    std::unique_ptr<ListElement<std::string>> ele2(ele->clone());

    AssertExt::IsNotNull(ele2);
    Assert::IsFalse(ele == ele2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_Clone_SetsInstanceElementNameToSameName)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));

    std::unique_ptr<ListElement<std::string>> ele2(ele->clone());

    Assert::AreEqual(ele->getElementName(), ele2->getElementName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_Clone_SetsInstanceChildElementNameToSameChildElementName)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));

    std::unique_ptr<ListElement<std::string>> ele2(ele->clone());

    Assert::AreEqual(ele->getChildElementName(), ele2->getChildElementName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ListElement_Clone_SetsInstanceDeserializationRequirementToSameRequirement)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kRequired));

    std::unique_ptr<ListElement<std::string>> ele2(ele->clone());

    Assert::IsTrue(ele->isRequired());
    Assert::IsTrue(ele2->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_Clone_ClonesChildren)
  {
    std::unique_ptr<ListElement<std::string>> ele(XMLObjectFactory::create<ListElement, std::string>(
      "Test", ChildElementName(""), DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child");
    document.InsertFirstChild(element);
    element->InsertFirstChild(subElement);
    subElement->SetText("T");

    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getChildren().size());

    std::unique_ptr<ListElement<std::string>> ele2(ele->clone());

    Assert::AreEqual(static_cast<size_t>(1), ele2->getChildren().size());
    Assert::AreEqual(ele->getChildren()[0], ele2->getChildren()[0]);
  }

#pragma endregion

  };
}