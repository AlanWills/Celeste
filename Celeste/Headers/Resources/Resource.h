#pragma once

#include "FileSystem/Path.h"
#include "FileSystem/File.h"
#include "Objects/Object.h"
#include "Debug/Assert.h"
#include "UID/StringId.h"
#include "CelesteDllExport.h"


namespace Celeste
{
  namespace Resources
  {
    class Resource : public Object
    {
      public:
        Resource() : m_resourceId(0) { }

        CelesteDllExport bool loadFromFile(const Path& filePath);
        CelesteDllExport void unload();

        StringId getResourceId() const { return m_resourceId; }

      protected:
        virtual bool doLoadFromFile(const Path& filePath) = 0;
        virtual void doUnload() = 0;

      private:
        /// A string id using the full path of the file it was loaded from which will provide a unique identifier
        StringId m_resourceId;
    };
  }
}