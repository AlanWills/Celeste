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
      bool onDeathCalled() const { return m_onDeathCalled; }

      void reset()
      {
        m_handleInputCalled = false;
        m_updateCalled = false;
        m_onDeathCalled = false;
      }

    protected:
      void onHandleInput() override;
      void onUpdate(float elapsedGameTime) override;
      void onDeath() override;
    
    private:
      typedef Celeste::Script Inherited;

      bool m_handleInputCalled;
      bool m_updateCalled;
      bool m_onDeathCalled;
  };
}