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
  std::tuple<bool, std::vector<GameObject*>> load(const Path& relativePathToLevelFile)
  {
    std::tuple<bool, std::vector<GameObject*>> result = std::make_tuple(false, std::vector<GameObject*>());

    observer_ptr<Data> data = getResourceManager().load<Data>(relativePathToLevelFile);
    if (data == nullptr)
    {
      ASSERT_FAIL();
      return result;
    }

    const XMLElement* documentRoot = data->getDocumentRoot();
    if (documentRoot == nullptr)
    {
      ASSERT_FAIL();
      return result;
    }

    SceneDataConverter screenData(documentRoot->Name());
    if (!screenData.convertFromXML(documentRoot))
    {
      ASSERT_FAIL();
      return result;
    }

    return std::make_tuple(true, screenData.instantiate());
  }
}