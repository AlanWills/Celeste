#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Objects/Component.h"


namespace CelesteTestUtils
{
  class MockComponent : public Celeste::Component
  {
    DECLARE_SCRIPT(MockComponent, CelesteTestUtilsDllExport)

    public:
      void setGameObject_Public(Celeste::GameObject& gameObject) { setGameObject(gameObject); }
      bool onSetGameObjectCalled() const { return m_onSetGameObjectCalled; }

      bool handleInputCalled() const { return m_handleInputCalled; }
      bool updateCalled() const { return m_updateCalled; }
      bool onDeathCalled() const { return m_onDeathCalled; }

      void reset()
      {
        m_onSetGameObjectCalled = false;
        m_handleInputCalled = false;
        m_updateCalled = false;
        m_onDeathCalled = false;
      }

      static Celeste::EntityAllocator<MockComponent>& getAllocator() { return m_componentAllocator; }

    protected:
      void onSetGameObject(Celeste::GameObject& parent) override { m_onSetGameObjectCalled = true; }
      void onHandleInput() override { Component::onHandleInput(); m_handleInputCalled = true; }
      void onUpdate(float elapsedGameTime) override { Component::onUpdate(elapsedGameTime); m_updateCalled = true; }
      void onDeath() override { Component::onDeath(); m_onDeathCalled = true; }

    private:
      bool m_onSetGameObjectCalled;
      bool m_handleInputCalled;
      bool m_updateCalled;
      bool m_onDeathCalled;
  };
}