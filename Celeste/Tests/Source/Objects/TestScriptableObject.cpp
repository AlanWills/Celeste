#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockScriptableObject.h"
#include "Mocks/Objects/FailDeserializationScriptableObject.h"
#include "Mocks/Fields/FailDeserializationField.h"
#include "Registries/ScriptableObjectRegistry.h"
#include "TestResources/TestResources.h"
#include "TestUtils/Assert/AssertCel.h"
#include "TestUtils/Assert/FileAssert.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste::Resources;


namespace TestCeleste::Objects
{
  CELESTE_TEST_CLASS(TestScriptableObject)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    getResourceManager().unloadAll<Data>();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    getResourceManager().unloadAll<Data>();

    ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();
    ScriptableObjectRegistry::removeScriptableObject<FailDeserializationScriptableObject>();
    ScriptableObjectRegistry::removeScriptableObject<FieldFailDeserializationScriptableObject>();
    ScriptableObjectRegistry::removeScriptableObject<FieldsPassDeserializationScriptableObject>();
    ScriptableObjectRegistry::removeScriptableObject<SingleChildScriptableObject>();
    ScriptableObjectRegistry::removeScriptableObject<ChildScriptableObjectPassesDeserializationScriptableObject>();
    ScriptableObjectRegistry::removeScriptableObject<ChildScriptableObjectFailDeserializationScriptableObject>();
  }

  //------------------------------------------------------------------------------------------------
  class FieldFailDeserializationScriptableObject : public MockScriptableObject
  {
  public:
    FieldFailDeserializationScriptableObject() :
      m_field(createField<FailDeserializationField>("FailField"))
    {
    }

    static std::string type_name() { return "FieldFailDeserializationScriptableObject"; }

  private:
    FailDeserializationField& m_field;
  };

  //------------------------------------------------------------------------------------------------
  class FieldsPassDeserializationScriptableObject : public MockScriptableObject
  {
  public:
    FieldsPassDeserializationScriptableObject() :
      m_intField(createValueField<int>("IntField", 0)),
      m_stringField(createReferenceField<std::string>("StringField", ""))
    {
    }

    static std::string type_name() { return "FieldsPassDeserializationScriptableObject"; }

    int getIntField() const { return m_intField.getValue(); }
    void setIntField(int value) { return m_intField.setValue(value); }

    const std::string& getStringField() const { return m_stringField.getValue(); }
    void setStringField(const std::string& value) { return m_stringField.setValue(value); }

  private:
    ValueField<int>& m_intField;
    ReferenceField<std::string>& m_stringField;
  };

  //------------------------------------------------------------------------------------------------
  class SingleChildScriptableObject : public MockScriptableObject
  {
  public:
    SingleChildScriptableObject() :
      m_child(createScriptableObject<MockScriptableObject>("Child"))
    {
    }

    static std::string type_name() { return "SingleChildScriptableObject"; }

    const MockScriptableObject& getChild() const { return m_child; }

  private:
    MockScriptableObject& m_child;
  };

  //------------------------------------------------------------------------------------------------
  class ChildScriptableObjectFailDeserializationScriptableObject : public MockScriptableObject
  {
  public:
    ChildScriptableObjectFailDeserializationScriptableObject() :
      m_child(createScriptableObject<FailDeserializationScriptableObject>("FailChild"))
    {
    }

    static std::string type_name() { return "ChildScriptableObjectFailDeserializationScriptableObject"; }

    const FailDeserializationScriptableObject& getChild() const { return m_child; }

  private:
    FailDeserializationScriptableObject& m_child;
  };

  //------------------------------------------------------------------------------------------------
  class ChildScriptableObjectPassesDeserializationScriptableObject : public MockScriptableObject
  {
  public:
    ChildScriptableObjectPassesDeserializationScriptableObject() :
      m_child(createScriptableObject<FieldsPassDeserializationScriptableObject>("SuccessChild"))
    {
    }

    static std::string type_name() { return "ChildScriptableObjectPassesDeserializationScriptableObject"; }

    FieldsPassDeserializationScriptableObject& getChild() const { return m_child; }

  private:
    FieldsPassDeserializationScriptableObject& m_child;
  };

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Constructor_SetsGuidToNewGuid)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");

    Assert::IsFalse(scriptableObject->getGuid().str().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Constructor_SetsFieldsVectorToEmptyVector)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");

    Assert::AreEqual(static_cast<size_t>(0), scriptableObject->getFieldsSize_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Constructor_SetsScriptableObjectsVectorToEmptyVector)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");

    Assert::AreEqual(static_cast<size_t>(0), scriptableObject->getScriptableObjectsSize_Public());
  }

#pragma endregion

#pragma region Create Tests

#pragma region Template Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Create_ReturnsInstanceOfInputtedType)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject(ScriptableObject::create<MockScriptableObject>(""));

    Assert::IsNotNull(scriptableObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Create_SetsNameToInput)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject(ScriptableObject::create<MockScriptableObject>("Test Name"));

    Assert::AreEqual("Test Name", scriptableObject->getName().c_str());
  }

#pragma endregion

#pragma region Typename Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Create_InputtingNonRegisteredTypeName_ReturnsNullptr)
  {
    Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    std::unique_ptr<ScriptableObject> scriptableObject(ScriptableObject::create(MockScriptableObject::type_name(), ""));

    Assert::IsNull(scriptableObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Create_InputtingRegisteredTypeName_ReturnsInstanceOfInputtedTypeName)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    std::unique_ptr<ScriptableObject> scriptableObject(ScriptableObject::create(MockScriptableObject::type_name(), ""));

    Assert::IsNotNull(scriptableObject.get());
    Assert::IsNotNull(dynamic_cast<MockScriptableObject*>(scriptableObject.get()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Create_InputtingRegisteredTypeName_SetsNameToInput)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    std::unique_ptr<ScriptableObject> scriptableObject(ScriptableObject::create(MockScriptableObject::type_name(), "Test"));

    Assert::IsNotNull(scriptableObject.get());
    Assert::AreEqual("Test", scriptableObject->getName().c_str());
  }

#pragma endregion

#pragma endregion

#pragma region Create Value Field Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_CreateValueField_ReturnsField_WithCorrectValuesSet)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    ValueField<int>& intField = scriptableObject->createValueField_Public("Test Int Field", 5);

    Assert::AreEqual("Test Int Field", intField.getName().c_str());
    Assert::AreEqual(5, intField.getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_CreateValueField_AddsFieldToFieldsVector)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");

    Assert::AreEqual(static_cast<size_t>(0), scriptableObject->getFieldsSize_Public());

    scriptableObject->createValueField_Public("Test Int Field", 5);

    Assert::AreEqual(static_cast<size_t>(1), scriptableObject->getFieldsSize_Public());
  }

#pragma endregion

#pragma region Create Reference Field Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_CreateReferenceField_ReturnsField_WithCorrectValuesSet)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    ReferenceField<std::string>& stringField = scriptableObject->createReferenceField_Public("Test String Field", std::string("Test Value"));

    Assert::AreEqual("Test String Field", stringField.getName().c_str());
    Assert::AreEqual("Test Value", stringField.getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_CreateReferenceField_AddsFieldToFieldsVector)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");

    Assert::AreEqual(static_cast<size_t>(0), scriptableObject->getFieldsSize_Public());

    scriptableObject->createReferenceField_Public("Test String Field", std::string("Test Value"));

    Assert::AreEqual(static_cast<size_t>(1), scriptableObject->getFieldsSize_Public());
  }

#pragma endregion

#pragma region Create Scriptable Object Field Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_CreateScriptableObjectField_ReturnsScriptableObject_WithCorrectValuesSet)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    MockScriptableObject& scriptableObjectField = scriptableObject->createScriptableObject_Public<MockScriptableObject>("Test String Field");

    Assert::AreEqual("Test String Field", scriptableObjectField.getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_CreateScriptableObjectField_AddsScriptableObjectToFieldsVector)
  {
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");

    Assert::AreEqual(static_cast<size_t>(0), scriptableObject->getFieldsSize_Public());

    scriptableObject->createScriptableObject_Public<MockScriptableObject>("Test String Field");

    Assert::AreEqual(static_cast<size_t>(1), scriptableObject->getScriptableObjectsSize_Public());
  }

#pragma endregion

#pragma region Load Tests

#pragma region Template Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_InputtingNonExistentFilePath_ReturnsNullptr)
  {
    std::unique_ptr<MockScriptableObject> object(ScriptableObject::load<MockScriptableObject>("ThisPathShouldExist"));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_DeserializationFails_ReturnsNullptr)
  {
    Path path(TempDirectory::getFullPath(), "FailedDeserialization.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNotNull(document.RootElement());

    std::unique_ptr<FailDeserializationScriptableObject> object(ScriptableObject::load<FailDeserializationScriptableObject>(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_Deserialize_NoNameAttribute_SetsNameToEmptyString)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNull(element->Attribute("name"));

    std::unique_ptr<MockScriptableObject> object(ScriptableObject::load<MockScriptableObject>(path));

    Assert::IsTrue(object->getName().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_Deserialize_LoadsNameAttribute)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("name", "Test Name");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("Test Name", element->Attribute("name"));

    std::unique_ptr<MockScriptableObject> object(ScriptableObject::load<MockScriptableObject>(path));

    Assert::AreEqual("Test Name", object->getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_Deserialize_NoGuidAttribute_SetsGuidToNewGuid)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNull(element->Attribute("guid"));

    std::unique_ptr<MockScriptableObject> object(ScriptableObject::load<MockScriptableObject>(path));

    Assert::IsFalse(object->getGuid().str().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_Deserialize_InvalidGuid_SetsGuidToNewGuid)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("guid", "Invalid");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("Invalid", element->Attribute("guid"));

    std::unique_ptr<MockScriptableObject> object(ScriptableObject::load<MockScriptableObject>(path));

    Assert::AreNotEqual("Invalid", object->getGuid().str().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_Deserialize_LoadsGuidAttribute)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", element->Attribute("guid"));

    std::unique_ptr<MockScriptableObject> object(ScriptableObject::load<MockScriptableObject>(path));

    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", object->getGuid().str().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_FieldFailsDeserialization_ReturnsNullptr)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<FieldFailDeserializationScriptableObject> object(ScriptableObject::load<FieldFailDeserializationScriptableObject>(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_DeserializesAllFieldsCorrectly)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("element");
    document.InsertFirstChild(element);
    element->SetAttribute("IntField", 5);
    element->SetAttribute("StringField", "Test String");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<FieldsPassDeserializationScriptableObject> object(ScriptableObject::load<FieldsPassDeserializationScriptableObject>(path));

    Assert::IsNotNull(object.get());
    Assert::AreEqual(5, object->getIntField());
    Assert::AreEqual("Test String", object->getStringField().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_ChildScriptableObject_WithNoValueSetForAttribute_DoesNotLoadDataOntoScriptableObject)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("name", "Test Name");
    child->SetAttribute("name", "Test Child Name");
    child->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-bbbb29f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNull(element->Attribute("Child"));

    std::unique_ptr<SingleChildScriptableObject> object(ScriptableObject::load<SingleChildScriptableObject>(path));

    // Justification for this not returning null is that no value for the child SO was specified, so we just fallback on the default value
    Assert::IsNotNull(object.get());
    Assert::AreEqual("Child", object->getChild().getName().c_str());
    Assert::AreNotEqual("be39a7c9-eeeb-4d1e-90a4-bbbb29f40e2f", object->getChild().getGuid().str().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_ChildScriptableObject_WithNoDataElement_AndNoMatchingDataFile_ReturnsNull)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    element->SetAttribute("name", "Test Name");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("SuccessChild", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", element->Attribute("SuccessChild"));
    FileAssert::FileDoesNotExist("be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    std::unique_ptr<ChildScriptableObjectPassesDeserializationScriptableObject> object(ScriptableObject::load<ChildScriptableObjectPassesDeserializationScriptableObject>(path));

    // This returns null compared to the above case because we specified a value, but were unable to provide the data for it
    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_ChildScriptableObjectCouldNotBeDeserialized_ReturnsNull)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    element->SetAttribute("FailChild", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");
    child->SetAttribute("name", "Test Child");
    child->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ChildScriptableObjectFailDeserializationScriptableObject> object(ScriptableObject::load<ChildScriptableObjectFailDeserializationScriptableObject>(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_ChildScriptableObjectCouldNotBeLoadedFromFile_ReturnsNull)
  {
    // Child SO
    Path childPath(TempDirectory::getFullPath(), "ChildObject.xml");
    XMLDocument childDocument;
    XMLElement* childElement = childDocument.NewElement("MockScriptableObject");
    childDocument.InsertFirstChild(childElement);
    childElement->SetAttribute("name", "Test Child");
    childElement->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == childDocument.SaveFile(childPath.c_str()));
    FileAssert::FileExists(childPath.as_string());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("name", "Test Child");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("FailChild", childPath.c_str());

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ChildScriptableObjectFailDeserializationScriptableObject> object(ScriptableObject::load<ChildScriptableObjectFailDeserializationScriptableObject>(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_DeserializesAllChildScriptableObjects_WithDataInTheSameFile_Correctly)
  {
    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    child->SetAttribute("name", "Child Scriptable Object");
    child->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");
    child->SetAttribute("IntField", 5);
    child->SetAttribute("StringField", "Test Value");
    element->SetAttribute("name", "Test Child");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("SuccessChild", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ChildScriptableObjectPassesDeserializationScriptableObject> object(ScriptableObject::load<ChildScriptableObjectPassesDeserializationScriptableObject>(path));

    Assert::IsNotNull(object.get());
    Assert::AreEqual("Child Scriptable Object", object->getChild().getName().c_str());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", object->getChild().getGuid().str().c_str());
    Assert::AreEqual(5, object->getChild().getIntField());
    Assert::AreEqual("Test Value", object->getChild().getStringField().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TemplateOverload_LoadsAllChildScriptableObjects_WithDataInOtherAssetFiles_Correctly)
  {
    // Child SO
    Path childPath(TempDirectory::getFullPath(), "ChildObject.xml");
    XMLDocument childDocument;
    XMLElement* childElement = childDocument.NewElement("MockScriptableObject");
    childDocument.InsertFirstChild(childElement);
    childElement->SetAttribute("name", "Child Scriptable Object");
    childElement->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");
    childElement->SetAttribute("IntField", 5);
    childElement->SetAttribute("StringField", "Test Value");

    Assert::IsTrue(XML_SUCCESS == childDocument.SaveFile(childPath.c_str()));
    FileAssert::FileExists(childPath.as_string());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("name", "Test Child");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("SuccessChild", childPath.c_str());

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ChildScriptableObjectPassesDeserializationScriptableObject> object(ScriptableObject::load<ChildScriptableObjectPassesDeserializationScriptableObject>(path));

    Assert::IsNotNull(object.get());
    Assert::AreEqual("Child Scriptable Object", object->getChild().getName().c_str());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", object->getChild().getGuid().str().c_str());
    Assert::AreEqual(5, object->getChild().getIntField());
    Assert::AreEqual("Test Value", object->getChild().getStringField().c_str());
  }

#pragma endregion

#pragma region Type Name Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_InputtingNonExistentFilePath_ReturnsNullptr)
  {
    std::unique_ptr<ScriptableObject> object(ScriptableObject::load("ThisPathShouldExist"));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_DeserializationFails_ReturnsNullptr)
  {
    ScriptableObjectRegistry::addScriptableObject<FailDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<FailDeserializationScriptableObject>());

    Path path(TempDirectory::getFullPath(), "FailedDeserialization.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNotNull(document.RootElement());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_Deserialize_NoNameAttribute_SetsNameToEmptyString)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNull(element->Attribute("name"));

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::IsTrue(object->getName().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_Deserialize_LoadsNameAttribute)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("name", "Test Name");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("Test Name", element->Attribute("name"));

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::AreEqual("Test Name", object->getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_Deserialize_NoGuidAttribute_SetsGuidToNewGuid)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNull(element->Attribute("guid"));

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::IsFalse(object->getGuid().str().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_Deserialize_InvalidGuid_SetsGuidToNewGuid)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("guid", "Invalid");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("Invalid", element->Attribute("guid"));

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::AreNotEqual("Invalid", object->getGuid().str().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_Deserialize_LoadsGuidAttribute)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", element->Attribute("guid"));

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", object->getGuid().str().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_FieldFailsDeserialization_ReturnsNullptr)
  {
    ScriptableObjectRegistry::addScriptableObject<FieldFailDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<FieldFailDeserializationScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_DeserializesAllFieldsCorrectly)
  {
    ScriptableObjectRegistry::addScriptableObject<FieldsPassDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<FieldsPassDeserializationScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement(FieldsPassDeserializationScriptableObject::type_name().c_str());
    document.InsertFirstChild(element);
    element->SetAttribute("IntField", 5);
    element->SetAttribute("StringField", "Test String");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));
    FieldsPassDeserializationScriptableObject* fieldsPassObject = dynamic_cast<FieldsPassDeserializationScriptableObject*>(object.get());

    Assert::IsNotNull(object.get());
    Assert::AreEqual(5, fieldsPassObject->getIntField());
    Assert::AreEqual("Test String", fieldsPassObject->getStringField().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_ChildScriptableObject_WithNoValueSetForAttribute_DoesNotLoadDataOntoScriptableObject)
  {
    ScriptableObjectRegistry::addScriptableObject<SingleChildScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<SingleChildScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement(SingleChildScriptableObject::type_name().c_str());
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    element->SetAttribute("name", "Test Name");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    child->SetAttribute("name", "Test Child Name");
    child->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-bbbb29f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::IsNull(element->Attribute("Child"));

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));
    SingleChildScriptableObject* singleChildObject = dynamic_cast<SingleChildScriptableObject*>(object.get());

    // Justification for this not returning null is that no value for the SO was specified, so we just fallback on the default value
    Assert::IsNotNull(object.get());
    Assert::AreEqual("Child", singleChildObject->getChild().getName().c_str());
    Assert::AreNotEqual("be39a7c9-eeeb-4d1e-90a4-bbbb29f40e2f", singleChildObject->getChild().getGuid().str().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_ChildScriptableObject_WithNoDataElement_AndNoMatchingDataFile_ReturnsFalse)
  {
    ScriptableObjectRegistry::addScriptableObject<ChildScriptableObjectPassesDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<ChildScriptableObjectPassesDeserializationScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    element->SetAttribute("name", "Test Name");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("SuccessChild", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", element->Attribute("SuccessChild"));
    FileAssert::FileDoesNotExist("be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    // This returns null compared to the above case because we specified a value, but were unable to provide the data for it
    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_ChildScriptableObjectCouldNotBeDeserialized_ReturnsNull)
  {
    ScriptableObjectRegistry::addScriptableObject<ChildScriptableObjectFailDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<ChildScriptableObjectFailDeserializationScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    child->SetAttribute("name", "Test Child");
    child->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");
    element->SetAttribute("name", "Test Child");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("FailChild", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_ChildScriptableObjectCouldNotBeLoadedFromFile_ReturnsNull)
  {
    ScriptableObjectRegistry::addScriptableObject<ChildScriptableObjectFailDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<ChildScriptableObjectFailDeserializationScriptableObject>());

    // Child SO
    Path childPath(TempDirectory::getFullPath(), "ChildObject.xml");
    XMLDocument childDocument;
    XMLElement* childElement = childDocument.NewElement("MockScriptableObject");
    childDocument.InsertFirstChild(childElement);
    childElement->SetAttribute("name", "Test Child");
    childElement->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == childDocument.SaveFile(childPath.c_str()));
    FileAssert::FileExists(childPath.as_string());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->SetAttribute("name", "Test Child");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("FailChild", childPath.c_str());

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    Assert::IsNull(object.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_DeserializesAllChildScriptableObjects_WithDataInTheSameFile_Correctly)
  {
    ScriptableObjectRegistry::addScriptableObject<ChildScriptableObjectPassesDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<ChildScriptableObjectPassesDeserializationScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement(ChildScriptableObjectPassesDeserializationScriptableObject::type_name().c_str());
    XMLElement* child = document.NewElement("MockScriptableObject");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child);
    child->SetAttribute("name", "Child Scriptable Object");
    child->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");
    child->SetAttribute("IntField", 5);
    child->SetAttribute("StringField", "Test Value");
    element->SetAttribute("name", "Test Child");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("SuccessChild", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));
    ChildScriptableObjectPassesDeserializationScriptableObject* childPassesObject = dynamic_cast<ChildScriptableObjectPassesDeserializationScriptableObject*>(object.get());

    Assert::IsNotNull(object.get());
    Assert::AreEqual("Child Scriptable Object", childPassesObject->getChild().getName().c_str());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", childPassesObject->getChild().getGuid().str().c_str());
    Assert::AreEqual(5, childPassesObject->getChild().getIntField());
    Assert::AreEqual("Test Value", childPassesObject->getChild().getStringField().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_TypeNameOverload_LoadsAllChildScriptableObjects_WithDataInOtherAssetFiles_Correctly)
  {
    ScriptableObjectRegistry::addScriptableObject<ChildScriptableObjectPassesDeserializationScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<ChildScriptableObjectPassesDeserializationScriptableObject>());

    // Child SO
    Path childPath(TempDirectory::getFullPath(), "ChildObject.xml");
    XMLDocument childDocument;
    XMLElement* childElement = childDocument.NewElement("MockScriptableObject");
    childDocument.InsertFirstChild(childElement);
    childElement->SetAttribute("name", "Child Scriptable Object");
    childElement->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-677029f40e2f");
    childElement->SetAttribute("IntField", 5);
    childElement->SetAttribute("StringField", "Test Value");

    Assert::IsTrue(XML_SUCCESS == childDocument.SaveFile(childPath.c_str()));
    FileAssert::FileExists(childPath.as_string());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement(ChildScriptableObjectPassesDeserializationScriptableObject::type_name().c_str());
    document.InsertFirstChild(element);
    element->SetAttribute("name", "Test Child");
    element->SetAttribute("guid", "be39a7c9-eeeb-4d1e-90a4-aaaa29f40e2f");
    element->SetAttribute("SuccessChild", childPath.c_str());

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));
    ChildScriptableObjectPassesDeserializationScriptableObject* childPassesObject = dynamic_cast<ChildScriptableObjectPassesDeserializationScriptableObject*>(object.get());

    AssertExt::IsNotNull(object);
    Assert::AreEqual("Child Scriptable Object", childPassesObject->getChild().getName().c_str());
    Assert::AreEqual("be39a7c9-eeeb-4d1e-90a4-677029f40e2f", childPassesObject->getChild().getGuid().str().c_str());
    Assert::AreEqual(5, childPassesObject->getChild().getIntField());
    Assert::AreEqual("Test Value", childPassesObject->getChild().getStringField().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Load_InputtingPathToNonRegisteredType_ReturnsNullptr)
  {
    Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<FieldsPassDeserializationScriptableObject>());

    Path path(TempDirectory::getFullPath(), "Object.xml");
    XMLDocument document;
    XMLElement* element = document.NewElement(FieldsPassDeserializationScriptableObject::type_name().c_str());
    document.InsertFirstChild(element);
    element->SetAttribute("IntField", 5);
    element->SetAttribute("StringField", "Test String");

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(path.c_str()));
    FileAssert::FileExists(path.as_string());

    std::unique_ptr<ScriptableObject> object(ScriptableObject::load(path));

    AssertExt::IsNull(object);
  }

#pragma endregion

#pragma endregion

#pragma region Save Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_InputtingNonExistentFullFilePath_CreatesFile)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");

    FileAssert::FileDoesNotExist(path.as_string());

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    scriptableObject->save(path);

    FileAssert::FileExists(path.as_string());

    observer_ptr<Data> data = getResourceManager().load<Data>(path);

    // Check the data is loadable
    Assert::IsNotNull(data);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_InputtingExistentFullFilePath_OverwritesFile)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    File file(path);
    file.create();
    file.append("Test");

    FileAssert::FileContentsEqual(path.as_string(), "Test");

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    scriptableObject->save(path);

    FileAssert::FileContentsNotEqual(path.as_string(), "Test");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_InputtingNonExistentRelativeFilePath_CreatesFile)
  {
    Path path(TempDirectory::getRelativePath(), "Test.xml");
    Path fullFilePath(TestResources::getResourcesDirectory(), path);

    FileAssert::FileDoesNotExist(fullFilePath.as_string());

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    scriptableObject->save(path);

    FileAssert::FileExists(fullFilePath.as_string());

    observer_ptr<Data> data = getResourceManager().load<Data>(path);

    // Check the data is loadable
    Assert::IsNotNull(data);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_InputtingExistentRelativeFilePath_OverwritesFile)
  {
    Path path(TempDirectory::getRelativePath(), "Test.xml");
    Path fullFilePath(TestResources::getResourcesDirectory(), path);
    File file(fullFilePath);
    file.create();
    file.append("Test");

    FileAssert::FileContentsEqual(fullFilePath.as_string(), "Test");

    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    scriptableObject->save(path);

    FileAssert::FileContentsNotEqual(fullFilePath.as_string(), "Test");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_CreatesElementForObject)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    scriptableObject->setName("Test");
    scriptableObject->save(path);

    observer_ptr<Data> data = getResourceManager().load<Data>(path);

    Assert::IsNotNull(data);
    Assert::IsNotNull(data->getDocumentRoot());
    Assert::AreEqual("Test", data->getDocumentRoot()->Name());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_SavesObjectNameAndGuid)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");
    scriptableObject->setName("Test");
    scriptableObject->save(path);

    observer_ptr<Data> data = getResourceManager().load<Data>(path);

    Assert::IsNotNull(data);
    Assert::AreEqual("Test", data->getDocumentRoot()->Attribute("name"));
    Assert::AreEqual(scriptableObject->getGuid().str().c_str(), data->getDocumentRoot()->Attribute("guid"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_SavesFieldsCorrectly)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    FieldsPassDeserializationScriptableObject object;
    object.setName("Test");
    object.setIntField(5);
    object.setStringField("Test Value");
    object.save(path);

    observer_ptr<Data> data = getResourceManager().load<Data>(path);

    Assert::IsNotNull(data);
    Assert::AreEqual(5, data->getDocumentRoot()->IntAttribute("IntField"));
    Assert::AreEqual("Test Value", data->getDocumentRoot()->Attribute("StringField"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObject_Save_SavesChildScriptableObjectsCorrectly)
  {
    Path path(TempDirectory::getFullPath(), "Test.xml");
    ChildScriptableObjectPassesDeserializationScriptableObject object;
    object.setName("Test");
    object.getChild().setName("TestChild");
    object.getChild().setIntField(5);
    object.getChild().setStringField("Test Value");
    object.save(path);

    observer_ptr<Data> data = getResourceManager().load<Data>(path);

    Assert::IsNotNull(data);

    const tinyxml2::XMLElement* testChild = data->getDocumentRoot()->FirstChildElement("TestChild");

    Assert::IsNotNull(testChild);
    Assert::AreEqual("TestChild", testChild->Attribute("name"));
    Assert::AreEqual(object.getChild().getGuid().str().c_str(), testChild->Attribute("guid"));
    Assert::AreEqual(5, testChild->IntAttribute("IntField"));
    Assert::AreEqual("Test Value", testChild->Attribute("StringField"));
  }

#pragma endregion

  };
}