#include "Scene/SceneLoader.h"
#include "DataConverters/Scene/SceneDataConverter.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Resources/ResourceManager.h"
#include "Scene/SceneUtils.h"

using namespace Celeste::Resources;


namespace Celeste::SceneLoader
{
  //------------------------------------------------------------------------------------------------
  void load(const Path& relativePathToLevelFile)
  {
    observer_ptr<Data> data = getResourceManager().load<Data>(relativePathToLevelFile);
    if (data == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    const XMLElement* documentRoot = data->getDocumentRoot();
    if (documentRoot == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    SceneDataConverter screenData(documentRoot->Name());
    if (!screenData.convertFromXML(documentRoot))
    {
      ASSERT_FAIL();
      return;
    }

    screenData.instantiate();
  }
}