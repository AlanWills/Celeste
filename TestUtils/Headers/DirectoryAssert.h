#pragma once

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TestUtils
{
  class DirectoryAssert
  {
    public:
      /// Checks that the directory with the inputted directory path exists
      static void DirectoryExists(const std::string& fullDirectoryPath);

      /// Checks that the directory with the inputted directory path exists
      static void DirectoryDoesNotExist(const std::string& fullDirectoryPath);

    private:
      // Set up the appropriate constructors and assignment operators so that an instance of this class is impossible to create
      DirectoryAssert() = default;
      DirectoryAssert(const DirectoryAssert& testUtils) = delete;
      DirectoryAssert& operator=(const DirectoryAssert&) = delete;
  };
}