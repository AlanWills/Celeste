#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/XML/AttributeScriptCommands.h"
#include "Lua/LuaState.h"

#include "DataConverters/DataConverter.h"
#include "Deserialization/MathsDeserializers.h"
#include "Bindings/MathsDataBindingGenerators.h"

using namespace Celeste;
using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua::Lua::XML::AttributeScriptCommands
{
#pragma region Dummy Data Converter Classes

  template <typename T>
  class DummyValueAttributeDataConverter : public DataConverter
  {
  public:
    DummyValueAttributeDataConverter(
      T defaultValue = T(),
      DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
      DataConverter("DummyValue"),
      m_attribute(createValueAttribute<T>("DummyAttribute", defaultValue, required))
    {
    }

    Celeste::XML::ValueAttribute<T>& m_attribute;
  };

  template <typename T>
  class DummyReferenceAttributeDataConverter : public DataConverter
  {
  public:
    DummyReferenceAttributeDataConverter(
      const T& defaultValue = T(),
      DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
      DataConverter("DummyReference"),
      m_attribute(createReferenceAttribute<T>("DummyAttribute", defaultValue, required))
    {
    }

    Celeste::XML::ReferenceAttribute<T>& m_attribute;
  };

#pragma endregion

  CELESTE_TEST_CLASS(TestAttributeScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_AddsAttributeUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_isBoolFunction_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["isBool"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["isBool"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_asBoolFunction_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["asBool"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["asBool"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_isFloatFunction_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["isFloat"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["isFloat"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_asFloatFunction_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["asFloat"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["asFloat"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_isStringFunction_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["isString"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["isString"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_asStringFunction_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["asString"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["asString"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_isUVec2_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["isUVec2"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["isUVec2"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_asUVec2_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["asUVec2"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["asUVec2"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_isVec2_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["isVec2"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["isVec2"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_Initialize_Adds_asVec2_ToAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"]["asVec2"].valid());

    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"]["asVec2"].valid());
  }

#pragma endregion

#pragma region Is Bool Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isBoolFunction_InputtingBoolValueAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isBool"];
    DummyValueAttributeDataConverter<bool> boolValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(boolValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isBoolFunction_InputtingBoolReferenceAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isBool"];
    DummyReferenceAttributeDataConverter<bool> boolValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(boolValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isBoolFunction_InputtingNonBoolValueAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isBool"];
    DummyValueAttributeDataConverter<int> nonBoolValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonBoolValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isBoolFunction_InputtingNonBoolReferenceAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isBool"];
    DummyReferenceAttributeDataConverter<int> nonBoolValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonBoolValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

#pragma endregion

#pragma region As Bool Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asBoolFunction_InputtingBoolValueAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asBool"];
    DummyValueAttributeDataConverter<bool> boolValueAttribute(true);
    auto result = function(static_cast<Celeste::XML::Attribute&>(boolValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());

    DummyValueAttributeDataConverter<bool> boolValueAttribute2(false);
    result = function(static_cast<Celeste::XML::Attribute&>(boolValueAttribute2.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asBoolFunction_InputtingBoolReferenceAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asBool"];
    DummyReferenceAttributeDataConverter<bool> boolValueAttribute(true);
    auto result = function(static_cast<Celeste::XML::Attribute&>(boolValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());

    DummyReferenceAttributeDataConverter<bool> boolValueAttribute2(false);
    result = function(static_cast<Celeste::XML::Attribute&>(boolValueAttribute2.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

#pragma endregion

#pragma region Is Float Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isFloatFunction_InputtingFloatValueAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isFloat"];
    DummyValueAttributeDataConverter<float> floatValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(floatValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isFloatFunction_InputtingFloatReferenceAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isFloat"];
    DummyReferenceAttributeDataConverter<float> floatValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(floatValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isFloatFunction_InputtingNonFloatValueAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isFloat"];
    DummyValueAttributeDataConverter<int> nonFloatValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonFloatValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isFloatFunction_InputtingNonFloatReferenceAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isFloat"];
    DummyReferenceAttributeDataConverter<int> nonFloatValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonFloatValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

#pragma endregion

#pragma region As Float Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asFloatFunction_InputtingFloatValueAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asFloat"];
    DummyValueAttributeDataConverter<float> floatValueAttribute(5.12f);
    auto result = function(static_cast<Celeste::XML::Attribute&>(floatValueAttribute.m_attribute));

    Assert::AreEqual(5.12f, result.get<float>());

    DummyValueAttributeDataConverter<float> floatValueAttribute2(-66);
    result = function(static_cast<Celeste::XML::Attribute&>(floatValueAttribute2.m_attribute));

    Assert::AreEqual(-66.0f, result.get<float>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asFloatFunction_InputtingFloatReferenceAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asFloat"];
    DummyReferenceAttributeDataConverter<float> floatValueAttribute(5.12f);
    auto result = function(static_cast<Celeste::XML::Attribute&>(floatValueAttribute.m_attribute));

    Assert::AreEqual(5.12f, result.get<float>());

    DummyReferenceAttributeDataConverter<float> floatValueAttribute2(-66);
    result = function(static_cast<Celeste::XML::Attribute&>(floatValueAttribute2.m_attribute));

    Assert::AreEqual(-66.0f, result.get<float>());
  }

#pragma endregion

#pragma region Is String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isStringFunction_InputtingStringValueAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isString"];
    DummyValueAttributeDataConverter<std::string> stringValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(stringValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isStringFunction_InputtingStringReferenceAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isString"];
    DummyReferenceAttributeDataConverter<std::string> stringValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(stringValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isStringFunction_InputtingNonStringValueAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isString"];
    DummyValueAttributeDataConverter<int> nonStringValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonStringValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isStringFunction_InputtingNonStringReferenceAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isString"];
    DummyReferenceAttributeDataConverter<int> nonStringValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonStringValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

#pragma endregion

#pragma region As String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asStringFunction_InputtingStringValueAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asString"];
    DummyValueAttributeDataConverter<std::string> stringValueAttribute("Test");
    auto result = function(static_cast<Celeste::XML::Attribute&>(stringValueAttribute.m_attribute));

    Assert::AreEqual("Test", result.get<std::string>().c_str());

    DummyValueAttributeDataConverter<std::string> stringValueAttribute2("Test Value 2");
    result = function(static_cast<Celeste::XML::Attribute&>(stringValueAttribute2.m_attribute));

    Assert::AreEqual("Test Value 2", result.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asStringFunction_InputtingStringReferenceAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asString"];
    DummyReferenceAttributeDataConverter<std::string> stringValueAttribute("Test");
    auto result = function(static_cast<Celeste::XML::Attribute&>(stringValueAttribute.m_attribute));

    Assert::AreEqual("Test", result.get<std::string>().c_str());

    DummyReferenceAttributeDataConverter<std::string> stringValueAttribute2("Test Value 2");
    result = function(static_cast<Celeste::XML::Attribute&>(stringValueAttribute2.m_attribute));

    Assert::AreEqual("Test Value 2", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Is Vec2 Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isVec2Function_InputtingVec2ValueAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isVec2"];
    DummyValueAttributeDataConverter<glm::vec2> vec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isVec2Function_InputtingVec2ReferenceAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isVec2"];
    DummyReferenceAttributeDataConverter<glm::vec2> vec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isVec2Function_InputtingNonVec2ValueAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isVec2"];
    DummyValueAttributeDataConverter<int> nonVec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonVec2ValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isVec2Function_InputtingNonVec2ReferenceAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isVec2"];
    DummyReferenceAttributeDataConverter<int> nonVec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonVec2ValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

#pragma endregion

#pragma region As Vec2 Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asVec2Function_InputtingVec2ValueAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asVec2"];
    DummyValueAttributeDataConverter<glm::vec2> vec2ValueAttribute(glm::vec2(1, -5));
    auto result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute.m_attribute));

    Assert::AreEqual(glm::vec2(1, -5), result.get<glm::vec2>());

    DummyValueAttributeDataConverter<glm::vec2> vec2ValueAttribute2(glm::vec2(10, -66.6f));
    result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute2.m_attribute));

    Assert::AreEqual(glm::vec2(10, -66.6f), result.get<glm::vec2>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asVec2Function_InputtingVec2ReferenceAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asVec2"];
    DummyReferenceAttributeDataConverter<glm::vec2> vec2ValueAttribute(glm::vec2(1, -5));
    auto result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute.m_attribute));

    Assert::AreEqual(glm::vec2(1, -5), result.get<glm::vec2>());

    DummyReferenceAttributeDataConverter<glm::vec2> vec2ValueAttribute2(glm::vec2(10, -66.6f));
    result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute2.m_attribute));

    Assert::AreEqual(glm::vec2(10, -66.6f), result.get<glm::vec2>());
  }

#pragma endregion

#pragma region Is UVec2 Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isUVec2Function_InputtingUVec2ValueAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isUVec2"];
    DummyValueAttributeDataConverter<glm::uvec2> uvec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(uvec2ValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isUVec2Function_InputtingUVec2ReferenceAttribute_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isUVec2"];
    DummyReferenceAttributeDataConverter<glm::uvec2> uvec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(uvec2ValueAttribute.m_attribute));

    Assert::IsTrue(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isUVec2Function_InputtingNonUVec2ValueAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isUVec2"];
    DummyValueAttributeDataConverter<int> nonUVec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonUVec2ValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_isUVec2Function_InputtingNonUVec2ReferenceAttribute_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["isUVec2"];
    DummyReferenceAttributeDataConverter<int> nonUVec2ValueAttribute;
    auto result = function(static_cast<Celeste::XML::Attribute&>(nonUVec2ValueAttribute.m_attribute));

    Assert::IsFalse(result.get<bool>());
  }

#pragma endregion

#pragma region As UVec2 Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asUVec2Function_InputtingUVec2ValueAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asUVec2"];
    DummyValueAttributeDataConverter<glm::uvec2> uvec2ValueAttribute(glm::uvec2(1, 5));
    auto result = function(static_cast<Celeste::XML::Attribute&>(uvec2ValueAttribute.m_attribute));

    Assert::AreEqual(glm::uvec2(1, 5), result.get<glm::uvec2>());

    DummyValueAttributeDataConverter<glm::uvec2> vec2ValueAttribute2(glm::uvec2(10, 66));
    result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute2.m_attribute));

    Assert::AreEqual(glm::uvec2(10, 66), result.get<glm::uvec2>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AttributeScriptCommands_asUVec2Function_InputtingUVec2ReferenceAttribute_ReturnsAttributeValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::XML::AttributeScriptCommands::initialize(state);

    sol::function function = state.globals()["Attribute"]["asUVec2"];
    DummyReferenceAttributeDataConverter<glm::uvec2> uvec2ValueAttribute(glm::uvec2(1, 5));
    auto result = function(static_cast<Celeste::XML::Attribute&>(uvec2ValueAttribute.m_attribute));

    Assert::AreEqual(glm::uvec2(1, 5), result.get<glm::uvec2>());

    DummyReferenceAttributeDataConverter<glm::uvec2> vec2ValueAttribute2(glm::uvec2(10, 66));
    result = function(static_cast<Celeste::XML::Attribute&>(vec2ValueAttribute2.m_attribute));

    Assert::AreEqual(glm::uvec2(10, 66), result.get<glm::uvec2>());
  }

#pragma endregion

  };
}