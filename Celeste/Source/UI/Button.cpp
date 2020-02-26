#include "UI/Button.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Input/MouseInteractionHandler.h"
#include "DataConverters/UI/ButtonDataConverter.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/SpriteRenderer.h"
#include "Audio/AudioSource.h"
#include "FileSystem/Path.h"


namespace Celeste
{
  using namespace Resources;
  using namespace Physics;
  using namespace Audio;
  using namespace Rendering;
  using namespace Input;

  namespace UI
  {
    REGISTER_SCRIPT(Button, 10)

    //------------------------------------------------------------------------------------------------
    Button::Button()
    {
      setDefaultTexture(ButtonDataConverter::getDefaultTextureDefaultPath());
      ASSERT_NOT_NULL(m_defaultTexture);

      setHighlightedTexture(ButtonDataConverter::getHighlightedTextureDefaultPath());
      ASSERT_NOT_NULL(m_highlightedTexture);

      setClickedTexture(ButtonDataConverter::getClickedTextureDefaultPath());
      ASSERT_NOT_NULL(m_clickedTexture);

      setHighlightedSound(ButtonDataConverter::getHighlightedSoundDefaultPath());
      ASSERT_NOT_NULL(m_highlightedSound);

      setClickedSound(ButtonDataConverter::getClickedSoundDefaultPath());
      ASSERT_NOT_NULL(m_clickedSound);
    }

    //------------------------------------------------------------------------------------------------
    void Button::onSetGameObject(GameObject& parent)
    {
      Inherited::onSetGameObject(parent);

      // Set the default texture on the sprite renderer for this button
      m_spriteRenderer = parent.findComponent<SpriteRenderer>();
      ASSERT_NOT_NULL(m_spriteRenderer);
      m_spriteRenderer->setTexture(m_defaultTexture);

      // Set up the collider so that it can respond to mouse interaction
      m_collider = parent.findComponent<RectangleCollider>();
      ASSERT_NOT_NULL(m_collider);
      m_collider->setDimensions(m_spriteRenderer->getDimensions());

      // Set up the events for mouse interaction
      m_mouseInteraction = parent.findComponent<MouseInteractionHandler>();
      ASSERT_NOT_NULL(m_mouseInteraction);
      m_mouseInteraction->getOnEnterEvent().subscribe([this](GameObject&) -> void { onEnter(); });
      m_mouseInteraction->getOnLeaveEvent().subscribe([this](GameObject&) -> void { onLeave(); });
      m_mouseInteraction->getOnLeftButtonDownEvent().subscribe([this](GameObject&) -> void { onLeftMouseButtonDown(); });
      m_mouseInteraction->getOnLeftButtonUpEvent().subscribe([this](GameObject&) -> void { onLeftMouseButtonUp(); });

      // Set up the audio source for this button
      m_audio = parent.findComponent<AudioSource>();
      if (m_audio != nullptr)
      {
          m_audio->setAudioType(AudioType::kSFX);
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::onUpdate(float secondsPerUpdate)
    {
      Inherited::onUpdate(secondsPerUpdate);

      m_clickTimer += secondsPerUpdate;

      if (m_collider->isHitByRay())
      {
        if (m_state != ButtonState::kClicked)
        {
          m_spriteRenderer->setTexture(m_highlightedTexture);
          m_collider->setDimensions(m_spriteRenderer->getDimensions());

          m_state = ButtonState::kHighlighted;
        }
      }
      else
      {
        m_spriteRenderer->setTexture(m_defaultTexture);
        m_collider->setDimensions(m_spriteRenderer->getDimensions());

        m_state = ButtonState::kIdle;
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::onDeath()
    {
      Inherited::onDeath();

      m_state = ButtonState::kIdle;
      m_clickTimer = 0;

      m_defaultTexture = nullptr;
      m_highlightedTexture = nullptr;
      m_clickedTexture = nullptr;
      m_highlightedSound = nullptr;
      m_clickedSound = nullptr;
      m_collider = nullptr;
      m_spriteRenderer = nullptr;
      m_mouseInteraction = nullptr;
      m_audio = nullptr;
    }

    //------------------------------------------------------------------------------------------------
    void Button::onEnter()
    {
      m_spriteRenderer->setTexture(m_highlightedTexture);
      m_collider->setDimensions(m_spriteRenderer->getDimensions());

      if (m_audio != nullptr)
      {
        m_audio->setSound(m_highlightedSound);
        m_audio->play();
      }

      m_state = ButtonState::kHighlighted;
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeave()
    {
      m_spriteRenderer->setTexture(m_defaultTexture);
      m_collider->setDimensions(m_spriteRenderer->getDimensions());

      m_state = ButtonState::kIdle;
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeftMouseButtonDown()
    {
      if (m_state != ButtonState::kClicked)
      {
        m_spriteRenderer->setTexture(m_clickedTexture);
        m_collider->setDimensions(m_spriteRenderer->getDimensions());

        if (m_audio != nullptr)
        {
          m_audio->setSound(m_clickedSound);
          m_audio->play();
        }

        m_state = ButtonState::kClicked;
        m_clickTimer = 0;
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeftMouseButtonUp()
    {
      if (m_state == ButtonState::kClicked)
      {
        // Update loop will sort out proper texture
        m_state = ButtonState::kIdle;
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::subscribeLeftClickCallback(const GameObjectClickCallback& callback)
    {
#if _DEBUG
      if (m_mouseInteraction == nullptr)
      {
        ASSERT_FAIL();
        return;
      }
#endif

      m_mouseInteraction->getOnLeftButtonUpEvent().subscribe(callback);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setDefaultTexture(const Path& path)
    {
      m_defaultTexture = getResourceManager().load<Texture2D>(path);
      ASSERT_NOT_NULL(m_defaultTexture);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setHighlightedTexture(const Path& path)
    {
      m_highlightedTexture = getResourceManager().load<Texture2D>(path);
      ASSERT_NOT_NULL(m_highlightedTexture);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setClickedTexture(const Path& path)
    {
      m_clickedTexture = getResourceManager().load<Texture2D>(path);
      ASSERT_NOT_NULL(m_clickedTexture);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setHighlightedSound(const Path& path)
    {
      m_highlightedSound = getResourceManager().load<Sound>(path);
      ASSERT_NOT_NULL(m_highlightedSound);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setClickedSound(const Path& path)
    {
      m_clickedSound = getResourceManager().load<Sound>(path);
      ASSERT_NOT_NULL(m_clickedSound);
    }
  }
}