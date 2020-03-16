#pragma once

#include "Objects/Component.h"
#include "glm/glm.hpp"


namespace Celeste::Input
{
  class KeyboardTransformer : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(KeyboardTransformer, CelesteDllExport)

    public:
      inline int getTranslateLeftKey() const { return m_translateLeftKey; }
      inline int getTranslateRightKey() const { return m_translateRightKey; }
      inline int getTranslateUpKey() const { return m_translateUpKey; }
      inline int getTranslateDownKey() const { return m_translateDownKey; }
      inline int getRotateLeftKey() const { return m_rotateLeftKey; }
      inline int getRotateRightKey() const { return m_rotateRightKey; }

      inline float getTranslationSpeed() const { return m_translationSpeed; }
      inline float getRotationSpeed() const { return m_rotationSpeed; }

      inline void setTranslateLeftKey(int translateLeftKey) { m_translateLeftKey = translateLeftKey; }
      inline void setTranslateRightKey(int translateRightKey) { m_translateRightKey = translateRightKey; }
      inline void setTranslateUpKey(int translateUpKey) { m_translateUpKey = translateUpKey; }
      inline void setTranslateDownKey(int translateDownKey) { m_translateDownKey = translateDownKey; }
      inline void setRotateLeftKey(int rotateLeftKey) { m_rotateLeftKey = rotateLeftKey; }
      inline void setRotateRightKey(int rotateRightKey) { m_rotateRightKey = rotateRightKey; }

      inline void setTranslationSpeed(float translationSpeed) { m_translationSpeed = translationSpeed; }
      inline void setRotationSpeed(float rotationSpeed) { m_rotationSpeed = rotationSpeed; }

      CelesteDllExport void handleInput() override;
      CelesteDllExport void update(float elapsedGameTime) override;

    protected:
      inline const glm::vec2& getDirectionVector() const { return m_directionVector; }
      inline void setDirectionVector(const glm::vec2& directionVector) { m_directionVector = directionVector; }

      inline float getRotationDelta() const { return m_deltaRotation; }
      inline void setRotationDelta(float delta) { m_deltaRotation = delta; }

    private:
      using Inherited = Component;

      glm::vec2 m_directionVector;
      float m_deltaRotation;

      int m_translateLeftKey;
      int m_translateRightKey;
      int m_translateUpKey;
      int m_translateDownKey;
      int m_rotateLeftKey;
      int m_rotateRightKey;

      float m_translationSpeed;
      float m_rotationSpeed;
  };
}