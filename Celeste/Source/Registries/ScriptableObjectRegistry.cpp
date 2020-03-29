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

#if _DEBUG
  //------------------------------------------------------------------------------------------------
  ScriptableObjectRegistry::BindingsMap& ScriptableObjectRegistry::getBindingsMap()
  {
    static BindingsMap bindingsMap;
    return bindingsMap;
  }

  //------------------------------------------------------------------------------------------------
  void ScriptableObjectRegistry::generateAllBindings(
    const Directory& destinationDirectory,
    const BindingCallback& onBindingGenerated)
  {
    for (const BindingsMapPair& pair : getBindingsMap())
    {
      Path path(destinationDirectory.getDirectoryPath(), pair.first + ".cs");
      pair.second.second(destinationDirectory);

      onBindingGenerated(pair.first, path);
    }
  }

  //------------------------------------------------------------------------------------------------
  void ScriptableObjectRegistry::generateBindingsForAssembly(
    const std::string& assemblyName,
    const Directory& destinationDirectory,
    const BindingCallback& onBindingGenerated)
  {
    for (const BindingsMapPair& pair : getBindingsMap())
    {
      // Check for equality or the namespace name starts with the inputted namespace (i.e. it is nested)
      if (pair.second.first.size() >= assemblyName.size() &&
          pair.second.first.compare(0, assemblyName.size(), assemblyName, 0, assemblyName.size()) == 0)
      {
        Path path(destinationDirectory.getDirectoryPath(), pair.first + ".cs");
        pair.second.second(destinationDirectory);

        onBindingGenerated(pair.first, path);
      }
    }
  }
#endif
}