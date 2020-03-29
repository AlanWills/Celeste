#include "Lua/DataConverters/LuaComponentDataConverter.h"
#include "Deserialization/MathsDeserializers.h"
#include "Bindings/MathsDataBindingGenerators.h"
#include "Objects/Component.h"

#include "Lua/LuaState.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Lua::LuaComponentDataConverter> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::Component> : std::false_type {};
}

namespace Celeste::Lua
{
  //------------------------------------------------------------------------------------------------
  LuaComponentDataConverter::LuaComponentDataConverter(const sol::table& converterManifest, const std::string& elementName) :
    Inherited(elementName)
  {
    if (converterManifest.valid())
    {
      convertAttributes(converterManifest);
      convertElements(converterManifest);
      convertCallbacks(converterManifest);
    }
  }

  //------------------------------------------------------------------------------------------------
  LuaComponentDataConverter::LuaComponentDataConverter(const LuaComponentDataConverter& rhs) :
    Inherited(rhs),
    m_doConvertFromXML(rhs.m_doConvertFromXML),
    m_doSetValues(rhs.m_doSetValues)
  {
  }

  //------------------------------------------------------------------------------------------------
  LuaComponentDataConverter& LuaComponentDataConverter::operator=(const LuaComponentDataConverter& rhs)
  {
    // Self assignment guard
    if (this == &rhs)
    {
      return *this;
    }

    Inherited::operator=(rhs);
    m_doConvertFromXML = rhs.m_doConvertFromXML;
    m_doSetValues = rhs.m_doSetValues;

    return *this;
  }

  //------------------------------------------------------------------------------------------------
  LuaComponentDataConverter::LuaComponentDataConverter(LuaComponentDataConverter&& rhs) :
    Inherited(std::move(rhs)),
    m_doConvertFromXML(std::move(rhs.m_doConvertFromXML)),
    m_doSetValues(std::move(rhs.m_doSetValues))
  {
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::convertAttributes(const sol::table& converterManifest)
  {
    // Find the attributes table and add each individual attribute
    const sol::table& attributes = converterManifest.get_or<sol::table>("Attributes", sol::nil);
    if (attributes != sol::nil)
    {
      for (const auto& attribute : attributes)
      {
        convertAttribute(attribute);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::convertAttribute(const std::pair<sol::object, sol::object>& luaAttribute)
  {
    if (!luaAttribute.first.valid() ||
      !luaAttribute.second.valid())
    {
      ASSERT_FAIL();
      return;
    }

    const sol::table& attributeTable = luaAttribute.second.as<sol::table>();
    if (!attributeTable.valid())
    {
      ASSERT_FAIL();
      return;
    }

    const std::string& luaName = attributeTable.get_or<std::string>("Name", "");
    if (luaName.empty())
    {
      ASSERT_FAIL();
      return;
    }

    const std::string& luaType = attributeTable.get_or<std::string>("Type", "");
    if (luaType.empty())
    {
      ASSERT_FAIL();
      return;
    }

    bool isRequired = attributeTable.get_or("Is Required", false);
    bool isReference = attributeTable.get_or("Is Reference", false);

    sol::optional<std::string> luaDefaultValue = attributeTable["Default Value"];

    createAttributeFromLuaData(
      luaName,
      luaType,
      isReference,
      isRequired ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired,
      luaDefaultValue);
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::createAttributeFromLuaData(
    const std::string& name,
    const std::string& typeName,
    bool isReference,
    DeserializationRequirement isRequired,
    const sol::optional<std::string>& luaDefaultValue)
  {
    // Ahhh - refactor this!!!!
    if (typeName == "float")
    {
      createAttributeFromLuaData<float>(name, isReference, isRequired, luaDefaultValue);
    }
    else if (typeName == "bool")
    {
      createAttributeFromLuaData<bool>(name, isReference, isRequired, luaDefaultValue);
    }
    else if (typeName == "string")
    {
      createAttributeFromLuaData<std::string>(name, isReference, isRequired, luaDefaultValue);
    }
    else if (typeName == "vec2")
    {
      createAttributeFromLuaData<glm::vec2>(name, isReference, isRequired, luaDefaultValue);
    }
    else if (typeName == "uvec2")
    {
      createAttributeFromLuaData<glm::uvec2>(name, isReference, isRequired, luaDefaultValue);
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::convertElements(const sol::table& converterManifest)
  {
    // Find the elements table and add each individual element
    sol::table elements = converterManifest.get_or<sol::table>("Elements", sol::nil);
    if (elements != sol::nil)
    {
      for (const auto& element : elements)
      {
        convertElement(element);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::convertElement(const std::pair<sol::object, sol::object>& luaElement)
  {
    if (!luaElement.first.valid() ||
      !luaElement.second.valid())
    {
      ASSERT_FAIL();
      return;
    }

    const sol::table& elementTable = luaElement.second.as<sol::table>();
    if (!elementTable.valid())
    {
      ASSERT_FAIL();
      return;
    }

    const std::string& luaName = elementTable.get_or<std::string>("Name", "");
    if (luaName.empty())
    {
      ASSERT_FAIL();
      return;
    }

    const std::string& luaType = elementTable.get_or<std::string>("Type", "");
    if (luaType.empty())
    {
      ASSERT_FAIL();
      return;
    }

    bool isRequired = elementTable.get_or("Is Required", false);
    bool isReference = elementTable.get_or("Is Reference", false);

    sol::optional<std::string> luaDefaultValue = elementTable["Default Value"];

    createElementFromLuaData(
      luaName,
      luaType,
      isReference,
      isRequired ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired,
      luaDefaultValue);
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::createElementFromLuaData(
    const std::string&,
    const std::string&,
    bool,
    DeserializationRequirement,
    const sol::optional<std::string>&)
  {
    ASSERT_FAIL();
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::convertCallbacks(const sol::table& converterManifest)
  {
    sol::function doConvertFromXMLFunction = converterManifest.get_or<sol::function>("ConvertFromXML", sol::nil);
    if (doConvertFromXMLFunction != sol::nil)
    {
      m_doConvertFromXML = doConvertFromXMLFunction;
    }

    sol::function doSetValuesFunction = converterManifest.get_or<sol::function>("SetValues", sol::nil);
    if (doSetValuesFunction != sol::nil)
    {
      m_doSetValues = doSetValuesFunction;
    }
  }

  //------------------------------------------------------------------------------------------------
  bool LuaComponentDataConverter::doConvertFromXML(const tinyxml2::XMLElement* element)
  {
    bool result = Inherited::doConvertFromXML(element);

    if (m_doConvertFromXML.valid())
    {
      result &= m_doConvertFromXML(element).get<bool>();
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentDataConverter::doSetValues(Component& component) const
  {
    Inherited::doSetValues(component);

    sol::protected_function_result doSetValuesResult;

    if (!LuaState::instance()[getElementName()].valid())
    {
      // Unregistered or incompatible, so just pass the component
      doSetValuesResult = m_doSetValues(this, component);
    }
    else
    {
      auto result = LuaState::instance()["Component"]["as"].get<sol::protected_function>().call(&component, getElementName());
      ASSERT(result.valid());

      // Successful conversion to correct type so we shouldn't need to do casting in lua
      doSetValuesResult = m_doSetValues(this, result.get<sol::object>());
    }

#if _DEBUG
    if (!doSetValuesResult.valid())
    {
      sol::error e = doSetValuesResult;
      LOG(e.what());
      ASSERT_FAIL();
    }
#endif
  }
}