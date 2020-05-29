#include "Animation/Animators/MoveToPositionAnimator.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Physics/RigidBody2D.h"
#include "Maths/Vector.h"
#include "Time/TimeUtils.h"


namespace Celeste::Animators
{
  REGISTER_COMPONENT(MoveToPositionAnimator, 10);

  //------------------------------------------------------------------------------------------------
  MoveToPositionAnimator::MoveToPositionAnimator(GameObject& gameObject) :
    Inherited(gameObject),
    m_time(0),
    m_elapsedTime(0),
    m_targetPosition(),
    m_startingPosition()
  {
  }

  //------------------------------------------------------------------------------------------------
  void MoveToPositionAnimator::update()
  {
    Inherited::update();

    m_elapsedTime += Time::getElapsedDeltaTime();
    glm::vec3 newTranslation = (m_time == 0 || m_elapsedTime > m_time) ? m_targetPosition : m_startingPosition + ((m_targetPosition - m_startingPosition) * m_elapsedTime / m_time);
    getGameObject().getTransform()->setTranslation(newTranslation);

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
    m_startingPosition = getGameObject().getTransform()->getTranslation();
    m_elapsedTime = 0;
  }
}