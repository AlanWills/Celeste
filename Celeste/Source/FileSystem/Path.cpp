#include "FileSystem/Path.h"
#include "Debug/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Path::Path(const char* fullPath) :
    m_path("")
  {
    if (fullPath != nullptr)
    {
      reset(fullPath);
    }
  }

  //------------------------------------------------------------------------------------------------
  Path::Path(const std::string& fullPath) :
    m_path("")
  {
    if (!fullPath.empty())
    {
      reset(fullPath);
    }
  }

  //------------------------------------------------------------------------------------------------
  Path::Path(const Path& path) :
    m_path(path.m_path)
  {
  }

  //------------------------------------------------------------------------------------------------
  Path::~Path()
  {
  }

  //------------------------------------------------------------------------------------------------
  Path& Path::operator=(const Path& other)
  {
    m_path = other.m_path;
    return *this;
  }

  //------------------------------------------------------------------------------------------------
  void Path::combine(const std::string& additionalPath)
  {
    if (additionalPath.empty())
    {
      return;
    }

    // Strip delimiters from the input
    std::string path(additionalPath);
    stripDelimiters(path);

    if (path == UPDIR_STRING)
    {
      // Rather than appending anything, our UPDIR_STRING means we should go up one directory
      // We simple change the path to be the parent directory's path.
      m_path = getParentDirectory();
      return;
    }

    size_t position = path.find_first_of('.');
    if (position != path.npos)
    {
      // Collapse any updirs within the string
      if (path[position + 1] == '.')
      {
        if ((position + 2) == path.length())
        {
          // We have an updir at the end
          combine(path.substr(0, position), UPDIR_STRING);
        }
        else if (position == 0)
        {
          // We have an updir at the start so remove the section of this instance's path and the rest of the string preceding it
          combine(UPDIR_STRING, path.substr(2));
        }
        else
        {
          // We have an updir in the middle of the string somewhere so remove it and the preceding section before it
          combine(path.substr(0, position), UPDIR_STRING, path.substr(position + 2));
        }
        
        return;
      }
    }

    // If our path doesn't end in the delimiter and the second doesn't start with the delimiter we should append the delimiter to the first path
    if ((!m_path.empty() && m_path.back() != PATH_DELIMITER) && (path.front() != PATH_DELIMITER))
    {
      m_path.push_back(PATH_DELIMITER);
    }
    // If the first path ends in the delimiter and the second beings with the delimiter we remove it from the end of the first path
    else if ((!m_path.empty() && m_path.back() == PATH_DELIMITER) && (path.front() == PATH_DELIMITER))
    {
      m_path.pop_back();
    }

    m_path.append(path);
  }

  //------------------------------------------------------------------------------------------------
  void Path::stripDelimiters(std::string& path)
  {
    if (path.empty())
    {
      return;
    }

    if (path.front() == PATH_DELIMITER)
    {
      path = path.substr(1);
    }

    if (path.back() == PATH_DELIMITER)
    {
      path.pop_back();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Path::getParentDirectory(std::string& outParentDirectory) const
  {
    // This can probably be done in a more efficient manner

    outParentDirectory.clear();

    if (m_path.empty() || (m_path.find_last_of(PATH_DELIMITER) == m_path.npos))
    {
      return;
    }

    outParentDirectory.append(m_path);

    if (outParentDirectory.back() == PATH_DELIMITER)
    {
      // If the path ends in a path delimiter, we do not want to count this so remove it
      outParentDirectory.pop_back();
    }

    size_t indexOfPathDelimiter = outParentDirectory.find_last_of(PATH_DELIMITER);
    while (outParentDirectory.length() > indexOfPathDelimiter)
    {
      outParentDirectory.pop_back();
    }
  }
  
  //------------------------------------------------------------------------------------------------
  bool Path::isAncestorOf(const Path& potentialChild) const
  {
    const std::string& potentialChildString = potentialChild.as_string();

    if (m_path.size() >= potentialChildString.size())
    {
      return false;
    }

    // Check that the parent matches character for character this path
    // If one character is off, we should return false
    for (size_t i = 0, n = m_path.size(); i < n; ++i)
    {
      if (potentialChildString[i] != m_path[i])
      {
        return false;
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  std::string Path::relativeTo(const Path& parent) const
  {
    if (!parent.isAncestorOf(*this))
    {
      ASSERT_FAIL();
      return "";
    }

    std::string result(m_path.substr(parent.as_string().size() + 1));

    if (result.front() == PATH_DELIMITER)
    {
      result = result.substr(1);
    }

    ASSERT(result.front() != PATH_DELIMITER);
    return result;
  }

  //------------------------------------------------------------------------------------------------
  bool operator==(const std::string& lhs, const Path& rhs) { return rhs == lhs; }

  //------------------------------------------------------------------------------------------------
  bool operator==(const char* lhs, const Path& rhs) { return rhs == lhs; }

  //------------------------------------------------------------------------------------------------
  bool operator!=(const std::string& lhs, const Path& rhs) { return rhs != lhs; }

  //------------------------------------------------------------------------------------------------
  bool operator!=(const char* lhs, const Path& rhs) { return rhs != lhs; }
}