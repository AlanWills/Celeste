#pragma once

#include "CelesteDllExport.h"
#include "Objects/Script.h"

#include <functional>


namespace Celeste
{
  class Path;
  class GameObject;

  namespace Physics
  {
    class RectangleCollider;
  }

  namespace Input
  {
    class MouseInteractionHandler;
  }

  namespace Rendering
  {
    class SpriteRenderer;
  }

  namespace Audio
  {
    class AudioSource;
  }

  namespace Resources
  {
    class Texture2D;
    class Sound;
  }

  namespace UI
  {
    class Button : public Script
    {
      DECLARE_UNMANAGED_COMPONENT(Button, CelesteDllExport)

      public:
        using GameObjectClickCallback = std::function<void(GameObject&)>;

        enum class ButtonState
        {
          kIdle,
          kHighlighted,
          kClicked,
        };

        inline observer_ptr<Resources::Texture2D> getDefaultTexture() const { return m_defaultTexture; }
        CelesteDllExport void setDefaultTexture(const Path& texturePath);

        inline observer_ptr<Resources::Texture2D> getHighlightedTexture() const { return m_highlightedTexture; }
        CelesteDllExport void setHighlightedTexture(const Path& texturePath);
        
        inline observer_ptr<Resources::Texture2D> getClickedTexture() const { return m_clickedTexture; }
        CelesteDllExport void setClickedTexture(const Path& texturePath);

        inline observer_ptr<Resources::Sound> getHighlightedSound() const { return m_highlightedSound; }
        CelesteDllExport void setHighlightedSound(const Path& texturePath);
        
        inline observer_ptr<Resources::Sound> getClickedSound() const { return m_clickedSound; }
        CelesteDllExport void setClickedSound(const Path& texturePath);

        template <typename ...Callbacks>
        void subscribeLeftClickCallback(const GameObjectClickCallback& callback, const Callbacks&... callbacks);
        CelesteDllExport void subscribeLeftClickCallback(const GameObjectClickCallback& callback);

        CelesteDllExport void update(float secondsPerUpdate) override;

      protected:
        inline ButtonState getButtonState() const { return m_state; }
        inline void setButtonState(ButtonState state) { m_state = state; }

      private:
        using Inherited = Script;

        void begin();
        void onEnter();
        void onLeave();
        void onLeftMouseButtonDown();
        void onLeftMouseButtonUp();

        bool m_begun = false;
        float m_clickTimer = 0;
        ButtonState m_state = ButtonState::kIdle;

        observer_ptr<Resources::Texture2D> m_defaultTexture = nullptr;
        observer_ptr<Resources::Texture2D> m_highlightedTexture = nullptr;
        observer_ptr<Resources::Texture2D> m_clickedTexture = nullptr;

        observer_ptr<Resources::Sound> m_highlightedSound = nullptr;
        observer_ptr<Resources::Sound> m_clickedSound = nullptr;

        observer_ptr<Rendering::SpriteRenderer> m_spriteRenderer = nullptr;
        observer_ptr<Input::MouseInteractionHandler> m_mouseInteraction = nullptr;
        observer_ptr<Physics::RectangleCollider> m_collider = nullptr;
        observer_ptr<Audio::AudioSource> m_audio = nullptr;
    };

    //------------------------------------------------------------------------------------------------
    template <typename ...Callbacks>
    void Button::subscribeLeftClickCallback(const GameObjectClickCallback& callback, const Callbacks&... callbacks)
    {
      subscribeLeftClickCallback(callback);
      subscribeLeftClickCallback(callbacks...);
    }
  }
}