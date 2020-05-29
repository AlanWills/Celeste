#pragma once

#include "System/ISystem.h"
#include "PhysicsUtils.h"
#include "SimulatedBody.h"


namespace Celeste::Physics
{
  class Collider;
  class RigidBody2D;

  class PhysicsManager : public System::ISystem
  {
    public:
      CelesteDllExport PhysicsManager();
      CelesteDllExport ~PhysicsManager() override;

      PhysicsManager(const PhysicsManager&) = delete;
      PhysicsManager& operator=(const PhysicsManager&) = delete;

      float getGravityScale() const { return m_gravityScale; }
      void setGravityScale(float gravityScale) { m_gravityScale = gravityScale; }

      size_t getSimulatedBodiesSize() const { return m_simulatedBodies.size(); }
      void clearSimulatedBodies() { m_simulatedBodies.clear(); }

      CelesteDllExport void addSimulatedBody(Collider& collider);
      CelesteDllExport void addSimulatedBody(RigidBody2D& rigidBody);
      CelesteDllExport void addSimulatedBody(Collider& collider, RigidBody2D& rigidBody);

      CelesteDllExport void update(float elapsedGameTime) override;

    private:
      using Inherited = System::ISystem;
      using SimulatedBodies = std::vector<SimulatedBody>;

      void doCollision(SimulatedBody& body, Collider& collider);

      float m_gravityScale;
      SimulatedBodies m_simulatedBodies;
  };
}