#include "Lua/ScriptCommands/DataConverters/LuaComponentDataConverterScriptCommands.h"
#include "Lua/DataConverters/LuaComponentDataConverterRegistry.h"
#include "Lua/LuaState.h"

#include "DataConverters/Objects/ComponentDataConverter.h"


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
  void initialize()
  {
    sol::state& state = LuaState::instance();

    state.new_usertype<LuaComponentDataConverter>(
      "LuaComponentDataConverter",
      sol::base_classes, sol::bases<ComponentDataConverter, EntityDataConverter<Component>, ObjectDataConverter<Component>, DataConverter>(),
      "register", &Lua::LuaComponentDataConverterRegistry::registerConverter,
      "hasConverter", &Lua::LuaComponentDataConverterRegistry::hasConverter,
      "getConverter", &Internals::getConverter);
  }
}