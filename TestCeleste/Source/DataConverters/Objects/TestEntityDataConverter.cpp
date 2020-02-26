#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Objects/MockEntityDataConverter.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestEntityDataConverter)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    MockEntityDataConverter converter("Entity");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    MockEntityDataConverter converter("Entity");

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_Constructor_SetsElementName_ToInput)
  {
    MockEntityDataConverter converter("Entity");

    Assert::AreEqual("Entity", converter.getElementName().c_str());
  }

#pragma endregion

#pragma region Copy Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_CopyConstructor_CopiesElementName)
  {
    EntityDataConverter<MockEntity> converter("Entity");
    EntityDataConverter<MockEntity> converter2(converter);

    Assert::AreEqual("Entity", converter.getElementName().c_str());
    Assert::AreEqual("Entity", converter2.getElementName().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_CopyConstructor_CopiesIsActiveAttribute)
  {
    const EntityDataConverter<MockEntity> converter("Entity");
    const EntityDataConverter<MockEntity> converter2(converter);

    Assert::AreEqual(static_cast<size_t>(1), converter2.getAttributesSize());
    Assert::IsNotNull(converter2.findAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Move Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_MoveConstructor_MovesElementName)
  {
    EntityDataConverter<MockEntity> converter("Entity");

    Assert::AreEqual("Entity", converter.getElementName().c_str());

    EntityDataConverter<MockEntity> converter2(std::move(converter));

    Assert::AreEqual("Entity", converter2.getElementName().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_MoveConstructor_MovesIsActiveAttribute)
  {
    EntityDataConverter<MockEntity> converter("Entity");
    const EntityDataConverter<MockEntity>& constConverter = static_cast<const EntityDataConverter<MockEntity>&>(converter);

    Assert::IsNotNull(constConverter.findAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));

    const EntityDataConverter<MockEntity> converter2(std::move(converter));

    Assert::IsNotNull(converter2.findAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Assignment Operator Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_AssignmentOperator_CopiesElementName)
  {
    EntityDataConverter<MockEntity> converter("Entity");
    EntityDataConverter<MockEntity> converter2("OtherEntity");

    Assert::AreEqual("OtherEntity", converter2.getElementName().c_str());

    converter2 = converter;

    Assert::AreEqual("Entity", converter2.getElementName().c_str());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    MockEntityDataConverter converter("Entity");

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertFromXML_InputtingNullptr_SetsIsDataLoadedCorrectlyToFalse)
  {
    MockEntityDataConverter converter("Entity");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "WubWubWub");

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectlyToFalse)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "WubWubWub");

    converter.convertFromXML(element);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "true");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectlyToTrue)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "true");

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertFromXML_InputtingValidXML_CallsDoConvertFromXML)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "true");

    Assert::IsFalse(converter.isDoConvertFromXMLCalled());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDoConvertFromXMLCalled());
  }

#pragma endregion

#pragma region Convert Is Active Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertIsActive_AttributeDoesNotExist_LeavesIsActiveAsTrue)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    const XMLElement* element = document.NewElement("Entity");

    Assert::IsNull(element->FindAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIsActive());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertIsActive_AttributeDoesNotExist_DoesNotCauseConversionToFail)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    const XMLElement* element = document.NewElement("Entity");

    Assert::IsNull(element->FindAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertIsActive_AttributeExists_InvalidText_LeavesIsActiveAsTrue)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "WubWubWub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIsActive());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertIsActive_AttributeExists_InvalidText_CausesConversionToFail)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "WubWubWub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertIsActive_AttributeExists_ValidText_SetsIsActiveToValue)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "false");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIsActive());

    converter.convertFromXML(element);

    Assert::IsFalse(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_ConvertIsActive_AttributeExists_ValidText_DoesNotCauseConversionToFail)
  {
    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "false");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_SetValues_InputtingNullEntity_DoesNothing)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    MockEntityDataConverter converter("Entity");

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(MockEntity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_SetValues_NonNullEntity_ButDataNotConvertedCorrectly_DoesNothing)
  {
    MockEntity entity;
    entity.setActive(false);

    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "WubWubWub");

    Assert::IsFalse(converter.convertFromXML(element));
    AssertCel::IsNotActive(entity);

    converter.setValues(entity);

    AssertCel::IsNotActive(entity);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_SetValues_NonNullEntity_AndDataLoadedCorrectly_SetsEntityIsActiveToLoadedValue)
  {
    MockEntity entity;

    MockEntityDataConverter converter("Entity");
    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "true");

    Assert::IsTrue(converter.convertFromXML(element));
    AssertCel::IsNotActive(entity);

    converter.setValues(entity);

    AssertCel::IsActive(entity);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityDataConverter_SetValues_NonNullEntity_AndDataLoadedCorrectly_CallsDoSetValues)
  {
    MockEntityDataConverter converter("Entity");
    MockEntity entity;

    XMLDocument document;
    XMLElement* element = document.NewElement("Entity");
    element->SetAttribute(EntityDataConverter<MockEntity>::IS_ACTIVE_ATTRIBUTE_NAME, "false");

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.isDoSetValuesCalled());

    converter.setValues(entity);

    Assert::IsTrue(converter.isDoSetValuesCalled());
  }

#pragma endregion

  };
}