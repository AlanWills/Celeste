#pragma once

#include "CelesteStl/Memory/ObserverPtr.h"

#include <vector>


namespace Celeste::Physics
{
  class Collider;
  class RigidBody2D;

  // Simulated body
  // Has collider
  // Rigidbody
  // And vector of colliders which it collided with last frame
  struct SimulatedBody
  {
    SimulatedBody(observer_ptr<Collider> collider, observer_ptr<RigidBody2D> rigidBody) :
      m_collider(collider),
      m_rigidBody(rigidBody),
      m_collidersLastFrame(),
      m_collidersThisFrame()
    {
    }

    observer_ptr<Collider> m_collider;
    observer_ptr<RigidBody2D> m_rigidBody;
    std::vector<observer_ptr<Collider>> m_collidersLastFrame;
    std::vector<observer_ptr<Collider>> m_collidersThisFrame;
  };
}