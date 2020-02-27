#include "Animation/Animators/MoveToPositionAnimator.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Physics/RigidBody2D.h"
#include "Maths/Vector.h"


namespace Celeste::Animators
{
  REGISTER_SCRIPT(MoveToPositionAnimator, 10);

  //------------------------------------------------------------------------------------------------
  MoveToPositionAnimator::MoveToPositionAnimator() :
    m_time(0),
    m_elapsedTime(0),
    m_targetPosition(),
    m_startingPosition()
  {
  }

  //------------------------------------------------------------------------------------------------
  void MoveToPositionAnimator::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

#if _DEBUG
    observer_ptr<GameObject> gameObject = getGameObject();
    if (gameObject == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    m_elapsedTime += elapsedGameTime;
    glm::vec3 newTranslation = (m_time == 0 || m_elapsedTime > m_time) ? m_targetPosition : m_startingPosition + ((m_targetPosition - m_startingPosition) * m_elapsedTime / m_time);
    gameObject->getTransform()->setTranslation(newTranslation);

    if (m_elapsedTime >= m_time)
    {
      // Animation complete
      setActive(false);
    }
  }

  //------------------------------------------------------------------------------------------------
  void MoveToPositionAnimator::setTargetPosition(const glm::vec3& targetPosition)
  {
    m_targetPosition = targetPosition;
    reset();
  }

  //------------------------------------------------------------------------------------------------
  void MoveToPositionAnimator::reset()
  {
    if (getGameObject() != nullptr)
    {
      m_startingPosition = getGameObject()->getTransform()->getTranslation();
    }

    m_elapsedTime = 0;
  }
}