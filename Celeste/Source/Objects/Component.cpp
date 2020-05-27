#include "Objects/Component.h"
#include "Maths/Transform.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Component::Component(GameObject& gameObject) :
    m_gameObject(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  Component::~Component()
  {
    m_gameObject.removeComponent(this);
  }

  //------------------------------------------------------------------------------------------------
  Transform* Component::getTransform()
  {
    return m_gameObject.getTransform();
  }
}