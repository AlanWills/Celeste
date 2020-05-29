#pragma once

#include "StaticLibExport.h"
#include "Objects/Component.h"


namespace CelesteMocks
{
  class MockUnmanagedComponent : public Celeste::Component
  {
    DECLARE_UNMANAGED_COMPONENT(MockUnmanagedComponent, StaticLibExport)

    public:
      bool updateCalled() const { return m_updateCalled; }

      void reset()
      {
        m_updateCalled = false;
      }

      void update() override { Component::update(); m_updateCalled = true; }

      static Celeste::ResizeableAllocator<MockUnmanagedComponent>& getAllocator() { return m_allocator; }

    private:
      using Inherited = Celeste::Component;

      bool m_updateCalled = false;
  };
}