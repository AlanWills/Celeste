#include "Lua/ScriptCommands/Testing/TestDiscovererScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Testing/TestDiscoverer.h"


namespace TestCelesteRuntime
{
  namespace Lua
  {
    namespace Testing
    {
      namespace TestDiscovererScriptCommands
      {
        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          Celeste::Lua::registerUserType<TestCelesteRuntime::Testing::TestDiscoverer>(
            "TestDiscoverer",
            "executeTests", &TestCelesteRuntime::Testing::TestDiscoverer::executeTests);
        }
      }
    }
  }
}