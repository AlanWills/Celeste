#include "UtilityHeaders/UnitTestHeaders.h"

#include "XML/XMLObjectFactory.h"
#include "XML/Attributes/DataAttribute.h"
#include "XML/Elements/DataElement.h"
#include "XML/Elements/ListElement.h"
#include "XML/Elements/DataConverterListElement.h"
#include "Mocks/DataConverters/MockDataConverter.h"
#include "AssertExt.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  namespace XML
  {
    CELESTE_TEST_CLASS(TestXMLObjectFactory)

#pragma region Create Value Attribute Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueAttribute_ReturnsInstanceOfNewValueAttribute)
    {
      std::unique_ptr<ValueAttribute<float>> attribute(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      AssertExt::IsNotNull(attribute);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueAttribute_SetsNewAttributeNameToInput)
    {
      std::unique_ptr<ValueAttribute<float>> attribute(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Test", attribute->getAttributeName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueAttribute_SetsNewAttributeValueToInput)
    {
      std::unique_ptr<ValueAttribute<float>> attribute(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 5.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual(5.0f, attribute->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueAttribute_SetsNewAttributeDeserializationRequirementToInput)
    {
      std::unique_ptr<ValueAttribute<float>> attribute(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kRequired));

      Assert::IsTrue(attribute->isRequired());
    }

#pragma endregion

#pragma region Create Reference Attribute Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceAttribute_ReturnsInstanceOfNewReferenceAttribute)
    {
      std::unique_ptr<ReferenceAttribute<float>> attribute(XMLObjectFactory::create<ReferenceAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      AssertExt::IsNotNull(attribute);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceAttribute_SetsNewAttributeNameToInput)
    {
      std::unique_ptr<ReferenceAttribute<float>> attribute(XMLObjectFactory::create<ReferenceAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Test", attribute->getAttributeName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceAttribute_SetsNewAttributeValueToInput)
    {
      std::unique_ptr<ReferenceAttribute<float>> attribute(XMLObjectFactory::create<ReferenceAttribute, float>(
        "Test", 5.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual(5.0f, attribute->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceAttribute_SetsNewAttributeDeserializationRequirementToInput)
    {
      std::unique_ptr<ReferenceAttribute<float>> attribute(XMLObjectFactory::create<ReferenceAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kRequired));

      Assert::IsTrue(attribute->isRequired());
    }

#pragma endregion

#pragma region Create Value Element Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueElement_ReturnsInstanceOfNewValueElement)
    {
      std::unique_ptr<ValueElement<float>> element(XMLObjectFactory::create<ValueElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      AssertExt::IsNotNull(element);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueElement_SetsNewElementNameToInput)
    {
      std::unique_ptr<ValueElement<float>> element(XMLObjectFactory::create<ValueElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Test", element->getElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueElement_SetsNewElementValueToInput)
    {
      std::unique_ptr<ValueElement<float>> element(XMLObjectFactory::create<ValueElement, float>(
        "Test", 5.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual(5.0f, element->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateValueElement_SetsNewElementDeserializationRequirementToInput)
    {
      std::unique_ptr<ValueElement<float>> element(XMLObjectFactory::create<ValueElement, float>(
        "Test", 0.0f, DeserializationRequirement::kRequired));

      Assert::IsTrue(element->isRequired());
    }

#pragma endregion

#pragma region Create Reference Element Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceElement_ReturnsInstanceOfNewReferenceElement)
    {
      std::unique_ptr<ReferenceElement<float>> element(XMLObjectFactory::create<ReferenceElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      AssertExt::IsNotNull(element);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceElement_SetsNewElementNameToInput)
    {
      std::unique_ptr<ReferenceElement<float>> element(XMLObjectFactory::create<ReferenceElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Test", element->getElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceElement_SetsNewElementValueToInput)
    {
      std::unique_ptr<ReferenceElement<float>> element(XMLObjectFactory::create<ReferenceElement, float>(
        "Test", 5.0f, DeserializationRequirement::kNotRequired));

      Assert::AreEqual(5.0f, element->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateReferenceElement_SetsNewElementDeserializationRequirementToInput)
    {
      std::unique_ptr<ReferenceElement<float>> element(XMLObjectFactory::create<ReferenceElement, float>(
        "Test", 0.0f, DeserializationRequirement::kRequired));

      Assert::IsTrue(element->isRequired());
    }

#pragma endregion

#pragma region Create List Element Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateListElement_ReturnsInstanceOfNewListElement)
    {
      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      AssertExt::IsNotNull(element);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateListElement_SetsNewElementNameToInput)
    {
      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Test", element->getElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateListElement_NotInputtingChildElementName_SetsNewElementChildElementNameToEmptyString)
    {
      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::AreEqual("", element->getChildElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateListElement_InputtingChildElementName_SetsNewElementChildElementNameToInput)
    {
      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Child", element->getChildElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateListElement_SetsNewElementDeserializationRequirementToInput)
    {
      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kRequired));

      Assert::IsTrue(element->isRequired());
    }

#pragma endregion

#pragma region Create Data Converter List Element Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateDataConverterListElement_ReturnsInstanceOfNewListElement)
    {
      std::unique_ptr<DataConverterListElement<MockDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
        "Test", DeserializationRequirement::kNotRequired));

      AssertExt::IsNotNull(element);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateDataConverterListElement_SetsNewElementNameToInput)
    {
      std::unique_ptr<DataConverterListElement<MockDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Test", element->getElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateDataConverterListElement_NotInputtingChildElementName_SetsNewElementChildElementNameToEmptyString)
    {
      std::unique_ptr<DataConverterListElement<MockDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::AreEqual("", element->getItemElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateDataConverterListElement_InputtingChildElementName_SetsNewElementChildElementNameToInput)
    {
      std::unique_ptr<DataConverterListElement<MockDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
        "Test", ChildElementName("Child"), DeserializationRequirement::kNotRequired));

      Assert::AreEqual("Child", element->getItemElementName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLObjectFactory_CreateDataConverterListElement_SetsNewElementDeserializationRequirementToInput)
    {
      std::unique_ptr<DataConverterListElement<MockDataConverter>> element(XMLObjectFactory::create<DataConverterListElement, MockDataConverter>(
        "Test", DeserializationRequirement::kRequired));

      Assert::IsTrue(element->isRequired());
    }

#pragma endregion

    };
  }
}