#include "Lua/ScriptCommands/XML/ElementScriptCommands.h"
#include "Lua/LuaState.h"


namespace Celeste
{
  namespace Lua
  {
    namespace XML
    {
      namespace ElementScriptCommands
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
    }
  }
}