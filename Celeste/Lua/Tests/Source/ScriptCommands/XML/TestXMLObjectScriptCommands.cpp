#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/XML/XMLObjectScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua
{
  namespace Lua
  {
    namespace XML
    {
      namespace XMLObjectScriptCommands
      {
        CELESTE_TEST_CLASS(TestXMLObjectScriptCommands)

#pragma region Initialize Tests

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(XMLObjectScriptCommands_Initialize_AddsXMLObjectUserType_ToGlobalTable)
        {
          sol::state& state = LuaState::instance();

          Assert::IsFalse(state.globals()["XMLObject"].valid());

          Celeste::Lua::XML::XMLObjectScriptCommands::initialize(state);

          Assert::IsTrue(state.globals()["XMLObject"].valid());
        }

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(XMLObjectScriptCommands_Initialize_Adds_isRequired_ToXMLObjectTable)
        {
          sol::state& state = LuaState::instance();

          Assert::IsFalse(state.globals()["XMLObject"]["isRequired"].valid());

          Celeste::Lua::XML::XMLObjectScriptCommands::initialize(state);

          Assert::IsTrue(state.globals()["XMLObject"]["isRequired"].valid());
        }

#pragma endregion

      };
    }
  }
}
}