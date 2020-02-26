#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/PlatformHeaders.h"

#include <string>
#include <stdarg.h>


namespace Celeste
{
  #if WINDOWS
  #define PATH_DELIMITER '\\'
  #else
  #define PATH_DELIMITER '/'
  #endif

  #define UPDIR_STRING ".."

  class Path
  {
    public:
      Path() : Path("") { }
      CelesteDllExport Path(const char* fullPath);
      CelesteDllExport Path(const std::string& fullPath);

      template <typename... T>
      Path(const char* path, const T&... paths);

      template <typename... T>
      Path(const std::string& path, const T&... paths);

      template <typename... T>
      Path(const Path& path, const T&... paths);

      CelesteDllExport Path(const Path& path);   // Copy constructor just copies underlying string
      CelesteDllExport ~Path();

      /// Assignment operator
      CelesteDllExport Path& operator=(const Path& other);

      /// Equality operators
      inline bool operator==(const Path& rhs) const { return m_path == rhs.m_path; }
      inline bool operator==(const std::string& rhs) const { return m_path == Path(rhs).m_path; }
      inline bool operator==(const char* rhs) const { return m_path == Path(rhs).m_path; }

      inline bool operator!=(const Path& rhs) const { return !(*this == rhs); }
      inline bool operator!=(const std::string& rhs) const { return !(*this == Path(rhs)); }
      inline bool operator!=(const char* rhs) const { return !(*this == Path(rhs)); }

      /// Appends a PATH_DELIMITER and the secondPath onto the firstPath
      /// std::string first("first\\path"), second("second\\path");
      /// e.g. combine(first, second) would change firstPath to "first\\path\\second\\path";
      template <typename T, typename... Args>
      void combine(const T&, const Args&... args);

      CelesteDllExport void combine(const std::string& path);
      void combine(const Path& path) { combine(path.as_string()); }
      void combine(const char* path) { combine(std::string(path)); }

      /// Returns the directory the object represented by the inputted path is in.
      /// e.g. for Root\\Directory\\File.txt this would return Root\\Directory
      /// e.g. for Root\\Directory this would return Root and for Root\\Directory\\ this would return Root
      /// Appends the full path onto the output string so anything already in the string will not be removed
      CelesteDllExport void getParentDirectory(std::string& outParentDirectory) const;
      static std::string getParentDirectory(const std::string& str) { return Path(str).getParentDirectory(); }
      std::string getParentDirectory() const
      {
        std::string parentDir;
        getParentDirectory(parentDir);
        return parentDir;
      }

      /// Sets the stored string path to be the new inputted values
      /// Allows a way to reuse the same Path object rather than constructing a new one
      template <typename T, typename... Args>
      void reset(const T& path, const Args&... args);

      CelesteDllExport bool isAncestorOf(const Path& potentialChild) const;

      /// Will remove the inputted path from this instance's path and return the value as a string
      /// Will fail and return "" if the inputted path is not an ancestor of this path.
      /// Leading delimiters will be trimmed
      CelesteDllExport std::string relativeTo(const Path& path) const;

      /// Returns the path represented by this object as a string
      inline const std::string& as_string() const { return m_path; }

      /// Returns the path represented by this object as a c-style char* array
      inline const char* c_str() const { return m_path.c_str(); }

    private:
      /// Removes any path delimiters from the front or end of the inputted string
      void stripDelimiters(std::string& path);

      std::string m_path;
  };

  //------------------------------------------------------------------------------------------------
  template <typename... T>
  Path::Path(const char* path, const T&... paths) :
    m_path(path)
  {
    combine(paths...);
  }

  //------------------------------------------------------------------------------------------------
  template <typename... T>
  Path::Path(const std::string& path, const T&... paths) :
    m_path(path)
  {
    combine(paths...);
  }

  //------------------------------------------------------------------------------------------------
  template <typename... T>
  Path::Path(const Path& path, const T&... paths) :
    Path(path.as_string(), paths...)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, typename... Args>
  void Path::combine(const T& path, const Args&... paths)
  {
    combine(path);
    combine(paths...);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, typename... Args>
  void Path::reset(const T& path, const Args&... paths)
  {
    m_path = "";
    combine(path, paths...);
  }

  // Symmetric overloads that just call the class operators

  //------------------------------------------------------------------------------------------------
  CelesteDllExport bool operator==(const std::string& lhs, const Path& rhs);

  //------------------------------------------------------------------------------------------------
  CelesteDllExport bool operator==(const char* lhs, const Path& rhs);

  //------------------------------------------------------------------------------------------------
  CelesteDllExport bool operator!=(const std::string& lhs, const Path& rhs);

  //------------------------------------------------------------------------------------------------
  CelesteDllExport bool operator!=(const char* lhs, const Path& rhs);
}