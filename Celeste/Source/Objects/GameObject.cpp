#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  GameObject::GameObject() :
    m_transform(),
    m_name(0),
    m_tag(0),
    m_screen()
  {
    ASSERT(Transform::canAllocate());
    m_transform = Transform::allocate(*this);
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::collisionEnter(Physics::Collider& collider)
  {
    for (Component* component : m_components)
    {
      if (component->isActive())
      {
        component->collisionEnter(collider);
      }
    }

    for (Component* script : m_scripts)
    {
      if (script->isActive())
      {
        script->collisionEnter(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::collision(Physics::Collider& collider)
  {
    for (Component* component : m_components)
    {
      if (component->isActive())
      {
        component->collision(collider);
      }
    }

    for (Component* script : m_scripts)
    {
      if (script->isActive())
      {
        script->collision(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::collisionExit(Physics::Collider& collider)
  {
    for (Component* component : m_components)
    {
      if (component->isActive())
      {
        component->collisionExit(collider);
      }
    }

    for (Component* script : m_scripts)
    {
      if (script->isActive())
      {
        script->collisionExit(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::triggerEnter(Physics::Collider& collider)
  {
    for (Component* component : m_components)
    {
      if (component->isActive())
      {
        component->triggerEnter(collider);
      }
    }

    for (Component* script : m_scripts)
    {
      if (script->isActive())
      {
        script->triggerEnter(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::trigger(Physics::Collider& collider)
  {
    for (Component* component : m_components)
    {
      if (component->isActive())
      {
        component->trigger(collider);
      }
    }
    
    for (Component* script : m_scripts)
    {
      if (script->isActive())
      {
        script->trigger(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::triggerExit(Physics::Collider& collider)
  {
    for (Component* component : m_components)
    {
      if (component->isActive())
      {
        component->triggerExit(collider);
      }
    }

    for (Component* script : m_scripts)
    {
      if (script->isActive())
      {
        script->triggerExit(collider);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::onHandleInput()
  {
    Inherited::onHandleInput();

    // Act on a copy so we can remove components during the handle input step
    for (Component* script : std::vector<Component*>(m_scripts))
    {
      if (script->isActive())
      {
        script->handleInput();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::onUpdate(GLfloat elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    // Act on a copy so we can remove components during the update step
    for (Component* script : std::vector<Component*>(m_scripts))
    {
      if (script->isActive())
      {
        script->update(elapsedGameTime);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::onDeath()
  {
    Inherited::onDeath();

    for (Component* component : m_components)
    {
      if (component->isAlive())
      {
        component->die();
      }
    }

    for (Component* script : m_scripts)
    {
      if (script->isAlive())
      {
        script->die();
      }
    }

    m_name = 0;
    m_tag = 0;
  }

  //------------------------------------------------------------------------------------------------
  void GameObject::setActive(bool isActive)
  {
    Inherited::setActive(isActive);

    for (Component* component : m_components)
    {
      component->setActive(isActive);
    }

    for (Component* script : m_scripts)
    {
      script->setActive(isActive);
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
  bool GameObject::deallocate()
  {
    for (Component* component : m_components)
    {
      component->deallocate();
    }

    for (Component* component : m_scripts)
    {
      component->deallocate();
    }

    Transform* transform = m_transform;
    m_transform = nullptr;

    if (transform != nullptr && transform->getGameObject() != nullptr)
    {
      // If the transform's gameobject is nullptr, it means it's already been deallocated
      transform->deallocate();
    }

    if (m_screen == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    if (!m_screen->deallocateGameObject(*this))
    {
      ASSERT_FAIL();
      return false;
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  GameObject* GameObject::findChildGameObject(StringId name)
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
  GameObject* GameObject::allocateGameObjectInScreen()
  {
    return m_screen != nullptr ? m_screen->allocateGameObject() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  GameObject* GameObject::allocateGameObjectInScreen(Transform& parentTransform)
  {
    return m_screen != nullptr ? m_screen->allocateGameObject(parentTransform) : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  Component* GameObject::getComponent(size_t index)
  {
    ASSERT(index < getComponentCount());
    if (index < m_components.size())
    {
      return m_components[index];
    }
    else if (index < (m_components.size() + m_scripts.size()))
    {
      return m_scripts[index - m_components.size()];
    }

    return nullptr;
  }

  //------------------------------------------------------------------------------------------------
  Component* GameObject::removeComponent(Component* component)
  {
#if _DEBUG
    if (component == nullptr || 
        this != component->getGameObject())
    {
      ASSERT_FAIL();
      return component;
    }
#endif
    
    if (auto componentIt = std::find(m_components.begin(), m_components.end(), component); componentIt != m_components.end())
    {
      component->setActive(false);
      m_components.erase(componentIt);
    }
    else if (auto scriptIt = std::find(m_scripts.begin(), m_scripts.end(), component); scriptIt != m_scripts.end())
    {
      component->setActive(false);
      m_scripts.erase(scriptIt);
    }
#if _DEBUG
    else
    {
      ASSERT_FAIL();
    }
#endif

    return component;
  }
}