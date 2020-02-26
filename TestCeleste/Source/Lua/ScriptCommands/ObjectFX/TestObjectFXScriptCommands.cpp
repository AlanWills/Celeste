#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/ObjectFX/ObjectFXScriptCommands.h"
#include "Lua/LuaState.h"

using namespace Celeste::Lua;


namespace TestCeleste
{
  namespace Lua
  {
    namespace ObjectFXScriptCommands
    {
      CELESTE_TEST_CLASS(TestObjectFXScriptCommands)

#pragma region Initialize Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ObjectFXScriptCommands_Initialize_InitializesLimitedLifeTimeScriptCommands)
      {
        Assert::IsFalse(LuaState::instance().globals()["LimitedLifeTime"].valid());

        Celeste::Lua::ObjectFXScriptCommands::initialize();

        Assert::IsTrue(LuaState::instance().globals()["LimitedLifeTime"].valid());
      }

#pragma endregion

      };
    }
  }
}