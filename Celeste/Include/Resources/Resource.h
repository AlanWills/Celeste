#pragma once

#include "FileSystem/Path.h"
#include "FileSystem/File.h"
#include "Objects/Object.h"
#include "Assert/Assert.h"
#include "StringId/string_id.h"
#include "CelesteDllExport.h"


namespace Celeste::Resources
{
  class Resource : public Object
  {
    public:
      Resource() : m_resourceId() { }

      CelesteDllExport bool loadFromFile(const Path& filePath);
      CelesteDllExport void unload();

      const Path& getFilePath() const { return m_filePath; }
      string_id getResourceId() const { return m_resourceId; }

    protected:
      virtual bool doLoadFromFile(const Path& filePath) = 0;
      virtual void doUnload() = 0;

    private:
      Path m_filePath;
      string_id m_resourceId;
  };
}