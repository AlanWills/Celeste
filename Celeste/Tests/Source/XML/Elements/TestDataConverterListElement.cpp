#include "UtilityHeaders/UnitTestHeaders.h"

#include "XML/Elements/DataConverterListElement.h"
#include "Mocks/DataConverters/MockDataConverter.h"
#include "AssertExt.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste::XML
{
  CELESTE_TEST_CLASS(TestDataConverterListElement)

#pragma region IsReference Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_IsReference_ReturnsFalse)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));

    Assert::IsFalse(element->isReference());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));

    Assert::IsFalse(element->convertFromXML(nullptr));
    Assert::IsTrue(element->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ConvertFromXML_InputtingNonNullElement_ButNoSubElements_ElementNotRequired_DoesNothing_ReturnsTrue)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsFalse(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ConvertFromXML_InputtingNonNullElement_ButNoSubElements_ElementRequired_DoesNothing_ReturnsFalse)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsTrue(ele->isRequired());
    Assert::IsFalse(ele->convertFromXML(element));
    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ConvertFromXML_InputtingNonNullElement_AndCorrectSubElements_ElementNotRequired_AddsReturnsTrue)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child");
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsFalse(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ConvertFromXML_InputtingNonNullElement_AndSubElements_OnlyConvertFromXMLsCorrectSubElements)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child_");
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child_"));
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ConvertFromXML_InputtingNonNullElement_AndSubElements_ChildElementNameIsEmpty_ConvertsAllSubElements)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child_");
    element->InsertFirstChild(subElement);
    XMLElement* subElement2 = document.NewElement("Child");
    element->InsertFirstChild(subElement2);

    Assert::AreEqual("", ele->getItemElementName().c_str());
    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child_"));
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(2), ele->getItems().size());
  }

#pragma endregion

#pragma region Foreach Iteration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ForeachIteration_EmptyList_DoesNothing)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));

    for (MockDataConverter* converter : *ele)
    {
      Assert::Fail();
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_ForeachIteration_NonEmptyList_IteratesOverCorrectElements)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    const_cast<std::vector<MockDataConverter*>&>(ele->getItems()).push_back(new MockDataConverter());
    const_cast<std::vector<MockDataConverter*>&>(ele->getItems()).push_back(new MockDataConverter());

    size_t index = 0;
    for (MockDataConverter* converter : *ele)
    {
      ++index;
    }

    Assert::AreEqual(static_cast<size_t>(2), index);
  }

#pragma endregion

#pragma region Clear Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_Clear_ClearsAllElementsFromList)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child");
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());

    ele->clear();

    Assert::IsTrue(ele->getItems().empty());
  }

#pragma endregion

#pragma region Clone Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_Clone_ReturnsNewInstanceOfDataConverterListElement)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsTrue(ele->convertFromXML(element));

    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele2(ele->clone());

    AssertExt::IsNotNull(ele2);
    Assert::IsFalse(ele == ele2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_Clone_SetsInstanceElementNameToSameName)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsTrue(ele->convertFromXML(element));

    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele2(ele->clone());

    Assert::AreEqual(ele->getElementName(), ele2->getElementName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_Clone_SetsInstanceChildElementNameToSameChildElementName)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsTrue(ele->convertFromXML(element));

    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele2(ele->clone());

    Assert::AreEqual(ele->getItemElementName(), ele2->getItemElementName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_Clone_SetsInstanceDeserializationRequirementToSameRequirement)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child");
    document.InsertFirstChild(element);
    element->InsertFirstChild(subElement);

    Assert::IsTrue(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));

    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele2(ele->clone());

    Assert::IsTrue(ele2->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterListElement_Clone_DoesNotCloneChildren)
  {
    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
      "Test", ChildElementName(""), DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement("Child");
    document.InsertFirstChild(element);
    element->InsertFirstChild(subElement);

    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());

    std::unique_ptr<DataConverterListElement<MockDataConverter>> ele2(ele->clone());

    Assert::IsTrue(ele2->getItems().empty());
  }

#pragma endregion

  };
}