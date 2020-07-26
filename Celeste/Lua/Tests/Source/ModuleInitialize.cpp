#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Game/Game.h"
#include "Assert/Assert.h"
#include "Assert/NullAsserter.h"
#include "OpenGL/GL.h"
#include "TestResources/TestResources.h"


namespace TestCelesteLua
{
  std::unique_ptr<Game> game(nullptr);

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestCelesteLua_Initialize)
  {
    // Issues with unique_ptrs over dll boundaries so have to do this in the test project
    Assertion::setAsserter(std::make_unique<NullAsserter>());

    CelesteTestResources::TestResources::initialize();
    TempDirectory::setParentDirectory(TestResources::getResourcesDirectory().as_string());

    game = std::make_unique<Game>(50, 50, OpenGLWindow::WindowMode::kWindowed, "Test Celeste Lua");
    game->getResourceManager().setResourcesDirectory(TestResources::getResourcesDirectory());
  }

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_CLEANUP(TestCeleste_Cleanup)
  {
    Game::exit();
    GL::terminate();

    game.reset();
  }
}