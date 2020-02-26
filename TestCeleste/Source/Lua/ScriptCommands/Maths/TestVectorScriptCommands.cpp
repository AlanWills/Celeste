#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Maths/VectorScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste
{
  namespace Lua
  {
    namespace Maths
    {
      namespace VectorScriptCommands
      {
        CELESTE_TEST_CLASS(TestVectorScriptCommands)

#pragma region Initialize Tests

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(VectorScriptCommands_Initialize_Adds_uvec2UserType_ToGlobalTable)
        {
          sol::state& state = LuaState::instance();

          Assert::IsFalse(state.globals()["uvec2"].valid());

          Celeste::Lua::Maths::VectorScriptCommands::initialize();

          Assert::IsTrue(state.globals()["uvec2"].valid());
        }

		//------------------------------------------------------------------------------------------------
		TEST_METHOD(VectorScriptCommands_Initialize_Adds_vec2UserType_ToGlobalTable)
		{
			sol::state& state = LuaState::instance();

			Assert::IsFalse(state.globals()["vec2"].valid());

			Celeste::Lua::Maths::VectorScriptCommands::initialize();

			Assert::IsTrue(state.globals()["vec2"].valid());
		}

#pragma endregion

        };
      }
    }
  }
}