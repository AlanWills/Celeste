#include "FileSystem/Directory.h"
#include "Lua/LuaState.h"
#include "Debug/Assert.h"
#include "Debug/Asserting/NullAsserter.h"

#include <iostream>

using namespace Celeste;

int main(int argc, char** argv)
{
  Assertion::setAsserter(new NullAsserter());

  Path pathToResourcesDirectory(argc > 1 ? argv[1] : Path(Directory::getExecutingAppDirectory(), "Resources").c_str());
  Directory directory(pathToResourcesDirectory);

  std::cout << "Using resource directory " << pathToResourcesDirectory.c_str() << std::endl;

  std::vector<File> files;
  directory.findFiles(files, ".lua", true);

  std::cout << std::to_string(files.size()) << " lua files found" << std::endl;

  int errorFileCount = 0;

  for (const File& file : files)
  {
    try
    {
      sol::load_result loadResult = Lua::LuaState::instance().load_file(file.getFilePath().as_string(), sol::load_mode::text);
      if (!loadResult.valid())
      {
        ++errorFileCount;
        std::cout << file.getFilePath().c_str() << ": Failed" << std::endl;
      }
    }
    catch (const sol::error& e)
    {
      ++errorFileCount;
      std::cout << file.getFilePath().c_str() << ": Failed" << std::endl;
      std::cout << e.what();
    }
  }

  return errorFileCount;
}