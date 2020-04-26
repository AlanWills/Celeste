#include "ScriptCommands/DataConverters/Objects/ComponentDataConverterScriptCommands.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "Lua/LuaState.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::ComponentDataConverter> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::Component> : std::false_type {};
}

namespace Celeste::Lua::Objects::ComponentDataConverterScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setValues(ComponentDataConverter& converter, sol::object component)
    {
      if (component == sol::nil)
      {
        ASSERT_FAIL();
        return;
      }

      converter.setValues(component.as<Component&>());
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<ComponentDataConverter>(
      "ComponentDataConverter",
      sol::base_classes, sol::bases<EntityDataConverter<Component>, ObjectDataConverter<Component>, DataConverter>(),
      "setValues", &Internals::setValues);
  }
}