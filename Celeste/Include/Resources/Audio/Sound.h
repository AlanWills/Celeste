#pragma once

#include "UtilityHeaders/ALHeaders.h"
#include "CelesteDllExport.h"
#include "Resources/Resource.h"

#include <string>


namespace Celeste::Resources
{
  class Sound : public Resource
  {
    public:
      CelesteDllExport Sound();
      CelesteDllExport ~Sound();

      ALuint getAudioHandle() const { return m_audioHandle; }

    protected:
      CelesteDllExport bool doLoadFromFile(const Path& soundFilePath) override;
      CelesteDllExport void doUnload() override;

    private:
      typedef Resource Inherited;

      ALuint m_audioHandle;
  };
}