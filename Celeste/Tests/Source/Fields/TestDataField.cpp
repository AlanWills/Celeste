#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Fields/MockDataField.h"

using namespace tinyxml2;


namespace TestCeleste
{
  namespace Fields
  {
    CELESTE_TEST_CLASS(TestDataField)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Constructor_SetsName_ToInput)
    {
      MockDataField<int, true> field("Test Name");

      Assert::AreEqual("Test Name", field.getName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_DefaultConstructor_SetsValue_ToDefaultValueOfType)
    {
      MockDataField<int, true> field("");

      Assert::AreEqual(0, field.getValue());

      MockDataField<std::string, true> field2("");

      Assert::AreEqual("", field2.getValue().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Constructor_SetsValue_ToInput)
    {
      MockDataField<int, true> field("", 5);

      Assert::AreEqual(5, field.getValue());

      MockDataField<std::string, true> field2("", "Test Value");

      Assert::AreEqual("Test Value", field2.getValue().c_str());
    }

#pragma endregion

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Deserialize_InputtingElement_WithNoMatchingAttribute_ReturnsFalse)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, true> field("Test", 5);

      Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute("Test"));
      Assert::IsFalse(field.deserialize(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Deserialize_InputtingElement_WithNoMatchingAttribute_DoesNotChangeValue)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, true> field("Test", 5);

      Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute("Test"));
      Assert::AreEqual(5, field.getValue());

      field.deserialize(element);

      Assert::AreEqual(5, field.getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Deserialize_InputtingElement_WithAttribute_InvalidValue_ReturnsFalse)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, true> field("Test", 5);
      element->SetAttribute("Test", "WubbaLubbaDubDub");

      Assert::AreEqual("WubbaLubbaDubDub", element->Attribute("Test"));
      Assert::IsFalse(field.deserialize(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Deserialize_InputtingElement_WithAttribute_InvalidValue_DoesNotChangeValue)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, true> field("Test", 5);
      element->SetAttribute("Test", "WubbaLubbaDubDub");

      Assert::AreEqual("WubbaLubbaDubDub", element->Attribute("Test"));
      Assert::AreEqual(5, field.getValue());

      field.deserialize(element);

      Assert::AreEqual(5, field.getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Deserialize_InputtingElement_WithAttribute_ValidValue_ReturnsTrue)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, true> field("Test", 5);
      element->SetAttribute("Test", "-6");

      Assert::AreEqual("-6", element->Attribute("Test"));
      Assert::IsTrue(field.deserialize(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Deserialize_InputtingElement_WithAttribute_ValidValue_SetsValueToCorrectValue)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, true> field("Test", 5);
      element->SetAttribute("Test", "-6");

      Assert::AreEqual("-6", element->Attribute("Test"));
      Assert::AreEqual(5, field.getValue());

      field.deserialize(element);

      Assert::AreEqual(-6, field.getValue());
    }

#pragma endregion

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Serialize_InputtingNullptr_DoesNothing)
    {
      MockDataField<int, false> field("Test", 5);
      field.serialize(nullptr);

      // Check this doesn't throw
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Serialize_InputtingNullptr_ReturnsNullptr)
    {
      MockDataField<int, false> field("Test", 5);
      
      Assert::IsNull(field.serialize(nullptr));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Serialize_InputtingElement_ReturnsElement)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, false> field("Test", 5);

      Assert::IsTrue(field.serialize(element) == element);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Serialize_InputtingElement_AddsCorrectAttribute_AndCorrectSerializedString)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, false> field("Test", 5);

      Assert::IsNull(element->Attribute("Test"));

      field.serialize(element);

      Assert::AreEqual(5, element->IntAttribute("Test"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataField_Serialize_InputtingElement_WithAttributeWithSameName_OverwritesAttributeValue)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      MockDataField<int, false> field("Test", 5);
      element->SetAttribute("Test", "-105");

      Assert::AreEqual(-105, element->IntAttribute("Test"));

      field.serialize(element);

      Assert::AreEqual(5, element->IntAttribute("Test"));
    }

#pragma endregion

    };
  }
}