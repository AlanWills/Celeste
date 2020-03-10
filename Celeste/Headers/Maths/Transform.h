#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"
#include "Matrix.h"
#include "Objects/Object.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "UtilityMacros/CustomMemoryMacros.h"

#include <vector>


namespace Celeste
{
  class GameObject;

  /// A class representing a transformation in 3D space with various utility functions for manipulation and hierarchy.
  class Transform : public Object
  {
    CUSTOM_MEMORY_DECLARATION(Transform, CelesteDllExport);

    public:
      CelesteDllExport Transform();
      CelesteDllExport ~Transform() override;

      inline bool hasParent() const { return m_parent != nullptr; }
      CelesteDllExport void setParent(Transform* parent);
      inline Transform* getParent() { return m_parent; }
      inline const Transform* getParent() const { return const_cast<Transform*>(this)->getParent(); }

      inline GameObject* getGameObject() { return m_gameObject; }
      inline CelesteDllExport const GameObject* getGameObject() const { return const_cast<Transform*>(this)->getGameObject(); }

      inline size_t getChildCount() const { return m_children.size(); }

      inline Transform* getChildTransform(size_t index)
      {
        ASSERT(index < m_children.size());
        return index < m_children.size() ? m_children[index] : nullptr;
      }
      inline CelesteDllExport const Transform* getChildTransform(size_t index) const { return const_cast<Transform*>(this)->getChildTransform(index); }

      inline GameObject* getChildGameObject(size_t index)
      {
        ASSERT(index < m_children.size());
        return index < m_children.size() ? m_children[index]->getGameObject() : nullptr;
      }
      inline CelesteDllExport const GameObject* getChildGameObject(size_t index) const { return const_cast<Transform*>(this)->getChildGameObject(index); }

      inline std::vector<Transform*>::const_iterator begin() const { return m_children.begin(); }
      inline std::vector<Transform*>::const_iterator end() const { return m_children.end(); }

      CelesteDllExport glm::mat4 getWorldMatrix() const;
      CelesteDllExport glm::mat4 getInverseWorldMatrix() const;

      CelesteDllExport void setWorldRotation(float rotation);
      CelesteDllExport float getWorldRotation() const;
      float getInverseWorldRotation() const { return -getWorldRotation(); }

      void setWorldTranslation(float x, float y) { setWorldTranslation(x, y, 0); }
      void setWorldTranslation(float x, float y, float z) { setWorldTranslation(glm::vec3(x, y, z)); }
      void setWorldTranslation(const glm::vec2& translation) { setWorldTranslation(glm::vec3(translation, 0)); }
      CelesteDllExport void setWorldTranslation(const glm::vec3& translation);
      CelesteDllExport glm::vec3 getWorldTranslation() const;
      glm::vec3 getInverseWorldTranslation() const { return -getWorldTranslation(); }

      void setWorldScale(float x, float y) { setWorldScale(x, y, 1); }
      void setWorldScale(float x, float y, float z) { setWorldScale(glm::vec3(x, y, z)); }
      void setWorldScale(const glm::vec2& scaling) { setWorldScale(glm::vec3(scaling, 1)); }
      CelesteDllExport void setWorldScale(const glm::vec3& scaling);
      CelesteDllExport glm::vec3 getWorldScale() const;
      glm::vec3 getInverseWorldScale() const { return glm::vec3(1) / getWorldScale(); }

      glm::mat4 getLocalMatrix() const { return createMatrix(getTranslation(), getRotation(), getScale()); }
      glm::mat4 getInverseLocalMatrix() const { return createInverseMatrix(getInverseTranslation(), getInverseRotation(), getInverseScale()); }

      inline void rotate(float deltaRotation) { m_rotation += deltaRotation; }
      inline void setRotation(float rotation) { m_rotation = rotation; }
      inline float getRotation() const { return m_rotation; }
      inline float getInverseRotation() const { return -m_rotation; }

      inline void translate(float x, float y) { translate(x, y, 0); }
      inline void translate(float x, float y, float z) { translate(glm::vec3(x, y, z)); }
      inline void translate(const glm::vec2& translation) { translate(glm::vec3(translation, 0)); }
      inline void translate(const glm::vec3& translation) { m_translation += translation; }
    
      inline void setTranslation(float x, float y) { setTranslation(glm::vec2(x, y)); }
      inline void setTranslation(float x, float y, float z) { setTranslation(glm::vec3(x, y, z)); }
      inline void setTranslation(const glm::vec2& translation) { setTranslation(glm::vec3(translation, m_translation.z)); }
      inline void setTranslation(const glm::vec3& translation) { m_translation = translation; }
      inline const glm::vec3& getTranslation() const { return m_translation; }
      inline glm::vec3 getInverseTranslation() const { return -m_translation; }

      inline void scale(float xScalingFactor, float yScalingFactor) { scale(glm::vec3(xScalingFactor, yScalingFactor, 1)); }
      inline void scale(float xScalingFactor, float yScalingFactor, float zScalingFactor) { scale(glm::vec3(xScalingFactor, yScalingFactor, zScalingFactor)); }
      inline void scale(const glm::vec2& scalingFactor) { scale(glm::vec3(scalingFactor, 1)); }
      inline void scale(const glm::vec3& scalingFactor) { m_scale *= scalingFactor; }

      inline void setScale(float x, float y) { setScale(x, y, 1); }
      inline void setScale(float x, float y, float z) { setScale(glm::vec3(x, y, z)); }
      inline void setScale(const glm::vec2& scaling) { setScale(glm::vec3(scaling, 1)); }
      inline void setScale(const glm::vec3& scaling) { m_scale = scaling; }
      inline const glm::vec3& getScale() const { return m_scale; }
      inline glm::vec3 getInverseScale() const { return glm::vec3(1 / m_scale.x, 1 / m_scale.y, 1 / m_scale.z); }

    private:
      Transform(GameObject& gameObject);

      GameObject* m_gameObject;
      Transform* m_parent;
      std::vector<Transform*> m_children;

      float m_rotation;
      glm::vec3 m_translation;
      glm::vec3 m_scale;

      friend class GameObject;
  };
}