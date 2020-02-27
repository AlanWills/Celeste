#include "Resources/ResourceManager.h"
#include "Resources/ResourceUtils.h"
#include "Screens/Loading/ScreenLoader.h"
#include "Game/Game.h"
#include "Debug/Assert.h"
#include "Debug/Asserting/NullAsserter.h"

#include <iostream>

using namespace Celeste;
using namespace Celeste::Resources;

int main(int argc, char** argv)
{
  Assertion::setAsserter(new NullAsserter());
  
  Path pathToResourcesDirectory(argc > 1 ? argv[1] : Path(Directory::getExecutingAppDirectory(), "Resources").c_str());
  Directory directory(pathToResourcesDirectory);

  std::cout << "Using resource directory " << pathToResourcesDirectory.c_str() << std::endl;

  std::vector<File> files;
  directory.findFiles(files, ".screen", true);

  std::cout << std::to_string(files.size()) << " scene files found" << std::endl;

  Game game;
  ResourceManager& resourceManager = game.getResourceManager();
  resourceManager.setResourcesDirectory(pathToResourcesDirectory);

  int errorFileCount = 0;
  for (const File& file : files)
  {
    observer_ptr<Screen> screen = ScreenLoader::load(file.getFilePath());
    if (screen == nullptr)
    {
      ++errorFileCount;
      std::cout << file.getFilePath().c_str() << ": Failed" << std::endl;
    }

    resourceManager.unload<Data>(file.getFilePath());
  }

  return errorFileCount;
}