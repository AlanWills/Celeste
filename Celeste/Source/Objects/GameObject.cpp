#include "Objects/GameObject.h"
#include "Rendering/SpriteBatch.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace Celeste
{
  CUSTOM_MEMORY_CREATION(GameObject, 100);

  //------------------------------------------------------------------------------------------------
  GameObject::GameObject() :
    m_transform(new Transform(*this)),
    m_name(0),
    m_tag(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  GameObject::~GameObject()
  {
    // Deleting game objects is going to invalidate iterators, so we cache the children here before deleting
    std::vector<GameObject*> children;
    for (GameObject* child : *this)
    {
      children.push_back(child);
    }

    for (GameObject* gameObject : children)
    {
      delete gameObject;
    }

    m_transform.reset();

    // Iterate in reverse so components can remove themselves from the m_managedComponents vector
    for (size_t i = m_managedComponents.size(); i > 0; --i)
    {
      delete m_managedComponents[i - 1];
    }

    // Iterate in reverse so components can remove themselves from the m_unmanagedComponents vector
    for (size_t i = m_unmanagedComponents.size(); i > 0; --i)
    {
      delete m_unmanagedComponents[i - 1];
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::collisionEnter(Physics::Collider& collider)
  {
    for (Component* component : m_managedComponents)
    {
      if (component->isActive())
      {
        component->collisionEnter(collider);
      }
    }

    for (Component* component : m_unmanagedComponents)
    {
      if (component->isActive())
      {
        component->collisionEnter(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::collision(Physics::Collider& collider)
  {
    for (Component* component : m_managedComponents)
    {
      if (component->isActive())
      {
        component->collision(collider);
      }
    }

    for (Component* component : m_unmanagedComponents)
    {
      if (component->isActive())
      {
        component->collision(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::collisionExit(Physics::Collider& collider)
  {
    for (Component* component : m_managedComponents)
    {
      if (component->isActive())
      {
        component->collisionExit(collider);
      }
    }

    for (Component* component : m_unmanagedComponents)
    {
      if (component->isActive())
      {
        component->collisionExit(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::triggerEnter(Physics::Collider& collider)
  {
    for (Component* component : m_managedComponents)
    {
      if (component->isActive())
      {
        component->triggerEnter(collider);
      }
    }

    for (Component* component : m_unmanagedComponents)
    {
      if (component->isActive())
      {
        component->triggerEnter(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::trigger(Physics::Collider& collider)
  {
    for (Component* component : m_managedComponents)
    {
      if (component->isActive())
      {
        component->trigger(collider);
      }
    }
    
    for (Component* component : m_unmanagedComponents)
    {
      if (component->isActive())
      {
        component->trigger(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::triggerExit(Physics::Collider& collider)
  {
    for (Component* component : m_managedComponents)
    {
      if (component->isActive())
      {
        component->triggerExit(collider);
      }
    }

    for (Component* component : m_unmanagedComponents)
    {
      if (component->isActive())
      {
        component->triggerExit(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::handleInput()
  {
    Inherited::handleInput();

    // Act on a copy so we can remove components during the handle input step
    for (Component* component : std::vector<Component*>(m_unmanagedComponents))
    {
      if (component->isActive())
      {
        component->handleInput();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::update(GLfloat elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    // Act on a copy so we can remove components during the update step
    for (Component* component : std::vector<Component*>(m_unmanagedComponents))
    {
      if (component->isActive())
      {
        component->update(elapsedGameTime);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::setActive(bool isActive)
  {
    Inherited::setActive(isActive);

    for (Component* component : m_managedComponents)
    {
      component->setActive(isActive);
    }

    for (Component* component : m_unmanagedComponents)
    {
      component->setActive(isActive);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::render(Rendering::SpriteBatch& spriteBatch, float lag)
  {
    glm::vec3 worldTranslation = getTransform()->getWorldTranslation();
    float worldRotation = getTransform()->getWorldRotation();
    const glm::vec3& worldScale = getTransform()->getWorldScale();

    // Render Sprites
    {
      Rendering::SpriteRenderer* spriteRenderer = findComponent<Rendering::SpriteRenderer>();
      if (spriteRenderer != nullptr && spriteRenderer->isActive())
      {
        spriteBatch.render(*spriteRenderer, worldTranslation, worldRotation, worldScale * glm::vec3(spriteRenderer->getDimensions(), 1));
      }
    }

    // Render Text
    {
      Rendering::TextRenderer* textRenderer = findComponent<Rendering::TextRenderer>();
      if (textRenderer != nullptr && textRenderer->isActive())
      {
        spriteBatch.render(*textRenderer, worldTranslation, worldRotation, worldScale);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  GameObject* GameObject::findChild(StringId name)
  { 
    for (GameObject* gameObject : *this)
    {
      if (gameObject->getName() == name)
      {
        return gameObject;
      }
    }

    return nullptr;
  }

  //------------------------------------------------------------------------------------------------
  Component* GameObject::getComponent(size_t index)
  {
    ASSERT(index < getComponentCount());
    if (index < m_managedComponents.size())
    {
      return m_managedComponents[index];
    }
    else if (index < (m_managedComponents.size() + m_unmanagedComponents.size()))
    {
      return m_unmanagedComponents[index - m_managedComponents.size()];
    }

    return nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::removeComponent(Component* component)
  {
#if _DEBUG
    if (component == nullptr || 
        this != component->getGameObject())
    {
      ASSERT_FAIL();
      return;
    }
#endif
    
    if (auto componentIt = std::find(m_managedComponents.begin(), m_managedComponents.end(), component); componentIt != m_managedComponents.end())
    {
      component->setActive(false);
      m_managedComponents.erase(componentIt);
    }
    else if (auto componentIt = std::find(m_unmanagedComponents.begin(), m_unmanagedComponents.end(), component); componentIt != m_unmanagedComponents.end())
    {
      component->setActive(false);
      m_unmanagedComponents.erase(componentIt);
    }
#if _DEBUG
    else
    {
      ASSERT_FAIL();
    }
#endif
  }
}