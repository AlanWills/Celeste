#include "DirectoryAssert.h"

#include <dirent.h>


namespace TestUtils
{
  //------------------------------------------------------------------------------------------------
  void DirectoryAssert::DirectoryExists(const std::string& fullDirectoryPath)
  {
    struct stat buf;
    Assert::IsTrue((stat(fullDirectoryPath.c_str(), &buf) == 0) && S_ISDIR(buf.st_mode));
  }

  //------------------------------------------------------------------------------------------------
  void DirectoryAssert::DirectoryDoesNotExist(const std::string& fullDirectoryPath)
  {
    struct stat buf;
    Assert::IsFalse((stat(fullDirectoryPath.c_str(), &buf) == 0) && S_ISDIR(buf.st_mode));
  }
}