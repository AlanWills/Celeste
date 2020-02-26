#pragma once

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TestUtils
{
  class FileAssert
  {
    public:
      /// Checks that the file with the inputted filepath exists
      static void FileExists(const std::string& fullFilePath);

      /// Checks that the file with the inputted filepath exists
      static void FileDoesNotExist(const std::string& fullFilePath);

      /// Checks that the contents of the file with the inputted filepath matches the inputted expected string
      static void FileContentsEqual(const std::string& fullFilePath, const std::string& expectedFileContents);

      /// Checks that the contents of the file with the inputted filepath does not match the inputted expected string
      static void FileContentsNotEqual(const std::string& fullFilePath, const std::string& notExpectedFileContents);

    private:
      // Set up the appropriate constructors and assignment operators so that an instance of this class is impossible to create
      FileAssert() = default;
      FileAssert(const FileAssert& testUtils) = delete;
      FileAssert& operator=(const FileAssert&) = delete;

      static std::string getFileContents(const std::string& fullFilePath);
  };
}