#include "TestGame.h"
#include "Lua/LuaState.h"

#include "ScriptCommands/Celeste/CelesteScriptCommands.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  TestGame::TestGame()
  {
    Path pathToResources = Path(Directory::getExecutingAppDirectory(), "TestGame", "Resources");
    getResourceManager().setResourcesDirectory(pathToResources);
  }

  //------------------------------------------------------------------------------------------------
  void TestGame::onInitialize()
  {
    Inherited::onInitialize();

    sol::state& state = Celeste::Lua::LuaState::instance();

    Celeste::Lua::CelesteScriptCommands::initialize(state);
  }

  //------------------------------------------------------------------------------------------------
  void TestGame::onInitializeDolce(Dolce::IDolce& /*dolce*/)
  {
  }
}