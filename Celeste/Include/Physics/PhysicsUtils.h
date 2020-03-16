#pragma once

#include "CelesteDllExport.h"


namespace Celeste::Physics
{
  class PhysicsManager;
  class Collider;
  class RigidBody2D;

  //------------------------------------------------------------------------------------------------
  CelesteDllExport PhysicsManager& getPhysicsManager();

  //------------------------------------------------------------------------------------------------
  CelesteDllExport void addSimulatedBody(Collider& collider);

  //------------------------------------------------------------------------------------------------
  CelesteDllExport void addSimulatedBody(RigidBody2D& rigidBody);

  //------------------------------------------------------------------------------------------------
  CelesteDllExport void addSimulatedBody(Collider& collider, RigidBody2D& rigidBody);

  //------------------------------------------------------------------------------------------------
  CelesteDllExport void clearSimulatedBodies();
}