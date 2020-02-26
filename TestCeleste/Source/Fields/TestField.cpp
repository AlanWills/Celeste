#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Fields/MockField.h"

using namespace tinyxml2;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestField)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Constuctor_SetsNameToInput)
  {
    MockField field("Test Name");

    Assert::AreEqual("Test Name", field.getName().c_str());
  }

#pragma endregion

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingNullptr_ReturnsFalse)
  {
    MockField field("");

    Assert::IsFalse(field.deserialize(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingNullptr_DoesNotCallDoDeserialize)
  {
    MockField field("");

    Assert::IsFalse(field.isDoDeserializeCalled());

    field.deserialize(nullptr);

    Assert::IsFalse(field.isDoDeserializeCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingElement_CallsDoDeserialize)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("");
    MockField field("");

    Assert::IsFalse(field.isDoDeserializeCalled());

    field.deserialize(element);

    Assert::IsTrue(field.isDoDeserializeCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingElement_ReturnsResultOfDoDeserialize)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("");
    MockField field("");

    Assert::IsTrue(field.getDoDeserializeResult());
    Assert::IsTrue(field.deserialize(element));

    field.setDoDeserializeResult(false);

    Assert::IsFalse(field.getDoDeserializeResult());
    Assert::IsFalse(field.deserialize(element));
  }

#pragma endregion

#pragma region Serialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingNullptr_ReturnsNullptr)
  {
    MockField field("");

    Assert::IsNull(field.serialize(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingNullptr_DoesNotCallDoSerialize)
  {
    MockField field("");

    Assert::IsFalse(field.isDoSerializeCalled());

    field.serialize(nullptr);

    Assert::IsFalse(field.isDoSerializeCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingElement_ReturnsElement)
  {
    MockField field("");
    XMLDocument document;
    XMLElement* element = document.NewElement("");

    Assert::IsTrue(element == field.serialize(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Field_Deserialize_InputtingElement_CallsDoSerialize)
  {
    MockField field("");
    XMLDocument document;
    XMLElement* element = document.NewElement("");

    Assert::IsFalse(field.isDoSerializeCalled());

    field.serialize(element);

    Assert::IsTrue(field.isDoSerializeCalled());
  }

#pragma endregion

};

}