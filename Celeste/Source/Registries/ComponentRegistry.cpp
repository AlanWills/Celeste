#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
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
}