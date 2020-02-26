#pragma once

#include "CelesteDllExport.h"
#include "tinyxml2.h"
#include <Memory/ObserverPtr.h>
#include "Debug/Assert.h"

#include <functional>
#include <unordered_map>
#include <memory>


namespace Celeste
{
  class Component;
  class GameObject;
  class ComponentDataConverter;

  class CelesteDllExport ComponentDataConverterRegistry
  {
    public:
      ComponentDataConverterRegistry() = delete;
      ComponentDataConverterRegistry(const ComponentDataConverterRegistry&) = delete;
      ComponentDataConverterRegistry& operator=(const ComponentDataConverterRegistry&) = delete;

      template <typename T>
      static bool addConverter();

      template <typename T>
      static void removeConverter() { removeConverter(T::ComponentType::type_name()); }

      template <typename T>
      static bool hasCustomConverter() { return hasCustomConverter(T::ComponentType::type_name()); }

      static void removeConverter(const std::string& componentName);

      static bool hasCustomConverter(const std::string& componentName) { return !getConverters().empty() && getConverters().find(componentName) != getConverters().end();  }

      /// Obtain a converter for the inputted component
      /// If a custom converter has been registered, the outputConverter is set to an instance of that converter
      /// Otherwise the outputConverter is set to an instance of the default component converter
      static void getConverter(const std::string& componentName, std::unique_ptr<ComponentDataConverter>& outputConverter);

      static observer_ptr<Component> convert(const tinyxml2::XMLElement* componentElement, GameObject& gameObject);

    private:
      using ConverterMap = std::unordered_map<std::string, ComponentDataConverter*>;

      static ConverterMap& getConverters();
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool ComponentDataConverterRegistry::addConverter()
  {
    const std::string& name = T::ComponentType::type_name();

    if (!hasCustomConverter(name))
    {
      getConverters().emplace(name, new T());
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}