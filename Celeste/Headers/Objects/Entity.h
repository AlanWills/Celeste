#pragma once

#include "CelesteDllExport.h"
#include "Object.h"
#include "Debug/Assert.h"


namespace Celeste
{
  class Entity : public Object
  {
    public:
      CelesteDllExport Entity();
      virtual ~Entity() = default;

      CelesteDllExport void handleInput();
      CelesteDllExport void update(float elapsedGameTime);
      CelesteDllExport void die();

      inline bool isAlive() const { return m_alive; }
      inline bool isActive() const { return m_active; }

      virtual void setActive(bool isActive) { m_active = isActive; }

    protected:
      virtual void onHandleInput() { }
      virtual void onUpdate(float elapsedGameTime) { }
      virtual void onDeath() { }

    private:
      bool m_alive = true;
      bool m_active = false;
  };
}