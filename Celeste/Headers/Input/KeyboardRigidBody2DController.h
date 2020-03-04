#pragma once

#include "Objects/Script.h"
#include "InputEnums.h"
#include "Maths/MathsEnums.h"


namespace Celeste::Physics
{
  class RigidBody2D;
}

namespace Celeste::Input
{
  class KeyboardRigidBody2DController : public Script
  {
    DECLARE_UNMANAGED_COMPONENT(KeyboardRigidBody2DController, CelesteDllExport)

    public:
      inline int getDecreaseXLinearVelocityKey() const { return m_decreaseXLinearVelocityKey; }
      inline void setDecreaseXLinearVelocityKey(int newKey) { m_decreaseXLinearVelocityKey = newKey; }

      inline int getIncreaseXLinearVelocityKey() const { return m_increaseXLinearVelocityKey; }
      inline void setIncreaseXLinearVelocityKey(int newKey) { m_increaseXLinearVelocityKey = newKey; }

      inline int getDecreaseYLinearVelocityKey() const { return m_decreaseYLinearVelocityKey; }
      inline void setDecreaseYLinearVelocityKey(int newKey) { m_decreaseYLinearVelocityKey = newKey; }

      inline int getIncreaseYLinearVelocityKey() const { return m_increaseYLinearVelocityKey; }
      inline void setIncreaseYLinearVelocityKey(int newKey) { m_increaseYLinearVelocityKey = newKey; }

      inline int getDecreaseAngularVelocityKey() const { return m_decreaseAngularVelocityKey; }
      inline void setDecreaseAngularVelocityKey(int newKey) { m_decreaseAngularVelocityKey = newKey; }

      inline int getIncreaseAngularVelocityKey() const { return m_increaseAngularVelocityKey; }
      inline void setIncreaseAngularVelocityKey(int newKey) { m_increaseAngularVelocityKey = newKey; }

      inline const glm::vec2& getLinearVelocityDelta() const { return m_linearVelocityDelta; }
      inline void setLinearVelocityDelta(const glm::vec2& velocityDelta) { m_linearVelocityDelta = velocityDelta; }
      inline void setLinearVelocityDelta(float xDelta, float yDelta) { setLinearVelocityDelta(glm::vec2(xDelta, yDelta)); }
      inline void setLinearVelocityDelta(float delta) { setLinearVelocityDelta(glm::vec2(delta, delta)); }

      inline float getAngularVelocityDelta() const { return m_angularVelocityDelta; }
      inline void setAngularVelocityDelta(float angularDelta) { m_angularVelocityDelta = angularDelta; }

      inline Maths::Space getSpace() const { return m_space; }
      inline void setSpace(Maths::Space space) { m_space = space; }

      inline IncrementMode getIncrementMode() const { return m_incrementMode; }
      inline void setIncrementMode(IncrementMode incrementMode) { m_incrementMode = incrementMode; }

      CelesteDllExport void handleInput() override;

    private:
      using Inherited = Script;

      void begin();

      bool m_begun = false;
      observer_ptr<Physics::RigidBody2D> m_rigidBody2D;

      int m_decreaseXLinearVelocityKey;
      int m_increaseXLinearVelocityKey;
      int m_decreaseYLinearVelocityKey;
      int m_increaseYLinearVelocityKey;

      int m_decreaseAngularVelocityKey;
      int m_increaseAngularVelocityKey;

      glm::vec2 m_linearVelocityDelta;
      float m_angularVelocityDelta;

      /// The space we will perform rigidbody alterations in.
      /// Default is kLocal.
      Maths::Space m_space;

      /// How we alter the rigid body's velocities
      /// Toggle is either applies the appropriate delta or not, whereas Increment will add/subtract from a cumulative total
      IncrementMode m_incrementMode;
  };
}