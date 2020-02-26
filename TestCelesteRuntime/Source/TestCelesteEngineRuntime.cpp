#include "Game/TestCelesteRuntimeGame.h"

#include "Resources/TestResources.h"
#include "Debug/Asserting/NullAsserter.h"
#include "Debug/Assert.h"

// Disables console window
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


// The MAIN function, from here we start the application and run the game loop
int main()
{
  // Set up the test resources here
  CelesteTestUtils::TestResources::setResourcesDirectory(Path(Directory::getExecutingAppDirectory(), "Resources"));
  CelesteTestUtils::TestResources::initialize();

  Assertion::setAsserter(new NullAsserter());

  // Don't use Resources::getResourcesDirectory() here because the ResourceManager won't be initialized
  Lua::LuaState::appendToLuaPackagePath(Path(CelesteTestUtils::TestResources::getResourcesDirectory(), "Scripts", "?.lua;"));

  // Don't need to use unique_ptr as it will be deleted through 'current' unique_ptr
  TestCelesteRuntime::TestCelesteRuntimeGame* game = new TestCelesteRuntime::TestCelesteRuntimeGame();
  game->run();

  return 0;
}