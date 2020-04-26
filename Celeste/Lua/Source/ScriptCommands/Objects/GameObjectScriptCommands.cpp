#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Registries/ComponentRegistry.h"
#include "Rendering/Renderer.h"
#include "Scene/SceneUtils.h"
#include "Scene/SceneManager.h"
#include "Lua/LuaState.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::GameObject> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::Component> : std::false_type {};
}

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
      return sol::make_object(LuaState::instance(), ComponentRegistry::createComponent(componentName, gameObject));
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> findChildGameObject(GameObject& gameObject, const std::string& childName)
    {
      return gameObject.findChild(childName);
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> findGameObject_StringOverload(const std::string& childName)
    {
      return getSceneManager().find(childName);
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> findGameObject_StringIdOverload(StringId childName)
    {
      return getSceneManager().find(childName);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<GameObject>(
      state,
      "GameObject",
      sol::base_classes, sol::bases<Entity, Object>(),
      "getName", &Internals::getName,
      "setName", &Internals::setName_String,
      "getParent", &Internals::getParent,
      "setParent", &GameObject::setParent,
      "getTransform", &Internals::getTransform,
      "getComponentCount", &GameObject::getComponentCount,
      "getComponent", &GameObject::getComponent,
      "addComponent", &Internals::addComponent,
      "getChildCount", &GameObject::getChildCount,
      "getChild", &GameObject::getChild,
      "findChild", &Internals::findChildGameObject,
      "find", sol::overload(&Internals::findGameObject_StringOverload, Internals::findGameObject_StringIdOverload));

    LuaState::requireModule("Objects.GameObject");
  }
}