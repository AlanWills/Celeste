#include "Lua/Components/LuaComponent.h"

#include "Objects/GameObject.h"


namespace Celeste::Lua
{
  CUSTOM_MEMORY_CREATION(LuaComponent, 100)

  //------------------------------------------------------------------------------------------------
  LuaComponent::LuaComponent(GameObject& gameObject) :
    Inherited(gameObject),
    m_onSetActiveFunc(),
    m_handleInputFunc(),
    m_updateFunc()
  {
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
    m_handleInputFunc = sol::nil;
    m_updateFunc = sol::nil;
  }
}