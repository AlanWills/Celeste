#include "Input/KeyboardTransformer.h"
#include "Input/InputManager.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace Celeste::Input
{
  REGISTER_COMPONENT(KeyboardTransformer, 10)

  //------------------------------------------------------------------------------------------------
  KeyboardTransformer::KeyboardTransformer(GameObject& gameObject) :
    Inherited(gameObject),
    m_translateLeftKey(GLFW_KEY_A),
    m_translateRightKey(GLFW_KEY_D),
    m_translateUpKey(GLFW_KEY_W),
    m_translateDownKey(GLFW_KEY_S),
    m_rotateLeftKey(GLFW_KEY_Q),
    m_rotateRightKey(GLFW_KEY_E),
    m_translationSpeed(1),
    m_rotationSpeed(0.01f),
    m_directionVector(),
    m_deltaRotation(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardTransformer::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

#if _DEBUG
    if (getGameObject().getTransform() == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    // Zero the direction and rotation delta again
    m_directionVector = glm::vec2();
    m_deltaRotation = 0;

    const Keyboard& keyboard = getKeyboard();

    // Only support one left/right key pressed
    if (keyboard.isKeyPressed(m_translateRightKey))
    {
      // Move along +ve local space x axis (right in local space)
      m_directionVector += glm::vec2(1, 0);
    }

    if (keyboard.isKeyPressed(m_translateLeftKey))
    {
      // Move along -ve local space x axis (left in local space)
      m_directionVector -= glm::vec2(1, 0);
    }

    if (keyboard.isKeyPressed(m_translateUpKey))
    {
      // Move along +ve local space y axis (up in local space)
      m_directionVector += glm::vec2(0, 1);
    }

    if (keyboard.isKeyPressed(m_translateDownKey))
    {
      // Move along -+ve local space y axis (down in local space)
      m_directionVector -= glm::vec2(0, 1);
    }

    if (keyboard.isKeyPressed(m_rotateLeftKey))
    {
      // Rotate left (-ve)
      m_deltaRotation -= 1;
    }

    if (keyboard.isKeyPressed(m_rotateRightKey))
    {
      // Rotate right (+ve)
      m_deltaRotation += 1;
    }

    observer_ptr<Transform> transform = getGameObject().getTransform();

    if (m_deltaRotation != 0)
    {
      transform->rotate(m_deltaRotation * m_rotationSpeed * elapsedGameTime);
    }

    if (m_directionVector != glm::vec2())
    {
      const glm::mat4& localMat = transform->getLocalMatrix();

      transform->translate(glm::vec3(m_directionVector.x * localMat[0] + m_directionVector.y * localMat[1]) * m_translationSpeed * elapsedGameTime);
    }
  }
}