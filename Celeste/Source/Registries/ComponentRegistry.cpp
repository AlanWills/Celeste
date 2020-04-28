#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "Bindings/BindingsGenerator.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  ComponentRegistry::~ComponentRegistry()
  {
  }

  //------------------------------------------------------------------------------------------------
  ComponentRegistry::ComponentMap& ComponentRegistry::getComponents()
  {
    static ComponentRegistry::ComponentMap components;
    return components;
  }

  //------------------------------------------------------------------------------------------------
#if _DEBUG
  ComponentRegistry::ComponentBindingStorage& ComponentRegistry::getBindings()
  {
    static ComponentRegistry::ComponentBindingStorage bindings;
    return bindings;
  }
#endif

  //------------------------------------------------------------------------------------------------
  bool ComponentRegistry::registerComponent(const std::string& name, const ComponentCreationFunction& creationFunction)
  {
    if (!hasComponent(name))
    {
      getComponents().emplace(name, creationFunction);
      return true;
    }

    ASSERT_FAIL();
    return false;
  }

  //------------------------------------------------------------------------------------------------
  void ComponentRegistry::deregisterComponent(const std::string& name)
  {
    if (!hasComponent(name))
    {
      return;
    }

    getComponents().erase(name);
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Component> ComponentRegistry::createComponent(const std::string& componentName, GameObject& gameObject)
  {
    if (componentName.empty() || !hasComponent(componentName))
    {
      ASSERT_FAIL();
      return observer_ptr<Component>();
    }

    return getComponents()[componentName](gameObject);
  }

#if _DEBUG
  //------------------------------------------------------------------------------------------------
  void ComponentRegistry::generateAllBindings(
    const Directory& destinationDirectory,
    const BindingCallback& onBindingGenerated)
  {
    for (const ComponentBindingStorageValue& binding : getBindings())
    {
      Path path(destinationDirectory.getDirectoryPath(), binding->getName() + ".cs");
      Bindings::BindingsGenerator::generateComponentBindings(destinationDirectory, *binding);

      onBindingGenerated(binding->getName(), path);
    }
  }

  //------------------------------------------------------------------------------------------------
  void ComponentRegistry::generateBindingsForAssembly(
    const std::string& namespaceName,
    const Directory& destinationDirectory,
    const BindingCallback& onBindingGenerated)
  {
    for (const ComponentBindingStorageValue& binding : getBindings())
    {
      // Check for equality or the namespace name starts with the inputted namespace (i.e. it is nested)
      if (binding->getNamespace().size() >= namespaceName.size() &&
          binding->getNamespace().compare(0, namespaceName.size(), namespaceName) == 0)
      {
        Path path(destinationDirectory.getDirectoryPath(), binding->getName() + ".cs");
        Bindings::BindingsGenerator::generateComponentBindings(destinationDirectory, *binding);

        onBindingGenerated(binding->getName(), path);
      }
    }
  }
#endif
}