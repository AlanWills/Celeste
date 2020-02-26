#include "Resources/Resource.h"


namespace Celeste
{
  namespace Resources
  {
    //------------------------------------------------------------------------------------------------
    bool Resource::loadFromFile(const Path& filePath)
    {
      if (!File(filePath).exists())
      {
        ASSERT_FAIL();
        return false;
      }

      m_resourceId = internString(filePath.as_string());
      return doLoadFromFile(filePath);
    }

    //------------------------------------------------------------------------------------------------
    void Resource::unload()
    {
      doUnload();
      m_resourceId = 0;
    }
  }
}