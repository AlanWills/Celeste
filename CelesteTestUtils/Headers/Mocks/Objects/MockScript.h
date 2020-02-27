#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Objects/Script.h"


namespace CelesteTestUtils
{
  class MockScript : public Celeste::Script
  {
    DECLARE_SCRIPT(MockScript, CelesteTestUtilsDllExport)

    public:
      bool handleInputCalled() const { return m_handleInputCalled; }
      bool updateCalled() const { return m_updateCalled; }

      void reset()
      {
        m_handleInputCalled = false;
        m_updateCalled = false;
      }

      void handleInput() override;
      void update(float elapsedGameTime) override;
    
    private:
      using Inherited = Celeste::Script;

      bool m_handleInputCalled;
      bool m_updateCalled;
  };
}