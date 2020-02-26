#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "Debug/Assert.h"

#include <fstream>
#include <direct.h>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  File::File(const std::string& filePath) :
    m_filePath(filePath)
  {
  }

  //------------------------------------------------------------------------------------------------
  File::File(const Path& path) :
    m_filePath(path)
  {
  }

  //------------------------------------------------------------------------------------------------
  File::File(const File& file) :
    m_filePath(file.m_filePath)
  {
    // No create here - preserve state of input file
  }

  //------------------------------------------------------------------------------------------------
  File& File::operator=(const File& other)
  {
    // No create here - preserve state of input directory
    m_filePath = other.m_filePath;
    return *this;
  }

  //------------------------------------------------------------------------------------------------
  bool File::exists(const std::string& fullFilePath)
  {
    struct stat buf;
    return (stat(fullFilePath.c_str(), &buf) == 0) && S_ISREG(buf.st_mode);
  }

  //------------------------------------------------------------------------------------------------
  void File::append(const std::string& stringToAppend) const
  {
    if (!exists())
    {
      create();
    }

    std::ofstream file(m_filePath.as_string(), std::ios_base::app);

    // Now append
    file << stringToAppend;;
  }

  //------------------------------------------------------------------------------------------------
  void File::create(bool clearIfAlreadyExists) const
  {
    if (exists(m_filePath))
    {
      if (!clearIfAlreadyExists)
      {
        // If it exists already and we do not need to clear it, we are done
        return;
      }
      else
      {
        // Otherwise we attempt to clear the file
        clear();
      }
    }

    // Create the parent directory
    Directory parentDir(m_filePath.getParentDirectory());
    if (parentDir.getDirectoryPath().as_string().empty())
    {
      ASSERT_FAIL();
      return;
    }

    parentDir.create();
    ASSERT(parentDir.exists());

    // Automatically creates the file if it does not exist
    std::ofstream file(m_filePath.as_string());
    ASSERT(file.good());
  }

  //------------------------------------------------------------------------------------------------
  void File::copy(const std::string& destinationPath)
  {
    if (!exists())
    {
      ASSERT_FAIL();
      return;
    }

    File destination(destinationPath);
    if (destination.exists())
    {
      return;
    }

    // Creates the destination file
    destination.create(false);

    // Read our file contents and append it to the newly created file
    std::string fileContents;
    read(fileContents);
    destination.append(fileContents);
  }

  //------------------------------------------------------------------------------------------------
  void File::remove() const
  {
    std::remove(m_filePath.c_str());
  }

  //------------------------------------------------------------------------------------------------
  void File::clear() const
  {
    if (exists())
    {
      std::ofstream file(m_filePath.as_string());
      file.clear();
    }
  }

  //------------------------------------------------------------------------------------------------
  void File::read(std::string& outFileContents) const
  {
    std::ifstream file(m_filePath.as_string());
    ASSERT(file.good());

    std::string buffer;

    while (std::getline(file, buffer))
    {
      outFileContents.append(buffer);
      outFileContents.append("\n");
    }

    if (!outFileContents.empty() && outFileContents.back() == '\n')
    {
      // Remove the final \n if it exists - this can be added by default and it's really annoying
      outFileContents.pop_back();
    }
  }

  //------------------------------------------------------------------------------------------------
  void File::readLines(std::vector<std::string>& outLines) const
  {
    std::ifstream file(m_filePath.as_string());
    ASSERT(file.good());

    std::string buffer;

    while (std::getline(file, buffer))
    {
      outLines.push_back(buffer);
    }
  }

  //------------------------------------------------------------------------------------------------
  std::string File::getFileName() const
  {
    const std::string& filePath = m_filePath.as_string();

    if (filePath.empty())
    {
      ASSERT_FAIL();
      return "";
    }

    std::string fileName(filePath);
    size_t index = fileName.find_last_of(PATH_DELIMITER);

    if (index < fileName.npos)
    {
      return fileName.substr(index + 1);
    }
    else
    {
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  std::string File::getExtensionlessFileName() const
  {
    if (m_filePath.as_string().empty())
    {
      ASSERT_FAIL();
      return "";
    }

    const std::string& filePath = m_filePath.as_string();

    size_t extIndex = filePath.find_last_of('.');   // Find last here in case we have a \\..\\ in our file path
    size_t delimIndex = filePath.find_last_of(PATH_DELIMITER);

    if (extIndex == filePath.npos &&
        delimIndex != filePath.npos)
    {
      return filePath.substr(delimIndex + 1, filePath.size());
    }
    else if (extIndex != filePath.npos &&
             delimIndex == filePath.npos)
    {
      return filePath.substr(0, extIndex);
    }
    else if (extIndex != filePath.npos &&
             delimIndex != filePath.npos)
    {
      return filePath.substr(delimIndex + 1, extIndex - (delimIndex + 1));
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }
}