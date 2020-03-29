#include "Lua/ScriptCommands/XML/XMLObjectScriptCommands.h"
#include "Lua/LuaState.h"

#include "XML/XMLObject.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::XML::XMLObject> : std::false_type {};
}

namespace Celeste::Lua::XML::XMLObjectScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Lua::LuaState::instance();

    using XMLObject = Celeste::XML::XMLObject;

    state.new_usertype<XMLObject>(
      "XMLObject",
      "isRequired", &XMLObject::isRequired);
  }
}