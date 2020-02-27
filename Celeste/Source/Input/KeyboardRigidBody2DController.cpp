#include "Input/KeyboardRigidBody2DController.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Physics/RigidBody2D.h"
#include "Input/InputManager.h"


namespace Celeste::Input
{
  REGISTER_SCRIPT(KeyboardRigidBody2DController, 10)

  //------------------------------------------------------------------------------------------------
  KeyboardRigidBody2DController::KeyboardRigidBody2DController() :
    m_rigidBody2D(),
    m_decreaseXLinearVelocityKey(-1),
    m_increaseXLinearVelocityKey(-1),
    m_decreaseYLinearVelocityKey(-1),
    m_increaseYLinearVelocityKey(-1),
    m_decreaseAngularVelocityKey(-1),
    m_increaseAngularVelocityKey(-1),
    m_linearVelocityDelta(1, 1),
    m_angularVelocityDelta(0.1f),
    m_space(Maths::Space::kLocal),
    m_incrementMode(IncrementMode::kContinuous)
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardRigidBody2DController::onSetGameObject(GameObject& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    m_rigidBody2D = getGameObject()->findComponent<Physics::RigidBody2D>();
    ASSERT(m_rigidBody2D != nullptr);
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardRigidBody2DController::handleInput()
  {
    Inherited::handleInput();

#if _DEBUG
    if (m_rigidBody2D == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    // Translate the object in the appropriate space we have chosen
    glm::mat4 matrix = m_space == Maths::Space::kLocal ? getTransform()->getLocalMatrix() : getTransform()->getWorldMatrix();
    const Keyboard& keyboard = getKeyboard();

    glm::vec2 deltaLinear;
    float deltaAngular = 0;

    if (keyboard.isKeyPressed(m_decreaseXLinearVelocityKey))
    {
      deltaLinear.x -= m_linearVelocityDelta.x;
    }

    if (keyboard.isKeyPressed(m_increaseXLinearVelocityKey))
    {
      deltaLinear.x += m_linearVelocityDelta.x;
    }

    if (keyboard.isKeyPressed(m_decreaseYLinearVelocityKey))
    {
      deltaLinear.y -= m_linearVelocityDelta.y;
    }

    if (keyboard.isKeyPressed(m_increaseYLinearVelocityKey))
    {
      deltaLinear.y += m_linearVelocityDelta.y;
    }

    if (keyboard.isKeyPressed(m_decreaseAngularVelocityKey))
    {
      deltaAngular -= m_angularVelocityDelta;
    }

    if (keyboard.isKeyPressed(m_increaseAngularVelocityKey))
    {
      deltaAngular += m_angularVelocityDelta;
    }

    if (m_incrementMode == IncrementMode::kToggle)
    {
      m_rigidBody2D->setLinearVelocity(glm::vec2(deltaLinear.x * matrix[0]) + glm::vec2(deltaLinear.y * matrix[1]));
      m_rigidBody2D->setAngularVelocity(deltaAngular);
    }
    else
    {
      if (deltaLinear != glm::vec2())
      {
        m_rigidBody2D->incrementLinearVelocity(glm::vec2(deltaLinear.x * matrix[0]) + glm::vec2(deltaLinear.y * matrix[1]));
      }

      if (deltaAngular != 0)
      {
        m_rigidBody2D->incrementAngularVelocity(deltaAngular);
      }
    }
  }
}