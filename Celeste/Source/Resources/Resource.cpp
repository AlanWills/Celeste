#include "Resources/Resource.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  bool Resource::loadFromFile(const Path& filePath)
  {
    if (!File(filePath).exists())
    {
      ASSERT_FAIL();
      return false;
    }

    m_filePath = filePath;
    m_resourceId = string_id(filePath.as_string());

    if (!doLoadFromFile(filePath))
    {
      ASSERT_FAIL();
      unload();
      return false;
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void Resource::unload()
  {
    doUnload();

    m_filePath = Path();
    m_resourceId = string_id();
  }
}