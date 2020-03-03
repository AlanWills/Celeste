#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Registries/ComponentRegistry.h"
#include "Screens/Screen.h"
#include "Rendering/Renderer.h"


namespace Celeste::Lua::GameObjectScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getName(GameObject& gameObject)
    {
      return deinternString(gameObject.getName());
    }

    //------------------------------------------------------------------------------------------------
    void setName_String(GameObject& gameObject, const std::string& name)
    {
      gameObject.setName(name);
    }

    //------------------------------------------------------------------------------------------------
    bool shouldRender(GameObject& gameObject)
    {
      observer_ptr<Rendering::Renderer> renderer = gameObject.findComponent<Rendering::Renderer>();
      return renderer != nullptr && renderer->isActive();
    }

    //------------------------------------------------------------------------------------------------
    void setShouldRender(GameObject& gameObject, bool shouldRender)
    {
      if (observer_ptr<Rendering::Renderer> renderer = gameObject.findComponent<Rendering::Renderer>(); renderer != nullptr)
      {
        renderer->setActive(shouldRender);
      }
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> getParent(GameObject& gameObject)
    {
      return gameObject.getParent();
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<Transform> getTransform(GameObject& gameObject)
    {
      return gameObject.getTransform();
    }

    //------------------------------------------------------------------------------------------------
    sol::object addComponent(GameObject& gameObject, const std::string& componentName)
    {
      return sol::make_object(LuaState::instance(), ComponentRegistry::allocateComponent(componentName, gameObject));
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> findChildGameObject(GameObject& gameObject, const std::string& childName)
    {
      return gameObject.findChildGameObject(childName);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<GameObject>(
      "GameObject",
      sol::base_classes, sol::bases<Entity, Object>(),
      "getName", &Internals::getName,
      "setName", &Internals::setName_String,
      "shouldRender", &Internals::shouldRender,
      "setShouldRender", &Internals::setShouldRender,
      "getParent", &Internals::getParent,
      "setParent", &GameObject::setParent,
      "getTransform", &Internals::getTransform,
      "getComponentCount", &GameObject::getComponentCount,
      "getComponent", &GameObject::getComponent,
      "addComponent", &Internals::addComponent,
      "getChildCount", &GameObject::getChildCount,
      "getChildTransform", &GameObject::getChildTransform,
      "getChildGameObject", &GameObject::getChildGameObject,
      "findChildGameObject", &Internals::findChildGameObject);

    LuaState::requireModule("Objects.GameObject");
  }
}