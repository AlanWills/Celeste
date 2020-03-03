#include "Objects/Component.h"
#include "Maths/Transform.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Component::Component()
  {
  }

  //------------------------------------------------------------------------------------------------
  Component::~Component()
  {
    if (m_gameObject != nullptr)
    {
      m_gameObject->removeComponent(this);
      m_gameObject = nullptr;
    }
  }

  //------------------------------------------------------------------------------------------------
  Transform* Component::getTransform()
  {
    ASSERT_NOT_NULL(m_gameObject);
    return m_gameObject != nullptr ? m_gameObject->getTransform() : nullptr;
  }
}