#pragma once

#include "Objects/Component.h"
#include "glm/glm.hpp"


namespace Celeste::Physics
{
  class RigidBody2D : public Component
  {
    DECLARE_COMPONENT(RigidBody2D, PhysicsManager, CelesteDllExport)

    public:
      inline const glm::vec2& getLinearVelocity() const { return m_linearVelocity; }
      inline void setLinearVelocity(float xVelocity, float yVelocity)
      {
        m_linearVelocity.x = glm::clamp<float>(xVelocity, m_minLinearVelocity.x, m_maxLinearVelocity.x);
        m_linearVelocity.y = glm::clamp<float>(yVelocity, m_minLinearVelocity.y, m_maxLinearVelocity.y);
      }
      inline void setLinearVelocity(const glm::vec2& linearVelocity)
      {
        m_linearVelocity.x = glm::clamp<float>(linearVelocity.x, m_minLinearVelocity.x, m_maxLinearVelocity.x);
        m_linearVelocity.y = glm::clamp<float>(linearVelocity.y, m_minLinearVelocity.y, m_maxLinearVelocity.y);
      }

      inline const glm::vec2& getMinLinearVelocity() const { return m_minLinearVelocity; }
      inline void setMinLinearVelocity(const glm::vec2& minLinearVelocity) { m_minLinearVelocity = minLinearVelocity; }

      inline const glm::vec2& getMaxLinearVelocity() const { return m_maxLinearVelocity; }
      inline void setMaxLinearVelocity(const glm::vec2& maxLinearVelocity) { m_maxLinearVelocity = maxLinearVelocity; }

      inline void incrementLinearVelocity(const glm::vec2& velocityDelta) { setLinearVelocity(m_linearVelocity + velocityDelta); }
      inline void incrementLinearVelocity(float xVelocityDelta, float yVelocityDelta) { incrementLinearVelocity(glm::vec2(xVelocityDelta, yVelocityDelta)); }

      /// Positive is clockwise
      inline float getAngularVelocity() const { return m_angularVelocity; }
      inline void setAngularVelocity(float angularVelocity) { m_angularVelocity = glm::clamp<float>(angularVelocity, m_minAngularVelocity, m_maxAngularVelocity); }

      inline float getMinAngularVelocity() const { return m_minAngularVelocity; }
      inline void setMinAngularVelocity(float minAngularVelocity) { m_minAngularVelocity = minAngularVelocity; }

      inline float getMaxAngularVelocity() const { return m_maxAngularVelocity; }
      inline void setMaxAngularVelocity(float maxAngularVelocity) { m_maxAngularVelocity = maxAngularVelocity; }

      inline void incrementAngularVelocity(float angularVelocityDelta) { setAngularVelocity(m_angularVelocity + angularVelocityDelta); }

      CelesteDllExport void update(float secondsPerUpdate) override;

    private:
      using Inherited = Component;

      glm::vec2 m_linearVelocity;
      glm::vec2 m_minLinearVelocity;
      glm::vec2 m_maxLinearVelocity;

      float m_angularVelocity;
      float m_minAngularVelocity;
      float m_maxAngularVelocity;
  };
}