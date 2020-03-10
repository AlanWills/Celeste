#include "Maths/Transform.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Transform::Allocator Transform::m_allocator(500);

  //------------------------------------------------------------------------------------------------
  Transform::Transform() :
    m_gameObject(nullptr),
    m_parent(nullptr),
    m_rotation(0),
    m_translation(glm::zero<glm::vec3>()),
    m_scale(glm::one<glm::vec3>())
  {
  }

  //------------------------------------------------------------------------------------------------
  Transform::Transform(GameObject& gameObject) :
    m_gameObject(&gameObject),
    m_parent(nullptr),
    m_rotation(0),
    m_translation(glm::zero<glm::vec3>()),
    m_scale(glm::one<glm::vec3>())
  {
  }

  //------------------------------------------------------------------------------------------------
  Transform::~Transform()
  {
    if (hasParent())
    {
      // Remove from parent
      m_parent->m_children.erase(std::remove(m_parent->m_children.begin(), m_parent->m_children.end(), this));
    }
  }

  //------------------------------------------------------------------------------------------------
  void* Transform::operator new(size_t)
  {
    ASSERT(m_allocator.canAllocate(1));
    return m_allocator.allocate();
  }

  //------------------------------------------------------------------------------------------------
  void Transform::operator delete(void* memory)
  {
    Transform& transform = *static_cast<Transform*>(memory);
    ASSERT(m_allocator.isAllocated(transform));

    if (m_allocator.isAllocated(transform))
    {
      m_allocator.deallocate(transform);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Transform::setParent(Transform* parent)
  {
    if (parent == this)
    {
      ASSERT_FAIL();
      return;
    }

    if (m_parent == parent)
    {
      // Optimisation if parents are equal
      // Saves us erasing and then re-adding this to the parent's children
      return;
    }

    if (hasParent())
    {
      m_parent->m_children.erase(std::remove(m_parent->m_children.begin(), m_parent->m_children.end(), this));
    }

    m_parent = parent;

    if (hasParent())
    {
      m_parent->m_children.push_back(this);
    }
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Transform::getWorldMatrix() const
  {
    if (!hasParent())
    {
      return getLocalMatrix();
    }

    return createMatrix(getWorldTranslation(), getWorldRotation(), getWorldScale());
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Transform::getInverseWorldMatrix() const
  {
    if (!hasParent())
    {
      return getInverseLocalMatrix();
    }

    return createInverseMatrix(getInverseWorldTranslation(), getInverseWorldRotation(), getInverseWorldScale());
  }

  //------------------------------------------------------------------------------------------------
  void Transform::setWorldRotation(float rotation)
  {
    if (!hasParent())
    {
      setRotation(rotation);
    }
    else
    {
      setRotation(rotation - m_parent->getWorldRotation());
    }
  }

  //------------------------------------------------------------------------------------------------
  float Transform::getWorldRotation() const
  {
    return !hasParent() ? m_rotation : m_parent->getWorldRotation() + m_rotation;
  }

  //------------------------------------------------------------------------------------------------
  void Transform::setWorldTranslation(const glm::vec3& translation)
  {
    if (!hasParent())
    {
      setTranslation(translation);
    }
    else
    {
      setTranslation(translation - m_parent->getWorldTranslation());
    }
  }

  //------------------------------------------------------------------------------------------------
  glm::vec3 Transform::getWorldTranslation() const
  {
    return !hasParent() ? m_translation : m_parent->getWorldTranslation() + m_translation;
  }

  //------------------------------------------------------------------------------------------------
  void Transform::setWorldScale(const glm::vec3& scale)
  {
    if (!hasParent())
    {
      setScale(scale);
    }
    else
    {
      setScale(scale / m_parent->getWorldScale());
    }
  }

  //------------------------------------------------------------------------------------------------
  glm::vec3 Transform::getWorldScale() const
  {
    return !hasParent() ? m_scale : m_parent->getWorldScale() * m_scale;
  }
}