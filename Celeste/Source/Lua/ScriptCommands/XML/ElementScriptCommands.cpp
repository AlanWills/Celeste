#include "Lua/ScriptCommands/XML/ElementScriptCommands.h"
#include "Lua/LuaState.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::XML::Element> : std::false_type {};
}

namespace Celeste::Lua::XML::ElementScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Lua::LuaState::instance();

    using Element = Celeste::XML::Element;

    state.new_usertype<Element>(
      "Element",
      sol::base_classes, sol::bases<Celeste::XML::XMLObject>());
  }
}