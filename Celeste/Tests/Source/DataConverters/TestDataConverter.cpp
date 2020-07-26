#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/MockDataConverter.h"
#include "Mocks/XML/Attributes/MockAttribute.h"
#include "Mocks/XML/Elements/MockElement.h"
#include "TestResources/TestResources.h"
#include "Resources/ResourceManager.h"
#include "TestUtils/Assert/FileAssert.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestDataConverter)

  template <typename T = std::string, DeserializationRequirement required = DeserializationRequirement::kNotRequired>
  class AttributeDataConverter : public MockDataConverter
  {
    public:
      AttributeDataConverter(const std::string& name = "AttributeDataConverter") :
        MockDataConverter(name),
        m_attribute(createValueAttribute<T>("TestAttribute", T(), required))
      {
      }

      const std::string& getAttributeXMLName() const { return m_attribute.getAttributeName(); }
      const XML::ValueAttribute<T>* getAttributePtr() const { return &m_attribute; }

    private:
      XML::ValueAttribute<T>& m_attribute;
  };

  class DuplicateAttributeDataConverter : public MockDataConverter
  {
    public:
      DuplicateAttributeDataConverter(const std::string& name = "DuplicateAttributeDataConverter") :
        MockDataConverter(name),
        m_attribute1(createValueAttribute<std::string>("Test")),
        m_attribute2(createValueAttribute<std::string>("Test"))
      {
      }

      const std::string& getAttributeXMLName() const { return m_attribute1.getAttributeName(); }
      const XML::ValueAttribute<std::string>* getAttribute1Ptr() const { return &m_attribute1; }
      const XML::ValueAttribute<std::string>* getAttribute2Ptr() const { return &m_attribute2; }

    private:
      XML::ValueAttribute<std::string>& m_attribute1;
      XML::ValueAttribute<std::string>& m_attribute2;
  };

  template <typename T = std::string, DeserializationRequirement required = DeserializationRequirement::kNotRequired>
  class ElementDataConverter: public MockDataConverter
  {
    public:
      ElementDataConverter(const std::string& name = "ElementDataConverter") :
        MockDataConverter(name),
        m_element(createValueElement<T>("TestElement", T(), required))
      {
      }

      const std::string& getElementXMLName() const { return m_element.getElementName(); }
      const XML::ValueElement<T>* getElementPtr() const { return &m_element; }

    private:
      XML::ValueElement<T>& m_element;
  };

  class DuplicateElementDataConverter : public MockDataConverter
  {
    public:
      DuplicateElementDataConverter(const std::string& name = "DuplicateElementDataConverter") :
        MockDataConverter(name),
        m_element1(createValueElement<std::string>("Test")),
        m_element2(createValueElement<std::string>("Test"))
      {
      }

      const std::string& getElementXMLName() const { return m_element1.getElementName(); }
      const XML::ValueElement<std::string>* getElement1Ptr() const { return &m_element1; }
      const XML::ValueElement<std::string>* getElement2Ptr() const { return &m_element2; }

    private:
      XML::ValueElement<std::string>& m_element1;
      XML::ValueElement<std::string>& m_element2;
  };

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    getResourceManager().unloadAll<Data>();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    getResourceManager().unloadAll<Data>();
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    MockDataConverter converter("Data");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_Constructor_SetsElementName_ToInput)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual("Data", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_Constructor_ClearsAttributesList)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_Constructor_ClearsElementsList)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());
  }

#pragma endregion

#pragma region Copy Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CopyConstructor_CopiesElementName)
  {
    MockDataConverter converter("Data");
    MockDataConverter converter2(converter);

    Assert::AreEqual(converter.getElementName(), converter2.getElementName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CopyConstructor_CopiesAttributes)
  {
    const MockDataConverter converter("Data");
    auto attribute = const_cast<MockDataConverter&>(converter).createValueAttribute_Public("Test", 5.0f, DeserializationRequirement::kNotRequired);

    const MockDataConverter converter2(converter);

    Assert::AreEqual(converter.getAttributesSize(), converter2.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr") == converter2.getAttribute(0));
    Assert::AreEqual("Test", converter2.getAttribute(0)->getAttributeName().c_str());
    Assert::AreEqual(5.0f, dynamic_cast<const XML::ValueAttribute<float>*>(converter2.getAttribute(0))->getValue());
    Assert::IsFalse(converter2.getAttribute(0)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CopyConstructor_CopiesElements)
  {
    const MockDataConverter converter("Data");
    auto attribute = const_cast<MockDataConverter&>(converter).createValueElement_Public("Test", 5.0f, DeserializationRequirement::kNotRequired);

    const MockDataConverter converter2(converter);

    Assert::AreEqual(converter.getElementsSize(), converter2.getElementsSize());
    Assert::IsFalse(converter.getElement(0) == converter2.getElement(0));
    Assert::AreEqual("Test", converter2.getElement(0)->getElementName().c_str());
    Assert::AreEqual(5.0f, dynamic_cast<const XML::ValueElement<float>*>(converter2.getElement(0))->getValue());
    Assert::IsFalse(converter2.getElement(0)->isRequired());
  }

#pragma endregion

#pragma region Move Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_MoveConstructor_MovesElementName)
  {
    MockDataConverter converter("Test");
    MockDataConverter converter2(std::move(converter));

    Assert::AreEqual("Test", converter2.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_MoveConstructor_MovesAttributes)
  {
    MockDataConverter converter("Data");
    auto attribute = converter.createValueAttribute_Public("Test", 5.0f, DeserializationRequirement::kNotRequired);

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());

    const MockDataConverter converter2(std::move(converter));

    Assert::AreEqual(static_cast<size_t>(1), converter2.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_MoveConstructor_MovesElements)
  {
    MockDataConverter converter("Data");
    auto element = converter.createValueElement_Public("Test", 5.0f, DeserializationRequirement::kNotRequired);

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());

    const MockDataConverter converter2(std::move(converter));

    Assert::AreEqual(static_cast<size_t>(1), converter2.getElementsSize());
  }

#pragma endregion

#pragma region Assignment Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_AssignmentOperator_CopiesName)
  {
    MockDataConverter converter("Test");
    MockDataConverter converter2("Another");

    Assert::AreEqual("Another", converter2.getElementName().c_str());

    converter2 = converter;

    Assert::AreEqual("Test", converter2.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_AssignmentOperator_ClearsAndCopiesAttributes)
  {
    MockDataConverter converter("Test");
    converter.createValueAttribute_Public("Attr", 5.0f);

    MockDataConverter converter2("Another");
    converter2.createValueAttribute_Public("Attr1", 0.0f);
    converter2.createValueAttribute_Public("Attr2", 1.0f);

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
    Assert::AreEqual(static_cast<size_t>(2), converter2.getAttributesSize());

    converter2 = converter;

    Assert::AreEqual(static_cast<size_t>(1), converter2.getAttributesSize());
    Assert::IsNotNull(static_cast<const MockDataConverter&>(converter2).findAttribute("Attr"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_AssignmentOperator_ClearsAndCopiesElements)
  {
    MockDataConverter converter("Test");
    converter.createValueElement_Public("Ele", 5.0f);

    MockDataConverter converter2("Another");
    converter2.createValueElement_Public("Ele1", 0.0f);
    converter2.createValueElement_Public("Ele2", 1.0f);

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
    Assert::AreEqual(static_cast<size_t>(2), converter2.getElementsSize());

    converter2 = converter;

    Assert::AreEqual(static_cast<size_t>(1), converter2.getElementsSize());
    Assert::IsNotNull(static_cast<const MockDataConverter&>(converter2).findElement("Ele"));
  }

#pragma endregion

#pragma region Add Data Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_AddData_InputtingAttribute_AddsToAttributesList)
  {
    MockDataConverter converter("Data");
    MockAttribute* attr = new MockAttribute("Test");

    Assert::AreEqual(static_cast<size_t>(0), converter.getAttributesSize());

    converter.addData_Public(attr);

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_AddData_InputtingElement_AddsToElementsList)
  {
    MockDataConverter converter("Data");
    MockElement* ele = new MockElement("Test");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());

    converter.addData_Public(ele);

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
  }

#pragma endregion

#pragma region Get Const Attribute Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_GetConstAttribute_InputtingInvalidIndex_ReturnsNullptr)
  {
    const MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getAttributesSize());
    Assert::IsNull(converter.getElement(0));
    Assert::IsNull(converter.getAttribute(1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_GetConstAttribute_InputtingValidIndex_ReturnsCorrectAttribute)
  {
    const AttributeDataConverter<std::string> converter("Data");

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
    Assert::IsTrue(converter.getAttributePtr() == converter.getAttribute(0));
  }

#pragma endregion

#pragma region Get Const Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_GetConstElement_InputtingInvalidIndex_ReturnsNullptr)
  {
    const MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());
    Assert::IsNull(converter.getElement(0));
    Assert::IsNull(converter.getElement(1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_GetConstElement_InputtingValidIndex_ReturnsCorrectElement)
  {
    const ElementDataConverter<std::string> converter("Data");

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
    Assert::IsTrue(converter.getElementPtr() == converter.getElement(0));
  }

#pragma endregion

#pragma region Find Const Attribute Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_FindConstAttribute_InputtingNonExistentName_ReturnsNullptr)
  {
    const MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getAttributesSize());
    Assert::IsNull(converter.findAttribute("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_FindConstAttribute_InputtingExistentName_ReturnsCorrectAttribute)
  {
    const AttributeDataConverter<std::string> converter("Data");

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
    Assert::IsTrue(converter.getAttributePtr() == converter.findAttribute(converter.getAttributeXMLName()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_FindConstAttribute_InputtingExistentName_ReturnsFirstAttributeWithMatchingName)
  {
    const DuplicateAttributeDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsTrue(converter.getAttribute1Ptr() == converter.findAttribute(converter.getAttributeXMLName()));
  }

#pragma endregion
  
#pragma region Find Const Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_FindConstElement_InputtingNonExistentName_ReturnsNullptr)
  {
    const MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());
    Assert::IsNull(converter.findElement("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_FindConstElement_InputtingExistentName_ReturnsCorrectElement)
  {
    const ElementDataConverter<std::string> converter("Data");

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
    Assert::IsTrue(converter.getElementPtr() == converter.findElement(converter.getElementXMLName()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_FindConstElement_InputtingExistentName_ReturnsFirstElementWithMatchingName)
  {
    const DuplicateElementDataConverter converter("Data");
    
    Assert::AreEqual(static_cast<size_t>(2), converter.getElementsSize());
    Assert::IsTrue(converter.getElement1Ptr() == converter.findElement(converter.getElementXMLName()));
  }

#pragma endregion

#pragma region Cleanup Data Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CleanupData_ClearsAttributeList)
  {
    AttributeDataConverter<std::string> converter("Data");

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
    
    converter.cleanupData();

    Assert::AreEqual(static_cast<size_t>(0), converter.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CleanupData_ClearsElementList)
  {
    ElementDataConverter<std::string> converter("Data");

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());

    converter.cleanupData();

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());
  }

#pragma endregion

#pragma region Convert From XML Tests

#pragma region XMLElement Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    MockDataConverter converter("Data");

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingNullptr_SetsDataLoadedCorrectlyToFalse)
  {
    MockDataConverter converter("Data");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_ConvertsAttributes)
  {
    AttributeDataConverter<std::string> converter("Data");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    element->SetAttribute(converter.getAttributeXMLName().c_str(), "Test Value");

    Assert::AreEqual("", converter.getAttributePtr()->getValue().c_str());

    converter.convertFromXML(element);

    Assert::AreEqual("Test Value", converter.getAttributePtr()->getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_RequiredAttributeThatDoesntExist_ReturnsFalse)
  {
    AttributeDataConverter<std::string, DeserializationRequirement::kRequired> converter("Data");
    XMLDocument document;
    const XMLElement* element = document.NewElement("Element");

    Assert::IsNull(element->FindAttribute(converter.getAttributeXMLName().c_str()));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_ConvertsElements)
  {
    ElementDataConverter<std::string> converter("Element");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    XMLElement* child = document.NewElement(converter.getElementXMLName().c_str());
    element->InsertFirstChild(child);
    child->SetText("Test Value");

    Assert::AreEqual("", converter.getElementPtr()->getValue().c_str());

    converter.convertFromXML(element);

    Assert::AreEqual("Test Value", converter.getElementPtr()->getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_RequiredElementThatDoesntExist_ReturnsFalse)
  {
    ElementDataConverter<std::string, DeserializationRequirement::kRequired> converter("Data");
    XMLDocument document;
    const XMLElement* element = document.NewElement("Element");

    Assert::IsNull(element->FirstChildElement(converter.getElementXMLName().c_str()));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_CallsDoConvertFromXML)
  {
    MockDataConverter converter("Data");
    XMLDocument document;
    XMLElement* element = document.NewElement("Element");

    Assert::IsFalse(converter.isDoConvertFromXMLCalled());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDoConvertFromXMLCalled());
  }

#pragma endregion

#pragma region Path Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingNonExistentPath_ReturnsFalse)
  {
    MockDataConverter converter("Data");
    Path filePath("WubbaLubbaDubDub");

    FileAssert::FileDoesNotExist(filePath.as_string());
    Assert::IsFalse(converter.convertFromXML(filePath));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingNonExistentPath_SetsDataLoadedCorrectlyToFalse)
  {
    MockDataConverter converter("Data");
    Path filePath("WubbaLubbaDubDub");
    converter.convertFromXML(filePath);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPath_ConvertsAttributes)
  {
    AttributeDataConverter<std::string> converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Data");
    element->SetAttribute(converter.getAttributeXMLName().c_str(), "Test Value");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::AreEqual("", converter.getAttributePtr()->getValue().c_str());

    converter.convertFromXML(filePath);

    Assert::AreEqual("Test Value", converter.getAttributePtr()->getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPath_RequiredAttributeThatDoesntExist_ReturnsFalse)
  {
    AttributeDataConverter<std::string, DeserializationRequirement::kRequired> converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::IsNull(element->FindAttribute(converter.getAttributeXMLName().c_str()));
    Assert::IsFalse(converter.convertFromXML(filePath));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPath_ConvertsElements)
  {
    ElementDataConverter<std::string> converter("Element");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    XMLElement* child = document.NewElement(converter.getElementXMLName().c_str());
    element->InsertFirstChild(child);
    child->SetText("Test Value");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::AreEqual("", converter.getElementPtr()->getValue().c_str());

    converter.convertFromXML(filePath);

    Assert::AreEqual("Test Value", converter.getElementPtr()->getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPath_RequiredElementThatDoesntExist_ReturnsFalse)
  {
    ElementDataConverter<std::string, DeserializationRequirement::kRequired> converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::IsNull(element->FirstChildElement(converter.getElementXMLName().c_str()));
    Assert::IsFalse(converter.convertFromXML(filePath));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPath_CallsDoConvertFromXML)
  {
    MockDataConverter converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::IsFalse(converter.isDoConvertFromXMLCalled());

    converter.convertFromXML(filePath);

    Assert::IsTrue(converter.isDoConvertFromXMLCalled());
  }

#pragma endregion

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingNonExistentPathString_ReturnsFalse)
  {
    MockDataConverter converter("Data");
    Path filePath("WubbaLubbaDubDub");

    FileAssert::FileDoesNotExist(filePath.as_string());
    Assert::IsFalse(converter.convertFromXML(filePath.as_string()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingNonExistentPathString_SetsDataLoadedCorrectlyToFalse)
  {
    MockDataConverter converter("Data");
    Path filePath("WubbaLubbaDubDub");
    converter.convertFromXML(filePath.as_string());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPathString_ConvertsAttributes)
  {
    AttributeDataConverter<std::string> converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Data");
    element->SetAttribute(converter.getAttributeXMLName().c_str(), "Test Value");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::AreEqual("", converter.getAttributePtr()->getValue().c_str());

    converter.convertFromXML(filePath.as_string());

    Assert::AreEqual("Test Value", converter.getAttributePtr()->getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPathString_RequiredAttributeThatDoesntExist_ReturnsFalse)
  {
    AttributeDataConverter<std::string, DeserializationRequirement::kRequired> converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Data");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::IsNull(element->FindAttribute(converter.getAttributeXMLName().c_str()));
    Assert::IsFalse(converter.convertFromXML(filePath.as_string()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPathString_ConvertsElements)
  {
    ElementDataConverter<std::string> converter("Element");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    XMLElement* child = document.NewElement(converter.getElementXMLName().c_str());
    element->InsertFirstChild(child);
    child->SetText("Test Value");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::AreEqual("", converter.getElementPtr()->getValue().c_str());

    converter.convertFromXML(filePath.as_string());

    Assert::AreEqual("Test Value", converter.getElementPtr()->getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPathString_RequiredElementThatDoesntExist_ReturnsFalse)
  {
    ElementDataConverter<std::string, DeserializationRequirement::kRequired> converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::IsNull(element->FirstChildElement(converter.getElementXMLName().c_str()));
    Assert::IsFalse(converter.convertFromXML(filePath.as_string()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_ConvertFromXML_InputtingExistentPathString_CallsDoConvertFromXML)
  {
    MockDataConverter converter("Data");
    Path filePath(TempDirectory::getFullPath(), "Test.xml");

    XMLDocument document;
    XMLElement* element = document.NewElement("Element");
    document.InsertFirstChild(element);
    document.SaveFile(filePath.c_str());

    FileAssert::FileExists(filePath.as_string());
    Assert::IsFalse(converter.isDoConvertFromXMLCalled());

    converter.convertFromXML(filePath.as_string());

    Assert::IsTrue(converter.isDoConvertFromXMLCalled());
  }

#pragma endregion

#pragma endregion

#pragma region Create Value Attribute Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueAttribute_ReturnsNewlyCreatedInstance)
  {
    MockDataConverter converter("Data");

    Assert::IsNotNull(&converter.createValueAttribute_Public<float>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueAttribute_AddsToDataConverter)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getAttributesSize());
    
    converter.createValueAttribute_Public<float>("Test");

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueAttribute_SetsAttributeNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto attribute = converter.createValueAttribute_Public<float>("Test");

    Assert::AreEqual("Test", attribute.getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueAttribute_SetsValueToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto attribute = converter.createValueAttribute_Public<float>("Test", 5.0f);

    Assert::AreEqual(5.0f, attribute.getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueAttribute_SetsDeserializationRequirementToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto attribute = converter.createValueAttribute_Public<float>("Test", 5.0f, DeserializationRequirement::kRequired);

    Assert::IsTrue(attribute.isRequired());
  }

#pragma endregion

#pragma region Create Reference Attribute Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceAttribute_ReturnsNewlyCreatedInstance)
  {
    MockDataConverter converter("Data");

    Assert::IsNotNull(&converter.createReferenceAttribute_Public<float>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceAttribute_AddsToDataConverter)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getAttributesSize());

    converter.createReferenceAttribute_Public<float>("Test");

    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceAttribute_SetsAttributeNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto attribute = converter.createReferenceAttribute_Public<float>("Test");

    Assert::AreEqual("Test", attribute.getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceAttribute_SetsValueToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto attribute = converter.createReferenceAttribute_Public<float>("Test", 5.0f);

    Assert::AreEqual(5.0f, attribute.getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceAttribute_SetsDeserializationRequirementToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto attribute = converter.createReferenceAttribute_Public<float>("Test", 5.0f, DeserializationRequirement::kRequired);

    Assert::IsTrue(attribute.isRequired());
  }

#pragma endregion

#pragma region Create Value Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueElement_ReturnsNewlyCreatedInstance)
  {
    MockDataConverter converter("Data");

    Assert::IsNotNull(&converter.createValueElement_Public<float>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueElement_AddsToDataConverter)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());

    converter.createValueElement_Public<float>("Test");

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueElement_SetsElementNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createValueElement_Public<float>("Test");

    Assert::AreEqual("Test", element.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueElement_SetsValueToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createValueElement_Public<float>("Test", 5.0f);

    Assert::AreEqual(5.0f, element.getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateValueElement_SetsDeserializationRequirementToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createValueElement_Public<float>("Test", 5.0f, DeserializationRequirement::kRequired);

    Assert::IsTrue(element.isRequired());
  }

#pragma endregion

#pragma region Create Reference Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceElement_ReturnsNewlyCreatedInstance)
  {
    MockDataConverter converter("Data");

    Assert::IsNotNull(&converter.createReferenceElement_Public<float>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceElement_AddsToDataConverter)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());

    converter.createReferenceElement_Public<float>("Test");

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceElement_SetsElementNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createReferenceElement_Public<float>("Test");

    Assert::AreEqual("Test", element.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceElement_SetsValueToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createReferenceElement_Public<float>("Test", 5.0f);

    Assert::AreEqual(5.0f, element.getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateReferenceElement_SetsDeserializationRequirementToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createReferenceElement_Public<float>("Test", 5.0f, DeserializationRequirement::kRequired);

    Assert::IsTrue(element.isRequired());
  }

#pragma endregion

#pragma region Create List Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateListElement_ReturnsNewlyCreatedInstance)
  {
    MockDataConverter converter("Data");

    Assert::IsNotNull(&converter.createListElement_Public<float>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateListElement_AddsToDataConverter)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());

    converter.createListElement_Public<float>("Test");

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateListElement_SetsElementNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createListElement_Public<float>("Test");

    Assert::AreEqual("Test", element.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateListElement_NotInputtingChildElementName_SetsChildElementNameToEmptyString)
  {
    MockDataConverter converter("Data");

    auto element = converter.createListElement_Public<float>("Test");

    Assert::AreEqual("", element.getChildElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateListElement_InputtingChildElementName_SetsChildElementNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createListElement_Public<float>("Test", "Child");

    Assert::AreEqual("Child", element.getChildElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateListElement_SetsDeserializationRequirementToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto element = converter.createListElement_Public<float>("Test", "Child", DeserializationRequirement::kRequired);

    Assert::IsTrue(element.isRequired());
  }

#pragma endregion

#pragma region Create Data Converter List Element Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateDataConverterListElement_ReturnsNewlyCreatedInstance)
  {
    MockDataConverter converter("Data");

    Assert::IsNotNull(&converter.createDataConverterListElement_Public<MockDataConverter>("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateDataConverterListElement_AddsToDataConverter)
  {
    MockDataConverter converter("Data");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());

    converter.createDataConverterListElement_Public<MockDataConverter>("Test");

    Assert::AreEqual(static_cast<size_t>(1), converter.getElementsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateDataConverterListElement_SetsElementNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto& element = converter.createDataConverterListElement_Public<MockDataConverter>("Test");

    Assert::AreEqual("Test", element.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateDataConverterListElement_NotInputtingItemElementName_SetsItemElementNameToEmptyString)
  {
    MockDataConverter converter("Data");

    auto& element = converter.createDataConverterListElement_Public<MockDataConverter>("Test");

    Assert::AreEqual("", element.getItemElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateDataConverterListElement_InputtingItemElementName_SetsItemElementNameToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto& element = converter.createDataConverterListElement_Public<MockDataConverter>("Test", "Child");

    Assert::AreEqual("Child", element.getItemElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverter_CreateDataConverterListElement_SetsDeserializationRequirementToInputtedValue)
  {
    MockDataConverter converter("Data");

    auto& element = converter.createDataConverterListElement_Public<MockDataConverter>("Test", "Child", DeserializationRequirement::kRequired);

    Assert::IsTrue(element.isRequired());
  }

#pragma endregion

  };
}