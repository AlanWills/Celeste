#include "Lua/ScriptCommands/DataConverters/Objects/ComponentDataConverterScriptCommands.h"
#include "Lua/LuaState.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"

#include "DataConverters/Objects/ComponentDataConverter.h"


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
  void initialize()
  {
    sol::state& state = LuaState::instance();

    state.new_usertype<ComponentDataConverter>(
      "ComponentDataConverter",
      sol::base_classes, sol::bases<EntityDataConverter<Component>, ObjectDataConverter<Component>, DataConverter>(),
      "setValues", &Internals::setValues);
  }
}