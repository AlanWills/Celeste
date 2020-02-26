#pragma once

#include "Objects/Entity.h"
#include "PhysicsUtils.h"
#include "SimulatedBody.h"


namespace Celeste::Physics
{
  class Collider;
  class RigidBody2D;

  class PhysicsManager : public Entity
  {
    public:
      CelesteDllExport PhysicsManager();
      PhysicsManager(const PhysicsManager&) = delete;
      PhysicsManager& operator=(const PhysicsManager&) = delete;

      float getGravityScale() const { return m_gravityScale; }
      void setGravityScale(float gravityScale) { m_gravityScale = gravityScale; }

      size_t getSimulatedBodiesSize() const { return m_simulatedBodies.size(); }
      void clearSimulatedBodies() { m_simulatedBodies.clear(); }

      CelesteDllExport void addSimulatedBody(Collider& collider);
      CelesteDllExport void addSimulatedBody(RigidBody2D& rigidBody);
      CelesteDllExport void addSimulatedBody(Collider& collider, RigidBody2D& rigidBody);

    protected:
      void onHandleInput() override;
      void onUpdate(float elapsedGameTime) override;
      void onDeath() override;

    private:
      using Inherited = Entity;
      using SimulatedBodies = std::vector<SimulatedBody>;

      void doCollision(SimulatedBody& body, Collider& collider);

      float m_gravityScale;
      SimulatedBodies m_simulatedBodies;
  };
}