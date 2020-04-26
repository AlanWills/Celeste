#include "ScriptCommands/DataConverters/LuaComponentDataConverterScriptCommands.h"
#include "Lua/DataConverters/LuaComponentDataConverterRegistry.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "sol/sol.hpp"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Lua::LuaComponentDataConverter> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::ComponentDataConverter> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::Component> : std::false_type {};
}

namespace Celeste::Lua::LuaComponentDataConverterScriptCommands
{
  namespace Internals
  {
    std::unique_ptr<ComponentDataConverter> getConverter(const std::string& componentName)
    {
      std::unique_ptr<ComponentDataConverter> converter(nullptr);
      LuaComponentDataConverterRegistry::getConverter(componentName, converter);

      return converter;
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<LuaComponentDataConverter>(
      "LuaComponentDataConverter",
      sol::base_classes, sol::bases<ComponentDataConverter, EntityDataConverter<Component>, ObjectDataConverter<Component>, DataConverter>(),
      "register", &Lua::LuaComponentDataConverterRegistry::registerConverter,
      "hasConverter", &Lua::LuaComponentDataConverterRegistry::hasConverter,
      "getConverter", &Internals::getConverter);
  }
}