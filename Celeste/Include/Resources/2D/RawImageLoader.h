#pragma once

#include "CelesteDllExport.h"
#include "FileSystem/Path.h"


namespace Celeste::Resources
{
  class CelesteDllExport RawImageLoader
  {
    public:
      RawImageLoader(const std::string& fullPathToImageFile);
      RawImageLoader(const Path& fullPathToImageFile) : RawImageLoader(fullPathToImageFile.as_string()) { }
      ~RawImageLoader();

      unsigned char* getData() const { return m_data; }
      int getWidth() const { return m_width; }
      int getHeight() const { return m_height; }

    private:
      unsigned char* m_data;

      int m_width;
      int m_height;
  };
}