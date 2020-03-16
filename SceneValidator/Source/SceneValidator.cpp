#include "Resources/ResourceManager.h"
#include "Resources/ResourceUtils.h"
#include "Scene/SceneLoader.h"
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
  directory.findFiles(files, ".scene", true);

  std::cout << std::to_string(files.size()) << " scene files found" << std::endl;

  Game game(1, 1, OpenGLWindow::WindowMode::kWindowed, "");
  game.getAudioManager().setMasterVolume(0);
  
  ResourceManager& resourceManager = game.getResourceManager();
  resourceManager.setResourcesDirectory(pathToResourcesDirectory);

  int errorFileCount = 0;
  for (const File& file : files)
  {
    std::tuple<bool, std::vector<GameObject*>> result = SceneLoader::load(file.getFilePath());

    if (!std::get<0>(result))
    {
      ++errorFileCount;
      std::cout << file.getFilePath().c_str() << ": Failed" << std::endl;
    }

    for (auto gameObject : std::get<1>(result))
    {
      delete gameObject;
    }

    resourceManager.unload<Data>(file.getFilePath());
  }

  return errorFileCount;
}