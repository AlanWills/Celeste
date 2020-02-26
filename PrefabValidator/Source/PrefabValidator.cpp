#include "Resources/ResourceManager.h"
#include "Resources/ResourceUtils.h"
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
  directory.findFiles(files, ".prefab", true);

  std::cout << std::to_string(files.size()) << " prefab files found" << std::endl;

  Game game;
  ResourceManager* resourceManager = game.getResourceManager();
  resourceManager->setResourcesDirectory(pathToResourcesDirectory);

  int errorFileCount = 0;
  for (const File& file : files)
  {
    Handle<Prefab> prefab = resourceManager->load<Prefab>(file.getFilePath());
    if (prefab.is_null())
    {
      ++errorFileCount;
      std::cout << file.getFilePath().c_str() << ": Failed" << std::endl;
    }

    resourceManager->unload<Prefab>(file.getFilePath());
  }

  return errorFileCount;
}