#pragma once

#include "Objects/Entity.h"


namespace CelesteTestUtils
{
  class MockEntity : public Celeste::Entity
  {
    private:
      using Inherited = Celeste::Entity;

    public:
      MockEntity() :
        m_setActiveCalled(false),
        m_onHandleInputCalled(false),
        m_onUpdateCalled(false)
        { }

      ~MockEntity() = default;

      bool isSetActiveCalled() const { return m_setActiveCalled; }
      bool isOnHandleInputCalled() const { return m_onHandleInputCalled; }
      bool isOnUpdateCalled() const { return m_onUpdateCalled; }

      void reset()
      {
        m_setActiveCalled = false;
        m_onHandleInputCalled = false;
        m_onUpdateCalled = false;
      }

      void setActive(bool isActive) { Inherited::setActive(isActive); m_setActiveCalled = isActive; }
      void handleInput() override { Inherited::handleInput(); m_onHandleInputCalled = true; }
      void update(float elapsedGameTime) override { Inherited::update(elapsedGameTime); m_onUpdateCalled = true; }

    private:
      bool m_setActiveCalled;
      bool m_onHandleInputCalled;
      bool m_onUpdateCalled;
  };
}