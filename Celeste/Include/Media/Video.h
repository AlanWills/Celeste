#pragma once

#include "CelesteDllExport.h"
#include "VideoSettings.h"

#include <string>


namespace Celeste
{
  namespace Media
  {
    class Video
    {
      public:
        CelesteDllExport static void play(const std::string& videoPath, const VideoSettings& videoSettings);
        CelesteDllExport static void playAsync(const std::string& videoPath, const VideoSettings& videoSettings);

      private:
        Video() = default;

        static std::string m_ffplayExecutableName;
    };
  }
}