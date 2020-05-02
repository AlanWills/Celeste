#include "Physics/PhysicsUtils.h"
#include "Physics/PhysicsManager.h"
#include "Game/Game.h"


namespace Celeste::Physics
{
  //------------------------------------------------------------------------------------------------
  PhysicsManager& getPhysicsManager()
  {
    return *Game::current().getSystem<Physics::PhysicsManager>();
  }

  //------------------------------------------------------------------------------------------------
  void addSimulatedBody(Collider& collider)
  {
    getPhysicsManager().addSimulatedBody(collider);
  }

  //------------------------------------------------------------------------------------------------
  void addSimulatedBody(RigidBody2D& rigidBody)
  {
    getPhysicsManager().addSimulatedBody(rigidBody);
  }

  //------------------------------------------------------------------------------------------------
  void addSimulatedBody(Collider& collider, RigidBody2D& rigidBody)
  {
    getPhysicsManager().addSimulatedBody(collider, rigidBody);
  }

  //------------------------------------------------------------------------------------------------
  void clearSimulatedBodies()
  {
    getPhysicsManager().clearSimulatedBodies();
  }
}