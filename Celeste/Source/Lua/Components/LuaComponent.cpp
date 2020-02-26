#include "Lua/Components/LuaComponent.h"

#include "Objects/GameObject.h"


namespace Celeste::Lua
{
  COMPONENT_MEMORY_CREATION(LuaComponent, 100)
  COMPONENT_MEMBER_DEFINITION(LuaComponent)

  //------------------------------------------------------------------------------------------------
  LuaComponent::LuaComponent() :
    m_onSetGameObjectFunc(),
    m_onHandleInputFunc(),
    m_onUpdateFunc(),
    m_onDeathFunc()
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
  void LuaComponent::onHandleInput()
  {
    Inherited::onHandleInput();

    if (m_onHandleInputFunc.valid())
    {
      m_onHandleInputFunc(m_instance);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::onUpdate(float elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    if (m_onUpdateFunc.valid())
    {
      m_onUpdateFunc(m_instance, elapsedGameTime);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::onDeath()
  {
    Inherited::onDeath();

    if (m_onDeathFunc.valid())
    {
      m_onDeathFunc(m_instance);
    }

    resetCallbacks();
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponent::resetCallbacks()
  {
    m_instance = sol::nil;
    m_onSetActiveFunc = sol::nil;
    m_onSetGameObjectFunc = sol::nil;
    m_onHandleInputFunc = sol::nil;
    m_onUpdateFunc = sol::nil;
    m_onDeathFunc = sol::nil;
  }
}