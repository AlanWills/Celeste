#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Objects/MockObjectDataConverter.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestObjectDataConverter)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    MockObjectDataConverter converter("Object");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_Constructor_SetsElementName_ToInput)
  {
    MockObjectDataConverter converter("Object");

    Assert::AreEqual("Object", converter.getElementName().c_str());
  }

#pragma endregion

#pragma region Copy Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_CopyConstructor_CopiesElementName)
  {
    ObjectDataConverter<MockObject> converter("Object");
    ObjectDataConverter<MockObject> converter2(converter);

    Assert::AreEqual("Object", converter.getElementName().c_str());
    Assert::AreEqual("Object", converter2.getElementName().c_str());
  }

#pragma endregion

#pragma region Move Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_MoveConstructor_MovesElementName)
  {
    ObjectDataConverter<MockObject> converter("Object");

    Assert::AreEqual("Object", converter.getElementName().c_str());
    
    ObjectDataConverter<MockObject> converter2(std::move(converter));

    Assert::AreEqual("Object", converter2.getElementName().c_str());
  }

#pragma endregion

#pragma region Assignment Operator Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_AssignmentOperator_CopiesElementName)
  {
    ObjectDataConverter<MockObject> converter("Object");
    ObjectDataConverter<MockObject> converter2("OtherObject");

    Assert::AreEqual("OtherObject", converter2.getElementName().c_str());

    converter2 = converter;

    Assert::AreEqual("Object", converter2.getElementName().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_AssignmentOperator_CopiesIsActiveAttribute)
  {
    // Don't know how we can properly test this...
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    MockObjectDataConverter converter("Object");

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_ConvertFromXML_InputtingNullptr_SetsIsDataLoadedCorrectlyToFalse)
  {
    MockObjectDataConverter converter("Object");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    // Can't have invalid XML for just the Object class but we leave the test to show it's been considered
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectlyToFalse)
  {
    // Can't have invalid XML for just the Object class but we leave the test to show it's been considered
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    MockObjectDataConverter converter("Object");
    XMLDocument document;
    XMLElement* element = document.NewElement("Object");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectlyToTrue)
  {
    MockObjectDataConverter converter("Object");
    XMLDocument document;
    XMLElement* element = document.NewElement("Object");

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_ConvertFromXML_InputtingValidXML_CallsDoConvertFromXML)
  {
    MockObjectDataConverter converter("Object");
    XMLDocument document;
    XMLElement* element = document.NewElement("Object");

    Assert::IsFalse(converter.isDoConvertFromXMLCalled());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDoConvertFromXMLCalled());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_SetValues_NonNullObject_ButDataNotConvertedCorrectly_DoesNotCallDoSetValues)
  {
    MockObject object;

    MockObjectDataConverter converter("Object");
    XMLDocument document;
    XMLElement* element = document.NewElement("Object");

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.isDoSetValuesCalled());

    converter.setValues(object);

    Assert::IsTrue(converter.isDoSetValuesCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectDataConverter_SetValues_NonNullObject_AndDataLoadedCorrectly_CallsDoSetValues)
  {
    MockObjectDataConverter converter("Object");
    MockObject object;

    XMLDocument document;
    XMLElement* element = document.NewElement("Object");

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.isDoSetValuesCalled());

    converter.setValues(object);

    Assert::IsTrue(converter.isDoSetValuesCalled());
  }

#pragma endregion

  };
}