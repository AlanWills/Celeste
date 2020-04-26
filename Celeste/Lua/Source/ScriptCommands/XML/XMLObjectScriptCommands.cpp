#include "ScriptCommands/XML/XMLObjectScriptCommands.h"
#include "XML/XMLObject.h"
#include "sol/sol.hpp"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::XML::XMLObject> : std::false_type {};
}

namespace Celeste::Lua::XML::XMLObjectScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using XMLObject = Celeste::XML::XMLObject;

    state.new_usertype<XMLObject>(
      "XMLObject",
      "isRequired", &XMLObject::isRequired);
  }
}