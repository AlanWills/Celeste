#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Objects/Script.h"


namespace CelesteTestUtils
{
  class CollisionDetector : public Celeste::Script
  {
    DECLARE_UNMANAGED_COMPONENT(CollisionDetector, CelesteTestUtilsDllExport)

    public:
      bool triggerEnterCalled() const { return m_triggerEnterCount > 0; }
      size_t triggerEnterCount() const { return m_triggerEnterCount; }

      bool triggerCalled() const { return m_triggerCount > 0; }
      size_t triggerCount() const { return m_triggerCount; }

      bool triggerExitCalled() const { return m_triggerExitCount > 0; }
      size_t triggerExitCount() const { return m_triggerExitCount; }

      bool collisionEnterCalled() const { return m_collisionEnterCount > 0; }
      size_t collisionEnterCount() const { return m_collisionEnterCount; }

      bool collisionCalled() const { return m_collisionCount > 0; }
      size_t collisionCount() const { return m_collisionCount; }

      bool collisionExitCalled() const { return m_collisionExitCount > 0; }
      size_t collisionExitCount() const { return m_collisionExitCount; }

      void reset()
      {
        m_triggerEnterCount = 0;
        m_triggerCount = 0;
        m_triggerExitCount = 0;
        m_collisionEnterCount = 0;
        m_collisionCount = 0;
        m_collisionExitCount = 0;
      }

      void triggerEnter(Celeste::Physics::Collider& collider) override { ++m_triggerEnterCount; }
      void trigger(Celeste::Physics::Collider& collider) override { ++m_triggerCount; }
      void triggerExit(Celeste::Physics::Collider& collider) override { ++m_triggerExitCount; }
      void collisionEnter(Celeste::Physics::Collider& collider) override { ++m_collisionEnterCount; }
      void collision(Celeste::Physics::Collider& collider) override { ++m_collisionCount; }
      void collisionExit(Celeste::Physics::Collider& collider) override { ++m_collisionExitCount; }

    private:
      using Inherited = Celeste::Script;

      size_t m_triggerEnterCount;
      size_t m_triggerCount;
      size_t m_triggerExitCount;

      size_t m_collisionEnterCount;
      size_t m_collisionCount;
      size_t m_collisionExitCount;
  };
}