#pragma once

#include "UtilityHeaders/LuaHeaders.h"
#include "Lua/DataConverters/LuaComponentDataConverter.h"
#include "CelesteDllExport.h"

#include <unordered_map>


namespace Celeste
{
  namespace Lua
  {
    class LuaComponentDataConverterRegistry
    {
      public:
        CelesteDllExport static size_t registeredConvertersSize() { return getInstance().m_converters.size(); }
        CelesteDllExport static void registerConverter(const std::string& componentName, sol::table converterTable);
        CelesteDllExport static void deregisterConverter(const std::string& componentName);
        CelesteDllExport static bool hasConverter(const std::string& componentName) { return getInstance().m_converters.find(componentName) != getInstance().m_converters.end(); }

        /// Obtain a converter for the inputted component
        /// If a custom converter has been registered, the outputConverter is set to an instance of that converter
        /// Otherwise the outputConverter is set to an instance of the default component converter
        CelesteDllExport static void getConverter(const std::string& componentName, std::unique_ptr<ComponentDataConverter>& outputConverter);

        CelesteDllExport static void clear();

      private:
        using LuaComponentDataConverters = std::unordered_map<std::string, LuaComponentDataConverter*>;

        static LuaComponentDataConverterRegistry& getInstance();

        LuaComponentDataConverterRegistry();
        ~LuaComponentDataConverterRegistry();
        LuaComponentDataConverterRegistry(const LuaComponentDataConverterRegistry&) = delete;
        LuaComponentDataConverterRegistry& operator=(const LuaComponentDataConverterRegistry&) = delete;

        LuaComponentDataConverters m_converters;
    };
  }
}