#pragma once

#include <functional>


namespace Celeste
{
  namespace Media
  {
    struct VideoSettings
    {
      public:
        VideoSettings() :
          m_autoExit(true),
          m_volume(1.0f),
          m_videoCompleteCallback(nullptr)
        {
        }

        bool m_autoExit;
        float m_volume;
        std::function<void()> m_videoCompleteCallback;
    };
  }
}