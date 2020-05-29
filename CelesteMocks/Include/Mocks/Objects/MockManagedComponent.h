#pragma once

#include "StaticLibExport.h"
#include "Objects/Component.h"


namespace CelesteMocks
{
  class MockManagedComponent : public Celeste::Component
  {
    DECLARE_MANAGED_COMPONENT(MockManagedComponent, MadeUpManager, StaticLibExport)

    public:
      bool updateCalled() const { return m_updateCalled; }

      void reset()
      {
        m_updateCalled = false;
      }

      void update() override { Component::update(); m_updateCalled = true; }

      static Celeste::ResizeableAllocator<MockManagedComponent>& getAllocator() { return m_allocator; }

    private:
      using Inherited = Celeste::Component;

      bool m_updateCalled = false;
  };
}