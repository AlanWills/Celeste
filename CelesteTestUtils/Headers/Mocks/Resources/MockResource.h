#pragma once

#include "Resources/Resource.h"


namespace CelesteTestUtils
{
  class MockResource : public Celeste::Resources::Resource
  {
    private:
      typedef Resource Inherited;

    public:
      MockResource() : m_loaded(false) { }
      ~MockResource() { }

      bool getLoaded() const { return m_loaded; }

    protected:
      bool doLoadFromFile(const Celeste::Path& path) override
      {
        m_loaded = true;
        return true;
      }

      void doUnload() override { m_loaded = false; }

    private:
      bool m_loaded;
  };
}