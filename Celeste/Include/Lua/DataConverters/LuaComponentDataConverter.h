#pragma once

#include "CelesteDllExport.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "sol/sol.hpp"


namespace Celeste::Lua
{
  class LuaComponentDataConverter : public ComponentDataConverter
  {
    public:
      CelesteDllExport LuaComponentDataConverter(const sol::table& converterManifest, const std::string& elementName);
      CelesteDllExport LuaComponentDataConverter(const LuaComponentDataConverter&);
      CelesteDllExport LuaComponentDataConverter(LuaComponentDataConverter&& rhs);
      CelesteDllExport LuaComponentDataConverter& operator=(const LuaComponentDataConverter&);

      void instantiate(std::unique_ptr<ComponentDataConverter>& output) override
      {
        output.reset(new LuaComponentDataConverter(*this));
      }

    protected:
      bool doConvertFromXML(const XMLElement* objectElement) override;
      void doSetValues(Component& component) const override;

    private:
      using Inherited = ComponentDataConverter;

      void convertAttributes(const sol::table& converterManifest);
      void convertAttribute(const std::pair<sol::object, sol::object>& luaAttribute);

      void createAttributeFromLuaData(
        const std::string& name,
        const std::string& typeName,
        bool isReference,
        DeserializationRequirement isRequired,
        const sol::optional<std::string>& luaDefaultValue);

      template <typename T>
      void createAttributeFromLuaData(
        const std::string& name,
        bool isReference,
        DeserializationRequirement isRequired,
        const sol::optional<std::string>& luaDefaultValue);

      void convertElements(const sol::table& converterManifest);
      void convertElement(const std::pair<sol::object, sol::object>& luaElement);

      void createElementFromLuaData(
        const std::string& name,
        const std::string& typeName,
        bool isReference,
        DeserializationRequirement isRequired,
        const sol::optional<std::string>& luaDefaultValue);

      template <typename T>
      void createElementFromLuaData(
        const std::string& name,
        bool isReference,
        DeserializationRequirement isRequired,
        const sol::optional<std::string>& luaDefaultValue);

      template <typename T>
      void getDefaultValue(const sol::optional<std::string>& luaDefaultValue, T& defaultValue);

      void convertCallbacks(const sol::table& converterManifest);

      sol::protected_function m_doConvertFromXML;
      sol::protected_function m_doSetValues;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void LuaComponentDataConverter::createAttributeFromLuaData(
    const std::string& name,
    bool isReference,
    DeserializationRequirement isRequired,
    const sol::optional<std::string>& luaDefaultValue)
  {
    T defaultValue = T();
    getDefaultValue(luaDefaultValue, defaultValue);

    if (isReference)
    {
      createReferenceAttribute<T>(name, defaultValue, isRequired);
    }
    else
    {
      createValueAttribute<T>(name, defaultValue, isRequired);
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void LuaComponentDataConverter::createElementFromLuaData(
    const std::string& name,
    bool isReference,
    DeserializationRequirement isRequired,
    const sol::optional<std::string>& luaDefaultValue)
  {
    T defaultValue = T();
    getDefaultValue<T>(luaDefaultValue, defaultValue);

    if (isReference)
    {
      createReferenceElement<T>(name, defaultValue, isRequired);
    }
    else
    {
      createValueElement<T>(name, defaultValue, isRequired);
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void LuaComponentDataConverter::getDefaultValue(
    const sol::optional<std::string>& luaDefaultValue,
    T& defaultValue)
  {
    if (luaDefaultValue != sol::nullopt)
    {
      deserialize<T>(luaDefaultValue.value(), defaultValue);
    }
  }
}