#include "FileSystem/Directory.h"
#include "Debug/Assert.h"

#include <direct.h>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Directory::Directory(const std::string& fullDirectoryPath) :
    m_dirPath(fullDirectoryPath)
  {
  }

  //------------------------------------------------------------------------------------------------
  Directory& Directory::operator=(const Directory& other)
  {
    // No create here - preserve state of input directory
    m_dirPath = other.m_dirPath;
    return *this;
  }

  //------------------------------------------------------------------------------------------------
  void Directory::getExecutingAppDirectory(std::string& outputDir)
  {
    char buffer[1024];
    _getcwd(buffer, 1024);

    outputDir.append(buffer);
  }

  //------------------------------------------------------------------------------------------------
  bool Directory::exists(const std::string& fullDirectoryPath)
  {
    // -1 corresponds to an error
    struct stat buf;
    return (stat(fullDirectoryPath.c_str(), &buf) == 0) && S_ISDIR(buf.st_mode);
  }

  //------------------------------------------------------------------------------------------------
  bool Directory::create() const
  {
    if (exists(m_dirPath))
    {
      return true;
    }

    Directory parentDirectory(m_dirPath.getParentDirectory());
    if (!parentDirectory.exists())
    {
      // Recursively create all the parent directories
      parentDirectory.create();
    }

    bool success = _mkdir(m_dirPath.c_str()) == 0;
    ASSERT(success);
    return success;
  }

  //------------------------------------------------------------------------------------------------
  void Directory::remove() const
  {
    if (exists(m_dirPath))
    {
      std::vector<File> files;
      findFiles(files);

      for (const File& file : files)
      {
        file.remove();
      }

      std::vector<Directory> dirs;
      findDirectories(dirs);

      for (const Directory& dir : dirs)
      {
        dir.remove();
      }

      int result = _rmdir(m_dirPath.c_str());
      ASSERT(result == 0);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Directory::findFiles(
    std::vector<File>& files,
    const std::string& extension,
    bool includeSubDirectories) const
  {
    if (!exists(m_dirPath))
    {
      ASSERT_FAIL_MSG("Directory does not exist");
      return;
    }

    DIR* dir = opendir(m_dirPath.c_str());

#ifdef WIN32
    // There are default folders (windows thing I guess).  Don't include these
    readdir(dir);
    readdir(dir);
#endif

    while (dirent* dirent = readdir(dir))
    {
      if (dirent->d_type == DT_REG)
      {
        Path filePath(m_dirPath, dirent->d_name);

        // Check the extension here
        if (extension != ".")
        {
          std::string thisExtension(dirent->d_name);
          thisExtension = thisExtension.substr(thisExtension.find_first_of('.'));

          if (extension == thisExtension)
          {
            files.emplace_back(File(filePath));
          }
        }
        else
        {
          files.push_back(File(filePath));
        }
      }
      else if (includeSubDirectories && dirent->d_type == DT_DIR)
      {
        Directory(Path(m_dirPath, dirent->d_name)).findFiles(files, extension, includeSubDirectories);
      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }

  //------------------------------------------------------------------------------------------------
  void Directory::findDirectories(
    std::vector<Directory>& directories,
    bool includeSubDirectories) const
  {
    if (!exists(m_dirPath))
    {
      ASSERT_FAIL_MSG("Directory does not exist");
      return;
    }

    DIR* dir = opendir(m_dirPath.c_str());

#ifdef WIN32
    // There are default folders (windows thing I guess).  Don't include these
    readdir(dir);
    readdir(dir);
#endif

    while (dirent* dirent = readdir(dir))
    {
      if (dirent->d_type == DT_DIR)
      {
        Directory directory(Path(m_dirPath, dirent->d_name));
        directories.push_back(directory);

        directory.findDirectories(directories, includeSubDirectories);
      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }

  //------------------------------------------------------------------------------------------------
  File Directory::createFile(const std::string& fileName)
  {
    File file = File(Path(m_dirPath, fileName));
    file.create();

    return file;
  }

  //------------------------------------------------------------------------------------------------
  Directory Directory::createDirectory(const std::string& directoryName)
  {
    Directory dir = Directory(Path(m_dirPath, directoryName));
    dir.create();

    return dir;
  }

  //------------------------------------------------------------------------------------------------
  std::string Directory::getDirectoryName() const
  {
    std::string directoryPath(m_dirPath.as_string());

    if (directoryPath.back() == PATH_DELIMITER)
    {
      directoryPath.pop_back();
    }

    size_t position = directoryPath.find_last_of(PATH_DELIMITER);
    if (position != directoryPath.npos)
    {
      return directoryPath.substr(position + 1);
    }
    else
    {
      return "";
    }
  }
}