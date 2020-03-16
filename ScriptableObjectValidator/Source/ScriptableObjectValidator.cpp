#include "Objects/ScriptableObject.h"
#include "Registries/ScriptableObjectRegistry.h"
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
  directory.findFiles(files, ".asset", true);

  std::cout << std::to_string(files.size()) << " scriptable object files found" << std::endl;

  Game game(1, 1, OpenGLWindow::WindowMode::kWindowed, "");
  game.getAudioManager().setMasterVolume(0);
  
  ResourceManager& resourceManager = game.getResourceManager();
  resourceManager.setResourcesDirectory(pathToResourcesDirectory);

  int errorFileCount = 0;
  for (const File& file : files)
  {
    observer_ptr<Data> data = resourceManager.load<Data>(file.getFilePath());
    if (data == nullptr)
    {
      ++errorFileCount;
      std::cout << file.getFilePath().c_str() << ": Loading Failed" << std::endl;
    }
    else
    {
      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject(data->getDocumentRoot()->Name(), "");
      if (scriptableObject == nullptr)
      {
        ++errorFileCount;
        std::cout << file.getFilePath().c_str() << ": Creating Failed" << std::endl;
      }
    }

    resourceManager.unload<Data>(file.getFilePath());
  }

  return errorFileCount;
}