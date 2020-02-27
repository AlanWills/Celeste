#include "Game/TestCelesteRuntimeGame.h"
#include "Lua/ScriptCommands/Testing/TestDiscovererScriptCommands.h"


namespace TestCelesteRuntime
{
  //------------------------------------------------------------------------------------------------
  void TestCelesteRuntimeGame::onInitialize()
  {
    Inherited::onInitialize();

    TestCelesteRuntime::Lua::Testing::TestDiscovererScriptCommands::initialize();
  }
}