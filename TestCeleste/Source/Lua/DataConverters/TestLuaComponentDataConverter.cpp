#include "Lua/DataConverters/LuaComponentDataConverter.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockComponent.h"

using namespace Celeste;
using namespace Celeste::Lua;
using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste::Lua
{
  CELESTE_TEST_CLASS(TestLuaComponentDataConverter)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingInvalidTable_DoesNotConvertAttributesOrElements)
  {
    LuaComponentDataConverter converter(LuaState::instance().create_table(), "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_SetsElementName_ToInput)
  {
    LuaComponentDataConverter converter(LuaState::instance().create_table(), "Test");

    Assert::AreEqual("Test", converter.getElementName().c_str());
  }

#pragma region Attribute Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ButNoIndividualAttributes_DoesNotAddAttributes)
  {
    sol::table table = LuaState::instance().create_table();
    table["Attributes"] = LuaState::instance().create_table();
    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_AttributeHasNoName_DoesNotAddAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Type"] = "bool";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_AttributeHasNoType_DoesNotAddAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(1), converter.getAttributesSize());
  }

#pragma region Unsigned Vec2 Attribute

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ValueUnsignedVec2Type_CreatesNewUnsignedValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    attrTable["Is Reference"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::uvec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_UnsignedVec2Type_NoIsReferenceEntry_CreatesNewUnsignedValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::uvec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ReferenceUnsignedVec2Type_CreatesNewUnsignedVec2Attribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    attrTable["Is Reference"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ReferenceAttribute<glm::uvec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithUnsignedVec2AttributeElement_HasTrueIsRequiredEntry_SetsIsRequiredToTrue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    attrTable["Is Required"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsTrue(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithUnsignedVec2AttributeElement_HasFalseIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    attrTable["Is Required"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithUnsignedVec2AttributeElement_NoIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithUnsignedVec2AttributeElement_HasDefaultValueEntry_SetsDefaultValueToValue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    attrTable["Default Value"] = "5,1";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::uvec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual(glm::uvec2(5, 1), dynamic_cast<const XML::ValueAttribute<glm::uvec2>*>(converter.findAttribute("Attr"))->getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithUnsignedVec2AttributeElement_NoDefaultValueEntry_SetsDefaultValueTo_glmuvec2)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "uvec2";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::uvec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual(glm::uvec2(), dynamic_cast<const XML::ValueAttribute<glm::uvec2>*>(converter.findAttribute("Attr"))->getValue());
  }

#pragma endregion

#pragma region Vec2 Attribute

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ValueVec2Type_CreatesNewValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    attrTable["Is Reference"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::vec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_Vec2Type_NoIsReferenceEntry_CreatesNewValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::vec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ReferenceVec2Type_CreatesNewVec2Attribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    attrTable["Is Reference"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ReferenceAttribute<glm::vec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithVec2AttributeElement_HasTrueIsRequiredEntry_SetsIsRequiredToTrue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    attrTable["Is Required"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsTrue(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithVec2AttributeElement_HasFalseIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    attrTable["Is Required"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithVec2AttributeElement_NoIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithVec2AttributeElement_HasDefaultValueEntry_SetsDefaultValueToValue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    attrTable["Default Value"] = "-5,1.2";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::vec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual(glm::vec2(-5, 1.2f), dynamic_cast<const XML::ValueAttribute<glm::vec2>*>(converter.findAttribute("Attr"))->getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithVec2AttributeElement_NoDefaultValueEntry_SetsDefaultValueTo_glmvec2)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "vec2";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<glm::vec2>*>(converter.findAttribute("Attr")));
    Assert::AreEqual(glm::vec2(), dynamic_cast<const XML::ValueAttribute<glm::vec2>*>(converter.findAttribute("Attr"))->getValue());
  }

#pragma endregion

#pragma region Bool Attribute

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ValueBoolType_CreatesNewBoolValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    attrTable["Is Reference"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<bool>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_BoolType_NoIsReferenceEntry_CreatesNewBoolValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<bool>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ReferenceBoolType_CreatesNewBoolReferenceAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    attrTable["Is Reference"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ReferenceAttribute<bool>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithBoolAttributeElement_HasTrueIsRequiredEntry_SetsIsRequiredToTrue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    attrTable["Is Required"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsTrue(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithBoolAttributeElement_HasFalseIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    attrTable["Is Required"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithBoolAttributeElement_NoIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;
    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithBoolAttributeElement_HasDefaultValueEntry_SetsDefaultValueToValue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    attrTable["Default Value"] = "true";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;
    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<bool>*>(converter.findAttribute("Attr")));
    Assert::IsTrue(dynamic_cast<const XML::ValueAttribute<bool>*>(converter.findAttribute("Attr"))->getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithBoolAttributeElement_NoDefaultValueEntry_SetsDefaultValueToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "bool";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    bool value = bool();
    bool other = value;

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<bool>*>(converter.findAttribute("Attr")));
    Assert::IsFalse(dynamic_cast<const XML::ValueAttribute<bool>*>(converter.findAttribute("Attr"))->getValue());
  }

#pragma endregion

#pragma region Float Attribute

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ValueFloatType_CreatesNewFloatValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    attrTable["Is Reference"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<float>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_FloatType_NoIsReferenceEntry_CreatesNewFloatValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<float>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ReferenceFloatType_CreatesNewFloatReferenceAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    attrTable["Is Reference"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ReferenceAttribute<float>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithFloatAttributeElement_HasTrueIsRequiredEntry_SetsIsRequiredToTrue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    attrTable["Is Required"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsTrue(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithFloatAttributeElement_HasFalseIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    attrTable["Is Required"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithFloatAttributeElement_NoIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;
    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithFloatAttributeElement_HasDefaultValueEntry_SetsDefaultValueToValue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    attrTable["Default Value"] = "1.0";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;
    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<float>*>(converter.findAttribute("Attr")));
    Assert::AreEqual(1.0f, dynamic_cast<const XML::ValueAttribute<float>*>(converter.findAttribute("Attr"))->getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithFloatAttributeElement_NoDefaultValueEntry_SetsDefaultValueToZero)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "float";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    bool value = bool();
    bool other = value;

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<float>*>(converter.findAttribute("Attr")));
    Assert::AreEqual(0.0f, dynamic_cast<const XML::ValueAttribute<float>*>(converter.findAttribute("Attr"))->getValue());
  }

#pragma endregion

#pragma region String Attribute

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ValueStringType_CreatesNewStringValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    attrTable["Is Reference"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<std::string>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_StringType_NoIsReferenceEntry_CreatesNewStringValueAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<std::string>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithAttributesElement_ReferenceStringType_CreatesNewStringReferenceAttribute)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    attrTable["Is Reference"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ReferenceAttribute<std::string>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Attr", converter.findAttribute("Attr")->getAttributeName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithStringAttributeElement_HasTrueIsRequiredEntry_SetsIsRequiredToTrue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    attrTable["Is Required"] = true;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsTrue(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithStringAttributeElement_HasFalseIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    attrTable["Is Required"] = false;
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithStringAttributeElement_NoIsRequiredEntry_SetsIsRequiredToFalse)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsFalse(converter.findAttribute("Attr")->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithStringAttributeElement_HasDefaultValueEntry_SetsDefaultValueToValue)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    attrTable["Default Value"] = "Test";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<std::string>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("Test", dynamic_cast<const XML::ValueAttribute<std::string>*>(converter.findAttribute("Attr"))->getValue().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithStringAttributeElement_NoDefaultValueEntry_SetsDefaultValueToEmptyString)
  {
    sol::table table = LuaState::instance().create_table();
    sol::table attributesTable = LuaState::instance().create_table();
    sol::table attrTable = attributesTable.create();
    attrTable["Name"] = "Attr";
    attrTable["Type"] = "string";
    table["Attributes"] = attributesTable;
    table["Attributes"]["Attribute"] = attrTable;

    const LuaComponentDataConverter converter(table, "Test");

    bool value = bool();
    bool other = value;

    // 1 attribute from base class
    Assert::AreEqual(static_cast<size_t>(2), converter.getAttributesSize());
    Assert::IsNotNull(dynamic_cast<const XML::ValueAttribute<std::string>*>(converter.findAttribute("Attr")));
    Assert::AreEqual("", dynamic_cast<const XML::ValueAttribute<std::string>*>(converter.findAttribute("Attr"))->getValue().c_str());
  }

#pragma endregion

#pragma endregion

#pragma region Element Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithElementsEntry_ButNoIndividualElementEntries_DoesNotAddElements)
  {
    sol::table table = LuaState::instance().create_table();
    table["Elements"] = LuaState::instance().create_table();
    const LuaComponentDataConverter converter(table, "Test");

    Assert::AreEqual(static_cast<size_t>(0), converter.getElementsSize());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithNoDoConvertFromXMLEntry_DoesNothing)
  {
    // Can't really do more than this right now
    LuaComponentDataConverter converter(LuaState::instance().create_table(), "Test");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Constructor_InputtingValidTable_WithNoDoSetValuesEntry_DoesNothing)
  {
    // Can't really do more than this right now
    LuaComponentDataConverter converter(LuaState::instance().create_table(), "Test");
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_ConvertFromXML_NoCallback_ReturnsTrue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Child");
    LuaComponentDataConverter converter(LuaState::instance().create_table(), "Test");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_ConvertFromXML_WithCallback_CallsCallback)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Child");
    sol::table table = LuaState::instance().create_table();
    table["ConvertFromXML"] = [](tinyxml2::XMLElement* element) -> bool
    {
      LuaState::instance().globals()["called"] = true;
      return true;
    };

    LuaComponentDataConverter converter(table, "Test");
    LuaState::instance().globals()["called"] = false;

    Assert::IsFalse(LuaState::instance().globals()["called"].get_or(true));

    converter.convertFromXML(element);

    Assert::IsTrue(LuaState::instance().globals()["called"].get_or(false));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_DoConvertFromXML_WithCallback_CallbackReturnsFalse_ReturnsFalse)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Child");
    sol::table table = LuaState::instance().create_table();
    table["ConvertFromXML"] = [](tinyxml2::XMLElement* element) -> bool
    {
      return false;
    };

    LuaComponentDataConverter converter(table, "Test");

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_DoConvertFromXML_WithCallback_CallbackReturnsTrue_ReturnsTrue)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Child");
    sol::table table = LuaState::instance().create_table();
    table["ConvertFromXML"] = [](tinyxml2::XMLElement* element) -> bool
    {
      return true;
    };

    LuaComponentDataConverter converter(table, "Test");

    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

#pragma region Do Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_DoSetValues_NoCallback_DoesNoLuaInteraction)
  {
    MockComponent component;
    LuaComponentDataConverter converter(LuaState::instance().create_table(), "Test");

    // Just check this doesn't throw
    converter.setValues(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_DoSetValues_WithCallback_ForNonLuaRegisteredComponent_CallsCallbackWithComponentPtr)
  {
    class TempComponent : public MockComponent {};

    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Child");

    TempComponent component;
    sol::table table = LuaState::instance().create_table();
    table["SetValues"] = [](LuaComponentDataConverter*, sol::object object) -> void
    {
      LuaState::instance().globals()["called"] = true;

      Assert::IsNotNull(&object.as<TempComponent&>());
    };

    LuaComponentDataConverter converter(table, "Test");
    LuaState::instance().globals()["called"] = false;
    Celeste::Lua::registerUserType<Component>("Component");

    Assert::IsTrue(LuaState::instance().globals()["Component"].valid());
    Assert::IsFalse(LuaState::instance().globals()["TempComponent"].valid());
    Assert::IsFalse(LuaState::instance().globals()["called"].get_or(true));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(component);

    Assert::IsTrue(LuaState::instance().globals()["called"].get_or(false));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_DoSetValues_WithCallback_ForLuaRegisteredComponent_CallsCallbackWithDerivedPtrType)
  {
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Child");

    MockComponent component;
    sol::table table = LuaState::instance().create_table();
    table["SetValues"] = [](LuaComponentDataConverter*, sol::object object) -> void
    {
      LuaState::instance().globals()["called"] = true;

      Assert::IsNotNull(&object.as<MockComponent&>());
    };

    LuaComponentDataConverter converter(table, "MockComponent");
    LuaState::instance().globals()["called"] = false;
    Celeste::Lua::registerUserType<Component>("Component");
    Celeste::Lua::registerUserType<MockComponent>("MockComponent");

    Assert::IsTrue(LuaState::instance().globals()["Component"].valid());
    Assert::IsTrue(LuaState::instance().globals()["MockComponent"].valid());
    Assert::IsFalse(LuaState::instance().globals()["called"].get_or(true));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(component);

    Assert::IsTrue(LuaState::instance().globals()["called"].get_or(false));
  }

#pragma endregion

  };
}