#pragma once

#include "CelesteDllExport.h"
#include "Path.h"

#include <string>
#include <vector>

namespace Celeste
{
  class File
  {
    public:
      /// \brief Automatically creates the file in the constructor and can optionally clear it too if specified.
      /// By default it does not clear the file if it exists already
      CelesteDllExport File(const std::string& filePath);
      CelesteDllExport File(const Path& path);

      /// Copy constructor and assignment operator do not create the file; just copy the path
      /// This seems reasonable as we wish to preserve the internal state of the filesystem if we are copying a File which does not exist
      CelesteDllExport File(const File& file);

      CelesteDllExport File& operator=(const File& file);
      inline bool operator==(const File& rhs) const { return m_filePath == rhs.m_filePath; }

      /// Returns true if the file exists
      CelesteDllExport static bool exists(const std::string& fullFilePath);
      static bool exists(const Path& filePath) { return exists(filePath.as_string()); }
      bool exists() const { return exists(m_filePath.as_string()); }

      /// Creates a file if it does not exist.
      /// Pass true to clear the file if it does exist
      CelesteDllExport void create(bool clearIfAlreadyExists = true) const;

      /// Copies this file to the inputted destination file path.
      /// If the destination file already exists, this function does nothing.
      CelesteDllExport void copy(const std::string& destinationPath);
      void copy(const Path& destinationPath) { copy(destinationPath.as_string()); }

      /// Opens a file and adds the inputted string to the end of it followed by std::endl
      /// Therefore, every call to this function will append the input onto a new line
      /// Will create the file if it does not exist
      CelesteDllExport void append(const std::string& stringToAppend) const;

      /// Deletes a file if it exists
      CelesteDllExport void remove() const;

      /// Clears a file if it existsk
      CelesteDllExport void clear() const;

      /// Opens a file if it exists and stores the contents in the outFileContents parameter
      CelesteDllExport void read(std::string& outFileContents) const;

      /// Adds all the lines for the file onto the end of the inputted vector, without altering any contents that might already be inside it
      CelesteDllExport void readLines(std::vector<std::string>& outLines) const;

      inline const Path& getFilePath() const { return m_filePath; }

      /// Obtains the name of the file relative to it's parent directory including extension
      CelesteDllExport std::string getFileName() const;

      /// Obtains the name of the file relative to it's parent directory not including extension
      CelesteDllExport std::string getExtensionlessFileName() const;

    private:
      Path m_filePath;
  };
}