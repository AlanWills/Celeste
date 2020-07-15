#pragma once

#include "CelesteDllExport.h"
#include "VideoSettings.h"
#include "FileSystem/Path.h"

#include <string>


namespace Celeste::Media
{
  class Video
  {
    public:
      CelesteDllExport static void play(const std::string& videoPath, const VideoSettings& videoSettings);
      CelesteDllExport static void playAsync(const std::string& videoPath, const VideoSettings& videoSettings);

    private:
      Video() = default;

      static Path m_ffplayExecutablePath;
  };
}