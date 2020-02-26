#include "Objects/Entity.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Entity::Entity()
  {
    setActive(true);
  }

  //------------------------------------------------------------------------------------------------
  void Entity::handleInput()
  {
    ASSERT(m_alive);
    ASSERT(m_active);
    onHandleInput();
  }

  //------------------------------------------------------------------------------------------------
  void Entity::update(float elapsedGameTime)
  {
    ASSERT(m_alive);
    ASSERT(m_active);
    onUpdate(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Entity::die()
  {
    ASSERT(m_alive);

    m_alive = false;
    m_active = false;

    onDeath();
  }
}