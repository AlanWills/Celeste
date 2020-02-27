#include "Lua/Components/LuaComponent.h"

#include "Objects/GameObject.h"


namespace Celeste::Lua
{
  COMPONENT_MEMORY_CREATION(LuaComponent, 100)
  COMPONENT_MEMBER_DEFINITION(LuaComponent)

  //------------------------------------------------------------------------------------------------
  LuaComponent::LuaComponent() :
    m_onSetGameObjectFunc(),
    m_handleInputFunc(),
    m_updateFunc()
  {
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::setInstance(const sol::table& instance)
  {
    m_instance = instance;

    onSetGameObject(*getGameObject());
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::setActive(bool active)
  {
    Inherited::setActive(active);

    if (m_onSetActiveFunc.valid())
    {
      m_onSetActiveFunc(m_instance, active);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::onSetGameObject(GameObject& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    if (m_onSetGameObjectFunc.valid())
    {
      m_onSetGameObjectFunc(m_instance, gameObject);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::handleInput()
  {
    Inherited::handleInput();

    if (m_handleInputFunc.valid())
    {
      m_handleInputFunc(m_instance);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    if (m_updateFunc.valid())
    {
      m_updateFunc(m_instance, elapsedGameTime);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::resetCallbacks()
  {
    m_instance = sol::nil;
    m_onSetActiveFunc = sol::nil;
    m_onSetGameObjectFunc = sol::nil;
    m_handleInputFunc = sol::nil;
    m_updateFunc = sol::nil;
  }
}