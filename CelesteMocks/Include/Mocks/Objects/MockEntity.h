#pragma once

#include "Objects/Entity.h"


namespace CelesteMocks
{
  class MockEntity : public Celeste::Entity
  {
    private:
      using Inherited = Celeste::Entity;

    public:
      MockEntity() :
        m_setActiveCalled(false),
        m_updateCalled(false)
        { }

      ~MockEntity() = default;

      bool isSetActiveCalled() const { return m_setActiveCalled; }
      bool isUpdateCalled() const { return m_updateCalled; }

      void reset()
      {
        m_setActiveCalled = false;
        m_updateCalled = false;
      }

      void setActive(bool isActive) { Inherited::setActive(isActive); m_setActiveCalled = isActive; }
      void update() override { Inherited::update(); m_updateCalled = true; }

    private:
      bool m_setActiveCalled;
      bool m_updateCalled;
  };
}