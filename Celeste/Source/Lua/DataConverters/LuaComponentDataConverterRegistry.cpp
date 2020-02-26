#include "Lua/DataConverters/LuaComponentDataConverterRegistry.h"


namespace Celeste
{
  namespace Lua
  {
    //------------------------------------------------------------------------------------------------
    LuaComponentDataConverterRegistry::LuaComponentDataConverterRegistry() :
      m_converters()
    {
    }

    //------------------------------------------------------------------------------------------------
    LuaComponentDataConverterRegistry::~LuaComponentDataConverterRegistry()
    {
      for (const auto& pair : m_converters)
      {
        delete pair.second;
      }
    }

    //------------------------------------------------------------------------------------------------
    LuaComponentDataConverterRegistry& LuaComponentDataConverterRegistry::getInstance()
    {
      static LuaComponentDataConverterRegistry instance;
      return instance;
    }

    //------------------------------------------------------------------------------------------------
    void LuaComponentDataConverterRegistry::registerConverter(const std::string& componentName, sol::table converterTable)
    {
      if (hasConverter(componentName))
      {
        ASSERT_FAIL();
        return;
      }

      // Process converter and add it to our registry
      if (!converterTable.valid())
      {
        ASSERT_FAIL();
        return;
      }

      getInstance().m_converters.emplace(componentName, new LuaComponentDataConverter{ converterTable, componentName });
    }

    //------------------------------------------------------------------------------------------------
    void LuaComponentDataConverterRegistry::deregisterConverter(const std::string& componentName)
    {
      if (hasConverter(componentName))
      {
        getInstance().m_converters[componentName]->cleanupData();
        delete getInstance().m_converters[componentName];
        getInstance().m_converters.erase(componentName);
      }
    }

    //------------------------------------------------------------------------------------------------
    void LuaComponentDataConverterRegistry::getConverter(
      const std::string& componentName, 
      std::unique_ptr<ComponentDataConverter>& outputConverter)
    {
      if (hasConverter(componentName))
      {
        getInstance().m_converters[componentName]->instantiate(outputConverter);
      }
    }

    //------------------------------------------------------------------------------------------------
    void LuaComponentDataConverterRegistry::clear()
    {
      for (const auto& pair : getInstance().m_converters)
      {
        delete pair.second;
      }

      getInstance().m_converters.clear();
    }
  }
}