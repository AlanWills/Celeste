#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "UtilityMacros/Unused.h"

#include "XML/Elements/DataConverterListElement.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Mocks/DataConverters/Objects/MockComponentDataConverter.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste::XML
{
  CELESTE_TEST_CLASS(TestComponentDataConverterListElement)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    ComponentDataConverterRegistry::removeConverter<MockComponentDataConverter>();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    ComponentDataConverterRegistry::removeConverter<MockComponentDataConverter>();
  }

#pragma region IsReference Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_IsReference_ReturnsFalse)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));

    Assert::IsFalse(element->isReference());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));

    Assert::IsFalse(element->convertFromXML(nullptr));
    Assert::IsTrue(element->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_ConvertFromXML_InputtingNonNullElement_ButNoSubElements_ElementNotRequired_DoesNothing_ReturnsTrue)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FirstChildElement("Child"));
    Assert::IsFalse(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_ConvertFromXML_InputtingNonNullElement_ButNoSubElements_ElementRequired_DoesNothing_ReturnsFalse)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FirstChildElement());
    Assert::IsTrue(ele->isRequired());
    Assert::IsFalse(ele->convertFromXML(element));
    Assert::IsTrue(ele->getItems().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_ConvertFromXML_InputtingNonNullElement_WithSubElements_AddsReturnsTrue)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement(MockComponent::type_name());
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement(MockComponent::type_name()));
    Assert::IsFalse(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());
  }

#pragma endregion

#pragma region Foreach Iteration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_ForeachIteration_EmptyList_DoesNothing)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));

    size_t index = 0;
    for (ComponentDataConverter* converter : *ele)
    {
      UNUSED(converter);
      ++index;
    }
    
    Assert::AreEqual(static_cast<size_t>(0), index);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_ForeachIteration_NonEmptyList_IteratesOverCorrectElements)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));
    const_cast<std::vector<ComponentDataConverter*>&>(ele->getItems()).push_back(new MockComponentDataConverter());
    const_cast<std::vector<ComponentDataConverter*>&>(ele->getItems()).push_back(new MockComponentDataConverter());

    size_t index = 0;
    for (ComponentDataConverter* converter : *ele)
    {
      UNUSED(converter);
      ++index;
    }

    Assert::AreEqual(static_cast<size_t>(2), index);
  }

#pragma endregion

#pragma region Clear Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_Clear_ClearsAllElementsFromList)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement(MockComponent::type_name());
    element->InsertFirstChild(subElement);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FirstChildElement(MockComponent::type_name()));
    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());

    ele->clear();

    Assert::IsTrue(ele->getItems().empty());
  }

#pragma endregion

#pragma region Clone Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_Clone_ReturnsNewInstanceOfDataConverterListElement)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsTrue(ele->convertFromXML(element));

    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele2(ele->clone());

    AssertExt::IsNotNull(ele2);
    Assert::IsFalse(ele == ele2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_Clone_SetsInstanceElementNameToSameName)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kNotRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsTrue(ele->convertFromXML(element));

    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele2(ele->clone());

    Assert::AreEqual(ele->getElementName(), ele2->getElementName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_Clone_SetsInstanceDeserializationRequirementToSameRequirement)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement(MockComponent::type_name());
    document.InsertFirstChild(element);
    element->InsertFirstChild(subElement);

    Assert::IsTrue(ele->isRequired());
    Assert::IsTrue(ele->convertFromXML(element));

    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele2(ele->clone());

    Assert::IsTrue(ele2->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterListElement_Clone_DoesNotCloneChildren)
  {
    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele(XMLObjectFactory::create<DataConverterListElement, ComponentDataConverter>(
      "Test", DeserializationRequirement::kRequired));
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* subElement = document.NewElement(MockComponent::type_name());
    document.InsertFirstChild(element);
    element->InsertFirstChild(subElement);

    Assert::IsTrue(ele->convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), ele->getItems().size());

    std::unique_ptr<DataConverterListElement<ComponentDataConverter>> ele2(ele->clone());

    Assert::IsTrue(ele2->getItems().empty());
  }

#pragma endregion

  };
}