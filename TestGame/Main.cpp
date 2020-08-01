#include "TestGame.h"
#include "Platform/Platform.h"
#include "Log/Log.h"

// Disables console window
#if WINDOWS && !defined(__CYGWIN__)
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

// The MAIN function, from here we start the application and run the game loop
int main()
{ 
  Celeste::Path logPath(Celeste::Directory::getExecutingAppDirectory(), "Logs", "Log.txt");
  Celeste::Log::addFileSink(logPath.as_string());

  Celeste::TestGame game;
  game.run();

  return 0;
}