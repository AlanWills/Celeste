#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Objects/Component.h"


namespace CelesteTestUtils
{
  class MockComponent : public Celeste::Component
  {
    DECLARE_UNMANAGED_COMPONENT(MockComponent, CelesteTestUtilsDllExport)

    public:
      void setGameObject_Public(Celeste::GameObject& gameObject) { setGameObject(gameObject); }
      bool onSetGameObjectCalled() const { return m_onSetGameObjectCalled; }

      bool handleInputCalled() const { return m_handleInputCalled; }
      bool updateCalled() const { return m_updateCalled; }

      void reset()
      {
        m_onSetGameObjectCalled = false;
        m_handleInputCalled = false;
        m_updateCalled = false;
      }

      void handleInput() override { Component::handleInput(); m_handleInputCalled = true; }
      void update(float elapsedGameTime) override { Component::update(elapsedGameTime); m_updateCalled = true; }

      static Celeste::EntityAllocator<MockComponent>& getAllocator() { return m_allocator; }

    protected:
      void onSetGameObject(Celeste::GameObject& parent) override { m_onSetGameObjectCalled = true; }

    private:
      bool m_onSetGameObjectCalled;
      bool m_handleInputCalled;
      bool m_updateCalled;
  };
}