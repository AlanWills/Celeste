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
        m_onHandleInputCalled(false),
        m_onUpdateCalled(false),
        m_onDeathCalled(false)
        { }

      ~MockEntity() = default;

      bool isOnHandleInputCalled() const { return m_onHandleInputCalled; }
      bool isOnUpdateCalled() const { return m_onUpdateCalled; }
      bool isOnDeathCalled() const { return m_onDeathCalled; }

      void reset()
      {
        m_onHandleInputCalled = false;
        m_onUpdateCalled = false;
        m_onDeathCalled = false;
      }

    protected:
      void onHandleInput() override { Inherited::onHandleInput(); m_onHandleInputCalled = true; }
      void onUpdate(float elapsedGameTime) override { Inherited::onUpdate(elapsedGameTime); m_onUpdateCalled = true; }
      void onDeath() override { Inherited::onDeath(); m_onDeathCalled = true; }

    private:
      bool m_onHandleInputCalled;
      bool m_onUpdateCalled;
      bool m_onDeathCalled;
  };
}