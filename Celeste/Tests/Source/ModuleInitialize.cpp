#include "UtilityHeaders/UnitTestHeaders.h"

#include "Game/Game.h"
#include "Debug/Assert.h"
#include "Debug/Asserting/NullAsserter.h"
#include "OpenGL/GL.h"
#include "Lua/LuaState.h"
#include "TestResources/TestResources.h"


namespace TestCeleste
{
  std::unique_ptr<Game> game(nullptr);

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestCeleste_Initialize)
  {
    // Issues with unique_ptrs over dll boundaries so have to do this in the test project
    Assertion::setAsserter(new NullAsserter());

    CelesteTestResources::TestResources::setResourcesDirectory(Path(Directory::getExecutingAppDirectory(), "Resources"));
    CelesteTestResources::TestResources::initialize();

    game = std::make_unique<Game>();
    game->getResourceManager().setResourcesDirectory(TestResources::getResourcesDirectory());
    
    Lua::LuaState::appendToLuaPackagePath(Path(Resources::getResourcesDirectory(), "Scripts", "?.lua;"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_CLEANUP(TestCeleste_Cleanup)
  {
    Game::exit();
    GL::terminate();

    game.reset();
  }
}