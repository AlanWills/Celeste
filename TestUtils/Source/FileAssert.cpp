#include "FileAssert.h"

#include <fstream>


namespace TestUtils
{
  //------------------------------------------------------------------------------------------------
  void FileAssert::FileExists(const std::string& fullFilePath)
  {
    std::fstream file(fullFilePath);
    Assert::IsTrue(file.good());
  }

  //------------------------------------------------------------------------------------------------
  void FileAssert::FileDoesNotExist(const std::string& fullFilePath)
  {
    std::fstream file(fullFilePath);
    Assert::IsFalse(file.good());
  }

  //------------------------------------------------------------------------------------------------
  void FileAssert::FileContentsEqual(const std::string& fullFilePath, const std::string& expectedFileContents)
  {
    Assert::AreEqual(expectedFileContents, getFileContents(fullFilePath));
  }

  //------------------------------------------------------------------------------------------------
  void FileAssert::FileContentsNotEqual(const std::string& fullFilePath, const std::string& notExpectedFileContents)
  {
    Assert::AreNotEqual(notExpectedFileContents, getFileContents(fullFilePath));
  }

  //------------------------------------------------------------------------------------------------
  std::string FileAssert::getFileContents(const std::string& fullFilePath)
  {
    FileExists(fullFilePath);

    std::ifstream file(fullFilePath);
    std::string actual, buffer;

    while (std::getline(file, buffer))
    {
      actual.append(buffer);
      actual.append("\n");
    }

    // Remove the final new line if it exists
    // This is a bit strange I know but there's a reason
    // When writing to a file, it appears in the FILE when inspecting in notepad that there is a newline at the end
    // However, std::getline doesn't pick it up, hence why we must remove it
    if ((actual.length() > 0) && (actual.back() == '\n'))
    {
      actual.pop_back();
    }

    return actual;
  }
}