#include "Physics/PhysicsManager.h"
#include "Physics/RigidBody2D.h"
#include "Physics/RectangleCollider.h"
#include "Physics/EllipseCollider.h"
#include "Physics/Collider.h"
#include "Objects/GameObject.h"


namespace Celeste::Physics
{
  //------------------------------------------------------------------------------------------------
  PhysicsManager::PhysicsManager() :
    m_gravityScale(9.81f),
    m_simulatedBodies()
  {
  }

  //------------------------------------------------------------------------------------------------
  PhysicsManager::~PhysicsManager()
  {
    RigidBody2D::m_componentAllocator.deallocateAll();
    RectangleCollider::m_componentAllocator.deallocateAll();
    EllipseCollider::m_componentAllocator.deallocateAll();
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::handleInput()
  {
    Inherited::handleInput();

    RigidBody2D::m_componentAllocator.handleInput();
    RectangleCollider::m_componentAllocator.handleInput();
    EllipseCollider::m_componentAllocator.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    RectangleCollider::m_componentAllocator.update(elapsedGameTime);
    EllipseCollider::m_componentAllocator.update(elapsedGameTime);

    if (!m_simulatedBodies.empty())
    {
      m_simulatedBodies.erase(std::remove_if(m_simulatedBodies.begin(), m_simulatedBodies.end(), [](const SimulatedBody& body) -> bool
        {
          return body.m_collider == nullptr && body.m_rigidBody == nullptr;
        }), m_simulatedBodies.end());
    }

    for (SimulatedBody& body : m_simulatedBodies)
    {
      // Gravity
      if (body.m_rigidBody != nullptr && body.m_rigidBody->isActive() && m_gravityScale != 0)
      {
        // Acceleration due to gravity - DO multiply by time
        body.m_rigidBody->incrementLinearVelocity(0, -m_gravityScale * elapsedGameTime * 40);
      }

      // Update the last frame collisions
      body.m_collidersLastFrame.assign(body.m_collidersThisFrame.begin(), body.m_collidersThisFrame.end());
      body.m_collidersThisFrame.clear();

      if (body.m_collider == nullptr || !body.m_collider->isActive())
      {
        // Body collider is null or not active, so don't include it in simulation
        continue;
      }

      // Possible improvement here - go through all colliders once before iterating over bodies and quad tree them
      // Then this narrows down the colliders we have to search through to check for intersection
      // But can use last frames collisions to work out exits/entries too
      // Will avoid quadratic algorithm

      for (RectangleCollider& collider : RectangleCollider::m_componentAllocator)
      {
        doCollision(body, collider);
      }

      for (EllipseCollider& collider : EllipseCollider::m_componentAllocator)
      {
        doCollision(body, collider);
      }
    }

    RigidBody2D::m_componentAllocator.update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::addSimulatedBody(Collider& collider)
  {
    // Check to see if body already exists?
    m_simulatedBodies.emplace_back(&collider, observer_ptr<RigidBody2D>());
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::addSimulatedBody(RigidBody2D& rigidBody)
  {
    // Check to see if body already exists?
    m_simulatedBodies.emplace_back(observer_ptr<Collider>(), &rigidBody);
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::addSimulatedBody(Collider& collider, RigidBody2D& rigidBody)
  {
    // Check to see if body already exists?
    m_simulatedBodies.emplace_back(&collider, &rigidBody);
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::doCollision(SimulatedBody& body, Collider& collider)
  {
    if (!collider.isActive() || body.m_collider == &collider)
    {
      // This collider is not active or is the same collider, so don't include it in simulation
      return;
    }

    if (collider.intersects(*body.m_collider))
    {
      // Add this collider to the rigidbody's latest collisions
      body.m_collidersThisFrame.push_back(&collider);

      // Collider intersects body
      if (collider.getColliderType() == ColliderType::kTrigger)
      {
        // Collider is a trigger, so we don't care about physics simulation
        if (std::find(body.m_collidersLastFrame.begin(), body.m_collidersLastFrame.end(), &collider) == body.m_collidersLastFrame.end())
        {
          // Body hasn't collided before so we call the trigger enter function
          body.m_collider->getGameObject()->triggerEnter(collider);
        }

        body.m_collider->getGameObject()->trigger(collider);
      }
      else
      {
        if (body.m_collider->getColliderType() != ColliderType::kTrigger && body.m_rigidBody != nullptr)
        {
          // We have intersected a collider and the simulated body is also a collider
          // We therefore adjust the position of the simulated body accordingly
          glm::vec2 newVelocity = body.m_rigidBody->getLinearVelocity();

          if (collider.getCentre().x < body.m_collider->getCentre().x)
          {
            // Body has moved left into a collider
            newVelocity.x = std::max(newVelocity.x, 0.0f);
          }
          else
          {
            // Body has moved right into a collider
            newVelocity.x = std::min(newVelocity.x, 0.0f);
          }

          if (collider.getCentre().y < body.m_collider->getCentre().y)
          {
            // Body has moved down into a collider
            newVelocity.y = std::max(newVelocity.y, 0.0f);
          }
          else
          {
            // Body has moved up into a collider
            newVelocity.y = std::min(newVelocity.y, 0.0f);
          }

          body.m_rigidBody->setLinearVelocity(newVelocity);
        }

        if (std::find(body.m_collidersLastFrame.begin(), body.m_collidersLastFrame.end(), &collider) == body.m_collidersLastFrame.end())
        {
          body.m_collider->getGameObject()->collisionEnter(collider);
        }
      }

      body.m_collider->getGameObject()->collision(collider);
    }
    else if (std::find(body.m_collidersLastFrame.begin(), body.m_collidersLastFrame.end(), &collider) != body.m_collidersLastFrame.end())
    {
      // Body intersected collider last frame so call exit based on collider type
      if (collider.getColliderType() == ColliderType::kTrigger)
      {
        body.m_collider->getGameObject()->triggerExit(collider);
      }
      else
      {
        body.m_collider->getGameObject()->collisionExit(collider);
      }
    }
  }
}