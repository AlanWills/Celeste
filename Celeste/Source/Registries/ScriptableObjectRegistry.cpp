#include "Registries/ScriptableObjectRegistry.h"
#include "Resources/ResourceManager.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  ScriptableObjectRegistry::InstantiationMap& ScriptableObjectRegistry::getInstantiationMap()
  {
    static InstantiationMap instantiationMap;
    return instantiationMap;
  }

  //------------------------------------------------------------------------------------------------
  std::unique_ptr<ScriptableObject> ScriptableObjectRegistry::loadScriptableObject(const Path& path)
  {
    observer_ptr<Resources::Data> data = Resources::getResourceManager().load<Resources::Data>(path);
    if (data != nullptr)
    {
      const char* rootElementName = data->getDocumentRoot()->Name();
      if (hasScriptableObject(rootElementName))
      {
        return std::move(std::get<1>(getInstantiationMap()[rootElementName])(path));
      }
    }

    return std::unique_ptr<ScriptableObject>();
  }
}